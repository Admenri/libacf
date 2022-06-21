#include "acf_Task.h"

///
// Method that will be executed on the target thread.
///
/*--cef()--*/
void ACFlibTask::Execute()
{
	this->m_callback(this->lParam1, this->lParam2, this->lParam3);
}
