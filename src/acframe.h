#pragma once

#include "acf_Types.h"
#include "acf_App.h"
#include "acf_Client.h"
#include "acf_Task.h"

#include "include/cef_base.h"
#include "include/cef_version.h"

ACF_EXPORTS(SetAdmenriProductKey, BOOL)(LPSTR key);

ACF_EXPORTS(Version, const char*)(void) { return "Admenri Cef Framework | Admenri Copyright (C) 2021"; }

ACF_EXPORTS(ExecuteProcess, int)(LPVOID lpAppEvents, BOOL copyData);

ACF_EXPORTS(Initialize, BOOL)(PACF_BASIC_INFO lpBasicInfo, LPVOID lpAppEvents, BOOL copyData);

ACF_EXPORTS(CreateClient, LPVOID)(LPVOID lpClientEvents, BOOL copyData);

ACF_EXPORTS(ReleaseClient, void)(ACFlibClient* lpObjClient);

ACF_EXPORTS(CreateBrowser, BOOL)(ACFlibClient* lpObjClient, DWORD* window_info, LPWSTR url, DWORD* browser_settings, CefDictionaryValue* extra_info, CefRequestContext* context);

ACF_EXPORTS(CreateBrowserSync, void)(ACFlibClient* lpObjClient, DWORD* window_info, LPWSTR url, DWORD* browser_settings, CefDictionaryValue* extra_info, CefRequestContext* context, DWORD* pRetVal);

ACF_EXPORTS(GetBrowserObject, void)(ACFlibClient* lpObjClient, HWND hWnd, DWORD* pRetVal);

ACF_EXPORTS(GetBrowserObjectAt, void)(ACFlibClient* lpObjClient, int index, DWORD* pRetVal);

ACF_EXPORTS(GetBrowserObjectId, void)(ACFlibClient* lpObjClient, int identity, DWORD* pRetVal);

ACF_EXPORTS(GetBrowserCount, int)(ACFlibClient* lpObjClient);

ACF_EXPORTS(NewWindowInfo, LPVOID)();

ACF_EXPORTS(DelWindowInfo, void)(LPVOID object);

ACF_EXPORTS(NewBrowserSettings, LPVOID)(void);

ACF_EXPORTS(DelBrowserSettings, void)(LPVOID object);

ACF_EXPORTS(SetBrowserSettingsState, void)(LPVOID object, int index, cef_state_t value);

ACF_EXPORTS(SetBrowserSettingsStr, void)(LPVOID object, int index, LPWSTR value);

ACF_EXPORTS(SetBrowserSettingsInt, void)(LPVOID object, int index, int value);

ACF_EXPORTS(SetWindowInfoChild, void)(LPVOID object, HWND parent, int x, int y, int nWidth, int nHeight);

ACF_EXPORTS(SetWindowInfoPopup, void)(LPVOID object, HWND parent, LPWSTR name);

ACF_EXPORTS(SetWindowInfoWindowless, void)(LPVOID object, HWND parent, bool shared_texture);

ACF_EXPORTS(SetWindowInfoStruct, void)(LPVOID object, PACF_WINDOWINFO pInfo);

ACF_EXPORTS(RunMessageLoop, void)();

ACF_EXPORTS(QuitMessageLoop, void)();

ACF_EXPORTS(DoMessageLoopWork, void)();

ACF_EXPORTS(EnableHighDPISupport, void)();

ACF_EXPORTS(SetOSModalLoop, void)(bool modal);

ACF_EXPORTS(Shutdown, void)();

ACF_EXPORTS(AddRef, void)(LPVOID object, int nType);

ACF_EXPORTS(Release, void)(LPVOID object,int nType);

ACF_EXPORTS(RegisterWidevineCdm, void)(LPWSTR path);

ACF_EXPORTS(AddEvents, void)(HWND hWnd, WINDOW_EVENT_TYPE nType, LPVOID lpfnEventCallback);

ACF_EXPORTS(CurrentlyOn, BOOL)(CefThreadId tid);

ACF_EXPORTS(PostTask, void)(CefThreadId tid, LPFN_POST_TASK func, int lParam1, int lParam2, int lParam3);

ACF_EXPORTS(PostDelayedTask, void)(CefThreadId tid, LPFN_POST_TASK func, int64 ms, int lParam1, int lParam2, int lParam3);
