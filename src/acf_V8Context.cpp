
#include "acf_Types.h"
#include "acf_Task.h"
#include "acf_Conv.h"
#include "acf_FrameEvents.h"

#include "include/cef_v8.h"

extern DWORD acf_v8_context_funcs[];
extern DWORD acf_browser_funcs[];
extern DWORD acf_frame_funcs[];
extern DWORD acf_taskrunner_funcs[];
extern DWORD acf_v8_value_funcs[];
extern DWORD acf_v8_exception_funcs[];
extern DWORD acf_v8_stack_trace_funcs[];
extern DWORD acf_v8_stack_frame_funcs[];

ACF_EXPORTS(V8ValueCreateUndefined, BOOL)(DWORD* target)
{
	CefRefPtr<CefV8Value> lpObj = CefV8Value::CreateUndefined();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_v8_value_funcs;

	return !!lpObj;
}

ACF_EXPORTS(V8ValueCreateNull, BOOL)(DWORD* target)
{
	CefRefPtr<CefV8Value> lpObj = CefV8Value::CreateNull();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_v8_value_funcs;

	return !!lpObj;
}

ACF_EXPORTS(V8ValueCreateBool, BOOL)(DWORD* target, bool value)
{
	CefRefPtr<CefV8Value> lpObj = CefV8Value::CreateBool(value);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_v8_value_funcs;

	return !!lpObj;
}

ACF_EXPORTS(V8ValueCreateInt, BOOL)(DWORD* target, int value)
{
	CefRefPtr<CefV8Value> lpObj = CefV8Value::CreateInt(value);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_v8_value_funcs;

	return !!lpObj;
}

ACF_EXPORTS(V8ValueCreateUInt, BOOL)(DWORD* target, int64 value)
{
	CefRefPtr<CefV8Value> lpObj = CefV8Value::CreateUInt(value);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_v8_value_funcs;

	return !!lpObj;
}

ACF_EXPORTS(V8ValueCreateDouble, BOOL)(DWORD* target, double value)
{
	CefRefPtr<CefV8Value> lpObj = CefV8Value::CreateDouble(value);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_v8_value_funcs;

	return !!lpObj;
}

ACF_EXPORTS(V8ValueCreateDate, BOOL)(DWORD* target, cef_time_t* value)
{
	cef_basetime_t time;
	cef_time_to_basetime(value, &time);
	CefRefPtr<CefV8Value> lpObj = CefV8Value::CreateDate(time);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_v8_value_funcs;

	return !!lpObj;
}

ACF_EXPORTS(V8ValueCreateString, BOOL)(DWORD* target, LPWSTR value)
{
	CefRefPtr<CefV8Value> lpObj = CefV8Value::CreateString(value);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_v8_value_funcs;

	return !!lpObj;
}

ACF_EXPORTS(V8ValueCreateObject, BOOL)(DWORD* target, LPVOID lpCallback1, BOOL copyData1, LPVOID lpCallback2, BOOL copyData2)
{
	CefRefPtr<ACFlibV8Accessor> lpAccessor = new ACFlibV8Accessor(lpCallback1, copyData1);
	CefRefPtr<ACFlibV8Interceptor> lpInterceptor = new ACFlibV8Interceptor(lpCallback2, copyData2);

	CefRefPtr<CefV8Value> lpObj = CefV8Value::CreateObject(lpAccessor, lpInterceptor);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_v8_value_funcs;

	return !!lpObj;
}

ACF_EXPORTS(V8ValueCreateArray, BOOL)(DWORD* target, int length)
{
	CefRefPtr<CefV8Value> lpObj = CefV8Value::CreateArray(length);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_v8_value_funcs;

	return !!lpObj;
}

ACF_EXPORTS(V8ValueCreateArrayBuffer, BOOL)(DWORD* target, LPVOID buffer, int length, LPVOID lpCallback, BOOL copyData)
{
	CefRefPtr<ACFlibV8ArrayBufferReleaseCallback> objCallback = new ACFlibV8ArrayBufferReleaseCallback(lpCallback, copyData);

	CefRefPtr<CefV8Value> lpObj = CefV8Value::CreateArrayBuffer(buffer, length, objCallback);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_v8_value_funcs;

	return !!lpObj;
}

