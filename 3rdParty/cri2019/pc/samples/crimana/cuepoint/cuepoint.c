/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010-2017 CRI Middleware Co., Ltd.
 *
 * Title   : CRI Mana Sample Program
 * Module  : Cuepoint
 *         : キューポイント機能を使ったムービ再生のサンプルです。
 *         : Movie playback using the Cuepoint function
 *
 * 説明 :
 *	あらかじめエンコード時に埋め込んでおいたキューポイント（タイミング情報）
 *	を、ランタイム時にコールバックで取得することができます。
 *	また、再生開始前にヘッダ解析を行うことで、キューポイント情報のリストを
 *	事前に取得することが出来ます。
 *	本サンプルにはありませんが、このリスト情報を使って、任意のキューポイント
 *	にシークするなどの演出も可能です。
 *
 * Description :
 *  Cuepoint information (timing information) is embedded into a movie
 *  at the time of encoding, and it can be retrieved at runtime through
 *  a callback. 
 *  By doing the header analysis before playback, the list of Cuepoint
 *  information can also be retrieved beforehand.
 *  The list is not used in this sample, but it can be used for various 
 *  operations such as the seek to any Cuepoint.
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
#define USM_FILE		PATH_MANA "surround_subaudio.usm"

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
 * Type definitions
 **************************************************************************/
/* アプリケーション構造体 */
/* Application structure  */
typedef struct AppTag{
	CriManaPlayerHn			player;
	CriManaPlayerStatus		player_status;
	SmpVideoTextureHn		svt;

	CriManaMovieInfo	mvinf;
	CriManaFrameInfo	frame_info;
	CriUint64			playing_tcount;
	CriUint64			playing_tunit;

	CriManaCuePointInfo *cueinf;
	CriManaEventPoint *last_event;
	CriSint32 cb_count;
} AppObj;

/**************************************************************************
 * 関数宣言
 * Function declarations
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

/* キューポイント通知コールバック */
/* Cuepoint notification callback */
static void user_cuepoint_callback(void* obj, CriManaPlayerHn player, CriManaEventPoint *eventinfo);

