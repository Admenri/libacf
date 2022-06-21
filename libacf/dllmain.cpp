// dllmain.cpp : 定义 DLL 应用程序的入口点。

#include "..\src\acf_Types.h"

#ifdef ACF_DEBUG

#include <string>
#include <sstream>

LONG CALLBACK ToLevelException(EXCEPTION_POINTERS* ExceptionInfo)
{
	std::wstringstream strTrace;
	MEMORY_BASIC_INFORMATION Infomation = {};
	WCHAR szExpCode[20];
	WCHAR szErrAddr[20];
	WCHAR szBaseAddr[20];
	WCHAR szFileName[MAX_PATH];

	wsprintf(szExpCode, TEXT("%X"), ExceptionInfo->ExceptionRecord->ExceptionCode);
	wsprintf(szErrAddr, TEXT("%X"), ExceptionInfo->ContextRecord->Eip);

	VirtualQuery((LPCVOID)ExceptionInfo->ContextRecord->Eip, &Infomation, sizeof(Infomation));
	
	wsprintf(szBaseAddr, TEXT("%X"), Infomation.AllocationBase);
	
	GetModuleFileNameW((HMODULE)Infomation.AllocationBase, szFileName, MAX_PATH);
	strTrace << "ACF Module Error occurred: \r\n" << "Exception: " << szExpCode << "\t" << "Address: " << szErrAddr << "\r\n" \
		<< "ModuleAddr: " << szBaseAddr << "\r\nModuleName: " << szFileName << "\r\n";
	
	MessageBoxW(NULL, strTrace.str().c_str(), TEXT("ACF Module Error"), MB_OK | MB_ICONHAND);
	
	return EXCEPTION_EXECUTE_HANDLER;
}

#endif

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
#ifdef ACF_DEBUG
		SetUnhandledExceptionFilter(&ToLevelException);
#endif
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
