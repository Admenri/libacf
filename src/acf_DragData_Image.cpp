
#include "acf_Types.h"
#include "include/cef_drag_data.h"
#include "include/cef_image.h"
#include "acf_Conv.h"

extern DWORD acf_drag_data_funcs[];
extern DWORD acf_image_funcs[];
extern DWORD acf_binary_funcs[];

bool ECALL drag_clone(CefDragData* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefDragData> dupObj = obj->Clone();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_drag_data_funcs;

	return !!dupObj;
}

bool ECALL drag_is_read_only(CefDragData* obj)
{
	ISVALIDR(obj, false);

	return obj->IsReadOnly();
}

bool ECALL drag_is_link(CefDragData* obj)
{
	ISVALIDR(obj, false);

	return obj->IsLink();
}

bool ECALL drag_is_fragment(CefDragData* obj)
{
	ISVALIDR(obj, false);

	return obj->IsFragment();
}

bool ECALL drag_is_file(CefDragData* obj)
{
	ISVALIDR(obj, false);

	return obj->IsFile();
}

bool ECALL drag_get_link_url(CefDragData* obj, DWORD* str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetLinkURL().c_str());

	return str != NULL;
}

bool ECALL drag_get_link_title(CefDragData* obj, DWORD* str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetLinkTitle().c_str());

	return str != NULL;
}

bool ECALL drag_get_link_meta_data(CefDragData* obj, DWORD* str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetLinkMetadata().c_str());

	return str != NULL;
}

bool ECALL drag_get_fragment_text(CefDragData* obj, DWORD* str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetFragmentText().c_str());

	return str != NULL;
}

bool ECALL drag_get_fragment_html(CefDragData* obj, DWORD* str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetFragmentHtml().c_str());

	return str != NULL;
}

bool ECALL drag_get_fragment_base_url(CefDragData* obj, DWORD* str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetFragmentBaseURL().c_str());

	return str != NULL;
}

bool ECALL drag_get_filename(CefDragData* obj, DWORD* str)
{
	ISVALIDR(obj, false);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetFileName().c_str());

	return str != NULL;
}

bool ECALL drag_get_file_contents(CefDragData* obj)
{
	ISVALIDR(obj, false);

	// FIXME

	return NULL;
}

bool ECALL drag_get_filenames(CefDragData* obj, LPVOID* eArray)
{
	ISVALIDR(obj, NULL);

	std::vector<CefString> keys;
	obj->GetFileNames(keys);

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

	return !!eArray;
}

void ECALL drag_set_link_url(CefDragData* obj, LPCWSTR link)
{
	ISVALID(obj);

	obj->SetLinkURL(link);
}

void ECALL drag_set_link_title(CefDragData* obj, LPCWSTR link)
{
	ISVALID(obj);

	obj->SetLinkTitle(link);
}

void ECALL drag_set_link_meta_data(CefDragData* obj, LPCWSTR link)
{
	ISVALID(obj);

	obj->SetLinkMetadata(link);
}

void ECALL drag_set_fragment_text(CefDragData* obj, LPCWSTR link)
{
	ISVALID(obj);

	obj->SetFragmentText(link);
}

void ECALL drag_set_fragment_html(CefDragData* obj, LPCWSTR link)
{
	ISVALID(obj);

	obj->SetFragmentHtml(link);
}

void ECALL drag_set_fragment_base_url(CefDragData* obj, LPCWSTR link)
{
	ISVALID(obj);

	obj->SetFragmentBaseURL(link);
}

void ECALL drag_reset_file_contents(CefDragData* obj)
{
	ISVALID(obj);

	obj->ResetFileContents();
}

void ECALL drag_add_file(CefDragData* obj, LPCWSTR path, LPCWSTR display_name)
{
	ISVALID(obj);

	obj->AddFile(path, display_name);
}

bool ECALL drag_get_image(CefDragData* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefImage> dupObj = obj->GetImage();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_image_funcs;

	return !!dupObj;
}

bool ECALL drag_get_image_point(CefDragData* obj, cef_point_t** lpPt)
{
	ISVALIDR(obj, NULL);

	**lpPt = obj->GetImageHotspot();

	return lpPt;
}

bool ECALL drag_has_image(CefDragData* obj)
{
	ISVALIDR(obj, NULL);

	return obj->HasImage();
}

