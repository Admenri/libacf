#pragma once

#include "acf_ResourceFilter.h"
#include "include\cef_client.h"
#include <list>

class ACFlibClient : public CefClient,
	public CefLifeSpanHandler,
	public CefLoadHandler,
	public CefDisplayHandler,
	public CefContextMenuHandler,
	public CefRenderHandler,
	public CefDownloadHandler,
	public CefDragHandler,
	public CefFindHandler,
	public CefJSDialogHandler,
	public CefDialogHandler,
	public CefKeyboardHandler,
	public CefRequestHandler,
	public CefResourceRequestHandler,
	public CefCookieAccessFilter,
	public CefFocusHandler,
	public CefLockHandler,
	public CefAudioHandler,
	public CefPermissionHandler
{
	typedef std::list<CefRefPtr<CefBrowser>> BrowserListValue;

public:

	ACFlibClient();
	ACFlibClient(LPVOID lpClientCallback, BOOL copyData);
	~ACFlibClient();

	static CefRefPtr<ACFlibClient> GetInterface();
	void PushItem(CefRefPtr<CefBrowser> browser);
	void RemoveItem(CefRefPtr<CefBrowser> browser);
	void ClearAllItems();
	int GetItemsCount() { return m_pListValue.size(); }
	CefRefPtr<CefBrowser> GetBrowserObject(HWND hWnd);
	CefRefPtr<CefBrowser> GetBrowserObjectAt(int index);
	CefRefPtr<CefBrowser> GetBrowserObjectId(int identity);
	BOOL IsUserBrowser(CefRefPtr<CefBrowser> browser);
	void CloseAllBrowsers();

	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE{ return this; }
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefDownloadHandler> GetDownloadHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefDragHandler> GetDragHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefFindHandler> GetFindHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefJSDialogHandler> GetJSDialogHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefDialogHandler> GetDialogHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefRequestHandler> GetRequestHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefFocusHandler> GetFocusHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefLockHandler> GetLockHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefAudioHandler> GetAudioHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefPermissionHandler> GetPermissionHandler() OVERRIDE { return this; }

private:

	LPVOID m_pClientCallback;
	BrowserListValue m_pListValue;
	BOOL m_copyData;

public:

	virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& target_url,
		const CefString& target_frame_name,
		CefLifeSpanHandler::WindowOpenDisposition target_disposition,
		bool user_gesture,
		const CefPopupFeatures& popupFeatures,
		CefWindowInfo& windowInfo,
		CefRefPtr<CefClient>& client,
		CefBrowserSettings& settings,
		CefRefPtr<CefDictionaryValue>& extra_info,
		bool* no_javascript_access) OVERRIDE;

	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDictionaryValue> extra_info)  OVERRIDE;

	virtual bool DoClose(CefRefPtr<CefBrowser> browser)  OVERRIDE;

	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser)  OVERRIDE;

	virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
		bool isLoading,
		bool canGoBack,
		bool canGoForward)  OVERRIDE;

	virtual void OnLoadStart(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		TransitionType transition_type)  OVERRIDE;

	virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		int httpStatusCode)  OVERRIDE;

	virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		ErrorCode errorCode,
		const CefString& errorText,
		const CefString& failedUrl)  OVERRIDE;

	virtual void OnAddressChange(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& url)  OVERRIDE;

	virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
		const CefString& title)  OVERRIDE;

	virtual void OnFaviconURLChange(CefRefPtr<CefBrowser> browser,
		const std::vector<CefString>& icon_urls)  OVERRIDE;

	virtual void OnFullscreenModeChange(CefRefPtr<CefBrowser> browser,
		bool fullscreen)  OVERRIDE;

	virtual bool OnTooltip(CefRefPtr<CefBrowser> browser, CefString& text)  OVERRIDE;

	virtual void OnStatusMessage(CefRefPtr<CefBrowser> browser,
		const CefString& value)  OVERRIDE;

	virtual bool OnConsoleMessage(CefRefPtr<CefBrowser> browser,
		cef_log_severity_t level,
		const CefString& message,
		const CefString& source,
		int line)  OVERRIDE;

	virtual bool OnAutoResize(CefRefPtr<CefBrowser> browser,
		const CefSize& new_size)  OVERRIDE;

	virtual void OnLoadingProgressChange(CefRefPtr<CefBrowser> browser,
		double progress)  OVERRIDE;

	virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefContextMenuParams> params,
		CefRefPtr<CefMenuModel> model)  OVERRIDE;

	virtual bool RunContextMenu(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefContextMenuParams> params,
		CefRefPtr<CefMenuModel> model,
		CefRefPtr<CefRunContextMenuCallback> callback)  OVERRIDE;

	virtual bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefContextMenuParams> params,
		int command_id,
		EventFlags event_flags)  OVERRIDE;

	virtual void OnContextMenuDismissed(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame)  OVERRIDE;

	virtual bool GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect& rect)  OVERRIDE;

	virtual void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)  OVERRIDE;

	virtual bool GetScreenPoint(CefRefPtr<CefBrowser> browser,
		int viewX,
		int viewY,
		int& screenX,
		int& screenY)  OVERRIDE;

	virtual bool GetScreenInfo(CefRefPtr<CefBrowser> browser,
		CefScreenInfo& screen_info)  OVERRIDE;

	virtual void OnPopupShow(CefRefPtr<CefBrowser> browser, bool show)  OVERRIDE;

	virtual void OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect)  OVERRIDE;

	virtual void OnPaint(CefRefPtr<CefBrowser> browser,
		PaintElementType type,
		const RectList& dirtyRects,
		const void* buffer,
		int width,
		int height)  OVERRIDE;

	virtual void OnAcceleratedPaint(CefRefPtr<CefBrowser> browser,
		PaintElementType type,
		const RectList& dirtyRects,
		void* shared_handle)  OVERRIDE;

	virtual bool OnCursorChange(CefRefPtr<CefBrowser> browser,
		CefCursorHandle cursor,
		cef_cursor_type_t type,
		const CefCursorInfo& custom_cursor_info)  OVERRIDE;

	virtual bool StartDragging(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDragData> drag_data,
		CefDragHandler::DragOperationsMask allowed_ops,
		int x,
		int y)  OVERRIDE;

	virtual void UpdateDragCursor(CefRefPtr<CefBrowser> browser,
		DragOperation operation)  OVERRIDE;

	virtual void OnScrollOffsetChanged(CefRefPtr<CefBrowser> browser,
		double x,
		double y)  OVERRIDE;

	virtual void OnImeCompositionRangeChanged(CefRefPtr<CefBrowser> browser,
		const CefRange& selected_range,
		const RectList& character_bounds)  OVERRIDE;

	virtual void OnTextSelectionChanged(CefRefPtr<CefBrowser> browser,
		const CefString& selected_text,
		const CefRange& selected_range)  OVERRIDE;

	virtual void OnVirtualKeyboardRequested(CefRefPtr<CefBrowser> browser,
		TextInputMode input_mode)  OVERRIDE;

	virtual void OnBeforeDownload(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDownloadItem> download_item,
		const CefString& suggested_name,
		CefRefPtr<CefBeforeDownloadCallback> callback)  OVERRIDE;

	virtual void OnDownloadUpdated(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDownloadItem> download_item,
		CefRefPtr<CefDownloadItemCallback> callback)  OVERRIDE;

	virtual bool OnDragEnter(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDragData> dragData,
		CefDragHandler::DragOperationsMask mask)  OVERRIDE;

	virtual void OnDraggableRegionsChanged(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const std::vector<CefDraggableRegion>& regions) OVERRIDE;

	virtual void OnFindResult(CefRefPtr<CefBrowser> browser,
		int identifier,
		int count,
		const CefRect& selectionRect,
		int activeMatchOrdinal,
		bool finalUpdate)  OVERRIDE;

	virtual bool OnJSDialog(CefRefPtr<CefBrowser> browser,
		const CefString& origin_url,
		JSDialogType dialog_type,
		const CefString& message_text,
		const CefString& default_prompt_text,
		CefRefPtr<CefJSDialogCallback> callback,
		bool& suppress_message)  OVERRIDE;

	virtual bool OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser,
		const CefString& message_text,
		bool is_reload,
		CefRefPtr<CefJSDialogCallback> callback)  OVERRIDE;

	virtual void OnResetDialogState(CefRefPtr<CefBrowser> browser)  OVERRIDE;

	virtual void OnDialogClosed(CefRefPtr<CefBrowser> browser)  OVERRIDE;

	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message)  OVERRIDE;

	virtual bool OnFileDialog(CefRefPtr<CefBrowser> browser,
		FileDialogMode mode,
		const CefString& title,
		const CefString& default_file_path,
		const std::vector<CefString>& accept_filters,
		CefRefPtr<CefFileDialogCallback> callback)  OVERRIDE;

	virtual bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
		const CefKeyEvent& event,
		CefEventHandle os_event,
		bool* is_keyboard_shortcut)  OVERRIDE;

	virtual bool OnKeyEvent(CefRefPtr<CefBrowser> browser,
		const CefKeyEvent& event,
		CefEventHandle os_event)  OVERRIDE;

	virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		bool user_gesture,
		bool is_redirect)  OVERRIDE;

	virtual bool OnOpenURLFromTab(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& target_url,
		CefRequestHandler::WindowOpenDisposition target_disposition,
		bool user_gesture)  OVERRIDE;

	virtual CefRefPtr<CefResourceRequestHandler> GetResourceRequestHandler(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		bool is_navigation,
		bool is_download,
		const CefString& request_initiator,
		bool& disable_default_handling)  OVERRIDE;

	virtual bool GetAuthCredentials(CefRefPtr<CefBrowser> browser,
		const CefString& origin_url,
		bool isProxy,
		const CefString& host,
		int port,
		const CefString& realm,
		const CefString& scheme,
		CefRefPtr<CefAuthCallback> callback)  OVERRIDE;

	virtual bool OnQuotaRequest(CefRefPtr<CefBrowser> browser,
		const CefString& origin_url,
		int64 new_size,
		CefRefPtr<CefCallback> callback)  OVERRIDE;

	virtual bool OnCertificateError(CefRefPtr<CefBrowser> browser,
		cef_errorcode_t cert_error,
		const CefString& request_url,
		CefRefPtr<CefSSLInfo> ssl_info,
		CefRefPtr<CefCallback> callback)  OVERRIDE;

	virtual bool OnSelectClientCertificate(
		CefRefPtr<CefBrowser> browser,
		bool isProxy,
		const CefString& host,
		int port,
		const X509CertificateList& certificates,
		CefRefPtr<CefSelectClientCertificateCallback> callback)  OVERRIDE;

	virtual void OnRenderViewReady(CefRefPtr<CefBrowser> browser)  OVERRIDE;

	virtual void OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser,
		TerminationStatus status)  OVERRIDE;

	virtual void OnDocumentAvailableInMainFrame(CefRefPtr<CefBrowser> browser)  OVERRIDE;

	virtual CefRefPtr<CefCookieAccessFilter> GetCookieAccessFilter(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request)  OVERRIDE;

	virtual ReturnValue OnBeforeResourceLoad(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		CefRefPtr<CefCallback> callback)  OVERRIDE;

	virtual CefRefPtr<CefResourceHandler> GetResourceHandler(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request)  OVERRIDE;

	virtual void OnResourceRedirect(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		CefRefPtr<CefResponse> response,
		CefString& new_url)  OVERRIDE;

	virtual bool OnResourceResponse(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		CefRefPtr<CefResponse> response)  OVERRIDE;

	virtual CefRefPtr<CefResponseFilter> GetResourceResponseFilter(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		CefRefPtr<CefResponse> response)  OVERRIDE;

	virtual void OnResourceLoadComplete(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		CefRefPtr<CefResponse> response,
		URLRequestStatus status,
		int64 received_content_length)  OVERRIDE;

	virtual void OnProtocolExecution(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		bool& allow_os_execution)  OVERRIDE;

	virtual bool CanSendCookie(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		const CefCookie& cookie)  OVERRIDE;

	virtual bool CanSaveCookie(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		CefRefPtr<CefResponse> response,
		const CefCookie& cookie)  OVERRIDE;

	virtual void OnTakeFocus(CefRefPtr<CefBrowser> browser, bool next)  OVERRIDE;

	virtual bool OnSetFocus(CefRefPtr<CefBrowser> browser, FocusSource source)  OVERRIDE;

	virtual void OnGotFocus(CefRefPtr<CefBrowser> browser)  OVERRIDE;

	virtual void OnMouseLockRequest(CefRefPtr<CefBrowser> browser, bool is_lost)  OVERRIDE;

	virtual void OnKeyboardLockRequest(CefRefPtr<CefBrowser> browser, bool is_lost)  OVERRIDE;

	virtual bool GetAudioParameters(CefRefPtr<CefBrowser> browser,
		CefAudioParameters& params)  OVERRIDE;

	virtual void OnAudioStreamStarted(CefRefPtr<CefBrowser> browser,
		const CefAudioParameters& params,
		int channels)  OVERRIDE;

	virtual void OnAudioStreamPacket(CefRefPtr<CefBrowser> browser,
		const float** data,
		int frames,
		int64 pts)  OVERRIDE;

	virtual void OnAudioStreamStopped(CefRefPtr<CefBrowser> browser)  OVERRIDE;

	virtual void OnAudioStreamError(CefRefPtr<CefBrowser> browser,
		const CefString& message)  OVERRIDE;

	virtual void OnAudioStateChange(CefRefPtr<CefBrowser> browser,
		bool audible)  OVERRIDE;

	virtual bool OnRequestMediaAccessPermission(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& requesting_origin,
		uint32 requested_permissions,
		CefRefPtr<CefMediaAccessCallback> callback) OVERRIDE;

	virtual bool OnShowPermissionPrompt(
		CefRefPtr<CefBrowser> browser,
		uint64 prompt_id,
		const CefString& requesting_origin,
		uint32 requested_permissions,
		CefRefPtr<CefPermissionPromptCallback> callback) OVERRIDE;

	virtual void OnDismissPermissionPrompt(
		CefRefPtr<CefBrowser> browser,
		uint64 prompt_id,
		cef_permission_request_result_t result) OVERRIDE;

protected:

	IMPLEMENT_REFCOUNTING(ACFlibClient);

};
