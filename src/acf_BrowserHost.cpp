
#include "acf_Types.h"
#include "acf_FrameEvents.h"
#include "acf_Client.h"
#include "acf_Conv.h"
#include "acf_Scheme.h"

#include "include/cef_browser.h"

extern DWORD acf_value_funcs[];
extern DWORD acf_dictionary_funcs[];
extern DWORD acf_browser_funcs[];
extern DWORD acf_browser_host_funcs[];
extern DWORD acf_request_context_funcs[];
extern DWORD acf_cookie_manager_funcs[];
extern DWORD acf_navigation_entry_funcs[];
extern DWORD acf_ssl_status_funcs[];

bool ECALL host_get_browser(CefBrowserHost* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefBrowser> pBrowser = obj->GetBrowser();

	pBrowser->AddRef();
	target[1] = (DWORD)((LPVOID)pBrowser);
	target[2] = (DWORD)acf_browser_funcs;

	return !!pBrowser;
}

void ECALL host_close_browser(CefBrowserHost* obj, bool force)
{
	ISVALID(obj);

	obj->CloseBrowser(force);
}

bool ECALL host_try_close_browser(CefBrowserHost* obj)
{
	ISVALIDR(obj, false);

	return obj->TryCloseBrowser();
}

void ECALL host_set_focus(CefBrowserHost* obj, bool focus)
{
	ISVALID(obj);

	obj->SetFocus(focus);
}

HWND ECALL host_get_window_handle(CefBrowserHost* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetWindowHandle();
}

HWND ECALL host_get_opener_window_handle(CefBrowserHost* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetOpenerWindowHandle();
}

bool ECALL host_has_view(CefBrowserHost* obj)
{
	ISVALIDR(obj, false);

	return obj->HasView();
}

LPVOID ECALL host_get_client(CefBrowserHost* obj)
{
	ISVALIDR(obj, nullptr);

	return obj->GetClient().get();
}

bool ECALL host_get_request_context(CefBrowserHost* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefRequestContext> pBrowser = obj->GetRequestContext();

	pBrowser->AddRef();
	target[1] = (DWORD)((LPVOID)pBrowser);
	target[2] = (DWORD)acf_request_context_funcs;

	return !!pBrowser;
}

bool ECALL host_get_zoom_level(CefBrowserHost* obj, double* target)
{
	ISVALIDR(obj, false);

	*target = obj->GetZoomLevel();

	return !!target;
}

void ECALL host_set_zoom_level(CefBrowserHost* obj, double* level)
{
	ISVALID(obj);

	obj->SetZoomLevel(*level);
}

void ECALL host_run_file_dialog(CefBrowserHost* obj, int mode, LPCWSTR title, LPCWSTR def_path,
	LPVOID* accept_filters, int sel_filter, LPVOID callback, BOOL copyData)
{
	ISVALID(obj);

	LPSTR pArgsList = (LPSTR)*accept_filters;

	int nCount = *(LPINT)(pArgsList + sizeof(INT));

	std::vector<CefString> pArgs(nCount);

	for (size_t i = 0; i < nCount; i++)
	{
		pArgs[i] = (LPSTR)(((LPDWORD)(pArgsList + sizeof(INT) * 2))[i]);
	}

	CefRefPtr<ACFlibRunFileDialogCallback> lpHandler = new ACFlibRunFileDialogCallback(callback, copyData);

	obj->RunFileDialog((cef_file_dialog_mode_t)mode, title, def_path, pArgs, sel_filter, lpHandler);
}

void ECALL host_start_download(CefBrowserHost* obj, LPCWSTR url)
{
	ISVALID(obj);

	obj->StartDownload(url);
}

void ECALL host_download_image(CefBrowserHost* obj, LPCWSTR url, bool is_icon,
	int max_image_size, bool bypass_cache, LPVOID callback, BOOL copyData)
{
	ISVALID(obj);

	CefRefPtr<ACFlibDownloadImageCallback> lpHandler = new ACFlibDownloadImageCallback(callback, copyData);

	obj->DownloadImage(url, is_icon, max_image_size, bypass_cache, lpHandler);
}

