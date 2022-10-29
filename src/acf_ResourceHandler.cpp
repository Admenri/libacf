
#include "acf_ResourceHandler.h"

ACFlibResourceHandler::ACFlibResourceHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, LPVOID callback) : m_browser(browser), m_frame(frame), m_callback(callback) {}

ACFlibResourceHandler::~ACFlibResourceHandler() {}

bool ACFlibResourceHandler::Open(CefRefPtr<CefRequest> request,
	bool& handle_request,
	CefRefPtr<CefCallback> callback)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		USES_CONVERSION;

		IMP_NEWECLASS(TempBrowser, m_browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, m_frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfRequestTable, acf_request_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallback, acf_callback);

		BOOL pHandle_request = NULL;

		LPVOID lpAddr1 = &pHandle_request;

		m_browser->AddRef();
		m_frame->AddRef();
		request->AddRef();
		callback->AddRef();
		BOOL bRetVal = NULL;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempCallback;
			push lpAddr1;
			push TempRequest;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x148];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		m_browser->Release();
		m_frame->Release();
		request->Release();
		callback->Release();

		handle_request = pHandle_request;
		return bRetVal;
	}
	return false;
}

void ACFlibResourceHandler::GetResponseHeaders(CefRefPtr<CefResponse> response,
	int64& response_length,
	CefString& redirectUrl)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		USES_CONVERSION;

		IMP_NEWECLASS(TempBrowser, m_browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, m_frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempResponse, response.get(), eClass::m_pVfResponseTable, acf_response_funcs);

		LPSTR pUrl = new char[4096];
		ZeroMemory(pUrl, 4096);

		int64 pLength = NULL;
		LPVOID lpLength = &pLength;

		m_browser->AddRef();
		m_frame->AddRef();
		response->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push pUrl;
			push lpLength;
			push TempResponse;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x14C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		m_browser->Release();
		m_frame->Release();
		response->Release();

		if (*pUrl != '\0')
			redirectUrl = CefString(pUrl);
		response_length = pLength;
	}
}

bool ACFlibResourceHandler::Skip(int64 bytes_to_skip,
	int64& bytes_skipped,
	CefRefPtr<CefResourceSkipCallback> callback)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		USES_CONVERSION;

		IMP_NEWECLASS(TempBrowser, m_browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, m_frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallbackResourceSkip, acf_callback_resource_skip);

		char* pLoingValue = (char*)&bytes_to_skip;
		DWORD dwValue1 = *(DWORD*)&pLoingValue[0];
		DWORD dwValue2 = *(DWORD*)&pLoingValue[4];

		int64 pLength = NULL;
		LPVOID lpLength = &pLength;

		m_browser->AddRef();
		m_frame->AddRef();
		callback->AddRef();
		BOOL bRetVal = NULL;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempCallback;
			push lpLength;
			push dwValue2;
			push dwValue1;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x150];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		m_browser->Release();
		m_frame->Release();
		callback->Release();

		bytes_skipped = pLength;
		return bRetVal;
	}
	return false;
}

bool ACFlibResourceHandler::Read(void* data_out,
	int bytes_to_read,
	int& bytes_read,
	CefRefPtr<CefResourceReadCallback> callback)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		USES_CONVERSION;

		IMP_NEWECLASS(TempBrowser, m_browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, m_frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallbackResourceRead, acf_callback_resource_read);

		int pLength = NULL;
		LPVOID lpLength = &pLength;

		m_browser->AddRef();
		m_frame->AddRef();
		callback->AddRef();
		BOOL bRetVal = NULL;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempCallback;
			push lpLength;
			push bytes_to_read;
			push data_out;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x154];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		m_browser->Release();
		m_frame->Release();
		callback->Release();

		bytes_read = pLength;
		return bRetVal;
	}
	return false;
}

void ACFlibResourceHandler::Cancel()
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		USES_CONVERSION;

		IMP_NEWECLASS(TempBrowser, m_browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, m_frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);

		m_browser->AddRef();
		m_frame->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x158];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		m_browser->Release();
		m_frame->Release();
	}
}
