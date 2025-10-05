/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010-2017 CRI Middleware Co., Ltd.
 *
 * Title   : CRI Mana Sample Program
 * Module  : Multilingual
 *
 * 説明 :
 *  Sofdec2では、ムービ再生の多言語対応のために二つの機能をサポートします。
 *	 - サブオーディオ再生
 *	 - 字幕取得機能 （字幕の表示はアプリ側の責任）
 *  本サンプルは、上記二つの機能を使用したマルチリンガル再生のデモです。
 *
 * Description :
 *  Sofdec2 supports the following 2 functions for multilingual movie playback.
 *   - subaudio playback
 *   - subtitle retrieval (Application is responsible for displaying subtitles.)
 *  This sample demonstrates a multilingual playback by using the above 
 *  2 functions.
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

/* サブオーディオトラック番号 */
/* どのトラックをサブオーディオとして使用するかはアプリが管理 */
/* Subaudio track number */
/* Application manages which track is used for subaudio. */
static const CriSint32 subaudio_track_list[] = {
		CRIMANA_AUDIO_TRACK_OFF,
		16,		/* 英語 */	/* English */
		17,		/* 日本語(男性) */ /* Japanase(male) */
		18,		/* 日本語(女性) */ /* Japanese(female) */
	};
static const CriSint32 num_subaudio_tracks = sizeof(subaudio_track_list)/sizeof(subaudio_track_list[0]);


/* 字幕チャンネル番号 */
/* Subtitle channel number */
static const CriSint32 subtitle_channel_list[] = {
		CRIMANA_SUBTITLE_CHANNEL_OFF,
		0,		/* 字幕1 (ダミーサンプルテキスト) */ /* Subtitle1 (dummy sample text) */
		1,		/* 字幕2 (ダミーサンプルテキスト) */ /* Subtitle2 (dummy sample text) */
	};
static	const CriSint32 num_subitlte_channels = sizeof(subtitle_channel_list)/sizeof(subtitle_channel_list[0]);

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

	CriSint32			usr_subaudio_cusor_pos;
	CriSint32			cur_subaudio_track_no;

	CriSint32			usr_subtitle_cursor_pos;
	CriSint32           cur_subtitle_channel_no;
	CriUint8			subtitle_buffer[256];

	CriBool				exit_request_flag;

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
static CriBool app_mana_prepare(AppObj *app_obj);
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