void ECALL host_print(CefBrowserHost* obj)
{
	ISVALID(obj);

	obj->Print();
}

void ECALL host_print_to_pdf(CefBrowserHost* obj, LPCWSTR path, cef_pdf_print_settings_t** settings, LPVOID callback, BOOL copyData)
{
	ISVALID(obj);

	CefRefPtr<ACFlibPdfPrintCallback> lpHandler = new ACFlibPdfPrintCallback(callback, copyData);

	obj->PrintToPDF(path, **settings, lpHandler);
}

void ECALL host_find(CefBrowserHost* obj, int id, LPCWSTR text, bool foward, bool case_sensitive, bool show_in_handler)
{
	ISVALID(obj);

	obj->Find(id, text, foward, case_sensitive, show_in_handler);
}

void ECALL host_stopfinding(CefBrowserHost* obj, bool clear)
{
	ISVALID(obj);

	obj->StopFinding(clear);
}

void ECALL host_show_devtools(CefBrowserHost* obj, DWORD* info, ACFlibClient* client, DWORD* settings, int x, int y)
{
	ISVALID(obj);

	auto pInfo = reinterpret_cast<CefWindowInfo*>(info[1]);
	auto pSettings = reinterpret_cast<CefBrowserSettings*>(settings[1]);

	obj->ShowDevTools(*pInfo, client, *pSettings, CefPoint(x, y));
}

void ECALL host_close_devtools(CefBrowserHost* obj)
{
	ISVALID(obj);

	obj->CloseDevTools();
}

bool ECALL host_has_devtools(CefBrowserHost* obj)
{
	ISVALIDR(obj, false);

	return obj->HasDevTools();
}

bool ECALL host_send_devtools_message(CefBrowserHost* obj, LPVOID data, int size)
{
	ISVALIDR(obj, false);

	return obj->SendDevToolsMessage(data, size);
}

int ECALL host_execute_devtools_method(CefBrowserHost* obj, int message_id,
	LPCWSTR method, CefDictionaryValue* params)
{
	ISVALIDR(obj, false);
	
	return obj->ExecuteDevToolsMethod(message_id, method, params);
}

LPVOID ECALL host_add_devtools_message_observer(CefBrowserHost* obj, LPVOID observer, BOOL copyData)
{
	ISVALIDR(obj, NULL);

	CefRefPtr<ACFlibDevToolsMessageObserver> lpObserver = new ACFlibDevToolsMessageObserver(observer, copyData);

	return obj->AddDevToolsMessageObserver(lpObserver);
}

bool ECALL host_get_navigation_entries(CefBrowserHost* obj, LPVOID visitor, BOOL copyData, bool current)
{
	ISVALIDR(obj, NULL);

	CefRefPtr<ACFlibNavigationEntryVisitor> lpHandler = new ACFlibNavigationEntryVisitor(visitor, copyData);

	obj->GetNavigationEntries(lpHandler, current);

	return !!obj;
}

void ECALL host_set_mouse_change_disabled(CefBrowserHost* obj, bool disabled)
{
	ISVALID(obj);

	obj->SetMouseCursorChangeDisabled(disabled);
}

bool ECALL host_is_mouse_change_disabled(CefBrowserHost* obj)
{
	ISVALIDR(obj, false);

	return obj->IsMouseCursorChangeDisabled();
}

void ECALL host_replace_misspelling(CefBrowserHost* obj, LPCWSTR word)
{
	ISVALID(obj);

	obj->ReplaceMisspelling(word);
}

void ECALL host_add_word_to_dictionary(CefBrowserHost* obj, LPCWSTR word)
{
	ISVALID(obj);

	obj->AddWordToDictionary(word);
}

bool ECALL host_is_window_rendering_disabled(CefBrowserHost* obj)
{
	ISVALIDR(obj, false);

	return obj->IsWindowRenderingDisabled();
}

void ECALL host_was_resized(CefBrowserHost* obj)
{
	ISVALID(obj);

	obj->WasResized();
}

