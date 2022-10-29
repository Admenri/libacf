
#include "acf_Client.h"
#include "acf_Class.h"

#include "acf_FrameEvents.h"
#include "acf_Conv.h"
#include "acf_ResourceHandler.h"

namespace {
	CefRefPtr<ACFlibClient> g_lpObjClientInterface = nullptr;
}

ACFlibClient::ACFlibClient() :
	m_pClientCallback(0)
{
	g_lpObjClientInterface = this;
}

ACFlibClient::ACFlibClient(LPVOID lpClientCallback, BOOL copyData) :
	m_pClientCallback(lpClientCallback), m_copyData(copyData)
{
	g_lpObjClientInterface = nullptr;
}

ACFlibClient::~ACFlibClient()
{
	if (this->m_pClientCallback && this->m_copyData)
		LocalFree(this->m_pClientCallback);
}

CefRefPtr<ACFlibClient> ACFlibClient::GetInterface()
{
	return g_lpObjClientInterface;
}

void ACFlibClient::PushItem(CefRefPtr<CefBrowser> browser)
{
	this->m_pListValue.push_back(browser);
}

void ACFlibClient::RemoveItem(CefRefPtr<CefBrowser> browser)
{
	BrowserListValue::iterator iend = this->m_pListValue.end();
	for (BrowserListValue::iterator iter = this->m_pListValue.begin(); iter != iend; iter++)
	{
		if ((*iter)->IsSame(browser))
		{
			this->m_pListValue.erase(iter);
			break;
		}
	}
}

void ACFlibClient::ClearAllItems()
{
	this->m_pListValue.clear();
}

CefRefPtr<CefBrowser> ACFlibClient::GetBrowserObject(HWND hWnd)
{
	CefRefPtr<CefBrowserHost> lpObjHost = nullptr;
	BrowserListValue::iterator iend = this->m_pListValue.end();
	for (BrowserListValue::iterator iter = this->m_pListValue.begin(); iter != iend; iter++)
	{
		lpObjHost = (*iter)->GetHost();
		if (lpObjHost->GetWindowHandle() == hWnd)
			return (*iter);
	}
	return CefRefPtr<CefBrowser>();
}

CefRefPtr<CefBrowser> ACFlibClient::GetBrowserObjectAt(int index)
{
	CefRefPtr<CefBrowserHost> lpObjHost = nullptr;
	BrowserListValue::iterator iter = this->m_pListValue.begin();
	while (index--) iter++;
	return *iter;
}

CefRefPtr<CefBrowser> ACFlibClient::GetBrowserObjectId(int identity)
{
	BrowserListValue::iterator iend = this->m_pListValue.end();
	for (BrowserListValue::iterator iter = this->m_pListValue.begin(); iter != iend; iter++)
	{
		if ((*iter)->GetIdentifier() == identity)
			return (*iter);
	}
	return CefRefPtr<CefBrowser>();
}

BOOL ACFlibClient::IsUserBrowser(CefRefPtr<CefBrowser> browser)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		browser->AddRef();
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		BOOL bRetVal = FALSE;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
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
		return bRetVal;
	}
	return TRUE;
}

void ACFlibClient::CloseAllBrowsers()
{
	for (auto i : m_pListValue)
		i->GetHost()->CloseBrowser(true);
}

bool ACFlibClient::OnBeforePopup(CefRefPtr<CefBrowser> browser,
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
	bool* no_javascript_access)
{
	if (this->m_pClientCallback != NULL)
	{
		USES_CONVERSION;
		LPVOID lpTempAddr = UnicodeToEStream(target_url.c_str());
		LPVOID lpTempAddr2 = UnicodeToEStream(target_frame_name.c_str());
		LPVOID lpTargetAddr = &lpTempAddr;
		LPVOID lpTargetAddr2 = &lpTempAddr2;

		LPVOID pClass = this->m_pClientCallback;
		
		BOOL bRetVal = FALSE;
		browser->AddRef();
		frame->AddRef();

		ACFOnPopupRetCallback* callback = new ACFOnPopupRetCallback();

		cef_popup_features_t lpPopupfeature(popupFeatures);
		LPVOID lpPopFea = &lpPopupfeature;
		LPVOID lppPopFea = &lpPopFea;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempDictionary, callback, eClass::m_pVfCallbackOnPopup, acf_callback_onpopup);

		IMP_NEWECLASS2(TempInfo, &windowInfo, eClass::m_infoTable);
		IMP_NEWECLASS2(TempSettings, &settings, eClass::m_settingsTable);

		DWORD pClient = (DWORD)(LPVOID)browser->GetHost()->GetClient().get();
		LPVOID pClientPtr = &pClient;

		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push pClientPtr;
			push no_javascript_access;
			push TempDictionary;
			push TempSettings;
			push TempInfo;
			push lppPopFea;
			movzx eax, user_gesture;
			push eax;
			push target_disposition;
			push lpTargetAddr2;
			push lpTargetAddr;
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

		if (pClient >= 0)
			client = (CefClient*)pClient;

		if (callback->GetValue())
			extra_info = callback->GetValue();

		delete callback;

		browser->Release();
		frame->Release();
		return bRetVal;
	}
	return false;
}

void ACFlibClient::OnAfterCreated(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefDictionaryValue> extra_info)
{
	if (!this->IsUserBrowser(browser)) return;
	this->PushItem(browser);
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempDictionary, extra_info.get() ? extra_info.get() : NULL, eClass::m_pVfDictionaryTable, acf_dictionary_funcs);

		browser->AddRef();
		if (extra_info.get())
			extra_info->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempDictionary;
			push TempBrowser;
			push ecx;
			call[edx + 0x10];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		if (extra_info.get())
			extra_info->Release();
	}
}

bool ACFlibClient::DoClose(CefRefPtr<CefBrowser> browser)
{
	BOOL bRetVal = FALSE;
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		browser->AddRef();
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempBrowser;
			push ecx;
			call[edx + 0x14];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
	CefRefPtr<CefBrowserHost> pHost = browser->GetHost();
	HWND hWnd = pHost->GetWindowHandle();
	SetParent(hWnd, NULL);
	ShowWindow(hWnd, SW_HIDE);
	return bRetVal;
}

