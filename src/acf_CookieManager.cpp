
#include "acf_Types.h"
#include "acf_Conv.h"
#include "acf_FrameEvents.h"

#include "include/cef_waitable_event.h"
#include "include/cef_cookie.h"

extern DWORD acf_cookie_manager_funcs[];

ACF_EXPORTS(CookieManagerGetGlobal, BOOL)(DWORD* target)
{
  CefRefPtr<CefCookieManager> lpObj = CefCookieManager::GetGlobalManager(nullptr);

  lpObj->AddRef();
  target[1] = (DWORD)((LPVOID)lpObj.get());
  target[2] = (DWORD)acf_cookie_manager_funcs;

  return !!lpObj;
}

void ECALL cookiemanager_set_supported_schemes(CefCookieManager* obj, LPVOID* schemes,
  bool include_defaults, LPVOID lpCallback, BOOL copyData)
{
  /*ISVALID(obj);

  LPSTR pArgsList = (LPSTR)*schemes;

  int nCount = *(LPINT)(pArgsList + sizeof(INT));

  std::vector<CefString> pArgs(nCount);

  for (size_t i = 0; i < nCount; i++)
  {
    pArgs[i] = (LPSTR)(((LPDWORD)(pArgsList + sizeof(INT) * 2))[i]);
  }

  CefRefPtr<ACFlibCompletionCallback> lpHandler = new ACFlibCompletionCallback(lpCallback, copyData);

  obj->SetSupportedSchemes(pArgs, include_defaults, lpHandler);*/
}

bool ECALL cookiemanager_visit_all_cookies(CefCookieManager* obj, LPVOID lpCallback, BOOL copyData)
{
  ISVALIDR(obj, NULL);

  CefRefPtr<ACFlibCookieVisitor> lpVisitor = new ACFlibCookieVisitor(lpCallback, copyData);

  return obj->VisitAllCookies(lpVisitor);
}

bool ECALL cookiemanager_visit_url_cookies(CefCookieManager* obj, LPCWSTR url, bool httponly, LPVOID lpCallback, BOOL copyData)
{
  ISVALIDR(obj, NULL);

  CefRefPtr<ACFlibCookieVisitor> lpVisitor = new ACFlibCookieVisitor(lpCallback, copyData);

  return obj->VisitUrlCookies(url, httponly, lpVisitor);
}

bool ECALL cookiemanager_set_cookie(CefCookieManager* obj, LPCWSTR url, ACF_COOKIE** cookie)
{
  ISVALIDR(obj, NULL);

  CefCookie dCookie;

  if ((**cookie).name && *(LPWSTR)EStreamToUnicode((**cookie).name) != '\0')
    CefString(&dCookie.name) = EStreamToUnicode((**cookie).name);
  if ((**cookie).value && *(LPWSTR)EStreamToUnicode((**cookie).value) != '\0')
    CefString(&dCookie.value) = EStreamToUnicode((**cookie).value);
  if ((**cookie).domain && *(LPWSTR)EStreamToUnicode((**cookie).domain) != '\0')
    CefString(&dCookie.domain) = EStreamToUnicode((**cookie).domain);
  if ((**cookie).path && *(LPWSTR)EStreamToUnicode((**cookie).path) != '\0')
    CefString(&dCookie.path) = EStreamToUnicode((**cookie).path);

  dCookie.secure = (**cookie).secure;
  dCookie.httponly = (**cookie).httponly;
  dCookie.has_expires = (**cookie).has_expires;

  cef_time_to_basetime((**cookie).creation, &dCookie.creation);
  cef_time_to_basetime((**cookie).last_access, &dCookie.last_access);
  cef_time_to_basetime((**cookie).expires, &dCookie.expires);

  dCookie.same_site = (cef_cookie_same_site_t)(**cookie).same_site;
  dCookie.priority = (cef_cookie_priority_t)(**cookie).priority;

  return obj->SetCookie(url, dCookie, nullptr);
}

bool ECALL cookiemanager_delete_cookies(CefCookieManager* obj, LPCWSTR url, LPCWSTR cookie_name)
{
  ISVALIDR(obj, NULL);

  return obj->DeleteCookies(url, cookie_name, nullptr);
}

bool ECALL cookiemanager_flush_store(CefCookieManager* obj, LPVOID lpCallback, BOOL copyData)
{
  ISVALIDR(obj, NULL);

  CefRefPtr<ACFlibCompletionCallback> lpHandler = lpCallback ? new ACFlibCompletionCallback(lpCallback, copyData) : nullptr;

  return obj->FlushStore(lpHandler);
}

