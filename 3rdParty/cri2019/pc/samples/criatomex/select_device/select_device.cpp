/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2017 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Select Device
 *         : 音声出力デバイスの選択
 * File    : select_device.cpp
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
/* ANSI C header files */
#include <stdio.h>
#include <string.h>

/* Win32 API header files */
#include <Windows.h>
#include <functiondiscoverykeys.h>
#include <propvarutil.h>

/* CRI SDK header file */
#include <cri_xpt.h>

/* CRI ADX2 header file */
#include <cri_atom_ex.h>
#include <cri_atom_asr.h>
#include <cri_atom_pc.h>
#include <cri_atom_wasapi.h>

/* CRI Framework header file */
#include <cri_framework.h>

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
/* サンプルデータのパス */
/* Path to the sample data */
#define PATH	"..\\..\\..\\..\\..\\common\\smpdata\\criatomex\\"

/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define ACF_FILE						"SampleProject.acf"
#define ACB_FILE						"AtomCueSheet.acb"
#define AWB_FILE						"AtomCueSheet.awb"

/* 最大デバイス数 */
#define MAX_DEVICES						(4)

/* デバイス名の最大長 */
#define MAX_DEVICE_NAME_LENGTH			(1024)

/* デバイスIDの最大長 */
#define MAX_DEVICE_ID_LENGTH			(256)

/**************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 **************************************************************************/
/* 未使用引数警告回避マクロ */
/* Macro to prevent an unused arguments warning from being displayed */
#define UNUSED(arg)						{ if ((arg) == (arg)) {} }

/**************************************************************************
 * 型定義
 * Type definitions
 **************************************************************************/
/* アプリケーション構造体 */
/* Application structure  */
typedef struct AppTag{
	CriAtomExPlayerHn player;
	CriAtomExAcbHn acb_hn;
	CriSint32 num_contents;
	CriSint32 selected_index;
	CriAtomDbasId dbas_id;
	CriAtomExPlaybackId playback_id;
	CriSint32 selected_device;
} AppObj;

/* デバイス情報 */
typedef struct AppDeviceInfoTag {
	char name[MAX_DEVICE_NAME_LENGTH];	/* デバイス名 */
	wchar_t id[MAX_DEVICE_ID_LENGTH];	/* デバイスID */
} AppDeviceInfo;

/**************************************************************************
 * 関数宣言
 * Function declarations
 **************************************************************************/
static void app_display_info(AppObj *app_obj);
static CriBool app_atomex_initialize(AppObj *app_obj);
static CriBool app_atomex_finalize(AppObj *app_obj);
static CriBool app_execute_main(AppObj *app_obj);
static void user_update_device_list(AppObj *app_obj);
static void CRIAPI user_endpoint_callback(void *object, IMMDevice *device);
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);
void *user_alloc_func(void *obj, CriUint32 size);
void user_free_func(void *obj, void *ptr);

/**************************************************************************
 * 変数定義
 * Variable definitions
 **************************************************************************/
/* エラーが発生したかどうか */
/* Flag for error occurrence */
static CriBool is_error_occurred = CRI_FALSE;

/* デバイス数 */
static CriSint32 num_devices = 0;

/* デバイス情報一覧 */
static AppDeviceInfo device_info[MAX_DEVICES] = { { 0, }, };

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
int main(int argc, char *argv[])
{
	AppObj app_obj;

	UNUSED(argc);
	UNUSED(argv);

	/* 変数の初期化 */
	/* Initialization of variables */
	memset(&app_obj, 0, sizeof(app_obj));
	app_obj.dbas_id = CRIATOMDBAS_ILLEGAL_ID;

	/* サンプル用共通ライブラリ初期化 */
	/* Initialization of common libraries for sample */
	criFw_Initialize();

	/* アプリケーション初期化処理 */
	/* Application initialization */
	app_atomex_initialize(&app_obj);

	for(;;) {
		/* V同期待ち */
		/* Wait for Vsync */
		criFwSys_WaitVsync();

		/* 情報表示 */
		/* Display information */
		app_display_info(&app_obj);

		/* アプリケーションメイン処理 */
		/* Application main process */
		if (CRI_FALSE == app_execute_main(&app_obj)) {
			/* サンプルの終了 */
			/* Exit sample */
			break;
		}

		/* システムの終了をチェック */
		/* Checking for system termination */
		if (CRI_FALSE != criFwSys_IsTerminated()) {
			/* サンプルの終了 */
			/* Exit sample */
			break;
		}
	}

	/* アプリケーション終了処理 */
	/* Application finalization */
	app_atomex_finalize(&app_obj);

	/* サンプル用共通ライブラリ終了 */
	/* Finalization of common libraries for sample */
	criFw_Finalize();

	/* エラーチェック */
	/* Error checking */
	if (is_error_occurred != CRI_FALSE) {
		return 1;
	}

	return 0;
}

