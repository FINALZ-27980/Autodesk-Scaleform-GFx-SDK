/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2008-2012 CRI Middleware Co., Ltd.
 *
 * Library  : Sample Library
 * Module   : Utility
 * File     : CriSmpFsUtility_PC.c
 *
 ****************************************************************************/

/***************************************************************************
 * インクルード
 * Header files
 ***************************************************************************/

#include <stdio.h>
#include <windows.h>
#include <cri_xpt.h>
#include "CriSmpFsUtility.h"

/***************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 ***************************************************************************/
#define CRISMPFSUTL_PRINTF_BUF_SIZE		(2048)

/***************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 ***************************************************************************/

/***************************************************************************
 * 変数定義
 * Variable definitions
 ***************************************************************************/
static LARGE_INTEGER frequency;
static LARGE_INTEGER counter_1st;

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/

/* エントリポイント */
int main(int argc, char *argv[])
{
	return criSample_Main(argc, argv);
}

Bool criSmpFsUtl_Initialize(void)
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&counter_1st);
	return (TRUE);
}

void criSmpFsUtl_Finalize(void)
{
	return;
}

void criSmpFsUtl_Sleep(Uint32 msec)
{
	Sleep((DWORD)msec);
	
	return;
}

void criSmpFsUtl_Printf(const Char8* format, ...)
{
	va_list args;
	Char8 str[CRISMPFSUTL_PRINTF_BUF_SIZE];

	va_start(args, format);
	vsprintf_s(str, CRISMPFSUTL_PRINTF_BUF_SIZE, format, args);
	va_end(args);

	OutputDebugString(str);
	
	return;
}

void *criSmpFsUtl_Alloc(Uint32 size)
{
	void *mem;
	
	mem = HeapAlloc(GetProcessHeap(), 0, (DWORD)size);

	return (mem);
}

void criSmpFsUtl_Free(void *ptr)
{
	HeapFree(GetProcessHeap(), 0, ptr);

	return;
}

CriSint64 criSmpFsUtl_GetTimeMs(void)
{
	LARGE_INTEGER counter;
	CriSint64 milliseconds;
	QueryPerformanceCounter(&counter);
	milliseconds = (counter.QuadPart-counter_1st.QuadPart)*1000/frequency.QuadPart;
	return milliseconds;
}

/* --- end of file --- */
