#pragma once

#include "acf_Types.h"

void FreeAryElement(void* pAryData);

LPVOID ECALL UnicodeToEStream(const wchar_t* str);
LPWSTR ECALL EStreamToUnicode(LPBYTE stream);

#define USES_CONVERSION
