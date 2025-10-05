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
#ifndef	CRI_INCL_SMP_PROF_THREE_D_H
#define	CRI_INCL_SMP_PROF_THREE_D_H
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
#define NUM_SOURCES		(2)
/**************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 **************************************************************************/

/***************************************************************************
 *      データ型定義
 *      Data Type Declarations
 ***************************************************************************/
/* 音源用構造体 */
/* Sound source structure */
typedef struct AppThreeDSourceTag {
	CriAtomExPlayerHn player;
	CriAtomExPlayerStatus player_status;
	CriAtomEx3dSourceHn source;
	CriAtomExVector pos;
	CriAtomExVector vel;
	CriAtomExVector cone;
	/* 軌道計算用 */
	/* for trajectory calculation */
	CriAtomExVector phase;
	CriAtomExVector ang_vel_factor;
	CriAtomExVector amplitude_factor;
	CriAtomExVector offset;
	CriBool need_update;
} AppThreeDSourceObj;

/* リスナー構造体 */
/* Listener structure */
typedef struct AppThreeDListenerTag {
	CriAtomEx3dListenerHn handle;
	CriAtomExVector pos;
	CriAtomExVector vel;
	CriAtomExVector forward;
	CriAtomExVector upward;
	CriBool auto_move;
	CriBool auto_rotate;
	CriBool need_update;
	/* 起動計算用 */
	/* for trajectory calculation */
	CriFloat32 position_phase;
	CriFloat32 orientation_phase;
} AppThreeDListenerObj;

/* アプリケーション構造体 */
/* Application structure  */
typedef struct AppThreeDTag {
	CriAtomExAcbHn acb_hn;
	AppThreeDSourceObj source[NUM_SOURCES];
	CriBool source_auto_move;
	AppThreeDListenerObj listener;
} AppThreeDObj;

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

void app_three_d_display_info(AppThreeDObj *app_obj);
CriBool app_three_d_initialize(AppThreeDObj *app_obj);
CriBool app_three_d_finalize(AppThreeDObj *app_obj);
CriBool app_three_d_execute_main(AppThreeDObj *app_obj);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif	/* CRI_INCL_SMP_PROF_THREE_D_H */
/* --- end of file --- */