void ECALL host_was_hidden(CefBrowserHost* obj, bool hidden)
{
	ISVALID(obj);

	obj->WasHidden(hidden);
}

void ECALL host_notify_screen_info_changed(CefBrowserHost* obj)
{
	ISVALID(obj);

	obj->NotifyScreenInfoChanged();
}

void ECALL host_invalidate(CefBrowserHost* obj, cef_paint_element_type_t type)
{
	ISVALID(obj);

	obj->Invalidate(type);
}

void ECALL host_send_external_begin_frame(CefBrowserHost* obj)
{
	ISVALID(obj);

	obj->SendExternalBeginFrame();
}

void ECALL host_send_key_event(CefBrowserHost* obj, cef_key_event_t** lppEvent)
{
	ISVALID(obj);

	CefKeyEvent lpEvent(**lppEvent);

	obj->SendKeyEvent(lpEvent);
}

void ECALL host_send_mouse_click_event(CefBrowserHost* obj, cef_mouse_event_t** lppEvent, cef_mouse_button_type_t type, BOOL mouse_up, int count)
{
	ISVALID(obj);

	CefMouseEvent lpEvent(**lppEvent);

	obj->SendMouseClickEvent(lpEvent, type, mouse_up, count);
}

void ECALL host_send_mouse_move_event(CefBrowserHost* obj, cef_mouse_event_t** lppEvent, BOOL leave)
{
	ISVALID(obj);

	CefMouseEvent lpEvent(**lppEvent);

	obj->SendMouseMoveEvent(lpEvent, leave);
}

void ECALL host_send_mouse_wheel_event(CefBrowserHost* obj, cef_mouse_event_t** lppEvent, int deltaX, int deltaY)
{
	ISVALID(obj);

	CefMouseEvent lpEvent(**lppEvent);

	obj->SendMouseWheelEvent(lpEvent, deltaX, deltaY);
}

void ECALL host_send_touch_event(CefBrowserHost* obj, cef_touch_event_t** lppEvent)
{
	ISVALID(obj);

	CefTouchEvent lpEvent(**lppEvent);

	obj->SendTouchEvent(lpEvent);
}

void ECALL host_focus_event(CefBrowserHost* obj, bool focus)
{
	ISVALID(obj);

	obj->SendFocusEvent(focus);
}

void ECALL host_send_capture_lost_event(CefBrowserHost* obj)
{
	ISVALID(obj);

	obj->SendCaptureLostEvent();
}

void ECALL host_notify_move_or_resized(CefBrowserHost* obj)
{
	ISVALID(obj);

	obj->NotifyMoveOrResizeStarted();
}

int ECALL host_get_windowless_frame_rate(CefBrowserHost* obj)
{
	ISVALIDR(obj, 0);

	return obj->GetWindowlessFrameRate();
}

void ECALL host_set_windowless_frame_rate(CefBrowserHost* obj, int rate)
{
	ISVALID(obj);

	obj->SetWindowlessFrameRate(rate);
}

void ECALL host_ime_set_composition(CefBrowserHost* obj, LPCWSTR text, LPVOID* lpAryData,
	cef_range_t** replace_range, cef_range_t** selection_range)
{
	ISVALID(obj);

	LPSTR lpDatas = (LPSTR)*lpAryData;

	int nCount = *(LPINT)(lpDatas + sizeof(INT));

	DWORD* lpObjs = (LPDWORD)(lpDatas + sizeof(INT) * 2);

	std::vector<CefCompositionUnderline> aryData(nCount);

	for (size_t i = 0; i < nCount; i++)
	{
		aryData[i].range.from = ((PACF_COMPOSITION_UNDERLINE)(lpObjs[i]))->from;
		aryData[i].range.to = ((PACF_COMPOSITION_UNDERLINE)(lpObjs[i]))->to;
		aryData[i].color = ((PACF_COMPOSITION_UNDERLINE)(lpObjs[i]))->color;
		aryData[i].background_color = ((PACF_COMPOSITION_UNDERLINE)(lpObjs[i]))->bgcolor;
		aryData[i].thick = ((PACF_COMPOSITION_UNDERLINE)(lpObjs[i]))->thick;
		aryData[i].style = (cef_composition_underline_style_t)((PACF_COMPOSITION_UNDERLINE)(lpObjs[i]))->style;
	}

	obj->ImeSetComposition(text, aryData, **replace_range, **selection_range);
}

