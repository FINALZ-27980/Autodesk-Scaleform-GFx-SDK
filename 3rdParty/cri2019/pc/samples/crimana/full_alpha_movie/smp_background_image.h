#ifndef	_SMP_IMAGE_BACKGROUND_H_INCLUDE
#define	_SMP_IMAGE_BACKGROUND_H_INCLUDE
/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010-2017 CRI Middleware Co., Ltd.
 *
 * Library  : Sample Library
 * Module   : Utility
 * File     : smp_image_background_PC.h
 * Date     : 2014-06-17
 * Version  : 0.61
 *
 * 説明：フルアルファムービ再生時、透過具合を分かりやすくするための背景静止画
 *       描画インタフェース
 *
 * Description: Background still image drawing inteface to easily perceive
 *              how transparent it is for full-alpha movie
 *
 ****************************************************************************/

#include <cri_xpt.h>
#include "smp_video_texture.h"

/***********************************************************************
 *		データ型
 *		Data type declaration
 ***********************************************************************/

/* ピクセル色情報構造体 */
/* Pixel color information structure */
typedef struct {
	CriUint8 r;
	CriUint8 g;
	CriUint8 b;
	CriUint8 a;
} SmpPixelColor;

/* 背景イメージ描画オブジェクト情報構造体 */
/* Background image drawing object information structure */
typedef struct {
	CriSint32	disp_width;		/* 描画幅 */    /* drawing width */
	CriSint32	disp_height;	/* 描画高 */    /* drawaing height */
	CriSint32	xpos;			/* 原点中心 */  /* origin-x */
	CriSint32	ypos;			/* 原点中心 */  /* origin-y */
	CriBool		windowed_flag;	/* False:フルスクリーン, True:ウィンドウ */
	                            /* False:full-screen, True:window */
	SmpVideoTextureHn svt_hn;
} SmpBackgroundImageConfig;

/* 背景イメージ描画オブジェクト構造体 */
/* Background image drawing object structure */
typedef struct {
	SmpBackgroundImageConfig property;	/* 背景イメージ情報 */
	                                    /* background image information */
	void *extra_obj;					/* 機種固有情報構造体ポインタ */
	                                    /* pointer to the target-specific information structure */
} SmpBackgroundImageObj, *SmpBackgroundImageHn;

/***************************************************************************
 *		関数宣言
 *		Function Declaration
 ***************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* ハンドル作成関数 */
/* Handle creation */
SmpBackgroundImageHn smp_background_image_create(const SmpBackgroundImageConfig *config);

/* ハンドル破棄関数 */
/* Handle destruction */
void smp_background_image_destroy(SmpBackgroundImageHn svi_hn);

/* 背景イメージデータのセット関数 */
/* Set background image data */
CriBool smp_background_image_set_data(SmpBackgroundImageHn svi_hn, const void *img_data, CriUint32 data_size, CriUint32 img_width, CriUint32 img_height);

/* 背景イメージデータのリリース関数 */
/* Release background image data */
void smp_background_image_release(SmpBackgroundImageHn sbi_hn);

/* ムービファイルの設定 */
/* Set movie file */
CriBool smp_background_image_set_movie_file(SmpBackgroundImageHn svi_hn, const CriChar8 *filename);

/* ムービファイルの設定（ヘッダ＆ボディ）*/
/* Set movie file (header & body) */
CriBool smp_background_image_set_movie_header_and_body_file(SmpBackgroundImageHn svi_hn, 
	const CriChar8 *header_filename, const CriChar8 *body_filename);

/* イメージの描画 */
/* Draw image */
void smp_background_image_draw(SmpBackgroundImageHn svi_hn);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif	/* _SMP_IMAGE_BACKGROUND_H_INCLUDE */

/* --- end of file --- */
