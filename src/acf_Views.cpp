
#include "acf_Conv.h"
#include "acf_Types.h"
#include "acf_FrameEvents.h"
#include "acf_Client.h"

#include "include/views/cef_view.h"
#include "include/views/cef_view_delegate.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_button.h"
#include "include/views/cef_panel.h"
#include "include/views/cef_scroll_view.h"
#include "include/views/cef_textfield.h"
#include "include/views/cef_window.h"

extern DWORD acf_image_funcs[];
extern DWORD acf_browser_funcs[];

extern DWORD acf_panel_funcs[];
extern DWORD acf_view_funcs[];
extern DWORD acf_window_funcs[];
extern DWORD acf_browser_view_funcs[];

bool ECALL view_as_browser_view(CefView* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefBrowserView> dupObj = obj->AsBrowserView();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_browser_view_funcs;

	return !!dupObj;
}

bool ECALL view_as_button(CefView* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefButton> dupObj = obj->AsButton();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)NULL;

	return !!dupObj;
}

bool ECALL view_as_panel(CefView* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefPanel> dupObj = obj->AsPanel();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_view_funcs;

	return !!dupObj;
}

bool ECALL view_as_scroll_view(CefView* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefScrollView> dupObj = obj->AsScrollView();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_browser_view_funcs;

	return !!dupObj;
}

bool ECALL view_as_text_field(CefView* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefTextfield> dupObj = obj->AsTextfield();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_browser_view_funcs;

	return !!dupObj;
}

BOOL ECALL view_get_type_string(CefView* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetTypeString().c_str());

	return !!str;
}

BOOL ECALL view_to_string(CefView* obj, bool includeChild, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->ToString(includeChild).c_str());

	return !!str;
}

bool ECALL view_is_valid(CefView* obj)
{
	ISVALIDR(obj, false);

	return obj->IsValid();
}

bool ECALL view_is_attached(CefView* obj)
{
	ISVALIDR(obj, false);

	return obj->IsAttached();
}

bool ECALL view_is_same(CefView* obj, CefView* that)
{
	ISVALIDR(obj, false);

	return obj->IsSame(that);
}

LPVOID ECALL view_get_delegate(CefView* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetDelegate().get();
}

bool ECALL view_get_window(CefView* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefWindow> dupObj = obj->GetWindow();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_window_funcs;

	return !!dupObj;
}

int ECALL view_get_id(CefView* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetID();
}

void ECALL view_set_id(CefView* obj, int id)
{
	ISVALID(obj);

	obj->SetID(id);
}

int ECALL view_get_group_id(CefView* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetGroupID();
}

void ECALL view_set_group_id(CefView* obj, int id)
{
	ISVALID(obj);

	obj->SetGroupID(id);
}

bool ECALL view_get_parent_view(CefView* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefView> dupObj = obj->GetParentView();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_view_funcs;

	return !!dupObj;
}

bool ECALL view_get_view_for_id(CefView* obj, int id, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefView> dupObj = obj->GetViewForID(id);

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_view_funcs;

	return !!dupObj;
}

void ECALL view_set_bounds(CefView* obj, cef_rect_t** prect)
{
	ISVALID(obj);

	obj->SetBounds(**prect);
}

void ECALL view_get_bounds(CefView* obj, cef_rect_t** prect)
{
	ISVALID(obj);

	auto rt = obj->GetBounds();
	(*prect)->x = rt.x;
	(*prect)->y = rt.y;
	(*prect)->width = rt.width;
	(*prect)->height = rt.height;
}

void ECALL view_get_bounds_in_screen(CefView* obj, cef_rect_t** prect)
{
	ISVALID(obj);

	auto rt = obj->GetBoundsInScreen();
	(*prect)->x = rt.x;
	(*prect)->y = rt.y;
	(*prect)->width = rt.width;
	(*prect)->height = rt.height;
}

void ECALL view_set_size(CefView* obj, cef_rect_t** prect)
{
	ISVALID(obj);

	CefSize sz((*prect)->width, (*prect)->height);

	obj->SetSize(sz);
}

void ECALL view_get_size(CefView* obj, cef_rect_t** prect)
{
	ISVALID(obj);

	auto rt = obj->GetSize();
	(*prect)->width = rt.width;
	(*prect)->height = rt.height;
}

