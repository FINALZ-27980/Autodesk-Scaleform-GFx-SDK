/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2008-2016 CRI Middleware Co., Ltd.
 *
 * Library  : Sample Library
 * Module   : Sample I/O interface for ANSI Standard
 * File     : CriSmpCustomIo_ANSI.c
 *
 ****************************************************************************/

/***************************************************************************
 * インクルード
 * Header files
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "cri_xpt.h"
#include "cri_file_system.h"
#include "CriSmpFsCustomIo.h"

/* 全機種共通のサンプルプログラムなので、機種固有の警告は無視する */
/* Disable target-specific warnings as it's a sample common to all platforms. */
#if defined(XPT_TGT_PC)
#pragma warning(disable : 4996)
#pragma warning(disable : 4100)
#elif defined(XPT_TGT_XBOX360)
#pragma warning(disable : 4100)
#endif

/***************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 ***************************************************************************/

/***************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 ***************************************************************************/
/* 未使用引数警告回避マクロ */
/* Macro to prevent an unused argument warning from being displayed */
#define UNUSED(arg)						{ if ((arg) == (arg)) {} }

/* 値の切り上げマクロ */
/* Macro to roud up a value */
#define ROUND_UP(a, align)				((((a) + (align) - 1) / (align)) * (align))

/* 最大値マクロ */
/* Macro to get the max value */
#define MAX(x, y)       ((x) > (y) ? (x) : (y))

/* 最小値マクロ */
/* Macro to get the min value */
#define MIN(x, y)       ((x) < (y) ? (x) : (y))

/***************************************************************************
 * 型定義
 * Type definitions
 ***************************************************************************/

/***************************************************************************
 * 変数宣言
 * Variable declarations
 ***************************************************************************/

/***************************************************************************
 * 関数宣言
 * Function declarations
 ***************************************************************************/
/* インターフェース登録用関数 */
/* Functions for the interface registration */
static CriFsIoError criSmpFsIoAnsi_Exists(const CriChar8 *path, CriBool *result);
static CriFsIoError criSmpFsIoAnsi_Remove(const CriChar8 *path);
static CriFsIoError criSmpFsIoAnsi_Rename(const CriChar8 *old_path, const CriChar8 *new_path);
static CriFsIoError criSmpFsIoAnsi_Open(
	const CriChar8 *path, CriFsFileMode mode, CriFsFileAccess access, CriFsFileHn *filehn);
static CriFsIoError criSmpFsIoAnsi_Close(CriFsFileHn filehn);
static CriFsIoError criSmpFsIoAnsi_GetFileSize(CriFsFileHn filehn, CriSint64 *file_size);
static CriFsIoError criSmpFsIoAnsi_Read(CriFsFileHn filehn,
	CriSint64 offset, CriSint64 read_size, void *buffer, CriSint64 buffer_size);
static CriFsIoError criSmpFsIoAnsi_IsReadComplete(CriFsFileHn filehn, CriBool *result);
static CriFsIoError criSmpFsIoAnsi_GetReadSize(CriFsFileHn filehn, CriSint64 *read_size);
static CriFsIoError criSmpFsIoAnsi_Write(CriFsFileHn filehn,
	CriSint64 offset, CriSint64 write_size, void *buffer, CriSint64 buffer_size);
static CriFsIoError criSmpFsIoAnsi_IsWriteComplete(CriFsFileHn filehn, CriBool *result);
static CriFsIoError criSmpFsIoAnsi_GetWriteSize(CriFsFileHn filehn, CriSint64 *write_size);
static CriFsIoError criSmpFsIoAnsi_Flush(CriFsFileHn filehn);
static CriFsIoError criSmpFsIoAnsi_GetNativeFileHandle(CriFsFileHn filehn, void **native_filehn);

/***************************************************************************
 * 変数定義
 * Variable definitions
 ***************************************************************************/
