
#include "acf_Types.h"
#include "acf_Conv.h"
#include "include/cef_dom.h"

extern DWORD acf_dom_document_funcs[];
extern DWORD acf_dom_node_funcs[];

int ECALL document_get_type(CefDOMDocument* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetType();
}

bool ECALL document_get_document(CefDOMDocument* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDOMNode> dupObj = obj->GetDocument();

	if (dupObj) {
		dupObj->AddRef();
		target[1] = (DWORD)((LPVOID)dupObj.get());
	}
	target[2] = (DWORD)acf_dom_node_funcs;

	return target != NULL;
}

bool ECALL document_get_body(CefDOMDocument* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDOMNode> dupObj = obj->GetBody();

	if (dupObj) {
		dupObj->AddRef();
		target[1] = (DWORD)((LPVOID)dupObj.get());
	}
	target[2] = (DWORD)acf_dom_node_funcs;

	return target != NULL;
}

bool ECALL document_get_head(CefDOMDocument* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDOMNode> dupObj = obj->GetHead();

	if (dupObj) {
		dupObj->AddRef();
		target[1] = (DWORD)((LPVOID)dupObj.get());
	}
	target[2] = (DWORD)acf_dom_node_funcs;

	return target != NULL;
}

BOOL ECALL document_get_title(CefDOMDocument* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetTitle().c_str());

	return str != NULL;
}

bool ECALL document_get_element_by_id(CefDOMDocument* obj, LPCWSTR id, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDOMNode> dupObj = obj->GetElementById(id);

	if (dupObj) {
		dupObj->AddRef();
		target[1] = (DWORD)((LPVOID)dupObj.get());
	}
	target[2] = (DWORD)acf_dom_node_funcs;

	return target != NULL;
}

bool ECALL document_get_focused_node(CefDOMDocument* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDOMNode> dupObj = obj->GetFocusedNode();

	if (dupObj) {
		dupObj->AddRef();
		target[1] = (DWORD)((LPVOID)dupObj.get());
	}
	target[2] = (DWORD)acf_dom_node_funcs;

	return target != NULL;
}

BOOL ECALL document_has_selection(CefDOMDocument* obj)
{
	ISVALIDR(obj, NULL);

	return obj->HasSelection();
}

int ECALL document_get_selection_start_offset(CefDOMDocument* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetSelectionStartOffset();
}

int ECALL document_get_selection_end_offset(CefDOMDocument* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetSelectionEndOffset();
}

BOOL ECALL document_get_selection_as_markup(CefDOMDocument* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetSelectionAsMarkup().c_str());

	return str != NULL;
}

BOOL ECALL document_get_selection_as_text(CefDOMDocument* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetSelectionAsText().c_str());

	return str != NULL;
}

BOOL ECALL document_get_base_url(CefDOMDocument* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetBaseURL().c_str());

	return str != NULL;
}

BOOL ECALL document_get_complete_url(CefDOMDocument* obj, LPCWSTR partial_url, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetCompleteURL(partial_url).c_str());

	return str != NULL;
}

DWORD acf_dom_document_funcs[] = {
	(DWORD)&document_get_type,
	(DWORD)&document_get_document,
	(DWORD)&document_get_body,
	(DWORD)&document_get_head,
	(DWORD)&document_get_title,
	(DWORD)&document_get_element_by_id,
	(DWORD)&document_get_focused_node,
	(DWORD)&document_has_selection,
	(DWORD)&document_get_selection_start_offset,
	(DWORD)&document_get_selection_end_offset,
	(DWORD)&document_get_selection_as_markup,
	(DWORD)&document_get_selection_as_text,
	(DWORD)&document_get_base_url,
	(DWORD)&document_get_complete_url,
};

int ECALL node_get_type(CefDOMNode* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetType();
}

BOOL ECALL node_is_text(CefDOMNode* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsText();
}

BOOL ECALL node_is_element(CefDOMNode* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsElement();
}

BOOL ECALL node_is_editable(CefDOMNode* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsEditable();
}

BOOL ECALL node_is_form_control_element(CefDOMNode* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsFormControlElement();
}

BOOL ECALL node_get_form_control_element_type(CefDOMNode* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetFormControlElementType().c_str());

	return str != NULL;
}

BOOL ECALL node_is_same(CefDOMNode* obj, CefDOMNode* that)
{
	ISVALIDR(obj, NULL);

	return obj->IsSame(that);
}

BOOL ECALL node_get_name(CefDOMNode* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetName().c_str());

	return str != NULL;
}

BOOL ECALL node_get_value(CefDOMNode* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetValue().c_str());

	return str != NULL;
}

BOOL ECALL node_set_value(CefDOMNode* obj, LPCWSTR value)
{
	ISVALIDR(obj, NULL);

	return obj->SetValue(value);
}

BOOL ECALL node_get_as_markup(CefDOMNode* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetAsMarkup().c_str());

	return str != NULL;
}

bool ECALL node_get_document(CefDOMNode* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDOMDocument> dupObj = obj->GetDocument();

	if (dupObj) {
		dupObj->AddRef();
		target[1] = (DWORD)((LPVOID)dupObj.get());
	}
	target[2] = (DWORD)acf_dom_document_funcs;

	return target != NULL;
}

