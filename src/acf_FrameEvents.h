#pragma once

#include "acf_Types.h"
#include "include/cef_v8.h"
#include "include/cef_request_context_handler.h"
#include "include/cef_app.h"
#include "include/cef_menu_model.h"
#include "include/cef_menu_model_delegate.h"
#include "include/cef_urlrequest.h"
#include "include/cef_devtools_message_observer.h"
#include "include/cef_urlrequest.h"
#include "include/cef_server.h"

#ifdef ACF_EXVER
#include "include/cef_permission.h"
#endif

class ACFV8RetValCallback : public CefBaseRefCounted
{
public:

	ACFV8RetValCallback();
	~ACFV8RetValCallback();

	void SetValue(CefV8Value* ret_val);
	CefV8Value* GetValue();

private:

	CefV8Value* _value;

protected:
	IMPLEMENT_REFCOUNTING(ACFV8RetValCallback);
};

class ACFOnPopupRetCallback : public CefBaseRefCounted
{
public:

	ACFOnPopupRetCallback();
	~ACFOnPopupRetCallback();

	void SetValue(CefDictionaryValue* ret_val);
	CefDictionaryValue* GetValue();

private:

	CefDictionaryValue* _value;

protected:
	IMPLEMENT_REFCOUNTING(ACFOnPopupRetCallback);
};

///////////////////////////////////////////////////////////////////////////////

class ACFlibStringVisitor : public CefStringVisitor
{
public:
	ACFlibStringVisitor(LPVOID lpCallback, BOOL copyData);
	~ACFlibStringVisitor();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual void Visit(const CefString& string) OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibStringVisitor);
};

class ACFlibDOMVisitor : public CefDOMVisitor
{
public:
	ACFlibDOMVisitor(LPVOID lpCallback, BOOL copyData);
	~ACFlibDOMVisitor();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual void Visit(CefRefPtr<CefDOMDocument> document) OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibDOMVisitor);
};

class ACFlibMenuModelDelegate : public CefMenuModelDelegate
{
public:

	ACFlibMenuModelDelegate(LPVOID lpCallback, BOOL copyData);
	~ACFlibMenuModelDelegate();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual void ExecuteCommand(CefRefPtr<CefMenuModel> menu_model,
		int command_id,
		cef_event_flags_t event_flags)  OVERRIDE;

	virtual void MouseOutsideMenu(CefRefPtr<CefMenuModel> menu_model,
		const CefPoint& screen_point)  OVERRIDE;

	virtual void UnhandledOpenSubmenu(CefRefPtr<CefMenuModel> menu_model,
		bool is_rtl)  OVERRIDE;

	virtual void UnhandledCloseSubmenu(CefRefPtr<CefMenuModel> menu_model,
		bool is_rtl)  OVERRIDE;

	virtual void MenuWillShow(CefRefPtr<CefMenuModel> menu_model)  OVERRIDE;

	virtual void MenuClosed(CefRefPtr<CefMenuModel> menu_model)  OVERRIDE;

	virtual bool FormatLabel(CefRefPtr<CefMenuModel> menu_model,
		CefString& label)  OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibMenuModelDelegate);
};

class ACFlibV8Accessor : public CefV8Accessor
{
public:

	ACFlibV8Accessor(LPVOID lpCallback, BOOL copyData);
	~ACFlibV8Accessor();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual bool Get(const CefString& name,
		const CefRefPtr<CefV8Value> object,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception)  OVERRIDE;

	virtual bool Set(const CefString& name,
		const CefRefPtr<CefV8Value> object,
		const CefRefPtr<CefV8Value> value,
		CefString& exception)  OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibV8Accessor);
};

class ACFlibV8Interceptor : public CefV8Interceptor
{
public:

	ACFlibV8Interceptor(LPVOID lpCallback, BOOL copyData);
	~ACFlibV8Interceptor();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual bool Get(const CefString& name,
		const CefRefPtr<CefV8Value> object,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception)  OVERRIDE;

	virtual bool Get(int index,
		const CefRefPtr<CefV8Value> object,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception)  OVERRIDE;

	virtual bool Set(const CefString& name,
		const CefRefPtr<CefV8Value> object,
		const CefRefPtr<CefV8Value> value,
		CefString& exception)  OVERRIDE;

	virtual bool Set(int index,
		const CefRefPtr<CefV8Value> object,
		const CefRefPtr<CefV8Value> value,
		CefString& exception)  OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibV8Interceptor);
};

class ACFlibV8ArrayBufferReleaseCallback : public CefV8ArrayBufferReleaseCallback
{
public:

	ACFlibV8ArrayBufferReleaseCallback(LPVOID lpCallback, BOOL copyData);
	~ACFlibV8ArrayBufferReleaseCallback();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual void ReleaseBuffer(void* buffer)  OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibV8ArrayBufferReleaseCallback);
};

