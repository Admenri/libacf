
#include "acf_FrameEvents.h"
#include "acf_Conv.h"
#include "acf_Class.h"
#include "acf_Client.h"

ACFlibStringVisitor::ACFlibStringVisitor(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibStringVisitor::~ACFlibStringVisitor() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

void ACFlibStringVisitor::Visit(const CefString& string)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		USES_CONVERSION;

		LPVOID tempString = UnicodeToEStream(string.c_str());

		LPVOID lpAddr1 = &tempString;

		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lpAddr1;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
	}
}

ACFlibDOMVisitor::ACFlibDOMVisitor(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibDOMVisitor::~ACFlibDOMVisitor() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

void ACFlibDOMVisitor::Visit(CefRefPtr<CefDOMDocument> document)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempDocument, document.get(), eClass::m_pVfDOMDocumentTable, acf_dom_document_funcs);

		document->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempDocument;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		document->Release();
	}
}

ACFlibMenuModelDelegate::ACFlibMenuModelDelegate(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibMenuModelDelegate::~ACFlibMenuModelDelegate() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

void ACFlibMenuModelDelegate::ExecuteCommand(CefRefPtr<CefMenuModel> menu_model,
	int command_id,
	cef_event_flags_t event_flags)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;
		IMP_NEWECLASS(TempMenuModel, menu_model.get(), eClass::m_pVfMenuTable, acf_menu_model_funcs);
		menu_model->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push event_flags;
			push command_id;
			push TempMenuModel;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		menu_model->Release();
	}
}

void ACFlibMenuModelDelegate::MouseOutsideMenu(CefRefPtr<CefMenuModel> menu_model,
	const CefPoint& screen_point)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;
		IMP_NEWECLASS(TempMenuModel, menu_model.get(), eClass::m_pVfMenuTable, acf_menu_model_funcs);

		cef_point_t sPt = { screen_point.x, screen_point.y };

		LPVOID lpPt = &sPt;
		LPVOID lppPt = &lpPt;

		menu_model->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lppPt;
			push TempMenuModel;
			push ecx;
			call[edx + 0x0C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		menu_model->Release();
	}
}

void ACFlibMenuModelDelegate::UnhandledOpenSubmenu(CefRefPtr<CefMenuModel> menu_model,
	bool is_rtl)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;
		IMP_NEWECLASS(TempMenuModel, menu_model.get(), eClass::m_pVfMenuTable, acf_menu_model_funcs);
		menu_model->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, is_rtl;
			push eax;
			push TempMenuModel;
			push ecx;
			call[edx + 0x10];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		menu_model->Release();
	}
}

void ACFlibMenuModelDelegate::UnhandledCloseSubmenu(CefRefPtr<CefMenuModel> menu_model,
	bool is_rtl)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;
		IMP_NEWECLASS(TempMenuModel, menu_model.get(), eClass::m_pVfMenuTable, acf_menu_model_funcs);

		menu_model->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, is_rtl;
			push eax;
			push TempMenuModel;
			push ecx;
			call[edx + 0x14];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		menu_model->Release();
	}
}

void ACFlibMenuModelDelegate::MenuWillShow(CefRefPtr<CefMenuModel> menu_model)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;
		IMP_NEWECLASS(TempMenuModel, menu_model.get(), eClass::m_pVfMenuTable, acf_menu_model_funcs);

		menu_model->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempMenuModel;
			push ecx;
			call[edx + 0x18];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		menu_model->Release();
	}
}

void ACFlibMenuModelDelegate::MenuClosed(CefRefPtr<CefMenuModel> menu_model)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;
		IMP_NEWECLASS(TempMenuModel, menu_model.get(), eClass::m_pVfMenuTable, acf_menu_model_funcs);

		menu_model->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempMenuModel;
			push ecx;
			call[edx + 0x1C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		menu_model->Release();
	}
}

bool ACFlibMenuModelDelegate::FormatLabel(CefRefPtr<CefMenuModel> menu_model,
	CefString& label)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;
		IMP_NEWECLASS(TempMenuModel, menu_model.get(), eClass::m_pVfMenuTable, acf_menu_model_funcs);

		USES_CONVERSION;

		LPVOID sStr = UnicodeToEStream(label.c_str());

		LPVOID lpStr = &sStr;

		menu_model->AddRef();
		BOOL bRetVal = NULL;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lpStr;
			push TempMenuModel;
			push ecx;
			call[edx + 0x20];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		menu_model->Release();
		return bRetVal;
	}
	return false;
}

ACFlibV8Accessor::ACFlibV8Accessor(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibV8Accessor::~ACFlibV8Accessor() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

bool ACFlibV8Accessor::Get(const CefString& name,
	const CefRefPtr<CefV8Value> object,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		ACFV8RetValCallback* callback = new ACFV8RetValCallback();

		IMP_NEWECLASS(TempObject, object.get(), eClass::m_pVfV8ValueTable, acf_v8_value_funcs);
		IMP_NEWECLASS(TempCallback, callback, eClass::m_pVfCallbackV8RetVal, acf_callback_v8retval);

		USES_CONVERSION;

		LPVOID sStr = UnicodeToEStream(name.c_str());
		LPVOID lpStr = &sStr;

		LPSTR lpBuffer = new char[4096];
		ZeroMemory(lpBuffer, 4096);

		object->AddRef();
		BOOL bRetVal = NULL;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lpBuffer;
			push TempCallback;
			push TempObject;
			push lpStr;
			push ecx;
			call[edx + 0x08];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		object->Release();

		retval = callback->GetValue();

		if (lpBuffer && *lpBuffer != '\0')
			exception = lpBuffer;
		delete[]lpBuffer;

		delete callback;

		return bRetVal;
	}
	return false;
};