void ECALL view_set_position(CefView* obj, cef_rect_t** prect)
{
	ISVALID(obj);

	CefPoint sz((*prect)->x, (*prect)->y);

	obj->SetPosition(sz);
}

void ECALL view_get_position(CefView* obj, cef_rect_t** prect)
{
	ISVALID(obj);

	auto rt = obj->GetPosition();
	(*prect)->x = rt.x;
	(*prect)->y = rt.y;
}

void ECALL view_set_insets(CefView* obj, cef_insets_t** prect)
{
	ISVALID(obj);

	obj->SetInsets(**prect);
}

void ECALL view_get_insets(CefView* obj, cef_rect_t** prect)
{
	ISVALID(obj);

	auto rt = obj->GetInsets();
	(*prect)->x = rt.left;
	(*prect)->y = rt.top;
	(*prect)->width = rt.right;
	(*prect)->height = rt.bottom;
}

void ECALL view_get_preferred_size(CefView* obj, cef_rect_t** prect)
{
	ISVALID(obj);

	auto rt = obj->GetPreferredSize();
	(*prect)->width = rt.width;
	(*prect)->height = rt.height;
}

void ECALL view_size_to_preferred_size(CefView* obj)
{
	ISVALID(obj);

	obj->SizeToPreferredSize();
}

void ECALL view_get_minimum_size(CefView* obj, cef_rect_t** prect)
{
	ISVALID(obj);

	auto rt = obj->GetMinimumSize();
	(*prect)->width = rt.width;
	(*prect)->height = rt.height;
}

void ECALL view_get_maximum_size(CefView* obj, cef_rect_t** prect)
{
	ISVALID(obj);

	auto rt = obj->GetMaximumSize();
	(*prect)->width = rt.width;
	(*prect)->height = rt.height;
}

int ECALL view_get_height_for_width(CefView* obj, int width)
{
	ISVALIDR(obj, NULL);

	return obj->GetHeightForWidth(width);
}

void ECALL view_invalidate_layout(CefView* obj)
{
	ISVALID(obj);

	obj->InvalidateLayout();
}

void ECALL view_set_visible(CefView* obj, bool visible)
{
	ISVALID(obj);

	obj->SetVisible(visible);
}

bool ECALL view_get_visible(CefView* obj)
{
	ISVALIDR(obj, false);

	return obj->IsVisible();
}

bool ECALL view_is_drawn(CefView* obj)
{
	ISVALIDR(obj, false);

	return obj->IsDrawn();
}

void ECALL view_set_enabled(CefView* obj, bool visible)
{
	ISVALID(obj);

	obj->SetEnabled(visible);
}

bool ECALL view_is_enabled(CefView* obj)
{
	ISVALIDR(obj, false);

	return obj->IsEnabled();
}

void ECALL view_set_focusable(CefView* obj, bool focusable)
{
	ISVALID(obj);

	obj->SetFocusable(focusable);
}

bool ECALL view_is_focusable(CefView* obj)
{
	ISVALIDR(obj, false);

	return obj->IsFocusable();
}

bool ECALL view_is_accessibility_focusable(CefView* obj)
{
	ISVALIDR(obj, false);

	return obj->IsAccessibilityFocusable();
}

void ECALL view_request_focus(CefView* obj)
{
	ISVALID(obj);

	obj->RequestFocus();
}

void ECALL view_set_bgcolor(CefView* obj, int color)
{
	ISVALID(obj);

	obj->SetBackgroundColor(color);
}

bool ECALL view_convert_point_to_screen(CefView* obj, cef_rect_t** prect)
{
	ISVALIDR(obj, false);

	CefPoint point;

	bool result = obj->ConvertPointToScreen(point);

	(*prect)->x = point.x;
	(*prect)->y = point.y;

	return result;
}

bool ECALL view_convert_point_from_screen(CefView* obj, cef_rect_t** prect)
{
	ISVALIDR(obj, false);

	CefPoint point;

	bool result = obj->ConvertPointFromScreen(point);

	(*prect)->x = point.x;
	(*prect)->y = point.y;

	return result;
}

bool ECALL view_convert_point_to_window(CefView* obj, cef_rect_t** prect)
{
	ISVALIDR(obj, false);

	CefPoint point;

	bool result = obj->ConvertPointToWindow(point);

	(*prect)->x = point.x;
	(*prect)->y = point.y;

	return result;
}

