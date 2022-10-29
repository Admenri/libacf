#include "acf_Task.h"

///
// Method that will be executed on the target thread.
///
/*--cef()--*/
void ACFlibTask::Execute()
{
	this->m_callback(this->lParam1, this->lParam2, this->lParam3);
}

ACFlibTaskStd::~ACFlibTaskStd()
{
	if (this->m_callback && this->m_copyData)
		LocalFree(this->m_callback);
}

///
// Method that will be executed on the target thread.
///
/*--cef()--*/
void ACFlibTaskStd::Execute()
{
	if (this->m_callback != NULL)
	{
		LPVOID pClass = this->m_callback;
		__asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
		}
	}
}