/* ファイルハンドル */
/* File handle */
typedef struct {
	FILE *fp;					/* ネイティブファイルハンドル */ /* native file handle */
	CriSint64 file_size;		/* ファイルサイズ */  /* file size */
	CriSint64 read_size;		/* 最終読み込みサイズ */  /* the last read size */
	CriSint64 write_size;		/* 最終書き込みサイズ */  /* the last write size */
} CriSmpFsFileObj, *CriSmpFsFileHn;

/* I/O処理インターフェース */
/* I/O processing interface */
static CriFsIoInterface g_CriSmpFsIoInterface = {
	criSmpFsIoAnsi_Exists,
	criSmpFsIoAnsi_Remove,
	criSmpFsIoAnsi_Rename,
	criSmpFsIoAnsi_Open,
	criSmpFsIoAnsi_Close,
	criSmpFsIoAnsi_GetFileSize,
	criSmpFsIoAnsi_Read,
	criSmpFsIoAnsi_IsReadComplete,
	NULL,
	criSmpFsIoAnsi_GetReadSize,
	criSmpFsIoAnsi_Write,
	criSmpFsIoAnsi_IsWriteComplete,
	NULL,
	criSmpFsIoAnsi_GetWriteSize,
	criSmpFsIoAnsi_Flush,
	NULL,
	criSmpFsIoAnsi_GetNativeFileHandle
};

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/*==========================================================================
 * I/Oインターフェース選択関数
 * I/O interface selection function
 *=========================================================================*/
/* I/Oインターフェース選択関数 */
/* I/O interface selection function */
CriError CriSmpFsSelectIoFunc(const CriChar8 *path,
	CriFsDeviceId *device_id, CriFsIoInterfacePtr *ioif)
{
	UNUSED(path);
	
	/* 引数のチェック */
	/* Check the arguments */
	assert(path != NULL);
	assert(device_id != NULL);
	assert(ioif != NULL);
	
	/* デフォルトのデバイスIDを使用 */
	/* 備考）本サンプルでは1つのデバイスのみを想定 */
    /* The default device ID is specified */
    /* Note: One device is used in this sample */
	(*device_id) = CRIFS_DEFAULT_DEVICE;
	
	/* I/Oインターフェースとしてg_CriSmpFsIoInterfaceを使用 */
    /* g_CriSmpFsIoInterface is used as the I/O interface */
	(*ioif) = &g_CriSmpFsIoInterface;
	
	return (CRIERR_OK);
}

/*==========================================================================
 * インターフェース登録用関数
 * Interface registration functions
 *=========================================================================*/
/* ファイルの有無の確認 */
/* Check whether the file exists */
static CriFsIoError criSmpFsIoAnsi_Exists(const CriChar8 *path, CriBool *result)
{
	FILE *fp;
	
	/* 引数のチェック */
	/* Check the arguments */
	assert(path != NULL);
	assert(result != NULL);
	
	/* ファイルの有無をチェック */
	/* Check whether the file exists */
	fp = fopen(path, "rb");
	if (fp == NULL) {
		(*result) = CRI_FALSE;
	} else {
		fclose(fp);
		(*result) = CRI_TRUE;
	}
	
	return (CRIFS_IO_ERROR_OK);
}

static CriFsIoError criSmpFsIoAnsi_Remove(const CriChar8 *path)
{
	int ret;
	
	/* 引数のチェック */
	/* Check the argument */
	assert(path != NULL);
	
	/* ファイルの削除 */
	/* Remove the file */
	ret = remove(path);
	if (ret != 0) {
		return (CRIFS_IO_ERROR_NG);
	}
	
	return (CRIFS_IO_ERROR_OK);
}

static CriFsIoError criSmpFsIoAnsi_Rename(const CriChar8 *old_path, const CriChar8 *new_path)
{
	int ret;
	
	/* 引数のチェック */
	/* Check the arguments */
	assert(old_path != NULL);
	assert(new_path != NULL);
	
	/* ファイル名の変更 */
	/* Rname the file */
	ret = rename(old_path, new_path);
	if (ret != 0) {
		return (CRIFS_IO_ERROR_NG);
	}
	
	return (CRIFS_IO_ERROR_OK);
}