bool ECALL view_convert_point_from_window(CefView* obj, cef_rect_t** prect)
{
	ISVALIDR(obj, false);

	CefPoint point;

	bool result = obj->ConvertPointFromWindow(point);

	(*prect)->x = point.x;
	(*prect)->y = point.y;

	return result;
}

bool ECALL view_convert_point_to_view(CefView* obj, CefView* view, cef_rect_t** prect)
{
	ISVALIDR(obj, false);

	CefPoint point;

	bool result = obj->ConvertPointToView(view, point);

	(*prect)->x = point.x;
	(*prect)->y = point.y;

	return result;
}

bool ECALL view_convert_point_from_view(CefView* obj, CefView* view, cef_rect_t** prect)
{
	ISVALIDR(obj, false);

	CefPoint point;

	bool result = obj->ConvertPointFromView(view, point);

	(*prect)->x = point.x;
	(*prect)->y = point.y;

	return result;
}

DWORD acf_view_funcs[] = {
	(DWORD)&view_as_browser_view,
	(DWORD)&view_as_button,
	(DWORD)&view_as_panel,
	(DWORD)&view_as_scroll_view,
	(DWORD)&view_as_text_field,
	(DWORD)&view_get_type_string,
	(DWORD)&view_to_string,
	(DWORD)&view_is_valid,
	(DWORD)&view_is_attached,
	(DWORD)&view_is_same,
	(DWORD)&view_get_delegate,
	(DWORD)&view_get_window,
	(DWORD)&view_get_id,
	(DWORD)&view_set_id,
	(DWORD)&view_get_group_id,
	(DWORD)&view_set_group_id,
	(DWORD)&view_get_parent_view,
	(DWORD)&view_get_view_for_id,
	(DWORD)&view_set_bounds,
	(DWORD)&view_get_bounds,
	(DWORD)&view_get_bounds_in_screen,
	(DWORD)&view_set_size,
	(DWORD)&view_get_size,
	(DWORD)&view_set_position,
	(DWORD)&view_get_position,
	(DWORD)&view_set_insets,
	(DWORD)&view_get_insets,
	(DWORD)&view_get_preferred_size,
	(DWORD)&view_size_to_preferred_size,
	(DWORD)&view_get_minimum_size,
	(DWORD)&view_get_maximum_size,
	(DWORD)&view_get_height_for_width,
	(DWORD)&view_invalidate_layout,
	(DWORD)&view_set_visible,
	(DWORD)&view_get_visible,
	(DWORD)&view_is_drawn,
	(DWORD)&view_set_enabled,
	(DWORD)&view_is_enabled,
	(DWORD)&view_set_focusable,
	(DWORD)&view_is_focusable,
	(DWORD)&view_is_accessibility_focusable,
	(DWORD)&view_request_focus,
	(DWORD)&view_set_bgcolor,
	(DWORD)&view_convert_point_to_screen,
	(DWORD)&view_convert_point_from_screen,
	(DWORD)&view_convert_point_to_window,
	(DWORD)&view_convert_point_from_window,
	(DWORD)&view_convert_point_to_view,
	(DWORD)&view_convert_point_from_view,
};

ACF_EXPORTS(WindowCreate, BOOL)(DWORD* target, LPVOID callback, bool copy)
{
	CefRefPtr<ACFlibWindowDelegate> lpHandler = callback ? new ACFlibWindowDelegate(callback, copy) : nullptr;

	CefRefPtr<CefWindow> lpObj = CefWindow::CreateTopLevelWindow(lpHandler);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_window_funcs;

	return !!lpObj;
}

template<class T>
void ECALL parent_to_view(T* obj, DWORD* target)
{
	CefRefPtr<CefView> pBrowser = dynamic_cast<CefView*>(obj);

	pBrowser->AddRef();
	target[1] = (DWORD)((LPVOID)pBrowser.get());
	target[2] = (DWORD)acf_view_funcs;
}

template<class T>
void ECALL parent_to_panel(T* obj, DWORD* target)
{
	CefRefPtr<CefPanel> pBrowser = dynamic_cast<CefPanel*>(obj);

	pBrowser->AddRef();
	target[1] = (DWORD)((LPVOID)pBrowser.get());
	target[2] = (DWORD)acf_panel_funcs;
}

