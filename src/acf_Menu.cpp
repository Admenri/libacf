
#include "acf_Types.h"
#include "include/cef_menu_model.h"
#include "include/cef_context_menu_handler.h"

#include "acf_Conv.h"
#include "acf_FrameEvents.h"

extern DWORD acf_menu_params_funcs[];
extern DWORD acf_menu_model_funcs[];
extern DWORD acf_callback_run_menu[];

ACF_EXPORTS(MenuModelCreate, BOOL)(LPVOID lpCallback, BOOL copyData, DWORD* target)
{
	CefRefPtr<ACFlibMenuModelDelegate> pDelegate = new ACFlibMenuModelDelegate(lpCallback, copyData);
	CefRefPtr<CefMenuModel> lpObj = CefMenuModel::CreateMenuModel(pDelegate);

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_menu_model_funcs;;

	return !!lpObj;
}

int ECALL param_get_x_coord(CefContextMenuParams* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetXCoord();
}

int ECALL param_get_y_coord(CefContextMenuParams* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetYCoord();
}

int ECALL param_get_type_flags(CefContextMenuParams* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetTypeFlags();
}

bool ECALL param_get_link_url(CefContextMenuParams* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetLinkUrl().c_str());

	return ansi_str != 0;
}

bool ECALL param_get_unfiltered_url(CefContextMenuParams* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetUnfilteredLinkUrl().c_str());

	return ansi_str != 0;
}

bool ECALL param_get_source_url(CefContextMenuParams* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetSourceUrl().c_str());

	return ansi_str != 0;
}

BOOL ECALL param_has_image_contents(CefContextMenuParams* obj)
{
	ISVALIDR(obj, FALSE);

	return obj->HasImageContents();
}

bool ECALL param_get_title_text(CefContextMenuParams* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetTitleText().c_str());

	return ansi_str != 0;
}

bool ECALL param_get_page_url(CefContextMenuParams* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetPageUrl().c_str());

	return ansi_str != 0;
}

bool ECALL param_get_frame_url(CefContextMenuParams* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetFrameUrl().c_str());

	return ansi_str != 0;
}

bool ECALL param_get_frame_charset(CefContextMenuParams* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetFrameCharset().c_str());

	return ansi_str != 0;
}

int ECALL param_get_media_type(CefContextMenuParams* obj)
{
	ISVALIDR(obj, FALSE);

	return obj->GetMediaType();
}

int ECALL param_get_media_state_flags(CefContextMenuParams* obj)
{
	ISVALIDR(obj, FALSE);

	return obj->GetMediaStateFlags();
}

bool ECALL param_get_selection_text(CefContextMenuParams* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetSelectionText().c_str());

	return ansi_str != 0;
}

bool ECALL param_get_misspelled_word(CefContextMenuParams* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetMisspelledWord().c_str());

	return ansi_str != 0;
}

BOOL ECALL param_get_dictionary_suggestions(CefContextMenuParams* obj, LPVOID* eArray)
{
	ISVALIDR(obj, FALSE);

	std::vector<CefString> keys;
	obj->GetDictionarySuggestions(keys);

	DWORD* pStrs = new DWORD[keys.size()];
	USES_CONVERSION;
	for (size_t i = 0; i < keys.size(); i++)
	{
		pStrs[i] = (DWORD)UnicodeToEStream(keys[i].c_str());
	}

	FreeAryElement(*eArray);

	int nSize = keys.size() * sizeof(DWORD);
	LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
	*(LPINT)pAry = 1;
	*(LPINT)(pAry + sizeof(INT)) = keys.size();
	memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
	delete[]pStrs;

	*eArray = pAry;

	return eArray != 0;
}

BOOL ECALL param_is_editable(CefContextMenuParams* obj)
{
	ISVALIDR(obj, FALSE);

	return obj->IsEditable();
}

BOOL ECALL param_is_spell_check_enabled(CefContextMenuParams* obj)
{
	ISVALIDR(obj, FALSE);

	return obj->IsSpellCheckEnabled();
}

int ECALL param_get_edit_state_flags(CefContextMenuParams* obj)
{
	ISVALIDR(obj, FALSE);

	return obj->GetEditStateFlags();
}