void ACFlibClient::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		browser->AddRef();
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempBrowser;
			push ecx;
			call[edx + 0x18];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
	this->RemoveItem(browser);
}

void ACFlibClient::OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
	bool isLoading,
	bool canGoBack,
	bool canGoForward)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
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
			call[edx + 0x1C];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
	}
};

void ACFlibClient::OnLoadStart(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	TransitionType transition_type)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
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
			call[edx + 0x20];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
	}
};

void ACFlibClient::OnLoadEnd(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	int httpStatusCode)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
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
			call[edx + 0x24];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
	}
};

void ACFlibClient::OnLoadError(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	ErrorCode errorCode,
	const CefString& errorText,
	const CefString& failedUrl)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
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
			call[edx + 0x28];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
	}
};

void ACFlibClient::OnAddressChange(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	const CefString& url)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);

		LPVOID url_str = UnicodeToEStream(url.c_str());
		LPVOID lpAddr1 = &url_str;

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
			push lpAddr1;
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
	}
}

void ACFlibClient::OnTitleChange(CefRefPtr<CefBrowser> browser,
	const CefString& title)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		LPVOID url_str = UnicodeToEStream(title.c_str());
		LPVOID lpAddr1 = &url_str;

		browser->AddRef();
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lpAddr1;
			push TempBrowser;
			push ecx;
			call[edx + 0x30];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
	}
}

void ACFlibClient::OnFaviconURLChange(CefRefPtr<CefBrowser> browser,
	const std::vector<CefString>& icon_urls)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		DWORD* pStrs = new DWORD[icon_urls.size()];
		USES_CONVERSION;
		for (size_t i = 0; i < icon_urls.size(); i++)
		{
			pStrs[i] = (DWORD)UnicodeToEStream(icon_urls[i].c_str());
		}

		int nSize = icon_urls.size() * sizeof(DWORD);
		LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
		*(LPINT)pAry = 1;
		*(LPINT)(pAry + sizeof(INT)) = icon_urls.size();
		memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
		delete[]pStrs;

		LPVOID pList = &pAry;

		browser->AddRef();
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push pList;
			push TempBrowser;
			push ecx;
			call[edx + 0x34];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
	}
}

void ACFlibClient::OnFullscreenModeChange(CefRefPtr<CefBrowser> browser,
	bool fullscreen)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
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
			movzx eax, fullscreen;
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

bool ACFlibClient::OnTooltip(CefRefPtr<CefBrowser> browser, CefString& text)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		LPVOID url_str = UnicodeToEStream(text.c_str());
		LPVOID lpAddr1 = &url_str;

		browser->AddRef();
		BOOL bRetVal = 0;
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lpAddr1;
			push TempBrowser;
			push ecx;
			call[edx + 0x3C];
			mov bRetVal, eax;
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		return bRetVal;
	}
	return false;
}

void ACFlibClient::OnStatusMessage(CefRefPtr<CefBrowser> browser,
	const CefString& value)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		LPVOID url_str = UnicodeToEStream(value.c_str());
		LPVOID lpAddr1 = &url_str;

		browser->AddRef();
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lpAddr1;
			push TempBrowser;
			push ecx;
			call[edx + 0x40];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
	}
}

bool ACFlibClient::OnConsoleMessage(CefRefPtr<CefBrowser> browser,
	cef_log_severity_t level,
	const CefString& message,
	const CefString& source,
	int line)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		LPVOID url_str1 = UnicodeToEStream(message.c_str());
		LPVOID url_str2 = UnicodeToEStream(source.c_str());
		LPVOID lpAddr1 = &url_str1, lpAddr2 = &url_str2;

		browser->AddRef();
		BOOL bRetVal = 0;
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push line;
			push lpAddr2;
			push lpAddr1;
			push level;
			push TempBrowser;
			push ecx;
			call[edx + 0x44];
			mov bRetVal, eax;
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		return bRetVal;
	}
	return false;
}

bool ACFlibClient::OnAutoResize(CefRefPtr<CefBrowser> browser,
	const CefSize& new_size)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		
		int width = new_size.width, height = new_size.height;

		browser->AddRef();
		BOOL bRetVal = 0;
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push height;
			push width;
			push TempBrowser;
			push ecx;
			call[edx + 0x48];
			mov bRetVal, eax;
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		return bRetVal;
	}
	return false;
}

void ACFlibClient::OnLoadingProgressChange(CefRefPtr<CefBrowser> browser,
	double progress)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		char* pLoingValue = (char*)&progress;
		DWORD dwValue1 = *(DWORD*)&pLoingValue[0];
		DWORD dwValue2 = *(DWORD*)&pLoingValue[4];

		browser->AddRef();
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
			push TempBrowser;
			push ecx;
			call[edx + 0x4C];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
	}
}

void ACFlibClient::OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefContextMenuParams> params,
	CefRefPtr<CefMenuModel> model)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempParams, params.get(), eClass::m_pVfMenuParams, acf_menu_params_funcs);
		IMP_NEWECLASS(TempModel, model.get(), eClass::m_pVfMenuTable, acf_menu_model_funcs);
		browser->AddRef();
		frame->AddRef();
		params->AddRef();
		model->AddRef();
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempModel;
			push TempParams;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x50];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
		params->Release();
		model->Release();
	}
}

bool ACFlibClient::RunContextMenu(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefContextMenuParams> params,
	CefRefPtr<CefMenuModel> model,
	CefRefPtr<CefRunContextMenuCallback> callback)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempParams, params.get(), eClass::m_pVfMenuParams, acf_menu_params_funcs);
		IMP_NEWECLASS(TempModel, model.get(), eClass::m_pVfMenuTable, acf_menu_model_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallbackMenu, acf_callback_run_menu);
		browser->AddRef();
		frame->AddRef();
		params->AddRef();
		model->AddRef();
		callback->AddRef();
		BOOL bRetVal = 0;
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempCallback;
			push TempModel;
			push TempParams;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x54];
			mov bRetVal, eax;
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
		params->Release();
		model->Release();
		callback->Release();
		return bRetVal;
	}
	return false;
}

