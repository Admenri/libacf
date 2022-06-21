
#include "acf_Types.h"
#include "acf_Conv.h"
#include "acf_FrameEvents.h"

#include "include/cef_cookie.h"

extern DWORD acf_cookie_manager_funcs[];

ACF_EXPORTS(CookieManagerGetGlobal, BOOL)(DWORD* target)
{
	CefRefPtr<CefCookieManager> lpObj = CefCookieManager::GetGlobalManager(NULL);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_cookie_manager_funcs;

	return !!lpObj;
}

void ECALL cookiemanager_set_supported_schemes(CefCookieManager* obj, LPVOID* schemes,
	bool include_defaults, LPVOID lpCallback, BOOL copyData)
{
	ISVALID(obj);

	LPSTR pArgsList = (LPSTR)*schemes;

	int nCount = *(LPINT)(pArgsList + sizeof(INT));

	std::vector<CefString> pArgs(nCount);

	for (size_t i = 0; i < nCount; i++)
	{
		pArgs[i] = (LPSTR)(((LPDWORD)(pArgsList + sizeof(INT) * 2))[i]);
	}

	CefRefPtr<ACFlibCompletionCallback> lpHandler = new ACFlibCompletionCallback(lpCallback, copyData);

	obj->SetSupportedSchemes(pArgs, include_defaults, lpHandler);
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

	dCookie.creation = *(**cookie).creation;
	dCookie.last_access = *(**cookie).last_access;
	dCookie.expires = *(**cookie).expires;

	dCookie.same_site = (cef_cookie_same_site_t)(**cookie).same_site;
	dCookie.priority = (cef_cookie_priority_t)(**cookie).priority;

	return obj->SetCookie(url, dCookie, NULL);
}

bool ECALL cookiemanager_delete_cookies(CefCookieManager* obj, LPCWSTR url, LPCWSTR cookie_name)
{
	ISVALIDR(obj, NULL);

	return obj->DeleteCookies(url, cookie_name, NULL);
}

bool ECALL cookiemanager_flush_store(CefCookieManager* obj, LPVOID lpCallback, BOOL copyData)
{
	ISVALIDR(obj, NULL);

	CefRefPtr<ACFlibCompletionCallback> lpHandler = new ACFlibCompletionCallback(lpCallback, copyData);

	return obj->FlushStore(lpHandler);
}

DWORD acf_cookie_manager_funcs[] = {
	(DWORD)&cookiemanager_set_supported_schemes,
	(DWORD)&cookiemanager_visit_all_cookies,
	(DWORD)&cookiemanager_visit_url_cookies,
	(DWORD)&cookiemanager_set_cookie,
	(DWORD)&cookiemanager_delete_cookies,
	(DWORD)&cookiemanager_flush_store,
};
