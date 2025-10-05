/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Acquiring the amount of buffering 
 *         : バッファリング量の取得
 * File    : buffering_size.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
/* CRI SDK header file */
#include <cri_xpt.h>

/* CRI ADX2 header file */
#include <cri_atom_ex.h>

/* CRI Framework header file */
#include <cri_framework.h>

/* サンプル共通ヘッダ */
/* Common header file for samples */
#include "smp_utl.h"

/* データディレクトリへのパス定義ヘッダ */
/* Header file for path definitions to data directory */
#include "smp_utl_data.h"

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define AWB_FILE						"SampleAdxPack.awb"

/* 最大再生ストリーム数 */
/* Max number of playback streams */
#define SMP_MAX_STREAMS		(4)

/* バッファリング量の表示単位 */
/* Display unit of buffered data size */
#if defined(XPT_TGT_VITA)
#define SMP_UNIT_SIZE		(8192)
#elif defined(XPT_TGT_WII)
#define SMP_UNIT_SIZE		(16384)
#else
#define SMP_UNIT_SIZE		(32768)
#endif

/**************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 **************************************************************************/

/**************************************************************************
 * 型定義
 * Type definitions
 **************************************************************************/
/* アプリケーション構造体 */
/* Application structure  */
typedef struct AppTag{
	CriAtomExVoicePoolHn pool;
	CriAtomExPlayerHn player;
	CriAtomAwbHn awb_hn;
	CriAtomExPlayerStatus player_status;
	CriAtomDbasId dbas_id;
} AppObj;

/**************************************************************************
 * 関数宣言
 * Function declarations
 **************************************************************************/
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);
static void *user_alloc_func(void *obj, CriUint32 size);
static void user_free_func(void *obj, void *ptr);

/* アプリケーション側の実装 */
/* Implementation on the application side */
static void app_display_info(AppObj *app_obj);

/**************************************************************************
 * 変数定義
 * Variable definitions
 **************************************************************************/
/* アプリケーション情報 */
/* Application information */
static AppObj app_obj_work = { 0, };
static AppObj *app_obj = &app_obj_work;

/* ファイルパス */
/* File path */
static CriChar8 awb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	CriSint32 line_no = 1;
	CriSint32 i, j, nbyte;
	CriAtomPlayerHn player;
	CriAtomPlayerStatus status;
	CriAtomStreamingInfo streaming_info;
	
	/* タイトルの表示 */
	/* Display title */
	criFwPrt_DrawText(1, line_no++, "[Buffering size sample]");
	line_no++;
	
	/* ステータスの表示 */
	/* Display status */
	criFwPrt_DrawText(1, line_no++, "Player Status : %s", str_status[app_obj->player_status]);
	line_no++;
	
	/* ストリーミング情報の表示 */
	/* Display streaming information */
	if (criAtomEx_GetStreamingInfo(&streaming_info)) {
		/* 一部のプラットフォームでは、ストリーミング情報を取得できません
		 * ここでは対応プラットフォームのみ情報を表示します */
		/* The streaming information cannot be retrieved in some platforms.
		 * So, it is displayed only for the supported platforms. */
		criFwPrt_DrawText(1, line_no++, "Streams       : %d", streaming_info.num_streaming);
		criFwPrt_DrawText(1, line_no++, "Total bitrate : %.1f [bps]", streaming_info.total_bps);
		criFwPrt_DrawText(1, line_no++, "Worst latency : %.3f [sec]", streaming_info.worst_latency);
		line_no++;
	}
	/* ボイスプール内のAtomプレーヤ（≒ボイス）の情報を表示 */
	/* Display info of Atom player (nearly identical to Voice) in voice pool) */
	for (i = 0; i < SMP_MAX_STREAMS; i++) {
		/* Atomプレーヤの取得 */
		/* Get Atom player status */
		player = criAtomExVoicePool_GetPlayerHandle(app_obj->pool, i);
		
		/* Atomプレーヤのステータス／バッファリング量を表示 */
		/* Display Atom player status and buffered data size */
		status = criAtomPlayer_GetStatus(player);
		nbyte = criAtomPlayer_GetInputBufferRemainSize(player);
		criFwPrt_DrawText( 1, line_no, "Voice[%d] (%s)", i, str_status[status]);
		criFwPrt_DrawText(20, line_no, ": ");
		for (j = 0; j < (nbyte / SMP_UNIT_SIZE); j++) {
			criFwPrt_DrawText( 22 + j, line_no, "*");
		}
		line_no++;
	}
	line_no++;
	
	/* 操作方法の表示 */
	/* Display operating instructions */
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, line_no++, "Start Voice A");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, line_no++, "Start Voice B");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, line_no++, "Start BGM A");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(10, line_no++, "Start BGM B");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON05));
	criFwPrt_DrawText(10, line_no++, "Stop");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, line_no++, "Finish");
}