static CriFsIoError criSmpFsIoAnsi_Open(
	const CriChar8 *path, CriFsFileMode mode, CriFsFileAccess access, CriFsFileHn *filehn)
{
	FILE *fp;
	CriChar8 cmode[4];
	CriSmpFsFileHn pfh;
	
	/* 引数のチェック */
	/* Check the arguments */
	assert(path != NULL);
	assert(filehn != NULL);
	
	/* 変数の初期化 */
	/* Initialize variables */
	memset(cmode, 0, sizeof(cmode));
	
	/* ファイルオープン方法をfopen用に変換 */
	/* Change the way to open a file to the fopen function */
	switch (mode) {
		case CRIFS_FILE_MODE_APPEND:
		if (access == CRIFS_FILE_ACCESS_WRITE) {
			strcpy(cmode, "ab");
		} else {
			return (CRIFS_IO_ERROR_NG);
		}
		break;
		
		case CRIFS_FILE_MODE_CREATE:
		case CRIFS_FILE_MODE_CREATE_NEW:
		case CRIFS_FILE_MODE_TRUNCATE:
		if (access == CRIFS_FILE_ACCESS_READ) {
			return (CRIFS_IO_ERROR_NG);
		} else {
			strcpy(cmode, "w+b");
		}
		break;
		
		case CRIFS_FILE_MODE_OPEN:
		case CRIFS_FILE_MODE_OPEN_OR_CREATE:
		if (access == CRIFS_FILE_ACCESS_READ) {
			strcpy(cmode, "rb");
		} else {
			strcpy(cmode, "r+b");
		}
		break;
		
		default:
		break;
	}
	
	/* ファイルの有無をチェック */
	/* Check whether the file exists */
	if (mode == CRIFS_FILE_MODE_CREATE_NEW) {
		/* →FILE_MODE_CREATE_NEW時はファイルが存在していてはいけない */
		/*  The file needs to exist to specify FILE_MODE_CREATE_NEW */
		fp = fopen(path, "rb");
		if (fp != NULL) {
			/* Error : Already exist. */
			fclose(fp);
			return (CRIFS_IO_ERROR_NG);
		}
	}
	if ((mode == CRIFS_FILE_MODE_OPEN) || (mode == CRIFS_FILE_MODE_TRUNCATE)) {
		/* →FILE_MODE_OPEN、FILE_MODE_TRUNCATE時はファイルが存在しなければならない */
		/*  The file needs to exist to specify FILE_MODE_OPEN/FILE_MODE_TRUNCATE */
		fp = fopen(path, "rb");
		if (fp == NULL) {
			/* Error : Fialed to open file. */
			return (CRIFS_IO_ERROR_NG);
		}
		fclose(fp);
	}
	
	/* ファイルハンドル領域の確保 */
	/* Allocate a file handle area */
	pfh = (CriSmpFsFileHn)malloc(sizeof(CriSmpFsFileObj));
	if (pfh == NULL) {
		return (CRIFS_IO_ERROR_NG);
	}
	memset(pfh, 0, sizeof(CriSmpFsFileObj));
	
	/* ファイルのオープン */
	/* Open a file */
	pfh->fp = fopen(path, cmode);
	if (pfh->fp == NULL) {
		free((void *)pfh);
		return (CRIFS_IO_ERROR_NG);
	}
	
	/* ファイルサイズの取得 */
	/* Get the file size */
	fseek(pfh->fp, 0, SEEK_END);
	pfh->file_size = ftell(pfh->fp);
	fseek(pfh->fp, 0, SEEK_SET);
	
	/* ハンドルの保存 */
	/* Store the file handle */
	(*filehn) = (CriSmpFsFileHn)pfh;
	
	return (CRIFS_IO_ERROR_OK);
}