bool ACFlibV8Accessor::Set(const CefString& name,
	const CefRefPtr<CefV8Value> object,
	const CefRefPtr<CefV8Value> value,
	CefString& exception)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;
		IMP_NEWECLASS(TempObject, object.get(), eClass::m_pVfV8ValueTable, acf_v8_value_funcs);
		IMP_NEWECLASS(TempValue, value.get(), eClass::m_pVfV8ValueTable, acf_v8_value_funcs);

		USES_CONVERSION;

		LPVOID sStr = UnicodeToEStream(name.c_str());
		LPVOID lpStr = &sStr;

		LPSTR lpBuffer = new char[4096];
		ZeroMemory(lpBuffer, 4096);

		object->AddRef();
		value->AddRef();
		BOOL bRetVal = NULL;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lpBuffer;
			push TempValue;
			push TempObject;
			push lpStr;
			push ecx;
			call[edx + 0x0C];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		object->Release();
		value->Release();

		if (lpBuffer && *lpBuffer != '\0')
			exception = lpBuffer;

		delete[]lpBuffer;

		return bRetVal;
	}
	return false;
};

ACFlibV8Interceptor::ACFlibV8Interceptor(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibV8Interceptor::~ACFlibV8Interceptor() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

bool ACFlibV8Interceptor::Get(const CefString& name,
	const CefRefPtr<CefV8Value> object,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		ACFV8RetValCallback* callback = new ACFV8RetValCallback();

		IMP_NEWECLASS(TempObject, object.get(), eClass::m_pVfV8ValueTable, acf_v8_value_funcs);
		IMP_NEWECLASS(TempCallback, callback, eClass::m_pVfCallbackV8RetVal, acf_callback_v8retval);

		USES_CONVERSION;

		LPVOID sStr = UnicodeToEStream(name.c_str());
		LPVOID lpStr = &sStr;

		LPSTR lpBuffer = new char[4096];
		ZeroMemory(lpBuffer, 4096);

		object->AddRef();
		BOOL bRetVal = NULL;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lpBuffer;
			push TempCallback;
			push TempObject;
			push lpStr;
			push ecx;
			call[edx + 0x08];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		object->Release();

		retval = callback->GetValue();

		if (lpBuffer && *lpBuffer != '\0')
			exception = lpBuffer;
		delete[]lpBuffer;

		delete callback;

		return bRetVal;
	}
	return false;
}

bool ACFlibV8Interceptor::Get(int index,
	const CefRefPtr<CefV8Value> object,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		ACFV8RetValCallback* callback = new ACFV8RetValCallback();

		IMP_NEWECLASS(TempObject, object.get(), eClass::m_pVfV8ValueTable, acf_v8_value_funcs);
		IMP_NEWECLASS(TempCallback, callback, eClass::m_pVfCallbackV8RetVal, acf_callback_v8retval);

		LPSTR lpBuffer = new char[4096];
		ZeroMemory(lpBuffer, 4096);

		object->AddRef();
		BOOL bRetVal = NULL;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lpBuffer;
			push TempCallback;
			push TempObject;
			push index;
			push ecx;
			call[edx + 0x0C];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		object->Release();

		retval = callback->GetValue();

		if (lpBuffer && *lpBuffer != '\0')
			exception = lpBuffer;
		delete[]lpBuffer;

		delete callback;

		return bRetVal;
	}
	return false;
}

bool ACFlibV8Interceptor::Set(const CefString& name,
	const CefRefPtr<CefV8Value> object,
	const CefRefPtr<CefV8Value> value,
	CefString& exception)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;
		IMP_NEWECLASS(TempObject, object.get(), eClass::m_pVfV8ValueTable, acf_v8_value_funcs);
		IMP_NEWECLASS(TempValue, value.get(), eClass::m_pVfV8ValueTable, acf_v8_value_funcs);

		USES_CONVERSION;

		LPVOID sStr = UnicodeToEStream(name.c_str());
		LPVOID lpStr = &sStr;

		LPSTR lpBuffer = new char[4096];
		ZeroMemory(lpBuffer, 4096);

		object->AddRef();
		value->AddRef();
		BOOL bRetVal = NULL;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lpBuffer;
			push TempValue;
			push TempObject;
			push lpStr;
			push ecx;
			call[edx + 0x10];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		object->Release();
		value->Release();

		if (lpBuffer && *lpBuffer != '\0')
			exception = lpBuffer;

		delete[]lpBuffer;

		return bRetVal;
	}
	return false;
}

bool ACFlibV8Interceptor::Set(int index,
	const CefRefPtr<CefV8Value> object,
	const CefRefPtr<CefV8Value> value,
	CefString& exception)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;
		IMP_NEWECLASS(TempObject, object.get(), eClass::m_pVfV8ValueTable, acf_v8_value_funcs);
		IMP_NEWECLASS(TempValue, value.get(), eClass::m_pVfV8ValueTable, acf_v8_value_funcs);

		LPSTR lpBuffer = new char[4096];
		ZeroMemory(lpBuffer, 4096);

		object->AddRef();
		value->AddRef();
		BOOL bRetVal = NULL;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lpBuffer;
			push TempValue;
			push TempObject;
			push index;
			push ecx;
			call[edx + 0x14];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		object->Release();
		value->Release();

		if (lpBuffer && *lpBuffer != '\0')
			exception = lpBuffer;

		delete[]lpBuffer;

		return bRetVal;
	}
	return false;
}

ACFlibV8ArrayBufferReleaseCallback::ACFlibV8ArrayBufferReleaseCallback(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibV8ArrayBufferReleaseCallback::~ACFlibV8ArrayBufferReleaseCallback() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

void ACFlibV8ArrayBufferReleaseCallback::ReleaseBuffer(void* buffer)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push buffer;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
	}
}

