/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010-2017 CRI Middleware Co., Ltd.
 *
 * Title   : CRI Mana Sample Program
 * Module  : Playback by Setting Work Buffers
 *
 * Description :
 *  メモリ関数を登録せず、ヘッダ解析して必要なワークバッファをアプリから
 *  割り当てるサンプルです。
 *
 * Description :
 *  This is a sample program that analyzes movie header to allocate 
 *  the required work buffers from the application.
 * 
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
/* CRI SDK Header */
#include <cri_xpt.h>
#include <cri_atom_ex.h>
#include <cri_atom_wasapi.h>
/* CRI Sofdec2 Header */
#include <cri_mana.h>

/* CRI Sample Framework Header */
#include <cri_framework.h>

/* サンプル動画描画ヘッダ */
/* Sample movie drawing header */
#include "smp_video_texture.h"

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define PATH_MANA		"../../../../../common/smpdata/crimana/"
#define USM_FILE		PATH_MANA "sample.usm"

/* メモリアライメント */
/* Memory alignment */
#define SMPUTL_MEM_ALIGN	(32)

/***************************************************************************
 *      処理マクロ
 *      Macro Functions
 ***************************************************************************/
/* 未使用引数警告回避マクロ */
/* Macro to prevent an unused arguments warning from being displayed */
#ifndef SMPUTL_UNUSED
#define SMPUTL_UNUSED(arg)				{ if (&(arg) == &(arg)) {} }
#endif

/**************************************************************************
 * 型定義
 **************************************************************************/
/* アプリケーション構造体 */
/* Application structure  */
typedef struct AppTag{
	CriSint32				size_atom_libwork;
	void					*buf_atom_libwork;
	CriSint32				size_mana_libwork;
	void					*buf_mana_libwork;
	CriSint32				size_mana_hnwork;
	void					*buf_mana_hnwork;
	CriSint32				size_mana_playwork;
	void					*buf_mana_playwork;

	CriManaPlayerHn			player;
	CriManaPlayerStatus		player_status;
	SmpVideoTextureHn		svt;

	CriManaFrameInfo	frame_info;
	CriUint64			playing_tcount;
	CriUint64			playing_tunit;
} AppObj;

/**************************************************************************
 * 関数宣言
 **************************************************************************/
/* エラーコールバック関数 */
/* Error callback function */
static void user_error_callback_func(
	const Char8 *errid, Uint32 p1, Uint32 p2, Uint32 *parray);

/* メモリ関数 */
/* Memory function */
static void *user_alloc(void *obj, CriUint32 size);
static void user_free(void *obj, void *ptr);

/* ムービの再生制御 */
/* Movie playback control */
static CriBool app_mana_initialize(AppObj *app_obj);
static CriBool app_mana_finalize(AppObj *app_obj);
static CriBool app_mana_start(AppObj *app_obj);
static CriBool app_mana_stop(AppObj *app_obj);
static CriBool app_mana_stop_complete(AppObj *app_obj);
static CriBool app_execute_main(AppObj *app_obj);
static CriBool app_update_frame(AppObj *app_obj);
static void app_display_info(AppObj *app_obj);

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
Sint32 main(Sint32 argc, Char8 *argv[])
{
	AppObj app_obj;
	CriBool ret;
	SMPUTL_UNUSED(argc);
	SMPUTL_UNUSED(argv);

	/* サンプル用共通ライブラリ初期化 */
	/* Initialization of common libraries for samples */
	criFw_Initialize();

	/* アプリケーション初期化処理 */
	/* Application initialization */
	app_mana_initialize(&app_obj);

	/* ヘッダ解析開始 */
	/* Start header analysis */
	ret = app_mana_start(&app_obj);

	/* ヘッダ解析成功 */
	/* Succeeded in the header analysis */
	if (ret == CRI_TRUE) {
		for(;;) {
			/* アプリケーションメイン処理 */
			/* Application main process  */
			if (CRI_FALSE == app_execute_main(&app_obj)) {
				/* 再生終了 */
				/* Finished playback */
				break;
			}
			/* システムの終了をチェック */
			/* Check for system termination */
			if (CRI_FALSE != criFwSys_IsTerminated()) {
				/* サンプルの終了 */
				/* Exit this sample */
				app_mana_stop_complete(&app_obj);
				break;
			}
	
			/* ビデオフレームの更新 */
			/* Update video frame */
			app_update_frame(&app_obj);
	
			/* 情報表示 */
			/* Display information */
			app_display_info(&app_obj);
	
			/* V同期待ち */
			/* Wait for V-sync */
			criFwSys_WaitVsync();
		}
	} else {
		criFwPrt_DebugPrintf("Failed DecodeHeader.\n");
	}

	/* アプリケーション終了処理 */
	/* Application finalization */
	app_mana_finalize(&app_obj);

	/* サンプル用共通ライブラリ終了 */
	/* Finalization of common libraries for samples */
	criFw_Finalize();

}


