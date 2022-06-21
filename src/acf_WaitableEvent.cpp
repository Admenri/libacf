
#include "acf_Types.h"
#include "include/cef_waitable_event.h"

extern DWORD acf_waitable_event_funcs[];

ACF_EXPORTS(WaitableCreate, BOOL)(BOOL auto_reset, BOOL signaled, DWORD* target)
{
	CefRefPtr<CefWaitableEvent> lpObj = CefWaitableEvent::CreateWaitableEvent(auto_reset, signaled);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_waitable_event_funcs;

	return target != NULL;
}

void ECALL waitevent_reset(CefWaitableEvent* obj)
{
	ISVALID(obj);

	obj->Reset();
}

void ECALL waitevent_signal(CefWaitableEvent* obj)
{
	ISVALID(obj);

	obj->Signal();
}

BOOL ECALL waitevent_is_signaled(CefWaitableEvent* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsSignaled();
}

void ECALL waitevent_wait(CefWaitableEvent* obj)
{
	ISVALID(obj);

	obj->Wait();
}

BOOL ECALL waitevent_timed_wait(CefWaitableEvent* obj, int64* max_ms)
{
	ISVALIDR(obj, NULL);

	return obj->TimedWait(*max_ms);
}

DWORD acf_waitable_event_funcs[] = {
	(DWORD)&waitevent_reset,
	(DWORD)&waitevent_signal,
	(DWORD)&waitevent_is_signaled,
	(DWORD)&waitevent_wait,
	(DWORD)&waitevent_timed_wait,
};