class ACFlibV8Handler : public CefV8Handler
{
public:

	ACFlibV8Handler(LPVOID lpCallback, BOOL copyData);
	~ACFlibV8Handler();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual bool Execute(const CefString& name,
		CefRefPtr<CefV8Value> object,
		const CefV8ValueList& arguments,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception)  OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibV8Handler);

};

class ACFlibRequestContextHandler : public CefRequestContextHandler
{
public:

	ACFlibRequestContextHandler(LPVOID lpCallback, BOOL copyData);
	~ACFlibRequestContextHandler();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual void OnRequestContextInitialized(
		CefRefPtr<CefRequestContext> request_context)  OVERRIDE;

	virtual bool OnBeforePluginLoad(const CefString& mime_type,
		const CefString& plugin_url,
		bool is_main_frame,
		const CefString& top_origin_url,
		CefRefPtr<CefWebPluginInfo> plugin_info,
		PluginPolicy* plugin_policy)  OVERRIDE;

	virtual CefRefPtr<CefResourceRequestHandler> GetResourceRequestHandler(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		bool is_navigation,
		bool is_download,
		const CefString& request_initiator,
		bool& disable_default_handling)  OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibRequestContextHandler);
};

class ACFlibCompletionCallback : public CefCompletionCallback
{
public:

	ACFlibCompletionCallback(LPVOID lpCallback, BOOL copyData);
	~ACFlibCompletionCallback();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual void OnComplete()  OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibCompletionCallback);
};


class ACFlibCookieVisitor : public CefCookieVisitor
{
public:
	ACFlibCookieVisitor(LPVOID lpCallback, BOOL copyData);
	~ACFlibCookieVisitor();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual bool Visit(const CefCookie& cookie,
		int count,
		int total,
		bool& deleteCookie)  OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibCookieVisitor);
};

class ACFlibResolveCallback : public CefResolveCallback
{
public:
	ACFlibResolveCallback(LPVOID lpCallback, BOOL copyData);
	~ACFlibResolveCallback();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual void OnResolveCompleted(
		cef_errorcode_t result,
		const std::vector<CefString>& resolved_ips)  OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibResolveCallback);
};

class ACFlibRunFileDialogCallback : public CefRunFileDialogCallback
{
public:

	ACFlibRunFileDialogCallback(LPVOID lpCallback, BOOL copyData);
	~ACFlibRunFileDialogCallback();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual void OnFileDialogDismissed(
		int selected_accept_filter,
		const std::vector<CefString>& file_paths)  OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibRunFileDialogCallback);
};

class ACFlibDownloadImageCallback : public CefDownloadImageCallback
{
public:

	ACFlibDownloadImageCallback(LPVOID lpCallback, BOOL copyData);
	~ACFlibDownloadImageCallback();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual void OnDownloadImageFinished(const CefString& image_url,
		int http_status_code,
		CefRefPtr<CefImage> image)  OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibDownloadImageCallback);
};

class ACFlibPdfPrintCallback : public CefPdfPrintCallback
{
public:

	ACFlibPdfPrintCallback(LPVOID lpCallback, BOOL copyData);
	~ACFlibPdfPrintCallback();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual void OnPdfPrintFinished(const CefString& path, bool ok) OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibPdfPrintCallback);
};

class ACFlibURLRequestClient : public CefURLRequestClient
{
public:

	ACFlibURLRequestClient(LPVOID lpCallback, BOOL copyData);
	~ACFlibURLRequestClient();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual void OnRequestComplete(CefRefPtr<CefURLRequest> request)  OVERRIDE;;

	virtual void OnUploadProgress(CefRefPtr<CefURLRequest> request,
		int64 current,
		int64 total)  OVERRIDE;;

	virtual void OnDownloadProgress(CefRefPtr<CefURLRequest> request,
		int64 current,
		int64 total)  OVERRIDE;

	virtual void OnDownloadData(CefRefPtr<CefURLRequest> request,
		const void* data,
		size_t data_length)  OVERRIDE;

	virtual bool GetAuthCredentials(bool isProxy,
		const CefString& host,
		int port,
		const CefString& realm,
		const CefString& scheme,
		CefRefPtr<CefAuthCallback> callback)  OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibURLRequestClient);
};

class ACFlibDevToolsMessageObserver : public CefDevToolsMessageObserver
{
public:

	ACFlibDevToolsMessageObserver(LPVOID lpCallback, BOOL copyData);
	~ACFlibDevToolsMessageObserver();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual bool OnDevToolsMessage(CefRefPtr<CefBrowser> browser,
		const void* message,
		size_t message_size)  OVERRIDE;

	virtual void OnDevToolsMethodResult(CefRefPtr<CefBrowser> browser,
		int message_id,
		bool success,
		const void* result,
		size_t result_size)  OVERRIDE;

