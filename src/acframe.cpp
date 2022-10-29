
#include "acframe.h"
#include "acf_Class.h"
#include "acf_ResourceFilter.h"
#include "acf_FrameEvents.h"
#include "acf_Scheme.h"

#include <string>

#include "include/cef_base.h"
#include "include/cef_browser.h"
#include "include/cef_parser.h"
#include "include/cef_urlrequest.h"
#include "include/cef_waitable_event.h"
#include "include/cef_api_hash.h"
#include "include/cef_server.h"

#include "include/views/cef_browser_view.h"
#include "include/views/cef_view.h"
#include "include/views/cef_window.h"
#include "include/views/cef_panel.h"

namespace {
	WindowEventCallback g_pListWindowEvent;
}

ACF_EXPORTS(SetGoogleAPIInfo, void)(int type, const char* value)
{
	// FIXME
}

// 增加引用
ACF_EXPORTS(AddRef, void)(LPVOID object, int nType)
{
	if (object != 0)
	{
		switch (nType)
		{
		case 10000:
			static_cast<CefCommandLine*>(object)->AddRef();
			break;
		case 10001:
			static_cast<CefBrowser*>(object)->AddRef();
			break;
		case 10002:
			static_cast<CefBrowserHost*>(object)->AddRef();
			break;
		case 10003:
			static_cast<CefFrame*>(object)->AddRef();
			break;
		case 10004:
			static_cast<CefMenuModel*>(object)->AddRef();
			break;
		case 10005:
			static_cast<CefContextMenuParams*>(object)->AddRef();
			break;
		case 10006:
			static_cast<CefRequest*>(object)->AddRef();
			break;
		case 10007:
			static_cast<CefValue*>(object)->AddRef();
			break;
		case 10008:
			static_cast<CefBinaryValue*>(object)->AddRef();
			break;
		case 10009:
			static_cast<CefDictionaryValue*>(object)->AddRef();
			break;
		case 10010:
			static_cast<CefListValue*>(object)->AddRef();
			break;
		case 10011:
			static_cast<CefDownloadItem*>(object)->AddRef();
			break;
		case 10012:
			static_cast<CefDragData*>(object)->AddRef();
			break;
		case 10013:
			static_cast<CefImage*>(object)->AddRef();
			break;
		case 10014:
			static_cast<CefV8Context*>(object)->AddRef();
			break;
		case 10015:
			static_cast<CefTaskRunner*>(object)->AddRef();
			break;
		case 10016:
			static_cast<CefV8Value*>(object)->AddRef();
			break;
		case 10017:
			static_cast<CefV8Exception*>(object)->AddRef();
			break;
		case 10018:
			static_cast<CefV8StackTrace*>(object)->AddRef();
			break;
		case 10019:
			static_cast<CefV8StackFrame*>(object)->AddRef();
			break;
		case 10020:
			static_cast<CefProcessMessage*>(object)->AddRef();
			break;
		case 10021:
			static_cast<CefRequestContext*>(object)->AddRef();
			break;
		case 10022:
			static_cast<CefCookieManager*>(object)->AddRef();
			break;
		case 10023:
			static_cast<CefNavigationEntry*>(object)->AddRef();
			break;
		case 10024:
			static_cast<CefSSLStatus*>(object)->AddRef();
			break;
		case 10025:
			static_cast<CefPostData*>(object)->AddRef();
			break;
		case 10026:
			static_cast<CefPostDataElement*>(object)->AddRef();
			break;
		case 10027:
			static_cast<CefURLRequest*>(object)->AddRef();
			break;
		case 10028:
			static_cast<CefX509Certificate*>(object)->AddRef();
			break;
		case 10029:
			static_cast<CefX509CertPrincipal*>(object)->AddRef();
			break;
		case 10030:
			static_cast<CefResponse*>(object)->AddRef();
			break;
		case 10031:
			static_cast<ACFResourceFilter*>(object)->AddRef();
			break;
		case 10032:
			static_cast<CefDOMDocument*>(object)->AddRef();
			break;
		case 10033:
			static_cast<CefDOMNode*>(object)->AddRef();
			break;
		case 10034:
			static_cast<CefWaitableEvent*>(object)->AddRef();
			break;
		case 10035:
			static_cast<CefSSLInfo*>(object)->AddRef();
			break;
		case 10036:
			static_cast<CefExtension*>(object)->AddRef();
			break;
		case 10037:
			static_cast<CefStreamReader*>(object)->AddRef();
			break;
		case 10038:
			static_cast<CefStreamWriter*>(object)->AddRef();
			break;
		case 10039:
			static_cast<CefServer*>(object)->AddRef();
			break;
		case 10040:
			static_cast<CefView*>(object)->AddRef();
			break;
		case 10041:
			static_cast<CefWindow*>(object)->AddRef();
			break;
		case 10042:
			static_cast<CefPanel*>(object)->AddRef();
			break;
		case 10043:
			static_cast<CefBrowserView*>(object)->AddRef();
			break;


		case 30000:
			static_cast<CefRunContextMenuCallback*>(object)->AddRef();
			break;
		case 30001:
			static_cast<CefDownloadItemCallback*>(object)->AddRef();
			break;
		case 30002:
			static_cast<CefBeforeDownloadCallback*>(object)->AddRef();
			break;
		case 30003:
			static_cast<CefJSDialogCallback*>(object)->AddRef();
			break;
		case 30004:
			static_cast<CefFileDialogCallback*>(object)->AddRef();
			break;
		case 30005:
			static_cast<CefAuthCallback*>(object)->AddRef();
			break;
		case 30006:
			static_cast<CefCallback*>(object)->AddRef();
			break;
		case 30007:
			static_cast<CefSelectClientCertificateCallback*>(object)->AddRef();
			break;
		case 30008:
			static_cast<CefResourceReadCallback*>(object)->AddRef();
			break;
		case 30009:
			static_cast<CefResourceSkipCallback*>(object)->AddRef();
			break;
		case 30010:
			static_cast<CefCallback*>(object)->AddRef();
			break;
		case 30011:
			static_cast<ACFV8RetValCallback*>(object)->AddRef();
			break;
		case 30012:
			static_cast<ACFOnPopupRetCallback*>(object)->AddRef();
			break;
		case 30013:
			static_cast<CefGetExtensionResourceCallback*>(object)->AddRef();
			break;
		case 30014:
			static_cast<CefMediaAccessCallback*>(object)->AddRef();
			break;
		case 30015:
			static_cast<CefPermissionPromptCallback*>(object)->AddRef();
			break;

		default:
			break;
		}
	}
}