bool ECALL node_get_parent(CefDOMNode* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDOMNode> dupObj = obj->GetParent();

	if (dupObj) {
		dupObj->AddRef();
		target[1] = (DWORD)((LPVOID)dupObj.get());
	}
	target[2] = (DWORD)acf_dom_node_funcs;

	return target != NULL;
}

bool ECALL node_get_previous_sibling(CefDOMNode* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDOMNode> dupObj = obj->GetPreviousSibling();

	if (dupObj) {
		dupObj->AddRef();
		target[1] = (DWORD)((LPVOID)dupObj.get());
	}
	target[2] = (DWORD)acf_dom_node_funcs;

	return target != NULL;
}

bool ECALL node_get_next_sibling(CefDOMNode* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDOMNode> dupObj = obj->GetNextSibling();

	if (dupObj) {
		dupObj->AddRef();
		target[1] = (DWORD)((LPVOID)dupObj.get());
	}
	target[2] = (DWORD)acf_dom_node_funcs;

	return target != NULL;
}

BOOL ECALL node_has_children(CefDOMNode* obj)
{
	ISVALIDR(obj, NULL);

	return obj->HasChildren();
}

bool ECALL node_get_first_child(CefDOMNode* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDOMNode> dupObj = obj->GetFirstChild();

	if (dupObj) {
		dupObj->AddRef();
		target[1] = (DWORD)((LPVOID)dupObj.get());
	}
	target[2] = (DWORD)acf_dom_node_funcs;

	return target != NULL;
}

bool ECALL node_get_last_child(CefDOMNode* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDOMNode> dupObj = obj->GetLastChild();

	if (dupObj) {
		dupObj->AddRef();
		target[1] = (DWORD)((LPVOID)dupObj.get());
	}
	target[2] = (DWORD)acf_dom_node_funcs;

	return target != NULL;
}

BOOL ECALL node_get_element_tag_name(CefDOMNode* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetElementTagName().c_str());

	return str != NULL;
}

BOOL ECALL node_has_element_attributes(CefDOMNode* obj)
{
	ISVALIDR(obj, NULL);

	return obj->HasElementAttributes();
}

BOOL ECALL node_has_element_attribute(CefDOMNode* obj, LPCWSTR name)
{
	ISVALIDR(obj, NULL);

	return obj->HasElementAttribute(name);
}

BOOL ECALL node_get_element_attribute(CefDOMNode* obj, LPCWSTR name, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetElementAttribute(name).c_str());

	return str != NULL;
}

BOOL ECALL node_get_element_attributes(CefDOMNode* obj, LPVOID* eArray)
{
	ISVALIDR(obj, NULL);

	std::map<CefString, CefString> keys;
	obj->GetElementAttributes(keys);

	DWORD* pStrs = new DWORD[keys.size()];
	USES_CONVERSION;
	int index = 0;
	for (auto iter = keys.begin(); iter != keys.end(); iter++)
	{
		pStrs[index] = (DWORD)new ACF_STRING_PAIR;
		((PACF_STRING_PAIR)pStrs[index])->key = (LPBYTE)UnicodeToEStream((*iter).first.c_str());
		((PACF_STRING_PAIR)pStrs[index])->value = (LPBYTE)UnicodeToEStream((*iter).second.c_str());
		++index;
	}

	FreeAryElement(*eArray);

	int nSize = keys.size() * sizeof(DWORD);
	LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
	*(LPINT)pAry = 1;
	*(LPINT)(pAry + sizeof(INT)) = keys.size();
	memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
	delete[]pStrs;

	*eArray = pAry;

	return eArray != NULL;
}

BOOL ECALL node_set_element_attribute(CefDOMNode* obj, LPCWSTR name, LPCWSTR value)
{
	ISVALIDR(obj, NULL);

	return obj->SetElementAttribute(name, value);
}

BOOL ECALL node_get_element_inner_text(CefDOMNode* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetElementInnerText().c_str());

	return str != NULL;
}

BOOL ECALL node_get_element_bounds(CefDOMNode* obj, cef_rect_t** pRect)
{
	ISVALIDR(obj, NULL);

	CefRect rt = obj->GetElementBounds();

	(**pRect).x = rt.x;
	(**pRect).y = rt.y;
	(**pRect).width = rt.width;
	(**pRect).height = rt.height;

	return pRect != NULL;
}

DWORD acf_dom_node_funcs[] = {
	(DWORD)&node_get_type,
	(DWORD)&node_is_text,
	(DWORD)&node_is_element,
	(DWORD)&node_is_editable,
	(DWORD)&node_is_form_control_element,
	(DWORD)&node_get_form_control_element_type,
	(DWORD)&node_is_same,
	(DWORD)&node_get_name,
	(DWORD)&node_get_value,
	(DWORD)&node_set_value,
	(DWORD)&node_get_as_markup,
	(DWORD)&node_get_document,
	(DWORD)&node_get_parent,
	(DWORD)&node_get_previous_sibling,
	(DWORD)&node_get_next_sibling,
	(DWORD)&node_has_children,
	(DWORD)&node_get_first_child,
	(DWORD)&node_get_last_child,
	(DWORD)&node_get_element_tag_name,
	(DWORD)&node_has_element_attributes,
	(DWORD)&node_has_element_attribute,
	(DWORD)&node_get_element_attribute,
	(DWORD)&node_get_element_attributes,
	(DWORD)&node_set_element_attribute,
	(DWORD)&node_get_element_inner_text,
	(DWORD)&node_get_element_bounds,
};
