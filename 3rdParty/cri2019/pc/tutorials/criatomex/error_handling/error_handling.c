/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2012 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 tutorial program
 * Module  : Error handling
 *         : エラーハンドリング
 * File    : error_handling.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
#include <windows.h>

/* CRI SDK header file */
#include <cri_xpt.h>

/* CRI ADX2 header files */
#include <cri_atom_ex.h>
#include <cri_atom_wasapi.h>

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/

/**************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 **************************************************************************/
/* 未使用引数警告回避マクロ */
/* Macro to prevent an unused arguments warning from being displayed */
#ifndef UNUSED
#define UNUSED(arg)						{ if (&(arg) == &(arg)) {} }
#endif

/**************************************************************************
 * 型定義
 * Type definitions
 **************************************************************************/

/**************************************************************************
 * 関数宣言
 * Function declarations
 **************************************************************************/
/* チュートリアル用エラーコールバック関数 */
/* Error callback functin for tutoral program */
static void tutorial_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);

/* システムの最低限の初期化 */
/* The minimum initialization of the system */
CriBool tutorial_initialize(void);

/* システムの終了処理 */
/* Finalization of the system */
void tutorial_finalize(void);

/* カレントスレッドのスリープ（ミリ秒指定） */
/* Sleep the current thread (in units of msec) */
void tutorial_sleep(CriUint32 msec);

/* デフォルトのヒープからメモリを確保 */
/* Allocate memory from the default heap */
void *tutorial_alloc(void *obj, CriUint32 size);

/* メモリの解放 */
/* Free memory */
void tutorial_free(void *obj, void *ptr);

/* 文字列のデバッグ表示 */
/* debug print to string */
void tutorial_printf(const CriChar8* msg);

/**************************************************************************
 * 変数定義
 * Variable definitions
 **************************************************************************/

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
int main(int argc, char *argv[])
{
	UNUSED(argc);
	UNUSED(argv);

	/* 最低限の初期化 */
	/* Initialization (minimum) */
	tutorial_initialize();

	/* エラーコールバック関数の登録 */
	/* Registeration of error callback function */
	criErr_SetCallback(tutorial_error_callback_func);

	/* メモリアロケータの登録 */
	/* Registeration of memory allocator */
	criAtomEx_SetUserAllocator(tutorial_alloc, tutorial_free, NULL);
	
	/* ライブラリの初期化 */
	/* Library initialization */
	criAtomEx_Initialize_WASAPI(NULL, NULL, 0);
	
	/* ACFファイルの読み込みと登録 */
	/* Load and register ACF file */
	criAtomEx_RegisterAcfFile(NULL, NULL, NULL, 0);
	
	/* ライブラリの終了 */
	/* Library finalization */
	criAtomEx_Finalize_WASAPI();

	/*  最小限の終了処理*/
	/* Finalization (minimum) */
	tutorial_finalize();

	return 0;
}

/* エラーコールバック関数 */
/* Error callback function */
static void tutorial_error_callback_func(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray)
{
	const CriChar8 *errmsg;
	UNUSED(parray);
	/* エラー文字列の表示 */
	/* Display an error message string */
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	tutorial_printf(errmsg);
	return;
}

CriBool tutorial_initialize(void)
{
	return TRUE;
}

void tutorial_finalize(void)
{
}

void tutorial_sleep(CriUint32 msec)
{
	Sleep(msec);
}

void *tutorial_alloc(void *obj, CriUint32 size)
{
	void *ptr;
	UNUSED(obj);
	ptr = malloc(size);
	return ptr;
}

void tutorial_free(void *obj, void *ptr)
{
	UNUSED(obj);
	free(ptr);
}

void tutorial_printf(const CriChar8* msg)
{
	OutputDebugString(msg);
	OutputDebugString("\n");
}

/* --- end of file --- */
