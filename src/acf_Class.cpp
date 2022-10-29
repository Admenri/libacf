
#include "acf_Class.h"

namespace eClass {
	DWORD m_pVfCmdTable;
	DWORD m_pVfBrowserTable;
	DWORD m_pVfBrowserHostTable;
	DWORD m_pVfFrameTable;
	DWORD m_pVfRequestTable;
	DWORD m_pVfMenuTable;
	DWORD m_pVfMenuParams;
	DWORD m_pVfValueTable;
	DWORD m_pVfBinaryValueTable;
	DWORD m_pVfDictionaryTable;
	DWORD m_pVfListTable;
	DWORD m_pVfDownloadTable;
	DWORD m_pVfDragDataTable;
	DWORD m_pVfImageTable;
	DWORD m_pVfV8ContextTable;
	DWORD m_pVfTaskRunnerTable;
	DWORD m_pVfV8ValueTable;
	DWORD m_pVfV8ExceptionTable;
	DWORD m_pVfV8StackTraceTable;
	DWORD m_pVfV8StackFrameTable;
	DWORD m_pVfProcessMessageTable;
	DWORD m_pVfRequestContextTable;
	DWORD m_pVfCookieManagerTable;
	DWORD m_pVfNavigationEntryTable;
	DWORD m_pVfSSLStatusTable;
	DWORD m_pVfPostDataTable;
	DWORD m_pVfPostElementTable;
	DWORD m_pVfURLRequestTable;
	DWORD m_pVfCertificateTable;
	DWORD m_pVfCertPrincipalTable;
	DWORD m_pVfResponseTable;
	DWORD m_pVfResourceFilterTable;
	DWORD m_pVfDOMDocumentTable;
	DWORD m_pVfDOMNodeTable;
	DWORD m_pVfWaitableEventTable;
	DWORD m_pVfSSLInfoTable;
	DWORD m_pVfExtensionTable;
	DWORD m_pVfStreamReaderTable;
	DWORD m_pVfStreamWriterTable;
	DWORD m_pVfServerTable;
	DWORD m_pVfViewTable;
	DWORD m_pVfWindowTable;
	DWORD m_pVfPanelTable;
	DWORD m_pVfBrowserViewTable;

	DWORD m_pVfCallbackMenu;
	DWORD m_pVfCallbackDownload;
	DWORD m_pVfCallbackDownloadBefore;
	DWORD m_pVfCallbackJSDialog;
	DWORD m_pVfCallbackDialog;
	DWORD m_pVfCallbackAuth;
	DWORD m_pVfCallbackRequest;
	DWORD m_pVfCallbackCertificate;
	DWORD m_pVfCallbackResourceRead;
	DWORD m_pVfCallbackResourceSkip;
	DWORD m_pVfCallback;
	DWORD m_pVfCallbackV8RetVal;
	DWORD m_pVfCallbackOnPopup;
	DWORD m_pVfCallbackExtensionResource;
	DWORD m_pVfCallbackPermission;
	DWORD m_pVfCallbackPermissionMedia;

	DWORD m_infoTable;
	DWORD m_settingsTable;
}

