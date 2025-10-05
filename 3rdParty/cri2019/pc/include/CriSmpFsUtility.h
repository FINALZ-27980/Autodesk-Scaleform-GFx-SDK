#ifndef	_CRISMPFSUTILITY_H_INCLUDED
#define	_CRISMPFSUTILITY_H_INCLUDED
/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2008-2012 CRI Middleware Co., Ltd.
 *
 * Library  : Sample Library
 * Module   : Utility
 * File     : CriSmpFsUtility.h
 * Date     : 2012-03-28
 * Version  : 0.92
 *
 ****************************************************************************/

#include "cri_xpt.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

CriBool CRIAPI criSmpFsUtl_Initialize(void);
void CRIAPI criSmpFsUtl_Finalize(void);

void CRIAPI criSmpFsUtl_Sleep(CriUint32 msec);

void CRIAPI criSmpFsUtl_Printf(const CriChar8* format, ...);

void * CRIAPI criSmpFsUtl_Alloc(CriUint32 size);
void CRIAPI criSmpFsUtl_Free(void *ptr);

CriSint64 criSmpFsUtl_GetTimeMs(void);

int criSample_Main(int argc, char *argv[]);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif	//	_CRISMPFSUTILITY_H_INCLUDED

/* --- end of file --- */

