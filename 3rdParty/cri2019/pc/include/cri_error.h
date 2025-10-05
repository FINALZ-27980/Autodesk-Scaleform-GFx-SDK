#ifndef	CRI_INCL_CRI_ERROR_H
#define	CRI_INCL_CRI_ERROR_H
/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2006 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Error
 * Module   : 
 * File     : cri_error.h
 *
 ****************************************************************************/
/*!
 * \file cri_error.h
 */
/*EN
 * \addtogroup CRI_ERROR Functions for error handling
 * @{
 */

/**************************************************************************** 
 *      Include file														* 
 ****************************************************************************/
#include "cri_xpt.h"

/**************************************************************************** 
 *		MACRO CONSTANT														* 
 ****************************************************************************/

/* Version Number */
#define CRIERROR_VER_NAME				"CRI Error"
#define CRIERROR_VER_NUM				"1.04.04"
#define CRIERROR_VER_OPTION

/*EN
 * \brief Error codes
 */
typedef enum {
	CRIERR_OK = 0,							/*EN< Succeeded */
	CRIERR_NG = -1,							/*EN< Error occurred */
	CRIERR_INVALID_PARAMETER = -2,			/*EN< Invalid argument */
	CRIERR_FAILED_TO_ALLOCATE_MEMORY = -3,	/*EN< Failed to allocate memory */
	CRIERR_UNSAFE_FUNCTION_CALL = -4,		/*EN< Parallel execution of thread-unsafe function */
	CRIERR_FUNCTION_NOT_IMPLEMENTED = -5,	/*EN< Function not implemented */
	CRIERR_LIBRARY_NOT_INITIALIZED = -6,	/*EN< Library not initialized */
	/* enum be 4bytes */
	CRIERR_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriError;

/*EN
 * \brief Error notification level
 */
typedef enum {
	CRIERR_NOTIFY_ALL = 0,		/*EN< Report all errors */
	CRIERR_NOTIFY_FATAL = 1,	/*EN<Report error (Disregards warning) */
	/* enum be 4bytes */
	CRIERR_NOTIFY_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriErrorNotificationLevel;

/* Error level */
typedef enum {
	CRIERR_LEVEL_ERROR = 0,
	CRIERR_LEVEL_WARNING = 1,
	/* enum be 4bytes */
	CRIERR_LEVEL_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriErrorLevel;

/**************************************************************************** 
 *		PROCESS MACRO														* 
 ****************************************************************************/

#if defined(CRIERROR_SIMPLIFY)
	/* Notification of Error */
	#define criErr_NotifyError(id, msg)							criErr_NotifyErrorSimple()
	#define criErr_NotifyError1(id, msg, p1)					criErr_NotifyErrorSimple()
	#define criErr_NotifyError2(id, msg, p1, p2)				criErr_NotifyErrorSimple()
	#define criErr_NotifyErrorPrmArray(id, msg, p1, p2, pa)		criErr_NotifyErrorSimple()
	#define criErr_NotifyErrorGeneric(_error_id, _error_no)		criErr_NotifyErrorSimple()
	/* Notification of Warning */
	#define criErr_NotifyWarning(id, msg)						criErr_NotifyWarningSimple()
	#define criErr_NotifyWarning1(id, msg, p1)					criErr_NotifyWarningSimple()
	#define criErr_NotifyWarning2(id, msg, p1, p2)				criErr_NotifyWarningSimple()
	#define criErr_NotifyWarningPrmArray(id, msg, p1, p2, pa)	criErr_NotifyWarningSimple()
	#define criErr_NotifyWarningGeneric(_error_id, _error_no)	criErr_NotifyWarningSimple()
#else
	/* Notification of Error */
	#define criErr_NotifyError(id, msg)							criErr_Notify(CRIERR_LEVEL_ERROR, id ":" msg)
	#define criErr_NotifyError1(id, msg, p1)					criErr_Notify1(CRIERR_LEVEL_ERROR, (id ":" msg), (CriUintPtr)(p1))
	#define criErr_NotifyError2(id, msg, p1, p2)				criErr_Notify2(CRIERR_LEVEL_ERROR, (id ":" msg), (CriUintPtr)(p1), (CriUintPtr)(p2))
	#define criErr_NotifyErrorPrmArray(id, msg, p1, p2, pa)		criErr_NotifyPrmArray(CRIERR_LEVEL_ERROR, (id ":" msg), (CriUintPtr)(p1), (CriUintPtr)(p2), (CriUintPtr *)(pa))
	#define criErr_NotifyErrorGeneric(_error_id, _error_no)		criErr_NotifyGeneric(CRIERR_LEVEL_ERROR, _error_id, _error_no)
	/* Notification of Warning */
	#define criErr_NotifyWarning(id, msg)						criErr_Notify(CRIERR_LEVEL_WARNING, id ":" msg)
	#define criErr_NotifyWarning1(id, msg, p1)					criErr_Notify1(CRIERR_LEVEL_WARNING, (id ":" msg), (CriUintPtr)(p1))
	#define criErr_NotifyWarning2(id, msg, p1, p2)				criErr_Notify2(CRIERR_LEVEL_WARNING, (id ":" msg), (CriUintPtr)(p1), (CriUintPtr)(p2))
	#define criErr_NotifyWarningPrmArray(id, msg, p1, p2, pa)	criErr_NotifyPrmArray(CRIERR_LEVEL_WARNING, (id ":" msg), (CriUintPtr)(p1), (CriUintPtr)(p2), (CriUintPtr *)(pa))
	#define criErr_NotifyWarningGeneric(_error_id, _error_no)	criErr_NotifyGeneric(CRIERR_LEVEL_WARNING, _error_id, _error_no)
#endif

/**************************************************************************** 
 *      Data type declaration												* 
 ****************************************************************************/

/*	Error Callback Function type	*/
typedef void (CRIAPI *CriErrCbFunc)(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);

/****************************************************************************
 *		Variable Declaration												*
 ****************************************************************************/
/* default argument of CriError */
#ifdef __cplusplus
namespace criErr {
	extern CriError ErrorContainer;
}
#endif	/* __cplusplus */

/****************************************************************************
 *		Function Declaration												*
 ****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*EN
 * \brief		Convert error ID to error message
 * \ingroup 	CRI_ERROR
 * \param[in]	errid	error ID
 * \return		error message
 * \par Description:
 * This function converts an error ID into a detailed error message. <br>
 * \attention
 * This function is an obsolete one. <br>
 * Use the ::criErr_ConvertIdToMessage function instead.
 * \sa criErr_ConvertIdToMessage
 */
const CriChar8* CRIAPI criErr_ConvertIdToMsg(const CriChar8 *errid);

/*EN
 * \brief		Convert error ID to error message
 * \ingroup 	CRI_ERROR
 * \param[in]	errid	error ID
 * \param[in]	p1		supplementary information 1
 * \param[in]	p2		supplementary information 2
 * \return		error message
 * \par Description:
 * This function converts error ID to detailed error message. <br>
 * \par Example:
 * \code
 * void user_error_callback_func(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);
 * {
 * 	const CriChar8 *errmsg;
 * 	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
 * 	printf("%s\n", errmsg);
 * }
 * \endcode
 */
const CriChar8* CRIAPI criErr_ConvertIdToMessage(const CriChar8 *errid, CriUint32 p1, CriUint32 p2);

/*EN
 * \brief		Register error callback function
 * \ingroup 	CRI_ERROR
 * \param[in]	cbf	error callback function
 * \return		NONE
 * \par Description:
 *This function registers an error callback function. <br>
 * The registered function is called if an error occurs within the CRI middleware library. <br>
 * Only one error callback function can be registered at a time. <br>
 * If this function is called again after being registered, the current registration is overwritten.
 * \par Example:
 * \code
 * void user_error_callback_func(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);
 * {
 * 	const CriChar8 *errmsg;
 * 	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
 * 	printf("%s\n", errmsg);
 * }
 * 
 * void main(int ac, char *av[])
 * {
 * 		:
 * 	// Registers the error callback function
 * 	criErr_SetCallback(user_error_callback_func);
 * 		:
 * }
 * \endcode
 */
void CRIAPI criErr_SetCallback(CriErrCbFunc cbf);

/*EN
 *  \brief		Change error notification level
 *	\ingroup 	CRI_ERROR
 *	\param[in]	level	error notification level
 *	\return		NONE
 * \par Description:
 *	This function changes the level of error information that is notified to the error callback.
 */
void CRIAPI criErr_SetErrorNotificationLevel(CriErrorNotificationLevel level);

/*EN
 *  \brief		Retrieve error count
 *	\ingroup 	CRI_ERROR
 *	\param[in]	level	error level
 *	\return		number of errors occurred
 * \par Description:
 *	This function retrieves the number of errors occurred.
 */
CriUint32 CRIAPI criErr_GetErrorCount(CriErrorLevel level);

/*EN
 *  \brief		Resets error count
 *	\ingroup 	CRI_ERROR
 *	\param[in]	level	error level
 *	\return		NONE
 * \par Explanation:
 *	This function resets the counter for the number of error occurred.
 */
void CRIAPI criErr_ResetErrorCount(CriErrorLevel level);

/* Error notification (Internal functions) */
void CRIAPI criErr_Notify(CriErrorLevel level, const CriChar8 *errid);
void CRIAPI criErr_Notify1(CriErrorLevel level, const CriChar8 *errid, CriUintPtr p1);
void CRIAPI criErr_Notify2(CriErrorLevel level, const CriChar8 *errid, CriUintPtr p1, CriUintPtr p2);
void CRIAPI criErr_NotifyPrmArray(CriErrorLevel level, const CriChar8 *errid, CriUintPtr p1, CriUintPtr p2, CriUintPtr *pa);
void CRIAPI criErr_NotifyGeneric(CriErrorLevel level, const CriChar8 *error_id, CriError error_no);
void CRIAPI criErr_NotifyErrorSimple(void);
void CRIAPI criErr_NotifyWarningSimple(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/***************************************************************************
 *      For compatibility with old versions
 ***************************************************************************/
#define criErr_Invoke(errid)						criErr_Notify(CRIERR_LEVEL_ERROR, errid)
#define criErr_Invoke1(errid, p1)					criErr_Notify1(CRIERR_LEVEL_ERROR, errid, p1)
#define criErr_Invoke2(errid, p1, p2)				criErr_Notify2(CRIERR_LEVEL_ERROR, errid, p1, p2)
#define criErr_InvokePrmArray(errid, p1, p2, pa)	criErr_NotifyPrmArray(CRIERR_LEVEL_ERROR, errid, p1, p2, pa)
#define criErr_InvokeGeneric(error_id, error_no)	criErr_NotifyGeneric(CRIERR_LEVEL_ERROR, error_id, error_no)
#define criErr_Occur(id, msg)						criErr_Notify(CRIERR_LEVEL_ERROR, id ":" msg)
#define criErr_Occur1(id, msg, p1)					criErr_Notify1(CRIERR_LEVEL_ERROR, (id ":" msg), (CriUintPtr)(p1))
#define criErr_Occur2(id, msg, p1, p2)				criErr_Notify2(CRIERR_LEVEL_ERROR, (id ":" msg), (CriUintPtr)(p1), (CriUintPtr)(p2))
#define criErr_OccurPrmArray(id, msg, p1, p2, pa)	criErr_NotifyPrmArray(CRIERR_LEVEL_ERROR, (id ":" msg), (CriUintPtr)(p1), (CriUintPtr)(p2), (CriUintPtr*)(pa))
#define criErr_OccurGeneric(_error_id, _error_no)	criErr_NotifyGeneric(CRIERR_LEVEL_ERROR, _error_id, _error_no)

/*EN
 * @}
 */

#endif	//	_CRI_INCL_CRI_ERROR_H

/* --- end of file --- */