/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriSint32 line_no;
	CriSint32 num_used, limit;
	CriAtomExPlayerStatus status;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	CriSint64 ms;
	CriSint64 num_samples;

	/* 変数の初期化 */
	/* Initialize variables */
	line_no = 1;

	/* タイトルの表示 */
	/* Display title */
	criFwPrt_DrawText( 1, line_no++, "[Select Device]");
	line_no++;

	/* バーチャルボイス残量の表示 */
	/* Display number of remaining virtual voices */
	criAtomEx_GetNumUsedVirtualVoices(&num_used, &limit);
	criFwPrt_DrawText( 1, line_no++, "Virtual voices        : %d / %d", num_used, limit);

	/* ステータスの表示 */
	/* Display status */
	status = criAtomExPlayer_GetStatus(app_obj->player);
	criFwPrt_DrawText( 1, line_no++, "Player Status         : %s", str_status[status]);

	/* 再生時刻／再生サンプル数の表示 */
	/* Display playback time */
	ms = criAtomExPlayer_GetTime(app_obj->player);
	criFwPrt_DrawText( 1, line_no++, "Player Time           : %lld [ms]", ms);
	criAtomExPlayback_GetNumPlayedSamples(app_obj->playback_id, &num_samples, NULL);
	criFwPrt_DrawText( 1, line_no++, "Played samples        : %lld", num_samples);
	line_no++;

	/* AWBファイル内コンテンツ数の表示 */
	/* Display number of contents in AWB file */
	criFwPrt_DrawText( 1, line_no++, "Number of contents    : %d", app_obj->num_contents);

	/* 選択中のキューインデックスを表示 */
	/* Display index of selected Cue */
	criFwPrt_DrawText( 1, line_no++, "Selected cue index    : %d", app_obj->selected_index);
	line_no++;

	/* 出力デバイス名 */
	/* Display selected device name */
	criFwPrt_DrawText( 1, line_no++, "Output Device         : %s", device_info[app_obj->selected_device].name);
	line_no++;

	/* 操作情報の表示 */
	/* Display operating instructions */
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, line_no++, "Start");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, line_no++, "Stop");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_RIGHT));
	criFwPrt_DrawText(10, line_no++, "Increment Cue ID");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(10, line_no++, "Decrement Cue ID");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_LEFT));
	criFwPrt_DrawText(10, line_no++, "Select Previous Sound Device");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_RIGHT));
	criFwPrt_DrawText(10, line_no++, "Select Next Sound Device");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, line_no++, "Update Device List");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, line_no++, "Finish");
}