/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriSint32 x, y;
	CriChar8 *str_status[] = {"STOP", "DECHDR", "WAIT_PREP", "PREP", "READY", "PLAYING", "PLAYEND", "ERROR"};

	x = 2; y = 1;
	criFwPrt_DrawText(x, y, "[CRI Mana: Simple playback]"); y++;
	/* Sofdec2ライブラリのバージョン情報を出力 */
	/* Display the version information of the Sofdec2 library */
	criFwPrt_DrawText(x, y, "Lib Ver: %s", criMana_GetLibraryVersionString()); y++; y++;

	/* ステータスの表示 */
	/* Display the status */
	criFwPrt_DrawText(x, y, "Player Status: %s", str_status[app_obj->player_status]); y++;
	/* 再生時刻の表示 */
	/* Display the playback time */
	criFwPrt_DrawText(x, y, "Playing Time : %6.2f[sec]", (Float32)app_obj->playing_tcount / app_obj->playing_tunit); y++;
	/* フレーム番号の表示 */
	/* Display the frame number */
	criFwPrt_DrawText(x, y, "Frame No.    : %d", app_obj->frame_info.frame_no); y++;
}

CriBool app_mana_initialize(AppObj *app_obj)
{
	/* エラーコールバック関数の登録 */
	/* Registration of error callback function */
	criErr_SetCallback(user_error_callback_func);

	/* ADX2,Sofdec2 にメモリアロケータを登録 */
	/* Registration of memory allocator for ADX2/Sofdec2 */
	//criAtomEx_SetUserAllocator(user_alloc, user_free, NULL);
	//criMana_SetUserAllocator(user_alloc, user_free, NULL);

	/* CRI AtomExライブラリの初期化 (必ずManaの初期化の前に行ってください) */
	/* Initialize the CRI AtomEx library (Be sure to do this before the Mana initialization) */
	app_obj->size_atom_libwork = criAtomEx_CalculateWorkSize_WASAPI(NULL);
	criFwPrt_DebugPrintf("[Work: AtomEx Lib]\n");
	app_obj->buf_atom_libwork = criFwMem_Alloc(app_obj->size_atom_libwork, SMPUTL_MEM_ALIGN);
	criAtomEx_Initialize_WASAPI(NULL, app_obj->buf_atom_libwork, app_obj->size_atom_libwork);

	/* CRI Manaライブラリの初期化（デフォルトでマルチスレッドモデル） */
	/* Initialize the CRI Mana library (with multithread model by default) */
	app_obj->size_mana_libwork = criMana_CalculateLibWorkSize(NULL);
	criFwPrt_DebugPrintf("[Work: Mana Lib]\n");
	app_obj->buf_mana_libwork = criFwMem_Alloc(app_obj->size_mana_libwork, SMPUTL_MEM_ALIGN);
	criMana_Initialize(NULL, app_obj->buf_mana_libwork, app_obj->size_mana_libwork);

	/* プレーヤの作成 */
	/* Create a player */
	app_obj->size_mana_hnwork = criManaPlayer_CalculateHanldeWorkSize();
	criFwPrt_DebugPrintf("[Work: Mana Player]\n");
	app_obj->buf_mana_hnwork = criFwMem_Alloc(app_obj->size_mana_hnwork, SMPUTL_MEM_ALIGN);
	app_obj->player = criManaPlayer_Create(app_obj->buf_mana_hnwork, app_obj->size_mana_hnwork);
	/* フレームプール数の設定 */
	/* Set the number of frame pools */
	criManaPlayer_SetNumberOfFramePools(app_obj->player, 2);
	/* プレーヤのステータス取得（変数初期化） */
	/* Get the player status (variable initialization) */
	app_obj->player_status = criManaPlayer_GetStatus(app_obj->player);

	/* メタデータ用メモリ関数の登録 */
	/* Registration of meta data allocation function */
	criManaPlayer_SetMetaDataWorkAllocator(app_obj->player, user_alloc, user_free, NULL, CRIMANA_META_FLAG_ALL);

	return CRI_TRUE;
}

