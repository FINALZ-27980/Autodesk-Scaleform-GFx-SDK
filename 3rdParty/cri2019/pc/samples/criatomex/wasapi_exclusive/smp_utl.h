/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2008-2016 CRI Middleware Co., Ltd.
 *
 * Library  : Sample Library
 * Module   : Utility
 * File     : smp_utl.h
 * Date     : 2016-02-25
 * Version  : 1.02
 *
 ****************************************************************************/
 /*!
 *	\file		smp_utl.h
 */

/* 多重定義防止					*/
/* Prevention of redefinition	*/
#ifndef	CRI_INCL_SMP_UTL_H
#define	CRI_INCL_SMP_UTL_H

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
#include "cri_xpt.h"
#include "cri_atom_ex.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
#if defined(XPT_TGT_PSP)
	#define SUPPORT_6CH_AUDIO		(FALSE)
#elif defined(XPT_TGT_WII)
	#define SUPPORT_6CH_AUDIO		(FALSE)
#else
	#define SUPPORT_6CH_AUDIO		(TRUE)
#endif

/***************************************************************************
 *      処理マクロ
 *      Macro Functions
 ***************************************************************************/
/* 未使用引数警告回避マクロ */
/* Macro to prevent an unused argument warning from being displayed */
#ifndef SMPUTL_UNUSED
#define SMPUTL_UNUSED(arg)				{ if (&(arg) == &(arg)) {} }
#endif

/***************************************************************************
 *      データ型宣言
 *      Data Type Declarations
 ***************************************************************************/

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

/* 必要なリソースのロード */
/* Load necessary resource */
void Sample_Preload(void);

/* 起動準備完了チェック */
/* Check completion of startup preparation */
CriBool Sample_IsReady(void);

/* 初期化処理 */
/* Initialization */
void Sample_Initialize(void);

/* 更新処理 */
/* Update processing */
CriBool Sample_Update(void);

/* 終了処理 */
/* Finalization */
void Sample_Finalize(void);

/* 後始末 */
/* Cleanup processing */
void Sample_Dispose(void);

/* システムの最低限の初期化に必要なワーク領域サイズの計算 */
/* Calculation of work size for the library initialization */
CriSint32 smputl_calculate_work_size(const CriAtomExConfig *config);

/* システムの最低限の初期化 */
/* The minimal initialization of the system */
CriBool smputl_initialize(const CriAtomExConfig *config, void *work, CriSint32 work_size);

/* システムの終了処理 */
/* Finalization of the system */
void smputl_finalize(void);

/* ボイスプールの作成 */
/* Create voice pool */
void smputl_allocate_voice_pool(void);

/* ボイスプールの破棄 */
/* Destroy voice pool */
void smputl_free_voice_pool(void);

/* アセットパスの生成 */
/* Make asset path */
void smputl_get_asset_path(CriChar8 *dest, const CriChar8 *rel_path, CriSint32 n);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif	/* CRI_INCL_SMP_UTL_H */

/* --- end of file --- */