BOOL ECALL param_is_custom_menu(CefContextMenuParams* obj)
{
	ISVALIDR(obj, FALSE);

	return obj->IsCustomMenu();
}

BOOL ECALL param_is_pepper_menu(CefContextMenuParams* obj)
{
	ISVALIDR(obj, FALSE);

	return obj->IsPepperMenu();
}

DWORD acf_menu_params_funcs[] = {
	(DWORD)&param_get_x_coord,
	(DWORD)&param_get_y_coord,
	(DWORD)&param_get_type_flags,
	(DWORD)&param_get_link_url,
	(DWORD)&param_get_unfiltered_url,
	(DWORD)&param_get_source_url,
	(DWORD)&param_has_image_contents,
	(DWORD)&param_get_title_text,
	(DWORD)&param_get_page_url,
	(DWORD)&param_get_frame_url,
	(DWORD)&param_get_frame_charset,
	(DWORD)&param_get_media_type,
	(DWORD)&param_get_media_state_flags,
	(DWORD)&param_get_selection_text,
	(DWORD)&param_get_misspelled_word,
	(DWORD)&param_get_dictionary_suggestions,
	(DWORD)&param_is_editable,
	(DWORD)&param_is_spell_check_enabled,
	(DWORD)&param_get_edit_state_flags,
	(DWORD)&param_is_custom_menu,
	(DWORD)&param_is_pepper_menu,
};

bool ECALL model_is_sub_menu(CefMenuModel* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsSubMenu();
}

bool ECALL model_clear(CefMenuModel* obj)
{
	ISVALIDR(obj, NULL);

	return obj->Clear();
}

int ECALL model_get_count(CefMenuModel* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetCount();
}

bool ECALL model_add_separator(CefMenuModel* obj)
{
	ISVALIDR(obj, NULL);

	return obj->AddSeparator();
}

bool ECALL model_add_item(CefMenuModel* obj, int command_id, LPCWSTR label)
{
	ISVALIDR(obj, NULL);

	return obj->AddItem(command_id, label);
}

bool ECALL model_add_check_item(CefMenuModel* obj, int command_id, LPCWSTR label)
{
	ISVALIDR(obj, NULL);

	return obj->AddCheckItem(command_id, label);
}

bool ECALL model_add_radio_item(CefMenuModel* obj, int command_id, LPCWSTR label, int group_id)
{
	ISVALIDR(obj, NULL);

	return obj->AddRadioItem(command_id, label, group_id);
}

bool ECALL model_add_sub_item(CefMenuModel* obj, int command_id, LPCWSTR label, DWORD* target)
{
	ISVALIDR(obj, NULL);

	CefRefPtr<CefMenuModel> pSubMenu = obj->AddSubMenu(command_id, label);

	pSubMenu->AddRef();
	target[1] = (DWORD)((LPVOID)pSubMenu);
	target[2] = (DWORD)acf_menu_model_funcs;

	return !!pSubMenu;
}

bool ECALL model_insert_separator_at(CefMenuModel* obj, int index)
{
	ISVALIDR(obj, NULL);

	return obj->InsertSeparatorAt(index);
}

bool ECALL model_insert_item_at(CefMenuModel* obj, int index, int command_id, LPCWSTR label)
{
	ISVALIDR(obj, NULL);

	return obj->InsertItemAt(index, command_id, label);
}

bool ECALL model_insert_check_item_at(CefMenuModel* obj, int index, int command_id, LPCWSTR label)
{
	ISVALIDR(obj, NULL);

	return obj->InsertCheckItemAt(index, command_id, label);
}

bool ECALL model_insert_radio_item_at(CefMenuModel* obj, int index, int command_id, LPCWSTR label, int group_id)
{
	ISVALIDR(obj, NULL);

	return obj->InsertRadioItemAt(index, command_id, label, group_id);
}

