/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 1998-2011 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Middleware Library
 * Module   : CRI Common Header for Windows, Xbox and Xbox360
 * File     : cri_xpts_win.h
 * Date     : 2011-08-10
 * Version  : 2.04
 *
 ****************************************************************************/

#ifndef CRI_INCL_CRI_XPTS_H
#define CRI_INCL_CRI_XPTS_H

/*****************************************************************************
 * Data type declaration
 *****************************************************************************/

#if !defined(_TYPEDEF_CriUint8)
#define _TYPEDEF_CriUint8
typedef unsigned char			CriUint8;		/* Unsigned 1-byte integer */
#endif

#if !defined(_TYPEDEF_CriSint8)
#define _TYPEDEF_CriSint8
typedef signed char				CriSint8;		/* Signed 1-byte integer */
#endif

#if !defined(_TYPEDEF_CriUint16)
#define _TYPEDEF_CriUint16
typedef unsigned short			CriUint16;		/* Unsigned 2-byte integer */
#endif

#if !defined(_TYPEDEF_CriSint16)
#define _TYPEDEF_CriSint16
typedef signed short			CriSint16;		/* Signed 2-byte integer */
#endif

#if !defined(_TYPEDEF_CriUint32)
#define _TYPEDEF_CriUint32
typedef unsigned long			CriUint32;		/* Unsigned 4-byte integer */
#endif

#if !defined(_TYPEDEF_CriSint32)
#define _TYPEDEF_CriSint32
typedef signed long				CriSint32;		/* Signed 4-byte integer */
#endif

#if !defined(_TYPEDEF_CriUint64)
#define _TYPEDEF_CriUint64
typedef unsigned __int64		CriUint64;		/* Unsigned 8-byte integer */
#endif

#if !defined(_TYPEDEF_CriSint64)
#define _TYPEDEF_CriSint64
typedef signed __int64			CriSint64;		/* Signed 8-byte integer */
#endif

#if !defined(_TYPEDEF_CriUint128)
#define _TYPEDEF_CriUint128
typedef struct {								/* Unsigned 16-byte integer */
	CriUint64	h;								/* Upper 64 bits */
	CriUint64	l;								/* Lower 64 bits */
} CriUint128;
#endif

#if !defined(_TYPEDEF_CriSint128)
#define _TYPEDEF_CriSint128
typedef struct {								/* Signed 16-byte integer */
	CriSint64	h;								/* Upper 64 bits */
	CriUint64	l;								/* Lower 64 bits */
} CriSint128;
#endif

#if !defined(_TYPEDEF_CriFloat16)
#define _TYPEDEF_CriFloat16
typedef signed short			CriFloat16;		/* 2-byte float type */
#endif

#if !defined(_TYPEDEF_CriFloat32)
#define _TYPEDEF_CriFloat32
typedef float					CriFloat32;		/* 4-byte float type */
#endif

#if !defined(_TYPEDEF_CriFloat64)
#define _TYPEDEF_CriFloat64
typedef double					CriFloat64;		/* 8-byte float type */
#endif

#if !defined(_TYPEDEF_CriFixed32)
#define _TYPEDEF_CriFixed32
typedef signed long				CriFixed32;		/* Fixed point 32 bits */
#endif

#if !defined(_TYPEDEF_CriBool)
#define _TYPEDEF_CriBool
typedef CriSint32				CriBool;		/* Logical type */
#endif

#if !defined(_TYPEDEF_CriChar8)
#define _TYPEDEF_CriChar8
typedef char					CriChar8;		/* Character type */
#endif

/*****************************************************************************
 * The integer type which can hold an pointer
 *****************************************************************************/

#if defined(CRI_WIN64) || defined(_WIN64) || defined(_M_X64)

#if !defined(_TYPEDEF_CriSintPtr)
#define _TYPEDEF_CriSintPtr
typedef signed __int64			CriSintPtr;
#endif

#if !defined(_TYPEDEF_CriUintPtr)
#define _TYPEDEF_CriUintPtr
typedef unsigned __int64		CriUintPtr;
#endif

#else

#if defined(_MSC_VER) && (_MSC_VER >= 1300)

#if !defined(_TYPEDEF_CriSintPtr)
#define _TYPEDEF_CriSintPtr
typedef __w64 signed int		CriSintPtr;
#endif

#if !defined(_TYPEDEF_CriUintPtr)
#define _TYPEDEF_CriUintPtr
typedef __w64 unsigned int		CriUintPtr;
#endif

#else

#if !defined(_TYPEDEF_CriSintPtr)
#define _TYPEDEF_CriSintPtr
typedef CriSint32				CriSintPtr;
#endif

#if !defined(_TYPEDEF_CriUintPtr)
#define _TYPEDEF_CriUintPtr
typedef CriUint32				CriUintPtr;
#endif

#endif

#endif	/* end of _WIN64 */

/*****************************************************************************
 * Calling convention
 *****************************************************************************/

#if !defined(CRIAPI)
#define CRIAPI	__cdecl
#endif

#endif	/* CRI_INCL_CRI_XPTS_H */

/* end of file */