// 释放引用
ACF_EXPORTS(Release, void)(LPVOID object, int nType)
{
	if (object != 0)
	{
		switch (nType)
		{
		case 10000:
			static_cast<CefCommandLine*>(object)->Release();
			break;
		case 10001:
			static_cast<CefBrowser*>(object)->Release();
			break;
		case 10002:
			static_cast<CefBrowserHost*>(object)->Release();
			break;
		case 10003:
			static_cast<CefFrame*>(object)->Release();
			break;
		case 10004:
			static_cast<CefMenuModel*>(object)->Release();
			break;
		case 10005:
			static_cast<CefContextMenuParams*>(object)->Release();
			break;
		case 10006:
			static_cast<CefRequest*>(object)->Release();
			break;
		case 10007:
			static_cast<CefValue*>(object)->Release();
			break;
		case 10008:
			static_cast<CefBinaryValue*>(object)->Release();
			break;
		case 10009:
			static_cast<CefDictionaryValue*>(object)->Release();
			break;
		case 10010:
			static_cast<CefListValue*>(object)->Release();
			break;
		case 10011:
			static_cast<CefDownloadItem*>(object)->Release();
			break;
		case 10012:
			static_cast<CefDragData*>(object)->Release();
			break;
		case 10013:
			static_cast<CefImage*>(object)->Release();
			break;
		case 10014:
			static_cast<CefV8Context*>(object)->Release();
			break;
		case 10015:
			static_cast<CefTaskRunner*>(object)->Release();
			break;
		case 10016:
			static_cast<CefV8Value*>(object)->Release();
			break;
		case 10017:
			static_cast<CefV8Exception*>(object)->Release();
			break;
		case 10018:
			static_cast<CefV8StackTrace*>(object)->Release();
			break;
		case 10019:
			static_cast<CefV8StackFrame*>(object)->Release ();
			break;
		case 10020:
			static_cast<CefProcessMessage*>(object)->Release();
			break;
		case 10021:
			static_cast<CefRequestContext*>(object)->Release();
			break;
		case 10022:
			static_cast<CefCookieManager*>(object)->Release();
			break;
		case 10023:
			static_cast<CefNavigationEntry*>(object)->Release();
			break;
		case 10024:
			static_cast<CefSSLStatus*>(object)->Release();
			break;
		case 10025:
			static_cast<CefPostData*>(object)->Release();
			break;
		case 10026:
			static_cast<CefPostDataElement*>(object)->Release();
			break;
		case 10027:
			static_cast<CefURLRequest*>(object)->Release();
			break;
		case 10028:
			static_cast<CefX509Certificate*>(object)->Release();
			break;
		case 10029:
			static_cast<CefX509CertPrincipal*>(object)->Release();
			break;
		case 10030:
			static_cast<CefResponse*>(object)->Release();
			break;
		case 10031:
			static_cast<ACFResourceFilter*>(object)->Release();
			break;
		case 10032:
			static_cast<CefDOMDocument*>(object)->Release();
			break;
		case 10033:
			static_cast<CefDOMNode*>(object)->Release();
			break;
		case 10034:
			static_cast<CefWaitableEvent*>(object)->Release();
			break;
		case 10035:
			static_cast<CefSSLInfo*>(object)->Release();
			break;
		case 10036:
			static_cast<CefExtension*>(object)->Release();
			break;
		case 10037:
			static_cast<CefStreamReader*>(object)->Release();
			break;
		case 10038:
			static_cast<CefStreamWriter*>(object)->Release();
			break;
		case 10039:
			static_cast<CefServer*>(object)->Release();
			break;
		case 10040:
			static_cast<CefView*>(object)->Release();
			break;
		case 10041:
			static_cast<CefWindow*>(object)->Release();
			break;
		case 10042:
			static_cast<CefPanel*>(object)->Release();
			break;
		case 10043:
			static_cast<CefBrowserView*>(object)->Release();
			break;

		case 30000:
			static_cast<CefRunContextMenuCallback*>(object)->Release();
			break;
		case 30001:
			static_cast<CefDownloadItemCallback*>(object)->Release();
			break;
		case 30002:
			static_cast<CefBeforeDownloadCallback*>(object)->Release();
			break;
		case 30003:
			static_cast<CefJSDialogCallback*>(object)->Release();
			break;
		case 30004:
			static_cast<CefFileDialogCallback*>(object)->Release();
			break;
		case 30005:
			static_cast<CefAuthCallback*>(object)->Release();
			break;
		case 30006:
			static_cast<CefCallback*>(object)->Release();
			break;
		case 30007:
			static_cast<CefSelectClientCertificateCallback*>(object)->Release();
			break;
		case 30008:
			static_cast<CefResourceReadCallback*>(object)->Release();
			break;
		case 30009:
			static_cast<CefResourceSkipCallback*>(object)->Release();
			break;
		case 30010:
			static_cast<CefCallback*>(object)->Release();
			break;
		case 30011:
			static_cast<ACFV8RetValCallback*>(object)->Release();
			break;
		case 30012:
			static_cast<ACFOnPopupRetCallback*>(object)->Release();
			break;
		case 30013:
			static_cast<CefGetExtensionResourceCallback*>(object)->Release();
			break;
		case 30014:
			static_cast<CefMediaAccessCallback*>(object)->Release();
			break;
		case 30015:
			static_cast<CefPermissionPromptCallback*>(object)->Release();
			break;

		default:
			break;
		}
	}
}