ACF_EXPORTS(V8ValueCreateFunction, BOOL)(DWORD* target, LPWSTR name, LPVOID lpCallback, BOOL copyData)
{
	CefRefPtr<ACFlibV8Handler> lpV8Handler = new ACFlibV8Handler(lpCallback, copyData);

	CefRefPtr<CefV8Value> lpObj = CefV8Value::CreateFunction(name, lpV8Handler);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_v8_value_funcs;

	return !!lpObj;
}

//--------------------------------------------------------------------------------------------

ACF_EXPORTS(TaskRunnerGetForCurrentThread, BOOL)(DWORD* target)
{
	CefRefPtr<CefTaskRunner> lpObj = CefTaskRunner::GetForCurrentThread();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_taskrunner_funcs;

	return !!lpObj;
}

ACF_EXPORTS(TaskRunnerGetForThread, BOOL)(DWORD* target, cef_thread_id_t tid)
{
	CefRefPtr<CefTaskRunner> lpObj = CefTaskRunner::GetForThread(tid);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_taskrunner_funcs;

	return !!lpObj;
}

bool ECALL task_is_same(CefTaskRunner* obj, CefTaskRunner* that)
{
	ISVALIDR(obj, NULL);

	return obj->IsSame(that);
}

bool ECALL task_belong_to_current_thread(CefTaskRunner* obj)
{
	ISVALIDR(obj, NULL);

	return obj->BelongsToCurrentThread();
}

bool ECALL task_belong_to_thread(CefTaskRunner* obj, cef_thread_id_t tid)
{
	ISVALIDR(obj, NULL);

	return obj->BelongsToThread(tid);
}

bool ECALL task_post_task(CefTaskRunner* obj, LPFN_POST_TASK lpfn, int lParam1, int lParam2, int lParam3)
{
	ISVALIDR(obj, NULL);

	CefRefPtr<ACFlibTask> pTask = new ACFlibTask(lpfn, lParam1, lParam2, lParam3);

	return obj->PostTask(pTask);
}

bool ECALL task_post_delayed_task(CefTaskRunner* obj, int64* delay, LPFN_POST_TASK lpfn, int lParam1, int lParam2, int lParam3)
{
	ISVALIDR(obj, NULL);

	CefRefPtr<ACFlibTask> pTask = new ACFlibTask(lpfn, lParam1, lParam2, lParam3);

	return obj->PostDelayedTask(pTask, *delay);
}

DWORD acf_taskrunner_funcs[] = {
	(DWORD)&task_is_same,
	(DWORD)&task_belong_to_current_thread,
	(DWORD)&task_belong_to_thread,
	(DWORD)&task_post_task,
	(DWORD)&task_post_delayed_task,
};

bool ECALL v8value_is_valid(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsValid();
}

bool ECALL v8value_is_undefined(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsUndefined();
}

bool ECALL v8value_is_null(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsNull();
}

bool ECALL v8value_is_bool(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsBool();
}

bool ECALL v8value_is_int(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsInt();
}

bool ECALL v8value_is_uint(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsUInt();
}

bool ECALL v8value_is_double(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsDouble();
}

bool ECALL v8value_is_date(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsDate();
}

bool ECALL v8value_is_string(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsString();
}

bool ECALL v8value_is_object(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsObject();
}

bool ECALL v8value_is_array(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsArray();
}

bool ECALL v8value_is_array_buffer(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsArrayBuffer();
}

bool ECALL v8value_is_function(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsFunction();
}

bool ECALL v8value_is_same(CefV8Value* obj, CefV8Value* that)
{
	ISVALIDR(obj, NULL);

	return obj->IsSame(that);
}

bool ECALL v8value_get_bool_value(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetBoolValue();
}

int32 ECALL v8value_get_int_value(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetIntValue();
}

BOOL ECALL v8value_get_uint_value(CefV8Value* obj, int64* value)
{
	ISVALIDR(obj, NULL);

	*value = obj->GetUIntValue();

	return value != NULL;
}

