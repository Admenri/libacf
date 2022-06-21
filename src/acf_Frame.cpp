
#include "acf_Types.h"
#include "acf_FrameEvents.h"

#include "include/cef_browser.h"
#include "include/cef_frame.h"
#include "include/cef_urlrequest.h"

#include "acf_Conv.h"

extern DWORD acf_v8_context_funcs[];
extern DWORD acf_browser_funcs[];
extern DWORD acf_frame_funcs[];
extern DWORD acf_url_request_funcs[];

bool ECALL frame_is_valid(CefFrame* obj)
{
	ISVALIDR(obj, false);

	return obj->IsValid();
}

void ECALL frame_undo(CefFrame* obj)
{
	ISVALID(obj);

	obj->Undo();
}

void ECALL frame_redo(CefFrame* obj)
{
	ISVALID(obj);

	obj->Redo();
}

void ECALL frame_cut(CefFrame* obj)
{
	ISVALID(obj);

	obj->Cut();
}

void ECALL frame_copy(CefFrame* obj)
{
	ISVALID(obj);

	obj->Copy();
}

void ECALL frame_paste(CefFrame* obj)
{
	ISVALID(obj);

	obj->Paste();
}

void ECALL frame_delete(CefFrame* obj)
{
	ISVALID(obj);

	obj->Delete();
}

void ECALL frame_selectall(CefFrame* obj)
{
	ISVALID(obj);

	obj->SelectAll();
}

void ECALL frame_viewsource(CefFrame* obj)
{
	ISVALID(obj);

	obj->ViewSource();
}

void ECALL frame_get_source(CefFrame* obj, LPVOID lpCallback, BOOL copyData)
{
	ISVALID(obj);

	CefRefPtr<ACFlibStringVisitor> lpVisitor = new ACFlibStringVisitor(lpCallback, copyData);
	obj->GetSource(lpVisitor);
}

void ECALL frame_get_text(CefFrame* obj, LPVOID lpCallback, BOOL copyData)
{
	ISVALID(obj);

	CefRefPtr<ACFlibStringVisitor> lpVisitor = new ACFlibStringVisitor(lpCallback, copyData);
	obj->GetText(lpVisitor);
}

void ECALL frame_load_request(CefFrame* obj, CefRequest* request)
{
	ISVALID(obj);
	
	obj->LoadRequest(request);
}

void ECALL frame_load_url(CefFrame* obj, LPCWSTR url)
{
	ISVALID(obj);

	obj->LoadURL(url);
}

void ECALL frame_execute_javascript(CefFrame* obj, LPCWSTR scripts, LPCWSTR url, int line)
{
	ISVALID(obj);

	obj->ExecuteJavaScript(scripts, url, line);
}

bool ECALL frame_is_main(CefFrame* obj)
{
	ISVALIDR(obj, false);

	return obj->IsMain();
}

bool ECALL frame_is_focused(CefFrame* obj)
{
	ISVALIDR(obj, false);

	return obj->IsFocused();
}

bool ECALL frame_get_name(CefFrame* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetName().c_str());

	return !!ansi_str;
}

bool ECALL frame_get_identifier(CefFrame* obj, int64* var)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*var = obj->GetIdentifier();

	return !!obj;
}

bool ECALL frame_get_parent(CefFrame* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	CefRefPtr<CefFrame> lpParent = obj->GetParent();

	lpParent->AddRef();
	target[1] = (DWORD)((LPVOID)lpParent);
	target[2] = (DWORD)acf_frame_funcs;

	return !!lpParent;
}

bool ECALL frame_get_url(CefFrame* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetURL().c_str());

	return !!ansi_str;
}

bool ECALL frame_get_browser(CefFrame* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	CefRefPtr<CefBrowser> lpParent = obj->GetBrowser();

	lpParent->AddRef();
	target[1] = (DWORD)((LPVOID)lpParent);
	target[2] = (DWORD)acf_browser_funcs;

	return !!lpParent;
}

bool ECALL frame_get_v8context(CefFrame* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	CefRefPtr<CefV8Context> lpParent = obj->GetV8Context();

	lpParent->AddRef();
	target[1] = (DWORD)((LPVOID)lpParent);
	target[2] = (DWORD)acf_v8_context_funcs;

	return !!lpParent;
}

void ECALL frame_visit_dom(CefFrame* obj, LPVOID lpCallback, BOOL copyData)
{
	ISVALID(obj);

	CefRefPtr<ACFlibDOMVisitor> lpVisitor = new ACFlibDOMVisitor(lpCallback, copyData);

	obj->VisitDOM(lpVisitor);
}

BOOL ECALL frame_create_url_request(CefFrame* obj, CefRequest* request, LPVOID lpCallback, BOOL copyData, DWORD* target)
{
	ISVALIDR(obj, NULL);

	CefRefPtr<ACFlibURLRequestClient> lpHandler = new ACFlibURLRequestClient(lpCallback, copyData);

	CefRefPtr<CefURLRequest> lpRequest = obj->CreateURLRequest(request, lpHandler);

	lpRequest->AddRef();
	target[1] = (DWORD)((LPVOID)lpRequest);
	target[2] = (DWORD)acf_url_request_funcs;

	return !!lpRequest;
}

void ECALL frame_send_process_message(CefFrame* obj, CefProcessId pid, CefProcessMessage* message)
{
	ISVALID(obj);

	obj->SendProcessMessage(pid, message);
}

void ECALL frame_set_emit_touch_events_for_mouse(CefFrame* obj, bool enabled, int configuration)
{
	ISVALID(obj);

#ifdef ACF_EXVER
	obj->SetEmitTouchEventsForMouse(enabled, configuration);
#endif
}

DWORD acf_frame_funcs[] = {
	(DWORD)&frame_is_valid,
	(DWORD)&frame_undo,
	(DWORD)&frame_redo,
	(DWORD)&frame_cut,
	(DWORD)&frame_copy,
	(DWORD)&frame_paste,
	(DWORD)&frame_delete,
	(DWORD)&frame_selectall,
	(DWORD)&frame_viewsource,
	(DWORD)&frame_get_source,
	(DWORD)&frame_get_text,
	(DWORD)&frame_load_request,
	(DWORD)&frame_load_url,
	(DWORD)&frame_execute_javascript,
	(DWORD)&frame_is_main,
	(DWORD)&frame_is_focused,
	(DWORD)&frame_get_name,
	(DWORD)&frame_get_identifier,
	(DWORD)&frame_get_parent,
	(DWORD)&frame_get_url,
	(DWORD)&frame_get_browser,
	(DWORD)&frame_get_v8context,
	(DWORD)&frame_visit_dom,
	(DWORD)&frame_create_url_request,
	(DWORD)&frame_send_process_message,
	(DWORD)&frame_set_emit_touch_events_for_mouse,
};