bool ACFlibClient::OnContextMenuCommand(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefContextMenuParams> params,
	int command_id,
	EventFlags event_flags)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempParams, params.get(), eClass::m_pVfMenuParams, acf_menu_params_funcs);
		browser->AddRef();
		frame->AddRef();
		params->AddRef();
		BOOL bRetVal = FALSE;
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push event_flags;
			push command_id;
			push TempParams;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x58];
			mov bRetVal, eax;
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
		params->Release();
		return bRetVal;
	}
	return false;
}

void ACFlibClient::OnContextMenuDismissed(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
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
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x5C];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
	}
}

bool ACFlibClient::GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		browser->AddRef();
		
		cef_rect_t sRect = { rect.x, rect.y, rect.width, rect.height };

		LPVOID lpAddrStruct = &sRect;
		LPVOID lppAddrStruct = &lpAddrStruct;

		BOOL bRetVal = NULL;
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lppAddrStruct;
			push TempBrowser;
			push ecx;
			call[edx + 0x60];
			mov bRetVal, eax;
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();

		rect = CefRect(sRect);

		return bRetVal;
	}
	return false;
};

void ACFlibClient::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		browser->AddRef();

		cef_rect_t sRect = { rect.x, rect.y, rect.width, rect.height };

		LPVOID lpAddrStruct = &sRect;
		LPVOID lppAddrStruct = &lpAddrStruct;

		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lppAddrStruct;
			push TempBrowser;
			push ecx;
			call[edx + 0x64];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();

		rect = CefRect(sRect);
	}
};

bool ACFlibClient::GetScreenPoint(CefRefPtr<CefBrowser> browser,
	int viewX,
	int viewY,
	int& screenX,
	int& screenY)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		browser->AddRef();
		BOOL bRetVal = NULL;
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push screenY;
			push screenX;
			push viewY;
			push viewX;
			push TempBrowser;
			push ecx;
			call[edx + 0x68];
			mov bRetVal, eax;
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();

		return bRetVal;
	}
	return false;
};

bool ACFlibClient::GetScreenInfo(CefRefPtr<CefBrowser> browser,
	CefScreenInfo& screen_info)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		browser->AddRef();

		ACF_SCREEN_INFO tInfo;
		tInfo.device_scale_factor = 1.0;

		LPVOID lpAddrStruct = &tInfo;
		LPVOID lppAddrStruct = &lpAddrStruct;

		BOOL bRetVal = NULL;
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lppAddrStruct;
			push TempBrowser;
			push ecx;
			call[edx + 0x6C];
			mov bRetVal, eax;
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();

		screen_info.device_scale_factor = tInfo.device_scale_factor;
		screen_info.depth = tInfo.depth;
		screen_info.depth_per_component = tInfo.depth_per_component;
		screen_info.is_monochrome = tInfo.is_monochrome;
		screen_info.rect = {
			tInfo.rect_x, tInfo.rect_y,
			tInfo.rect_width, tInfo.rect_height
		};
		screen_info.available_rect = {
			tInfo.available_rect_x, tInfo.available_rect_y,
			tInfo.available_rect_width, tInfo.available_rect_height
		};

		return bRetVal;
	}
	return false;
};

void ACFlibClient::OnPopupShow(CefRefPtr<CefBrowser> browser, bool show)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
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
			movzx eax, show;
			push eax;
			push TempBrowser;
			push ecx;
			call[edx + 0x70];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
	}
};

void ACFlibClient::OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect) 
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		browser->AddRef();

		cef_rect_t sRect = { rect.x, rect.y, rect.width, rect.height };

		LPVOID lpAddrStruct = &sRect;
		LPVOID lppAddrStruct = &lpAddrStruct;

		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lppAddrStruct;
			push TempBrowser;
			push ecx;
			call[edx + 0x74];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
	}
};

void ACFlibClient::OnPaint(CefRefPtr<CefBrowser> browser,
	PaintElementType type,
	const RectList& dirtyRects,
	const void* buffer,
	int width,
	int height)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		browser->AddRef();

		DWORD* pStrs = new DWORD[dirtyRects.size()];
		for (size_t i = 0; i < dirtyRects.size(); i++)
		{
			pStrs[i] = (DWORD)new cef_rect_t(dirtyRects[i]);
		}

		int nSize = dirtyRects.size() * sizeof(DWORD);
		LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
		*(LPINT)pAry = 1;
		*(LPINT)(pAry + sizeof(INT)) = dirtyRects.size();
		memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
		delete[]pStrs;

		LPVOID pList = &pAry;

		int nType = type;

		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push height;
			push width;
			push buffer;
			push pList;
			push nType;
			push TempBrowser;
			push ecx;
			call[edx + 0x78];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
	}
};

void ACFlibClient::OnAcceleratedPaint(CefRefPtr<CefBrowser> browser,
	PaintElementType type,
	const RectList& dirtyRects,
	void* shared_handle)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		browser->AddRef();

		DWORD* pStrs = new DWORD[dirtyRects.size()];
		for (size_t i = 0; i < dirtyRects.size(); i++)
		{
			pStrs[i] = (DWORD)new cef_rect_t(dirtyRects[i]);
		}

		int nSize = dirtyRects.size() * sizeof(DWORD);
		LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
		*(LPINT)pAry = 1;
		*(LPINT)(pAry + sizeof(INT)) = dirtyRects.size();
		memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
		delete[]pStrs;

		LPVOID pList = &pAry;

		int nType = type;

		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push shared_handle;
			push pList;
			push nType;
			push TempBrowser;
			push ecx;
			call[edx + 0x7C];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
	}
};

bool ACFlibClient::OnCursorChange(CefRefPtr<CefBrowser> browser,
	CefCursorHandle cursor,
	cef_cursor_type_t type,
	const CefCursorInfo& custom_cursor_info)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		browser->AddRef();

		ACF_CURSOR_INFO sRect = {
			custom_cursor_info.hotspot.x,
			custom_cursor_info.hotspot.y,
			custom_cursor_info.image_scale_factor,
			(int64)custom_cursor_info.buffer,
			custom_cursor_info.size.width,
			custom_cursor_info.size.height,
		};

		LPVOID lpAddrStruct = &sRect;
		LPVOID lppAddrStruct = &lpAddrStruct;

		int nType = type;

		BOOL nRetVal = FALSE;
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lppAddrStruct;
			push nType;
			push cursor;
			push TempBrowser;
			push ecx;
			call[edx + 0x80];
			mov nRetVal, eax;
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		return nRetVal;
	}
	return false;
};