static CriBool app_atomex_initialize(AppObj *app_obj)
{
	CriAtomExStandardVoicePoolConfig pool_config;

	/* エラーコールバック関数の登録 */
	/* Registeration of error callback function */
	criErr_SetCallback(user_error_callback_func);

	/* メモリアロケータの登録 */
	/* Registeration of memory allocator */
	criAtomEx_SetUserAllocator(user_alloc_func, user_free_func, NULL);

	/* デバイス一覧の初期化 */
	user_update_device_list(app_obj);

	/* ライブラリを初期化 */
	/* Initialize the library */
	criAtomEx_Initialize_WASAPI(NULL, NULL, 0);

	/* D-BASの作成 */
	/* ストリーミング再生を行う場合はD-BASを作成する必要があります。 */
	/* Create a D-BAS */
	/* It is necessary to create a D-BAS for streaming playback */
	app_obj->dbas_id = criAtomDbas_Create(NULL, NULL, 0);

	/* ACFファイルの読み込みと登録 */
	/* Load ACB file and create an ACB handle */
	criAtomEx_RegisterAcfFile(NULL, PATH ACF_FILE, NULL, 0);

	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, PATH ACB_FILE, NULL, PATH AWB_FILE, NULL, 0);

	/* コンテンツ数の取得 */
	/* Get number of contents */
	app_obj->num_contents = criAtomExAcb_GetNumCues(app_obj->acb_hn);

	/* ボイスプールの作成 */
	/* Create a voice pool */
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&pool_config);
	pool_config.player_config.max_channels = 6;
	pool_config.player_config.max_sampling_rate = 96000;
	pool_config.player_config.streaming_flag = CRI_TRUE;
	criAtomExVoicePool_AllocateStandardVoicePool(&pool_config, NULL, 0);

	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);

	/* 本サンプルでは、全てのキューを再生できるようにするため、
	 * データ側で設定したパンタイプを「パン3D」で上書きします。*/
	criAtomExPlayer_SetPanType(app_obj->player, CRIATOMEX_PAN_TYPE_PAN3D);

	/* 再生するキューインデックスを指定 */
	/* Specify Cue index to be played */
	app_obj->selected_index = 0;

	return CRI_TRUE;
}

static CriBool app_atomex_finalize(AppObj *app_obj)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);

	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	criAtomExVoicePool_FreeAll();

	/* ACBハンドルの破棄 */
	/* Destroy ACB handle */
	criAtomExAcb_Release(app_obj->acb_hn);

	/* ACFの登録解除 */
	/* Unregister ACF */
	criAtomEx_UnregisterAcf();

	/* D-BASの破棄 */
	/* Destroy D-BAS */
	criAtomDbas_Destroy(app_obj->dbas_id);

	/* ライブラリ終了処理 */
	/* Finalize the library */
	criAtomEx_Finalize_WASAPI();

	return CRI_TRUE;
}

static CriBool app_execute_main(AppObj *app_obj)
{
	const CriFwPadStatus	*pad_status;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON01) {
		/* キューインデックスの指定 */
		/* Specify Cue index */
		criAtomExPlayer_SetCueIndex(
			app_obj->player, app_obj->acb_hn, app_obj->selected_index);

		/* 再生の開始 */
		/* Start playback */
		app_obj->playback_id = criAtomExPlayer_Start(app_obj->player);
	}

	if (pad_status->down & CRIFWPAD_BUTTON02) {
		/* 再生停止 */
		/* Stop playback */
		criAtomExPlayer_Stop(app_obj->player);
	}

	/* Cue IDの変更 */
	/* Change Cue ID */
	if (pad_status->down & CRIFWPAD_UP) {
		app_obj->selected_index++;
		if (app_obj->selected_index >= app_obj->num_contents) {
			app_obj->selected_index = 0;
		}
	}
	if (pad_status->down & CRIFWPAD_DOWN) {
		app_obj->selected_index--;
		if (app_obj->selected_index < 0) {
			app_obj->selected_index = app_obj->num_contents - 1;
		}
	}

	/* デバイスの変更 */
	/* Change output device */
	if (pad_status->down & CRIFWPAD_LEFT) {
		app_obj->selected_device--;
		if (app_obj->selected_device < 0) {
			app_obj->selected_device = num_devices - 1;
		}

		/* CRIATOM_SOUND_RENDERER_NATIVEに指定されたデバイスをアサイン */
		criAtom_SetDeviceId_WASAPI(
			CRIATOM_SOUND_RENDERER_NATIVE, device_info[app_obj->selected_device].id);
	}
	if (pad_status->down & CRIFWPAD_RIGHT) {
		app_obj->selected_device++;
		if (app_obj->selected_device >= num_devices) {
			app_obj->selected_device = 0;
		}

		/* CRIATOM_SOUND_RENDERER_NATIVEに指定されたデバイスをアサイン */
		criAtom_SetDeviceId_WASAPI(
			CRIATOM_SOUND_RENDERER_NATIVE, device_info[app_obj->selected_device].id);
	}

	if (pad_status->down & CRIFWPAD_BUTTON03) {
		/* デバイス一覧の更新 */
		user_update_device_list(app_obj);
	}

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		/* サンプルの終了 */
		/* Exit sample */
		return CRI_FALSE;
	}

	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();

	return CRI_TRUE;
}

