
#include "acf_App.h"
#include "acf_Types.h"
#include "acf_Class.h"

#include "acf_Conv.h"

ACFlibApp::ACFlibApp() :
	m_pAppCallback(0) {}

ACFlibApp::ACFlibApp(LPVOID lpAppCallback, BOOL copyData) :
	m_pAppCallback(lpAppCallback), m_copyData(copyData) {}

ACFlibApp::~ACFlibApp()
{
	if (this->m_pAppCallback && this->m_copyData)
		LocalFree(this->m_pAppCallback);
}

void ACFlibApp::OnBeforeCommandLineProcessing(
	const CefString& process_type,
	CefRefPtr<CefCommandLine> command_line)
{
	if (this->m_pAppCallback != NULL)
	{
		command_line->AddRef();
		IMP_NEWECLASS(TempVfptr, command_line.get(), eClass::m_pVfCmdTable, acf_commandline_funcs);

		LPVOID strProcessType = UnicodeToEStream(process_type.c_str());
		LPVOID lpTempAddr = &strProcessType;

		LPVOID pClass = this->m_pAppCallback;
		__asm{
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempVfptr;
			push lpTempAddr;
			push ecx;
			call [edx + 0x8];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		command_line->Release();
	}
}

void ACFlibApp::OnContextInitialized()
{
	if (this->m_pAppCallback != NULL)
	{
		LPVOID pClass = this->m_pAppCallback;
		__asm{
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push ecx;
			call [edx + 0xC];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
	}
}

void ACFlibApp::OnBeforeChildProcessLaunch(
	CefRefPtr<CefCommandLine> command_line)
{
	if (this->m_pAppCallback != NULL)
	{
		command_line->AddRef();
		IMP_NEWECLASS(TempVfptr, command_line.get(), eClass::m_pVfCmdTable, acf_commandline_funcs);
		LPVOID pClass = this->m_pAppCallback;
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempVfptr;
			push ecx;
			call[edx + 0x10];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		command_line->Release();
	}
}

void ACFlibApp::OnScheduleMessagePumpWork(int64 delay_ms)
{
	if (this->m_pAppCallback != NULL)
	{
		LPVOID pClass = this->m_pAppCallback;

		char* pLoingValue = (char*)&delay_ms;
		DWORD dwValue1 = *(DWORD*)&pLoingValue[0];
		DWORD dwValue2 = *(DWORD*)&pLoingValue[4];
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push dwValue2;
			push dwValue1;
			push ecx;
			call[edx + 0x14];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
	}
}

void ACFlibApp::OnWebKitInitialized()
{
	if (this->m_pAppCallback != NULL)
	{
		LPVOID pClass = this->m_pAppCallback;
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push ecx;
			call[edx + 0x18];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
	}
}

void ACFlibApp::OnBrowserCreated(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefDictionaryValue> extra_info)
{
	if (this->m_pAppCallback != NULL)
	{
		LPVOID pClass = this->m_pAppCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempDictionary, extra_info.get() ? extra_info.get() : NULL, eClass::m_pVfDictionaryTable, acf_dictionary_funcs);

		browser->AddRef();
		if (extra_info)
			extra_info->AddRef();
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempDictionary;
			push TempBrowser;
			push ecx;
			call[edx + 0x1C];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		if (extra_info)
			extra_info->Release();
		browser->Release();
	}
}

void ACFlibApp::OnBrowserDestroyed(CefRefPtr<CefBrowser> browser)
{
	if (this->m_pAppCallback != NULL)
	{
		LPVOID pClass = this->m_pAppCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		browser->AddRef();
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempBrowser;
			push ecx;
			call[edx + 0x20];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
	}
}

void ACFlibApp::OnContextCreated(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context)
{
	if (this->m_pAppCallback != NULL)
	{
		LPVOID pClass = this->m_pAppCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempContext, context.get(), eClass::m_pVfV8ContextTable, acf_v8_context_funcs);
		browser->AddRef();
		frame->AddRef();
		context->AddRef();
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempContext;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x24];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
		context->Release();
	}
}