ACFlibV8Handler::ACFlibV8Handler(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibV8Handler::~ACFlibV8Handler() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

bool ACFlibV8Handler::Execute(const CefString& name,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList& arguments,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		ACFV8RetValCallback* callback = new ACFV8RetValCallback();

		IMP_NEWECLASS(TempObject, object.get(), eClass::m_pVfV8ValueTable, acf_v8_value_funcs);
		IMP_NEWECLASS(TempCallback, callback, eClass::m_pVfCallbackV8RetVal, acf_callback_v8retval);

		USES_CONVERSION;

		LPVOID lpszName = UnicodeToEStream(name.c_str());
		LPVOID lpAddr = &lpszName;

		LPSTR lpBuffer = new char[4096];
		ZeroMemory(lpBuffer, 4096);

		DWORD* pStrs = new DWORD[arguments.size()];
		for (size_t i = 0; i < arguments.size(); i++)
		{
			PECLASS_VFPTR pNewClass = new ECLASS_VFPTR;
			pNewClass->dwVfTable = eClass::m_pVfV8ValueTable;
			pNewClass->pCFuncs = acf_v8_value_funcs;
			pNewClass->pObject = ((LPVOID)(arguments[i].get()));

			pStrs[i] = (DWORD)pNewClass;
		}

		int nSize = arguments.size() * sizeof(DWORD);
		LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
		*(LPINT)pAry = 1;
		*(LPINT)(pAry + sizeof(INT)) = arguments.size();
		memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
		delete[]pStrs;

		LPVOID pList = &pAry;

		object->AddRef();
		BOOL bRetVal = NULL;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lpBuffer;
			push TempCallback;
			push pList;
			push TempObject;
			push lpAddr;
			push ecx;
			call[edx + 0x08];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		object->Release();

		retval = callback->GetValue();

		if (lpBuffer && *lpBuffer != '\0')
			exception = lpBuffer;

		delete[]lpBuffer;

		delete callback;

		return bRetVal;
	}
	return false;
}

ACFlibRequestContextHandler::ACFlibRequestContextHandler(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibRequestContextHandler::~ACFlibRequestContextHandler() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

void ACFlibRequestContextHandler::OnRequestContextInitialized(
	CefRefPtr<CefRequestContext> request_context)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;
		IMP_NEWECLASS(TempContext, request_context.get(), eClass::m_pVfRequestContextTable, acf_request_context_funcs);

		request_context->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempContext;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		request_context->Release();
	}
}

//bool ACFlibRequestContextHandler::OnBeforePluginLoad(const CefString& mime_type,
//	const CefString& plugin_url,
//	bool is_main_frame,
//	const CefString& top_origin_url,
//	CefRefPtr<CefWebPluginInfo> plugin_info,
//	PluginPolicy* plugin_policy)
//{
//	if (this->m_callback != NULL)
//	{
//		LPVOID pClass = this->m_callback;
//		
//		USES_CONVERSION;
//
//		PACF_WEB_PLUGIN_INFO pInfo = new ACF_WEB_PLUGIN_INFO;
//		pInfo->name = (LPBYTE)UnicodeToEStream(plugin_info->GetName().c_str());
//		pInfo->path = (LPBYTE)UnicodeToEStream(plugin_info->GetPath().c_str());
//		pInfo->version = (LPBYTE)UnicodeToEStream(plugin_info->GetVersion().c_str());
//		pInfo->description = (LPBYTE)UnicodeToEStream(plugin_info->GetDescription().c_str());
//
//		LPVOID sMimeType = UnicodeToEStream(mime_type.c_str());
//		LPVOID sPluginUrl = UnicodeToEStream(plugin_url.c_str());
//		LPVOID sTopOriUrl = UnicodeToEStream(top_origin_url.c_str());
//
//		LPVOID pStruct = &pInfo;
//		LPVOID lpTempAddr1 = &sMimeType;
//		LPVOID lpTempAddr2 = &sPluginUrl;
//		LPVOID lpTempAddr3 = &sTopOriUrl;
//
//		BOOL bRetVal = NULL;
//		__asm {
//			push ecx;
//			push ebx;
//			push edi;
//			push esi;
//			mov ebx, pClass;
//			mov edx, [ebx];
//			lea ecx, pClass;
//			push plugin_policy;
//			push pStruct;
//			push lpTempAddr3;
//			movzx eax, is_main_frame;
//			push eax;
//			push lpTempAddr2;
//			push lpTempAddr1;
//			push ecx;
//			call[edx + 0x0C];
//			mov bRetVal, eax;
//			pop esi;
//			pop edi;
//			pop ebx;
//			pop ecx;
//		}
//		return bRetVal;
//	}
//	return false;
//}

CefRefPtr<CefResourceRequestHandler> ACFlibRequestContextHandler::GetResourceRequestHandler(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request,
	bool is_navigation,
	bool is_download,
	const CefString& request_initiator,
	bool& disable_default_handling)
{
	return nullptr;
}

ACFlibCompletionCallback::ACFlibCompletionCallback(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibCompletionCallback::~ACFlibCompletionCallback() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

void ACFlibCompletionCallback::OnComplete()
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
	}
}

PACF_COOKIE transfer_cookie_data(const CefCookie& cookie)
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

ACFlibCookieVisitor::ACFlibCookieVisitor(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibCookieVisitor::~ACFlibCookieVisitor() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

bool ACFlibCookieVisitor::Visit(const CefCookie& cookie,
	int count,
	int total,
	bool& deleteCookie)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;
		BOOL delCookie = NULL;

		LPVOID pCookie = transfer_cookie_data(cookie);
		LPVOID lppCookie = &pCookie;
		LPVOID pDelCookie = &delCookie;

		BOOL bRetVal = NULL;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push pDelCookie;
			push total;
			push count;
			push lppCookie;
			push ecx;
			call[edx + 0x08];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		deleteCookie = delCookie;
		return bRetVal;
	}
	return false;
}

ACFlibResolveCallback::ACFlibResolveCallback(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibResolveCallback::~ACFlibResolveCallback() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

void ACFlibResolveCallback::OnResolveCompleted(
	cef_errorcode_t result,
	const std::vector<CefString>& resolved_ips)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		DWORD* pStrs = new DWORD[resolved_ips.size()];
		USES_CONVERSION;
		for (size_t i = 0; i < resolved_ips.size(); i++)
		{
			pStrs[i] = (DWORD)UnicodeToEStream(resolved_ips[i].c_str());
		}

		int nSize = resolved_ips.size() * sizeof(DWORD);
		LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
		*(LPINT)pAry = 1;
		*(LPINT)(pAry + sizeof(INT)) = resolved_ips.size();
		memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
		delete[]pStrs;

		LPVOID pList = &pAry;

		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push pList;
			push result;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
	}
}