void ECALL host_ime_commit_text(CefBrowserHost* obj, LPCWSTR text, cef_range_t** replace_range, int relative_cursor_pos)
{
	ISVALID(obj);

	obj->ImeCommitText(text, **replace_range, relative_cursor_pos);
}

void ECALL host_ime_finish_composing_text(CefBrowserHost* obj, bool selection)
{
	ISVALID(obj);

	obj->ImeFinishComposingText(selection);
}

void ECALL host_cancel_composition(CefBrowserHost* obj)
{
	ISVALID(obj);

	obj->ImeCancelComposition();
}

void ECALL host_drag_target_drag_enter(CefBrowserHost* obj, CefDragData* data, cef_mouse_event_t** lpEvent, cef_drag_operations_mask_t allowed_ops)
{
	ISVALID(obj);

	obj->DragTargetDragEnter(data, **lpEvent, allowed_ops);
}

void ECALL host_drag_target_drag_over(CefBrowserHost* obj, cef_mouse_event_t** lpEvent, cef_drag_operations_mask_t allowed_ops)
{
	ISVALID(obj);

	obj->DragTargetDragOver(**lpEvent, allowed_ops);
}

void ECALL host_drag_target_drag_leave(CefBrowserHost* obj)
{
	ISVALID(obj);

	obj->DragTargetDragLeave();
}

void ECALL host_drag_target_drop(CefBrowserHost* obj, cef_mouse_event_t** lpEvent)
{
	ISVALID(obj);

	obj->DragTargetDrop(**lpEvent);
}

void ECALL host_drag_source_ended_ad(CefBrowserHost* obj, int x, int y, cef_drag_operations_mask_t ops)
{
	ISVALID(obj);

	obj->DragSourceEndedAt(x, y, ops);
}

void ECALL host_drag_source_system_drag_ended(CefBrowserHost* obj)
{
	ISVALID(obj);

	obj->DragSourceSystemDragEnded();
}

BOOL ECALL host_get_visible_navigation_entry(CefBrowserHost* obj, DWORD* target)
{
	ISVALIDR(obj, NULL);

	CefRefPtr<CefNavigationEntry> pObj = obj->GetVisibleNavigationEntry();

	pObj->AddRef();
	target[1] = (DWORD)((LPVOID)pObj);
	target[2] = (DWORD)acf_navigation_entry_funcs;

	return target != NULL;
}

void ECALL host_set_accessibility_state(CefBrowserHost* obj, cef_state_t accessibility_state)
{
	ISVALID(obj);

	obj->SetAccessibilityState(accessibility_state);
}

void ECALL host_set_auto_resize_enabled(CefBrowserHost* obj, bool enabled,
	int min_width, int min_height, int max_width, int max_height)
{
	ISVALID(obj);

	obj->SetAutoResizeEnabled(enabled, CefSize(min_width, min_height), CefSize(max_width, max_height));
}

bool ECALL host_get_extension(CefBrowserHost* obj, DWORD* target)
{
	ISVALIDR(obj, NULL);

	CefRefPtr<CefExtension> pObj = obj->GetExtension();

	pObj->AddRef();
	target[1] = (DWORD)((LPVOID)pObj);
	target[2] = (DWORD)acf_extension_funcs;

	return !!pObj;
}

bool ECALL host_is_background_host(CefBrowserHost* obj)
{
	ISVALIDR(obj, false);

	return obj->IsBackgroundHost();
}

void ECALL host_set_audio_muted(CefBrowserHost* obj, bool muted)
{
	ISVALID(obj);

	obj->SetAudioMuted(muted);
}

bool ECALL host_is_audio_muted(CefBrowserHost* obj)
{
	ISVALIDR(obj, false);

	return obj->IsAudioMuted();
}

