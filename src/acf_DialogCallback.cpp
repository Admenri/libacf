
#include "acf_Types.h"
#include "acf_Conv.h"

#include "include/cef_jsdialog_handler.h"
#include "include/cef_dialog_handler.h"

extern DWORD acf_callback_js_dialog[];
extern DWORD acf_callback_dialog[];

void ECALL jsdialog_continue(CefJSDialogCallback* obj, bool success, LPCWSTR input)
{
	ISVALID(obj);

	obj->Continue(success, input);
}

DWORD acf_callback_js_dialog[] = {
	(DWORD)&jsdialog_continue,
};

void ECALL filedialog_continue(CefFileDialogCallback* obj, int filter, LPVOID* aryFilePaths)
{
	ISVALID(obj);

	LPSTR pArgsList = (LPSTR)*aryFilePaths;

	int nCount = *(LPINT)(pArgsList + sizeof(INT));

	std::vector<CefString> pArgs(nCount);

	for (size_t i = 0; i < nCount; i++)
	{
		pArgs[i] = (LPWSTR)EStreamToUnicode((LPBYTE)((LPDWORD)(pArgsList + sizeof(INT) * 2))[i]);
	}

	obj->Continue(filter, pArgs);
}

void ECALL filedialog_cancel(CefFileDialogCallback* obj)
{
	ISVALID(obj);

	obj->Cancel();
}

DWORD acf_callback_dialog[] = {
	(DWORD)&filedialog_continue,
	(DWORD)&filedialog_cancel,
};
