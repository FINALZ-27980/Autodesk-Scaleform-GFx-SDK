/*****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 1998-2016 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Middleware Library
 * Module   : CRI Common Header / Post-Process
 * File     : cri_xpt_post.h
 * Date     : 2016-04-01
 * Version  : 2.09
 *
 *****************************************************************************/
#ifndef CRI_INCL_CRI_XPT_POST_H
#define CRI_INCL_CRI_XPT_POST_H


/*****************************************************************************
 *      Macro definition 
 *****************************************************************************/

/* Static Asart when compiling
 *   This function is equal to STATIC_ASSERT of C++ Boost, and is imprementated
 *   by C language. If the condition is false, a compiler error is caused and
 *   it stop compiling.
 */
#define XPT_STATIC_ASSERT(cond) void xpt_static_assert_dummy_function(void* xpt_static_assert_array[(cond)?1:-1])

#ifdef __cplusplus
extern "C"
{
#endif
/* avoid warning  */
XPT_STATIC_ASSERT(1);
#ifdef __cplusplus
}
#endif


/*****************************************************************************
 *      Compiler option test
 *****************************************************************************/

/* Enum type test
 *   It is verified that the enum type adjusts to the int type. 
 *   To display an appropriate error message, it checks the compiler option 
 *   if possible. General static asart test works if it is impossible. 
 */
#if defined(__MWERKS__) /* CodeWarrior */
    //#if !__option(enumsalwaysint)
    //    #error ERROR cri_xpt_post.h : Compiler option 'Enums Always Int' should be ON.
    //#endif
#elif defined(__GNUC__)
    //#if Compiler option -fshort-enums is used
    //    #error ERROR cri_xpt_post.h : Compiler option '-fshort-enums' should not be used.
    //#endif
#endif
//typedef enum {XPT_TEST_ENUM_0, XPT_TEST_ENUM_1, XPT_TEST_ENUM_2} XptTestEnum;
//XPT_STATIC_ASSERT(sizeof(XptTestEnum) == sizeof(Uint32));	/* enum should be 4byte. */

/*****************************************************************************
 * Macros of constant value
 *****************************************************************************/

/* Null pointer type */
#if !defined(CRI_NULL)
#ifdef __cplusplus
#define CRI_NULL	(0)
#else
#define CRI_NULL	((void *)0)
#endif
#endif

/* Logical constant (TRUE, FALSE) */
#if !defined(CRI_FALSE)
#define CRI_FALSE	(0)
#endif
#if !defined(CRI_TRUE)
#define CRI_TRUE	(1)
#endif

/* Logical constant (switch) */
#if !defined(CRI_OFF)
#define CRI_OFF		(0)
#endif
#if !defined(CRI_ON)
#define CRI_ON		(1)
#endif

/* Success or Failure */
#if !defined(CRI_OK)
#define CRI_OK		(0)			/* Success */
#endif
#if !defined(CRI_NG)
#define CRI_NG		(-1)		/* Failure */
#endif

/*****************************************************************************
 * The integer type which can hold an pointer or an address up to 64 bits.
 * NOTE: In the environment of pointer 32bit and ROM address space 64bit, 
 *       this type can treat both transparently. 
 *****************************************************************************/

#if !defined(_TYPEDEF_CriUint64Adr)
#define _TYPEDEF_CriUint64Adr
typedef CriUint64				CriUint64Adr;		/* The integer type which can hold an pointer or an address up to 64 bits */
#endif

#if !defined(CRI_PTR_TO_UINT64ADR)
#define CRI_PTR_TO_UINT64ADR(ptr)		((CriUint64Adr)((CriUintPtr)(ptr)))	/* Convert pointer to CriUint64Adr */
#endif

#if !defined(CRI_UINT64ADR_TO_PTR)
#define CRI_UINT64ADR_TO_PTR(uint64adr)	((void *)(CriUintPtr)(uint64adr))	/* Convert CriUint64Adr to pointer */
#endif

#if !defined(CRI_XPT_DISABLE_UNPREFIXED_TYPE)

/*****************************************************************************
 * Macros for compatibility with old version
 *****************************************************************************/