void ECALL host_set_view_visible(CefBrowserHost* obj, bool visible)
{
	ISVALID(obj);

	obj->SetViewVisible(visible);
}

void ECALL host_set_page_frozen(CefBrowserHost* obj, bool frozen)
{
	ISVALID(obj);

	obj->SetPageFrozen(frozen);
}

void ECALL host_save_page(CefBrowserHost* obj, LPCWSTR main_file, LPCWSTR dir_path, cef_save_page_type_t type)
{
	ISVALID(obj);

	obj->SavePageTo(main_file, dir_path, type);
}

DWORD acf_browser_host_funcs[] = {
	(DWORD)&host_get_browser,
	(DWORD)&host_close_browser,
	(DWORD)&host_try_close_browser,
	(DWORD)&host_set_focus,
	(DWORD)&host_get_window_handle,
	(DWORD)&host_get_opener_window_handle,
	(DWORD)&host_has_view,
	(DWORD)&host_get_client,
	(DWORD)&host_get_request_context,
	(DWORD)&host_get_zoom_level,
	(DWORD)&host_set_zoom_level,
	(DWORD)&host_run_file_dialog,
	(DWORD)&host_start_download,
	(DWORD)&host_download_image,
	(DWORD)&host_print,
	(DWORD)&host_print_to_pdf,
	(DWORD)&host_find,
	(DWORD)&host_stopfinding,
	(DWORD)&host_show_devtools,
	(DWORD)&host_close_devtools,
	(DWORD)&host_has_devtools,
	(DWORD)&host_send_devtools_message,
	(DWORD)&host_execute_devtools_method,
	(DWORD)&host_add_devtools_message_observer,
	(DWORD)&host_get_navigation_entries,
	(DWORD)&host_set_mouse_change_disabled,
	(DWORD)&host_is_mouse_change_disabled,
	(DWORD)&host_replace_misspelling,
	(DWORD)&host_add_word_to_dictionary,
	(DWORD)&host_is_window_rendering_disabled,
	(DWORD)&host_was_resized,
	(DWORD)&host_was_hidden,
	(DWORD)&host_notify_screen_info_changed,
	(DWORD)&host_invalidate,
	(DWORD)&host_send_external_begin_frame,
	(DWORD)&host_send_key_event,
	(DWORD)&host_send_mouse_click_event,
	(DWORD)&host_send_mouse_move_event,
	(DWORD)&host_send_mouse_wheel_event,
	(DWORD)&host_send_touch_event,
	(DWORD)&host_focus_event,
	(DWORD)&host_send_capture_lost_event,
	(DWORD)&host_notify_move_or_resized,
	(DWORD)&host_get_windowless_frame_rate,
	(DWORD)&host_set_windowless_frame_rate,
	(DWORD)&host_ime_set_composition,
	(DWORD)&host_ime_commit_text,
	(DWORD)&host_ime_finish_composing_text,
	(DWORD)&host_cancel_composition,
	(DWORD)&host_drag_target_drag_enter,
	(DWORD)&host_drag_target_drag_over,
	(DWORD)&host_drag_target_drag_leave,
	(DWORD)&host_drag_target_drop,
	(DWORD)&host_drag_source_ended_ad,
	(DWORD)&host_drag_source_system_drag_ended,
	(DWORD)&host_get_visible_navigation_entry,
	(DWORD)&host_set_accessibility_state,
	(DWORD)&host_set_auto_resize_enabled,
	(DWORD)&host_get_extension,
	(DWORD)&host_is_background_host,
	(DWORD)&host_set_audio_muted,
	(DWORD)&host_is_audio_muted,
	(DWORD)&host_set_view_visible,
	(DWORD)&host_set_page_frozen,
	(DWORD)&host_save_page,
};

ACF_EXPORTS(RequestContextGetGlobal, BOOL)(DWORD* target)
{
	CefRefPtr<CefRequestContext> lpObj = CefRequestContext::GetGlobalContext();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_request_context_funcs;

	return !!lpObj;
}