ACFlibRunFileDialogCallback::ACFlibRunFileDialogCallback(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibRunFileDialogCallback::~ACFlibRunFileDialogCallback() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

void ACFlibRunFileDialogCallback::OnFileDialogDismissed(
	const std::vector<CefString>& file_paths)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		DWORD* pStrs = new DWORD[file_paths.size()];
		USES_CONVERSION;
		for (size_t i = 0; i < file_paths.size(); i++)
		{
			pStrs[i] = (DWORD)UnicodeToEStream(file_paths[i].c_str());
		}

		int nSize = file_paths.size() * sizeof(DWORD);
		LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
		*(LPINT)pAry = 1;
		*(LPINT)(pAry + sizeof(INT)) = file_paths.size();
		memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
		delete[]pStrs;

		LPVOID pList = &pAry;

		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push pList;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
	}
}

ACFlibDownloadImageCallback::ACFlibDownloadImageCallback(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibDownloadImageCallback::~ACFlibDownloadImageCallback() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

void ACFlibDownloadImageCallback::OnDownloadImageFinished(const CefString& image_url,
	int http_status_code,
	CefRefPtr<CefImage> image)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempImage, image.get(), eClass::m_pVfImageTable, acf_image_funcs);

		USES_CONVERSION;

		LPVOID lpUrl = UnicodeToEStream(image_url.c_str());

		LPVOID lppUrl = &lpUrl;

		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempImage;
			push http_status_code;
			push lppUrl;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
	}
}

ACFlibPdfPrintCallback::ACFlibPdfPrintCallback(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibPdfPrintCallback::~ACFlibPdfPrintCallback() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

void ACFlibPdfPrintCallback::OnPdfPrintFinished(const CefString& path, bool ok)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		USES_CONVERSION;

		LPVOID lpUrl = UnicodeToEStream(path.c_str());

		LPVOID lppUrl = &lpUrl;

		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, ok;
			push eax;
			push lppUrl;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
	}
}

ACFlibURLRequestClient::ACFlibURLRequestClient(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibURLRequestClient::~ACFlibURLRequestClient() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

void ACFlibURLRequestClient::OnRequestComplete(CefRefPtr<CefURLRequest> request)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfURLRequestTable, acf_url_request_funcs);

		request->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempRequest;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		request->Release();
	}
}

void ACFlibURLRequestClient::OnUploadProgress(CefRefPtr<CefURLRequest> request,
	int64 current,
	int64 total)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfURLRequestTable, acf_url_request_funcs);

		char* pLoingValue1 = (char*)&current;
		DWORD dwValue1_1 = *(DWORD*)&pLoingValue1[0];
		DWORD dwValue2_1 = *(DWORD*)&pLoingValue1[4];

		char* pLoingValue2 = (char*)&total;
		DWORD dwValue1_2 = *(DWORD*)&pLoingValue2[0];
		DWORD dwValue2_2 = *(DWORD*)&pLoingValue2[4];

		request->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push dwValue2_2;
			push dwValue1_2;
			push dwValue2_1;
			push dwValue1_1;
			push TempRequest;
			push ecx;
			call[edx + 0x0C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		request->Release();
	}
}

void ACFlibURLRequestClient::OnDownloadProgress(CefRefPtr<CefURLRequest> request,
	int64 current,
	int64 total)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfURLRequestTable, acf_url_request_funcs);

		char* pLoingValue1 = (char*)&current;
		DWORD dwValue1_1 = *(DWORD*)&pLoingValue1[0];
		DWORD dwValue2_1 = *(DWORD*)&pLoingValue1[4];

		char* pLoingValue2 = (char*)&total;
		DWORD dwValue1_2 = *(DWORD*)&pLoingValue2[0];
		DWORD dwValue2_2 = *(DWORD*)&pLoingValue2[4];

		request->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push dwValue2_2;
			push dwValue1_2;
			push dwValue2_1;
			push dwValue1_1;
			push TempRequest;
			push ecx;
			call[edx + 0x10];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		request->Release();
	}
}

void ACFlibURLRequestClient::OnDownloadData(CefRefPtr<CefURLRequest> request,
	const void* data,
	size_t data_length)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfURLRequestTable, acf_url_request_funcs);

		request->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push data_length;
			push data;
			push TempRequest;
			push ecx;
			call[edx + 0x14];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		request->Release();
	}
}

bool ACFlibURLRequestClient::GetAuthCredentials(bool isProxy,
	const CefString& host,
	int port,
	const CefString& realm,
	const CefString& scheme,
	CefRefPtr<CefAuthCallback> callback)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallbackAuth, acf_callback_auth);

		USES_CONVERSION;

		LPVOID paHost = UnicodeToEStream(host.c_str());
		LPVOID paRealm = UnicodeToEStream(realm.c_str());
		LPVOID paScheme = UnicodeToEStream(scheme.c_str());

		LPVOID lpHostAddr = &paHost;
		LPVOID lpRealmAddr = &paRealm;
		LPVOID lpSchemeAddr = &paScheme;

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
			push ecx;
			call[edx + 0x18];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		callback->Release();
		return bRetVal;
	}
	return false;
}

ACFlibDevToolsMessageObserver::ACFlibDevToolsMessageObserver(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibDevToolsMessageObserver::~ACFlibDevToolsMessageObserver() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

bool ACFlibDevToolsMessageObserver::OnDevToolsMessage(CefRefPtr<CefBrowser> browser,
	const void* message,
	size_t message_size)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		browser->AddRef();
		BOOL bRetVal = NULL;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push message_size;
			push message;
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
	return false;
}

void ACFlibDevToolsMessageObserver::OnDevToolsMethodResult(CefRefPtr<CefBrowser> browser,
	int message_id,
	bool success,
	const void* result,
	size_t result_size)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

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
			push result_size;
			push result;
			movzx eax, success;
			push eax;
			push message_id;
			push TempBrowser;
			push ecx;
			call[edx + 0x0C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

void ACFlibDevToolsMessageObserver::OnDevToolsEvent(CefRefPtr<CefBrowser> browser,
	const CefString& method,
	const void* params,
	size_t params_size)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		USES_CONVERSION;

		LPVOID paMethod = UnicodeToEStream(method.c_str());
		LPVOID lpMethod = &paMethod;

		browser->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push params_size;
			push params;
			push lpMethod;
			push TempBrowser;
			push ecx;
			call[edx + 0x10];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

void ACFlibDevToolsMessageObserver::OnDevToolsAgentAttached(CefRefPtr<CefBrowser> browser)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

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
			call[edx + 0x14];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

void ACFlibDevToolsMessageObserver::OnDevToolsAgentDetached(CefRefPtr<CefBrowser> browser)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

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
			call[edx + 0x18];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser->Release();
	}
}