static void user_update_device_list(AppObj *app_obj)
{
	/* デバイス情報一覧のクリア */
	memset(device_info, 0, sizeof(device_info));

	/* デバイス数のリセット */
	/* 備考）デバイス0番はデフォルトデバイスとして使用。 */
	num_devices = 1;
	strcpy_s(device_info[0].name, MAX_DEVICE_NAME_LENGTH, "(Default Device)");

	/* 選択デバイスをデフォルトに戻す */
	app_obj->selected_device = 0;
	criAtom_SetDeviceId_WASAPI(CRIATOM_SOUND_RENDERER_NATIVE, NULL);

	/* オーディオデバイスの列挙 */
	criAtom_EnumAudioEndpoints_WASAPI(user_endpoint_callback, NULL);
}

/* デバイス検出時に呼び出されるコールバック */
static void CRIAPI user_endpoint_callback(void *object, IMMDevice *device)
{
	HRESULT hr;
	DWORD state;
	IPropertyStore *property_store;
	PROPVARIANT propvar;
	LPWSTR device_name;
	LPWSTR device_id;

	UNUSED(object);

	/* 最大デバイス数以上は無視 */
	if (num_devices >= MAX_DEVICES) {
		return;
	}

	/* デバイスの状態を取得 */
	hr = device->GetState(&state);
	if (FAILED(hr) || (state != DEVICE_STATE_ACTIVE)) {
		/* 非アクティブなデバイスは除外 */
		return;
	}

	/* デバイスのプロパティを参照 */
	hr = device->OpenPropertyStore(STGM_READ, &property_store);
	if (FAILED(hr)) {
		/* プロパティが取得できないデバイスは除外 */
		return;
	}

	/* デバイス名の取得 */
	hr = property_store->GetValue(PKEY_Device_FriendlyName, &propvar);
	if (FAILED(hr)) {
		property_store->Release();
		return;
	}

	/* PROPVARIANT型を文字列に変換 */
	hr = PropVariantToStringAlloc(propvar, &device_name);
	if (SUCCEEDED(hr)) {
		/* デバイスIDの取得 */
		hr = device->GetId(&device_id);
		if (SUCCEEDED(hr)) {
			/* デバイスIDの保存 */
			wcscpy_s(device_info[num_devices].id, MAX_DEVICE_ID_LENGTH, device_id);

			/* デバイスID領域を解放 */
			CoTaskMemFree(device_id);
		}

		/* デバイス名の保存 */
		WideCharToMultiByte(CP_THREAD_ACP, 0,
			device_name, (int)wcslen(device_name) + 1,
			device_info[num_devices].name, MAX_DEVICE_NAME_LENGTH, NULL, NULL);

		/* デバイス名を解放 */
		CoTaskMemFree(device_name);

		/* デバイス数の更新 */
		num_devices++;
	}

	/* プロパティへの参照を破棄 */
	property_store->Release();
}

/* エラーコールバック関数 */
/* error callback function */
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray)
{
	const CriChar8 *errmsg;

	UNUSED(parray);

	/* エラー文字列の表示 */
	/* Display an error message */
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	criFwPrt_DebugPrintf("%s\n", errmsg);

	/* エラーが起きたことを記録 */
	/* Notify error occurrence */
	is_error_occurred = CRI_TRUE;
}

void *user_alloc_func(void *obj, CriUint32 size)
{
	void *ptr;

	UNUSED(obj);

	ptr = criFwMem_Alloc(size, 1);

	return ptr;
}

void user_free_func(void *obj, void *ptr)
{
	UNUSED(obj);

	criFwMem_Free(ptr);
}

/* --- end of file --- */