void ECALL window_show(CefWindow* obj)
{
	ISVALID(obj);

	obj->Show();
}

void ECALL window_hide(CefWindow* obj)
{
	ISVALID(obj);

	obj->Hide();
}

void ECALL window_center(CefWindow* obj, cef_rect_t** prect)
{
	ISVALID(obj);
	CefSize sz((*prect)->width, (*prect)->height);
	obj->CenterWindow(sz);
}

void ECALL window_close(CefWindow* obj)
{
	ISVALID(obj);

	obj->Close();
}

bool ECALL window_is_closed(CefWindow* obj)
{
	ISVALIDR(obj, false);

	return obj->IsClosed();
}

void ECALL window_activate(CefWindow* obj)
{
	ISVALID(obj);

	obj->Activate();
}

void ECALL window_deactivate(CefWindow* obj)
{
	ISVALID(obj);

	obj->Deactivate();
}

bool ECALL window_is_active(CefWindow* obj)
{
	ISVALIDR(obj, false);

	return obj->IsActive();
}

void ECALL window_bring_to_top(CefWindow* obj)
{
	ISVALID(obj);

	obj->BringToTop();
}

void ECALL window_set_on_top(CefWindow* obj, bool allow)
{
	ISVALID(obj);

	obj->SetAlwaysOnTop(allow);
}

void ECALL window_maximum(CefWindow* obj)
{
	ISVALID(obj);

	obj->Maximize();
}

void ECALL window_minimum(CefWindow* obj)
{
	ISVALID(obj);

	obj->Minimize();
}

void ECALL window_restore(CefWindow* obj)
{
	ISVALID(obj);

	obj->Restore();
}

void ECALL window_set_fullscreen(CefWindow* obj, bool fullscreen)
{
	ISVALID(obj);

	obj->SetFullscreen(fullscreen);
}

bool ECALL window_is_maximized(CefWindow* obj)
{
	ISVALIDR(obj, false);

	return obj->IsMaximized();
}

bool ECALL window_is_minimized(CefWindow* obj)
{
	ISVALIDR(obj, false);

	return obj->IsMinimized();
}

bool ECALL window_is_fullscreen(CefWindow* obj)
{
	ISVALIDR(obj, false);

	return obj->IsFullscreen();
}

void ECALL window_set_title(CefWindow* obj, LPWSTR str)
{
	ISVALID(obj);

	obj->SetTitle(str);
}

bool ECALL window_get_title(CefWindow* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetTitle().c_str());

	return !!ansi_str;
}

void ECALL window_set_icon(CefWindow* obj, CefImage* image)
{
	ISVALID(obj);

	obj->SetWindowIcon(image);
}

bool ECALL window_get_icon(CefWindow* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefImage> lpObj = obj->GetWindowIcon();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_image_funcs;

	return !!lpObj;
}

void ECALL window_set_app_icon(CefWindow* obj, CefImage* image)
{
	ISVALID(obj);

	obj->SetWindowAppIcon(image);
}

bool ECALL window_get_app_icon(CefWindow* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefImage> lpObj = obj->GetWindowAppIcon();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_image_funcs;

	return !!lpObj;
}

int ECALL window_add_overlay_view(CefWindow* window, CefView* view, cef_docking_mode_t mode, DWORD* result)
{
	ISVALIDR(window, 0);

	CefRefPtr<CefOverlayController> lpObj = window->AddOverlayView(view, mode);

	result[1] = (DWORD)((LPVOID)lpObj.get());
	result[2] = (DWORD)NULL;

	return !!lpObj;
}

void ECALL window_show_menu(CefWindow* obj, CefMenuModel* model, cef_rect_t** rect, cef_menu_anchor_position_t pos)
{
	ISVALID(obj);

	CefPoint pt((*rect)->x, (*rect)->y);

	obj->ShowMenu(model, pt, pos);
}

void ECALL window_cancel_menu(CefWindow* obj)
{
	ISVALID(obj);

	obj->CancelMenu();
}

int ECALL window_get_display(CefWindow* window, DWORD* result)
{
	ISVALIDR(window, 0);

	CefRefPtr<CefDisplay> lpObj = window->GetDisplay();

	result[1] = (DWORD)((LPVOID)lpObj.get());
	result[2] = (DWORD)NULL;

	return !!lpObj;
}

