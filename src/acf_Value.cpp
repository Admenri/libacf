
#include "acf_Types.h"
#include "acf_Conv.h"

#include "include/cef_values.h"

extern DWORD acf_value_funcs[];
extern DWORD acf_binary_funcs[];
extern DWORD acf_dictionary_funcs[];
extern DWORD acf_list_funcs[];

ACF_EXPORTS(ValueCreate, BOOL)(DWORD* target)
{
	CefRefPtr<CefValue> lpObj = CefValue::Create();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_value_funcs;

	return !!lpObj;
}

bool ECALL value_is_valid(CefValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsValid();
}

bool ECALL value_is_owned(CefValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsOwned();
}

bool ECALL value_is_read_only(CefValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsReadOnly();
}

bool ECALL value_is_same(CefValue* obj, CefValue* that)
{
	ISVALIDR(obj, NULL);

	return obj->IsSame(that);
}

bool ECALL value_is_equal(CefValue* obj, CefValue* that)
{
	ISVALIDR(obj, NULL);

	return obj->IsEqual(that);
}

bool ECALL value_copy(CefValue* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefValue> dupObj = obj->Copy();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_value_funcs;

	return !!dupObj;
}

int ECALL value_get_type(CefValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetType();
}

bool ECALL value_get_bool(CefValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetBool();
}

int ECALL value_get_int(CefValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetInt();
}

bool ECALL value_get_double(CefValue* obj, double* ret_val)
{
	ISVALIDR(obj, NULL);

	*ret_val = obj->GetDouble();

	return ret_val;
}

bool ECALL value_get_string(CefValue* obj, DWORD* ansi_string)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*ansi_string = (DWORD)UnicodeToEStream(obj->GetString().c_str());

	return ansi_string;
}

bool ECALL value_get_binary(CefValue* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefBinaryValue> dupObj = obj->GetBinary();

	if (dupObj)
		dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_binary_funcs;;

	return !!dupObj;
}

bool ECALL value_get_dictionary(CefValue* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDictionaryValue> dupObj = obj->GetDictionary();

	if (dupObj)
		dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_dictionary_funcs;;

	return !!dupObj;
}

bool ECALL value_get_list(CefValue* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefListValue> dupObj = obj->GetList();

	if (dupObj)
		dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_list_funcs;;

	return !!dupObj;
}

BOOL ECALL value_set_null(CefValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->SetNull();
}

BOOL ECALL value_set_bool(CefValue* obj, bool value)
{
	ISVALIDR(obj, NULL);

	return obj->SetBool(value);
}

BOOL ECALL value_set_int(CefValue* obj, int value)
{
	ISVALIDR(obj, NULL);

	return obj->SetInt(value);
}

BOOL ECALL value_set_double(CefValue* obj, double* value)
{
	ISVALIDR(obj, NULL);

	return obj->SetDouble(*value);
}

BOOL ECALL value_set_string(CefValue* obj, LPCWSTR value)
{
	ISVALIDR(obj, NULL);

	return obj->SetString(value);
}

BOOL ECALL value_set_binary(CefValue* obj, CefBinaryValue* value)
{
	ISVALIDR(obj, NULL);

	return obj->SetBinary(value);
}

BOOL ECALL value_set_dictionary(CefValue* obj, CefDictionaryValue* value)
{
	ISVALIDR(obj, NULL);

	return obj->SetDictionary(value);
}

BOOL ECALL value_set_list(CefValue* obj, CefListValue* value)
{
	ISVALIDR(obj, NULL);

	return obj->SetList(value);
}

DWORD acf_value_funcs[] = {
	(DWORD)&value_is_valid,
	(DWORD)&value_is_owned,
	(DWORD)&value_is_read_only,
	(DWORD)&value_is_same,
	(DWORD)&value_is_equal,
	(DWORD)&value_copy,
	(DWORD)&value_get_type,
	(DWORD)&value_get_bool,
	(DWORD)&value_get_int,
	(DWORD)&value_get_double,
	(DWORD)&value_get_string,
	(DWORD)&value_get_binary,
	(DWORD)&value_get_dictionary,
	(DWORD)&value_get_list,
	(DWORD)&value_set_null,
	(DWORD)&value_set_bool,
	(DWORD)&value_set_int,
	(DWORD)&value_set_double,
	(DWORD)&value_set_string,
	(DWORD)&value_set_binary,
	(DWORD)&value_set_dictionary,
	(DWORD)&value_set_list,
};

ACF_EXPORTS(BinaryValueCreate, BOOL)(DWORD* target, LPVOID buffer, int size)
{
	CefRefPtr<CefBinaryValue> lpObj = CefBinaryValue::Create(buffer, size);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_binary_funcs;

	return !!lpObj;
}

