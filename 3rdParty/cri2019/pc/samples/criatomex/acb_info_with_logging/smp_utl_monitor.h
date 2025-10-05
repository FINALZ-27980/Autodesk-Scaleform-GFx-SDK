/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2008-2011 CRI Middleware Co., Ltd.
 *
 * Library  : Sample Library
 * Module   : Utility
 * File     : smp_utl_monitor.h
 * Date     : 2011-06-03
 * Version  : 1.00
 *
 ****************************************************************************/
 /*!
 *	\file		smp_utl.h
 */

/* 多重定義防止					*/
/* Prevention of redefinition	*/
#ifndef	CRI_INCL_SMP_UTL_MONITOR_H
#define	CRI_INCL_SMP_UTL_MONITOR_H

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
#include "cri_xpt.h"
#include "cri_atom_ex_monitor.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/

/***************************************************************************
 *      処理マクロ
 *      Macro Functions
 ***************************************************************************/

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

/* システムの最低限の初期化に必要なワーク領域サイズの計算 */
/* Calculation of work size for the library initialization */
CriSint32 smputl_monitor_calculate_work_size(const CriAtomExMonitorConfig *config);

/* システムの最低限の初期化 */
/* The minimal initialization of the system */
CriBool smputl_monitor_initialize(const CriAtomExMonitorConfig *config, void *work, CriSint32 work_size);

/* システムの終了処理 */
/* Finalization of the system */
void smputl_monitor_finalize(void);
	
/* サーバー処理 */
/* Server function of the system */
void smputl_monitor_execute(void);
	
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif	/* CRI_INCL_SMP_UTL_MONITOR_H */

/* --- end of file --- */

