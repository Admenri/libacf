
#include "acf_Types.h"
#include "include/cef_download_item.h"
#include "include/cef_download_handler.h"
#include "acf_Conv.h"

extern DWORD acf_download_funcs[];
extern DWORD acf_callback_download[];
extern DWORD acf_callback_download_before[];

BOOL ECALL download_is_valid(CefDownloadItem* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsValid();
}

BOOL ECALL download_is_in_progress(CefDownloadItem* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsInProgress();
}

BOOL ECALL download_is_complete(CefDownloadItem* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsComplete();
}

BOOL ECALL download_is_canceled(CefDownloadItem* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsCanceled();
}

BOOL ECALL download_get_current_speed(CefDownloadItem* obj, int64* speed)
{
	ISVALIDR(obj, NULL);

	*speed = obj->GetCurrentSpeed();

	return speed != NULL;
}

int ECALL download_get_percent_complete(CefDownloadItem* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetPercentComplete();
}

BOOL ECALL download_get_total_bytes(CefDownloadItem* obj, int64* speed)
{
	ISVALIDR(obj, NULL);

	*speed = obj->GetTotalBytes();

	return speed != NULL;
}

BOOL ECALL download_get_received_bytes(CefDownloadItem* obj, int64* speed)
{
	ISVALIDR(obj, NULL);

	*speed = obj->GetReceivedBytes();

	return speed != NULL;
}

BOOL ECALL download_get_start_time(CefDownloadItem* obj, cef_time_t** time_)
{
	ISVALIDR(obj, NULL);

	**time_ = obj->GetStartTime();

	return time_ != NULL;
}

BOOL ECALL download_get_end_time(CefDownloadItem* obj, cef_time_t** time_)
{
	ISVALIDR(obj, NULL);

	**time_ = obj->GetEndTime();

	return time_ != NULL;
}

BOOL ECALL download_get_fullpath(CefDownloadItem* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	*str = (DWORD)UnicodeToEStream(obj->GetFullPath().c_str());

	return str != NULL;
}

int ECALL download_get_id(CefDownloadItem* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetId();
}

BOOL ECALL download_get_url(CefDownloadItem* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	*str = (DWORD)UnicodeToEStream(obj->GetURL().c_str());

	return str != NULL;
}

BOOL ECALL download_get_original_url(CefDownloadItem* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	*str = (DWORD)UnicodeToEStream(obj->GetOriginalUrl().c_str());

	return str != NULL;
}

BOOL ECALL download_get_suggested_file_name(CefDownloadItem* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	*str = (DWORD)UnicodeToEStream(obj->GetSuggestedFileName().c_str());

	return str != NULL;
}

BOOL ECALL download_get_content_disposition(CefDownloadItem* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	*str = (DWORD)UnicodeToEStream(obj->GetContentDisposition().c_str());

	return str != NULL;
}

BOOL ECALL download_get_mime_type(CefDownloadItem* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	*str = (DWORD)UnicodeToEStream(obj->GetMimeType().c_str());

	return str != NULL;
}

DWORD acf_download_funcs[] = {
	(DWORD)&download_is_valid,
	(DWORD)&download_is_in_progress,
	(DWORD)&download_is_complete,
	(DWORD)&download_is_canceled,
	(DWORD)&download_get_current_speed,
	(DWORD)&download_get_percent_complete,
	(DWORD)&download_get_total_bytes,
	(DWORD)&download_get_received_bytes,
	(DWORD)&download_get_start_time,
	(DWORD)&download_get_end_time,
	(DWORD)&download_get_fullpath,
	(DWORD)&download_get_id,
	(DWORD)&download_get_url,
	(DWORD)&download_get_original_url,
	(DWORD)&download_get_suggested_file_name,
	(DWORD)&download_get_content_disposition,
	(DWORD)&download_get_mime_type,
};

void ECALL download_cancel(CefDownloadItemCallback* obj)
{
	ISVALID(obj);

	obj->Cancel();
}

void ECALL download_pause(CefDownloadItemCallback* obj)
{
	ISVALID(obj);

	obj->Pause();
}

void ECALL download_resume(CefDownloadItemCallback* obj)
{
	ISVALID(obj);

	obj->Resume();
}

DWORD acf_callback_download[] = {
	(DWORD)&download_cancel,
	(DWORD)&download_pause,
	(DWORD)&download_resume,
};

void ECALL before_download_continue(CefBeforeDownloadCallback* obj, LPCWSTR path, bool show_dialog)
{
	ISVALID(obj);

	obj->Continue(path, show_dialog);
}

DWORD acf_callback_download_before[] = {
	(DWORD)&before_download_continue,
};