bool ECALL binary_is_valid(CefBinaryValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsValid();
}

bool ECALL binary_is_owned(CefBinaryValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsOwned();
}

bool ECALL binary_is_same(CefBinaryValue* obj, CefBinaryValue* that)
{
	ISVALIDR(obj, NULL);

	return obj->IsSame(that);
}

bool ECALL binary_is_equal(CefBinaryValue* obj, CefBinaryValue* that)
{
	ISVALIDR(obj, NULL);

	return obj->IsEqual(that);
}

bool ECALL binary_copy(CefBinaryValue* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefBinaryValue> dupObj = obj->Copy();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_value_funcs;

	return !!dupObj;
}

int ECALL binary_get_size(CefBinaryValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetSize();
}

int ECALL binary_get_data(CefBinaryValue* obj, LPVOID buffer, int size, int offset)
{
	ISVALIDR(obj, NULL);

	return obj->GetData(buffer, size, offset);
}

DWORD acf_binary_funcs[] = {
	(DWORD)&binary_is_valid,
	(DWORD)&binary_is_owned,
	(DWORD)&binary_is_same,
	(DWORD)&binary_is_equal,
	(DWORD)&binary_copy,
	(DWORD)&binary_get_size,
	(DWORD)&binary_get_data,
};

ACF_EXPORTS(DictionaryValueCreate, BOOL)(DWORD* target)
{
	CefRefPtr<CefDictionaryValue> lpObj = CefDictionaryValue::Create();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_dictionary_funcs;

	return !!lpObj;
}

bool ECALL dictionary_is_valid(CefDictionaryValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsValid();
}

bool ECALL dictionary_is_owned(CefDictionaryValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsOwned();
}

bool ECALL dictionary_is_read_only(CefDictionaryValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsReadOnly();
}

bool ECALL dictionary_is_same(CefDictionaryValue* obj, CefDictionaryValue* that)
{
	ISVALIDR(obj, NULL);

	return obj->IsSame(that);
}

bool ECALL dictionary_is_equal(CefDictionaryValue* obj, CefDictionaryValue* that)
{
	ISVALIDR(obj, NULL);

	return obj->IsEqual(that);
}

bool ECALL dictionary_copy(CefDictionaryValue* obj, DWORD* target, bool exclude_empty)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDictionaryValue> dupObj = obj->Copy(exclude_empty);

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_value_funcs;

	return !!dupObj;
}

int ECALL dictionary_get_size(CefDictionaryValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetSize();
}

BOOL ECALL dictionary_clear(CefDictionaryValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->Clear();
}

bool ECALL dictionary_has_key(CefDictionaryValue* obj, LPCWSTR key)
{
	ISVALIDR(obj, NULL);

	return obj->HasKey(key);
}

bool ECALL dictionary_get_keys(CefDictionaryValue* obj, LPVOID* eArray)
{
	ISVALIDR(obj, NULL);

	std::vector<CefString> keys;
	obj->GetKeys(keys);

	DWORD* pStrs = new DWORD[keys.size()];
	USES_CONVERSION;
	for (size_t i = 0; i < keys.size(); i++)
	{
		pStrs[i] = (DWORD)UnicodeToEStream(keys[i].c_str());
	}

	FreeAryElement(*eArray);

	int nSize = keys.size() * sizeof(DWORD);
	LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
	*(LPINT)pAry = 1;
	*(LPINT)(pAry + sizeof(INT)) = keys.size();
	memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
	delete[]pStrs;

	*eArray = pAry;

	return !!eArray;
}

bool ECALL dictionary_remove(CefDictionaryValue* obj, LPCWSTR key)
{
	ISVALIDR(obj, NULL);

	return obj->Remove(key);
}

int ECALL dictionary_get_type(CefDictionaryValue* obj, LPCWSTR key)
{
	ISVALIDR(obj, NULL);

	return obj->GetType(key);
}

bool ECALL dictionary_get_value(CefDictionaryValue* obj, LPCWSTR key, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefValue> dupObj = obj->GetValue(key);

	if (dupObj)
		dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_value_funcs;

	return !!dupObj;
}

bool ECALL dictionary_get_bool(CefDictionaryValue* obj, LPCWSTR key)
{
	ISVALIDR(obj, NULL);

	return obj->GetBool(key);
}

int ECALL dictionary_get_int(CefDictionaryValue* obj, LPCWSTR key)
{
	ISVALIDR(obj, NULL);

	return obj->GetInt(key);
}

bool ECALL dictionary_get_double(CefDictionaryValue* obj, LPCWSTR key, double* ret_val)
{
	ISVALIDR(obj, NULL);

	*ret_val = obj->GetDouble(key);

	return ret_val;
}

