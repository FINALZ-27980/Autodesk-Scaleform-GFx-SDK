/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2014 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Detailed Voice playback sample for Profiler
 *         : プロファイラ用のボイス詳細設定サンプル
 * File    : for_profiler_simple.c
 *
 ****************************************************************************/

/* 多重定義防止					*/
/* Prevention of redefinition	*/
#ifndef	CRI_INCL_SMP_PROF_VOICE_DETAIL_H
#define	CRI_INCL_SMP_PROF_VOICE_DETAIL_H
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
typedef struct AppVoiceDetailTag{
	CriAtomExVoicePoolHn adx_pool_hn;
	CriAtomExPlayerHn player_adx;
	CriAtomExPlayerHn player_hca;
	CriAtomExAcbHn acb_hn;
} AppVoiceDetailObj;

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
void app_voice_detail_initialize(AppVoiceDetailObj* voice_detail_obj);
/* 単純再生サンプルの終了処理 */
/* Finalize simple playback sample */
void app_voice_detail_finalize(AppVoiceDetailObj *voice_detail_obj);
/* 画面に情報を表示する */
/* Display information on screen */
void app_voice_detail_display_info(AppVoiceDetailObj *voice_detail_obj);
/* 画面表示以外の処理をする */
/* Execute except displaying */
CriBool app_voice_detail_execute_main(AppVoiceDetailObj *voice_detail_obj);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif	/* CRI_INCL_SMP_PROF_VOICE_DETAIL_H */
/* --- end of file --- */