bool ACFlibClient::StartDragging(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefDragData> drag_data,
	CefDragHandler::DragOperationsMask allowed_ops,
	int x,
	int y)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempDrag, drag_data.get(), eClass::m_pVfDragDataTable, acf_drag_data_funcs);
		browser->AddRef();

		BOOL bRetVal = FALSE;
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push y;
			push x;
			push allowed_ops;
			push TempDrag;
			push TempBrowser;
			push ecx;
			call[edx + 0x84];
			mov bRetVal, eax;
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		return bRetVal;
	}
	return false;
};

void ACFlibClient::UpdateDragCursor(CefRefPtr<CefBrowser> browser,
	DragOperation operation)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		browser->AddRef();
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push operation;
			push TempBrowser;
			push ecx;
			call[edx + 0x88];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
};

void ACFlibClient::OnScrollOffsetChanged(CefRefPtr<CefBrowser> browser,
	double x,
	double y)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		browser->AddRef();
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		char* pLoingValue_x = (char*)&x;
		DWORD dwValue1_x = *(DWORD*)&pLoingValue_x[0];
		DWORD dwValue2_x = *(DWORD*)&pLoingValue_x[4];

		char* pLoingValue_y = (char*)&y;
		DWORD dwValue1_y = *(DWORD*)&pLoingValue_y[0];
		DWORD dwValue2_y = *(DWORD*)&pLoingValue_y[4];

		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push dwValue2_y;
			push dwValue1_y;
			push dwValue2_x;
			push dwValue1_x;
			push TempBrowser;
			push ecx;
			call[edx + 0x8C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
};

void ACFlibClient::OnImeCompositionRangeChanged(CefRefPtr<CefBrowser> browser,
	const CefRange& selected_range,
	const RectList& character_bounds)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		browser->AddRef();

		DWORD* pStrs = new DWORD[character_bounds.size()];
		for (size_t i = 0; i < character_bounds.size(); i++)
		{
			pStrs[i] = (DWORD)new cef_rect_t(character_bounds[i]);
		}

		int nSize = character_bounds.size() * sizeof(DWORD);
		LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
		*(LPINT)pAry = 1;
		*(LPINT)(pAry + sizeof(INT)) = character_bounds.size();
		memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
		delete[]pStrs;

		LPVOID pList = &pAry;

		cef_range_t range = selected_range;

		LPVOID pRange = &range;
		LPVOID ppRange = &pRange;

		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push pList;
			push ppRange;
			push TempBrowser;
			push ecx;
			call[edx + 0x90];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
	}
};

void ACFlibClient::OnTextSelectionChanged(CefRefPtr<CefBrowser> browser,
	const CefString& selected_text,
	const CefRange& selected_range)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		browser->AddRef();

		USES_CONVERSION;

		LPVOID text = UnicodeToEStream(selected_text.c_str());

		LPVOID pText = &text;

		cef_range_t range = selected_range;

		LPVOID pRange = &range;
		LPVOID ppRange = &pRange;

		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push ppRange;
			push pText;
			push TempBrowser;
			push ecx;
			call[edx + 0x94];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
	}
};

void ACFlibClient::OnVirtualKeyboardRequested(CefRefPtr<CefBrowser> browser,
	TextInputMode input_mode)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		browser->AddRef();
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push input_mode;
			push TempBrowser;
			push ecx;
			call[edx + 0x98];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
};

void ACFlibClient::OnBeforeDownload(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefDownloadItem> download_item,
	const CefString& suggested_name,
	CefRefPtr<CefBeforeDownloadCallback> callback)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		browser->AddRef();
		download_item->AddRef();
		callback->AddRef();
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempDownload, download_item.get(), eClass::m_pVfDownloadTable, acf_download_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallbackDownloadBefore, acf_callback_download_before);

		USES_CONVERSION;

		LPVOID name = UnicodeToEStream(suggested_name.c_str());

		LPVOID pName = &name;

		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempCallback;
			push pName;
			push TempDownload;
			push TempBrowser;
			push ecx;
			call[edx + 0x9C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		download_item->Release();
		callback->Release();
	}
}

void ACFlibClient::OnDownloadUpdated(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefDownloadItem> download_item,
	CefRefPtr<CefDownloadItemCallback> callback)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		browser->AddRef();
		download_item->AddRef();
		callback->AddRef();
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempDownload, download_item.get(), eClass::m_pVfDownloadTable, acf_download_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallbackDownload, acf_callback_download);

		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempCallback;
			push TempDownload;
			push TempBrowser;
			push ecx;
			call[edx + 0xA0];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		download_item->Release();
		callback->Release();
	}
}

bool ACFlibClient::OnDragEnter(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefDragData> dragData,
	CefDragHandler::DragOperationsMask mask)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		browser->AddRef();
		dragData->AddRef();
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempDrag, dragData.get(), eClass::m_pVfDragDataTable, acf_drag_data_funcs);

		BOOL bRetVal = FALSE;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push mask;
			push TempDrag;
			push TempBrowser;
			push ecx;
			call[edx + 0xA4];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		dragData->Release();
		return bRetVal;
	}
	return false;
}

void ACFlibClient::OnDraggableRegionsChanged(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	const std::vector<CefDraggableRegion>& regions)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);

		DWORD* pStrs = new DWORD[regions.size()];
		for (size_t i = 0; i < regions.size(); i++)
		{
			pStrs[i] = (DWORD)new ACF_DRAG_REGION;
			((PACF_DRAG_REGION)pStrs[i])->x = regions[i].bounds.x;
			((PACF_DRAG_REGION)pStrs[i])->y = regions[i].bounds.y;
			((PACF_DRAG_REGION)pStrs[i])->width = regions[i].bounds.width;
			((PACF_DRAG_REGION)pStrs[i])->height = regions[i].bounds.height;
			((PACF_DRAG_REGION)pStrs[i])->draggable = regions[i].draggable;
		}

		int nSize = regions.size() * sizeof(DWORD);
		LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
		*(LPINT)pAry = 1;
		*(LPINT)(pAry + sizeof(INT)) = regions.size();
		memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
		delete[]pStrs;

		LPVOID pList = &pAry;

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
			push pList;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0xA8];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
	}
}