ACF_EXPORTS(ExecuteProcess, int)(LPVOID lpAppEvents, BOOL copyData)
{
	CefMainArgs main_args(GetModuleHandle(NULL));
	CefRefPtr<ACFlibApp> lpObjApp = new ACFlibApp(lpAppEvents, copyData);

	return CefExecuteProcess(main_args, lpObjApp, NULL);
}

ACF_EXPORTS(Initialize, BOOL)(PACF_BASIC_INFO lpBasicInfo, LPVOID lpAppEvents, BOOL copyData)
{
	CefMainArgs main_args(GetModuleHandle(NULL));
	CefSettings basic_info;
	CefRefPtr<ACFlibApp> lpObjApp = lpAppEvents ? new ACFlibApp(lpAppEvents, copyData) : nullptr;

	wchar_t* lpwszBuffer = 0;
#define TRANS_SETTING_STR(name) \
	if (lpBasicInfo->##name && *lpBasicInfo->##name != '\0') { CefString(&basic_info.##name##) = lpBasicInfo->##name##; }
#define TRANS_SETTING(name) \
	basic_info.##name = lpBasicInfo->##name;

	TRANS_SETTING_STR(browser_subprocess_path);
	TRANS_SETTING_STR(cache_path);
	TRANS_SETTING_STR(root_cache_path);
	TRANS_SETTING_STR(user_data_path);
	TRANS_SETTING_STR(user_agent);
	TRANS_SETTING_STR(locale);
	TRANS_SETTING_STR(log_file);
	TRANS_SETTING_STR(javascript_flags);
	TRANS_SETTING_STR(resources_dir_path);
	TRANS_SETTING_STR(locales_dir_path);
	TRANS_SETTING_STR(accept_language_list);

	TRANS_SETTING(no_sandbox);
	TRANS_SETTING(chrome_runtime);
	TRANS_SETTING(multi_threaded_message_loop);
	TRANS_SETTING(external_message_pump);
	TRANS_SETTING(windowless_rendering_enabled);
	TRANS_SETTING(command_line_args_disabled);
	TRANS_SETTING(persist_session_cookies);
	TRANS_SETTING(persist_user_preferences);
	TRANS_SETTING(pack_loading_disabled);
	TRANS_SETTING(remote_debugging_port);
	TRANS_SETTING(uncaught_exception_stack_size);
	TRANS_SETTING(background_color);
	basic_info.log_severity = (cef_log_severity_t)lpBasicInfo->log_severity;

#undef TRANS_SETTINGS_STR
#undef TRANS_SETTINGS

	return CefInitialize(main_args, basic_info, lpObjApp, NULL);
}

ACF_EXPORTS(CreateClient, LPVOID)(LPVOID lpClientEvents, BOOL copyData)
{
	CefRefPtr<ACFlibClient> lpObjClient = new ACFlibClient(lpClientEvents, copyData);

	lpObjClient->AddRef();
	return lpObjClient.get();
}

ACF_EXPORTS(ReleaseClient, void)(ACFlibClient* lpObjClient)
{
	delete lpObjClient;
}

ACF_EXPORTS(CreateBrowser, BOOL)(ACFlibClient* lpObjClient, DWORD* window_info, LPWSTR url, DWORD* browser_settings, CefDictionaryValue* extra_info, CefRequestContext* context)
{
	auto pInfo = reinterpret_cast<CefWindowInfo*>(window_info[1]);
	auto settings = reinterpret_cast<CefBrowserSettings*>(browser_settings[1]);

	return CefBrowserHost::CreateBrowser((*pInfo), lpObjClient, url, (*settings), extra_info, context);
}

ACF_EXPORTS(CreateBrowserSync, void)(ACFlibClient* lpObjClient, DWORD* window_info, LPWSTR url, DWORD* browser_settings, CefDictionaryValue* extra_info, CefRequestContext* context, DWORD* pRetVal)
{
	CefRefPtr<CefBrowser> lpObjBrowser = nullptr;
	auto pInfo = reinterpret_cast<CefWindowInfo*>(window_info[1]);
	auto settings = reinterpret_cast<CefBrowserSettings*>(browser_settings[1]);

	lpObjBrowser = CefBrowserHost::CreateBrowserSync(*pInfo, lpObjClient, url, *settings, extra_info, context);
	if (lpObjBrowser)
	{
		lpObjBrowser->AddRef();
		pRetVal[1] = (DWORD)((LPVOID)lpObjBrowser.get());
		pRetVal[2] = (DWORD)acf_browser_funcs;
	}
}

ACF_EXPORTS(CloseAllBrowsers, void)(ACFlibClient* lpObjClient)
{
	if (!lpObjClient)
		return;

	lpObjClient->CloseAllBrowsers();
}

ACF_EXPORTS(GetBrowserObject, void)(ACFlibClient* lpObjClient, HWND hWnd, DWORD* pRetVal)
{
	if (pRetVal == NULL) return;
	CefRefPtr<CefBrowser> lpObjBrowser = nullptr;
	if (lpObjClient != NULL)
	{
		lpObjBrowser = lpObjClient->GetBrowserObject(hWnd);
		if (lpObjBrowser != NULL)
		{
			lpObjBrowser->AddRef();
			pRetVal[1] = (DWORD)((LPVOID)lpObjBrowser.get());
			pRetVal[2] = (DWORD)acf_browser_funcs;
		}
	}
}

ACF_EXPORTS(GetBrowserObjectAt, void)(ACFlibClient* lpObjClient, int index, DWORD* pRetVal)
{
	if (pRetVal == NULL) return;
	CefRefPtr<CefBrowser> lpObjBrowser = nullptr;
	if (lpObjClient != NULL)
	{
		lpObjBrowser = lpObjClient->GetBrowserObjectAt(index);
		if (lpObjBrowser != NULL)
		{
			lpObjBrowser->AddRef();
			pRetVal[1] = (DWORD)((LPVOID)lpObjBrowser.get());
			pRetVal[2] = (DWORD)acf_browser_funcs;
		}
	}
}

ACF_EXPORTS(GetBrowserObjectId, void)(ACFlibClient* lpObjClient, int identity, DWORD* pRetVal)
{
	if (pRetVal == NULL) return;
	CefRefPtr<CefBrowser> lpObjBrowser = nullptr;
	if (lpObjClient != NULL)
	{
		lpObjBrowser = lpObjClient->GetBrowserObjectId(identity);
		if (lpObjBrowser != NULL)
		{
			lpObjBrowser->AddRef();
			pRetVal[1] = (DWORD)((LPVOID)lpObjBrowser.get());
			pRetVal[2] = (DWORD)acf_browser_funcs;
		}
	}
}

ACF_EXPORTS(GetBrowserCount, int)(ACFlibClient* lpObjClient)
{
	if (lpObjClient != NULL)
	{
		return lpObjClient->GetItemsCount();
	}
	return 0;
}

ACF_EXPORTS(NewWindowInfo, LPVOID)() {
	return new CefWindowInfo;
}

ACF_EXPORTS(DelWindowInfo, void)(LPVOID object) {
	CefWindowInfo* pObject = reinterpret_cast<CefWindowInfo*>(object);
	delete pObject;
}

ACF_EXPORTS(NewBrowserSettings, LPVOID)(void) {
	return new CefBrowserSettings;
}

ACF_EXPORTS(DelBrowserSettings, void)(LPVOID object) {
	CefBrowserSettings* pObject = reinterpret_cast<CefBrowserSettings*>(object);
	delete pObject;
}

ACF_EXPORTS(SetBrowserSettingsState, void)(LPVOID object, int index, cef_state_t value) {
	CefBrowserSettings* settings = reinterpret_cast<CefBrowserSettings*>(object);
	switch (index)
	{
	case 0:
		settings->remote_fonts = value;
		break;
	case 1:
		settings->javascript = value;
		break;
	case 2:
		settings->javascript_close_windows = value;
		break;
	case 3:
		settings->javascript_access_clipboard = value;
		break;
	case 4:
		settings->javascript_dom_paste = value;
		break;
	case 5:
		settings->image_loading = value;
		break;
	case 6:
		settings->image_shrink_standalone_to_fit = value;
		break;
	case 7:
		settings->text_area_resize = value;
		break;
	case 8:
		settings->tab_to_links = value;
		break;
	case 9:
		settings->local_storage = value;
		break;
	case 10:
		settings->databases = value;
		break;
	case 11:
		settings->webgl = value;
		break;
	default:
		break;
	}
}

ACF_EXPORTS(SetBrowserSettingsStr, void)(LPVOID object, int index, LPWSTR value) {
	CefBrowserSettings* settings = reinterpret_cast<CefBrowserSettings*>(object);
	switch (index)
	{
	case 0:
		CefString(&settings->standard_font_family) = value;
		break;
	case 1:
		CefString(&settings->fixed_font_family) = value;
		break;
	case 2:
		CefString(&settings->serif_font_family) = value;
		break;
	case 3:
		CefString(&settings->sans_serif_font_family) = value;
		break;
	case 4:
		CefString(&settings->cursive_font_family) = value;
		break;
	case 5:
		CefString(&settings->fantasy_font_family) = value;
		break;
	case 6:
		CefString(&settings->default_encoding) = value;
		break;
	case 7:
		CefString(&settings->accept_language_list) = value;
		break;
	default:
		break;
	}
}

ACF_EXPORTS(SetBrowserSettingsInt, void)(LPVOID object, int index, int value) {
	CefBrowserSettings* settings = reinterpret_cast<CefBrowserSettings*>(object);
	switch (index)
	{
	case 0:
		settings->windowless_frame_rate = value;
		break;
	case 1:
		settings->default_font_size = value;
		break;
	case 2:
		settings->default_fixed_font_size = value;
		break;
	case 3:
		settings->minimum_font_size = value;
		break;
	case 4:
		settings->minimum_logical_font_size = value;
		break;
	case 5:
		settings->background_color = value;
		break;
	default:
		break;
	}
}

ACF_EXPORTS(SetWindowInfoChild, void)(LPVOID object, HWND parent, int x, int y, int nWidth, int nHeight) {
	CefWindowInfo* info = reinterpret_cast<CefWindowInfo*>(object);
	CefRect rc;
	rc.x = x;
	rc.y = y;
	rc.width = nWidth;
	rc.height = nHeight;
	info->SetAsChild(parent, rc);
}

ACF_EXPORTS(SetWindowInfoPopup, void)(LPVOID object, HWND parent, LPWSTR name) {
	CefWindowInfo* info = reinterpret_cast<CefWindowInfo*>(object);
	info->SetAsPopup(parent, name);
}

ACF_EXPORTS(SetWindowInfoWindowless, void)(LPVOID object, HWND parent, bool shared_texture) {
	CefWindowInfo* info = reinterpret_cast<CefWindowInfo*>(object);
	info->SetAsWindowless(parent);
	info->shared_texture_enabled = shared_texture;
}

ACF_EXPORTS(SetWindowInfoStruct, void)(LPVOID object, PACF_WINDOWINFO pInfo) {
	CefWindowInfo* info = reinterpret_cast<CefWindowInfo*>(object);

	if (pInfo->window_name && *pInfo->window_name != '\0')
		CefString(&info->window_name) = pInfo->window_name;
	if (pInfo->ex_style >= 0)
		info->ex_style = pInfo->ex_style;
	if (pInfo->style >= 0)
		info->style = pInfo->style;
	info->bounds.x = pInfo->x;
	info->bounds.y = pInfo->y;
	info->bounds.width = pInfo->width;
	info->bounds.height = pInfo->height;
	info->parent_window = (HWND)pInfo->parent_window;
	info->menu = (HMENU)pInfo->menu;
	info->window = (HWND)pInfo->window;

	info->windowless_rendering_enabled = pInfo->windowless_rendering_enabled;
	info->shared_texture_enabled = pInfo->shared_texture_enabled;
	info->external_begin_frame_enabled = pInfo->external_begin_frame_enabled;
}

ACF_EXPORTS(RunMessageLoop, void)()
{
	CefRunMessageLoop();
}

ACF_EXPORTS(QuitMessageLoop, void)()
{
	CefQuitMessageLoop();
}

ACF_EXPORTS(DoMessageLoopWork, void)()
{
	CefDoMessageLoopWork();
}

ACF_EXPORTS(EnableHighDPISupport, void)()
{
	CefEnableHighDPISupport();
}

ACF_EXPORTS(Shutdown, void)()
{
	CefShutdown();
}

ACF_EXPORTS(SetOSModalLoop, void)(bool modal)
{
	CefSetOSModalLoop(modal);
}

void OnControlKeyDown(LPVOID lpfnCallback, WPARAM wParam, LPARAM lParam)
{
	int nFlags = 0;
	if (wParam != 17 && (GetKeyState(17) & 8000)) nFlags = 1;
	if (wParam != 16 && (GetKeyState(16) & 8000)) nFlags |= 2;
	if (wParam != 18 && (GetKeyState(18) & 8000)) nFlags |= 4;
	__asm {
		push nFlags;
		push wParam;
		call lpfnCallback;
	}
}

void OnControlKeyUp(LPVOID lpfnCallback, WPARAM wParam, LPARAM lParam)
{
	int nFlags = 0;
	if (wParam != 17 && (GetKeyState(17) & 8000)) nFlags = 1;
	if (wParam != 16 && (GetKeyState(16) & 8000)) nFlags |= 2;
	if (wParam != 18 && (GetKeyState(18) & 8000)) nFlags |= 4;
	__asm {
		push nFlags;
		push wParam;
		call lpfnCallback;
	}
}

void OnControlChar(LPVOID lpfnCallback, WPARAM wParam)
{
	__asm {
		push wParam;
		call lpfnCallback;
	}
}

void OnControlMouseMove(LPVOID lpfnCallback, int x, int y, int flags)
{
	__asm {
		push flags;
		push y;
		push x;
		call lpfnCallback;
	}
}

void OnControlLeftDown(LPVOID lpfnCallback, int x, int y, int flags)
{
	__asm {
		push flags;
		push y;
		push x;
		call lpfnCallback;
	}
}

void OnControlLeftUp(LPVOID lpfnCallback, int x, int y, int flags)
{
	__asm {
		push flags;
		push y;
		push x;
		call lpfnCallback;
	}
}

void OnControlLeftDbClick(LPVOID lpfnCallback, int x, int y, int flags)
{
	__asm {
		push flags;
		push y;
		push x;
		call lpfnCallback;
	}
}

void OnControlRightDown(LPVOID lpfnCallback, int x, int y, int flags)
{
	__asm {
		push flags;
		push y;
		push x;
		call lpfnCallback;
	}
}

void OnControlRightUp(LPVOID lpfnCallback, int x, int y, int flags)
{
	__asm {
		push flags;
		push y;
		push x;
		call lpfnCallback;
	}
}

LRESULT CALLBACK MsgLoopWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WindowEventCallback::iterator iend = g_pListWindowEvent.end();
	for (WindowEventCallback::iterator iter = g_pListWindowEvent.begin(); iter != iend; iter++)
	{
		if (iter->hWnd == hWnd)
		{
			if (iter->nType == uMsg)
			{
				switch (uMsg)
				{
				case WM_KEYDOWN:
					OnControlKeyDown(iter->lpfnEventCallback, wParam, 0);
					break;
				case WM_KEYUP:
					OnControlKeyUp(iter->lpfnEventCallback, wParam, 0);
					break;
				case WM_CHAR:
					OnControlChar(iter->lpfnEventCallback, wParam);
					break;
				case WM_MOUSEMOVE:
					OnControlMouseMove(iter->lpfnEventCallback, lParam & 65535, lParam >> 16, wParam);
					break;
				case WM_LBUTTONDOWN:
					OnControlLeftDown(iter->lpfnEventCallback, lParam & 65535, lParam >> 16, wParam);
					break;
				case WM_LBUTTONUP:
					OnControlLeftUp(iter->lpfnEventCallback, lParam & 65535, lParam >> 16, wParam);
					break;
				case WM_LBUTTONDBLCLK:
					OnControlLeftDbClick(iter->lpfnEventCallback, lParam & 65535, lParam >> 16, wParam);
					break;
				case WM_RBUTTONDOWN:
					OnControlRightDown(iter->lpfnEventCallback, lParam & 65535, lParam >> 16, wParam);
					break;
				case WM_RBUTTONUP:
					OnControlRightUp(iter->lpfnEventCallback, lParam & 65535, lParam >> 16, wParam);
					break;
				default:
					break;
				}
			}
			return CallWindowProc(iter->lpfnPrevWndFunc, hWnd, uMsg, wParam, lParam);
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

ACF_EXPORTS(AddEvents, void)(HWND hWnd, WINDOW_EVENT_TYPE nType, LPVOID lpfnEventCallback)
{
	WNDPROC lpPrevWndFunc = NULL;
	WindowEventCallback::iterator iend = g_pListWindowEvent.end();
	for (WindowEventCallback::iterator iter = g_pListWindowEvent.begin(); iter != iend; iter++)
	{
		if (iter->hWnd == hWnd)
		{
			lpPrevWndFunc = iter->lpfnPrevWndFunc;
			if (iter->nType == nType)
			{
				iter->lpfnEventCallback = lpfnEventCallback;
				return;
			}
		}
	}

	WINDOW_EVENT_CALLBACK lpData;
	lpData.hWnd = hWnd;
	if (lpPrevWndFunc == NULL)
	{
		lpData.lpfnPrevWndFunc = (WNDPROC)SetWindowLong(hWnd, GWL_WNDPROC, (LONG)MsgLoopWndProc);
	}
	else lpData.lpfnPrevWndFunc = lpPrevWndFunc;
	lpData.nType = nType;
	lpData.lpfnEventCallback = lpfnEventCallback;
	g_pListWindowEvent.push_back(lpData);
}

ACF_EXPORTS(CurrentlyOn, BOOL)(CefThreadId tid)
{
	return CefCurrentlyOn(tid);
}

ACF_EXPORTS(PostTask, void)(CefThreadId tid, LPFN_POST_TASK func, int lParam1, int lParam2, int lParam3)
{
	CefRefPtr<ACFlibTask> pTask = new ACFlibTask(func, lParam1, lParam2, lParam3);
	CefPostTask(tid, pTask);
}

ACF_EXPORTS(PostDelayedTask, void)(CefThreadId tid, LPFN_POST_TASK func, int64 ms, int lParam1, int lParam2, int lParam3)
{
	CefRefPtr<ACFlibTask> pTask = new ACFlibTask(func, lParam1, lParam2, lParam3);
	CefPostDelayedTask(tid, pTask, ms);
}

ACF_EXPORTS(PostTaskStd, void)(CefThreadId tid, LPVOID callback, bool copy)
{
	CefRefPtr<ACFlibTaskStd> pTask = new ACFlibTaskStd(callback, copy);
	CefPostTask(tid, pTask);
}

ACF_EXPORTS(PostDelayedTaskStd, void)(CefThreadId tid, int64 ms, LPVOID callback, bool copy)
{
	CefRefPtr<ACFlibTaskStd> pTask = new ACFlibTaskStd(callback, copy);
	CefPostDelayedTask(tid, pTask, ms);
}