	virtual void OnDevToolsEvent(CefRefPtr<CefBrowser> browser,
		const CefString& method,
		const void* params,
		size_t params_size)  OVERRIDE;

	virtual void OnDevToolsAgentAttached(CefRefPtr<CefBrowser> browser)  OVERRIDE;

	virtual void OnDevToolsAgentDetached(CefRefPtr<CefBrowser> browser)  OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibDevToolsMessageObserver);
};

#ifdef ACF_EXVER

class ACFlibPermissionHandler : public CefPermissionHandler
{
public:

	ACFlibPermissionHandler(LPVOID lpCallback, BOOL copyData);
	~ACFlibPermissionHandler();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual bool RequestPermission(
		PermissionType permission,
		bool user_gesture)  OVERRIDE;

	virtual bool RequestPermissions(
		PermissionType permission,
		bool user_gesture,
		int total,
		int count)  OVERRIDE;

	virtual void ResetPermission(
		PermissionType permission,
		const CefString& requesting_origin,
		const CefString& embedding_origin)  OVERRIDE;

	virtual bool GetPermissionStatus(
		PermissionType permission,
		const CefString& requesting_origin,
		const CefString& embedding_origin)  OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibPermissionHandler);
};

#endif

class ACFlibNavigationEntryVisitor : public CefNavigationEntryVisitor
{
public:

	ACFlibNavigationEntryVisitor(LPVOID lpCallback, BOOL copyData);
	~ACFlibNavigationEntryVisitor();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	bool Visit(CefRefPtr<CefNavigationEntry> entry,
		bool current,
		int index,
		int total)  OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibNavigationEntryVisitor);
};

class ACFlibExtensionHandler : public CefExtensionHandler
{
public:

	ACFlibExtensionHandler(LPVOID lpCallback, BOOL copyData);
	~ACFlibExtensionHandler();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual void OnExtensionLoadFailed(cef_errorcode_t result)  OVERRIDE;

	virtual void OnExtensionLoaded(CefRefPtr<CefExtension> extension)  OVERRIDE;

	virtual void OnExtensionUnloaded(CefRefPtr<CefExtension> extension)  OVERRIDE;

	virtual bool OnBeforeBackgroundBrowser(CefRefPtr<CefExtension> extension,
		const CefString& url,
		CefRefPtr<CefClient>& client,
		CefBrowserSettings& settings)  OVERRIDE;

	virtual bool OnBeforeBrowser(CefRefPtr<CefExtension> extension,
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefBrowser> active_browser,
		int index,
		const CefString& url,
		bool active,
		CefWindowInfo& windowInfo,
		CefRefPtr<CefClient>& client,
		CefBrowserSettings& settings)  OVERRIDE;

	virtual CefRefPtr<CefBrowser> GetActiveBrowser(
		CefRefPtr<CefExtension> extension,
		CefRefPtr<CefBrowser> browser,
		bool include_incognito)  OVERRIDE;

	virtual bool CanAccessBrowser(CefRefPtr<CefExtension> extension,
		CefRefPtr<CefBrowser> browser,
		bool include_incognito,
		CefRefPtr<CefBrowser> target_browser)  OVERRIDE;

	virtual bool GetExtensionResource(
		CefRefPtr<CefExtension> extension,
		CefRefPtr<CefBrowser> browser,
		const CefString& file,
		CefRefPtr<CefGetExtensionResourceCallback> callback)  OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibExtensionHandler);
};

class ACFlibServerHandler : public CefServerHandler
{
public:

	ACFlibServerHandler(LPVOID lpCallback, BOOL copyData);
	~ACFlibServerHandler();

private:

	LPVOID m_callback; BOOL m_copyData;

protected:

	virtual void OnServerCreated(CefRefPtr<CefServer> server)  OVERRIDE;

	virtual void OnServerDestroyed(CefRefPtr<CefServer> server)  OVERRIDE;

	virtual void OnClientConnected(CefRefPtr<CefServer> server,
		int connection_id)  OVERRIDE;

	virtual void OnClientDisconnected(CefRefPtr<CefServer> server,
		int connection_id)  OVERRIDE;

	virtual void OnHttpRequest(CefRefPtr<CefServer> server,
		int connection_id,
		const CefString& client_address,
		CefRefPtr<CefRequest> request)  OVERRIDE;

	virtual void OnWebSocketRequest(CefRefPtr<CefServer> server,
		int connection_id,
		const CefString& client_address,
		CefRefPtr<CefRequest> request,
		CefRefPtr<CefCallback> callback)  OVERRIDE;

	virtual void OnWebSocketConnected(CefRefPtr<CefServer> server,
		int connection_id)  OVERRIDE;

	virtual void OnWebSocketMessage(CefRefPtr<CefServer> server,
		int connection_id,
		const void* data,
		size_t data_size)  OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibServerHandler);
};