static CriFsIoError criSmpFsIoAnsi_Close(CriFsFileHn filehn)
{
	CriSmpFsFileHn pfh;
	
	/* 引数のチェック */
	/* Check the arguments */
	assert(filehn != NULL);
	
	/* 変数の初期化 */
	/* Initialize variables */
	pfh = (CriSmpFsFileHn)filehn;
	
	/* ファイルのクローズ */
	/* Close the file */
	if (pfh->fp != NULL) {
		fclose(pfh->fp);
		pfh->fp = NULL;
	}
	
	/* ハンドル領域の解放 */
	/* Deallocate the handle area */
	free((void *)pfh);
	
	return (CRIFS_IO_ERROR_OK);
}

static CriFsIoError criSmpFsIoAnsi_GetFileSize(CriFsFileHn filehn, CriSint64 *file_size)
{
	CriSmpFsFileHn pfh;
	
	/* 引数のチェック */
	/* Check the arguments */
	assert(filehn != NULL);
	assert(file_size != NULL);
	
	/* 変数の初期化 */
	/* Initialize variables */
	pfh = (CriSmpFsFileHn)filehn;
	
	/* ファイルサイズの保存 */
	/* Store the file size */
	(*file_size) = pfh->file_size;
	
	return (CRIFS_IO_ERROR_OK);
}

static CriFsIoError criSmpFsIoAnsi_Read(CriFsFileHn filehn,
	CriSint64 offset, CriSint64 read_size, void *buffer, CriSint64 buffer_size)
{
	CriSmpFsFileHn pfh;
	int ret;
	size_t reqbyte, rdbyte;
	
	/* 引数のチェック */
	/* Check the arguments */
	assert(filehn != NULL);
	assert(offset >= 0);
	assert(read_size >= 0);
	assert(buffer != NULL);
	assert(buffer_size >= 0);
	
	/* 変数の初期化 */
	/* Initialize variables */
	pfh = (CriSmpFsFileHn)filehn;
	
	/* 読み込み開始位置まで移動 */
	/* Move to a position for starting file read */
	ret = fseek(pfh->fp, (long)offset, SEEK_SET);
	if (ret != 0) {
		return (CRIFS_IO_ERROR_NG);
	}
	
	/* 読み込みサイズの計算 */
	reqbyte = (size_t)MIN(read_size, buffer_size);
	
	/* データの読み込み */
	/* Read data */
	rdbyte = fread(buffer, 1, reqbyte, pfh->fp);
	
	/* エラーチェック */
	/* Error checking */
	ret = ferror(pfh->fp);
	if (ret != 0) {
		clearerr(pfh->fp);
		return (CRIFS_IO_ERROR_NG);
	}
	
	/* 読み込みサイズの保存 */
	/* Store the read size */
	pfh->read_size = (CriSint64)rdbyte;
	
	return (CRIFS_IO_ERROR_OK);
}

static CriFsIoError criSmpFsIoAnsi_IsReadComplete(CriFsFileHn filehn, CriBool *result)
{
	UNUSED(filehn);
	
	/* 引数のチェック */
	/* Check the arguments */
	assert(filehn != NULL);
	assert(result != NULL);
	
	/* 同期I/Oで実装しているので常にCRI_TRUEを返す */
	/* Always return TRUE as it is implemented as synchronus I/O */
	(*result) = CRI_TRUE;
	
	return (CRIFS_IO_ERROR_OK);
}

static CriFsIoError criSmpFsIoAnsi_GetReadSize(CriFsFileHn filehn, CriSint64 *read_size)
{
	CriSmpFsFileHn pfh;
	
	/* 引数のチェック */
	/* Check the arguments */
	assert(filehn != NULL);
	assert(read_size != NULL);
	
	/* 変数の初期化 */
	/* Initialize variables */
	pfh = (CriSmpFsFileHn)filehn;
	
	/* ファイルサイズの保存 */
	/* Store the file size */
	(*read_size) = pfh->read_size;
	
	return (CRIFS_IO_ERROR_OK);
}

