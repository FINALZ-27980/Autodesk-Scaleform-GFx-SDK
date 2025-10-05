/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010-2017 CRI Middleware Co., Ltd.
 *
 * Title   : CRI Mana Sample Program
 * Module  : Playback with ADX2
 *         : Movie playback using the Cuepoint function
 *
 * 説明 :
 *  ムービ再生をしながらADX2でAWBファイルからストリーミング再生するデモです。
 *  Sofdec2でムービをストリーミング再生しながら、ADX2で音声をストリーミング
 *  する場合、以下の点に注意する必要があります。
 *    (a) CRI File Systemライブラリの初期化設定構造体 (CriFsConfig)の設定
 *    (b) ADX2のD-BAS作成パラメータ構造体 (CriDbasConfig)の設定
 *
 * [注意]
 *  ムービと音声を同時にストリーミング再生しない場合は上記の調整は不要です。
 *  本サンプルは、ムービ再生を行いながら、最大4本の音声ストリーミングを再生
 *  します。app_atomex_initialize関数に重要な設定を記述しましたので参照くだ
 *  さい。
 *
 * Description :
 *  This sample demonstrates streaming playback from AWB file with ADX2 
 *  while playing a movie.
 *  To perform streaming audio with ADX2 while streaming movie with Sofdec2,
 *  please note the following:
 *    (a) Set the CRI File System library initialization configuration 
 *        structure (CriFsConfig)
 *    (b) Set the ADX2's D-BAS creation parameters structure (CriDbasConfig)
 *
 * [Note]
 *  If streaming playbacks of movie and audio are not performed simultaneously,
 *  the above adjustments are not required.
 *  In this sample, up to 4 audio streams are played during movie playback.
 *  Please refer to the comments in the app_atomex_initialize function
 *  which describe the important settings.
 *
 */

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
/* C-Standard Header */
#include <string.h>

/* CRI SDK Header */
#include <cri_xpt.h>
#include <cri_atom_ex.h>
#include <cri_atom_wasapi.h>
#include <cri_file_system.h>
/* CRI Sofdec2 Header */
#include <cri_mana.h>

/* CRI Sample Framework Header */
#include <cri_framework.h>
/* サンプル動画描画ヘッダ */
/* Sample movie drawing header */
#include "smp_video_texture.h"

#include "../../../../common/smpdata/criatomex/AtomCueSheet.h"

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
/* サンプルで使用するムービファイル */
/* File names used in this sample */
#define PATH_MANA		"../../../../../common/smpdata/crimana/"
#define USM_FILE		PATH_MANA "sample.usm"
/* サンプルで使用するオーディオファイル */
/* Audio files used in this sample */
#define PATH_ATOM		"../../../../../common/smpdata/criatomex/"
#define ACF_FILE		"SampleProject.acf"
#define ACB_FILE		"AtomCueSheet.acb"
#define AWB_FILE		"AtomCueSheet.awb"

/* メモリアライメント */
/* Memory alignment */
#define SMPUTL_MEM_ALIGN	(32)

/* 最大Atomボイス数 */
/* Maximum number of Atom voices */
#define NUM_VOICES			(4)

/* ムービストリーミング本数 */
/* Number of movie streams */
#define NUM_MOVIES			(1)

/* 最大瞬間オーディオビットレート */
/* 48kHz, 2chのADXを4本再生と想定 */
/* Maximum momentary audio bitrate */
/* Assumed to be 4 ADX streams of 48kHz, 2ch */
#define AUDIO_MAXBPS		(192*1024 * 4)

/* 最大瞬間ビデオビットレート */
/*   - ビデオのビットレートはWizz.exeでも確認可能 */
/* Maximum momentary video bitrate */
/* Video bitrate can also be checked by Wizz. */
#define MOVIE_MAXBPS		(6*1024*1024)

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
	/* Mana用変数 */
	/* Variables for Mana */
	CriManaPlayerHn			mana_player;
	CriManaPlayerStatus		mana_player_status;
	SmpVideoTextureHn		svt;
	CriManaMovieInfo        mvinf;
	CriManaFrameInfo		frame_info;
	CriUint64				playing_tcount;
	CriUint64				playing_tunit;

	/* AtomEx用変数 */
	/* Variables for AtomEx */
	CriAtomExPlayerHn atomex_player;
	CriAtomExAcbHn	acb_hn;
	CriAtomExVoicePoolHn voice_pool;
	CriAtomExPlayerStatus atomex_player_status;
	CriSint32 atomex_play_id;
	CriAtomDbasId dbas_id;
	CriSint32 dbas_size;
	CriSint32 num_using_voices;
	CriSint32 num_limit_voices;

} AppObj;