ACF_EXPORTS(RequestContextCreate, BOOL)(DWORD* target, PACF_REQUEST_CONTEXT_SETTINGS settings, LPVOID lpCallback, BOOL copyData)
{
	CefRefPtr<ACFlibRequestContextHandler> lpHandler = new ACFlibRequestContextHandler(lpCallback, copyData);

	CefRequestContextSettings pSettings;

	if (settings->cache_path && *settings->cache_path != '\0')
		CefString(&pSettings.cache_path) = settings->cache_path;
	if (settings->accept_language_list && *settings->accept_language_list != '\0')
		CefString(&pSettings.accept_language_list) = settings->accept_language_list;
	pSettings.persist_session_cookies = settings->persist_session_cookies;
	pSettings.persist_user_preferences = settings->persist_user_preferences;
	pSettings.ignore_certificate_errors = settings->ignore_cert_error;

	CefRefPtr<CefRequestContext> lpObj = CefRequestContext::CreateContext(pSettings, lpHandler);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_request_context_funcs;

	return true;
}

ACF_EXPORTS(RequestContextCreateOther, BOOL)(DWORD* target, CefRequestContext* other, LPVOID lpCallback, BOOL copyData)
{
	CefRefPtr<ACFlibRequestContextHandler> lpHandler = new ACFlibRequestContextHandler(lpCallback, copyData);

	CefRefPtr<CefRequestContext> lpObj = CefRequestContext::CreateContext(other, lpHandler);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_request_context_funcs;

	return true;
}

bool ECALL requestcontext_is_same(CefRequestContext* obj, CefRequestContext* that)
{
	ISVALIDR(obj, NULL);

	return obj->IsSame(that);
}

bool ECALL requestcontext_is_sharing_with(CefRequestContext* obj, CefRequestContext* that)
{
	ISVALIDR(obj, NULL);

	return obj->IsSharingWith(that);
}

bool ECALL requestcontext_is_global(CefRequestContext* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsGlobal();
}

LPVOID ECALL requestcontext_get_handler(CefRequestContext* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetHandler();
}

bool ECALL requestcontext_get_cache_path(CefRequestContext* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetCachePath().c_str());

	return str != NULL;
}

bool ECALL requestcontext_get_cookie_manager(CefRequestContext* obj, LPVOID lpCallback, BOOL copyData, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<ACFlibCompletionCallback> lpHandler = new ACFlibCompletionCallback(lpCallback, copyData);

	CefRefPtr<CefCookieManager> pBrowser = obj->GetCookieManager(lpHandler);

	pBrowser->AddRef();
	target[1] = (DWORD)((LPVOID)pBrowser);
	target[2] = (DWORD)acf_cookie_manager_funcs;

	return true;
}

bool ECALL requestcontext_register_scheme_handler_factory(CefRequestContext* obj, LPSTR scheme, LPSTR domain, LPVOID callback, BOOL copyData)
{
	ISVALIDR(obj, NULL);

	CefRefPtr<ACFlibSchemeHandler> lpHandler = new ACFlibSchemeHandler(callback, copyData);

	return obj->RegisterSchemeHandlerFactory(scheme, domain, lpHandler);
}

bool ECALL requestcontext_clear_scheme_handler_factories(CefRequestContext* obj)
{
	ISVALIDR(obj, NULL);

	return obj->ClearSchemeHandlerFactories();
}

void ECALL requestcontext_purge_plugin_list_cache(CefRequestContext* obj, bool reload_pages)
{
	ISVALID(obj);

	obj->PurgePluginListCache(reload_pages);
}

bool ECALL requestcontext_has_preference(CefRequestContext* obj, LPCWSTR name)
{
	ISVALIDR(obj, NULL);

	return obj->HasPreference(name);
}

bool ECALL requestcontext_get_preference(CefRequestContext* obj, LPCWSTR name, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefValue> pBrowser = obj->GetPreference(name);

	pBrowser->AddRef();
	target[1] = (DWORD)((LPVOID)pBrowser);
	target[2] = (DWORD)acf_value_funcs;

	return true;
}

