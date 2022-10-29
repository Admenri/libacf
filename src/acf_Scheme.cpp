
#include "acf_Scheme.h"
#include "acf_Class.h"
#include "acf_Conv.h"

extern DWORD acf_callback_resource_read[];
extern DWORD acf_callback_resource_skip[];
extern DWORD acf_callback[];

void ECALL resread_continue(CefResourceReadCallback* obj, int bytes_read)
{
    ISVALID(obj);

    obj->Continue(bytes_read);
}

void ECALL resskip_continue(CefResourceSkipCallback* obj, int64* bytes_skipped)
{
    ISVALID(obj);

    obj->Continue(*bytes_skipped);
}

void ECALL callback_continue(CefCallback* obj)
{
	ISVALID(obj);

	obj->Continue();
}

void ECALL callback_cancel(CefCallback* obj)
{
	ISVALID(obj);

	obj->Cancel();
}

DWORD acf_callback_resource_read[] = {
    (DWORD)&resread_continue,
};

DWORD acf_callback_resource_skip[] = {
    (DWORD)&resskip_continue,
};

DWORD acf_callback[] = {
	(DWORD)&callback_continue,
	(DWORD)&callback_cancel,
};

ACF_EXPORTS(RegisterSchemeHandlerFactory, BOOL)(LPWSTR scheme, LPWSTR domain, LPVOID callback, BOOL copyData)
{
    CefRefPtr<ACFlibSchemeHandler> lpHandler = callback ? new ACFlibSchemeHandler(callback, copyData) : nullptr;
	
    return CefRegisterSchemeHandlerFactory(scheme, domain, lpHandler);
}

ACFlibSchemeHandler::ACFlibSchemeHandler(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibSchemeHandler::~ACFlibSchemeHandler() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

CefRefPtr<CefResourceHandler> ACFlibSchemeHandler::Create(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	const CefString& scheme_name,
	CefRefPtr<CefRequest> request)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfRequestTable, acf_request_funcs);

		USES_CONVERSION;

		LPVOID pSchemeName = UnicodeToEStream(scheme_name.c_str());
		LPVOID lpNameAddr = &pSchemeName;

		browser->AddRef();
		frame->AddRef();
		request->AddRef();
		BOOL bRetVal = NULL;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempRequest;
			push lpNameAddr;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x08];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		frame->Release();
		request->Release();

		if (bRetVal)
		{
			m_browser = browser;
			m_frame = frame;

			return this;
		}
	}

	return nullptr;
}

bool ACFlibSchemeHandler::Open(CefRefPtr<CefRequest> request,
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
			call[edx + 0x0C];
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
};

void ACFlibSchemeHandler::GetResponseHeaders(CefRefPtr<CefResponse> response,
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
			call[edx + 0x10];
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
};

bool ACFlibSchemeHandler::Skip(int64 bytes_to_skip,
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
			call[edx + 0x14];
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
};

bool ACFlibSchemeHandler::Read(void* data_out,
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
			call[edx + 0x18];
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
};

void ACFlibSchemeHandler::Cancel()
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
			call[edx + 0x1C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		m_browser->Release();
		m_frame->Release();
	}
};