void Sample_Initialize(void)
{
	CriAtomExStandardVoicePoolConfig pool_config;
	CriAtomExDbasConfig dbas_config;
	CriSint32 adx_bps;
	
	/* エラーコールバック関数の登録 */
	/* Registration of error callback function */
	criErr_SetCallback(user_error_callback_func);
	
	/* メモリアロケータの登録 */
	/* Registration of memory allocator */
	criAtomEx_SetUserAllocator(user_alloc_func, user_free_func, NULL);
	
	/* ライブラリの初期化 */
	/* Library initialization */
	smputl_initialize(NULL, NULL, 0);

	/* D-BASの作成 */
	/* Create D-BAS */
	adx_bps = criAtomEx_CalculateAdxBitrate(2, CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE);
	criAtomExDbas_SetDefaultConfig(&dbas_config);
	dbas_config.max_streams = SMP_MAX_STREAMS;
	dbas_config.max_bps = adx_bps * SMP_MAX_STREAMS;
	app_obj->dbas_id = criAtomExDbas_Create(&dbas_config, NULL, 0);
	
	/* ボイスプールの作成 */
	/* Create a voice pool */
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&pool_config);
	pool_config.num_voices = SMP_MAX_STREAMS;
	pool_config.player_config.streaming_flag = CRI_TRUE;
	app_obj->pool = criAtomExVoicePool_AllocateStandardVoicePool(&pool_config, NULL, 0);
	
	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(awb_path, AWB_FILE, sizeof(awb_path));

	/* AWBハンドルの作成 */
	/* Create an AWB handle */
	app_obj->awb_hn = criAtomAwb_LoadToc(NULL, awb_path, NULL, 0);

	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* AWBハンドルの破棄 */
	/* Destroy AWB handle */
	criAtomAwb_Release(app_obj->awb_hn);
	
	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	criAtomExVoicePool_Free(app_obj->pool);
	
	/* D-BASの破棄 */
	/* Destroy D-BAS */
	criAtomExDbas_Destroy(app_obj->dbas_id);
	
	/* ライブラリの終了 */
	/* Library finalization */
	smputl_finalize();
}

CriBool Sample_Update(void)
{
	const CriFwPadStatus	*pad_status;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON01) {
		criAtomExPlayer_SetWaveId(app_obj->player, app_obj->awb_hn, SAMPLEADXPACK_AWB_VOICE_A_ADX);
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		criAtomExPlayer_SetWaveId(app_obj->player, app_obj->awb_hn, SAMPLEADXPACK_AWB_VOICE_B_ADX);
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		criAtomExPlayer_SetWaveId(app_obj->player, app_obj->awb_hn, SAMPLEADXPACK_AWB_TTRAILER_SHORTLOOP_ADX);
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		criAtomExPlayer_SetWaveId(app_obj->player, app_obj->awb_hn, SAMPLEADXPACK_AWB_MUSIC_LOOP_ADX);
		criAtomExPlayer_Start(app_obj->player);
	}
	
	if (pad_status->down & CRIFWPAD_BUTTON05) {
		/* 再生停止 */  /* Stop playback */
		criAtomExPlayer_Stop(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return CRI_FALSE;	/* サンプルの終了 */  /* Exit this sample */
	}

	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);

	/* 画面に情報を表示 */
	/* Display information on screen */
	app_display_info(app_obj);

	return CRI_TRUE;
}

/* エラーコールバック関数 */
/* error callback function */
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray)
{
	const CriChar8 *errmsg;
	
	SMPUTL_UNUSED(parray);
	
	/* エラー文字列の表示 */
	/* Display error message */
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	criFwPrt_DebugPrintf("%s\n", errmsg);
	
	return;
}

static void *user_alloc_func(void *obj, CriUint32 size)
{
	void *ptr;
	SMPUTL_UNUSED(obj);
	ptr = criFwMem_Alloc(size, 1);
	return ptr;
}

static void user_free_func(void *obj, void *ptr)
{
	SMPUTL_UNUSED(obj);
	criFwMem_Free(ptr);
}

/* --- end of file --- */