void ACFlibClient::OnFindResult(CefRefPtr<CefBrowser> browser,
	int identifier,
	int count,
	const CefRect& selectionRect,
	int activeMatchOrdinal,
	bool finalUpdate)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		cef_rect_t obj_rect = selectionRect;

		LPVOID pRect = &obj_rect;
		LPVOID ppRect = &pRect;

		browser->AddRef();
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, finalUpdate;
			push eax;
			push activeMatchOrdinal;
			push ppRect;
			push count;
			push identifier;
			push TempBrowser;
			push ecx;
			call[edx + 0xAC];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
	}
}

bool ACFlibClient::OnJSDialog(CefRefPtr<CefBrowser> browser,
	const CefString& origin_url,
	JSDialogType dialog_type,
	const CefString& message_text,
	const CefString& default_prompt_text,
	CefRefPtr<CefJSDialogCallback> callback,
	bool& suppress_message)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallbackJSDialog, acf_callback_js_dialog);

		USES_CONVERSION;

		LPVOID pUrl = UnicodeToEStream(origin_url.c_str());
		LPVOID pMessage = UnicodeToEStream(message_text.c_str());
		LPVOID pText = UnicodeToEStream(default_prompt_text.c_str());
		LPVOID lpAddr1 = &pUrl;
		LPVOID lpAddr2 = &pMessage;
		LPVOID lpAddr3 = &pText;
		int nType = dialog_type;

		BOOL suppress = NULL;
		LPVOID lpSuppressMessage = &suppress;

		BOOL bRetVal = FALSE;
		browser->AddRef();
		callback->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lpSuppressMessage;
			push TempCallback;
			push lpAddr3;
			push lpAddr2;
			push nType;
			push lpAddr1;
			push TempBrowser;
			push ecx;
			call[edx + 0xB0];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		callback->Release();
		suppress_message = suppress;

		return bRetVal;
	}
	return false;
}

bool ACFlibClient::OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser,
	const CefString& message_text,
	bool is_reload,
	CefRefPtr<CefJSDialogCallback> callback)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		browser->AddRef();
		callback->AddRef();
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallbackJSDialog, acf_callback_js_dialog);

		USES_CONVERSION;

		LPVOID pMessage = UnicodeToEStream(message_text.c_str());
		LPVOID lpAddr1 = &pMessage;

		BOOL bRetVal = FALSE;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempCallback;
			movzx eax, is_reload;
			push eax;
			push lpAddr1;
			push TempBrowser;
			push ecx;
			call[edx + 0xB4];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		callback->Release();
		return bRetVal;
	}
	return false;
}

void ACFlibClient::OnResetDialogState(CefRefPtr<CefBrowser> browser)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		browser->AddRef();
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempBrowser;
			push ecx;
			call[edx + 0xB8];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

void ACFlibClient::OnDialogClosed(CefRefPtr<CefBrowser> browser)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		browser->AddRef();
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempBrowser;
			push ecx;
			call[edx + 0xBC];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

bool ACFlibClient::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefProcessId source_process,
	CefRefPtr<CefProcessMessage> message)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
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
			call[edx + 0xC0];
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

bool ACFlibClient::OnFileDialog(CefRefPtr<CefBrowser> browser,
	FileDialogMode mode,
	const CefString& title,
	const CefString& default_file_path,
	const std::vector<CefString>& accept_filters,
	CefRefPtr<CefFileDialogCallback> callback)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallbackDialog, acf_callback_dialog);

		USES_CONVERSION;

		LPVOID pTitle = UnicodeToEStream(title.c_str());
		LPVOID pPath = UnicodeToEStream(default_file_path.c_str());

		DWORD* pStrs = new DWORD[accept_filters.size()];
		USES_CONVERSION;
		for (size_t i = 0; i < accept_filters.size(); i++)
		{
			pStrs[i] = (DWORD)UnicodeToEStream(accept_filters[i].c_str());
		}

		int nSize = accept_filters.size() * sizeof(DWORD);
		LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
		*(LPINT)pAry = 1;
		*(LPINT)(pAry + sizeof(INT)) = accept_filters.size();
		memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
		delete[]pStrs;

		LPVOID pList = &pAry;
		LPVOID lpAddr1 = &pTitle;
		LPVOID lpAddr2 = &pPath;

		browser->AddRef();
		callback->AddRef();
		BOOL nRetVal = 0;
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempCallback;
			push pList;
			push lpAddr2;
			push lpAddr1;
			push mode;
			push TempBrowser;
			push ecx;
			call[edx + 0xC4];
			mov nRetVal, eax;
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		callback->Release();

		return nRetVal;
	}
	return false;
}

bool ACFlibClient::OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
	const CefKeyEvent& sEvent,
	CefEventHandle os_event,
	bool* is_keyboard_shortcut)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;
		browser->AddRef();
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		
		cef_key_event_t pEvent = sEvent;

		LPVOID ptrEvent = &pEvent;
		LPVOID lptrEvent = &ptrEvent;

		BOOL nRetVal = 0;
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push is_keyboard_shortcut;
			push os_event;
			push lptrEvent;
			push TempBrowser;
			push ecx;
			call[edx + 0xC8];
			mov nRetVal, eax;
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();

		return nRetVal;
	}
	return false;
}

bool ACFlibClient::OnKeyEvent(CefRefPtr<CefBrowser> browser,
	const CefKeyEvent& sEvent,
	CefEventHandle os_event)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		browser->AddRef();
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		cef_key_event_t pEvent = sEvent;

		LPVOID ptrEvent = &pEvent;
		LPVOID lptrEvent = &ptrEvent;

		BOOL nRetVal = 0;
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push os_event;
			push lptrEvent;
			push TempBrowser;
			push ecx;
			call[edx + 0xCC];
			mov nRetVal, eax;
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		return nRetVal;
	}
	return false;
}

bool ACFlibClient::OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request,
	bool user_gesture,
	bool is_redirect)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfRequestTable, acf_request_funcs);

		BOOL nRetVal = 0;
		browser->AddRef();
		frame->AddRef();
		request->AddRef();
		__asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, is_redirect;
			push eax;
			movzx eax, user_gesture;
			push eax;
			push TempRequest;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0xD0];
			mov nRetVal, eax;
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
		request->Release();
		return nRetVal;
	}
	return false;
}