bool ECALL dictionary_get_string(CefDictionaryValue* obj, LPCWSTR key, DWORD* ansi_string)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*ansi_string = (DWORD)UnicodeToEStream(obj->GetString(key).c_str());

	return ansi_string;
}

bool ECALL dictionary_get_binary(CefDictionaryValue* obj, LPCWSTR key, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefBinaryValue> dupObj = obj->GetBinary(key);
	
	if (dupObj)
		dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_binary_funcs;

	return !!dupObj;
}

bool ECALL dictionary_get_dictionary(CefDictionaryValue* obj, LPCWSTR key, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDictionaryValue> dupObj = obj->GetDictionary(key);

	if (dupObj)
		dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_dictionary_funcs;

	return !!dupObj;
}

bool ECALL dictionary_get_list(CefDictionaryValue* obj, LPCWSTR key, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefListValue> dupObj = obj->GetList(key);

	if (dupObj)
		dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_list_funcs;

	return !!dupObj;
}

bool ECALL dictionary_set_value(CefDictionaryValue* obj, LPCWSTR key, CefValue* value)
{
	ISVALIDR(obj, false);

	return obj->SetValue(key, value);
}

bool ECALL dictionary_set_bool(CefDictionaryValue* obj, LPCWSTR key, bool value)
{
	ISVALIDR(obj, NULL);

	return obj->SetBool(key, value);
}

int ECALL dictionary_set_int(CefDictionaryValue* obj, LPCWSTR key, int value)
{
	ISVALIDR(obj, NULL);

	return obj->SetInt(key, value);
}

bool ECALL dictionary_set_double(CefDictionaryValue* obj, LPCWSTR key, double* ret_val)
{
	ISVALIDR(obj, NULL);

	return obj->SetDouble(key, *ret_val);
}

bool ECALL dictionary_set_string(CefDictionaryValue* obj, LPCWSTR key, LPCWSTR value)
{
	ISVALIDR(obj, NULL);

	return obj->SetString(key, value);
}

bool ECALL dictionary_set_binary(CefDictionaryValue* obj, LPCWSTR key, CefBinaryValue* value)
{
	ISVALIDR(obj, false);

	return obj->SetBinary(key, value);
}

bool ECALL dictionary_set_dictionary(CefDictionaryValue* obj, LPCWSTR key, CefDictionaryValue* value)
{
	ISVALIDR(obj, false);

	return obj->SetDictionary(key, value);
}

bool ECALL dictionary_set_list(CefDictionaryValue* obj, LPCWSTR key, CefListValue* value)
{
	ISVALIDR(obj, false);

	return obj->SetList(key, value);
}

DWORD acf_dictionary_funcs[] = {
	(DWORD)&dictionary_is_valid,
	(DWORD)&dictionary_is_owned,
	(DWORD)&dictionary_is_read_only,
	(DWORD)&dictionary_is_same,
	(DWORD)&dictionary_is_equal,
	(DWORD)&dictionary_copy,
	(DWORD)&dictionary_get_size,
	(DWORD)&dictionary_clear,
	(DWORD)&dictionary_has_key,
	(DWORD)&dictionary_get_keys,
	(DWORD)&dictionary_remove,
	(DWORD)&dictionary_get_type,
	(DWORD)&dictionary_get_value,
	(DWORD)&dictionary_get_bool,
	(DWORD)&dictionary_get_int,
	(DWORD)&dictionary_get_double,
	(DWORD)&dictionary_get_string,
	(DWORD)&dictionary_get_binary,
	(DWORD)&dictionary_get_dictionary,
	(DWORD)&dictionary_get_list,
	(DWORD)&dictionary_set_value,
	(DWORD)&dictionary_set_bool,
	(DWORD)&dictionary_set_int,
	(DWORD)&dictionary_set_double,
	(DWORD)&dictionary_set_string,
	(DWORD)&dictionary_set_binary,
	(DWORD)&dictionary_set_dictionary,
	(DWORD)&dictionary_set_list,
};

ACF_EXPORTS(ListValueCreate, BOOL)(DWORD* target)
{
	CefRefPtr<CefListValue> lpObj = CefListValue::Create();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_list_funcs;

	return !!lpObj;
}

bool ECALL list_is_valid(CefListValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsValid();
}

bool ECALL list_is_owned(CefListValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsOwned();
}

bool ECALL list_is_read_only(CefListValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsReadOnly();
}

bool ECALL list_is_same(CefListValue* obj, CefListValue* that)
{
	ISVALIDR(obj, NULL);

	return obj->IsSame(that);
}

bool ECALL list_is_equal(CefListValue* obj, CefListValue* that)
{
	ISVALIDR(obj, NULL);

	return obj->IsEqual(that);
}