/**************************************************************************
 * 変数定義
 * Variable definitions
 **************************************************************************/
/* 再生するCue ID のリスト */
/* ADXフォーマットのCue    */
/* List of Cue ID to be played */
/* Cue in ADX format */
static CriSint32 g_cue_id_list[] = {
	CRI_ATOMCUESHEET_BOMB2,
	CRI_ATOMCUESHEET_VOICE_A,
	CRI_ATOMCUESHEET_VOICE_B,
	CRI_ATOMCUESHEET_VOICE_C,
};

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

/* 基本アプリケーションルーチン */
/* Basic application routine */
static CriBool app_initialize(AppObj *app_obj);
static CriBool app_finalize(AppObj *app_obj);
static CriBool app_execute_main(AppObj *app_obj);
static CriBool app_update_frame(AppObj *app_obj);
static void app_display_info(AppObj *app_obj);

/* ムービの再生制御 */
/* Movie playback control */
static CriBool app_mana_prepare(AppObj *app_obj);
static CriBool app_mana_create_player(AppObj *app_obj);
static CriBool app_mana_start(AppObj *app_obj);
static CriBool app_mana_stop(AppObj *app_obj);
static CriBool app_mana_stop_complete(AppObj *app_obj);

/* オーディオ再生制御 */
/* Audio playback control */
static CriBool app_atomex_initialize(AppObj *app_obj);
static CriBool app_atomex_create_player(AppObj *app_obj);
static CriBool app_atomex_start(AppObj *app_obj);
static CriBool app_atomex_stop(AppObj *app_obj);

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
Sint32 main(Sint32 argc, Char8 *argv[])
{
	CriBool ret;
	AppObj app_obj;
	SMPUTL_UNUSED(argc);
	SMPUTL_UNUSED(argv);

	/* サンプル用共通ライブラリ初期化 */
	/* Initialization of common libraries for samples */
	criFw_Initialize();

	/* アプリケーション初期化処理 */
	/* Application initialization */
	app_initialize(&app_obj);

	/* ヘッダ解析開始 */
	/* Start header analysis */
	ret = app_mana_prepare(&app_obj);

	if (ret == CRI_TRUE) {

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
	} else {
		criFwPrt_DebugPrintf("Failed DecodeHeader.\n");
	}

	/* アプリケーション終了処理 */
	/* Application finalization */
	app_finalize(&app_obj);

	/* サンプル用共通ライブラリ終了 */
	/* Finalization of common libraries for samples */
	criFw_Finalize();

}