class ACFlibCookieVisitorSync : public CefCookieVisitor
{
public:
  ACFlibCookieVisitorSync(CefRefPtr<CefWaitableEvent> lock) : m_lock(lock) {}
  ~ACFlibCookieVisitorSync() = default;

  std::vector<CefCookie>& GetResult() { return m_cookies; }

private:
  CefRefPtr<CefWaitableEvent> m_lock;
  std::vector<CefCookie> m_cookies;

protected:

  virtual bool Visit(const CefCookie& cookie,
    int count,
    int total,
    bool& deleteCookie)  OVERRIDE {
    m_cookies.push_back(cookie);

    if (count + 1 >= total)
      m_lock->Signal();

    return true;
  };

  IMPLEMENT_REFCOUNTING(ACFlibCookieVisitorSync);
};

PACF_COOKIE transfer_cookie_data(const CefCookie& cookie);

bool ECALL cookiemanager_visit_all_cookies_sync(CefCookieManager* obj, int max_ms, LPVOID* eArray)
{
  ISVALIDR(obj, false);

  CefRefPtr<CefWaitableEvent> lock = CefWaitableEvent::CreateWaitableEvent(true, false);
  CefRefPtr<ACFlibCookieVisitorSync> lpHandler = new ACFlibCookieVisitorSync(lock);

  obj->VisitAllCookies(lpHandler);
  lock->TimedWait(max_ms);

  FreeAryElement(*eArray);
  std::vector<CefCookie>& data = lpHandler->GetResult();

  DWORD* pStrs = new DWORD[data.size()];
  for (size_t i = 0; i < data.size(); i++)
    pStrs[i] = (DWORD)transfer_cookie_data(data[i]);

  int nSize = data.size() * sizeof(DWORD);
  LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
  *(LPINT)pAry = 1;
  *(LPINT)(pAry + sizeof(INT)) = data.size();
  memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
  delete[]pStrs;

  *eArray = pAry;

  return !!lpHandler->GetResult().size();
}

bool ECALL cookiemanager_visit_url_cookies_sync(CefCookieManager* obj, LPWSTR url, bool httpOnly, int max_ms, LPVOID* eArray)
{
  ISVALIDR(obj, false);

  CefRefPtr<CefWaitableEvent> lock = CefWaitableEvent::CreateWaitableEvent(true, false);
  CefRefPtr<ACFlibCookieVisitorSync> lpHandler = new ACFlibCookieVisitorSync(lock);

  obj->VisitUrlCookies(url, httpOnly, lpHandler);
  lock->TimedWait(max_ms);

  FreeAryElement(*eArray);
  std::vector<CefCookie>& data = lpHandler->GetResult();

  DWORD* pStrs = new DWORD[data.size()];
  for (size_t i = 0; i < data.size(); i++)
    pStrs[i] = (DWORD)transfer_cookie_data(data[i]);

  int nSize = data.size() * sizeof(DWORD);
  LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
  *(LPINT)pAry = 1;
  *(LPINT)(pAry + sizeof(INT)) = data.size();
  memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
  delete[]pStrs;

  *eArray = pAry;

  return !!lpHandler->GetResult().size();
}

BOOL ECALL cookiemanager_clear_data_for_origin(CefCookieManager* obj,
  uint32_t remove_mask,
  uint32_t quota_storage_remove_mask,
  LPCWSTR storage_origin,
  LPVOID lpCallback, BOOL copyData)
{
  ISVALIDR(obj, FALSE);

  CefRefPtr<ACFlibCompletionCallback> lpHandler = lpCallback ? new ACFlibCompletionCallback(lpCallback, copyData) : nullptr;

  return obj->ClearDataForOrigin(remove_mask, quota_storage_remove_mask, storage_origin, lpHandler);
}

DWORD acf_cookie_manager_funcs[] = {
  (DWORD)&cookiemanager_set_supported_schemes,
  (DWORD)&cookiemanager_visit_all_cookies,
  (DWORD)&cookiemanager_visit_url_cookies,
  (DWORD)&cookiemanager_set_cookie,
  (DWORD)&cookiemanager_delete_cookies,
  (DWORD)&cookiemanager_flush_store,
  (DWORD)&cookiemanager_visit_all_cookies_sync,
  (DWORD)&cookiemanager_visit_url_cookies_sync,
  (DWORD)&cookiemanager_clear_data_for_origin,
};