bool ECALL requestcontext_get_all_preferences(CefRequestContext* obj, bool include_defaults, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDictionaryValue> pBrowser = obj->GetAllPreferences(include_defaults);

	pBrowser->AddRef();
	target[1] = (DWORD)((LPVOID)pBrowser);
	target[2] = (DWORD)acf_dictionary_funcs;

	return !!target;
}

bool ECALL requestcontext_can_set_preference(CefRequestContext* obj, LPCWSTR name)
{
	ISVALIDR(obj, NULL);

	return obj->CanSetPreference(name);
}

bool ECALL requestcontext_set_preference(CefRequestContext* obj, LPCWSTR name, CefValue* value, DWORD* error)
{
	ISVALIDR(obj, NULL);

	CefString pError;

	BOOL bRetVal = obj->SetPreference(name, value, pError);

	USES_CONVERSION;

	*error = (DWORD)UnicodeToEStream(pError.c_str());

	return bRetVal;
}

void ECALL requestcontext_clear_certificate_exceptions(CefRequestContext* obj, LPVOID lpCallback, BOOL copyData)
{
	ISVALID(obj);

	CefRefPtr<ACFlibCompletionCallback> lpHandler = new ACFlibCompletionCallback(lpCallback, copyData);

	obj->ClearCertificateExceptions(lpHandler);
}

void ECALL requestcontext_clear_http_auth_credentials(CefRequestContext* obj, LPVOID lpCallback, BOOL copyData)
{
	ISVALID(obj);

	CefRefPtr<ACFlibCompletionCallback> lpHandler = new ACFlibCompletionCallback(lpCallback, copyData);

	obj->ClearHttpAuthCredentials(lpHandler);
}

void ECALL requestcontext_close_all_connections(CefRequestContext* obj, LPVOID lpCallback, BOOL copyData)
{
	ISVALID(obj);

	CefRefPtr<ACFlibCompletionCallback> lpHandler = new ACFlibCompletionCallback(lpCallback, copyData);

	obj->CloseAllConnections(lpHandler);
}

void ECALL requestcontext_resolve_host(CefRequestContext* obj, LPCWSTR origin, LPVOID lpCallback, BOOL copyData)
{
	ISVALID(obj);

	CefRefPtr<ACFlibResolveCallback> lpHandler = new ACFlibResolveCallback(lpCallback, copyData);

	obj->ResolveHost(origin, lpHandler);
}

void ECALL requestcontext_load_extension(CefRequestContext* obj, LPCWSTR root_dir, CefDictionaryValue* manifest, LPVOID callback, BOOL copyData)
{
	ISVALID(obj);

	CefRefPtr<ACFlibExtensionHandler> lpHandler = new ACFlibExtensionHandler(callback, copyData);

	obj->LoadExtension(root_dir, manifest, lpHandler);
}

BOOL ECALL requestcontext_did_load_extension(CefRequestContext* obj, LPCWSTR extension_id)
{
	ISVALIDR(obj, false);

	return obj->DidLoadExtension(extension_id);
}

BOOL ECALL requestcontext_has_extension(CefRequestContext* obj, LPCWSTR extension_id)
{
	ISVALIDR(obj, false);

	return obj->HasExtension(extension_id);
}

BOOL ECALL requestcontext_get_extensions(CefRequestContext* obj, LPVOID* eArray)
{
	ISVALIDR(obj, NULL);

	std::vector<CefString> keys;
	obj->GetExtensions(keys);

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

	return !!eArray;
}

BOOL ECALL requestcontext_get_extension(CefRequestContext* obj, LPCWSTR extension_id, DWORD* target)
{
	CefRefPtr<CefExtension> pObj = obj->GetExtension(extension_id);

	if (pObj)
		pObj->AddRef();
	target[1] = (DWORD)((LPVOID)pObj);
	target[2] = (DWORD)acf_extension_funcs;

	return !!target;
}

void ECALL requestcontext_get_media_router(CefRequestContext* obj)
{
	// FIXME
}