bool ACFlibClient::OnOpenURLFromTab(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	const CefString& target_url,
	CefRequestHandler::WindowOpenDisposition target_disposition,
	bool user_gesture)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);

		USES_CONVERSION;

		LPVOID paTargetUrl = UnicodeToEStream(target_url.c_str());
		LPVOID lpTargetUrl = &paTargetUrl;

		BOOL nRetVal = 0;
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
			movzx eax, user_gesture;
			push eax;
			push target_disposition;
			push lpTargetUrl;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0xD4];
			mov nRetVal, eax;
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
		}
		browser->Release();
		frame->Release();
		return nRetVal;
	}
	return false;
}

CefRefPtr<CefResourceRequestHandler> ACFlibClient::GetResourceRequestHandler(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request,
	bool is_navigation,
	bool is_download,
	const CefString& request_initiator,
	bool& disable_default_handling)
{
	return this; // ACFlibClient Handler
}

bool ACFlibClient::GetAuthCredentials(CefRefPtr<CefBrowser> browser,
	const CefString& origin_url,
	bool isProxy,
	const CefString& host,
	int port,
	const CefString& realm,
	const CefString& scheme,
	CefRefPtr<CefAuthCallback> callback)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallbackAuth, acf_callback_auth);

		USES_CONVERSION;

		LPVOID paOriginUrl = UnicodeToEStream(origin_url.c_str());
		LPVOID paHost = UnicodeToEStream(host.c_str());
		LPVOID paRealm = UnicodeToEStream(realm.c_str());
		LPVOID paScheme = UnicodeToEStream(scheme.c_str());

		LPVOID lpOriginUrl = &paOriginUrl;
		LPVOID lpHostAddr = &paHost;
		LPVOID lpRealmAddr = &paRealm;
		LPVOID lpSchemeAddr = &paScheme;

		browser->AddRef();
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
			push lpSchemeAddr;
			push lpRealmAddr;
			push port;
			push lpHostAddr;
			movzx eax, isProxy;
			push eax;
			push lpOriginUrl;
			push TempBrowser;
			push ecx;
			call[edx + 0xD8];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		callback->Release();
		return bRetVal;
	}
	return false;
}

bool ACFlibClient::OnQuotaRequest(CefRefPtr<CefBrowser> browser,
	const CefString& origin_url,
	int64 new_size,
	CefRefPtr<CefCallback> callback)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallbackRequest, acf_callback_request);

		USES_CONVERSION;

		LPVOID paOriginUrl = UnicodeToEStream(origin_url.c_str());
		LPVOID lpOriginUrl = &paOriginUrl;

		char* pLoingValue = (char*)&new_size;
		DWORD dwValue1 = *(DWORD*)&pLoingValue[0];
		DWORD dwValue2 = *(DWORD*)&pLoingValue[4];

		browser->AddRef();
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
			push dwValue2;
			push dwValue1;
			push lpOriginUrl;
			push TempBrowser;
			push ecx;
			call[edx + 0xDC];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		callback->Release();
		return bRetVal;
	}
	return false;
}

bool ACFlibClient::OnCertificateError(CefRefPtr<CefBrowser> browser,
	cef_errorcode_t cert_error,
	const CefString& request_url,
	CefRefPtr<CefSSLInfo> ssl_info,
	CefRefPtr<CefCallback> callback)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempSSLInfo, ssl_info.get(), eClass::m_pVfSSLInfoTable, acf_ssl_info_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallbackRequest, acf_callback_request);

		USES_CONVERSION;

		LPVOID paUrl = UnicodeToEStream(request_url.c_str());
		LPVOID lpUrl = &paUrl;

		browser->AddRef();
		ssl_info->AddRef();
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
			push TempSSLInfo;
			push lpUrl;
			push cert_error;
			push TempBrowser;
			push ecx;
			call[edx + 0xE0];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		ssl_info->Release();
		callback->Release();
		return bRetVal;
	}
	return false;
}

bool ACFlibClient::OnSelectClientCertificate(
	CefRefPtr<CefBrowser> browser,
	bool isProxy,
	const CefString& host,
	int port,
	const X509CertificateList& certificates,
	CefRefPtr<CefSelectClientCertificateCallback> callback)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallbackCertificate, acf_callback_certificate);

		USES_CONVERSION;

		DWORD* pStrs = new DWORD[certificates.size()];
		for (size_t i = 0; i < certificates.size(); i++)
		{
			PECLASS_VFPTR pNewClass = new ECLASS_VFPTR;
			pNewClass->dwVfTable = eClass::m_pVfCertificateTable;
			pNewClass->pCFuncs = acf_certificate_funcs;
			pNewClass->pObject = ((LPVOID)(certificates[i].get()));

			pStrs[i] = (DWORD)pNewClass;
		}

		int nSize = certificates.size() * sizeof(DWORD);
		LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
		*(LPINT)pAry = 1;
		*(LPINT)(pAry + sizeof(INT)) = certificates.size();
		memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
		delete[]pStrs;

		LPVOID pList = &pAry;

		LPVOID paHost = UnicodeToEStream(host.c_str());
		LPVOID lpHost = &paHost;

		browser->AddRef();
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
			push pList;
			push port;
			push lpHost;
			movzx eax, isProxy;
			push eax;
			push TempBrowser;
			push ecx;
			call[edx + 0xE4];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		callback->Release();
		return bRetVal;
	}
	return false;
}

/* Discard E8: PluginCrash */

void ACFlibClient::OnRenderViewReady(CefRefPtr<CefBrowser> browser)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		browser->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempBrowser;
			push ecx;
			call[edx + 0xE8];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

void ACFlibClient::OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser,
	TerminationStatus status)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		browser->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push status;
			push TempBrowser;
			push ecx;
			call[edx + 0xEC];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

void ACFlibClient::OnDocumentAvailableInMainFrame(CefRefPtr<CefBrowser> browser)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		browser->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempBrowser;
			push ecx;
			call[edx + 0xF0];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

CefRefPtr<CefCookieAccessFilter> ACFlibClient::GetCookieAccessFilter(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request)
{
	return this; // ACFlibClient Handler
}

