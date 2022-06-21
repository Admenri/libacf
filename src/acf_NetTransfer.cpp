
#include "acf_Types.h"
#include "acf_Conv.h"
#include "acf_Class.h"
#include "acf_FrameEvents.h"

#include "include/cef_request.h"
#include "include/cef_response.h"
#include "include/cef_urlrequest.h"

extern DWORD acf_response_funcs[];
extern DWORD acf_url_request_funcs[];
extern DWORD acf_post_data_funcs[];
extern DWORD acf_post_element_funcs[];

ACF_EXPORTS(ResponseCreate, BOOL)(DWORD* target)
{
	CefRefPtr<CefResponse> lpObj = CefResponse::Create();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_response_funcs;

	return !!lpObj;
}

BOOL ECALL response_is_read_only(CefResponse* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsReadOnly();
}

int ECALL response_get_error(CefResponse* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetError();
}

void ECALL response_set_error(CefResponse* obj, cef_errorcode_t error)
{
	ISVALID(obj);

	obj->SetError(error);
}

int ECALL response_get_status(CefResponse* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetStatus();
}

void ECALL response_set_status(CefResponse* obj, int status)
{
	ISVALID(obj);

	obj->SetStatus(status);
}

BOOL ECALL response_get_status_text(CefResponse* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	*str = (DWORD)UnicodeToEStream(obj->GetStatusText().c_str());

	return str != NULL;
}

void ECALL response_set_status_text(CefResponse* obj, LPCWSTR status)
{
	ISVALID(obj);

	obj->SetStatusText(status);
}

BOOL ECALL response_get_mime_type(CefResponse* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	*str = (DWORD)UnicodeToEStream(obj->GetMimeType().c_str());

	return str != NULL;
}

void ECALL response_set_mime_type(CefResponse* obj, LPCWSTR status)
{
	ISVALID(obj);

	obj->SetMimeType(status);
}

BOOL ECALL response_get_charset(CefResponse* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	*str = (DWORD)UnicodeToEStream(obj->GetCharset().c_str());

	return str != NULL;
}

void ECALL response_set_charset(CefResponse* obj, LPCWSTR status)
{
	ISVALID(obj);

	obj->SetCharset(status);
}

BOOL ECALL response_get_header_by_name(CefResponse* obj, LPCWSTR name, DWORD* str)
{
	ISVALIDR(obj, NULL);

	*str = (DWORD)UnicodeToEStream(obj->GetHeaderByName(name).c_str());

	return str != NULL;
}

void ECALL response_set_header_by_name(CefResponse* obj, LPCWSTR name, LPCWSTR value, BOOL overwrite)
{
	ISVALID(obj);

	obj->SetHeaderByName(name, value, overwrite);
}

BOOL ECALL response_get_header_map(CefResponse* obj, LPVOID* eArray)
{
	ISVALIDR(obj, NULL);

	std::multimap<CefString, CefString> keys;
	obj->GetHeaderMap(keys);

	DWORD* pStrs = new DWORD[keys.size()];
	USES_CONVERSION;
	int index = 0;
	for (auto iter = keys.begin(); iter != keys.end(); iter++)
	{
		pStrs[index] = (DWORD)new ACF_STRING_PAIR;
		((PACF_STRING_PAIR)pStrs[index])->key = (LPBYTE)UnicodeToEStream((*iter).first.c_str());
		((PACF_STRING_PAIR)pStrs[index])->value = (LPBYTE)UnicodeToEStream((*iter).second.c_str());
		++index;
	}

	FreeAryElement(*eArray);

	int nSize = keys.size() * sizeof(DWORD);
	LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
	*(LPINT)pAry = 1;
	*(LPINT)(pAry + sizeof(INT)) = keys.size();
	memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
	delete[]pStrs;

	*eArray = pAry;

	return eArray != NULL;
}