CriBool app_mana_finalize(AppObj *app_obj)
{
	/* 動画テクスチャの破棄 */
	/* Destroy the texture for movie */
	smpvideo_texture_destroy(app_obj->svt);	

	/* プレーヤハンドルの破棄 */
	/* Destroy the player handle */
	criManaPlayer_Destroy(app_obj->player);

	/* Manaライブラリの終了 */
	/* Finish the Mana library */
	criMana_Finalize();

	/* AtomExライブラリの終了 */
	/* Finish the AtomEx library */
	criAtomEx_Finalize_WASAPI();

	/* ワーク解放 */
	/* Release the work buffers */
	if (app_obj->buf_atom_libwork != NULL) { criFwMem_Free(app_obj->buf_atom_libwork); app_obj->buf_atom_libwork = NULL;}
	if (app_obj->buf_mana_libwork != NULL) { criFwMem_Free(app_obj->buf_mana_libwork); app_obj->buf_mana_libwork = NULL;}
	if (app_obj->buf_mana_hnwork != NULL) { criFwMem_Free(app_obj->buf_mana_hnwork); app_obj->buf_mana_hnwork = NULL;}
	if (app_obj->buf_mana_playwork != NULL) { criFwMem_Free(app_obj->buf_mana_playwork); app_obj->buf_mana_playwork = NULL;}

	return CRI_TRUE;
}

CriBool app_mana_start(AppObj *app_obj)
{
	CriManaMovieInfo mvinf;
	CriManaVideoInfo *video;
	SmpVideoTextureConfig svt_config = {0};

	/* ムービファイルの指定 */
	/* Specify a movie file */
	criManaPlayer_SetFile(app_obj->player, NULL, USM_FILE);
	/* ヘッダ解析開始 */
	/* Start header analysis */
	criManaPlayer_DecodeHeader(app_obj->player);
	/* 情報表示用のパラメータクリア */
	/* Clear parameters for information display */
	app_obj->frame_info.frame_no = -1;

	/* ヘッダ解析終了待ちループ */
	/* ※本サンプルでは処理を明確にするためにローカルループで組んでいますが、
	 *   実アプリではローカルループで組むと処理落ちにつながります。
	 *   ヘッダ解析の終了待ちもメインループに組み込むことをオススメします。
	 */
	/* [Note] This sample implements a local loop to clearly define each process,  */
	/*        but this may cause a slowdown in an actual application.              */
	/*        It is recommended that the wait for completion of header analysis    */
	/*        should also be included in the main loop.                            */
	/* Wait loop for completion of header analysis */
	for(;;) {
		const CriFwPadStatus	*pad_status;
		/* パッド状態の取得 */
		/* Get the pad status */
		pad_status = criFwPad_GetStatus(0);
		if (pad_status->down & CRIFWPAD_BUTTON08) {
			/* サンプルの途中強制終了 */
			/* Exit the sample forcibly */
			app_mana_stop_complete(app_obj);
			return CRI_FALSE;
		}
	
		criAtomEx_ExecuteMain();
		criMana_ExecuteMain();
	
		/* Manaプレーヤのステータス取得 */
		/* Get the Mana player status */
		app_obj->player_status = criManaPlayer_GetStatus(app_obj->player);
		/* ヘッダ情報が取得できたらループを抜ける */
		/* Exit the loop if the header information is retrieved */
		if (criManaPlayer_GetMovieInfo(app_obj->player, &mvinf) == CRI_TRUE) {
			break;
		}
	
		/* エラー状態の検知 */
		/* Detect an error status */
		if (app_obj->player_status == CRIMANAPLAYER_STATUS_ERROR) {
			/* もしエラー状態になったらハンドルを停止する */
			/* If it becomes an error status, then stop the handle. */
			app_mana_stop(app_obj);
		}
		if (app_obj->player_status == CRIMANAPLAYER_STATUS_STOP) {
			/* STOP状態ということはエラーが発生した */
			/* The STOP means an error occurred. */
			return CRI_FALSE;
		}

		/* システムの終了をチェック */
		/* Check for system termination */
		if (CRI_FALSE != criFwSys_IsTerminated()) {
			/* サンプルの終了 */
			/* Exit this sample */
			app_mana_stop_complete(app_obj);
			return CRI_FALSE;
		}

		/* V同期待ち */
		/* Wait for V-sync */
		criFwSys_WaitVsync();
	}

	/* ムービ情報の確認 */
	/* Display the movie information */
	if (mvinf.is_playable != CRI_TRUE) {
		criFwPrt_DebugPrintf("This movie file is not playable on this platform.\n");
		return CRI_FALSE;
	}
	video = &mvinf.video_prm[0];
	criFwPrt_DebugPrintf("#################################\n");
	criFwPrt_DebugPrintf("(%d, %d), %d[fps], %d[Frames]\n", video->width, video->height, video->framerate, video->total_frames);
	criFwPrt_DebugPrintf("#################################\n");

	/* ムービ仕様にあわせて、動画テクスチャの作成 */
	/* Create a movie texture based on the movie specification */
	svt_config.width  = video->width;
	svt_config.height = video->height;
	if (mvinf.num_alpha_streams == 1) {
		svt_config.use_alpha = CRI_TRUE;
	} else {
		svt_config.use_alpha = CRI_FALSE;
	}
	svt_config.windowed_flag = CRI_TRUE;
	app_obj->svt = smpvideo_texture_create_YUVA(&svt_config);

	/* 再生用ワークバッファの設定 */
	/* Configure the work buffer for playback */
	{
		CriManaPlaybackBasicWorkConfig config_basic;
		CriManaPlaybackExWorkConfig config_ex;
		criManaPlayer_GetPlaybackWorkParam(app_obj->player, &config_basic, &config_ex);
		/* 必要ならここでパラメータ調整 */
		/* Adjust parameters here if needed */
		app_obj->size_mana_playwork = criManaPlayer_CalculatePlaybackWorkSize(app_obj->player, &config_basic, &config_ex);
		criFwPrt_DebugPrintf("[Work: Mana Playback]\n");
		app_obj->buf_mana_playwork = criFwMem_Alloc(app_obj->size_mana_playwork, SMPUTL_MEM_ALIGN);
		criManaPlayer_SetPlaybackWork(app_obj->player, &config_basic, &config_ex, app_obj->buf_mana_playwork, app_obj->size_mana_playwork);
	}

	/* ムービ再生の開始 */
	/* Start movie playback */
	criManaPlayer_Start(app_obj->player);

	return CRI_TRUE;
}