static CriFsIoError criSmpFsIoAnsi_Write(CriFsFileHn filehn,
	CriSint64 offset, CriSint64 write_size, void *buffer, CriSint64 buffer_size)
{
	CriSmpFsFileHn pfh;
	int ret;
	size_t reqbyte, wrbyte;
	size_t fsize;
	
	/* 引数のチェック */
	/* Check the arguments */
	assert(filehn != NULL);
	assert(offset >= 0);
	assert(write_size >= 0);
	assert(buffer != NULL);
	assert(buffer_size >= 0);
	
	/* 変数の初期化 */
	/* Initialize variables */
	pfh = (CriSmpFsFileHn)filehn;
	
	/* 書き込み開始位置まで移動 */
	/* Move to a position for starting file write */
	ret = fseek(pfh->fp, (long)offset, SEEK_SET);
	if (ret != 0) {
		return (CRIFS_IO_ERROR_NG);
	}
	
	/* 書き込みサイズの計算 */
	reqbyte = (size_t)MIN(write_size, buffer_size);
	
	/* データの書き込み */
	/* Write data */
	wrbyte = fwrite(buffer, 1, reqbyte, pfh->fp);
	
	/* エラーチェック */
	/* Error checking */
	ret = ferror(pfh->fp);
	if (ret != 0) {
		clearerr(pfh->fp);
		return (CRIFS_IO_ERROR_NG);
	}
	
	/* 書き込みサイズの保存 */
	/* Store the write size */
	pfh->write_size = (CriSint64)wrbyte;
	
	/* ファイルサイズの補正 */
	/* Correct file size */
	fsize = ftell(pfh->fp);
	pfh->file_size = MAX(pfh->file_size, (CriSint64)fsize);
	
	return (CRIFS_IO_ERROR_OK);
}

static CriFsIoError criSmpFsIoAnsi_IsWriteComplete(CriFsFileHn filehn, CriBool *result)
{
	UNUSED(filehn);
	
	/* 引数のチェック */
	/* Check the arguments */
	assert(filehn != NULL);
	assert(result != NULL);
	
	/* 同期I/Oで実装しているので常にCRI_TRUEを返す */
	/* Always return TRUE as it is implemented as synchronus I/O */
	(*result) = CRI_TRUE;
	
	return (CRIFS_IO_ERROR_OK);
}

static CriFsIoError criSmpFsIoAnsi_GetWriteSize(CriFsFileHn filehn, CriSint64 *write_size)
{
	CriSmpFsFileHn pfh;
	
	/* 引数のチェック */
	/* Check the arguments */
	assert(filehn != NULL);
	assert(write_size != NULL);
	
	/* 変数の初期化 */
	/* Initialize variables */
	pfh = (CriSmpFsFileHn)filehn;
	
	/* ファイルサイズの保存 */
	/* Store the file size */
	(*write_size) = pfh->write_size;
	
	return (CRIFS_IO_ERROR_OK);
}

static CriFsIoError criSmpFsIoAnsi_Flush(CriFsFileHn filehn)
{
	CriSmpFsFileHn pfh;
	
	/* 引数のチェック */
	/* Check the arguments */
	assert(filehn != NULL);
	
	/* 変数の初期化 */
	/* Initialize variables */
	pfh = (CriSmpFsFileHn)filehn;
	
	/* フラッシュの実行 */
	/* Execute the file flush */
	fflush(pfh->fp);
	
	return (CRIFS_IO_ERROR_OK);
}

/* ネイティブファイルハンドルの取得 */
/* Get a native file handle */
static CriFsIoError criSmpFsIoAnsi_GetNativeFileHandle(CriFsFileHn filehn, void **native_filehn)
{
	CriSmpFsFileHn pfh;
	
	/* 引数のチェック */
	/* Check the arguments */
	assert(filehn != NULL);
	assert(native_filehn);
	
	/* 変数の初期化 */
	/* Initialize variables */
	pfh = (CriSmpFsFileHn)filehn;
	
	/* ファイルポインタの保存 */
	/* Store the file pointer */
	(*native_filehn) = (void *)pfh->fp;
	
	return (CRIFS_IO_ERROR_OK);
}

/* --- end of file --- */