/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriSint32 x, y;
	const CriChar8 *str_mana_status[] = {"STOP", "DECHDR", "WAIT_PREP", "PREP", "READY", "PLAYING", "PLAYEND", "ERROR"};
	const CriChar8 *str_atom_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};

	x = 2; y = 1;
	criFwPrt_DrawText(x, y, "[CRI Mana: Playback with ADX2 (Multi-streaming)]"); y++;
	/* Sofdec2ライブラリのバージョン情報を出力 */
	/* Display the version information of the Sofdec2 library */
	criFwPrt_DrawText(x, y, "Lib Ver: %s", criMana_GetLibraryVersionString()); y++; y++;

	/* Manaプレーヤのステータスの表示 */
	/* Display the Mana player status */
	criFwPrt_DrawText(x, y, "<Mana Player>"); y++;
	criFwPrt_DrawText(x, y, "Player Status: %s", str_mana_status[app_obj->mana_player_status]); y++;
	criFwPrt_DrawText(x, y, "Playing Time : %6.2f[sec]", (Float32)app_obj->playing_tcount / app_obj->playing_tunit); y++;
	criFwPrt_DrawText(x, y, "Frame No.    : %d", app_obj->frame_info.frame_no); y++;
	y++;
	/* AtomExプレーヤのステータスの表示 */
	/* Display the AtomEx player status */
	criFwPrt_DrawText(x, y, "<AtomEx Player>"); y++;
	criFwPrt_DrawText(x, y, "D-BAS Size   :%d", app_obj->dbas_size);y++;
	criFwPrt_DrawText(x, y, "Player Status:%s", str_atom_status[app_obj->atomex_player_status]);y++;
	criFwPrt_DrawText(x, y, "Play Cue ID  :%d", g_cue_id_list[app_obj->atomex_play_id]);y++;
	criFwPrt_DrawText(x, y, "Num Voices   :%d / %d", app_obj->num_using_voices, app_obj->num_limit_voices);y++;
	y++;
	/* キー操作の説明表示 */
	/* Display key operation instructions */
	criFwPrt_DrawText(    x, y, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01)); 
	criFwPrt_DrawText( x+10, y, "Start and increment Cue ID");y++;
	criFwPrt_DrawText(    x, y, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText( x+10, y, "Stop");y++;
	criFwPrt_DrawText(    x, y, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText( x+10, y, "Finish");y++;

}

CriBool app_initialize(AppObj *app_obj)
{
	/* エラーコールバック関数の登録 */
	/* Registration of error callback function */
	criErr_SetCallback(user_error_callback_func);

	/* ADX2,Sofdec2 にメモリアロケータを登録 */
	/* 別々のアロケータを登録することももちろん可能 */
	/* Registration of memory allocator for ADX2/Sofdec2 */
	/* Separate allocators can be registered. */
	criAtomEx_SetUserAllocator(user_alloc, user_free, NULL);
	criMana_SetUserAllocator(user_alloc, user_free, NULL);

	/* ADX2の初期化 必ずManaライブラリの前に行ってください */
	/* Initialize the CRI Mana library (with multithread model by default) */
	app_atomex_initialize(app_obj);

	/* CRI Manaライブラリの初期化（デフォルトでマルチスレッドモデル） */
	/* Manaライブラリ側の初期化は、Atomのストリーミングの影響を考慮する必要はない */
	/* Initialize the CRI Mana library (multithread model by default) */
	/* In the Mana libray initialization, there's no need to consider      */
	/* the impact of the Atom streaming. */
	criMana_Initialize(NULL, NULL, 0);

	/* AtomExプレーヤの作成 */
	/* Create an AtomEx player */
	app_atomex_create_player(app_obj);

	/* Manaプレーヤの作成 */
	/* Create a Mana player */
	app_mana_create_player(app_obj);

	return CRI_TRUE;
}

CriBool app_atomex_initialize(AppObj *app_obj)
{
	CriFsConfig config_fs = {0};
	CriAtomExConfig_WASAPI config_atom = {0};
	CriAtomDbasConfig config_dbas = {0};

	/* CriFileSystemの初期化構造体の設定 */
	/* Setting of the CriFileSystem initialization structure */
	/* The setting shown below is for the case where streming playbacks of */
	/* audio and movie are performed simultaneously.                       */
	criFs_SetDefaultConfig(&config_fs);
	config_fs.thread_model		= CRIFS_THREAD_MODEL_MULTI;
	config_fs.num_binders		= 1;				/* AWBハンドルにつき一つ消費する */
	                                                /* Consumes one per AWB handle */
	config_fs.num_loaders		= NUM_VOICES +		/* 最大同時に再生するストリーミング(Audio+Video)の本数分必要 */
	                                                /* Required to be the maximum number of items for simultaneous streaming playback (Audio+Video) */
								  NUM_MOVIES;		/* Manaプレーヤハンドルにつき一つローダを消費                */
	                                                /* One loader is consumed per Mana player handle */
	config_fs.num_group_loaders = 0;				/* AtomEx, Manaライブラリの内部では使用しません */
	                                                /* Not used within the AtomEx and the Mana libraries */
	config_fs.num_stdio_handles = 0;				/* AtomEx, Manaライブラリの内部では使用しません */
	                                                /* Not used within the AtomEx and the Mana libraries */
	config_fs.num_installers    = 0;				/* AtomEx, Manaライブラリの内部では使用しません */
	                                                /* Not used within the AtomEx and the Mana libraries */
	config_fs.max_binds         = 1;				/* AWBハンドルにつき一つ消費する */
	                                                /* Consumes one per AWB handle */
	config_fs.max_files         = 1+1;				/* 最大同時にオープンするファイル数 ここではAWB+USMの二つ */
	                                                /* Maximum number of files opened simultaneously. 2 for AWB+USM */
	config_fs.max_path          = CRIFS_CONFIG_DEFAULT_MAX_PATH;

	/* CriAtomExライブラリの初期化 */
	/* 再生するオーディオの仕様にあわせて適宜修正してください */
	/* CriAtomEx library initialization */
	/* Modify as needed based on the specification of the audio for playback */
	criAtomEx_SetDefaultConfig_WASAPI(&config_atom);
	config_atom.atom_ex.fs_config = &config_fs;						/* 上で設定したCriFsConfigをセット */
	                                                                /* Set the CriFsConfig configured above */
	criAtomEx_Initialize_WASAPI(&config_atom, NULL, 0);

	/* D-BASの作成 */
	/*   ムービのストリーミング再生と同時に音声ストリーミングをする場合、     */
	/*   ムービ再生を考慮してD-BASを設定する必要があります。                  */
	/*   ムービ再生中にオーディオのストリーミングをしない場合は必要ありません */
	/* D-BAS creation */
	/*   When performing audio streaming at the same time as movie streaming playback,   */
	/*   D-BAS should be configured with consideration for movie playback.               */
	/*   This is not necessary if no audio streaming is performed during movie playback. */
	criAtomDbas_SetDefaultConfig(&config_dbas);
	config_dbas.identifier  = 0;									/* アプリ任意の識別子 */
	                                                                /* Application-unique identifier */
	config_dbas.max_bps     = AUDIO_MAXBPS + MOVIE_MAXBPS;			/* 瞬間最大ビットレート (ムービのビットレートも加味)   */
	                                                                /* Maximum instantaneous bitrate (also considering the movie bitrate)   */
	config_dbas.max_streams = NUM_VOICES + NUM_MOVIES;				/* 最大ストリーミング数 (ムービのストリーム本数も加味) */
	                                                                /* Maximum number of streaming items (also considering the number of movie streams) */
	app_obj->dbas_id = criAtomDbas_Create(&config_dbas, NULL, 0);
	app_obj->dbas_size = criAtomDbas_CalculateWorkSize(&config_dbas);	/* D-BASのワークサイズを記録 */
	                                                                    /* Save the D-BAS work size */

	return CRI_TRUE;
}

CriBool app_mana_create_player(AppObj *app_obj)
{
	SmpVideoTextureConfig svt_config = {0};

	/* プレーヤの作成 */
	/* Create a player */
	app_obj->mana_player = criManaPlayer_Create(NULL, 0);
	/* フレームプール数の設定 */
	/* Set the number of frame pools */
	criManaPlayer_SetNumberOfFramePools(app_obj->mana_player, 2);

	/* プレーヤのステータス取得（変数初期化） */
	/* Get the player status (to initialize the variable */
	app_obj->mana_player_status = criManaPlayer_GetStatus(app_obj->mana_player);

	return CRI_TRUE;
}

CriBool app_atomex_create_player(AppObj *app_obj)
{
	CriAtomExAdxVoicePoolConfig adxvp_config;

	/* ACFファイルの読み込みと登録 */
	/* Load and register an ACF file */
	criAtomEx_RegisterAcfFile(NULL, PATH_ATOM ACF_FILE, NULL, 0);

	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load an ACB file to create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
			NULL, PATH_ATOM ACB_FILE, NULL, PATH_ATOM AWB_FILE, NULL, 0);

	/* ADXボイスプール(ストリーミング用)作成 */
	/* Create an ADX voice pool (for streaming) */
	criAtomExVoicePool_SetDefaultConfigForAdxVoicePool(&adxvp_config);
	adxvp_config.num_voices = NUM_VOICES;
	adxvp_config.player_config.streaming_flag = CRI_TRUE;
	app_obj->voice_pool = criAtomExVoicePool_AllocateAdxVoicePool(&adxvp_config, NULL, 0);

	/* プレーヤの作成 */
	/* Create a player */
	app_obj->atomex_player = criAtomExPlayer_Create(NULL, NULL, 0);
	app_obj->atomex_player_status = criAtomExPlayer_GetStatus(app_obj->atomex_player);
	app_obj->atomex_play_id = CRI_ATOMCUESHEET_HELI_LOOP;

	return CRI_TRUE;
}