void ECALL response_set_header_map(CefResponse* obj, LPVOID* eArray)
{
	ISVALID(obj);

	std::multimap<CefString, CefString> keys;

	LPSTR pAry = (LPSTR)*eArray;

	int nSize = *(LPINT)(pAry + sizeof(INT));

	PACF_STRING_PAIR* pPair = (PACF_STRING_PAIR*)(pAry + sizeof(INT) * 2);

	for (size_t i = 0; i < nSize; i++)
	{
		LPWSTR tmpKey = EStreamToUnicode(pPair[i]->key);
		LPWSTR tmpValue = EStreamToUnicode(pPair[i]->value);

		keys.insert(std::make_pair(tmpKey ? tmpKey : std::wstring(), tmpValue ? tmpValue : std::wstring()));
	}

	obj->SetHeaderMap(keys);
}

BOOL ECALL response_get_url(CefResponse* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	*str = (DWORD)UnicodeToEStream(obj->GetURL().c_str());

	return str != NULL;
}

void ECALL response_set_url(CefResponse* obj, LPCWSTR status)
{
	ISVALID(obj);

	obj->SetURL(status);
}

DWORD acf_response_funcs[] = {
	(DWORD)&response_is_read_only,
	(DWORD)&response_get_error,
	(DWORD)&response_set_error,
	(DWORD)&response_get_status,
	(DWORD)&response_set_status,
	(DWORD)&response_get_status_text,
	(DWORD)&response_set_status_text,
	(DWORD)&response_get_mime_type,
	(DWORD)&response_set_mime_type,
	(DWORD)&response_get_charset,
	(DWORD)&response_set_charset,
	(DWORD)&response_get_header_by_name,
	(DWORD)&response_set_header_by_name,
	(DWORD)&response_get_header_map,
	(DWORD)&response_set_header_map,
	(DWORD)&response_get_url,
	(DWORD)&response_set_url,
};

ACF_EXPORTS(PostDataCreate, BOOL)(DWORD* target)
{
	CefRefPtr<CefPostData> lpObj = CefPostData::Create();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_post_data_funcs;

	return !!lpObj;
}

bool ECALL postdata_isread_only(CefPostData* obj)
{
	ISVALIDR(obj, FALSE);

	return obj->IsReadOnly();
}

bool ECALL postdata_has_excluded_elements(CefPostData* obj)
{
	ISVALIDR(obj, FALSE);

	return obj->HasExcludedElements();
}

int ECALL postdata_get_element_count(CefPostData* obj)
{
	ISVALIDR(obj, FALSE);

	return obj->GetElementCount();
}

BOOL ECALL postdata_get_elements(CefPostData* obj, LPVOID* eArray)
{
	ISVALIDR(obj, FALSE);

	CefPostData::ElementVector arguments;
	obj->GetElements(arguments);

	DWORD* pStrs = new DWORD[arguments.size()];
	for (size_t i = 0; i < arguments.size(); i++)
	{
		PECLASS_VFPTR pNewClass = new ECLASS_VFPTR;
		pNewClass->dwVfTable = eClass::m_pVfPostElementTable;
		pNewClass->pCFuncs = acf_post_element_funcs;
		arguments[i]->AddRef();
		pNewClass->pObject = ((LPVOID)(arguments[i].get()));

		pStrs[i] = (DWORD)pNewClass;
	}

	int nSize = arguments.size() * sizeof(DWORD);
	LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
	*(LPINT)pAry = 1;
	*(LPINT)(pAry + sizeof(INT)) = arguments.size();
	memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
	delete[]pStrs;

	*eArray = pAry;

	return eArray != NULL;
}

BOOL ECALL postdata_remove_element(CefPostData* obj, CefPostDataElement* element)
{
	ISVALIDR(obj, FALSE);

	return obj->RemoveElement(element);
}

BOOL ECALL postdata_add_element(CefPostData* obj, CefPostDataElement* element)
{
	ISVALIDR(obj, FALSE);

	return obj->AddElement(element);
}

void ECALL postdata_remove_elements(CefPostData* obj)
{
	ISVALID(obj);

	obj->RemoveElements();
}

DWORD acf_post_data_funcs[] = {
	(DWORD)&postdata_isread_only,
	(DWORD)&postdata_has_excluded_elements,
	(DWORD)&postdata_get_element_count,
	(DWORD)&postdata_get_elements,
	(DWORD)&postdata_remove_element,
	(DWORD)&postdata_add_element,
	(DWORD)&postdata_remove_elements,
};

