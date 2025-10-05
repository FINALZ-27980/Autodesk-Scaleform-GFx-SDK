/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010 CRI Middleware Co., Ltd.
 *
 * Library  : CRI AtomEx Monitor Library
 * Module   : Monitor Library C Interface Header
 * File     : cri_atom_ex_monitor.h
 *
 ****************************************************************************/
/*!
 *	\file cri_atom_ex_monitor.h
 */

#ifndef CRI_INCL_CRI_ATOMEX_MONITOR_H
#define CRI_INCL_CRI_ATOMEX_MONITOR_H

/***************************************************************************
 *      Include files
 ***************************************************************************/

#include "cri_xpt.h"
#include "cri_atom_ex.h"

/***************************************************************************
 *      Macro Constants
 ***************************************************************************/
/* Version Number */
#define CRIATOMEX_MONITOR_VERSION				(0x01110300)
#define CRIATOMEX_MONITOR_VER_NUM				"1.11.03.00"
#define CRIATOMEX_MONITOR_VER_NAME				"CRI AtomEx Monitor"
#define CRIATOMEX_MONITOR_VER_OPTION

/*EN
 * \brief Default number of preview objects
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par Description:
 * Default number of preview objects.<br>
 * \sa criAtomExMonitor_SetDefaultConfig
 */
#define CRIATOMX_MONITOR_DEFAULT_NUM_PUREVIEW_OBJECTS		(200)

/*EN
 * \brief Default communication buffer size
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par Description:
 * Default communication buffer size.<br>
 * \sa criAtomExMonitor_SetDefaultConfig
 */
#define CRIATOMX_MONITOR_DEFAULT_COMMUNICATION_BUFFER_SIZE	(2*1024*1024)

/*EN
 * \brief Default playback position update interval
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par Description:
 * Default playback position update interval.<br>
 * \sa criAtomExMonitor_SetDefaultConfig
 */
#define CRIATOMX_MONITOR_DEFAULT_PLAYBACK_POSITION_UPDATE_INTERVAL	(8)

/*EN
 * \brief Different types of logs
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par Description:
 * Different types of logs available.<br>
 * \sa criAtomExMonitor_SetLogMode
 */
#define CRIATOMEX_MONITOR_LOG_MODE_OFF						(0)
#define CRIATOMEX_MONITOR_LOG_MODE_PLAYBACK					(1)
#define CRIATOMEX_MONITOR_LOG_MODE_ERROR					(1 << 1)
#define CRIATOMEX_MONITOR_LOG_MODE_LOW_LEVEL_PLAYBACK		(1 << 2)
#define CRIATOMEX_MONITOR_LOG_MODE_SYSTEM_INFORMATION		(1 << 3)
#define CRIATOMEX_MONITOR_LOG_MODE_HANDLE_INFORMATION		(1 << 4)
#define CRIATOMEX_MONITOR_LOG_MODE_CUE_LIMIT				(1 << 5)
#define CRIATOMEX_MONITOR_LOG_MODE_PROBABILITY				(1 << 6)
#define CRIATOMEX_MONITOR_LOG_MODE_CATEGORY					(1 << 7)
#define CRIATOMEX_MONITOR_LOG_MODE_EXECUTING_INFORMATION	(1 << 8)
#define CRIATOMEX_MONITOR_LOG_MODE_3D_INFO					(1 << 9)
#define CRIATOMEX_MONITOR_LOG_MODE_USER_LOG					(1 << 10)

#define CRIATOMEX_MONITOR_LOG_MODE_ALL						(0xFFFFFFFF)


/***************************************************************************
 *      Macro Functions
 ***************************************************************************/

/*EN
 * \brief Assign the default values to the configuration structure of the Monitor library
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par Description:
 * Assign the default values to the configuration structure of the Monitor library.
 * \sa CriAtomExMonitorConfig
 */
