/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2014 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Simple playback sample for Profiler
 *         : プロファイラ用の単純再生サンプル
 * File    : for_profiler_simple.c
 *
 ****************************************************************************/

/* 多重定義防止					*/
/* Prevention of redefinition	*/
#ifndef	CRI_INCL_SMP_PROF_SIMPLE_H
#define	CRI_INCL_SMP_PROF_SIMPLE_H
/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
/* CRI SDK header file */
#include <cri_xpt.h>

/* CRI ADX2 header file */
#include <cri_atom_ex.h>
/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/

/**************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 **************************************************************************/

/***************************************************************************
 *      データ型定義
 *      Data Type Declarations
 ***************************************************************************/
/* アプリケーション構造体 */
/* Application structure  */
typedef struct AppSimpleTag{
	CriAtomExPlayerHn player_se;
	CriAtomExPlayerHn player_bgm;
	CriAtomExAcbHn acb_hn;
	CriAtomExPlayerStatus player_status_se;
	CriAtomExPlayerStatus player_status_bgm;
} AppSimpleObj;

/***************************************************************************
 *      変数宣言
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 単純再生サンプルの初期化 */
/* Initialize simple playback sample */
void app_simple_initialize(AppSimpleObj* simple_obj);
/* 単純再生サンプルの終了処理 */
/* Finalize simple playback sample */
void app_simple_finalize(AppSimpleObj *simple_obj);
/* 画面に情報を表示する */
/* Display information on screen */
void app_simple_display_info(AppSimpleObj *simple_obj);
/* 画面表示以外の処理をする */
/* Execute except displaying */
CriBool app_simple_execute_main(AppSimpleObj *simple_obj);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif	/* CRI_INCL_SMP_PROF_SIMPLE_H */
/* --- end of file --- */