CriBool app_finalize(AppObj *app_obj)
{
	/* 動画テクスチャの破棄 */
	/* Destroy the texture for movie */
	smpvideo_texture_destroy(app_obj->svt);	

	/* プレーヤハンドルの破棄 */
	/* Destroy the player handle */
	criManaPlayer_Destroy(app_obj->mana_player);

	/* プレーヤハンドルの破棄 */
	/* Destroy the player handle */
	criAtomExPlayer_Destroy(app_obj->atomex_player);
	
	/* ボイスプールの破棄 */
	/* Destroy the voice pool */
	criAtomExVoicePool_Free(app_obj->voice_pool);
	
	/* AWBハンドルの破棄 */
	/* Destroy the AWB handle */
	criAtomExAcb_Release(app_obj->acb_hn);

	/* D-BASの破棄 */
	/* Destroy the D-BAS */
	criAtomDbas_Destroy(app_obj->dbas_id);

	/* ACFの登録解除 */
	/* Unregister the ACF */
	criAtomEx_UnregisterAcf();

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
	/* 再生の開始 */
	/* Star a playback */
	criManaPlayer_Start(app_obj->mana_player);
	
	/* 情報表示用のパラメータクリア */
	/* Clear parameters for information display */
	app_obj->frame_info.frame_no = -1;

	return CRI_TRUE;
}