BOOL ECALL v8value_get_double_value(CefV8Value* obj, double* value)
{
	ISVALIDR(obj, NULL);

	*value = obj->GetDoubleValue();

	return value != NULL;
}

BOOL ECALL v8value_get_date_value(CefV8Value* obj, cef_time_t** time_)
{
	ISVALIDR(obj, NULL);

	cef_time_from_basetime(obj->GetDateValue(), *time_);

	return time_ != NULL;
}

BOOL ECALL v8value_get_string_value(CefV8Value* obj, DWORD* value)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*value = (DWORD)UnicodeToEStream(obj->GetStringValue().c_str());

	return value != NULL;
}

bool ECALL v8value_is_user_created(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsUserCreated();
}

bool ECALL v8value_has_exception(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->HasException();
}

bool ECALL v8value_get_exception(CefV8Value* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefV8Exception> pBrowser = obj->GetException();

	pBrowser->AddRef();
	target[1] = (DWORD)((LPVOID)pBrowser.get());
	target[2] = (DWORD)acf_v8_exception_funcs;

	return !!pBrowser;
}

bool ECALL v8value_clear_exception(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->ClearException();
}

bool ECALL v8value_will_rethrow_exceptions(CefV8Value* obj)
{
	ISVALIDR(obj, NULL);

	return obj->WillRethrowExceptions();
}

bool ECALL v8value_set_rethrow_exceptions(CefV8Value* obj, bool rethrow)
{
	ISVALIDR(obj, NULL);

	return obj->SetRethrowExceptions(rethrow);
}

bool ECALL v8value_has_value(CefV8Value* obj, LPCWSTR key)
{
	ISVALIDR(obj, NULL);

	return obj->HasValue(key);
}

bool ECALL v8value_has_value_at(CefV8Value* obj, int index)
{
	ISVALIDR(obj, NULL);

	return obj->HasValue(index);
}

bool ECALL v8value_delete_value(CefV8Value* obj, LPCWSTR key)
{
	ISVALIDR(obj, NULL);

	return obj->DeleteValue(key);
}

bool ECALL v8value_delete_value_at(CefV8Value* obj, int index)
{
	ISVALIDR(obj, NULL);

	return obj->DeleteValue(index);
}

bool ECALL v8value_get_value(CefV8Value* obj, LPCWSTR key, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefV8Value> pBrowser = obj->GetValue(key);

	pBrowser->AddRef();
	target[1] = (DWORD)((LPVOID)pBrowser.get());
	target[2] = (DWORD)acf_v8_value_funcs;

	return !!pBrowser;
}

bool ECALL v8value_get_value_at(CefV8Value* obj, int index, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefV8Value> pBrowser = obj->GetValue(index);

	pBrowser->AddRef();
	target[1] = (DWORD)((LPVOID)pBrowser.get());
	target[2] = (DWORD)acf_v8_value_funcs;

	return !!pBrowser;
}

bool ECALL v8value_set_value1(CefV8Value* obj, LPCWSTR key, CefV8Value* value, cef_v8_propertyattribute_t attr)
{
	ISVALIDR(obj, false);

	return obj->SetValue(key, value, attr);
}

bool ECALL v8value_set_value2(CefV8Value* obj, int index, CefV8Value* value)
{
	ISVALIDR(obj, false);

	return obj->SetValue(index, value);
}

bool ECALL v8value_set_value3(CefV8Value* obj, LPCWSTR key, cef_v8_accesscontrol_t settings, cef_v8_propertyattribute_t attr)
{
	ISVALIDR(obj, false);

	return obj->SetValue(key, settings, attr);
}

bool ECALL v8value_get_keys(CefV8Value* obj, LPVOID* eArray)
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

bool ECALL v8value_set_user_data(CefV8Value* obj, LPVOID user_data)
{
	ISVALIDR(obj, false);

	return obj->SetUserData(static_cast<CefBaseRefCounted*>(user_data));
}

LPVOID ECALL v8value_get_user_data(CefV8Value* obj)
{
	ISVALIDR(obj, nullptr);

	return obj->GetUserData().get();
}

