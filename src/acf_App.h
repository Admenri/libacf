#pragma once

#include "include\cef_app.h"

#include "acf_Client.h"
#include "acf_Types.h"

class ACFlibApp : public CefApp,
	public CefBrowserProcessHandler,
	public CefRenderProcessHandler,
	public CefLoadHandler
{

public:

	ACFlibApp();
	ACFlibApp(LPVOID lpAppCallback, BOOL copyData);
	~ACFlibApp();

	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE { return this; }

	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE { return this; }

private:

	LPVOID m_pAppCallback;
	BOOL m_copyData;

protected:

	virtual void OnBeforeCommandLineProcessing(
		const CefString& process_type,
		CefRefPtr<CefCommandLine> command_line) OVERRIDE;

	virtual void OnContextInitialized() OVERRIDE;

	virtual void OnBeforeChildProcessLaunch(
		CefRefPtr<CefCommandLine> command_line)  OVERRIDE;

	virtual void OnScheduleMessagePumpWork(int64 delay_ms)  OVERRIDE;

	// ------------------- Renderer --------------------

	virtual void OnWebKitInitialized()  OVERRIDE;

	virtual void OnBrowserCreated(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDictionaryValue> extra_info)  OVERRIDE;

	virtual void OnBrowserDestroyed(CefRefPtr<CefBrowser> browser)  OVERRIDE;

	virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context)  OVERRIDE;

	virtual void OnContextReleased(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context)  OVERRIDE;

	virtual void OnUncaughtException(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context,
		CefRefPtr<CefV8Exception> exception,
		CefRefPtr<CefV8StackTrace> stackTrace)  OVERRIDE;

	virtual void OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefDOMNode> node)  OVERRIDE;

	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message)  OVERRIDE;

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

protected:

	IMPLEMENT_REFCOUNTING(ACFlibApp);

};
