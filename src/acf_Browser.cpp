
#include "acf_Types.h"
#include "acf_Conv.h"

#include "include/cef_browser.h"

extern DWORD acf_browser_funcs[];
extern DWORD acf_browser_host_funcs[];
extern DWORD acf_frame_funcs[];
extern DWORD acf_dictionary_funcs[];

bool ECALL browser_get_host(CefBrowser* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefBrowserHost> dupObj = obj->GetHost();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_browser_host_funcs;

	return dupObj != NULL;
}

bool ECALL browser_can_go_back(CefBrowser* obj)
{
	ISVALIDR(obj, false);

	return obj->CanGoBack();
}

void ECALL browser_go_back(CefBrowser* obj)
{
	ISVALID(obj);

	obj->GoBack();
}

bool ECALL browser_can_go_forward(CefBrowser* obj)
{
	ISVALIDR(obj, false);

	return obj->CanGoForward();
}

void ECALL browser_go_forward(CefBrowser* obj)
{
	ISVALID(obj);

	obj->GoForward();
}

bool ECALL browser_is_loading(CefBrowser* obj)
{
	ISVALIDR(obj, false);

	return obj->IsLoading();
}

void ECALL browser_reload(CefBrowser* obj)
{
	ISVALID(obj);

	obj->Reload();
}

void ECALL browser_reload_ignore_cache(CefBrowser* obj)
{
	ISVALID(obj);

	obj->ReloadIgnoreCache();
}

void ECALL browser_stopload(CefBrowser* obj)
{
	ISVALID(obj);

	obj->StopLoad();
}

int ECALL browser_getidentifier(CefBrowser* obj)
{
	ISVALIDR(obj, 0);

	return obj->GetIdentifier();
}

bool ECALL browser_is_same(CefBrowser* obj, CefBrowser* that)
{
	ISVALIDR(obj, false);

	return obj->IsSame(that);
}

bool ECALL browser_is_popup(CefBrowser* obj)
{
	ISVALIDR(obj, false);

	return obj->IsPopup();
}

bool ECALL browser_has_document(CefBrowser* obj)
{
	ISVALIDR(obj, false);

	return obj->HasDocument();
}

bool ECALL browser_get_main_frame(CefBrowser* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefFrame> lpFrame = obj->GetMainFrame();

	lpFrame->AddRef();
	target[1] = (DWORD)((LPVOID)lpFrame.get());
	target[2] = (DWORD)acf_frame_funcs;

	return lpFrame != NULL;
}

bool ECALL browser_get_focused_frame(CefBrowser* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefFrame> lpFrame = obj->GetFocusedFrame();

	lpFrame->AddRef();
	target[1] = (DWORD)((LPVOID)lpFrame.get());
	target[2] = (DWORD)acf_frame_funcs;

	return lpFrame != NULL;
}

bool ECALL browser_get_frame_id(CefBrowser* obj, int64* id, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefFrame> lpFrame = obj->GetFrame(*id);

	if (lpFrame)
		lpFrame->AddRef();
	target[1] = (DWORD)((LPVOID)lpFrame.get());
	target[2] = (DWORD)acf_frame_funcs;

	return lpFrame != NULL;
}

bool ECALL browser_get_frame_name(CefBrowser* obj, LPCWSTR name, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefFrame> lpFrame = obj->GetFrame(name);

	if (lpFrame)
		lpFrame->AddRef();
	target[1] = (DWORD)((LPVOID)lpFrame.get());
	target[2] = (DWORD)acf_frame_funcs;

	return lpFrame != NULL;
}

int ECALL browser_get_frame_count(CefBrowser* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetFrameCount();
}

bool ECALL browser_get_frame_identifiers(CefBrowser* obj, LPVOID* eArray)
{
	ISVALIDR(obj, NULL);

	std::vector<int64> data;

	obj->GetFrameIdentifiers(data);

	FreeAryElement(*eArray);

	int nSize = data.size() * sizeof(int64);
	LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
	*(LPINT)pAry = 1;
	*(LPINT)(pAry + sizeof(INT)) = data.size();
	memcpy(pAry + sizeof(INT) * 2, data.data(), nSize);

	*eArray = pAry;

	return !!eArray;
}

bool ECALL browser_get_frame_names(CefBrowser* obj, LPVOID* eArray)
{
	ISVALIDR(obj, NULL);

	std::vector<CefString> keys;
	obj->GetFrameNames(keys);

	DWORD* pStrs = new DWORD[keys.size()];
	USES_CONVERSION;
	for (size_t i = 0; i < keys.size(); i++)
	{
		pStrs[i] = (DWORD)UnicodeToEStream(keys[i].c_str());
	}

	FreeAryElement(*eArray);

	int nSize = keys.size() * sizeof(DWORD);
	LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
	*(LPINT)pAry = 1;
	*(LPINT)(pAry + sizeof(INT)) = keys.size();
	memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
	delete[]pStrs;

	*eArray = pAry;

	return 0;
}

bool ECALL browser_get_extra_info(CefBrowser* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDictionaryValue> lpFrame = obj->GetExtraInfo();

	if (lpFrame)
		lpFrame->AddRef();
	target[1] = (DWORD)((LPVOID)lpFrame.get());
	target[2] = (DWORD)acf_dictionary_funcs;

	return lpFrame != NULL;
}

DWORD acf_browser_funcs[] = {
	(DWORD)&browser_get_host,
	(DWORD)&browser_can_go_back,
	(DWORD)&browser_go_back,
	(DWORD)&browser_can_go_forward,
	(DWORD)&browser_go_forward,
	(DWORD)&browser_is_loading,
	(DWORD)&browser_reload,
	(DWORD)&browser_reload_ignore_cache,
	(DWORD)&browser_stopload,
	(DWORD)&browser_getidentifier,
	(DWORD)&browser_is_same,
	(DWORD)&browser_is_popup,
	(DWORD)&browser_has_document,
	(DWORD)&browser_get_main_frame,
	(DWORD)&browser_get_focused_frame,
	(DWORD)&browser_get_frame_id,
	(DWORD)&browser_get_frame_name,
	(DWORD)&browser_get_frame_count,
	(DWORD)&browser_get_frame_identifiers,
	(DWORD)&browser_get_frame_names,
	(DWORD)&browser_get_extra_info,
};