void ACFlibApp::OnContextReleased(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context)
{
	if (this->m_pAppCallback != NULL)
	{
		LPVOID pClass = this->m_pAppCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempContext, context.get(), eClass::m_pVfV8ContextTable, acf_v8_context_funcs);
		browser->AddRef();
		frame->AddRef();
		context->AddRef();
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempContext;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x28];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
		context->Release();
	}
}

void ACFlibApp::OnUncaughtException(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context,
	CefRefPtr<CefV8Exception> exception,
	CefRefPtr<CefV8StackTrace> stackTrace)
{
	if (this->m_pAppCallback != NULL)
	{
		LPVOID pClass = this->m_pAppCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempContext, context.get(), eClass::m_pVfV8ContextTable, acf_v8_context_funcs);
		IMP_NEWECLASS(TempException, exception.get(), eClass::m_pVfV8ExceptionTable, acf_v8_exception_funcs);
		IMP_NEWECLASS(TempStackTrace, stackTrace.get(), eClass::m_pVfV8StackTraceTable, acf_v8_stack_trace_funcs);
		browser->AddRef();
		frame->AddRef();
		context->AddRef();
		exception->AddRef();
		stackTrace->AddRef();
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempStackTrace;
			push TempException;
			push TempContext;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x2C];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
		context->Release();
		exception->Release();
		stackTrace->Release();
	}
}

void ACFlibApp::OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefDOMNode> node)
{
	if (this->m_pAppCallback != NULL)
	{
		LPVOID pClass = this->m_pAppCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempNode, node.get(), eClass::m_pVfDOMNodeTable, acf_dom_node_funcs);
		browser->AddRef();
		frame->AddRef();
		if (node)
			node->AddRef();
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempNode;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x30];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
		if (node)
			node->Release();
	}
}

bool ACFlibApp::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefProcessId source_process,
	CefRefPtr<CefProcessMessage> message)
{
	if (this->m_pAppCallback != NULL)
	{
		LPVOID pClass = this->m_pAppCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempMessage, message.get(), eClass::m_pVfProcessMessageTable, acf_process_message_funcs);
		browser->AddRef();
		frame->AddRef();
		message->AddRef();
		BOOL nRetVal = 0;
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempMessage;
			push source_process;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x34];
			mov nRetVal, eax;
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
		message->Release();
		return nRetVal;
	}
	return false;
}

void ACFlibApp::OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
	bool isLoading,
	bool canGoBack,
	bool canGoForward)
{
	if (this->m_pAppCallback != NULL)
	{
		LPVOID pClass = this->m_pAppCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		browser->AddRef();
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, canGoForward;
			push eax;
			movzx eax, canGoBack;
			push eax;
			movzx eax, isLoading;
			push eax;
			push TempBrowser;
			push ecx;
			call[edx + 0x38];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
	}
}

void ACFlibApp::OnLoadStart(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	TransitionType transition_type)
{ 
	if (this->m_pAppCallback != NULL)
	{
		LPVOID pClass = this->m_pAppCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		browser->AddRef();
		frame->AddRef();
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push transition_type;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x3C];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
	}
}

void ACFlibApp::OnLoadEnd(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	int httpStatusCode)
{ 
	if (this->m_pAppCallback != NULL)
	{
		LPVOID pClass = this->m_pAppCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		browser->AddRef();
		frame->AddRef();
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push httpStatusCode;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x40];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
	}
}

void ACFlibApp::OnLoadError(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	ErrorCode errorCode,
	const CefString& errorText,
	const CefString& failedUrl)
{
	if (this->m_pAppCallback != NULL)
	{
		LPVOID pClass = this->m_pAppCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		browser->AddRef();
		frame->AddRef();

		USES_CONVERSION;

		LPVOID error_str = UnicodeToEStream(errorText.c_str());
		LPVOID url_str = UnicodeToEStream(failedUrl.c_str());

		LPVOID lpAddr1 = &error_str, lpAddr2 = &url_str;

		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lpAddr2;
			push lpAddr1;
			push errorCode;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x44];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
	}
}

void ACFlibApp::OnRegisterCustomSchemes(
	CefRawPtr<CefSchemeRegistrar> registrar)
{
	// FIXME: ready to add binding to epl
}