CriBool app_mana_stop(AppObj *app_obj)
{
	/* API名変更 @Ver.1.10 */
	/* Changed the API name @Ver.1.10 */
	//criManaPlayer_RequestStop(app_obj->mana_player);
	criManaPlayer_Stop(app_obj->mana_player);
	
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
		app_obj->mana_player_status = criManaPlayer_GetStatus(app_obj->mana_player);
		if (app_obj->mana_player_status == CRIMANAPLAYER_STATUS_PLAYEND ||
			app_obj->mana_player_status == CRIMANAPLAYER_STATUS_STOP) {
			break;
		}
		if (app_obj->mana_player_status == CRIMANAPLAYER_STATUS_ERROR) {
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
		app_atomex_start(app_obj);	/* AtomExプレーヤの再生開始 */
		                            /* Start the playback of AtomEx player */
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		app_atomex_stop(app_obj);	/* AtomExプレーヤの再生停止 */
		                            /* Stop the playback of AtomEx player */
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
	app_obj->mana_player_status = criManaPlayer_GetStatus(app_obj->mana_player);
	/* 再生時刻の取得 */
	/* Get the playback time */
	criManaPlayer_GetTime(app_obj->mana_player, &app_obj->playing_tcount, &app_obj->playing_tunit);

	/* 再生終了 or 停止状態ならアプリ終了を要求 */
	/* Issue a request for application termination if the status is playend or stop. */
	if (app_obj->mana_player_status == CRIMANAPLAYER_STATUS_PLAYEND ||
		app_obj->mana_player_status == CRIMANAPLAYER_STATUS_STOP) {
		return CRI_FALSE;
	}

	/* エラー状態の検知 */
	/* Detect an error status */
	if (app_obj->mana_player_status == CRIMANAPLAYER_STATUS_ERROR) {
		/* もしエラー状態になったらハンドルを停止する */
		/* If it becomes an error status, then stop the handle. */
		app_mana_stop(app_obj);
	}

	/* AtomExプレーヤのステータス取得 */
	/* Get the AtomEx player status */
	app_obj->atomex_player_status = criAtomExPlayer_GetStatus(app_obj->atomex_player);

	/* 使用中のボイス数の取得 */
	/* Get the number of voices in use */
	criAtomExVoicePool_GetNumUsedVoices(app_obj->voice_pool, &app_obj->num_using_voices, &app_obj->num_limit_voices);

	return CRI_TRUE;
}

CriBool app_update_frame(AppObj *app_obj)
{
	CriManaFrameInfo frame_info;

	/* フレームプールにデコード済みのフレームがあるか？ */
	/* Any decoded frames in the frame pool? */
	if (criManaPlayer_ReferFrame(app_obj->mana_player, &frame_info) == CRI_TRUE) {

		/* フレームが表示時刻になっているか？ */
		/* The time of frame is on time for display time ? */
		if (criManaPlayer_IsFrameOnTime(app_obj->mana_player, &frame_info) == CRI_TRUE) {
			CriManaTextureBuffersYUV yuvbufs;
			
			/* シェーダー用にフレームバッファのコピー */
			/* Copy the frame buffer for shaders */
			smpvideo_texture_lock_buffer(app_obj->svt, &yuvbufs);
			criManaPlayer_CopyFrameToBuffersYUV(app_obj->mana_player, &frame_info, &yuvbufs);
			smpvideo_texture_unlock_buffer(app_obj->svt);

			/* 描画し終わったのでフレームを破棄 */
			/* Destroy the frame because drawing is completed. */
			criManaPlayer_DiscardFrame(app_obj->mana_player, &frame_info);

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

CriBool app_atomex_start(AppObj *app_obj)
{
	CriUint32 num_cues;

	/* キューIDの指定 */
	/* Specify Cue ID */
	criAtomExPlayer_SetCueId(app_obj->atomex_player, app_obj->acb_hn, g_cue_id_list[app_obj->atomex_play_id]);
	
	/* 再生の開始 */
	/* Start playback */
	criAtomExPlayer_Start(app_obj->atomex_player);

	/* キューIDのインクリメント */
	/* Increment the Cue ID */
	num_cues = sizeof(g_cue_id_list)/sizeof(g_cue_id_list[0]);
	app_obj->atomex_play_id = (app_obj->atomex_play_id+1) % num_cues;

	return CRI_TRUE;
}

CriBool app_atomex_stop(AppObj *app_obj)
{
	criAtomExPlayer_Stop(app_obj->atomex_player);

	return CRI_TRUE;
}

CriBool app_mana_prepare(AppObj *app_obj)
{
	SmpVideoTextureConfig svt_config = {0};
	CriManaVideoInfo *video;

	/* ムービファイルの指定 */
	/* Specify a movie file */
	criManaPlayer_SetFile(app_obj->mana_player, NULL, USM_FILE);
	/* ヘッダ解析開始 */
	/* Start header analysis */
	criManaPlayer_DecodeHeader(app_obj->mana_player);
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
		criAtomEx_ExecuteMain();
		criMana_ExecuteMain();
	
		/* Manaプレーヤのステータス取得 */
		/* Get the Mana player status */
		app_obj->mana_player_status = criManaPlayer_GetStatus(app_obj->mana_player);
		/* ヘッダ情報が取得できたらループを抜ける */
		/* Exit the loop if the header information is retrieved */
		if (criManaPlayer_GetMovieInfo(app_obj->mana_player, &app_obj->mvinf) == CRI_TRUE) {
			break;
		}
	
		/* エラー状態の検知 */
		/* Detect an error status */
		if (app_obj->mana_player_status == CRIMANAPLAYER_STATUS_ERROR) {
			/* もしエラー状態になったらハンドルを停止する */
			/* If it becomes an error status, then stop the handle. */
			app_mana_stop(app_obj);
		}
		if (app_obj->mana_player_status == CRIMANAPLAYER_STATUS_STOP) {
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
	criFwPrt_DebugPrintf("File : %s\n", USM_FILE);
	criFwPrt_DebugPrintf("(%d, %d), %d[fps], %d[Frames]\n", video->width, video->height, video->framerate, video->total_frames);
	criFwPrt_DebugPrintf("#################################\n");

	/* ムービ仕様にあわせて、動画テクスチャの作成 */
	/* Create a movie texture based on the movie specification */
	video = &app_obj->mvinf.video_prm[0];
	svt_config.name   = "Playback with ADX2";
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

/* エラーコールバック関数 */
/* error callback function */
void user_error_callback_func(const Char8 *errid, Uint32 p1, Uint32 p2, Uint32 *parray)
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