int ECALL v8value_get_externally_allocated_memory(CefV8Value* obj)
{
	ISVALIDR(obj, false);

	return obj->GetExternallyAllocatedMemory();
}

int ECALL v8value_adjust_externally_allocated_memory(CefV8Value* obj, int change_in_bytes)
{
	ISVALIDR(obj, false);

	return obj->AdjustExternallyAllocatedMemory(change_in_bytes);
}

int ECALL v8value_get_array_length(CefV8Value* obj)
{
	ISVALIDR(obj, false);

	return obj->GetArrayLength();
}

int ECALL v8value_get_array_buffer_realease_callback(CefV8Value* obj)
{
	ISVALIDR(obj, false);

	// FIXME

	return NULL;
}

BOOL ECALL v8value_neuter_array_buffer(CefV8Value* obj)
{
	ISVALIDR(obj, false);

	return obj->NeuterArrayBuffer();
}

BOOL ECALL v8value_get_function_name(CefV8Value* obj, DWORD* str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetFunctionName().c_str());

	return str != NULL;
}

int ECALL v8value_get_function_handler(CefV8Value* obj)
{
	ISVALIDR(obj, false);

	// FIXME

	return NULL;
}

bool ECALL v8value_execute_function(CefV8Value* obj, CefV8Value* object, DWORD*** argument, DWORD* target)
{
	ISVALIDR(obj, false);

	LPSTR pArgsList = (LPSTR)*argument;

	int nCount = *(LPINT)(pArgsList + sizeof(INT));

	CefV8ValueList pArgs(nCount);

	for (size_t i = 0; i < nCount; i++)
	{
		pArgs[i] = (CefV8Value*)(((DWORD*)(((LPDWORD)(pArgsList + sizeof(INT) * 2))[i]))[1]);
	}

	CefRefPtr<CefV8Value> pBrowser = obj->ExecuteFunction(object, pArgs);

	pBrowser->AddRef();
	target[1] = (DWORD)((LPVOID)pBrowser.get());
	target[2] = (DWORD)acf_v8_value_funcs;

	return !!pBrowser;
}

bool ECALL v8value_execute_function_with_context(CefV8Value* obj, CefV8Context* context, CefV8Value* object, DWORD*** argument, DWORD* target)
{
	ISVALIDR(obj, false);

	LPSTR pArgsList = (LPSTR)*argument;

	int nCount = *(LPINT)(pArgsList + sizeof(INT));

	CefV8ValueList pArgs(nCount);

	for (size_t i = 0; i < nCount; i++)
	{
		pArgs[i] = (CefV8Value*)(((DWORD*)(((LPDWORD)(pArgsList + sizeof(INT) * 2))[i]))[1]);
	}

	CefRefPtr<CefV8Value> pBrowser = obj->ExecuteFunctionWithContext(context, object, pArgs);

	pBrowser->AddRef();
	target[1] = (DWORD)((LPVOID)pBrowser.get());
	target[2] = (DWORD)acf_v8_value_funcs;

	return !!pBrowser;
}

