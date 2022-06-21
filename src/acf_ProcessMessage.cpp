
#include "acf_Types.h"
#include "acf_Conv.h"

#include "include/cef_process_message.h"

extern DWORD acf_process_message_funcs[];
extern DWORD acf_list_funcs[];

ACF_EXPORTS(ProcessMessageCreate, BOOL)(DWORD* target, LPWSTR name)
{
	CefRefPtr<CefProcessMessage> lpObj = CefProcessMessage::Create(name);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_process_message_funcs;

	return !!lpObj;
}

bool ECALL message_is_valid(CefProcessMessage* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsValid();
}

bool ECALL message_is_read_only(CefProcessMessage* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsReadOnly();
}

bool ECALL message_copy(CefProcessMessage* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefProcessMessage> dupObj = obj->Copy();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_process_message_funcs;

	return !!dupObj;
}

bool ECALL message_get_name(CefProcessMessage* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetName().c_str());

	return str != NULL;
}

bool ECALL message_get_argument_list(CefProcessMessage* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefListValue> dupObj = obj->GetArgumentList();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_list_funcs;

	return !!dupObj;
}

DWORD acf_process_message_funcs[] = {
	(DWORD)&message_is_valid,
	(DWORD)&message_is_read_only,
	(DWORD)&message_copy,
	(DWORD)&message_get_name,
	(DWORD)&message_get_argument_list,
};