DWORD acf_drag_data_funcs[] = {
	(DWORD)&drag_clone,
	(DWORD)&drag_is_read_only,
	(DWORD)&drag_is_link,
	(DWORD)&drag_is_fragment,
	(DWORD)&drag_is_file,
	(DWORD)&drag_get_link_url,
	(DWORD)&drag_get_link_title,
	(DWORD)&drag_get_link_meta_data,
	(DWORD)&drag_get_fragment_text,
	(DWORD)&drag_get_fragment_html,
	(DWORD)&drag_get_fragment_base_url,
	(DWORD)&drag_get_filename,
	(DWORD)&drag_get_file_contents,
	(DWORD)&drag_get_filenames,
	(DWORD)&drag_set_link_url,
	(DWORD)&drag_set_link_title,
	(DWORD)&drag_set_link_meta_data,
	(DWORD)&drag_set_fragment_text,
	(DWORD)&drag_set_fragment_html,
	(DWORD)&drag_set_fragment_base_url,
	(DWORD)&drag_reset_file_contents,
	(DWORD)&drag_add_file,
	(DWORD)&drag_get_image,
	(DWORD)&drag_get_image_point,
	(DWORD)&drag_has_image,
};

bool ECALL image_is_empty(CefImage* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsEmpty();
}

bool ECALL image_is_same(CefImage* obj, CefImage* that)
{
	ISVALIDR(obj, NULL);

	return obj->IsSame(that);
}

bool ECALL image_add_bitmap(CefImage* obj, float* scale, int width, int height,
	cef_color_type_t crtype, cef_alpha_type_t aptype, LPVOID data_buffer, int size)
{
	ISVALIDR(obj, NULL);

	return obj->AddBitmap(*scale, width, height, crtype, aptype, data_buffer, size);
}

bool ECALL image_add_png(CefImage* obj, float* scale, LPVOID buffer, int size)
{
	ISVALIDR(obj, NULL);

	return obj->AddPNG(*scale, buffer, size);
}

bool ECALL image_add_jpeg(CefImage* obj, float* scale, LPVOID buffer, int size)
{
	ISVALIDR(obj, NULL);

	return obj->AddJPEG(*scale, buffer, size);
}

int ECALL image_get_width(CefImage* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetWidth();
}

int ECALL image_get_height(CefImage* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetHeight();
}

BOOL ECALL image_has_representation(CefImage* obj, float* scale)
{
	ISVALIDR(obj, NULL);

	return obj->HasRepresentation(*scale);
}

BOOL ECALL image_remove_representation(CefImage* obj, float* scale)
{
	ISVALIDR(obj, NULL);

	return obj->RemoveRepresentation(*scale);
}

BOOL ECALL image_get_representation(CefImage* obj, float* scale, float* real_scale, int* width, int* height)
{
	ISVALIDR(obj, NULL);

	return obj->GetRepresentationInfo(*scale, *real_scale, *width, *height);
}

bool ECALL image_get_as_bitmap(CefImage* obj, float* scale, cef_color_type_t crtype, cef_alpha_type_t aptype, int* width, int* height,DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefBinaryValue> dupObj = obj->GetAsBitmap(*scale, crtype, aptype, *width, *height);

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_binary_funcs;

	return !!dupObj;
}

bool ECALL image_get_as_png(CefImage* obj, float* scale, bool transparency, int* width, int* height, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefBinaryValue> dupObj = obj->GetAsPNG(*scale, transparency, *width, *height);

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_binary_funcs;

	return !!dupObj;
}

bool ECALL image_get_as_jpeg(CefImage* obj, float* scale, int quality, int* width, int* height, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefBinaryValue> dupObj = obj->GetAsJPEG(*scale, quality, *width, *height);

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_binary_funcs;

	return !!dupObj;
}

DWORD acf_image_funcs[] = {
	(DWORD)&image_is_empty,
	(DWORD)&image_is_same,
	(DWORD)&image_add_bitmap,
	(DWORD)&image_add_png,
	(DWORD)&image_add_jpeg,
	(DWORD)&image_get_width,
	(DWORD)&image_get_height,
	(DWORD)&image_has_representation,
	(DWORD)&image_remove_representation,
	(DWORD)&image_get_representation,
	(DWORD)&image_get_as_bitmap,
	(DWORD)&image_get_as_png,
	(DWORD)&image_get_as_jpeg,
};