ACF_EXPORTS(PostDataElementCreate, BOOL)(DWORD* target)
{
	CefRefPtr<CefPostDataElement> lpObj = CefPostDataElement::Create();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_post_element_funcs;

	return !!lpObj;
}

bool ECALL postelement_is_read_only(CefPostDataElement* obj)
{
	ISVALIDR(obj, FALSE);

	return obj->IsReadOnly();
}

void ECALL postelement_set_to_empty(CefPostDataElement* obj)
{
	ISVALID(obj);

	obj->SetToEmpty();
}

void ECALL postelement_set_to_file(CefPostDataElement* obj, LPCWSTR file)
{
	ISVALID(obj);

	obj->SetToFile(file);
}

void ECALL postelement_set_to_bytes(CefPostDataElement* obj, int size, LPVOID buffer)
{
	ISVALID(obj);

	obj->SetToBytes(size, buffer);
}

int ECALL postelement_get_type(CefPostDataElement* obj)
{
	ISVALIDR(obj, FALSE);

	return obj->GetType();
}

BOOL ECALL postelement_get_file(CefPostDataElement* obj, DWORD* str)
{
	ISVALIDR(obj, FALSE);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetFile().c_str());

	return str != NULL;
}

int ECALL postelement_get_bytes_count(CefPostDataElement* obj)
{
	ISVALIDR(obj, FALSE);

	return obj->GetBytesCount();
}

int ECALL postelement_get_bytes(CefPostDataElement* obj, int size, LPVOID bytes)
{
	ISVALIDR(obj, FALSE);

	return obj->GetBytes(size, bytes);
}

DWORD acf_post_element_funcs[] = {
	(DWORD)&postelement_is_read_only,
	(DWORD)&postelement_set_to_empty,
	(DWORD)&postelement_set_to_file,
	(DWORD)&postelement_set_to_bytes,
	(DWORD)&postelement_get_type,
	(DWORD)&postelement_get_file,
	(DWORD)&postelement_get_bytes_count,
	(DWORD)&postelement_get_bytes,
};

ACF_EXPORTS(URLRequestCreate, BOOL)(DWORD* target, CefRequest* request, LPVOID client, BOOL copyData, CefRequestContext* context)
{
	CefRefPtr<ACFlibURLRequestClient> lpClient = new ACFlibURLRequestClient(client, copyData);

	CefRefPtr<CefURLRequest> lpObj = CefURLRequest::Create(request, lpClient, context);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_url_request_funcs;

	return !!lpObj;
}

bool ECALL urlrequest_get_request(CefURLRequest* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefRequest> dupObj = obj->GetRequest();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_request_funcs;

	return !!dupObj;
}

DWORD ECALL urlrequest_get_client(CefURLRequest* obj)
{
	ISVALIDR(obj, false);

	return (DWORD)(LPVOID)obj->GetClient();
}

int ECALL urlrequest_get_request_status(CefURLRequest* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetRequestStatus();
}

int ECALL urlrequest_get_request_error(CefURLRequest* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetRequestError();
}

bool ECALL urlrequest_get_response(CefURLRequest* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefResponse> dupObj = obj->GetResponse();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_response_funcs;

	return !!dupObj;
}

BOOL ECALL urlrequest_response_was_cached(CefURLRequest* obj)
{
	ISVALIDR(obj, NULL);

	return obj->ResponseWasCached();
}

void ECALL urlrequest_cancel(CefURLRequest* obj)
{
	ISVALID(obj);

	obj->Cancel();
}

DWORD acf_url_request_funcs[] = {
	(DWORD)&urlrequest_get_request,
	(DWORD)&urlrequest_get_client,
	(DWORD)&urlrequest_get_request_status,
	(DWORD)&urlrequest_get_request_error,
	(DWORD)&urlrequest_get_response,
	(DWORD)&urlrequest_response_was_cached,
	(DWORD)&urlrequest_cancel,
};
