
#include "acf_Conv.h"
#include <windows.h>

LPVOID ECALL UnicodeToEStream(const wchar_t* str)
{
	if (!str)
		return NULL;
	INT nLen = wcslen(str) * 2 + 2; // Wide String
	LPBYTE pData = (LPBYTE)malloc(nLen + 2 * sizeof(INT));
	ZeroMemory(pData, nLen);
	*(LPINT)pData = 1;
	*(LPINT)(pData + sizeof(INT)) = nLen;
	wcscpy((LPWSTR)(pData + 2 * sizeof(INT)), str);
	return pData;
}

LPWSTR ECALL EStreamToUnicode(LPBYTE stream)
{
	if (!stream)
		return NULL;

	if (*(LPWSTR)(stream + 2 * sizeof(INT)) == '\0')
		return NULL;

	return (LPWSTR)(stream + 2 * sizeof(INT));
}

LPBYTE GetAryElementInf(void* pAryData, LPINT pnElementCount)
{
	LPINT pnData = (LPINT)pAryData;
	INT nArys = *pnData++;
	INT nElementCount = 1;
	while (nArys > 0)
	{
		nElementCount *= *pnData++;
		nArys--;
	}

	if (pnElementCount != NULL)
		*pnElementCount = nElementCount;
	return (LPBYTE)pnData;
}

void FreeAryElement(void* pAryData) // 对于文本和字节集数组有效
{
	DWORD AryElementCount = 0;
	LPINT* pArryPtr = (LPINT*)GetAryElementInf(pAryData, (LPINT)AryElementCount);

	for (INT i = 0; i < (INT)AryElementCount; i++)
	{
		void* pElementData = *pArryPtr;
		if (pElementData)
		{
			free(pElementData);
			*pArryPtr = NULL;
		}
		pArryPtr++;
	}

	free(pAryData);
}
