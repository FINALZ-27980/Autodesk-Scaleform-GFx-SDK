#ifndef	CRI_INCL_SMP_VIDEO_TEXTURE_H
#define	CRI_INCL_SMP_VIDEO_TEXTURE_H
/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010-2019 CRI Middleware Co., Ltd.
 *
 * Library  : Sample Library
 * Module   : Utility
 * File     : smp_video_texture.h
 * Date     : 2019-02-22
 * Version  : 0.83
 *
 * 説明：
 *  一つの描画スクリーンに対して、一つのムービ描画を想定。
 *  複数のスクリーンを作成すれば、マルチ再生もできる。
 *
 * Description：
 *  Assumes that one movie is rendered on one screen.
 *  If multiple screens are created, multi-playback will also be supported.
 *
 ****************************************************************************/

#include <cri_xpt.h>
#include <cri_mana.h>

/***********************************************************************
 *		データ型
 *		Data type declaration
 ***********************************************************************/

/* ビデオ描画テクスチャ情報 */
/* Video drawing texture information */
typedef struct {
	const CriChar8 *name;		/* PC用。複数ウィンドウの作成に必要 */
	                            /* For PC. Required to create multiple windows. */
	CriSint32	width;
	CriSint32	height;
	CriSint32	xpos;			/* 原点中心 */	/* origin-x */
	CriSint32	ypos;			/* 原点中心 */	/* origin-y */
	CriBool		windowed_flag;	/* False:フルスクリーン, True:ウィンドウ */
	                            /* False:full-screen, True:Window */
	CriBool		use_alpha;		/* アルファチャンネルを使用するかどうか  */
	                            /* Whether to use alpha-channel or not */
} SmpVideoTextureConfig;

/* ビデオ描画スクリーンオブジェクト */
/* Video drawing screen object */
typedef struct {
	struct _smp_video_texture_vtbl *vtbl;	/* インタフェース */
	                                        /* Interface */
	SmpVideoTextureConfig property;			/* テクスチャ情報 */
	                                        /* Texture information */
	void *extra_obj;	/* 機種固有情報構造体ポインタ */
	                    /* Pointer to the target-specific information structure */
} SmpVideoTextureObj, *SmpVideoTextureHn;

/* インタフェース関数 */
/* Interface function */
typedef struct _smp_video_texture_vtbl {

	/* ハンドルの破棄 */
	/* Destroy handle */
	void (*Destroy)(SmpVideoTextureHn tex);

	/* テクスチャバッファ領域のロック(内部バッファの割り当て) */
	/* Lock texture buffer area (to allocate internal buffer) */
	void (*LockBuffer)(SmpVideoTextureHn tex, void* texbuf);
	
	/* テクスチャバッファ領域のアンロック(内部バッファの割り当て解除) */
	/* Unlock texture buffer area (to deallocate internal buffer) */
	void (*UnLockBuffer)(SmpVideoTextureHn tex);

	/* テクスチャ描画の前処理 (必要な機種のみ実装) */
	/* Pre-processing for texture drawing (to be implemented for the corresponding platform) */
	void (*BeginDraw)(SmpVideoTextureHn tex);

	/* テクスチャの描画 */
	/* Draw texture */
	void (*Draw)(SmpVideoTextureHn tex);

	/* テクスチャ描画の後処理 (必要な機種のみ実装) */
	/* Post-processing for texture drawing (to be implemented for the corresponding platform) */
	void (*EndDraw)(SmpVideoTextureHn tex);

	/* テクスチャ描画領域の移動 */
	/* Move the texture drawing area */
	void (*Move)(SmpVideoTextureHn tex, CriSint32 xpos, CriSint32 ypos);
	
	/* テクスチャ描画領域のリサイズ */
	/* Resize the texture drawing area */
	void (*Resize)(SmpVideoTextureHn tex, CriSint32 width, CriSint32 height);

	/* テクスチャバッファ領域のバインド(外部バッファの登録) */
	/* Bind texture buffer area (to register external buffer) */
	void (*Bind)(SmpVideoTextureHn tex, void* texbuf);

	/* テクスチャバッファ領域のアンバインド(外部バッファの登録削除) */
	/* Unbind texture buffer area (to unregister external buffer) */
	void (*UnBind)(SmpVideoTextureHn tex);

} SmpVideoTexture_IF;