ACFlibClient::ReturnValue ACFlibClient::OnBeforeResourceLoad(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request,
	CefRefPtr<CefCallback> callback)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfRequestTable, acf_request_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallbackRequest, acf_callback_request);

		int	nRetVal = NULL;
		browser->AddRef();
		frame->AddRef();
		request->AddRef();
		callback->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempCallback;
			push TempRequest;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0xF4];
			mov nRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		frame->Release();
		request->Release();
		callback->Release();
		return (ReturnValue)nRetVal;
	}
	return RV_CONTINUE;
}

void ACFlibClient::OnResourceRedirect(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request,
	CefRefPtr<CefResponse> response,
	CefString& new_url)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfRequestTable, acf_request_funcs);
		IMP_NEWECLASS(TempResponse, response.get(), eClass::m_pVfResponseTable, acf_response_funcs);

		USES_CONVERSION;
		LPVOID paUrl = UnicodeToEStream(new_url.c_str());
		LPVOID lpUrlAddr = &paUrl;

		browser->AddRef();
		frame->AddRef();
		request->AddRef();
		response->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lpUrlAddr;
			push TempResponse;
			push TempRequest;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0xF8];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		frame->Release();
		request->Release();
		response->Release();
	}
}

bool ACFlibClient::OnResourceResponse(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request,
	CefRefPtr<CefResponse> response)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfRequestTable, acf_request_funcs);
		IMP_NEWECLASS(TempResponse, response.get(), eClass::m_pVfResponseTable, acf_response_funcs);

		BOOL bRetVal = NULL;
		browser->AddRef();
		frame->AddRef();
		request->AddRef();
		response->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempResponse;
			push TempRequest;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0xFC];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		frame->Release();
		request->Release();
		response->Release();
		return bRetVal;
	}
	return false;
}

CefRefPtr<CefResponseFilter> ACFlibClient::GetResourceResponseFilter(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request,
	CefRefPtr<CefResponse> response)
{
	CefRefPtr<ACFlibResourceFilter> lpHandler = nullptr;

	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfRequestTable, acf_request_funcs);
		IMP_NEWECLASS(TempResponse, response.get(), eClass::m_pVfResponseTable, acf_response_funcs);

		BOOL bRetVal = NULL;
		browser->AddRef();
		frame->AddRef();
		request->AddRef();
		response->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempResponse;
			push TempRequest;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x100];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		frame->Release();
		request->Release();
		response->Release();

		if (bRetVal)
			lpHandler = new ACFlibResourceFilter(this->m_pClientCallback, browser, request->GetURL(), response->GetMimeType());
	}
	
	return lpHandler;
}

// OnResourceFilterReady
// Offset: 0x104
// CefBrowser browser
// const CefString& url
// const CefString& mime_type
// ACFResourceFilter filter

void ACFlibClient::OnResourceLoadComplete(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request,
	CefRefPtr<CefResponse> response,
	URLRequestStatus status,
	int64 received_content_length)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfRequestTable, acf_request_funcs);
		IMP_NEWECLASS(TempResponse, response.get(), eClass::m_pVfResponseTable, acf_response_funcs);

		char* pLoingValue = (char*)&received_content_length;
		DWORD dwValue1 = *(DWORD*)&pLoingValue[0];
		DWORD dwValue2 = *(DWORD*)&pLoingValue[4];

		browser->AddRef();
		frame->AddRef();
		request->AddRef();
		response->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push dwValue2;
			push dwValue1;
			push status;
			push TempResponse;
			push TempRequest;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x108];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		frame->Release();
		request->Release();
		response->Release();
	}
}

void ACFlibClient::OnProtocolExecution(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request,
	bool& allow_os_execution)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfRequestTable, acf_request_funcs);

		BOOL os_execute = NULL;
		LPVOID lpExecute = &os_execute;

		browser->AddRef();
		frame->AddRef();
		request->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lpExecute;
			push TempRequest;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x10C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		frame->Release();
		request->Release();

		allow_os_execution = os_execute;
	}
}

static PACF_COOKIE transfer_cookie_data(const CefCookie& cookie)
{
	PACF_COOKIE pCookie = new ACF_COOKIE;

	USES_CONVERSION;

	pCookie->name = (LPBYTE)UnicodeToEStream(cookie.name.str);
	pCookie->value = (LPBYTE)UnicodeToEStream(cookie.value.str);
	pCookie->domain = (LPBYTE)UnicodeToEStream(cookie.domain.str);
	pCookie->path = (LPBYTE)UnicodeToEStream(cookie.path.str);

	pCookie->secure = cookie.secure;
	pCookie->httponly = cookie.httponly;

	pCookie->has_expires = cookie.has_expires;
	pCookie->same_site = cookie.same_site;
	pCookie->priority = cookie.priority;

	pCookie->creation = new cef_time_t();
	cef_time_from_basetime(cookie.creation, pCookie->creation);
	pCookie->last_access = new cef_time_t();
	cef_time_from_basetime(cookie.last_access, pCookie->last_access);
	pCookie->expires = new cef_time_t();
	cef_time_from_basetime(cookie.expires, pCookie->expires);

	return pCookie;
}

bool ACFlibClient::CanSendCookie(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request,
	const CefCookie& cookie)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfRequestTable, acf_request_funcs);

		LPVOID pCookie = transfer_cookie_data(cookie);
		LPVOID lppCookie = &pCookie;

		BOOL bRetVal = NULL;
		browser->AddRef();
		frame->AddRef();
		request->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lppCookie;
			push TempRequest;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x110];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		frame->Release();
		request->Release();
		return bRetVal;
	}
	return false;
}

bool ACFlibClient::CanSaveCookie(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request,
	CefRefPtr<CefResponse> response,
	const CefCookie& cookie)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfRequestTable, acf_request_funcs);

		LPVOID pCookie = transfer_cookie_data(cookie);
		LPVOID lppCookie = &pCookie;

		BOOL bRetVal = NULL;
		browser->AddRef();
		frame->AddRef();
		request->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lppCookie;
			push TempRequest;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x114];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		frame->Release();
		request->Release();
		return bRetVal;
	}
	return false;
}

void ACFlibClient::OnTakeFocus(CefRefPtr<CefBrowser> browser, bool next)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		browser->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, next;
			push eax;
			push TempBrowser;
			push ecx;
			call[edx + 0x118];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

