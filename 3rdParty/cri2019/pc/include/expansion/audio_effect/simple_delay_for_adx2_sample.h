/****************************************************************************
 *
 * Copyright (c) 2017 CRI Middleware Co., Ltd.
 *
 ****************************************************************************/
/*!
 *	\file		simple_delay_for_adx2_sample.h
 */

/* 多重定義防止 */
/* Prevention of redefinition */
#ifndef	SIMPLE_DELAY_FOR_ADX2_SAMPLE_H_INCLUDED
#define	SIMPLE_DELAY_FOR_ADX2_SAMPLE_H_INCLUDED

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
#include <cri_atom_asr.h>

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/

/*!
 * \brief 最大遅延時間[ms]
 * \par 説明:
 * ディレイの最大遅延時間を指定します。<br>
 * 動作時にはディレイの最大値はこのインデックスで指定した値に制限されます。
 */
#define SIMPLE_DELAY_MAX_DELAY_TIME_MS				1000

/*!
 * \brief 遅延時間[ms]
 * \par 説明:
 * このインデックスにディレイの遅延時間を指定します。
 */
#define SIMPLE_DELAY_PARAMETER_DELAY_TIME_MS		0
/*!
 * \brief 出力ゲイン
 * \par 説明:
 * このインデックスにディレイをかけた音声に対して乗ずるゲインを指定します。
 */
#define SIMPLE_DELAY_PARAMETER_OUTPUT_GAIN			1
/*!
 * \brief ディレイの動作時パラメタ数
 */
#define SIMPLE_DELAY_NUM_PARAMETERS					2

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief ディレイエフェクトのバージョン情報付きインターフェースを取得
 * \return バージョン情報付きインターフェース
 * \par 説明:
 * ディレイエフェクトのバージョン情報付きインターフェースを取得します。
 */
CriAtomExAsrAfxInterfaceWithVersionPtr simpleDelay_GetInterfaceWithVersion(void);

#ifdef __cplusplus
}
#endif

#endif	/* SIMPLE_DELAY_FOR_ADX2_SAMPLE_H_INCLUDED */