bool ECALL list_copy(CefListValue* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefListValue> dupObj = obj->Copy();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_list_funcs;

	return !!dupObj;
}

BOOL ECALL list_set_size(CefListValue* obj, int size)
{
	ISVALIDR(obj, NULL);

	return obj->SetSize(size);
}

int ECALL list_get_size(CefListValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetSize();
}

BOOL ECALL list_clear(CefListValue* obj)
{
	ISVALIDR(obj, NULL);

	return obj->Clear();
}

BOOL ECALL list_remove(CefListValue* obj, int index)
{
	ISVALIDR(obj, NULL);

	return obj->Remove(index);
}

int ECALL list_get_type(CefListValue* obj, int index)
{
	ISVALIDR(obj, NULL);

	return obj->GetType(index);
}

bool ECALL list_get_value(CefListValue* obj, int key, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefValue> dupObj = obj->GetValue(key);

	if (dupObj)
		dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_value_funcs;

	return !!dupObj;
}

bool ECALL list_get_bool(CefListValue* obj, int key)
{
	ISVALIDR(obj, NULL);

	return obj->GetBool(key);
}

int ECALL list_get_int(CefListValue* obj, int key)
{
	ISVALIDR(obj, NULL);

	return obj->GetInt(key);
}

bool ECALL list_get_double(CefListValue* obj, int key, double* ret_val)
{
	ISVALIDR(obj, NULL);

	*ret_val = obj->GetDouble(key);

	return ret_val;
}

bool ECALL list_get_string(CefListValue* obj, int key, DWORD* ansi_string)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*ansi_string = (DWORD)UnicodeToEStream(obj->GetString(key).c_str());

	return ansi_string;
}

bool ECALL list_get_binary(CefListValue* obj, int key, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefBinaryValue> dupObj = obj->GetBinary(key);

	if (dupObj)
		dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_binary_funcs;

	return !!dupObj;
}

bool ECALL list_get_dictionary(CefListValue* obj, int key, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDictionaryValue> dupObj = obj->GetDictionary(key);

	if (dupObj)
		dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_dictionary_funcs;

	return !!dupObj;
}

bool ECALL list_get_list(CefListValue* obj, int key, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefListValue> dupObj = obj->GetList(key);

	if (dupObj)
		dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_list_funcs;

	return !!dupObj;
}

bool ECALL list_set_value(CefListValue* obj, int key, CefValue* value)
{
	ISVALIDR(obj, false);

	return obj->SetValue(key, value);
}

bool ECALL list_set_bool(CefListValue* obj, int key, bool value)
{
	ISVALIDR(obj, NULL);

	return obj->SetBool(key, value);
}

int ECALL list_set_int(CefListValue* obj, int key, int value)
{
	ISVALIDR(obj, NULL);

	return obj->SetInt(key, value);
}

bool ECALL list_set_double(CefListValue* obj, int key, double* ret_val)
{
	ISVALIDR(obj, NULL);

	return obj->SetDouble(key, *ret_val);
}

bool ECALL list_set_string(CefListValue* obj, int key, LPCWSTR value)
{
	ISVALIDR(obj, NULL);

	return obj->SetString(key, value);
}

bool ECALL list_set_binary(CefListValue* obj, int key, CefBinaryValue* value)
{
	ISVALIDR(obj, false);

	return obj->SetBinary(key, value);
}

bool ECALL list_set_dictionary(CefListValue* obj, int key, CefDictionaryValue* value)
{
	ISVALIDR(obj, false);

	return obj->SetDictionary(key, value);
}

bool ECALL list_set_list(CefListValue* obj, int key, CefListValue* value)
{
	ISVALIDR(obj, false);

	return obj->SetList(key, value);
}

DWORD acf_list_funcs[] = {
	(DWORD)&list_is_valid,
	(DWORD)&list_is_owned,
	(DWORD)&list_is_read_only,
	(DWORD)&list_is_same,
	(DWORD)&list_is_equal,
	(DWORD)&list_copy,
	(DWORD)&list_set_size,
	(DWORD)&list_get_size,
	(DWORD)&list_clear,
	(DWORD)&list_remove,
	(DWORD)&list_get_type,
	(DWORD)&list_get_value,
	(DWORD)&list_get_bool,
	(DWORD)&list_get_int,
	(DWORD)&list_get_double,
	(DWORD)&list_get_string,
	(DWORD)&list_get_binary,
	(DWORD)&list_get_dictionary,
	(DWORD)&list_get_list,
	(DWORD)&list_set_value,
	(DWORD)&list_set_bool,
	(DWORD)&list_set_int,
	(DWORD)&list_set_double,
	(DWORD)&list_set_string,
	(DWORD)&list_set_binary,
	(DWORD)&list_set_dictionary,
	(DWORD)&list_set_list,
};
