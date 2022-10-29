
#include "acf_Types.h"
#include "acf_Conv.h"
#include "acf_FrameEvents.h"

#include "include/cef_request.h"
#include "include/cef_request_handler.h"
#include "include/cef_urlrequest.h"

extern DWORD acf_request_funcs[];
extern DWORD acf_post_data_funcs[];
extern DWORD acf_post_element_funcs[];
extern DWORD acf_callback_auth[];
extern DWORD acf_url_request_funcs[];
extern DWORD acf_callback_request[];
extern DWORD acf_response_funcs[];

void ECALL requestcallback_continue(CefCallback* obj)
{
	ISVALID(obj);

	obj->Continue();
}

void ECALL requestcallback_cancel(CefCallback* obj)
{
	ISVALID(obj);

	obj->Cancel();
}

DWORD acf_callback_request[] = {
	(DWORD)&requestcallback_continue,
	(DWORD)&requestcallback_cancel,
};

void ECALL auth_continue(CefAuthCallback* obj, LPCWSTR username, LPCWSTR password)
{
	ISVALID(obj);

	obj->Continue(username, password);
}

void ECALL auth_cancel(CefAuthCallback* obj)
{
	ISVALID(obj);

	obj->Cancel();
}

DWORD acf_callback_auth[] = {
	(DWORD)&auth_continue,
	(DWORD)&auth_cancel,
};

ACF_EXPORTS(RequestCreate, BOOL)(DWORD* target)
{
	CefRefPtr<CefRequest> lpObj = CefRequest::Create();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_request_funcs;

	return !!lpObj;
}

bool ECALL request_is_read_only(CefRequest* obj)
{
	ISVALIDR(obj, false);

	return obj->IsReadOnly();
}

bool ECALL request_get_url(CefRequest* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetURL().c_str());

	return ansi_str != 0;
}

void ECALL request_set_url(CefRequest* obj, LPCWSTR str)
{
	ISVALID(obj);

	obj->SetURL(str);
}

bool ECALL request_get_method(CefRequest* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetMethod().c_str());

	return ansi_str != 0;
}

void ECALL request_set_method(CefRequest* obj, LPCWSTR str)
{
	ISVALID(obj);

	obj->SetMethod(str);
}

void ECALL request_set_referer(CefRequest* obj, LPCWSTR url, cef_referrer_policy_t policy)
{
	ISVALID(obj);

	obj->SetReferrer(url, policy);
}

bool ECALL request_get_referer_url(CefRequest* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetReferrerURL().c_str());

	return ansi_str != 0;
}

int ECALL request_get_referer_policy(CefRequest* obj)
{
	ISVALIDR(obj, FALSE);

	return obj->GetReferrerPolicy();
}

bool ECALL request_get_post_data(CefRequest* obj, DWORD* target)
{
	ISVALIDR(obj, NULL);

	CefRefPtr<CefPostData> lpObj = obj->GetPostData();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_post_data_funcs;

	return !!lpObj;
}

void ECALL request_set_post_data(CefRequest* obj, CefPostData* data)
{
	ISVALID(obj);

	obj->SetPostData(data);
}

BOOL ECALL request_get_header_map(CefRequest* obj, LPVOID* eArray)
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

void ECALL request_set_header_map(CefRequest* obj, LPVOID* eArray)
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

bool ECALL request_get_header_by_name(CefRequest* obj, LPCWSTR name, DWORD* ansi_str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetHeaderByName(name).c_str());

	return ansi_str != 0;
}

void ECALL request_set_header_by_name(CefRequest* obj, LPCWSTR name, LPCWSTR value, bool overwrite)
{
	ISVALID(obj);

	USES_CONVERSION;

	obj->SetHeaderByName(name, value, overwrite);
}

void ECALL request_set(CefRequest* obj, LPCWSTR url, LPCWSTR method, CefPostData* data, LPVOID* eArray)
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

	obj->Set(url, method, data, keys);
}

int ECALL request_get_flags(CefRequest* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetFlags();
}

void ECALL request_set_flags(CefRequest* obj, int flags)
{
	ISVALID(obj);

	obj->SetFlags(flags);
}

bool ECALL request_get_first_party_for_cookie(CefRequest* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetFirstPartyForCookies().c_str());

	return ansi_str != 0;
}

void ECALL request_set_first_party_for_cookie(CefRequest* obj, LPCWSTR str)
{
	ISVALID(obj);

	obj->SetFirstPartyForCookies(str);
}

int ECALL request_get_resource_type(CefRequest* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetResourceType();
}

int ECALL request_get_transition_type(CefRequest* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetTransitionType();
}

void ECALL request_get_identifier(CefRequest* obj, int64* id)
{
	ISVALID(obj);

	*id = obj->GetIdentifier();
}

DWORD acf_request_funcs[] = {
	(DWORD)&request_is_read_only,
	(DWORD)&request_get_url,
	(DWORD)&request_set_url,
	(DWORD)&request_get_method,
	(DWORD)&request_set_method,
	(DWORD)&request_set_referer,
	(DWORD)&request_get_referer_url,
	(DWORD)&request_get_referer_policy,
	(DWORD)&request_get_post_data,
	(DWORD)&request_set_post_data,
	(DWORD)&request_get_header_map,
	(DWORD)&request_set_header_map,
	(DWORD)&request_get_header_by_name,
	(DWORD)&request_set_header_by_name,
	(DWORD)&request_set,
	(DWORD)&request_get_flags,
	(DWORD)&request_set_flags,
	(DWORD)&request_get_first_party_for_cookie,
	(DWORD)&request_set_first_party_for_cookie,
	(DWORD)&request_get_resource_type,
	(DWORD)&request_get_transition_type,
	(DWORD)&request_get_identifier,
};
