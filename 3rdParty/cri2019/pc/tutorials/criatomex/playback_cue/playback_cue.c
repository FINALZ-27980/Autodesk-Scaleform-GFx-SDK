/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 tutorial program
 * Module  : Cue playback (memory)
 *         : キュー再生（メモリ）
 * File    : playback_cue.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
#include <windows.h>

/* CRI SDK header file */
#include <cri_xpt.h>

/* CRI ADX2 header files */
#include <cri_atom_ex.h>
#include <cri_atom_wasapi.h>

/* チュートリアルで使用するACBファイルのヘッダファイル */
/* Header file for ACB file used in this tutorial */
#include  "../../../../common/smpdata/criatomex/tutorial.h"

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
/* データディレクトリへのパス */
/* Header file for path definitions to data directory */
#define PATH				"..\\..\\..\\..\\..\\common\\smpdata\\criatomex\\"

/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define ACF_FILE			"TutorialProject.acf"
#define ACB_FILE			"tutorial.acb"

/**************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 **************************************************************************/
/* 未使用引数警告回避マクロ */
/* Macro to prevent an unused arguments wanring from being displayed */
#ifndef UNUSED
#define UNUSED(arg)						{ if (&(arg) == &(arg)) {} }
#endif

/**************************************************************************
 * 型定義
 * Type definitions
 **************************************************************************/

/**************************************************************************
 * 関数宣言
 * Function declarations
 **************************************************************************/
/* チュートリアル用エラーコールバック関数 */
/* Error callback for tutorial program */
static void tutorial_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);

/* システムの最低限の初期化 */
/* The minimum initialization of the system */
CriBool tutorial_initialize(void);

/* システムの終了処理 */
/* Finalization of the system */
void tutorial_finalize(void);

/* カレントスレッドのスリープ（ミリ秒指定） */
/* Sleep the current thread (in units of msec) */
void tutorial_sleep(CriUint32 msec);

/* デフォルトのヒープからメモリを確保 */
/* Allocate memory from the default heap */
void *tutorial_alloc(void *obj, CriUint32 size);

/* メモリの解放 */
/* Free memory */
void tutorial_free(void *obj, void *ptr);

/* 文字列のデバッグ表示 */
/* Debug print to string */
void tutorial_printf(const CriChar8* msg);

/**************************************************************************
 * 変数定義
 * Variable definitions
 **************************************************************************/

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
int main(int argc, char *argv[])
{
	CriAtomExPlayerHn player;
	CriAtomExVoicePoolHn voice_pool;
	CriAtomExAcbHn acb_hn;

	UNUSED(argc);
	UNUSED(argv);

	/* 最低限の初期化 */
	/* Initialization (minimum) */
	tutorial_initialize();

	/* エラーコールバック関数の登録 */
	/* Registeration of error callback function */
	criErr_SetCallback(tutorial_error_callback_func);

	/* メモリアロケータの登録 */
	/* Registeration of memory allocator */
	criAtomEx_SetUserAllocator(tutorial_alloc, tutorial_free, NULL);
	
	/* ライブラリの初期化 */
	/* Library initialization */
	criAtomEx_Initialize_WASAPI(NULL, NULL, 0);

	/* ACFファイルの読み込みと登録 */
	/* Load and register an ACF file */
	criAtomEx_RegisterAcfFile(NULL, PATH ACF_FILE, NULL, 0);
	
	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load an ACB file and create an ACB handle */
	acb_hn = criAtomExAcb_LoadAcbFile(NULL, PATH ACB_FILE, NULL, NULL, NULL, 0);

	/* ボイスプールの作成 */
	/* Create a voice pool */
	voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(NULL, NULL, 0);
	
	/* プレーヤの作成 */
	/* Create a player */
	player = criAtomExPlayer_Create(NULL, NULL, 0);

	/* キューIDの指定 */
	/* Specify a Cue ID */
	criAtomExPlayer_SetCueId(player, acb_hn, CRI_TUTORIAL_BOMB2);

	/* 再生の開始 */
	/* Start playback */
	criAtomExPlayer_Start(player);

	for(;;) {
		CriAtomExPlayerStatus explayer_status;
		tutorial_sleep(10);

		/* サーバ処理の実行 */
		/* Execute the server process */
		criAtomEx_ExecuteMain();

		/* Exプレーヤのステータス確認 */
		/* Get AtomEx player status */
		explayer_status = criAtomExPlayer_GetStatus(player);

		/* 再生が終了したらループを抜ける */
        /* Exit the playback loop if the status is PLAYEND */
		if (explayer_status == CRIATOMEXPLAYER_STATUS_PLAYEND) {
			break;
		}
	}

	/* Atomハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(player);
	
	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	criAtomExVoicePool_Free(voice_pool);

	/* ACBハンドルの破棄 */
	/* Destroy ACB handle */
	criAtomExAcb_Release(acb_hn);

	/* ACFの登録解除 */
	/* Unregister ACF */
	criAtomEx_UnregisterAcf();

	/* ライブラリの終了 */
	/* Finalize the library */
	criAtomEx_Finalize_WASAPI();

	/*  最小限の終了処理*/
	/* Finalization (minimum) */
	tutorial_finalize();

	return 0;
}

/* エラーコールバック関数 */
/* Error callback function */
static void tutorial_error_callback_func(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray)
{
	const CriChar8 *errmsg;
	UNUSED(parray);
	/* エラー文字列の表示 */
	/* Display an error message string */
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	tutorial_printf(errmsg);
	return;
}

CriBool tutorial_initialize(void)
{
	return TRUE;
}

void tutorial_finalize(void)
{
}

void tutorial_sleep(CriUint32 msec)
{
	Sleep(msec);
}

void *tutorial_alloc(void *obj, CriUint32 size)
{
	void *ptr;
	UNUSED(obj);
	ptr = malloc(size);
	return ptr;
}

void tutorial_free(void *obj, void *ptr)
{
	UNUSED(obj);
	free(ptr);
}

void tutorial_printf(const CriChar8* msg)
{
	OutputDebugString(msg);
	OutputDebugString("\n");
}

/* --- end of file --- */