DWORD acf_v8_value_funcs[] = {
	(DWORD)&v8value_is_valid,
	(DWORD)&v8value_is_undefined,
	(DWORD)&v8value_is_null,
	(DWORD)&v8value_is_bool,
	(DWORD)&v8value_is_int,
	(DWORD)&v8value_is_uint,
	(DWORD)&v8value_is_double,
	(DWORD)&v8value_is_date,
	(DWORD)&v8value_is_string,
	(DWORD)&v8value_is_object,
	(DWORD)&v8value_is_array,
	(DWORD)&v8value_is_array_buffer,
	(DWORD)&v8value_is_function,
	(DWORD)&v8value_is_same,
	(DWORD)&v8value_get_bool_value,
	(DWORD)&v8value_get_int_value,
	(DWORD)&v8value_get_uint_value,
	(DWORD)&v8value_get_double_value,
	(DWORD)&v8value_get_date_value,
	(DWORD)&v8value_get_string_value,
	(DWORD)&v8value_is_user_created,
	(DWORD)&v8value_has_exception,
	(DWORD)&v8value_get_exception,
	(DWORD)&v8value_clear_exception,
	(DWORD)&v8value_will_rethrow_exceptions,
	(DWORD)&v8value_set_rethrow_exceptions,
	(DWORD)&v8value_has_value,
	(DWORD)&v8value_has_value_at,
	(DWORD)&v8value_delete_value,
	(DWORD)&v8value_delete_value_at,
	(DWORD)&v8value_get_value,
	(DWORD)&v8value_get_value_at,
	(DWORD)&v8value_set_value1,
	(DWORD)&v8value_set_value2,
	(DWORD)&v8value_set_value3,
	(DWORD)&v8value_get_keys,
	(DWORD)&v8value_set_user_data,
	(DWORD)&v8value_get_user_data,
	(DWORD)&v8value_get_externally_allocated_memory,
	(DWORD)&v8value_adjust_externally_allocated_memory,
	(DWORD)&v8value_get_array_length,
	(DWORD)&v8value_get_array_buffer_realease_callback,
	(DWORD)&v8value_neuter_array_buffer,
	(DWORD)&v8value_get_function_name,
	(DWORD)&v8value_get_function_handler,
	(DWORD)&v8value_execute_function,
	(DWORD)&v8value_execute_function_with_context,
};

ACF_EXPORTS(V8ContextGetCurrent, BOOL)(DWORD* target)
{
	CefRefPtr<CefV8Context> lpObj = CefV8Context::GetCurrentContext();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_v8_context_funcs;

	return !!lpObj;
}

ACF_EXPORTS(V8ContextGetEntered, BOOL)(DWORD* target)
{
	CefRefPtr<CefV8Context> lpObj = CefV8Context::GetEnteredContext();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_v8_context_funcs;

	return !!lpObj;
}

bool ECALL context_get_taskrunner(CefV8Context* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefTaskRunner> pBrowser = obj->GetTaskRunner();

	pBrowser->AddRef();
	target[1] = (DWORD)((LPVOID)pBrowser.get());
	target[2] = (DWORD)acf_taskrunner_funcs;

	return !!pBrowser;
}

bool ECALL context_is_valid(CefV8Context* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsValid();
}

bool ECALL context_get_browser(CefV8Context* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefBrowser> pBrowser = obj->GetBrowser();

	pBrowser->AddRef();
	target[1] = (DWORD)((LPVOID)pBrowser.get());
	target[2] = (DWORD)acf_browser_funcs;

	return !!pBrowser;
}

bool ECALL context_get_frame(CefV8Context* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefFrame> pFrame = obj->GetFrame();

	pFrame->AddRef();
	target[1] = (DWORD)((LPVOID)pFrame.get());
	target[2] = (DWORD)acf_frame_funcs;

	return !!pFrame;
}

bool ECALL context_get_global(CefV8Context* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefV8Value> pFrame = obj->GetGlobal();

	pFrame->AddRef();
	target[1] = (DWORD)((LPVOID)pFrame.get());
	target[2] = (DWORD)acf_v8_value_funcs;

	return !!pFrame;
}

bool ECALL context_enter(CefV8Context* obj)
{
	ISVALIDR(obj, NULL);

	return obj->Enter();
}

bool ECALL context_exit(CefV8Context* obj)
{
	ISVALIDR(obj, NULL);

	return obj->Exit();
}

bool ECALL context_is_same(CefV8Context* obj, CefV8Context* that)
{
	ISVALIDR(obj, NULL);

	return obj->IsSame(that);
}

bool ECALL context_eval(CefV8Context* obj, LPCWSTR code, LPCWSTR url, int line, DWORD* value, DWORD* exception)
{
	ISVALIDR(obj, NULL);

	CefRefPtr<CefV8Value> valRet = nullptr;
	CefRefPtr<CefV8Exception> excRet = nullptr;

	BOOL bRetVal = obj->Eval(code, url, line, valRet, excRet);

	if (valRet) {
		valRet->AddRef();
		value[1] = (DWORD)((LPVOID)valRet.get());
		value[2] = (DWORD)acf_v8_value_funcs;
	}

	if (excRet) {
		excRet->AddRef();
		exception[1] = (DWORD)((LPVOID)excRet.get());
		exception[2] = (DWORD)acf_v8_exception_funcs;
	}

	return bRetVal;
}