/* キューポイントリストの表示 */
/* Display Cuepoint list */
static void user_print_cuepoint_list(CriManaCuePointInfo *cueinf);

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
Sint32 main(Sint32 argc, Char8 *argv[])
{
	AppObj app_obj = {0};
	SMPUTL_UNUSED(argc);
	SMPUTL_UNUSED(argv);

	/* サンプル用共通ライブラリ初期化 */
	/* Initialization of common libraries for samples */
	criFw_Initialize();

	/* アプリケーション初期化処理 */
	/* Application initialization */
	app_mana_initialize(&app_obj);

	/* ムービ再生の開始 */
	/* Start movie playback */
	app_mana_start(&app_obj);

	for(;;) {
		/* アプリケーションメイン処理 */
		/* Application main process */
		if (CRI_FALSE == app_execute_main(&app_obj)) {
			/* 再生終了 */
			/* Finished playback */
			break;
		}
		/* システムの終了をチェック */
		/* Checking for system termination */
		if (CRI_FALSE != criFwSys_IsTerminated()) {
			/* サンプルの終了 */
			/* Exit sample */
			app_mana_stop_complete(&app_obj);
			break;
		}

		/* ビデオフレームの更新 */
		/* Update the video frame */
		app_update_frame(&app_obj);

		/* 情報表示 */
		/* Display information */
		app_display_info(&app_obj);

		/* V同期待ち */
		/* Wait for V-sync */
		criFwSys_WaitVsync();
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
	CriFloat32 playing_time, event_time;

	x = 2; y = 1;
	criFwPrt_DrawText(x, y, "[CRI Mana: Cuepoint]"); y++;
	/* Sofdec2ライブラリのバージョン情報を出力 */
	/* Display the version information of the Sofdec2 library */
	criFwPrt_DrawText(x, y, "Lib Ver: %s", criMana_GetLibraryVersionString()); y++; y++;

	/* ステータスの表示 */
	/* Display the status */
	criFwPrt_DrawText(x, y, "Player Status: %s", str_status[app_obj->player_status]); y++;
	/* 再生時刻の表示 */
	/* Display the playback time */
	playing_time = (CriFloat32)app_obj->playing_tcount / app_obj->playing_tunit;
	criFwPrt_DrawText(x, y, "Playing Time : %6.2f[sec]", playing_time); y++;
	/* フレーム番号の表示 */
	/* Display the frame number */
	criFwPrt_DrawText(x, y, "Frame No.    : %d", app_obj->frame_info.frame_no); y++; y++;

	/* [キューポイント] */
	/* キューポイント関連情報を表示 */
	/* [Cuepoint] */
	/* Display the Cuepoint related information */
	criFwPrt_DrawText(x, y, "<Cuepoint Info>"); y++;
	criFwPrt_DrawText(x, y, "Num Cuepoints Triggered: %d / %d", app_obj->cb_count,
						(app_obj->cueinf!=NULL)? app_obj->cueinf->num_eventpoint : 0 ); y++;y++;
	/* コールバックで通知されたイベント情報の表示 */
	/* Display the event information notified by the callback */
	criFwPrt_DrawText(x, y, "Event CB:");
	if (app_obj->last_event!=NULL) {
		/* ただし、表示期間は2秒とする */
		/* But, it is displayed for 2 seconds. */
		event_time = (CriFloat32)app_obj->last_event->time / app_obj->last_event->tunit;
		if (playing_time <  event_time + 2.0f) {
			criFwPrt_DrawText(x+10, y, "(%5.2fsec) : %s, type=%d, param=%s", 
										event_time, app_obj->last_event->cue_name, 
										app_obj->last_event->type, app_obj->last_event->param_string);
		}
	} y++;y++;
	/* キューポイントの場所と位置を表示 */
	/* Display the position of Cuepoint */
	if (app_obj->last_event != NULL) {
		CriSint32 wscale = 60;
		CriSint32 i;
		CriUint32 j;
		CriSint32 cur_frame_no = app_obj->frame_info.frame_no;
		CriUint32 total_frames = app_obj->mvinf.video_prm[0].total_frames;
		if (total_frames != 0) {
			 cur_frame_no = cur_frame_no % total_frames;
		}
		criFwPrt_DrawText( x, y, "Cue :");
		if (app_obj->cueinf != NULL && criManaPlayer_GetStatus(app_obj->player) == CRIMANAPLAYER_STATUS_PLAYING) {
			for (j = 0; j < app_obj->cueinf->num_eventpoint; j++) {
				CriSint32 event_frame_id, event_pos_x;
				event_frame_id = criManaPlayer_CalcFrameNoFromTime(app_obj->player, app_obj->cueinf->eventtable[j].time, app_obj->cueinf->eventtable[j].tunit);
				event_pos_x = (CriSint32)(event_frame_id / ((CriFloat32)total_frames/wscale));
				criFwPrt_DrawText( 5+x+event_pos_x, y, "C");
			} 
		} y++;
		/* Draw playback position */
		criFwPrt_DrawText( x, y, "Pos :");
		for (i = 0; i < wscale; i++) {
			if (i == (CriSint32)(cur_frame_no / ((CriFloat32)total_frames/wscale))) {
				if (criManaPlayer_GetStatus(app_obj->player) == CRIMANAPLAYER_STATUS_PLAYING) {
					criFwPrt_DrawText( 5+x+i,y, ">");
				} else {
					criFwPrt_DrawText( 5+x+i,y, "-");
				}
			} else {
				criFwPrt_DrawText( 5+x+i,y, "-");
			}
		}
	}
}

CriBool app_mana_initialize(AppObj *app_obj)
{
	SmpVideoTextureConfig svt_config = {0};

	/* エラーコールバック関数の登録 */
	/* Registration of error callback function */
	criErr_SetCallback(user_error_callback_func);

	/* ADX2,Sofdec2 にメモリアロケータを登録 */
	/* Registration of memory allocator for ADX2/Sofdec2 */
	criAtomEx_SetUserAllocator(user_alloc, user_free, NULL);
	criMana_SetUserAllocator(user_alloc, user_free, NULL);

	/* CRI AtomExライブラリの初期化 (必ずManaの初期化の前に行ってください) */
	/* Initialize the CRI AtomEx library (Be sure to do this before the Mana initialization) */
	criAtomEx_Initialize_WASAPI(NULL, NULL, 0);

	/* CRI Manaライブラリの初期化（デフォルトでマルチスレッドモデル） */
	/* Initialize the CRI Mana library (with multithread model by default) */
	criMana_Initialize(NULL, NULL, 0);

	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criManaPlayer_Create(NULL, 0);
	/* フレームプール数の設定 */
	/* Set the number of frame pools */
	criManaPlayer_SetNumberOfFramePools(app_obj->player, 2);

	/* [キューポイント] */
	/* キューポイントの取得にはメタデータ用のワークが必要   */
	/* メタデータ用のワークには個別にアロケータを登録します */
	/* [Cuepoint] */
	/* Work area for meta data is required to get the Cuepoint */
	criManaPlayer_SetMetaDataWorkAllocator(app_obj->player, user_alloc, user_free, NULL, CRIMANA_META_FLAG_ALL);

	/* プレーヤのステータス取得（変数初期化） */
	/* Get the player status (for variable initialization) */
	app_obj->player_status = criManaPlayer_GetStatus(app_obj->player);
	
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

	return CRI_TRUE;
}

CriBool app_mana_start(AppObj *app_obj)
{
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
		if (criManaPlayer_GetMovieInfo(app_obj->player, &app_obj->mvinf) == CRI_TRUE) {
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
		/* Checking for system termination */
		if (CRI_FALSE != criFwSys_IsTerminated()) {
			/* サンプルの終了 */
			/* Exit sample */
			app_mana_stop_complete(app_obj);
			return CRI_FALSE;
		}

		/* V同期待ち */
		/* Wait for V-sync */
		criFwSys_WaitVsync();
	}

	/* ムービ情報の確認 */
	/* Display movie information */
	if (app_obj->mvinf.is_playable != CRI_TRUE) {
		criFwPrt_DebugPrintf("This movie file is not playable on this platform.\n");
		return CRI_FALSE;
	}
	video = &app_obj->mvinf.video_prm[0];
	criFwPrt_DebugPrintf("#################################\n");
	criFwPrt_DebugPrintf("(%d, %d), %d[fps], %d[Frames]\n", video->width, video->height, video->framerate, video->total_frames);
	criFwPrt_DebugPrintf("#################################\n");

	/* [キューポイント] */
	/* キューポイントリストの取得 */
	/* [Cuepoint] */
	/* Get the Cuepoint list */
	app_obj->cueinf = criManaPlayer_GetCuePointInfo(app_obj->player);
	if (app_obj->cueinf != NULL) {
		user_print_cuepoint_list(app_obj->cueinf);
		
		/* キューポイント通知コールバックをセット */
		/* Set the Cuepoint notification callback */
		criManaPlayer_SetCuePointCallback(app_obj->player, user_cuepoint_callback, (void*)app_obj);

	} else {
		criFwPrt_DebugPrintf("<NO CUEPOINT INFO FOUND>");
	}

	/* ムービ仕様にあわせて、動画テクスチャの作成 */
	/* Create a movie texture based on the movie specification */
	svt_config.name   = "Cuepoint";
	svt_config.width  = video->width;
	svt_config.height = video->height;
	if (app_obj->mvinf.num_alpha_streams == 1) {
		svt_config.use_alpha = CRI_TRUE;
	} else {
		svt_config.use_alpha = CRI_FALSE;
	}
	svt_config.windowed_flag = CRI_TRUE;
	app_obj->svt = smpvideo_texture_create_YUVA(&svt_config);

	/* ムービ再生の開始 */
	/* Start the movie playback */
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
		/* Stop the playback (asynchronously) */
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
		/* The time of frame is on time for display time ? */
		if (criManaPlayer_IsFrameOnTime(app_obj->player, &frame_info) == CRI_TRUE) {
			CriManaTextureBuffersYUV yuvbufs;
			
			/* シェーダー用にフレームバッファのコピー */
			/* Copy the frame buffer for shaders */
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

/* [キューポイント] キューポイント通知コールバック */
/* [Cuepoint] Cuepoint notification callback */
static void user_cuepoint_callback(void* obj, CriManaPlayerHn player, CriManaEventPoint *eventinfo)
{
	CriUint64 tcount, tunit;
	AppObj *app_obj = (AppObj*)obj;

	/* [NOTE] コールバック内の処理について */
	/* キューポイントコールバック内では、Manaプレーヤの再生制御APIは呼び出さないで下さい */
	/* (例えば、Start, DecodeHeader, Stop, Create, Destroyなど。）                        */
	/* もしこのコールバックをトリガーにしてプレーヤを操作したい場合は、コマンドを記録し   */
	/* このコールバック発生後にメインループで呼び出して下さい                             */
	/* [NOTE] Processing in the callback */
	/* Do not call the playback control API for Mana player in the Cuepoint callback.     */
	/* (e.g. Start, DecodeHeader, Stop, Create, Destroy)                                  */
	/* To control a player by using this callback as a trigger, store a command and       */
	/* call the function from within the mainloop after a callback occurred.              */

	/* 再生時刻を取得 */
	/* Get the playback time */
	criManaPlayer_GetTime(player, &tcount, &tunit);

	/* キューポイントイベント情報をデバッグ表示 */
	/* Display the Cuepoint event information for debugging */
	criFwPrt_DebugPrintf("(%5.2fsec) Event Callback: %s, %d / %d , type=%d", 
					(Float32)tcount/tunit, 
					eventinfo->cue_name, (Uint32)eventinfo->time, (Uint32)eventinfo->tunit, 
					eventinfo->type);
	if (eventinfo->param_string == NULL) {
		criFwPrt_DebugPrintf("\n");
	} else {
		criFwPrt_DebugPrintf(", %s\n", eventinfo->param_string);
	}

	app_obj->last_event = eventinfo;
	app_obj->cb_count++;
}

/* キューポイントリスト情報の表示 */
/* Display the Cuepoint list information */
static void user_print_cuepoint_list(CriManaCuePointInfo *cueinf)
{
	Uint32 i;
	criFwPrt_DebugPrintf("<CUE POINT LIST>\n");
	for (i = 0; i < cueinf->num_eventpoint; i++) {
		criFwPrt_DebugPrintf("(%d): %s , %d / %d , type=%d", 
			i, cueinf->eventtable[i].cue_name, 
			(Uint32)cueinf->eventtable[i].time, (Uint32)cueinf->eventtable[i].tunit, 
			cueinf->eventtable[i].type, cueinf->eventtable[i].param_string);
		if (cueinf->eventtable[i].param_string == NULL) {
			criFwPrt_DebugPrintf("\n");
		} else {
			criFwPrt_DebugPrintf(", %s\n", cueinf->eventtable[i].param_string);
		}
	}

	return;
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
	ptr = criFwMem_Alloc(size, SMPUTL_MEM_ALIGN);
	return ptr;
}

void user_free(void *obj, void *ptr)
{
	SMPUTL_UNUSED(obj);
	criFwMem_Free(ptr);
}


/* EOF */
