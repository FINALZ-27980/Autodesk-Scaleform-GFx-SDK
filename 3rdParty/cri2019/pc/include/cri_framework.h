/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2009-2015 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Framework
 * Module   : Library User's Header
 * File     : cri_framework.h
 *
 ****************************************************************************/
 /*!
 *	\file		cri_framework.h
 */

/* Prevention of redefinition	*/
#ifndef CRI_FW_H_INCLUDED
#define CRI_FW_H_INCLUDED

/***************************************************************************
 *      Include files
 ***************************************************************************/
#include "cri_xpt.h"

#if defined(XPT_TGT_ANDROID)
#include <jni.h>
#endif

/***************************************************************************
 *      Macro Constants
 ***************************************************************************/
/* Version Number */
#define CRI_FW_VERSION				(0x00700400)
#define CRI_FW_VER_NUM				"0.70.04"
#define CRI_FW_VER_NAME				"CRI Framework"

#define CRIFWPAD_UP			(0x0001)
#define CRIFWPAD_DOWN		(0x0002)
#define CRIFWPAD_LEFT		(0x0004)
#define CRIFWPAD_RIGHT		(0x0008)
#define CRIFWPAD_BUTTON01	(0x0010)
#define CRIFWPAD_BUTTON02	(0x0020)
#define CRIFWPAD_BUTTON03	(0x0040)
#define CRIFWPAD_BUTTON04	(0x0080)
#define CRIFWPAD_BUTTON05	(0x0100)
#define CRIFWPAD_BUTTON06	(0x0200)
#define CRIFWPAD_BUTTON07	(0x0400)
#define CRIFWPAD_BUTTON08	(0x0800)
#define CRIFWPAD_BUTTON09	(0x1000)
#define CRIFWPAD_BUTTON10	(0x2000)

/***************************************************************************
 *      Macro Functions
 ***************************************************************************/
/* Avoid unused variable warnings */
#ifndef CRIFW_UNUSED
#define CRIFW_UNUSED(arg) { if (&(arg) == &(arg)) {} }
#endif

/***************************************************************************
 *      Data Type Declarations
 ***************************************************************************/
 typedef struct CriFwPadStickPosition {
 	CriFloat32	x;
	CriFloat32	y;
 } CriFwPadStickPosition;

/* Input Data type declaration by pad */
typedef struct CriFwPadStatus {
	CriUint32	down;
	CriUint32	up;
	CriUint32	press;
	CriUint32 	num_triggers;
	const CriFloat32 	*triggers;
	CriUint32 	num_sticks;
	const CriFwPadStickPosition *sticks;
} CriFwPadStatus;

/***************************************************************************
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      Prototype Functions
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*==========================================================================
 *      CRI Fw API
 *=========================================================================*/

CriBool CRIAPI criFw_Initialize(void);

void CRIAPI criFw_Finalize(void);

/*==========================================================================
 *      CRI Fw System API
 *=========================================================================*/
CriBool CRIAPI criFwSys_IsTerminated(void);
void CRIAPI criFwSys_WaitVsync(void);

/*==========================================================================
 *      CRI Fw Memory allocater API
 *=========================================================================*/
void* CRIAPI criFwMem_Alloc(CriSint32 size, CriSint32 align);

void CRIAPI criFwMem_Free(void *ptr);

/*==========================================================================
 *      CRI Fw Print API
 *=========================================================================*/
void CRIAPI criFwPrt_DrawText(CriSint32 x, CriSint32 y, const CriChar8 *format, ...);

void CRIAPI criFwPrt_DebugPrintf(const CriChar8 *format, ...);

/*==========================================================================
 *      CRI Fw Pad API
 *=========================================================================*/
const CriFwPadStatus* CRIAPI criFwPad_GetStatus(CriSint32 port);

const CriChar8* CRIAPI criFwPad_GetButtonName(CriUint32 button_code);

CriSint32 CRIAPI criFwPad_GetMaxPort(void);

#ifdef __cplusplus
}
#endif

#endif	/* CRI_FW_H_INCLUDED */

/* --- end of file --- */
