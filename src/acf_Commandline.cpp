
#include "acf_Types.h"
#include "include/cef_command_line.h"

#include "acf_Conv.h"

extern DWORD acf_commandline_funcs[];

ACF_EXPORTS(CommandLineCreate, BOOL)(DWORD* target)
{
	CefRefPtr<CefCommandLine> lpObj = CefCommandLine::CreateCommandLine();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_commandline_funcs;

	return !!lpObj;
}

ACF_EXPORTS(CommandLineGetGlobal, BOOL)(DWORD* target)
{
	CefRefPtr<CefCommandLine> lpObj = CefCommandLine::GetGlobalCommandLine();

	lpObj->AddRef();
	target[1] = (DWORD)((LPVOID)lpObj.get());
	target[2] = (DWORD)acf_commandline_funcs;

	return !!lpObj;
}

bool ECALL cmd_is_valid(CefCommandLine* obj)
{
	ISVALIDR(obj, false);

	return obj->IsValid();
}

bool ECALL cmd_is_read_only(CefCommandLine* obj)
{
	ISVALIDR(obj, false);

	return obj->IsReadOnly();
}

bool ECALL cmd_copy(CefCommandLine* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefCommandLine> dupObj = obj->Copy();

	dupObj->AddRef();
	target[1] = (DWORD)((LPVOID)dupObj.get());
	target[2] = (DWORD)acf_commandline_funcs;

	return !!dupObj;
}

void ECALL cmd_init_from_argv(CefCommandLine* obj, int argc, LPCWSTR argv)
{
	ISVALID(obj);

	obj->InitFromArgv(argc, (const char* const*)argv);
}

void ECALL cmd_init_from_string(CefCommandLine* obj, LPCWSTR commandline)
{
	ISVALID(obj);

	obj->InitFromString(commandline);
}

void ECALL cmd_reset(CefCommandLine* obj)
{
	ISVALID(obj);

	obj->Reset();
}

void ECALL cmd_get_argv(CefCommandLine* obj, LPVOID* eArray)
{
	ISVALID(obj);

	std::vector<CefString> keys;
	obj->GetArgv(keys);

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
}

int ECALL cmd_get_commandline_string(CefCommandLine* obj, DWORD* cmdstring)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*cmdstring = (DWORD)UnicodeToEStream(obj->GetCommandLineString().c_str());

	return cmdstring != NULL;
}

int ECALL cmd_get_program(CefCommandLine* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetProgram().c_str());

	return ansi_str != 0;
}

void ECALL cmd_set_program(CefCommandLine* obj, LPCWSTR program)
{
	ISVALID(obj);

	obj->SetProgram(program);
}

bool ECALL cmd_has_switches(CefCommandLine* obj)
{
	ISVALIDR(obj, false);

	return obj->HasSwitches();
}

bool ECALL cmd_has_switch(CefCommandLine* obj, LPCWSTR name)
{
	ISVALIDR(obj, false);

	return obj->HasSwitch(name);
}

int ECALL cmd_get_switch_value(CefCommandLine* obj, LPCWSTR name, DWORD* ansi_str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetSwitchValue(name).c_str());

	return ansi_str != 0;
}

void ECALL cmd_get_switches(CefCommandLine* obj, LPVOID* eArray)
{
	ISVALID(obj);

	std::map<CefString, CefString> keys;
	obj->GetSwitches(keys);

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
}

void ECALL cmd_append_switch(CefCommandLine* obj, LPCWSTR name)
{
	ISVALID(obj);

	obj->AppendSwitch(name);
}

void ECALL cmd_append_switch_value(CefCommandLine* obj, LPCWSTR name, LPCWSTR value)
{
	ISVALID(obj);

	obj->AppendSwitchWithValue(name, value);
}

bool ECALL cmd_has_arguments(CefCommandLine* obj)
{
	ISVALIDR(obj, false);

	return obj->HasArguments();
}

void ECALL cmd_get_arguments(CefCommandLine* obj, LPVOID* eArray)
{
	ISVALID(obj);

	std::vector<CefString> keys;
	obj->GetArguments(keys);

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
}

void ECALL cmd_append_argument(CefCommandLine* obj, LPCWSTR name)
{
	ISVALID(obj);

	obj->AppendArgument(name);
}

void ECALL cmd_prepend_wrapper(CefCommandLine* obj, LPCWSTR name)
{
	ISVALID(obj);

	obj->PrependWrapper(name);
}

DWORD acf_commandline_funcs[] = {
	(DWORD)&cmd_is_valid,
	(DWORD)&cmd_is_read_only,
	(DWORD)&cmd_copy,
	(DWORD)&cmd_init_from_argv,
	(DWORD)&cmd_init_from_string,
	(DWORD)&cmd_reset,
	(DWORD)&cmd_get_argv,
	(DWORD)&cmd_get_commandline_string,
	(DWORD)&cmd_get_program,
	(DWORD)&cmd_set_program,
	(DWORD)&cmd_has_switches,
	(DWORD)&cmd_has_switch,
	(DWORD)&cmd_get_switch_value,
	(DWORD)&cmd_get_switches,
	(DWORD)&cmd_append_switch,
	(DWORD)&cmd_append_switch_value,
	(DWORD)&cmd_has_arguments,
	(DWORD)&cmd_get_arguments,
	(DWORD)&cmd_append_argument,
	(DWORD)&cmd_prepend_wrapper,
};