ACFV8RetValCallback::ACFV8RetValCallback() : _value(0) {}

ACFV8RetValCallback::~ACFV8RetValCallback() {}

void ACFV8RetValCallback::SetValue(CefV8Value* ret_val)
{
	if (!ret_val)
		return;

	ret_val->AddRef();

	_value = ret_val;
}

CefV8Value* ACFV8RetValCallback::GetValue()
{
	return _value;
}

extern DWORD acf_callback_v8retval[];

void ECALL v8retval_setretval(ACFV8RetValCallback* obj, CefV8Value* retval)
{
	ISVALID(obj);

	retval->AddRef();

	obj->SetValue(retval);
}

DWORD acf_callback_v8retval[] = {
	(DWORD)&v8retval_setretval,
};

ACFOnPopupRetCallback::ACFOnPopupRetCallback() : _value(0) {}

ACFOnPopupRetCallback::~ACFOnPopupRetCallback() {}

void ACFOnPopupRetCallback::SetValue(CefDictionaryValue* ret_val)
{
	if (!ret_val)
		return;

	ret_val->AddRef();

	_value = ret_val;
}

CefDictionaryValue* ACFOnPopupRetCallback::GetValue()
{
	return _value;
}

void ECALL popupdic_setretval(ACFOnPopupRetCallback* obj, CefDictionaryValue* retval)
{
	ISVALID(obj);

	retval->AddRef();

	obj->SetValue(retval);
}

DWORD acf_callback_onpopup[] = {
	(DWORD)&popupdic_setretval,
};

ACFlibNavigationEntryVisitor::ACFlibNavigationEntryVisitor(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibNavigationEntryVisitor::~ACFlibNavigationEntryVisitor() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

bool ACFlibNavigationEntryVisitor::Visit(CefRefPtr<CefNavigationEntry> entry,
	bool current,
	int index,
	int total)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempEntry, entry.get(), eClass::m_pVfNavigationEntryTable, acf_navigation_entry_funcs);

		entry->AddRef();
		BOOL bRetVal = FALSE;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push total;
			push index;
			movzx eax, current;
			push eax;
			push TempEntry;
			push ecx;
			call[edx + 0x08];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		entry->Release();
		return bRetVal;
	}
	return false;
}

ACFlibExtensionHandler::ACFlibExtensionHandler(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibExtensionHandler::~ACFlibExtensionHandler() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

void ACFlibExtensionHandler::OnExtensionLoadFailed(cef_errorcode_t result)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push result;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
	}
}

void ACFlibExtensionHandler::OnExtensionLoaded(CefRefPtr<CefExtension> extension)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempExtension, extension.get(), eClass::m_pVfExtensionTable, acf_extension_funcs);

		extension->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempExtension;
			push ecx;
			call[edx + 0x0C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		extension->Release();
	}
}

void ACFlibExtensionHandler::OnExtensionUnloaded(CefRefPtr<CefExtension> extension)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempExtension, extension.get(), eClass::m_pVfExtensionTable, acf_extension_funcs);

		extension->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempExtension;
			push ecx;
			call[edx + 0x10];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		extension->Release();
	}
}

bool ACFlibExtensionHandler::OnBeforeBackgroundBrowser(CefRefPtr<CefExtension> extension,
	const CefString& url,
	CefRefPtr<CefClient>& client,
	CefBrowserSettings& settings)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempExtension, extension.get(), eClass::m_pVfExtensionTable, acf_extension_funcs);

		IMP_NEWECLASS2(TempSettings, &settings, eClass::m_settingsTable);

		LPVOID lpUrlAddress = UnicodeToEStream(url.c_str());
		LPVOID lpAddress1 = &lpUrlAddress;

		DWORD pClient = 0;
		LPVOID pClientPtr = &pClient;

		extension->AddRef();
		BOOL bRetVal = FALSE;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempSettings;
			push pClientPtr;
			push lpAddress1;
			push TempExtension;
			push ecx;
			call[edx + 0x14];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		extension->Release();

		if (pClient >= 0)
			client = (CefClient*)pClient;

		return bRetVal;
	}
	return false;
}

bool ACFlibExtensionHandler::OnBeforeBrowser(CefRefPtr<CefExtension> extension,
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefBrowser> active_browser,
	int index,
	const CefString& url,
	bool active,
	CefWindowInfo& windowInfo,
	CefRefPtr<CefClient>& client,
	CefBrowserSettings& settings)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempExtension, extension.get(), eClass::m_pVfExtensionTable, acf_extension_funcs);
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempActiveBrowser, active_browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		IMP_NEWECLASS2(TempInfo, &windowInfo, eClass::m_infoTable);
		IMP_NEWECLASS2(TempSettings, &settings, eClass::m_settingsTable);

		LPVOID lpUrlAddress = UnicodeToEStream(url.c_str());
		LPVOID lpAddress1 = &lpUrlAddress;

		DWORD pClient = 0;
		LPVOID pClientPtr = &pClient;

		extension->AddRef();
		browser->AddRef();
		active_browser->AddRef();
		BOOL bRetVal = FALSE;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempSettings;
			push pClientPtr;
			push TempInfo;
			movzx eax, active;
			push eax;
			push lpAddress1;
			push index;
			push TempActiveBrowser;
			push TempBrowser;
			push TempExtension;
			push ecx;
			call[edx + 0x18];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		extension->Release();
		browser->Release();
		active_browser->Release();

		if (pClient >= 0)
			client = (CefClient*)pClient;

		return bRetVal;
	}
	return false;
}

