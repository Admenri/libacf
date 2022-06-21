
#include "acf_Types.h"
#include "acf_FrameEvents.h"

#ifdef ACF_EXVER

#include "include/cef_permission.h"

ACF_EXPORTS(RegisterPermissionHandler, BOOL)(LPVOID lpCallback, BOOL copyData)
{
	CefRefPtr<ACFlibPermissionHandler> lpHandler = new ACFlibPermissionHandler(lpCallback, copyData);

	return CefRegisterPermissionHandler(lpHandler);
}

ACF_EXPORTS(ClearPermissionHandler, BOOL)()
{
	return CefClearPermissionHandler();
}

#endif