bool ACFlibClient::OnSetFocus(CefRefPtr<CefBrowser> browser, FocusSource source)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		BOOL bRetVal = NULL;
		browser->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push source;
			push TempBrowser;
			push ecx;
			call[edx + 0x11C];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		return bRetVal;
	}
	return false;
}

void ACFlibClient::OnGotFocus(CefRefPtr<CefBrowser> browser)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		browser->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempBrowser;
			push ecx;
			call[edx + 0x120];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

void ACFlibClient::OnMouseLockRequest(CefRefPtr<CefBrowser> browser, bool is_lost)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		browser->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, is_lost;
			push eax;
			push TempBrowser;
			push ecx;
			call[edx + 0x124];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

void ACFlibClient::OnKeyboardLockRequest(CefRefPtr<CefBrowser> browser, bool is_lost)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		browser->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, is_lost;
			push eax;
			push TempBrowser;
			push ecx;
			call[edx + 0x128];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

bool ACFlibClient::GetAudioParameters(CefRefPtr<CefBrowser> browser,
	CefAudioParameters& params)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		cef_audio_parameters_t pParam = { (cef_channel_layout_t)0, 0, 0 };

		LPVOID lpParam = &pParam;
		LPVOID lppParam = &lpParam;

		BOOL bRetVal = NULL;
		browser->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lppParam;
			push TempBrowser;
			push ecx;
			call[edx + 0x12C];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		params = CefAudioParameters(pParam);

		return bRetVal;
	}
	return false;
}

void ACFlibClient::OnAudioStreamStarted(CefRefPtr<CefBrowser> browser,
	const CefAudioParameters& params,
	int channels)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		cef_audio_parameters_t pParam = params;

		LPVOID lpParam = &pParam;
		LPVOID lppParam = &lpParam;

		browser->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push channels;
			push lppParam;
			push TempBrowser;
			push ecx;
			call[edx + 0x130];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

void ACFlibClient::OnAudioStreamPacket(CefRefPtr<CefBrowser> browser,
	const float** data,
	int frames,
	int64 pts)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		char* pLoingValue = (char*)&pts;
		DWORD dwValue1 = *(DWORD*)&pLoingValue[0];
		DWORD dwValue2 = *(DWORD*)&pLoingValue[4];

		browser->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push dwValue2;
			push dwValue1;
			push frames;
			push data;
			push TempBrowser;
			push ecx;
			call[edx + 0x134];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

void ACFlibClient::OnAudioStreamStopped(CefRefPtr<CefBrowser> browser)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		browser->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempBrowser;
			push ecx;
			call[edx + 0x138];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

void ACFlibClient::OnAudioStreamError(CefRefPtr<CefBrowser> browser,
	const CefString& message)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		USES_CONVERSION;

		LPVOID lpMsg = UnicodeToEStream(message.c_str());
		LPVOID lpMsgAddr = &lpMsg;

		browser->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lpMsgAddr;
			push TempBrowser;
			push ecx;
			call[edx + 0x13C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

void ACFlibClient::OnAudioStateChange(CefRefPtr<CefBrowser> browser,
	bool audible)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		browser->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, audible;
			push eax;
			push TempBrowser;
			push ecx;
			call[edx + 0x140];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

CefRefPtr<CefResourceHandler> ACFlibClient::GetResourceHandler(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request)
{
	CefRefPtr<ACFlibResourceHandler> lpHandler = nullptr;

	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfRequestTable, acf_request_funcs);

		browser->AddRef();
		frame->AddRef();
		request->AddRef();
		BOOL bRetVal = FALSE;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempRequest;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x144];
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
			lpHandler = new ACFlibResourceHandler(browser, frame, m_pClientCallback);
	}
	return lpHandler;
}

bool ACFlibClient::OnRequestMediaAccessPermission(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	const CefString& requesting_origin,
	uint32 requested_permissions,
	CefRefPtr<CefMediaAccessCallback> callback)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfFrameTable, acf_frame_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallbackPermissionMedia, acf_callback_permissionmedia);

		USES_CONVERSION;

		LPVOID pOrigin = UnicodeToEStream(requesting_origin.c_str());
		LPVOID lpOrigin = &pOrigin;

		browser->AddRef();
		frame->AddRef();
		callback->AddRef();

		BOOL bRetVal = FALSE;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempCallback;
			push requested_permissions;
			push lpOrigin;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x15C];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		frame->Release();
		callback->Release();

		return bRetVal;
	}
	return false;
}

bool ACFlibClient::OnShowPermissionPrompt(
	CefRefPtr<CefBrowser> browser,
	uint64 prompt_id,
	const CefString& requesting_origin,
	uint32 requested_permissions,
	CefRefPtr<CefPermissionPromptCallback> callback)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallbackPermission, acf_callback_permission);

		USES_CONVERSION;

		LPVOID pOrigin = UnicodeToEStream(requesting_origin.c_str());
		LPVOID lpOrigin = &pOrigin;

		char* pLoingValue = (char*)&prompt_id;
		DWORD dwValue1 = *(DWORD*)&pLoingValue[0];
		DWORD dwValue2 = *(DWORD*)&pLoingValue[4];

		browser->AddRef();
		callback->AddRef();

		BOOL bRetVal = FALSE;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempCallback;
			push requested_permissions;
			push lpOrigin;
			push dwValue2;
			push dwValue1;
			push TempBrowser;
			push ecx;
			call[edx + 0x160];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
		callback->Release();

		return bRetVal;
	}
	return false;
}

void ACFlibClient::OnDismissPermissionPrompt(
	CefRefPtr<CefBrowser> browser,
	uint64 prompt_id,
	cef_permission_request_result_t result)
{
	if (this->m_pClientCallback != NULL)
	{
		LPVOID pClass = this->m_pClientCallback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		USES_CONVERSION;

		char* pLoingValue = (char*)&prompt_id;
		DWORD dwValue1 = *(DWORD*)&pLoingValue[0];
		DWORD dwValue2 = *(DWORD*)&pLoingValue[4];

		int nResult = result;

		browser->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push nResult;
			push dwValue2;
			push dwValue1;
			push TempBrowser;
			push ecx;
			call[edx + 0x164];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}