ACF_EXPORTS(NewClass, void)(DWORD **pNewClass, int nType)
{
	DWORD dwVfptr = **pNewClass;
	if (dwVfptr != NULL)
	{
		switch (nType)
		{
		case 10000:
			eClass::m_pVfCmdTable = dwVfptr;
			break;
		case 10001:
			eClass::m_pVfBrowserTable = dwVfptr;
			break;
		case 10002:
			eClass::m_pVfBrowserHostTable = dwVfptr;
			break;
		case 10003:
			eClass::m_pVfFrameTable = dwVfptr;
			break;
		case 10004:
			eClass::m_pVfMenuTable = dwVfptr;
			break;
		case 10005:
			eClass::m_pVfMenuParams = dwVfptr;
			break;
		case 10006:
			eClass::m_pVfRequestTable = dwVfptr;
			break;
		case 10007:
			eClass::m_pVfValueTable = dwVfptr;
			break;
		case 10008:
			eClass::m_pVfBinaryValueTable = dwVfptr;
			break;
		case 10009:
			eClass::m_pVfDictionaryTable = dwVfptr;
			break;
		case 10010:
			eClass::m_pVfListTable = dwVfptr;
			break;
		case 10011:
			eClass::m_pVfDownloadTable = dwVfptr;
			break;
		case 10012:
			eClass::m_pVfDragDataTable = dwVfptr;
			break;
		case 10013:
			eClass::m_pVfImageTable = dwVfptr;
			break;
		case 10014:
			eClass::m_pVfV8ContextTable = dwVfptr;
			break;
		case 10015:
			eClass::m_pVfTaskRunnerTable = dwVfptr;
			break;
		case 10016:
			eClass::m_pVfV8ValueTable = dwVfptr;
			break;
		case 10017:
			eClass::m_pVfV8ExceptionTable = dwVfptr;
			break;
		case 10018:
			eClass::m_pVfV8StackTraceTable = dwVfptr;
			break;
		case 10019:
			eClass::m_pVfV8StackFrameTable = dwVfptr;
			break;
		case 10020:
			eClass::m_pVfProcessMessageTable = dwVfptr;
			break;
		case 10021:
			eClass::m_pVfRequestContextTable = dwVfptr;
			break;
		case 10022:
			eClass::m_pVfCookieManagerTable = dwVfptr;
			break;
		case 10023:
			eClass::m_pVfNavigationEntryTable = dwVfptr;
			break;
		case 10024:
			eClass::m_pVfSSLStatusTable = dwVfptr;
			break;
		case 10025:
			eClass::m_pVfPostDataTable = dwVfptr;
			break;
		case 10026:
			eClass::m_pVfPostElementTable = dwVfptr;
			break;
		case 10027:
			eClass::m_pVfURLRequestTable = dwVfptr;
			break;
		case 10028:
			eClass::m_pVfCertificateTable = dwVfptr;
			break;
		case 10029:
			eClass::m_pVfCertPrincipalTable = dwVfptr;
			break;
		case 10030:
			eClass::m_pVfResponseTable = dwVfptr;
			break;
		case 10031:
			eClass::m_pVfResourceFilterTable = dwVfptr;
			break;
		case 10032:
			eClass::m_pVfDOMDocumentTable = dwVfptr;
			break;
		case 10033:
			eClass::m_pVfDOMNodeTable = dwVfptr;
			break;
		case 10034:
			eClass::m_pVfWaitableEventTable = dwVfptr;
			break;
		case 10035:
			eClass::m_pVfSSLInfoTable = dwVfptr;
			break;
		case 10036:
			eClass::m_pVfExtensionTable = dwVfptr;
			break;
		case 10037:
			eClass::m_pVfStreamReaderTable = dwVfptr;
			break;
		case 10038:
			eClass::m_pVfStreamWriterTable = dwVfptr;
			break;
		case 10039:
			eClass::m_pVfServerTable = dwVfptr;
			break;
		case 10040:
			eClass::m_pVfViewTable = dwVfptr;
			break;
		case 10041:
			eClass::m_pVfWindowTable = dwVfptr;
			break;
		case 10042:
			eClass::m_pVfPanelTable = dwVfptr;
			break;
		case 10043:
			eClass::m_pVfBrowserViewTable = dwVfptr;
			break;


		case 20000:
			eClass::m_infoTable = dwVfptr;
			return;
		case 20001:
			eClass::m_settingsTable = dwVfptr;
			return;


		case 30000:
			eClass::m_pVfCallbackMenu = dwVfptr;
			break;
		case 30001:
			eClass::m_pVfCallbackDownload = dwVfptr;
			break;
		case 30002:
			eClass::m_pVfCallbackDownloadBefore = dwVfptr;
			break;
		case 30003:
			eClass::m_pVfCallbackJSDialog = dwVfptr;
			break;
		case 30004:
			eClass::m_pVfCallbackDialog = dwVfptr;
			break;
		case 30005:
			eClass::m_pVfCallbackAuth = dwVfptr;
			break;
		case 30006:
			eClass::m_pVfCallbackRequest = dwVfptr;
			break;
		case 30007:
			eClass::m_pVfCallbackCertificate = dwVfptr;
			break;
		case 30008:
			eClass::m_pVfCallbackResourceRead = dwVfptr;
			break;
		case 30009:
			eClass::m_pVfCallbackResourceSkip = dwVfptr;
			break;
		case 30010:
			eClass::m_pVfCallback = dwVfptr;
			break;
		case 30011:
			eClass::m_pVfCallbackV8RetVal = dwVfptr;
			break;
		case 30012:
			eClass::m_pVfCallbackOnPopup = dwVfptr;
			break;
		case 30013:
			eClass::m_pVfCallbackExtensionResource = dwVfptr;
			break;
		case 30014:
			eClass::m_pVfCallbackPermissionMedia = dwVfptr;
			break;
		case 30015:
			eClass::m_pVfCallbackPermission = dwVfptr;
			break;

		default:
			break;
		}
		dwVfptr += sizeof(DWORD);
		DWORD dwSrcAddr = *(DWORD*)dwVfptr;
		dwSrcAddr += 6;
		BYTE* pCoder = (BYTE*)dwSrcAddr;
		if (*pCoder != 0xE9) eClass::SetFunctionHookAddr((LPVOID)dwSrcAddr, eClass::Copy);
	}
}

__declspec(naked) void eClass::Copy(void)
{
	__asm {
		mov esi, [esp];
		call Alloc;
		mov edi, eax;
		pop ecx;
		xchg ecx, esi;
		push ecx;
		push esi;
		push edi;
		call memcpy;
		push edi;
		lea eax, [esp];
		push esi;
		push eax;
		call[ebx + 8];
		pop eax;
		retn;
	}
}

LPVOID eClass::SetFunctionHookAddr(LPVOID lpSrcAddr, LPVOID lpHookAddr)
{
	DWORD dwOldProtect;
	char* lSrcAddr = (char*)lpSrcAddr;
	ULONG nOffset = (*(ULONG*)& lSrcAddr[1]);
	ULONG pAddr = (DWORD)lpSrcAddr + nOffset;
	pAddr += 5;
	LPVOID lpSrcFunction = (LPVOID)pAddr;
	DWORD dwOffset = (DWORD)lpSrcAddr - (DWORD)lpHookAddr;
	dwOffset = ~dwOffset;
	dwOffset -= 4;
	if (VirtualProtectEx((HANDLE)-1, lSrcAddr, 5, PAGE_EXECUTE_READWRITE, &dwOldProtect))
	{
		lSrcAddr[0] = 0xE9;
		*(DWORD*)& lSrcAddr[1] = dwOffset;
		VirtualProtectEx((HANDLE)-1, lSrcAddr, 5, dwOldProtect, NULL);
	}
	return lpSrcFunction;
}

LPVOID __stdcall eClass::Alloc(int nSize)
{
	return HeapAlloc(GetProcessHeap(), 0, nSize);
}

void __stdcall eClass::memcpy(void *dest, void *src, int size)
{
	::memcpy(dest, src, size);
}