CefRefPtr<CefBrowser> ACFlibExtensionHandler::GetActiveBrowser(
	CefRefPtr<CefExtension> extension,
	CefRefPtr<CefBrowser> browser,
	bool include_incognito)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempExtension, extension.get(), eClass::m_pVfExtensionTable, acf_extension_funcs);
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		extension->AddRef();
		browser->AddRef();
		ECLASS_VFPTR* bRetVal = FALSE;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, include_incognito;
			push eax;
			push TempBrowser;
			push TempExtension;
			push ecx;
			call[edx + 0x1C];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		extension->Release();
		browser->Release();

		if (bRetVal && bRetVal->pObject)
			return (CefBrowser*)bRetVal->pObject;
	}
	return nullptr;
}

bool ACFlibExtensionHandler::CanAccessBrowser(CefRefPtr<CefExtension> extension,
	CefRefPtr<CefBrowser> browser,
	bool include_incognito,
	CefRefPtr<CefBrowser> target_browser)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempExtension, extension.get(), eClass::m_pVfExtensionTable, acf_extension_funcs);
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempTargetBrowser, target_browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		extension->AddRef();
		browser->AddRef();
		target_browser->AddRef();
		BOOL bRetVal = FALSE;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempTargetBrowser;
			movzx eax, include_incognito;
			push eax;
			push TempBrowser;
			push TempExtension;
			push ecx;
			call[edx + 0x20];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		extension->Release();
		browser->Release();
		target_browser->Release();

		return bRetVal;
	}
	return false;
}

bool ACFlibExtensionHandler::GetExtensionResource(
	CefRefPtr<CefExtension> extension,
	CefRefPtr<CefBrowser> browser,
	const CefString& file,
	CefRefPtr<CefGetExtensionResourceCallback> callback)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempExtension, extension.get(), eClass::m_pVfExtensionTable, acf_extension_funcs);
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallbackExtensionResource, acf_callback_extension_resource);

		LPVOID lpUrlAddress = UnicodeToEStream(file.c_str());
		LPVOID lpAddress1 = &lpUrlAddress;

		extension->AddRef();
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
			push lpAddress1;
			push TempBrowser;
			push TempExtension;
			push ecx;
			call[edx + 0x24];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		extension->Release();
		browser->Release();
		callback->Release();

		return bRetVal;
	}
	return false;
}

ACFlibServerHandler::ACFlibServerHandler(LPVOID lpCallback, BOOL copyData) : m_callback(lpCallback), m_copyData(copyData) {}

ACFlibServerHandler::~ACFlibServerHandler() { if (this->m_callback && this->m_copyData) LocalFree(this->m_callback); }

void ACFlibServerHandler::OnServerCreated(CefRefPtr<CefServer> server)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempServer, server.get(), eClass::m_pVfServerTable, acf_server_funcs);

		server->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempServer;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		server->Release();
	}
}

void ACFlibServerHandler::OnServerDestroyed(CefRefPtr<CefServer> server)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempServer, server.get(), eClass::m_pVfServerTable, acf_server_funcs);

		server->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempServer;
			push ecx;
			call[edx + 0x0C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		server->Release();
	}
}

void ACFlibServerHandler::OnClientConnected(CefRefPtr<CefServer> server,
	int connection_id)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempServer, server.get(), eClass::m_pVfServerTable, acf_server_funcs);

		server->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push connection_id;
			push TempServer;
			push ecx;
			call[edx + 0x10];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		server->Release();
	}
}

void ACFlibServerHandler::OnClientDisconnected(CefRefPtr<CefServer> server,
	int connection_id)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempServer, server.get(), eClass::m_pVfServerTable, acf_server_funcs);

		server->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push connection_id;
			push TempServer;
			push ecx;
			call[edx + 0x14];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		server->Release();
	}
}

void ACFlibServerHandler::OnHttpRequest(CefRefPtr<CefServer> server,
	int connection_id,
	const CefString& client_address,
	CefRefPtr<CefRequest> request)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempServer, server.get(), eClass::m_pVfServerTable, acf_server_funcs);
		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfRequestTable, acf_request_funcs);

		LPVOID lpAddress = UnicodeToEStream(client_address.c_str());
		LPVOID lpTempAddress1 = &lpAddress;

		server->AddRef();
		request->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempRequest;
			push lpTempAddress1;
			push connection_id;
			push TempServer;
			push ecx;
			call[edx + 0x18];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		server->Release();
		request->Release();
	}
}

void ACFlibServerHandler::OnWebSocketRequest(CefRefPtr<CefServer> server,
	int connection_id,
	const CefString& client_address,
	CefRefPtr<CefRequest> request,
	CefRefPtr<CefCallback> callback)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempServer, server.get(), eClass::m_pVfServerTable, acf_server_funcs);
		IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfRequestTable, acf_request_funcs);
		IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfCallback, acf_callback);

		LPVOID lpAddress = UnicodeToEStream(client_address.c_str());
		LPVOID lpTempAddress1 = &lpAddress;

		server->AddRef();
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
			push lpTempAddress1;
			push connection_id;
			push TempServer;
			push ecx;
			call[edx + 0x1C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		server->Release();
		request->Release();
		callback->Release();
	}
}

void ACFlibServerHandler::OnWebSocketConnected(CefRefPtr<CefServer> server,
	int connection_id)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempServer, server.get(), eClass::m_pVfServerTable, acf_server_funcs);

		server->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push connection_id;
			push TempServer;
			push ecx;
			call[edx + 0x20];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		server->Release();
	}
}

void ACFlibServerHandler::OnWebSocketMessage(CefRefPtr<CefServer> server,
	int connection_id,
	const void* data,
	size_t data_size)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempServer, server.get(), eClass::m_pVfServerTable, acf_server_funcs);

		server->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push data_size;
			push data;
			push connection_id;
			push TempServer;
			push ecx;
			call[edx + 0x24];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		server->Release();
	}
}

ACFlibWindowDelegate::~ACFlibWindowDelegate()
{
	if (this->m_callback && this->m_copy)
		LocalFree(this->m_callback);
}

