
#include "acf_Types.h"
#include "acf_Conv.h"
#include "acf_FrameEvents.h"

#include "include/cef_extension.h"

extern DWORD acf_extension_funcs[];
extern DWORD acf_stream_reader_funcs[];
extern DWORD acf_stream_writer_funcs[];
extern DWORD acf_dictionary_funcs[];
extern DWORD acf_request_context_funcs[];
extern DWORD acf_server_funcs[];
extern DWORD acf_taskrunner_funcs[];

BOOL ECALL ext_get_identifier(CefExtension* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetIdentifier().c_str());

	return ansi_str != 0;
}

BOOL ECALL ext_get_path(CefExtension* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetPath().c_str());

	return ansi_str != 0;
}

bool ECALL ext_get_manifest(CefExtension* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDictionaryValue> dupObj = obj->GetManifest();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_dictionary_funcs;

	return dupObj != NULL;
}

bool ECALL ext_is_same(CefExtension* obj, CefExtension* that)
{
	ISVALIDR(obj, false);

	return obj->IsSame(that);
}

LPVOID ECALL ext_get_handler(CefExtension* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetHandler();
}

bool ECALL ext_get_loader_context(CefExtension* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefRequestContext> dupObj = obj->GetLoaderContext();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_request_context_funcs;

	return dupObj != NULL;
}

bool ECALL ext_is_loaded(CefExtension* obj)
{
	ISVALIDR(obj, false);

	return obj->IsLoaded();
}

void ECALL ext_unload(CefExtension* obj)
{
	ISVALID(obj);

	obj->Unload();
}

DWORD acf_extension_funcs[] = {
	(DWORD)&ext_get_identifier,
	(DWORD)&ext_get_path,
	(DWORD)&ext_get_manifest,
	(DWORD)&ext_is_same,
	(DWORD)&ext_get_handler,
	(DWORD)&ext_get_loader_context,
	(DWORD)&ext_is_loaded,
	(DWORD)&ext_unload,
};

extern DWORD acf_server_funcs[];

ACF_EXPORTS(ServerCreate, void)(LPCWSTR address, int port, int backlog, LPVOID callback, BOOL copyData)
{
	CefRefPtr<ACFlibServerHandler> lpHandler = new ACFlibServerHandler(callback, copyData);

	CefServer::CreateServer(address, port, backlog, lpHandler);
}

BOOL ECALL server_get_taskrunner(CefServer* obj, DWORD* target)
{
	ISVALIDR(obj, FALSE);

	CefRefPtr<CefTaskRunner> lpObj = obj->GetTaskRunner();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_taskrunner_funcs;

	return !!target;
}

void ECALL server_shutdown(CefServer* obj)
{
	ISVALID(obj);

	obj->Shutdown();
}

BOOL ECALL server_is_running(CefServer* obj)
{
	ISVALIDR(obj, FALSE);

	return obj->IsRunning();
}

BOOL ECALL server_get_address(CefServer* obj, DWORD* string)
{
	ISVALIDR(obj, FALSE);

	USES_CONVERSION;

	*string = (DWORD)UnicodeToEStream(obj->GetAddress().c_str());

	return !!string;
}

BOOL ECALL server_has_connection(CefServer* obj)
{
	ISVALIDR(obj, FALSE);

	return obj->HasConnection();
}

BOOL ECALL server_is_valid_connection(CefServer* obj, int connection_id)
{
	ISVALIDR(obj, FALSE);

	return obj->IsValidConnection(connection_id);
}

void ECALL server_send_http200_response(CefServer* obj, int connection_id, LPCWSTR content_type, LPVOID data, int size)
{
	ISVALID(obj);

	obj->SendHttp200Response(connection_id, content_type, data, size);
}

void ECALL server_send_http404_response(CefServer* obj, int connection_id)
{
	ISVALID(obj);

	obj->SendHttp404Response(connection_id);
}

void ECALL server_send_http500_response(CefServer* obj, int connection_id, LPCWSTR error_message)
{
	ISVALID(obj);

	obj->SendHttp500Response(connection_id, error_message);
}

void ECALL server_send_http_response(CefServer* obj, int connection_id, int response_code, LPCWSTR content_type, int64* length, LPVOID* eArray)
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

	obj->SendHttpResponse(connection_id, response_code, content_type, *length, keys);
}

void ECALL server_send_raw_data(CefServer* obj, int connection_id, LPVOID data, int size)
{
	ISVALID(obj);

	obj->SendRawData(connection_id, data, size);
}

void ECALL server_close_connection(CefServer* obj, int connection_id)
{
	ISVALID(obj);

	obj->CloseConnection(connection_id);
}

void ECALL server_send_websocket_message(CefServer* obj, int connection_id, LPVOID data, int size)
{
	ISVALID(obj);

	obj->SendWebSocketMessage(connection_id, data, size);
}

DWORD acf_server_funcs[] = {
	(DWORD)&server_get_taskrunner,
	(DWORD)&server_shutdown,
	(DWORD)&server_is_running,
	(DWORD)&server_get_address,
	(DWORD)&server_has_connection,
	(DWORD)&server_is_valid_connection,
	(DWORD)&server_send_http200_response,
	(DWORD)&server_send_http404_response,
	(DWORD)&server_send_http500_response,
	(DWORD)&server_send_http_response,
	(DWORD)&server_send_raw_data,
	(DWORD)&server_close_connection,
	(DWORD)&server_send_websocket_message,
};

extern DWORD acf_stream_reader_funcs[] = {0};
extern DWORD acf_stream_writer_funcs[] = {0};
