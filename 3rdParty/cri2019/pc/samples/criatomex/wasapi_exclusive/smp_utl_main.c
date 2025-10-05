/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2015 CRI Middleware Co., Ltd.
 *
 * Library  : Sample Library
 * Module   : Entry Point
 * File     : smp_utl_main.c
 * Date     : 2015-01-14
 * Version  : 1.00
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
#include <stdio.h>
#include <cri_xpt.h>
#include <cri_framework.h>
#include "smp_utl.h"

/***************************************************************************
 *		定数マクロ
 *		Constant Macros
 ***************************************************************************/

/***************************************************************************
 *		処理マクロ
 *		Process Macros
 ***************************************************************************/
/* 未使用引数警告回避マクロ */
#define UNUSED(arg)						{ if ((arg) == (arg)) {} }

/***************************************************************************
 *      変数宣言
 *      Variable Declaration
 ***************************************************************************/

/***************************************************************************
 *      変数定義
 *      Variable Definitions
 ***************************************************************************/

/***************************************************************************
 *		関数宣言
 *		Function Declaration
 ***************************************************************************/

/***************************************************************************
 *		関数定義
 *		Function Definitions
 ***************************************************************************/
int main(int argc, char *argv[])
{
	UNUSED(argc);
	UNUSED(argv);

	/* サンプル用共通ライブラリ初期化 */
	/* Initialization of common libraries for sample */
	criFw_Initialize();

	/* アプリケーション初期化処理 */
	/* Application initialization */
	Sample_Initialize();

	for(;;) {
		/* V同期待ち */
		/* Wait for Vsync */
		criFwSys_WaitVsync();

		/* アプリケーションメイン処理 */
		/* Application main process */
		if (CRI_FALSE == Sample_Update()) {
			/* サンプルの終了 */
			/* Exit sample */
			break;
		}

		/* システムの終了をチェック */
		/* Checking for system termination */
		if (CRI_FALSE != criFwSys_IsTerminated()) {
			/* サンプルの終了 */
			/* Exit sample */
			break;
		}
	}

	/* アプリケーション終了処理 */
	/* Application finalization */
	Sample_Finalize();

	/* サンプル用共通ライブラリ終了 */
	/* Finalization of common libraries for sample */
	criFw_Finalize();

	return (0);
}

/* --- end of file --- */
