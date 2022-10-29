#pragma once

#include "acf_Types.h"

extern DWORD acf_commandline_funcs[];
extern DWORD acf_browser_funcs[];
extern DWORD acf_browser_host_funcs[];
extern DWORD acf_frame_funcs[];
extern DWORD acf_menu_model_funcs[];
extern DWORD acf_menu_params_funcs[];
extern DWORD acf_request_funcs[];
extern DWORD acf_value_funcs[];
extern DWORD acf_binary_funcs[];
extern DWORD acf_dictionary_funcs[];
extern DWORD acf_list_funcs[];
extern DWORD acf_download_funcs[];
extern DWORD acf_drag_data_funcs[];
extern DWORD acf_image_funcs[];
extern DWORD acf_v8_context_funcs[];
extern DWORD acf_taskrunner_funcs[];
extern DWORD acf_v8_value_funcs[];
extern DWORD acf_v8_exception_funcs[];
extern DWORD acf_v8_stack_trace_funcs[];
extern DWORD acf_v8_stack_frame_funcs[];
extern DWORD acf_process_message_funcs[];
extern DWORD acf_request_context_funcs[];
extern DWORD acf_cookie_manager_funcs[];
extern DWORD acf_navigation_entry_funcs[];
extern DWORD acf_ssl_status_funcs[];
extern DWORD acf_post_data_funcs[];
extern DWORD acf_post_element_funcs[];
extern DWORD acf_url_request_funcs[];
extern DWORD acf_certificate_funcs[];
extern DWORD acf_certprincipal_funcs[];
extern DWORD acf_response_funcs[];
extern DWORD acf_resource_filter_funcs[];
extern DWORD acf_dom_document_funcs[];
extern DWORD acf_dom_node_funcs[];
extern DWORD acf_waitable_event_funcs[];
extern DWORD acf_ssl_info_funcs[];
extern DWORD acf_extension_funcs[];
extern DWORD acf_stream_reader_funcs[];
extern DWORD acf_stream_writer_funcs[];
extern DWORD acf_server_funcs[];
extern DWORD acf_view_funcs[];
extern DWORD acf_window_funcs[];
extern DWORD acf_panel_funcs[];
extern DWORD acf_browser_view_funcs[];

extern DWORD acf_callback_run_menu[];
extern DWORD acf_callback_download[];
extern DWORD acf_callback_download_before[];
extern DWORD acf_callback_js_dialog[];
extern DWORD acf_callback_dialog[];
extern DWORD acf_callback_auth[];
extern DWORD acf_callback_request[];
extern DWORD acf_callback_certificate[];
extern DWORD acf_callback_resource_read[];
extern DWORD acf_callback_resource_skip[];
extern DWORD acf_callback[];
extern DWORD acf_callback_v8retval[];
extern DWORD acf_callback_onpopup[];
extern DWORD acf_callback_extension_resource[];
extern DWORD acf_callback_permission[];
extern DWORD acf_callback_permissionmedia[];

ACF_EXPORTS(NewClass, void)(DWORD **pNewClass,int nType);

namespace eClass {
	void Copy(void);

	LPVOID __stdcall Alloc(int nSize);
	void __stdcall memcpy(void *dest, void *src, int size);

	LPVOID SetFunctionHookAddr(LPVOID lpSrcAddr, LPVOID lpHookAddr);

	// Module Part
	extern DWORD m_pVfCmdTable;
	extern DWORD m_pVfBrowserTable;
	extern DWORD m_pVfBrowserHostTable;
	extern DWORD m_pVfFrameTable;
	extern DWORD m_pVfRequestTable;
	extern DWORD m_pVfMenuTable;
	extern DWORD m_pVfMenuParams;
	extern DWORD m_pVfValueTable;
	extern DWORD m_pVfBinaryValueTable;
	extern DWORD m_pVfDictionaryTable;
	extern DWORD m_pVfListTable;
	extern DWORD m_pVfDownloadTable;
	extern DWORD m_pVfDragDataTable;
	extern DWORD m_pVfImageTable;
	extern DWORD m_pVfV8ContextTable;
	extern DWORD m_pVfTaskRunnerTable;
	extern DWORD m_pVfV8ValueTable;
	extern DWORD m_pVfV8ExceptionTable;
	extern DWORD m_pVfV8StackTraceTable;
	extern DWORD m_pVfV8StackFrameTable;
	extern DWORD m_pVfProcessMessageTable;
	extern DWORD m_pVfRequestContextTable;
	extern DWORD m_pVfCookieManagerTable;
	extern DWORD m_pVfNavigationEntryTable;
	extern DWORD m_pVfSSLStatusTable;
	extern DWORD m_pVfPostDataTable;
	extern DWORD m_pVfPostElementTable;
	extern DWORD m_pVfURLRequestTable;
	extern DWORD m_pVfCertificateTable;
	extern DWORD m_pVfCertPrincipalTable;
	extern DWORD m_pVfResponseTable;
	extern DWORD m_pVfResourceFilterTable;
	extern DWORD m_pVfDOMDocumentTable;
	extern DWORD m_pVfDOMNodeTable;
	extern DWORD m_pVfWaitableEventTable;
	extern DWORD m_pVfSSLInfoTable;
	extern DWORD m_pVfExtensionTable;
	extern DWORD m_pVfStreamReaderTable;
	extern DWORD m_pVfStreamWriterTable;
	extern DWORD m_pVfServerTable;
	extern DWORD m_pVfViewTable;
	extern DWORD m_pVfWindowTable;
	extern DWORD m_pVfPanelTable;
	extern DWORD m_pVfBrowserViewTable;

	// Callback Part
	extern DWORD m_pVfCallbackMenu;
	extern DWORD m_pVfCallbackDownload;
	extern DWORD m_pVfCallbackDownloadBefore;
	extern DWORD m_pVfCallbackJSDialog;
	extern DWORD m_pVfCallbackDialog;
	extern DWORD m_pVfCallbackAuth;
	extern DWORD m_pVfCallbackRequest;
	extern DWORD m_pVfCallbackCertificate;
	extern DWORD m_pVfCallbackResourceRead;
	extern DWORD m_pVfCallbackResourceSkip;
	extern DWORD m_pVfCallback;
	extern DWORD m_pVfCallbackV8RetVal;
	extern DWORD m_pVfCallbackOnPopup;
	extern DWORD m_pVfCallbackExtensionResource;
	extern DWORD m_pVfCallbackPermission;
	extern DWORD m_pVfCallbackPermissionMedia;

	// Struct Part
	extern DWORD m_infoTable;
	extern DWORD m_settingsTable;
}

// EPL Class Struct
#define IMP_NEWECLASS(LocalName, Object, Vfptr, funcs) \
	ECLASS_VFPTR LocalName##T, *LocalName##TT, **LocalName; \
	LocalName##T.dwVfTable = Vfptr; \
	LocalName##T.pObject = (LPVOID)Object; \
	LocalName##T.pCFuncs = (LPVOID)funcs; \
	LocalName##TT = &LocalName##T; \
	LocalName = &LocalName##TT;

// EPL Class Struct2
#define IMP_NEWECLASS2(LocalName, Object, Vfptr) \
	ECLASS_VFPTR2 LocalName##T, *LocalName##TT, **LocalName; \
	LocalName##T.dwVfTable = Vfptr; \
	LocalName##T.pObject = (LPVOID)Object; \
	LocalName##TT = &LocalName##T; \
	LocalName = &LocalName##TT;