void ACFlibWindowDelegate::OnWindowCreated(CefRefPtr<CefWindow> window)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempWindow, window.get(), eClass::m_pVfWindowTable, acf_window_funcs);

		window->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempWindow;
			push ecx;
			call[edx + 0x8];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		window->Release();
	}
}

void ACFlibWindowDelegate::OnWindowDestroyed(CefRefPtr<CefWindow> window)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempWindow, window.get(), eClass::m_pVfWindowTable, acf_window_funcs);

		window->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempWindow;
			push ecx;
			call[edx + 0xC];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		window->Release();
	}
}

void ACFlibWindowDelegate::OnWindowActivationChanged(CefRefPtr<CefWindow> window,
	bool active)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempWindow, window.get(), eClass::m_pVfWindowTable, acf_window_funcs);

		window->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, active;
			push eax;
			push TempWindow;
			push ecx;
			call[edx + 0x10];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		window->Release();
	}
}

CefRefPtr<CefWindow> ACFlibWindowDelegate::GetParentWindow(CefRefPtr<CefWindow> window,
	bool* is_menu,
	bool* can_activate_menu)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempWindow, window.get(), eClass::m_pVfWindowTable, acf_window_funcs);

		ECLASS_VFPTR* bRetVal = FALSE;

		window->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push can_activate_menu;
			push is_menu;
			push TempWindow;
			push ecx;
			call[edx + 0x14];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		window->Release();
		if (bRetVal && bRetVal->pObject)
			return static_cast<CefWindow*>(bRetVal->pObject);
	}
	return nullptr;
}

CefRect ACFlibWindowDelegate::GetInitialBounds(CefRefPtr<CefWindow> window)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempWindow, window.get(), eClass::m_pVfWindowTable, acf_window_funcs);

		cef_rect_t* rt = new cef_rect_t();

		LPVOID pRect = &rt;

		window->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push pRect;
			push TempWindow;
			push ecx;
			call[edx + 0x18];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		window->Release();

		CefRect rtObj(*rt);

		delete rt;

		return rtObj;
	}
	return CefRect();
}

cef_show_state_t ACFlibWindowDelegate::GetInitialShowState(CefRefPtr<CefWindow> window)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempWindow, window.get(), eClass::m_pVfWindowTable, acf_window_funcs);

		int nRetVal = 0;
		window->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempWindow;
			push ecx;
			call[edx + 0x1C];
			mov nRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		window->Release();
		return static_cast<cef_show_state_t>(nRetVal);
	}
	return cef_show_state_t();
}

bool ACFlibWindowDelegate::IsFrameless(CefRefPtr<CefWindow> window)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempWindow, window.get(), eClass::m_pVfWindowTable, acf_window_funcs);

		int nRetVal = 0;
		window->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempWindow;
			push ecx;
			call[edx + 0x20];
			mov nRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		window->Release();
		return nRetVal;
	}
	return FALSE;
}

bool ACFlibWindowDelegate::CanResize(CefRefPtr<CefWindow> window)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempWindow, window.get(), eClass::m_pVfWindowTable, acf_window_funcs);

		int nRetVal = 0;
		window->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempWindow;
			push ecx;
			call[edx + 0x24];
			mov nRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		window->Release();
		return nRetVal;
	}
	return FALSE;
}

bool ACFlibWindowDelegate::CanMaximize(CefRefPtr<CefWindow> window)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempWindow, window.get(), eClass::m_pVfWindowTable, acf_window_funcs);

		int nRetVal = 0;
		window->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempWindow;
			push ecx;
			call[edx + 0x28];
			mov nRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		window->Release();
		return nRetVal;
	}
	return FALSE;
}

bool ACFlibWindowDelegate::CanMinimize(CefRefPtr<CefWindow> window)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempWindow, window.get(), eClass::m_pVfWindowTable, acf_window_funcs);

		int nRetVal = 0;
		window->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempWindow;
			push ecx;
			call[edx + 0x2C];
			mov nRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		window->Release();
		return nRetVal;
	}
	return FALSE;
}

bool ACFlibWindowDelegate::CanClose(CefRefPtr<CefWindow> window)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempWindow, window.get(), eClass::m_pVfWindowTable, acf_window_funcs);

		int nRetVal = 0;
		window->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempWindow;
			push ecx;
			call[edx + 0x30];
			mov nRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		window->Release();
		return nRetVal;
	}
	return FALSE;
}

bool ACFlibWindowDelegate::OnAccelerator(CefRefPtr<CefWindow> window, int command_id)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempWindow, window.get(), eClass::m_pVfWindowTable, acf_window_funcs);

		int nRetVal = 0;
		window->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push command_id;
			push TempWindow;
			push ecx;
			call[edx + 0x34];
			mov nRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		window->Release();
		return nRetVal;
	}
	return FALSE;
}

bool ACFlibWindowDelegate::OnKeyEvent(CefRefPtr<CefWindow> window,
	const CefKeyEvent& sEvent)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempWindow, window.get(), eClass::m_pVfWindowTable, acf_window_funcs);

		cef_key_event_t pEvent = sEvent;

		LPVOID ptrEvent = &pEvent;
		LPVOID lptrEvent = &ptrEvent;

		int nRetVal = 0;
		window->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lptrEvent;
			push TempWindow;
			push ecx;
			call[edx + 0x38];
			mov nRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		window->Release();
		return nRetVal;
	}
	return FALSE;
}

ACFlibPanelDelegate::~ACFlibPanelDelegate()
{
	if (this->m_callback && this->m_copy)
		LocalFree(this->m_callback);
}

CefSize ACFlibPanelDelegate::GetPreferredSize(CefRefPtr<CefView> view)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempView, view.get(), eClass::m_pVfViewTable, acf_view_funcs);

		cef_size_t* rt = new cef_size_t();

		LPVOID pRect = &rt;

		view->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push pRect;
			push TempView;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		view->Release();

		CefSize rtObj(*rt);

		delete rt;

		return rtObj;
	}
	return CefSize();
}