/* Null pointer type */
#if !defined(NULL)
#define NULL		(CRI_NULL)
#endif

/* Logical constant (TRUE, FALSE) */
#if !defined(FALSE)
#define FALSE		(CRI_FALSE)
#endif
#if !defined(TRUE)
#define TRUE		(CRI_TRUE)
#endif

/* Logical constant (switch) */
#if !defined(OFF)
#define OFF			(CRI_OFF)
#endif
#if !defined(ON)
#define ON			(CRI_ON)
#endif

/* Success or Failure */
#if !defined(OK)
#define OK			(CRI_OK)
#endif
#if !defined(NG)
#define NG			(CRI_NG)
#endif

/*****************************************************************************
 * Types for compatibility with old version
 *****************************************************************************/

#if !defined(_TYPEDEF_Uint8)
#define _TYPEDEF_Uint8
typedef CriUint8				Uint8;		/* Unsigned 1-byte integer */
#endif

#if !defined(_TYPEDEF_Sint8)
#define _TYPEDEF_Sint8
typedef CriSint8				Sint8;		/* Signed 1-byte integer */
#endif

#if !defined(_TYPEDEF_Uint16)
#define _TYPEDEF_Uint16
typedef CriUint16				Uint16;		/* Unsigned 2-byte integer */
#endif

#if !defined(_TYPEDEF_Sint16)
#define _TYPEDEF_Sint16
typedef CriSint16				Sint16;		/* Signed 2-byte integer */
#endif

#if !defined(_TYPEDEF_Uint32)
#define _TYPEDEF_Uint32
typedef CriUint32				Uint32;		/* Unsigned 4-byte integer */
#endif

#if !defined(_TYPEDEF_Sint32)
#define _TYPEDEF_Sint32
typedef CriSint32				Sint32;		/* Signed 4-byte integer */
#endif

#if !defined(_TYPEDEF_Uint64)
#define _TYPEDEF_Uint64
typedef CriUint64				Uint64;		/* Unsigned 8-byte integer */
#endif

#if !defined(_TYPEDEF_Sint64)
#define _TYPEDEF_Sint64
typedef CriSint64				Sint64;		/* Signed 8-byte integer */
#endif

#if !defined(_TYPEDEF_Uint128)
#define _TYPEDEF_Uint128
typedef CriUint128				Uint128;	/* Unsigned 16-byte integer */
#endif

#if !defined(_TYPEDEF_Sint128)
#define _TYPEDEF_Sint128
typedef CriSint128				Sint128;	/* Signed 16-byte integer */
#endif

#if !defined(_TYPEDEF_Float16)
#define _TYPEDEF_Float16
typedef CriFloat16				Float16;	/* 2-byte float type */
#endif

#if !defined(_TYPEDEF_Float32)
#define _TYPEDEF_Float32
typedef CriFloat32				Float32;	/* 4-byte float type */
#endif

#if !defined(_TYPEDEF_Float64)
#define _TYPEDEF_Float64
typedef CriFloat64				Float64;	/* 8-byte float type */
#endif

#if !defined(_TYPEDEF_Fixed32)
#define _TYPEDEF_Fixed32
typedef CriFixed32				Fixed32;	/* Fixed point 32 bits */
#endif

/* Avoiding conflict with X11 API(xtrapproto.h) */
#if !defined(_TYPEDEF_Bool) && !defined(Bool)
#define _TYPEDEF_Bool
typedef CriBool					Bool;		/* Logical type */
#endif

#if !defined(_TYPEDEF_Char8)
#define _TYPEDEF_Char8
typedef CriChar8				Char8;		/* Character type */
#endif

#if !defined(_TYPEDEF_SintPtr)
#define _TYPEDEF_SintPtr
typedef CriSintPtr				SintPtr;
#endif

#if !defined(_TYPEDEF_UintPtr)
#define _TYPEDEF_UintPtr
typedef CriUintPtr				UintPtr;
#endif

#endif	/* CRI_XPT_DISABLE_UNPREFIXED_TYPE */

#endif	/* CRI_INCL_CRI_XPT_POST_H */

/* end of file */