CriBool app_mana_stop(AppObj *app_obj)
{
	/* API名変更 @Ver.1.10 */
	/* Changed the API name @Ver.1.10 */
	//criManaPlayer_RequestStop(app_obj->player);
	criManaPlayer_Stop(app_obj->player);
	
	return CRI_TRUE;
}

/* 完了復帰で再生停止を待つ */
/* Wait for completion of playback in synchronous mode */
CriBool app_mana_stop_complete(AppObj *app_obj)
{
	app_mana_stop(app_obj);
	for(;;) {
		criAtomEx_ExecuteMain();
		criMana_ExecuteMain();
		/* 再生終了 or 停止状態になるのを待つ */
		/* Wait until the status becomes playend or stop */
		app_obj->player_status = criManaPlayer_GetStatus(app_obj->player);
		if (app_obj->player_status == CRIMANAPLAYER_STATUS_PLAYEND ||
			app_obj->player_status == CRIMANAPLAYER_STATUS_STOP) {
			break;
		}
		if (app_obj->player_status == CRIMANAPLAYER_STATUS_ERROR) {
			/* 停止処理中にエラーになったらもう一度 */
			/* Try again if an error occurred during the stop process. */
			app_mana_stop(app_obj);
		}
		/* デコードスレッド駆動のために定期的に寝て待つ */
		/* Sleep and wait regularly to invoke the decoding thread. */
		criFwSys_WaitVsync();
	}

	return CRI_TRUE;
}