/****************************************************************************
 *		関数の宣言
 *		Function Declaration
 ****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* テクスチャハンドルの作成 */
/* Create texture handle */
SmpVideoTextureHn smpvideo_texture_create(const SmpVideoTextureConfig *config);

/* YUV個別3枚テクスチャハンドルの作成 */
/* Create texture handle for separate YUV 3 planes */
SmpVideoTextureHn smpvideo_texture_create_YUVA(const SmpVideoTextureConfig *config);

/* 32ビットRGBAテクスチャハンドルの作成 */
/* Create texture handle for 32-bit RGBA */
SmpVideoTextureHn smpvideo_texture_create_RGBA32(const SmpVideoTextureConfig *config);

/* [機種固有] YUV420(P3)テクスチャハンドルの作成 */
/* [Target-specific] Create texture handle for YUV420(P3) */
SmpVideoTextureHn smpvideo_texture_create_YUV420P3(const SmpVideoTextureConfig *config);

/* [機種固有] YUV420(P2)テクスチャハンドルの作成 */
/* [Target-specific] Create texture handle for YUV420(P2) */
SmpVideoTextureHn smpvideo_texture_create_YUV420P2(const SmpVideoTextureConfig *config);

/* [機種固有] デバイス解像度の設定 */
/* [Target-specific] Set Device Resolution */
void smpvideo_set_device_resolution(const CriSint32 width, const CriSint32 height);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/****************************************************************************
 *		アプリ呼び出し用関数マクロ
 ****************************************************************************/

/* ハンドルの破棄 */
/* Destroy handle */
#define smpvideo_texture_destroy(tex) \
	if (tex && tex->vtbl->Destroy) (*(tex)->vtbl->Destroy)(tex)

/* テクスチャバッファ領域のロック(内部バッファの割り当て) */
/* Lock texture buffer area (to allocate internal buffer) */
#define smpvideo_texture_lock_buffer(tex, texbuf) \
	if (tex && tex->vtbl->LockBuffer) (*(tex)->vtbl->LockBuffer)(tex, texbuf)

/* テクスチャバッファ領域のアンロック(内部バッファの割り当て解除) */
/* Unlock texture buffer area (to deallocate internal buffer) */
#define smpvideo_texture_unlock_buffer(tex) \
	if (tex && tex->vtbl->UnLockBuffer) (*(tex)->vtbl->UnLockBuffer)(tex)

/* テクスチャバッファ領域のバインド(外部バッファの登録) */
/* Bind texture buffer area (to register external buffer) */
#define smpvideo_texture_bind_buffer(tex, texbuf) \
	if (tex && tex->vtbl->Bind) (*(tex)->vtbl->Bind)(tex, texbuf)
	
/* テクスチャバッファ領域のアンバインド(外部バッファの登録削除) */
/* Unbind texture buffer area (to unregister external buffer) */
#define smpvideo_texture_unbind_buffer(tex) \
	if (tex && tex->vtbl->UnBind) (*(tex)->vtbl->UnBind)(tex)

/* テクスチャ描画の前処理 */
/* Pre-processing for texture drawing */
#define smpvideo_texture_begin_draw(tex) \
	if (tex && tex->vtbl->BeginDraw) (*(tex)->vtbl->BeginDraw)(tex)

/* テクスチャの描画 */
/* Draw texture */
#define smpvideo_texture_draw(tex) \
	if (tex && tex->vtbl->Draw) (*(tex)->vtbl->Draw)(tex)

/* テクスチャ描画の後処理 */
/* Post-processing for texture drawing */
#define smpvideo_texture_end_draw(tex) \
	if (tex && tex->vtbl->EndDraw) (*(tex)->vtbl->EndDraw)(tex)

/* テクスチャ描画領域の移動 */
/* Move the texture drawing area */
#define smpvideo_texture_move(tex, xpos, ypos) \
	if (tex && tex->vtbl->Move) (*(tex)->vtbl->Move)(tex, xpos, ypos);

/* テクスチャ描画領域のリサイズ */
/* Resize the texture drawing area */
#define smpvideo_texture_resize(tex, width, height) \
	if (tex && tex->vtbl->Resize) (*(tex)->vtbl->Resize)(tex, width, height);


#endif	/* CRI_INCL_SMP_VIDEO_TEXTURE_H */

/* --- end of file --- */