bool ECALL model_insert_sub_item_at(CefMenuModel* obj, int index, int command_id, LPCWSTR label, DWORD* target)
{
	ISVALIDR(obj, NULL);

	CefRefPtr<CefMenuModel> pSubMenu = obj->InsertSubMenuAt(index, command_id, label);

	pSubMenu->AddRef();
	target[1] = (DWORD)((LPVOID)pSubMenu);
	target[2] = (DWORD)acf_menu_model_funcs;

	return !!pSubMenu;
}

bool ECALL model_remove(CefMenuModel* obj, int command_id)
{
	ISVALIDR(obj, NULL);

	return obj->Remove(command_id);
}

bool ECALL model_remove_at(CefMenuModel* obj, int index)
{
	ISVALIDR(obj, NULL);

	return obj->RemoveAt(index);
}

int ECALL model_get_index_of(CefMenuModel* obj, int command_id)
{
	ISVALIDR(obj, NULL);

	return obj->GetIndexOf(command_id);
}

int ECALL model_get_command_id_at(CefMenuModel* obj, int index)
{
	ISVALIDR(obj, NULL);

	return obj->GetCommandIdAt(index);
}

bool ECALL model_set_command_id_at(CefMenuModel* obj, int index, int command_id)
{
	ISVALIDR(obj, NULL);

	return obj->SetCommandIdAt(index, command_id);
}

BOOL ECALL model_get_label(CefMenuModel* obj, int command_id, DWORD* ansi_str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetLabel(command_id).c_str());

	return ansi_str != 0;
}

BOOL ECALL model_get_label_at(CefMenuModel* obj, int index, DWORD* ansi_str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetLabelAt(index).c_str());

	return ansi_str != 0;
}

bool ECALL model_set_label(CefMenuModel* obj, int command_id, LPCWSTR label)
{
	ISVALIDR(obj, NULL);

	return obj->SetLabel(command_id, label);
}

bool ECALL model_set_label_at(CefMenuModel* obj, int index, LPCWSTR label)
{
	ISVALIDR(obj, NULL);

	return obj->SetLabelAt(index, label);
}

int ECALL model_get_type(CefMenuModel* obj, int command_id)
{
	ISVALIDR(obj, NULL);

	return obj->GetType(command_id);
}

int ECALL model_get_type_at(CefMenuModel* obj, int index)
{
	ISVALIDR(obj, NULL);

	return obj->GetTypeAt(index);
}

int ECALL model_get_group_id(CefMenuModel* obj, int command_id)
{
	ISVALIDR(obj, NULL);

	return obj->GetGroupId(command_id);
}

int ECALL model_get_group_id_at(CefMenuModel* obj, int index)
{
	ISVALIDR(obj, NULL);

	return obj->GetGroupIdAt(index);
}

bool ECALL model_set_group_id(CefMenuModel* obj, int command_id, int group_id)
{
	ISVALIDR(obj, NULL);

	return obj->SetGroupId(command_id, group_id);
}

bool ECALL model_set_group_id_at(CefMenuModel* obj, int index, int group_id)
{
	ISVALIDR(obj, NULL);

	return obj->SetGroupIdAt(index, group_id);
}

bool ECALL model_get_sub_menu(CefMenuModel* obj, int command_id, DWORD* target)
{
	ISVALIDR(obj, NULL);

	CefRefPtr<CefMenuModel> pSubMenu = obj->GetSubMenu(command_id);

	pSubMenu->AddRef();
	target[1] = (DWORD)((LPVOID)pSubMenu);
	target[2] = (DWORD)acf_menu_model_funcs;

	return !!pSubMenu;
}

bool ECALL model_get_sub_menu_at(CefMenuModel* obj, int index, DWORD* target)
{
	ISVALIDR(obj, NULL);

	CefRefPtr<CefMenuModel> pSubMenu = obj->GetSubMenuAt(index);

	pSubMenu->AddRef();
	target[1] = (DWORD)((LPVOID)pSubMenu);
	target[2] = (DWORD)acf_menu_model_funcs;

	return !!pSubMenu;
}

bool ECALL model_is_visible(CefMenuModel* obj, int command_id)
{
	ISVALIDR(obj, NULL);

	return obj->IsVisible(command_id);
}