CriBool app_execute_main(AppObj *app_obj)
{
	const CriFwPadStatus	*pad_status;
	/* パッド状態の取得 */
	/* Get the pad status */
	pad_status = criFwPad_GetStatus(0);
	if (pad_status->down & CRIFWPAD_BUTTON08) {
		/* サンプルの途中強制終了 */
		/* Exit the sample forcibly */
		app_mana_stop_complete(app_obj);
		return CRI_FALSE;
	}

	if (pad_status->down & CRIFWPAD_BUTTON01) {
		/* 再生中止(即時復帰) */
		/* Cancel playback (asynchronously) */
		app_mana_stop(app_obj);
	}

	/* [定期処理] Atom側のサーバ処理を実行 */
	/* [Periodic processing] Execute Atom's server processing */
	criAtomEx_ExecuteMain();

	/* [定期処理] ムービ時刻の同期 */
	/* [Periodic processing] Synchronize the movie time */
	criMana_SyncMasterTimer();
	/* [定期処理] サーバ処理の実行 */
	/* [Periodic processing] Execute the server processing */
	criMana_ExecuteMain();

	/* Manaプレーヤのステータス取得 */
	/* Get the Mana player status */
	app_obj->player_status = criManaPlayer_GetStatus(app_obj->player);
	/* 再生時刻の取得 */
	/* Get the playback time */
	criManaPlayer_GetTime(app_obj->player, &app_obj->playing_tcount, &app_obj->playing_tunit);

	/* 再生終了 or 停止状態ならアプリ終了を要求 */
	/* Issue a request for application termination if the status is playend or stop. */
	if (app_obj->player_status == CRIMANAPLAYER_STATUS_PLAYEND ||
		app_obj->player_status == CRIMANAPLAYER_STATUS_STOP) {
		return CRI_FALSE;
	}

	/* エラー状態の検知 */
	/* Detect an error status */
	if (app_obj->player_status == CRIMANAPLAYER_STATUS_ERROR) {
		/* もしエラー状態になったらハンドルを停止する */
		/* If it becomes an error status, then stop the handle. */
		app_mana_stop(app_obj);
	}

	return CRI_TRUE;
}

static CriBool app_update_frame(AppObj *app_obj)
{
	CriManaFrameInfo frame_info;

	/* フレームプールにデコード済みのフレームがあるか？ */
	/* Any decoded frames in the frame pool? */
	if (criManaPlayer_ReferFrame(app_obj->player, &frame_info) == CRI_TRUE) {

		/* フレームが表示時刻になっているか？ */
		/* The frame is on time for display time? */
		if (criManaPlayer_IsFrameOnTime(app_obj->player, &frame_info) == CRI_TRUE) {
			CriManaTextureBuffersYUV yuvbufs;
			
			/* シェーダー用にフレームバッファのコピー */
			/* Copy the frame buffer for shader */
			smpvideo_texture_lock_buffer(app_obj->svt, &yuvbufs);
			criManaPlayer_CopyFrameToBuffersYUV(app_obj->player, &frame_info, &yuvbufs);
			smpvideo_texture_unlock_buffer(app_obj->svt);

			/* 描画し終わったのでフレームを破棄 */
			/* Destroy the frame because drawing is completed. */
			criManaPlayer_DiscardFrame(app_obj->player, &frame_info);

			/* 描画したフレームの情報を参考に記録しておく */
			/* Store the information of drawn frame for later reference */
			app_obj->frame_info = frame_info;
		}
	}

	/* 描画 */
	/* Drawing */
	smpvideo_texture_begin_draw(app_obj->svt);
	smpvideo_texture_draw(app_obj->svt);
	smpvideo_texture_end_draw(app_obj->svt);


	return CRI_TRUE;
}

/* エラーコールバック関数 */
/* error callback function */
static void user_error_callback_func(const Char8 *errid, Uint32 p1, Uint32 p2, Uint32 *parray)
{
	const Char8 *errmsg;
	SMPUTL_UNUSED(parray);
	/* エラー文字列の表示 */
	/* Display error message */
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	criFwPrt_DebugPrintf("%s\n", errmsg);
	return;
}


void *user_alloc(void *obj, CriUint32 size)
{
	void *ptr;
	SMPUTL_UNUSED(obj);
	criFwPrt_DebugPrintf("[Meta Alloc CbFunc]\n");
	ptr = criFwMem_Alloc(size, SMPUTL_MEM_ALIGN);
	return ptr;
}

void user_free(void *obj, void *ptr)
{
	SMPUTL_UNUSED(obj);
	criFwPrt_DebugPrintf("[Meta Free CbFunc]\n");
	criFwMem_Free(ptr);
}


/* EOF */