void ECALL window_get_client_area(CefWindow* obj, cef_rect_t** rect)
{
	ISVALID(obj);

	auto sz = obj->GetClientAreaBoundsInScreen();

	(*rect)->x = sz.x;
	(*rect)->y = sz.y;
	(*rect)->width = sz.width;
	(*rect)->height = sz.height;
}

void ECALL window_set_draggable_regions(CefWindow* obj, LPVOID* eArray)
{
	ISVALID(obj);

	LPSTR pData = ((LPSTR)*eArray) + sizeof(INT) * 2;
	ACF_DRAG_REGION* pList = reinterpret_cast<decltype(pList)>(pData);
	int size = *((LPINT)(((LPSTR)*eArray) + sizeof(INT)));

	std::vector<CefDraggableRegion> pArgs;
	for (size_t i = 0; i < size; i++)
	{
		cef_draggable_region_t tmp;
		tmp.bounds.x = pList[i].x;
		tmp.bounds.y = pList[i].y;
		tmp.bounds.width = pList[i].width;
		tmp.bounds.height = pList[i].height;
		tmp.draggable = pList[i].draggable;
		pArgs.push_back(tmp);
	}

	obj->SetDraggableRegions(pArgs);
}

HWND ECALL window_get_handle(CefWindow* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetWindowHandle();
}

void ECALL window_send_key_press(CefWindow* obj, int code, int flags)
{
	ISVALID(obj);

	obj->SendKeyPress(code, flags);
}

void ECALL window_send_mouse_move(CefWindow* obj, int x, int y)
{
	ISVALID(obj);

	obj->SendMouseMove(x, y);
}

void ECALL window_send_mouse_events(CefWindow* obj, cef_mouse_button_type_t button, bool down, bool up)
{
	ISVALID(obj);

	obj->SendMouseEvents(button, down, up);
}

void ECALL window_set_accelerator(CefWindow* obj, int cid, int code, bool shift, bool ctrl, bool alt)
{
	ISVALID(obj);

	obj->SetAccelerator(cid, code, shift, ctrl, alt);
}

void ECALL window_remove_accelerator(CefWindow* obj, int cid)
{
	ISVALID(obj);

	obj->RemoveAccelerator(cid);
}

void ECALL window_remove_all_accelerators(CefWindow* obj)
{
	ISVALID(obj);
	
	obj->RemoveAllAccelerators();
}

DWORD acf_window_funcs[] = {
	(DWORD)&parent_to_view<CefWindow>,
	(DWORD)&parent_to_panel<CefWindow>,
	(DWORD)&window_show,
	(DWORD)&window_hide,
	(DWORD)&window_center,
	(DWORD)&window_close,
	(DWORD)&window_is_closed,
	(DWORD)&window_activate,
	(DWORD)&window_deactivate,
	(DWORD)&window_is_active,
	(DWORD)&window_bring_to_top,
	(DWORD)&window_set_on_top,
	(DWORD)&window_maximum,
	(DWORD)&window_minimum,
	(DWORD)&window_restore,
	(DWORD)&window_set_fullscreen,
	(DWORD)&window_is_maximized,
	(DWORD)&window_is_minimized,
	(DWORD)&window_is_fullscreen,
	(DWORD)&window_set_title,
	(DWORD)&window_get_title,
	(DWORD)&window_set_icon,
	(DWORD)&window_get_icon,
	(DWORD)&window_set_app_icon,
	(DWORD)&window_get_app_icon,
	(DWORD)&window_add_overlay_view,
	(DWORD)&window_show_menu,
	(DWORD)&window_cancel_menu,
	(DWORD)&window_get_display,
	(DWORD)&window_get_client_area,
	(DWORD)&window_set_draggable_regions,
	(DWORD)&window_get_handle,
	(DWORD)&window_send_key_press,
	(DWORD)&window_send_mouse_move,
	(DWORD)&window_send_mouse_events,
	(DWORD)&window_set_accelerator,
	(DWORD)&window_remove_accelerator,
	(DWORD)&window_remove_all_accelerators,
};