RESTART_PLAYBACK:

	/* ヘッダ解析開始 */
	/* Start header analysis */
	ret = app_mana_prepare(&app_obj);
	if (ret == CRI_TRUE) {

		/* 再生開始 */
		/* Start playback */
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
				/* Finished playback */
				app_mana_stop_complete(&app_obj);
				app_obj.exit_request_flag = CRI_TRUE;
				
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
	} else {
		criFwPrt_DebugPrintf("Failed DecodeHeader.\n");
	}

	/* 動画テクスチャの破棄 */
	/* Destroy the movie texture */
	smpvideo_texture_destroy(app_obj.svt);	

	if (app_obj.exit_request_flag != CRI_TRUE) {
		/* トラック情報を変更して再度再生 */
		/* Change the track information, and play again */
		goto RESTART_PLAYBACK;
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
	CriSint32 x, y, i;
	CriChar8 *str_status[] = {"STOP", "DECHDR", "WAIT_PREP", "PREP", "READY", "PLAYING", "PLAYEND", "ERROR"};

	x = 2; y = 1;
	criFwPrt_DrawText(x, y, "[CRI Mana: Multilingual]"); y++;
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

	/* 操作情報表示 */
	/* Display the operation information */
	y++;
	criFwPrt_DrawText(x, y, "<User Control>"); y++;
	criFwPrt_DrawText(x, y, "up/down key    : Select subaudio track"); y++;
	criFwPrt_DrawText(x, y, "left/right key : Select subtitle channel"); y++;
	criFwPrt_DrawText(x, y, "1 key          : Switch to the track/channel"); y++;

	y++;
	/* サブオーディオトラック番号の表示 */
	/* Display the subaudio track number */
	if (app_obj->cur_subaudio_track_no == CRIMANA_AUDIO_TRACK_OFF) {
		criFwPrt_DrawText(x, y, "Subaudio Track No. : OFF"); y++;
	} else {
		criFwPrt_DrawText(x, y, "Subaudio Track No. : %d", app_obj->cur_subaudio_track_no); y++;
	}
	/* 字幕番号の表示 */
	/* Display the subtitle number */
	if (app_obj->cur_subtitle_channel_no == CRIMANA_SUBTITLE_CHANNEL_OFF) {
		criFwPrt_DrawText(x, y, "Subtilte ch No.    : OFF"); y++;
	} else {
		criFwPrt_DrawText(x, y, "Subtilte ch No.    : %d", app_obj->cur_subtitle_channel_no); y++;
	}

	/* サブオーディオトラック番号の表示 */
	/* Display the subaudio track number */
	y++;
	criFwPrt_DrawText(x, y, "<Subaudio Select>"); y++;
	for (i=0;i<num_subaudio_tracks;i++) {
		criFwPrt_DrawText(x+2, y, "Track: %2d ", subaudio_track_list[i]);
		if (app_obj->usr_subaudio_cusor_pos == i) {
			criFwPrt_DrawText(x, y, "*");
		} y++;
	}

	/* 字幕番号の表示 */
	/* Display the subtitle number */
	y++;
	criFwPrt_DrawText(x, y, "<Subtitle Select>"); y++;
	for (i=0;i<num_subitlte_channels;i++) {
		criFwPrt_DrawText(x+1 + i*7, y, "Ch:%d ", subtitle_channel_list[i]);
		if (app_obj->usr_subtitle_cursor_pos == i) {
			criFwPrt_DrawText(x + i*7, y, "*");
		}
	} y++;y++;
	criFwPrt_DrawText(x, y, "SBT> %s", app_obj->subtitle_buffer); y++;

}

CriBool app_mana_initialize(AppObj *app_obj)
{
	/* アプリ変数の初期化 */
	/* Initialize application variables */
	app_obj->exit_request_flag = CRI_FALSE;
	app_obj->usr_subaudio_cusor_pos = 1;
	app_obj->usr_subtitle_cursor_pos = 1;
	app_obj->cur_subaudio_track_no = subaudio_track_list[1];
	app_obj->cur_subtitle_channel_no = subtitle_channel_list[1];

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
	/* Initialize the CRI Mana library (multithread model by default) */
	criMana_Initialize(NULL, NULL, 0);

	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criManaPlayer_Create(NULL, 0);
	/* フレームプール数の設定 */
	/* Set the number of frame pools */
	criManaPlayer_SetNumberOfFramePools(app_obj->player, 2);
	/* プレーヤのステータス取得（変数初期化） */
	/* Get the player status (to initialize the variable */
	app_obj->player_status = criManaPlayer_GetStatus(app_obj->player);

	/* メタデータ用メモリ関数の登録 */
	/* Register the memory function for meta data */
	criManaPlayer_SetMetaDataWorkAllocator(app_obj->player, user_alloc, user_free, NULL, CRIMANA_META_FLAG_ALL);

	return CRI_TRUE;
}