#define criAtomExMonitor_SetDefaultConfig(p_config)	\
{\
	(p_config)->max_preivew_object = CRIATOMX_MONITOR_DEFAULT_NUM_PUREVIEW_OBJECTS;\
	(p_config)->communication_buffer_size = CRIATOMX_MONITOR_DEFAULT_COMMUNICATION_BUFFER_SIZE;\
	(p_config)->additional_buffer = 0;\
	(p_config)->additional_buffer_size = 0;\
	(p_config)->playback_position_update_interval = CRIATOMX_MONITOR_DEFAULT_PLAYBACK_POSITION_UPDATE_INTERVAL;\
}
 
/***************************************************************************
 *      Data Type Declarations
 ***************************************************************************/
/*EN
 * \brief Configuration structure used to initialize the Monitor library
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par Description:
 * This structure is used to specify the behavior of the Monitor library.<br>
 * It is passed as an argument to the ::criAtomExMonitor_Initialize function.<br>
 * \sa criAtomExMonitor_Initialize, criAtomExMonitor_SetDefaultConfig
 */
typedef struct CriAtomExMonitorConfigTag {
	/*EN
		\brief max_preview_object
	 */
	CriUint32	max_preivew_object;
	/*EN
		\brief communication_buffer_size
		\par Description:
		Specify the buffer size to be used for communication between the monitor library and the authoring tool. <br>
		There are two buffers, one for sending and one for receiving, and each has an extension area that is half of the setting value. <br>
		Therefore, the buffer size actually required is three times the set value. <br>
	 */
	CriUint32	communication_buffer_size;
	/*EN
		\brief additional_buffer
	 */
	CriUintPtr	additional_buffer;
	/*EN
		\brief additional_buffer_size
	 */
	CriUint32	additional_buffer_size;
	/*EN
		\brief Playback position update interval
		\par Description:
		This variable specifies the interval at which to send the playback positions
		when the server processing is executed.<br>
		By changing the value of playback_position_update_interval, 
		the frequency at which the playback positions are sent can be lowered 
		without changing the execution frequency of the server process.<br>
		<br>
		In playback_position_update_interval, specify how many times the server process 
		should be executed before the playback position information is sent.<br>
		For example, if playback_position_update_interval is set to 2, 
		the playback position information is sent each time 
		the server process has been executed twice.<br>
		(The frequency of sending the playback position information is 1/2.)<br>
	*/
	CriSint32	playback_position_update_interval;
} CriAtomExMonitorConfig;

/*EN
 * \brief Date Update Type
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par Description:
 * It is the target of data update by CRI Atom Craft (authoring tool) at in-game preview. <br>
 * \sa CriAtomExMonitorDataUpdateNotificationInfo
 */