CefSize ACFlibPanelDelegate::GetMinimumSize(CefRefPtr<CefView> view)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempView, view.get(), eClass::m_pVfViewTable, acf_view_funcs);

		cef_size_t* rt = new cef_size_t();

		LPVOID pRect = &rt;

		view->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push pRect;
			push TempView;
			push ecx;
			call[edx + 0x0C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		view->Release();

		CefSize rtObj(*rt);

		delete rt;

		return rtObj;
	}
	return CefSize();
}

CefSize ACFlibPanelDelegate::GetMaximumSize(CefRefPtr<CefView> view)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempView, view.get(), eClass::m_pVfViewTable, acf_view_funcs);

		cef_size_t* rt = new cef_size_t();

		LPVOID pRect = &rt;

		view->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push pRect;
			push TempView;
			push ecx;
			call[edx + 0x10];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		view->Release();

		CefSize rtObj(*rt);

		delete rt;

		return rtObj;
	}
	return CefSize();
}

int ACFlibPanelDelegate::GetHeightForWidth(CefRefPtr<CefView> view, int width)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempView, view.get(), eClass::m_pVfViewTable, acf_view_funcs);

		int nRetVal = 0;

		view->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push width;
			push TempView;
			push ecx;
			call[edx + 0x14];
			mov nRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		view->Release();

		return nRetVal;
	}
	return 0;
}

void ACFlibPanelDelegate::OnParentViewChanged(CefRefPtr<CefView> view,
	bool added,
	CefRefPtr<CefView> parent)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempView, view.get(), eClass::m_pVfViewTable, acf_view_funcs);
		IMP_NEWECLASS(TempParent, parent.get(), eClass::m_pVfViewTable, acf_view_funcs);

		view->AddRef();
		parent->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempParent;
			movzx eax, added;
			push eax;
			push TempView;
			push ecx;
			call[edx + 0x18];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		view->Release();
		parent->Release();
	}
}

void ACFlibPanelDelegate::OnChildViewChanged(CefRefPtr<CefView> view,
	bool added,
	CefRefPtr<CefView> child)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempView, view.get(), eClass::m_pVfViewTable, acf_view_funcs);
		IMP_NEWECLASS(TempParent, child.get(), eClass::m_pVfViewTable, acf_view_funcs);

		view->AddRef();
		child->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempParent;
			movzx eax, added;
			push eax;
			push TempView;
			push ecx;
			call[edx + 0x1C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		view->Release();
		child->Release();
	}
}

void ACFlibPanelDelegate::OnWindowChanged(CefRefPtr<CefView> view, bool added)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempView, view.get(), eClass::m_pVfViewTable, acf_view_funcs);

		view->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, added;
			push eax;
			push TempView;
			push ecx;
			call[edx + 0x20];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		view->Release();
	}
}

void ACFlibPanelDelegate::OnLayoutChanged(CefRefPtr<CefView> view,
	const CefRect& new_bounds)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempView, view.get(), eClass::m_pVfViewTable, acf_view_funcs);

		cef_rect_t pEvent = new_bounds;

		LPVOID ptrEvent = &pEvent;
		LPVOID lptrEvent = &ptrEvent;

		view->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push lptrEvent;
			push TempView;
			push ecx;
			call[edx + 0x24];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		view->Release();
	}
}

void ACFlibPanelDelegate::OnFocus(CefRefPtr<CefView> view)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempView, view.get(), eClass::m_pVfViewTable, acf_view_funcs);

		view->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempView;
			push ecx;
			call[edx + 0x28];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		view->Release();
	}
}

void ACFlibPanelDelegate::OnBlur(CefRefPtr<CefView> view)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempView, view.get(), eClass::m_pVfViewTable, acf_view_funcs);

		view->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempView;
			push ecx;
			call[edx + 0x2C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		view->Release();
	}
}

ACFlibBrowserViewDelegate::~ACFlibBrowserViewDelegate()
{
	if (this->m_callback && this->m_copy)
		LocalFree(this->m_callback);
}

void ACFlibBrowserViewDelegate::OnBrowserCreated(CefRefPtr<CefBrowserView> browser_view,
	CefRefPtr<CefBrowser> browser)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempView, browser_view.get(), eClass::m_pVfBrowserViewTable, acf_browser_view_funcs);
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		browser_view->AddRef();
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
			push TempView;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser_view->Release();
		browser->Release();
	}
}

void ACFlibBrowserViewDelegate::OnBrowserDestroyed(CefRefPtr<CefBrowserView> browser_view,
	CefRefPtr<CefBrowser> browser)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempView, browser_view.get(), eClass::m_pVfBrowserViewTable, acf_browser_view_funcs);
		IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);

		browser_view->AddRef();
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
			push TempView;
			push ecx;
			call[edx + 0x0C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser_view->Release();
		browser->Release();
	}
}

CefRefPtr<CefBrowserViewDelegate> ACFlibBrowserViewDelegate::GetDelegateForPopupBrowserView(
	CefRefPtr<CefBrowserView> browser_view,
	const CefBrowserSettings& settings,
	CefRefPtr<CefClient> client,
	bool is_devtools)
{
	return this;
}

bool ACFlibBrowserViewDelegate::OnPopupBrowserViewCreated(
	CefRefPtr<CefBrowserView> browser_view,
	CefRefPtr<CefBrowserView> popup_browser_view,
	bool is_devtools)
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		IMP_NEWECLASS(TempView, browser_view.get(), eClass::m_pVfBrowserViewTable, acf_browser_view_funcs);
		IMP_NEWECLASS(TempBrowser, popup_browser_view.get(), eClass::m_pVfBrowserViewTable, acf_browser_view_funcs);

		BOOL bRetVal = FALSE;
		browser_view->AddRef();
		popup_browser_view->AddRef();
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, is_devtools;
			push eax;
			push TempBrowser;
			push TempView;
			push ecx;
			call[edx + 0x10];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		browser_view->Release();
		popup_browser_view->Release();
		return bRetVal;
	}
	return NULL;
}

ACFlibBrowserViewDelegate::ChromeToolbarType ACFlibBrowserViewDelegate::GetChromeToolbarType()
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;

		int nRetVal = 0;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push ecx;
			call[edx + 0x14];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
		return static_cast<ChromeToolbarType>(nRetVal);
	}
	return ChromeToolbarType();
}