DWORD acf_v8_context_funcs[] = {
	(DWORD)&context_get_taskrunner,
	(DWORD)&context_is_valid,
	(DWORD)&context_get_browser,
	(DWORD)&context_get_frame,
	(DWORD)&context_get_global,
	(DWORD)&context_enter,
	(DWORD)&context_exit,
	(DWORD)&context_is_same,
	(DWORD)&context_eval,
};

BOOL ECALL exception_get_message(CefV8Exception* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetMessage().c_str());

	return str != NULL;
}

BOOL ECALL exception_get_source_line(CefV8Exception* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetSourceLine().c_str());

	return str != NULL;
}

BOOL ECALL exception_get_script_resource_name(CefV8Exception* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetScriptResourceName().c_str());

	return str != NULL;
}

int ECALL exception_get_line_number(CefV8Exception* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetLineNumber();
}

int ECALL exception_get_start_position(CefV8Exception* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetStartPosition();
}

int ECALL exception_get_end_position(CefV8Exception* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetEndPosition();
}

int ECALL exception_get_start_column(CefV8Exception* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetStartColumn();
}

int ECALL exception_get_end_column(CefV8Exception* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetEndColumn();
}

DWORD acf_v8_exception_funcs[] = {
	(DWORD)&exception_get_message,
	(DWORD)&exception_get_source_line,
	(DWORD)&exception_get_script_resource_name,
	(DWORD)&exception_get_line_number,
	(DWORD)&exception_get_start_position,
	(DWORD)&exception_get_end_position,
	(DWORD)&exception_get_start_column,
	(DWORD)&exception_get_end_column,
};

ACF_EXPORTS(V8StackTraceGetCurrent, BOOL)(int frame_limit, DWORD* target)
{
	CefRefPtr<CefV8StackTrace> lpObj = CefV8StackTrace::GetCurrent(frame_limit);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_v8_stack_trace_funcs;

	return !!lpObj;
}

BOOL ECALL trace_is_valid(CefV8StackTrace* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsValid();
}

int ECALL trace_get_frame_count(CefV8StackTrace* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetFrameCount();
}

BOOL ECALL trace_get_frame(CefV8StackTrace* obj, int index, DWORD* target)
{
	ISVALIDR(obj, NULL);

	CefRefPtr<CefV8StackFrame> lpObj = obj->GetFrame(index);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_v8_stack_frame_funcs;

	return target != NULL;
}

DWORD acf_v8_stack_trace_funcs[] = {
	(DWORD)&trace_is_valid,
	(DWORD)&trace_get_frame_count,
	(DWORD)&trace_get_frame,
};

BOOL ECALL stackframe_is_valid(CefV8StackFrame* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsValid();
}

BOOL ECALL stackframe_get_script_name(CefV8StackFrame* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetScriptName().c_str());

	return str != NULL;
}

BOOL ECALL stackframe_get_script_name_or_source_url(CefV8StackFrame* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetScriptNameOrSourceURL().c_str());

	return str != NULL;
}

BOOL ECALL stackframe_get_function_name(CefV8StackFrame* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetFunctionName().c_str());

	return str != NULL;
}

int ECALL stackframe_get_line_number(CefV8StackFrame* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetLineNumber();
}

int ECALL stackframe_get_column(CefV8StackFrame* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetColumn();
}

BOOL ECALL stackframe_is_eval(CefV8StackFrame* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsEval();
}

BOOL ECALL stackframe_is_constructor(CefV8StackFrame* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsConstructor();
}

DWORD acf_v8_stack_frame_funcs[] = {
	(DWORD)&stackframe_is_valid,
	(DWORD)&stackframe_get_script_name,
	(DWORD)&stackframe_get_script_name_or_source_url,
	(DWORD)&stackframe_get_function_name,
	(DWORD)&stackframe_get_line_number,
	(DWORD)&stackframe_get_column,
	(DWORD)&stackframe_is_eval,
	(DWORD)&stackframe_is_constructor,
};