DWORD acf_request_context_funcs[] = {
	(DWORD)&requestcontext_is_same,
	(DWORD)&requestcontext_is_sharing_with,
	(DWORD)&requestcontext_is_global,
	(DWORD)&requestcontext_get_handler,
	(DWORD)&requestcontext_get_cache_path,
	(DWORD)&requestcontext_get_cookie_manager,
	(DWORD)&requestcontext_register_scheme_handler_factory,
	(DWORD)&requestcontext_clear_scheme_handler_factories,
	(DWORD)&requestcontext_purge_plugin_list_cache,
	(DWORD)&requestcontext_has_preference,
	(DWORD)&requestcontext_get_preference,
	(DWORD)&requestcontext_get_all_preferences,
	(DWORD)&requestcontext_can_set_preference,
	(DWORD)&requestcontext_set_preference,
	(DWORD)&requestcontext_clear_certificate_exceptions,
	(DWORD)&requestcontext_clear_http_auth_credentials,
	(DWORD)&requestcontext_close_all_connections,
	(DWORD)&requestcontext_resolve_host,
	(DWORD)&requestcontext_load_extension,
	(DWORD)&requestcontext_did_load_extension,
	(DWORD)&requestcontext_has_extension,
	(DWORD)&requestcontext_get_extensions,
	(DWORD)&requestcontext_get_extension,
	(DWORD)&requestcontext_get_media_router,
};

bool ECALL navigation_is_valid(CefNavigationEntry* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsValid();
}

BOOL ECALL navigation_get_url(CefNavigationEntry* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetURL().c_str());

	return str != NULL;
}

BOOL ECALL navigation_get_display_url(CefNavigationEntry* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetDisplayURL().c_str());

	return str != NULL;
}

BOOL ECALL navigation_get_original_url(CefNavigationEntry* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetOriginalURL().c_str());

	return str != NULL;
}

BOOL ECALL navigation_get_title(CefNavigationEntry* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetTitle().c_str());

	return str != NULL;
}

int ECALL navigation_get_transition_type(CefNavigationEntry* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetTransitionType();
}

bool ECALL navigation_has_post_data(CefNavigationEntry* obj)
{
	ISVALIDR(obj, NULL);

	return obj->HasPostData();
}

BOOL ECALL navigation_get_completion_time(CefNavigationEntry* obj, cef_time_t** pTime)
{
	ISVALIDR(obj, NULL);

	**pTime = obj->GetCompletionTime();

	return pTime != NULL;
}

int ECALL navigation_get_http_status_code(CefNavigationEntry* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetHttpStatusCode();
}

BOOL ECALL navigation_get_ssl_status(CefNavigationEntry* obj, DWORD* target)
{
	ISVALIDR(obj, NULL);

	CefRefPtr<CefSSLStatus> pObj = obj->GetSSLStatus();

	pObj->AddRef();
	target[1] = (DWORD)((LPVOID)pObj);
	target[2] = (DWORD)acf_ssl_status_funcs;

	return target != 0;
}

DWORD acf_navigation_entry_funcs[] = {
	(DWORD)&navigation_is_valid,
	(DWORD)&navigation_get_url,
	(DWORD)&navigation_get_display_url,
	(DWORD)&navigation_get_original_url,
	(DWORD)&navigation_get_title,
	(DWORD)&navigation_get_transition_type,
	(DWORD)&navigation_has_post_data,
	(DWORD)&navigation_get_completion_time,
	(DWORD)&navigation_get_http_status_code,
	(DWORD)&navigation_get_ssl_status,
};

extern DWORD acf_callback_extension_resource[];

void ECALL extensioncallback_continue(CefGetExtensionResourceCallback* obj, CefStreamReader* stream)
{
	ISVALID(obj);

	obj->Continue(stream);
}

void ECALL extensioncallback_cancel(CefGetExtensionResourceCallback* obj)
{
	ISVALID(obj);

	obj->Cancel();
}

DWORD acf_callback_extension_resource[] = {
	(DWORD)&extensioncallback_continue,
	(DWORD)&extensioncallback_cancel,
};