typedef enum CriAtomExMonitorDataUpdateTargetTag {
	CRIATOMEXMONITOR_DATA_UPDATE_TARGET_ACF = 0,			/*EN< ACF Update */
	CRIATOMEXMONITOR_DATA_UPDATE_TARGET_ACB = 1,			/*EN< ACB Update */
	/* enum size is 4bytes */
	CRIATOMEXMONITOR_DATA_UPDATE_TARGET_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExMonitorDataUpdateTarget;

/*EN
 * \brief Date Update Status
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par Description:
 * It is the state of data update by CRI Atom Craft (authoring tool) at in-game preview. <br>
 * \sa CriAtomExMonitorDataUpdateNotificationInfo
 */
typedef enum CriAtomExMonitorDataUpdateEventTag {
	CRIATOMEXMONITOR_DATA_UPDATE_EVENT_BEGIN = 0,	/*EN< Start Event */
	CRIATOMEXMONITOR_DATA_UPDATE_EVENT_END   = 1,	/*EN< End Event  */
	/* enum size is 4bytes */
	CRIATOMEXMONITOR_DATA_UPDATE_EVENT_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExMonitorDataUpdateEvent;

/*EN
 * \brief Date Update Info
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par Description:
 * It is the infomation of data update by CRI Atom Craft (authoring tool) at in-game preview. <br>
 * \sa criAtomExMonitor_SetDataUpdateNotificationCallback
 */
typedef struct CriAtomExMonitorDataUpdateNotificationInfoTag {
	CriAtomExMonitorDataUpdateTarget target;			/*EN< Target */
	CriAtomExMonitorDataUpdateEvent event;				/*EN< Event */
	CriAtomExAcbHn acb_hn;								/*EN< ACB handle */
	const CriChar8* name;								/*EN< Name */
} CriAtomExMonitorDataUpdateNotificationInfo;

/*EN
 * \brief Get the data update notification information by authoring tool Callback function
 * \ingroup ATOMEXLIB_ACB
 * \par Description:
 * \param[in]	obj			User specified object
 * \param[in]	info		Data update notification information
 * \return					None
 * \par Description:
 * This is a callback function to be called when data update processing from the authoring tool occurs during in-game preview. <br>
 * Use this when you want to obtain the data update status on the application side during in-game preview. <br>
 * <br>
 * Use the ::criAtomExMonitor_SetDataUpdateNotificationCallback function to register the callback function. <br>
 * The registered callback function is executed at the timing before and after data update from the authoring tool during in-game preview. <br>
 * \attention
 * Basically, please do not use the Atom API within the callback function. <br>
 * If you block long processing within this callback function, problems such as out of sound will occur, so please be careful.<br>
 * Please refer to the CriAtomExMonitorDataUpdateNotificationInfo structure passed as an argument to the callback function only within the callback function. <br>
 * Before referring outside the callback function, save the contents in a separate area beforehand.
 * \sa criAtomExMonitor_SetDataUpdateNotificationCallback, CriAtomExMonitorDataUpdateNotificationInfo
 */
typedef void (CRIAPI *CriAtomExMonitorDataUpdateNotificationCbFunc)(
	void *obj, const CriAtomExMonitorDataUpdateNotificationInfo* info);

/*	Log Callback Function type	*/
typedef void (*CriAtomExMonitorLogCbFunc)(void* obj, const CriChar8 *log_string);

/***************************************************************************
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      Prototype Functions
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*EN
 * \brief Calculate the size of the work buffer required to initialize the monitoring feature
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \param[in]	config		configuration structure for initialization
 * \return		CriSint32	work buffer size
 * \par Description:
 * This function retrieves the size of the work buffer needed to use the monitoring feature.<br>
 * <br>
 * If the calculation of the size of the work buffer fails, this function returns -1.<br>
 * The reason why the calculation failed can be determined 
 * by checking the error callback message.<br>
 * \par Remarks:
 * The work buffer size needed by the monitoring feature depends on 
 * the values of the parameters in the ::CriAtomExMonitorConfig structure.<br>
 * <br>
 * If you specify NULL for the argument, the default settings 
 * (i.e., the same parameters than when ::criAtomExMonitor_SetDefaultConfig is used) 
 * are used for calculating the size of the work buffer.
 * <br>
 * The information passed in the config argument is only referenced within the function.<br>
 * Therefore the memory it uses can be released after executing the function.
 * \sa criAtomExMonitor_SetDefaultConfig, criAtomExMonitor_Initialize, CriAtomExMonitorConfig
 */
CriSint32 CRIAPI criAtomExMonitor_CalculateWorkSize(const CriAtomExMonitorConfig* config);

/*EN
 * \brief Initialize the monitoring feature
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \param[in]	config		configuration structure for initialization
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \par Description:
 * This function initializes the monitoring feature.<br>
 * Before using the monitoring feature, always execute this function.<br>
 * (Once this function is executed, the monitoring feature will be available 
 * until the ::criAtomExMonitor_Finalize function is called.)<br>
 * This function should be called after the ::criAtomEx_Initialize function and 
 * before the ::criAtomEx_Finalize function.<br>
 * \sa criAtomExMonitor_Finalize, CriAtomExMonitorConfig
 */
void CRIAPI criAtomExMonitor_Initialize(
	const CriAtomExMonitorConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Finalize the monitoring feature
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par Description:
 * This function finalizes the monitoring feature.<br>
 * \attention
 * This function cannot be called before executing the ::criAtomExMonitor_Initialize function.<br>
 * \sa criAtomExMonitor_Initialize
 */
void CRIAPI criAtomExMonitor_Finalize(void);

/*EN
 * \brief Get the server IP address string
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par Description:
 * Get the server IP address string.<br>
 * \attention
 * This function cannot be called before executing the ::criAtomExMonitor_Initialize function.<br>
 * \sa criAtomExMonitor_Initialize, criAtomExMonitor_GetClientIpString
 */
const CriChar8* CRIAPI criAtomExMonitor_GetServerIpString(void);

/*EN
 * \brief Get the client IP address string
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par Description:
 * Get the client IP address string.<br>
 * \attention
 * This function cannot be called before executing the ::criAtomExMonitor_Initialize function.<br>
 * \sa criAtomExMonitor_Initialize, criAtomExMonitor_GetServerIpString
 */
const CriChar8* CRIAPI criAtomExMonitor_GetClientIpString(void);

/*EN
 * \brief Get the tool connection status
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \return		CriBool	connection status (CRI_TRUE: connected, CRI_FALSE: not connected)
 * \par Description:
 * Determines if the tool is connected or not.<br>
 * \attention
 * This function cannot be called before executing the ::criAtomExMonitor_Initialize function.<br>
 * \sa criAtomExMonitor_Initialize
 */
CriBool CRIAPI criAtomExMonitor_IsConnected(void);

/*EN
 * \brief Register the log retrieval callback function
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \param		cbf			callback function
 * \param		obj			user specified object
 * \par Description:
 * Registers a callback function for getting log.<br>
 * The log retrieval process is started by registering a callback function 
 * and stopped by setting it to NULL.<br>
 * To change the log mode, call the ::criAtomExMonitor_SetLogMode function.<br>
 * \attention
 * This function cannot be called before executing the ::criAtomExMonitor_Initialize function.<br>
 * \sa criAtomExMonitor_Initialize, criAtomExMonitor_SetLogMode
 */
void CRIAPI criAtomExMonitor_SetLogCallback(CriAtomExMonitorLogCbFunc cbf, void* obj);

/*EN
 * \brief Specify log mode
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \param		mode		Log output mode
 * \par Description:
 * Specify the log retrieval mode.<br>
 * The log retrieval callback function (registered 
 * by the ::criAtomExMonitor_SetLogCallback function) will be called 
 * depending on the mode specified by this function.<br>
 * \sa criAtomExMonitor_SetLogCallback
 */
void CRIAPI criAtomExMonitor_SetLogMode(CriUint32 mode);

/*EN
 * \brief User log output
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \param		message		User log message
 * \par Description: 
 * Outputs the user log. <br>
 * The log output can be obtained and displayed by using a log acquisition callback or profiler. 
 * \sa criAtomExMonitor_SetLogCallback
 */
void CRIAPI criAtomExMonitor_OutputUserLog(const CriChar8* message);

/*EN
 * \brief Set data update notification callback function
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \param[in]	func		Data update notification callback function
 * \param[in]	obj			user specified object
 * \par Description: 
 * Register a callback function to be called when data update processing from the authoring tool occurs during in-game preview. <br>
 * \attention
 * Please do not use the Atom API within the callback function. <br>
 * The callback function is also executed from server processing in the AtomMonitor library. <br>
 * Therefore, if you execute an API that does not consider interrupts to server processing, errors may occur or deadlock may occur. <br>
 * <br>
 * If you block long processing within the callback function, problems such as out of sound will occur, so please be careful. <br>
 * <br>
 * Only one callback function can be registered. <br>
 * If you perform a registration operation more than once, the already registered callback function will be overwritten by the callback function registered later. <br>
 * <br>
 * Registering registered functions can be canceled by specifying NULL for func. <br>
 * \attention
 * This function can not be executed before the ::criAtomExMonitor_Initialize function is executed. <br>
 * \sa CriAtomExMonitorDataUpdateNotificationCbFunc, CriAtomExMonitorDataUpdateNotificationInfo
 */
void CRIAPI criAtomExMonitor_SetDataUpdateNotificationCallback(
	CriAtomExMonitorDataUpdateNotificationCbFunc func, void *obj);

#ifdef __cplusplus
}
#endif

#endif //	CRI_INCL_CRI_ATOMEX_MONITOR_H
