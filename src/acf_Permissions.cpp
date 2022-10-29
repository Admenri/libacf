
#include "acf_Types.h"

#include "include/cef_permission_handler.h"

extern DWORD acf_callback_permissionmedia[];
extern DWORD acf_callback_permission[];

void ECALL permissioncb_continue_media(CefMediaAccessCallback* obj, uint32 options)
{
  ISVALID(obj);

  obj->Continue(options);
}

void ECALL permissioncb_cancel_media(CefMediaAccessCallback* obj)
{
  ISVALID(obj);

  obj->Cancel();
}

DWORD acf_callback_permissionmedia[] = {
  (DWORD)&permissioncb_continue_media,
  (DWORD)&permissioncb_cancel_media,
};

void ECALL permissioncb_continue(CefPermissionPromptCallback* callback, cef_permission_request_result_t result)
{
  ISVALID(callback);
  callback->Continue(result);
}

DWORD acf_callback_permission[] = {
  (DWORD)&permissioncb_continue,
};