ACF_EXPORTS(PanelCreate, BOOL)(DWORD* target, LPVOID callback, bool copy)
{
	CefRefPtr<ACFlibPanelDelegate> lpHandler = callback ? new ACFlibPanelDelegate(callback, copy) : nullptr;

	CefRefPtr<CefPanel> lpObj = CefPanel::CreatePanel(dynamic_cast<CefPanelDelegate*>(lpHandler.get()));

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_panel_funcs;

	return !!lpObj;
}

bool ECALL panel_as_window(CefPanel* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefWindow> dupObj = obj->AsWindow();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_window_funcs;

	return !!dupObj;
}

void ECALL panel_layout(CefPanel* obj)
{
	ISVALID(obj);

	obj->Layout();
}

void ECALL panel_add_child_view(CefPanel* obj, CefView* child)
{
	ISVALID(obj);

	obj->AddChildView(child);
}

void ECALL panel_add_child_view_at(CefPanel* obj, CefView* child, int index)
{
	ISVALID(obj);

	obj->AddChildViewAt(child, index);
}

void ECALL panel_reorder_child_view(CefPanel* obj, CefView* child, int index)
{
	ISVALID(obj);

	obj->ReorderChildView(child, index);
}

void ECALL panel_remove_child_view(CefPanel* obj, CefView* child)
{
	ISVALID(obj);

	obj->RemoveChildView(child);
}

void ECALL panel_remove_all_child_views(CefPanel* obj)
{
	ISVALID(obj);

	obj->RemoveAllChildViews();
}

int ECALL panel_get_child_view_count(CefPanel* obj)
{
	ISVALIDR(obj, 0);

	return obj->GetChildViewCount();
}

bool ECALL panel_get_child_view_at(CefPanel* obj, int index, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefView> lpObj = obj->GetChildViewAt(index);

	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_view_funcs;

	return !!lpObj;
}

DWORD acf_panel_funcs[] = {
	(DWORD)&parent_to_view<CefPanel>,
	(DWORD)&panel_as_window,
	(DWORD)&panel_layout,
	(DWORD)&panel_add_child_view,
	(DWORD)&panel_add_child_view_at,
	(DWORD)&panel_reorder_child_view,
	(DWORD)&panel_remove_child_view,
	(DWORD)&panel_remove_all_child_views,
	(DWORD)&panel_get_child_view_count,
	(DWORD)&panel_get_child_view_at,
};

ACF_EXPORTS(BrowserViewCreate, BOOL)(DWORD* target,
	                                   ACFlibClient* lpObjClient,
	                                   LPWSTR url,
	                                   DWORD* browser_settings,
	                                   CefDictionaryValue* extra_info,
	                                   CefRequestContext* context,
	                                   LPVOID callback,
	                                   bool copy)
{
	auto settings = reinterpret_cast<CefBrowserSettings*>(browser_settings[1]);

	CefRefPtr<ACFlibBrowserViewDelegate> lpHandler = (!!callback) ? new ACFlibBrowserViewDelegate(callback, copy) : nullptr;

	CefRefPtr<CefBrowserView> lpObj = CefBrowserView::CreateBrowserView(nullptr, url, CefBrowserSettings(), extra_info, context, lpHandler);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_browser_view_funcs;

	return !!lpObj;
}

ACF_EXPORTS(BrowserViewGetForBrowser, BOOL)(DWORD* target, CefBrowser* bro)
{
	CefRefPtr<CefBrowserView> lpObj = CefBrowserView::GetForBrowser(bro);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_browser_view_funcs;

	return !!lpObj;
}

bool ECALL bview_get_browser(CefBrowserView* obj, DWORD* target)
{
	CefRefPtr<CefBrowser> lpObj = obj->GetBrowser();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_browser_funcs;

	return !!lpObj;
}

bool ECALL bview_get_chrome_toolbar(CefBrowserView* obj, DWORD* target)
{
	CefRefPtr<CefView> lpObj = obj->GetChromeToolbar();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_view_funcs;

	return !!lpObj;
}

void ECALL bview_set_prefer_accelerator(CefBrowserView* obj, bool prefer)
{
	ISVALID(obj);

	obj->SetPreferAccelerators(prefer);
}

DWORD acf_browser_view_funcs[] = {
	(DWORD)&parent_to_view<CefBrowserView>,
	(DWORD)&bview_get_browser,
	(DWORD)&bview_get_chrome_toolbar,
	(DWORD)&bview_set_prefer_accelerator,
};