bool ECALL model_is_visible_at(CefMenuModel* obj, int index)
{
	ISVALIDR(obj, NULL);

	return obj->IsVisibleAt(index);
}

bool ECALL model_set_visible(CefMenuModel* obj, int command_id, bool visible)
{
	ISVALIDR(obj, NULL);

	return obj->SetVisible(command_id, visible);
}

bool ECALL model_set_visible_at(CefMenuModel* obj, int index, bool visible)
{
	ISVALIDR(obj, NULL);

	return obj->SetVisibleAt(index, visible);
}

bool ECALL model_is_enabled(CefMenuModel* obj, int command_id)
{
	ISVALIDR(obj, NULL);

	return obj->IsEnabled(command_id);
}

bool ECALL model_is_enabled_at(CefMenuModel* obj, int index)
{
	ISVALIDR(obj, NULL);

	return obj->IsEnabledAt(index);
}

bool ECALL model_set_enabled(CefMenuModel* obj, int command_id, bool enabled)
{
	ISVALIDR(obj, NULL);

	return obj->SetEnabled(command_id, enabled);
}

bool ECALL model_set_enabled_at(CefMenuModel* obj, int index, bool enabled)
{
	ISVALIDR(obj, NULL);

	return obj->SetEnabledAt(index, enabled);
}

bool ECALL model_is_checked(CefMenuModel* obj, int command_id)
{
	ISVALIDR(obj, NULL);

	return obj->IsChecked(command_id);
}

bool ECALL model_is_checked_at(CefMenuModel* obj, int index)
{
	ISVALIDR(obj, NULL);

	return obj->IsCheckedAt(index);
}

bool ECALL model_set_checked(CefMenuModel* obj, int command_id, bool enabled)
{
	ISVALIDR(obj, NULL);

	return obj->SetChecked(command_id, enabled);
}

bool ECALL model_set_checked_at(CefMenuModel* obj, int index, bool enabled)
{
	ISVALIDR(obj, NULL);

	return obj->SetCheckedAt(index, enabled);
}

bool ECALL model_has_accelerator(CefMenuModel* obj, int command_id)
{
	ISVALIDR(obj, NULL);

	return obj->HasAccelerator(command_id);
}

bool ECALL model_has_accelerator_at(CefMenuModel* obj, int index)
{
	ISVALIDR(obj, NULL);

	return obj->HasAcceleratorAt(index);
}

bool ECALL model_set_accelerator(CefMenuModel* obj, int command_id, int key_code,
	bool shift, bool ctrl, bool alt)
{
	ISVALIDR(obj, NULL);

	return obj->SetAccelerator(command_id, key_code, shift, ctrl, alt);
}

bool ECALL model_set_accelerator_at(CefMenuModel* obj, int index, int key_code,
	bool shift, bool ctrl, bool alt)
{
	ISVALIDR(obj, NULL);

	return obj->SetAcceleratorAt(index, key_code, shift, ctrl, alt);
}

bool ECALL model_remove_accelerator(CefMenuModel* obj, int command_id)
{
	ISVALIDR(obj, NULL);

	return obj->RemoveAccelerator(command_id);
}

bool ECALL model_remove_accelerator_at(CefMenuModel* obj, int index)
{
	ISVALIDR(obj, NULL);

	return obj->RemoveAcceleratorAt(index);
}

bool ECALL model_get_accelerator(CefMenuModel* obj, int command_id, int* key_code,
	bool* shift, bool* ctrl, bool* alt)
{
	ISVALIDR(obj, NULL);

	return obj->GetAccelerator(command_id, *key_code, *shift, *ctrl, *alt);
}

bool ECALL model_get_accelerator_at(CefMenuModel* obj, int index, int* key_code,
	bool* shift, bool* ctrl, bool* alt)
{
	ISVALIDR(obj, NULL);

	return obj->GetAcceleratorAt(index, *key_code, *shift, *ctrl, *alt);
}

bool ECALL model_set_color(CefMenuModel* obj, int command_id, cef_menu_color_type_t color_type, cef_color_t color)
{
	ISVALIDR(obj, NULL);

	return obj->SetColor(command_id, color_type, color);
}

