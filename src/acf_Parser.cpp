
#include "acf_Parser.h"
#include "acf_Types.h"
#include "acf_Conv.h"

#include "include/cef_parser.h"

extern DWORD acf_binary_funcs[];
extern DWORD acf_value_funcs[];

ACF_EXPORTS(Base64Encode, BOOL)(LPVOID buffer, int size, DWORD* var)
{
	CefString pData = CefBase64Encode(buffer, size);

	*var = (DWORD)UnicodeToEStream(pData.c_str());

	return !!var;
}

ACF_EXPORTS(Base64Decode, BOOL)(LPWSTR data, DWORD* target)
{
	CefRefPtr<CefBinaryValue> lpObj = CefBase64Decode(data);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_binary_funcs;

	return lpObj->IsValid();
}

ACF_EXPORTS(URIEncode, BOOL)(LPWSTR text, bool plus, DWORD* var)
{
	CefString pData = CefURIEncode(text, plus);

	*var = (DWORD)UnicodeToEStream(pData.c_str());

	return !!var;
}

ACF_EXPORTS(URIDecode, BOOL)(LPWSTR text, bool utf8, cef_uri_unescape_rule_t rule, DWORD* var)
{
	CefString pData = CefURIDecode(text, utf8, rule);

	*var = (DWORD)UnicodeToEStream(pData.c_str());

	return !!var;
}

ACF_EXPORTS(JSONParse, BOOL)(LPWSTR text, cef_json_parser_options_t options, DWORD* target)
{
	CefRefPtr<CefValue> pValue = CefParseJSON(text, options);

	pValue->AddRef();
	target[1] = (DWORD)((LPVOID)pValue.get());
	target[2] = (DWORD)acf_value_funcs;

	return !!pValue;
}

ACF_EXPORTS(JSONParseBin, BOOL)(LPVOID buffer, int size, cef_json_parser_options_t options, DWORD* target)
{
	CefRefPtr<CefValue> pValue = CefParseJSON(buffer, size, options);

	pValue->AddRef();
	target[1] = (DWORD)((LPVOID)pValue.get());
	target[2] = (DWORD)acf_value_funcs;

	return !!pValue;
}

ACF_EXPORTS(JSONWrite, BOOL)(CefValue* node, cef_json_writer_options_t options, DWORD* var)
{
	CefString pData = CefWriteJSON(node, options);

	*var = (DWORD)UnicodeToEStream(pData.c_str());

	return !!var;
}