CriBool app_mana_finalize(AppObj *app_obj)
{
	///* 動画テクスチャの破棄 */
	///* Destroy the texture for movie */
	//smpvideo_texture_destroy(app_obj->svt);	

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

static CriBool app_mana_prepare(AppObj *app_obj)
{
	SmpVideoTextureConfig svt_config = {0};
	CriManaVideoInfo *video;
	CriSint32 i;

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
	/* オーディオのトラック情報や字幕数はヘッダ情報から参照可能です。*/
	/* The audio track information and the number of subtitles can be referenced from the header information. */
	criFwPrt_DebugPrintf("Audio Tracks:%d, Subtitle Channels:%d\n", app_obj->mvinf.num_audio_streams, app_obj->mvinf.num_subtitle_channels);
	for (i=0;i<CRIMANA_MAX_AUDIO_NUM;i++) {
		if (app_obj->mvinf.audio_prm[i].num_channels != 0) {	
			criFwPrt_DebugPrintf("Track #%2d: Available, %d ch\n", i, app_obj->mvinf.audio_prm[i].num_channels);
		}
	}
	criFwPrt_DebugPrintf("#################################\n");

	/* ムービ仕様にあわせて、動画テクスチャの作成 */
	/* Create a movie texture based on the movie specification */
	video = &app_obj->mvinf.video_prm[0];
	svt_config.name   = "Multilingual Sample";
	svt_config.width  = video->width;
	svt_config.height = video->height;
	if (app_obj->mvinf.num_alpha_streams == 1) {
		svt_config.use_alpha = CRI_TRUE;
	} else {
		svt_config.use_alpha = CRI_FALSE;
	}
	svt_config.windowed_flag = CRI_TRUE;
	app_obj->svt = smpvideo_texture_create_YUVA(&svt_config);

	return CRI_TRUE;
}

CriBool app_mana_start(AppObj *app_obj)
{

	/* サブオーディオトラックの設定 */
	/* Set a subaudioo track */
	criManaPlayer_SetSubAudioTrack(app_obj->player, app_obj->cur_subaudio_track_no);

	/* 字幕の設定 */
	/* Set a subtitle */
	criManaPlayer_SetSubtitleChannel(app_obj->player, app_obj->cur_subtitle_channel_no);

	/* 再生用ワークバッファの設定 */
	/* Set the work buffer for playback */
	{
		CriManaPlaybackBasicWorkConfig config_basic;
		CriManaPlaybackExWorkConfig config_ex;
		criManaPlayer_GetPlaybackWorkParam(app_obj->player, &config_basic, &config_ex);
		
		/* criManaPlayer_SetSubAudioTrack で指定したオーディオトラックが 有効なトラック */
		/* ならば、config_exにサブオーディオパラメタがセットされます                    */
		/* If the audio track specified by the criManaPlayer_SetSubAudioTrack is valid, */
		/* then the subaudio parameter is set to the config_ex.                         */
		criFwPrt_DebugPrintf("----------------------\n");
		criFwPrt_DebugPrintf("Subaudio Track # : %d\n", app_obj->cur_subaudio_track_no);
		criFwPrt_DebugPrintf("  - channels     : %d\n", config_ex.sub_audio_params.num_channels);
		criFwPrt_DebugPrintf("  - samplingrate : %d\n", config_ex.sub_audio_params.sampling_rate);
		criFwPrt_DebugPrintf("----------------------\n");

		criManaPlayer_SetPlaybackWork(app_obj->player, &config_basic, &config_ex, NULL, 0);
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
		app_obj->exit_request_flag = CRI_TRUE;
		return CRI_FALSE;
	}

	/* ユーザ入力 */
	/* User input */
	if (pad_status->down & CRIFWPAD_UP) {
		app_obj->usr_subaudio_cusor_pos--;
		if (app_obj->usr_subaudio_cusor_pos < 0) {
			app_obj->usr_subaudio_cusor_pos = 0;
		}
	}
	if (pad_status->down & CRIFWPAD_DOWN) {
		app_obj->usr_subaudio_cusor_pos++;
		app_obj->usr_subaudio_cusor_pos %= num_subaudio_tracks;
	}
	if (pad_status->down & CRIFWPAD_LEFT) {
		app_obj->usr_subtitle_cursor_pos--;
		if (app_obj->usr_subtitle_cursor_pos < 0) {
			app_obj->usr_subtitle_cursor_pos = 0;
		}
	}
	if (pad_status->down & CRIFWPAD_RIGHT) {
		app_obj->usr_subtitle_cursor_pos++;
		app_obj->usr_subtitle_cursor_pos %= num_subitlte_channels;
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		/* オーディオトラック、字幕を変更してリスタート */
		/* Restart after changing the audio track and the subtitle */
		app_obj->cur_subaudio_track_no = subaudio_track_list[app_obj->usr_subaudio_cusor_pos];
		app_obj->cur_subtitle_channel_no = subtitle_channel_list[app_obj->usr_subtitle_cursor_pos];

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

	/* 字幕の取得 */
	/* Get the subtitle */
	criManaPlayer_GetSubtitleOnTime(app_obj->player, app_obj->subtitle_buffer, sizeof(app_obj->subtitle_buffer));

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