bool ECALL model_set_color_at(CefMenuModel* obj, int index, cef_menu_color_type_t color_type, cef_color_t color)
{
	ISVALIDR(obj, NULL);

	return obj->SetColorAt(index, color_type, color);
}

bool ECALL model_get_color(CefMenuModel* obj, int command_id, cef_menu_color_type_t color_type, cef_color_t* color)
{
	ISVALIDR(obj, NULL);

	return obj->GetColor(command_id, color_type, *color);
}

bool ECALL model_get_color_at(CefMenuModel* obj, int index, cef_menu_color_type_t color_type, cef_color_t* color)
{
	ISVALIDR(obj, NULL);

	return obj->GetColorAt(index, color_type, *color);
}

bool ECALL model_set_font_list(CefMenuModel* obj, int command_id, LPCWSTR flist)
{
	ISVALIDR(obj, NULL);

	return obj->SetFontList(command_id, flist);
}

bool ECALL model_set_font_list_at(CefMenuModel* obj, int index, LPCWSTR flist)
{
	ISVALIDR(obj, NULL);

	return obj->SetFontListAt(index, flist);
}

DWORD acf_menu_model_funcs[] = {
	(DWORD)&model_is_sub_menu,
	(DWORD)&model_clear,
	(DWORD)&model_get_count,
	(DWORD)&model_add_separator,
	(DWORD)&model_add_item,
	(DWORD)&model_add_check_item,
	(DWORD)&model_add_radio_item,
	(DWORD)&model_add_sub_item,
	(DWORD)&model_insert_separator_at,
	(DWORD)&model_insert_item_at,
	(DWORD)&model_insert_check_item_at,
	(DWORD)&model_insert_radio_item_at,
	(DWORD)&model_insert_sub_item_at,
	(DWORD)&model_remove,
	(DWORD)&model_remove_at,
	(DWORD)&model_get_index_of,
	(DWORD)&model_get_command_id_at,
	(DWORD)&model_set_command_id_at,
	(DWORD)&model_get_label,
	(DWORD)&model_get_label_at,
	(DWORD)&model_set_label,
	(DWORD)&model_set_label_at,
	(DWORD)&model_get_type,
	(DWORD)&model_get_type_at,
	(DWORD)&model_get_group_id,
	(DWORD)&model_get_group_id_at,
	(DWORD)&model_set_group_id,
	(DWORD)&model_set_group_id_at,
	(DWORD)&model_get_sub_menu,
	(DWORD)&model_get_sub_menu_at,
	(DWORD)&model_is_visible,
	(DWORD)&model_is_visible_at,
	(DWORD)&model_set_visible,
	(DWORD)&model_set_visible_at,
	(DWORD)&model_is_enabled,
	(DWORD)&model_is_enabled_at,
	(DWORD)&model_set_enabled,
	(DWORD)&model_set_enabled_at,
	(DWORD)&model_is_checked,
	(DWORD)&model_is_checked_at,
	(DWORD)&model_set_checked,
	(DWORD)&model_set_checked_at,
	(DWORD)&model_has_accelerator,
	(DWORD)&model_has_accelerator_at,
	(DWORD)&model_set_accelerator,
	(DWORD)&model_set_accelerator_at,
	(DWORD)&model_remove_accelerator,
	(DWORD)&model_remove_accelerator_at,
	(DWORD)&model_get_accelerator,
	(DWORD)&model_get_accelerator_at,
	(DWORD)&model_set_color,
	(DWORD)&model_set_color_at,
	(DWORD)&model_get_color,
	(DWORD)&model_get_color_at,
	(DWORD)&model_set_font_list,
	(DWORD)&model_set_font_list_at,
};

void ECALL run_menu_continue(CefRunContextMenuCallback* obj, int command_id, cef_event_flags_t event_flags)
{
	ISVALID(obj);

	obj->Continue(command_id, event_flags);
}

void ECALL run_menu_cancel(CefRunContextMenuCallback* obj)
{
	ISVALID(obj);

	obj->Cancel();
}

DWORD acf_callback_run_menu[] = {
	(DWORD)&run_menu_continue,
	(DWORD)&run_menu_cancel,
};