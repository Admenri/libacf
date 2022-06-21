#pragma once

#include <windows.h>
#include <list>

#include "include/internal/cef_time.h"
#include "include/internal/cef_types_wrappers.h"

#define ACF_EXPORTS(name, type) extern "C" __declspec(dllexport) type __cdecl acf##name
#define ISVALID(v) if (!v) return;
#define ISVALIDR(v, r) if (!v) return r;
#define ECALL __stdcall

//基础设置信息结构
typedef struct _acf_basic_info {
	BOOL no_sandbox;
	LPWSTR browser_subprocess_path;
	BOOL chrome_runtime;
	BOOL multi_threaded_message_loop;
	BOOL external_message_pump;
	BOOL windowless_rendering_enabled;
	BOOL command_line_args_disabled;
	LPWSTR cache_path;
	LPWSTR root_cache_path;
	LPWSTR user_data_path;
	BOOL persist_session_cookies;
	BOOL persist_user_preferences;
	LPWSTR user_agent;
	LPWSTR product_version;
	LPWSTR locale;
	LPWSTR log_file;
	int log_severity;
	LPWSTR javascript_flags;
	LPWSTR resources_dir_path;
	LPWSTR locales_dir_path;
	BOOL pack_loading_disabled;
	int remote_debugging_port;
	int uncaught_exception_stack_size;
	BOOL ignore_certificate_errors;
	unsigned int background_color;
	LPWSTR accept_language_list;
	LPWSTR application_client_id_for_file_scanning;
} ACF_BASIC_INFO, *PACF_BASIC_INFO;

//易语言类虚表结构
typedef struct _eclass_vfptr{
	DWORD dwVfTable;
	LPVOID pObject;
	LPVOID pCFuncs;
} ECLASS_VFPTR, *PECLASS_VFPTR;

//易语言类虚表结构2
typedef struct _eclass_vfptr2 {
	DWORD dwVfTable;
	LPVOID pObject;
} ECLASS_VFPTR2, * PECLASS_VFPTR2;

//控件事件列表
typedef enum _window_event_type {
	WET_KEYDOWN = 0x100,
	WET_KEYUP = 0x101,
	WET_CHAR = 0x102,
	WET_MOUSEMOVE = 0x200,
	WET_LBUTTONDOWN = 0x201,
	WET_LBUTTONUP = 0x202,
	WET_LBUTTONDBLCLK = 0x203,
	WET_RBUTTONDOWN = 0x0204,
	WET_RBUTTONUP = 0x0205,
} WINDOW_EVENT_TYPE;

//控件消息接管
typedef struct _window_event_callback {
	WNDPROC lpfnPrevWndFunc;
	HWND hWnd;
	WINDOW_EVENT_TYPE nType;
	LPVOID lpfnEventCallback;
} WINDOW_EVENT_CALLBACK;

typedef struct _acf_screen_info_t {
	float device_scale_factor;
	int depth;
	int depth_per_component;
	int is_monochrome;
	int rect_x;
	int rect_y;
	int rect_width;
	int rect_height;
	int available_rect_x;
	int available_rect_y;
	int available_rect_width;
	int available_rect_height;
} ACF_SCREEN_INFO, *PACF_SCREEN_INFO;

typedef struct _acf_cursor_info_t {
	int x;
	int y;
	float scale;
	int buffer;
	int width;
	int height;
} ACF_CURSOR_INFO, *PACF_CURSOR_INFO;

typedef struct _acf_drag_region_t {
	int x;
	int y;
	int width;
	int height;
	bool draggable;
} ACF_DRAG_REGION, *PACF_DRAG_REGION;

typedef struct _acf_web_plugin_info_t {
	LPBYTE name;
	LPBYTE path;
	LPBYTE version;
	LPBYTE description;
} ACF_WEB_PLUGIN_INFO, *PACF_WEB_PLUGIN_INFO;

typedef struct _acf_cookie_t {
	LPBYTE name;
	LPBYTE value;
	LPBYTE domain;
	LPBYTE path;
	BOOL secure;
	BOOL httponly;
	cef_time_t* creation;
	cef_time_t* last_access;
	BOOL has_expires;
	cef_time_t* expires;
	int same_site;
	int priority;
} ACF_COOKIE, *PACF_COOKIE;

typedef struct	_acf_request_context_settings_t {
	LPWSTR cache_path;
	BOOL persist_session_cookies;
	BOOL persist_user_preferences;
	BOOL ignore_cert_error;
	LPWSTR accept_language_list;
} ACF_REQUEST_CONTEXT_SETTINGS, *PACF_REQUEST_CONTEXT_SETTINGS;

typedef struct _acf_composition_underline_t {
	int from;
	int to;
	int color;
	int bgcolor;
	bool thick;
	int style;
} ACF_COMPOSITION_UNDERLINE, *PACF_COMPOSITION_UNDERLINE;

typedef struct _acf_string_pair_t {
	LPBYTE key;
	LPBYTE value;
} ACF_STRING_PAIR, *PACF_STRING_PAIR;

typedef struct _acf_MSG_t {
	int          hwnd;
	int          message;
	int          wParam;
	int          lParam;
	int          time;
	cef_point_t* pt;
} ACF_MSG, *PACF_MSG;

typedef struct _acf_window_info_t {
	int ex_style;
	LPWSTR window_name;
	int style;
	int x;
	int y;
	int width;
	int height;
	int parent_window;
	int menu;

	BOOL windowless_rendering_enabled;
	BOOL shared_texture_enabled;
	BOOL external_begin_frame_enabled;

	int window;
} ACF_WINDOWINFO, *PACF_WINDOWINFO;

typedef void(CALLBACK* LPFN_POST_TASK)(int, int, int);
typedef std::list<WINDOW_EVENT_CALLBACK> WindowEventCallback;