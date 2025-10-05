/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Atom
 * Module   : Library User's Header for WASAPI
 * File     : cri_atom_wasapi.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_atom_wasapi.h
 */

/* Prevent redefinition	*/
#ifndef CRI_INCL_CRI_ATOM_WASAPI_H
#define CRI_INCL_CRI_ATOM_WASAPI_H

/***************************************************************************
 *      Include files
 ***************************************************************************/
#include <Windows.h>
#include <sdkddkver.h>
#include <Audioclient.h>
#include <AudioSessionTypes.h>
#include <mmdeviceapi.h>
#include <cri_xpt.h>
#include <cri_atom.h>
#include <cri_atom_ex.h>
#include <cri_atom_asr.h>

/***************************************************************************
 *      Macro Constants
 ***************************************************************************/

/***************************************************************************
 *      Macro Functions
 ***************************************************************************/
/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*EN
 * \brief Assign the default values to the configuration structure used for the library's initialization.
 * \ingroup ATOMLIB_WASAPI
 * \param[out]	p_config	Pointer to the configuration structure used for the library's initialization.
 * \par Description: 
 * Assign the default values to the configuration structure (::CriAtomConfig_WASAPI)
 * that is passed to the ::criAtom_Initialize_WASAPI function. <br>
 * \attention
 * This macro is for the low level API. <br>
 * When using the functions of the AtomEx layer, call the
 * ::criAtomEx_SetDefaultConfig_WASAPI macro instead. 
 * \sa CriAtomConfig_WASAPI
 */
#define criAtom_SetDefaultConfig_WASAPI(p_config)			\
{															\
	criAtom_SetDefaultConfig(&(p_config)->atom);			\
	criAtomAsr_SetDefaultConfig(&(p_config)->asr);			\
	criAtomHcaMx_SetDefaultConfig(&(p_config)->hca_mx);		\
}

/*EN
 * \brief Audio endpoint enumeration callback
 * \ingroup ATOMLIB_WASAPI
 * \param[in]	object				User Object
 * \param[in]	device				IMMDevice instance
 * \par Description: 
 * The type of the callback function used to notify the audio endpoint.<br>
 * By registering this function type callback function in the ::criAtom_EnumAudioEndpoints_WASAPI function,<br>
 * it is possible to receive an IMMDevice instance via a callback.<br>
 * \attention
 * IMMDevice instances MUST NOT be discarded within the callback function.<br>
 * \sa criAtom_EnumAudioEndpoints_WASAPI
 */
typedef void (CRIAPI *CriAtomAudioEndpointCbFunc_WASAPI)(void *object, IMMDevice *device);

/*EN
 * \brief Device update notification callback
 * \ingroup ATOMLIB_WASAPI
 * \param[in]	object				User Object
 * \par Description: 
 * The type of callback function used for device update notification. <br>
 * By registering this function type callback function in the ::criAtom_SetDeviceUpdateCallback_WASAPI function,
 * it is possible to receive notification via callback when the device is updated. <br>
 * \sa criAtom_SetDeviceUpdateCallback_WASAPI
 */
typedef void (CRIAPI *CriAtomDeviceUpdateCbFunc_WASAPI)(void *object);

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*EN
 * \brief Assign the default values to the configuration structure used for the library's initialization.
 * \ingroup ATOMLIB_WASAPI
 * \param[out]	p_config	Pointer to the configuration structure used for the library's initialization.
 * \par Description: 
 * Assign the default values to the configuration structure (::CriAtomExConfig_WASAPI)
 * that is passed to the ::criAtomEx_Initialize_WASAPI function. <br>
 * \sa CriAtomExConfig_WASAPI
 */
#define criAtomEx_SetDefaultConfig_WASAPI(p_config)			\
{															\
	criAtomEx_SetDefaultConfig(&(p_config)->atom_ex);		\
	criAtomExAsr_SetDefaultConfig(&(p_config)->asr);		\
	criAtomExHcaMx_SetDefaultConfig(&(p_config)->hca_mx);	\
}

/***************************************************************************
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*EN
 * \brief Configuration structure used for the initialization of the Atom library
 * \ingroup ATOMLIB_WASAPI
 * This configuration structure is used to specify the behavior of the CRI Atom library. <br>
 * It is passed as an argument to the ::criAtom_Initialize_WASAPI function. <br>
 * \attention
 * This structure is used for low level API. <br>
 * When using the functions of the AtomEx layer, use the
 * ::CriAtomExConfig_WASAPI structure instead. 
 * \sa criAtom_Initialize_WASAPI, criAtom_SetDefaultConfig_WASAPI
 */
typedef struct CriAtomConfigTag_WASAPI {
	CriAtomConfig			atom;		/*EN< Configuration structure for the intialization of the Atom library */
	CriAtomAsrConfig		asr;		/*EN< Configuration structure for the intialization of ASR */
	CriAtomHcaMxConfig		hca_mx;		/*EN< Configuration structure for the intialization of HCA-MX */
} CriAtomConfig_WASAPI;

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*EN
 * \brief Configuration structure used for the initialization of the Atom library
 * \ingroup ATOMLIB_WASAPI
 * This configuration structure is used to specify the behavior of the CRI Atom library. <br>
 * It is passed as an argument to the ::criAtomEx_Initialize_WASAPI function. <br>
 * \sa criAtomEx_Initialize_WASAPI, criAtomEx_SetDefaultConfig_WASAPI
 */
typedef struct CriAtomExConfigTag_WASAPI {
	CriAtomExConfig			atom_ex;	/*EN< Configuration structure for the intialization of AtomEx */
	CriAtomExAsrConfig		asr;		/*EN< Configuration structure for the intialization of ASR */
	CriAtomExHcaMxConfig	hca_mx;		/*EN< Configuration structure for the intialization of HCA-MX */
} CriAtomExConfig_WASAPI;

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
 *      CRI Atom API
 *=========================================================================*/
/*EN
 * \brief Calculate the size of the work buffer required to initialize the library
 * \ingroup ATOMLIB_WASAPI
 * \param[in]	config		Configuration structure for initialization
 * \return		CriSint32	Work buffer size
 * \par Description: 
 * This function retrieves the size of the work buffer needed to use the library. <br>
 * \par Remarks: 
 * The work buffer size needed by the library's initialization depends on the values of the parameters in
 * the ::CriAtomConfig_WASAPI structure.<br>
 * <br>
 * The information passed in the config argument is only referenced within this function.<br>
 * Therefore the memory it uses can be released after executing the function.
 * \attention
 * This function is for the low level API. <br>
 * When using the functions of the AtomEx layer, call 
 * ::criAtomEx_CalculateWorkSize_WASAPI instead. 
 * \sa CriAtomConfig_WASAPI, criAtom_Initialize_WASAPI
 */
CriSint32 CRIAPI criAtom_CalculateWorkSize_WASAPI(const CriAtomConfig_WASAPI *config);

/*EN
 * \brief Library initialization
 * \ingroup ATOMLIB_WASAPI
 * \param[in]	config		Configuration structure for initialization
 * \param[in]	work		Work buffer
 * \param[in]	work_size	Work buffer size
 * \par Description: 
 * Initializes the library. <br>
 * In order to be able to use the features of the library, you must first call this function. <br>
 * (Once this function is called, the features of the library are available until the ::criAtom_Finalize_WASAPI function
 * is called.) <br>
 * <br>
 * To initialize the library, you must allocate a memory area (work buffer)
 * that will be used internally by the library. <br>
 * The size of the work buffer needed by the library depends on the values of the parameters in the configuration structure
 * used for initialization. <br>
 * Use the ::criAtom_CalculateWorkSize_WASAPI function to calculate
 * the work buffer size. <br>
 * \par Remarks: 
 * If an allocator has already been registered with the ::criAtom_SetUserAllocator macro,
 * the work buffer size does not need to be specified. <br>
 * (By passing NULL for work and 0 for work_size, the amount of memory corresponding to the work buffer size
 * is dynamically allocated by the registered allocator.) 
 * <br>
 * The information passed in the config argument is only referenced within this function.<br>
 * Therefore the memory it uses can be released after executing the function.
 * \attention
 * This function calls the following functions internally: <br>
 * 	- ::criAtom_Initialize
 * 	- ::criAtomAsr_Initialize
 * 	- ::criAtomHcaMx_Initialize
 * 	.
 * Therefore, if you call this function, do not call the functions listed above. <br>
 * <br>
 * If you call this function, you must always call the ::criAtom_Finalize_WASAPI  function later. <br>
 * Do not call this function again until you have called the ::criAtom_Finalize_WASAPI function. <br>
 * <br>
 * This function is for the low level API. <br>
 * When using the functions of the AtomEx layer, call 
 * ::criAtomEx_Initialize_WASAPI instead. 
 * \sa CriAtomConfig_WASAPI, criAtom_Finalize_WASAPI,
 * criAtom_SetUserAllocator, criAtom_CalculateWorkSize_WASAPI
 */
void CRIAPI criAtom_Initialize_WASAPI(
	const CriAtomConfig_WASAPI *config, void *work, CriSint32 work_size);

/*EN
 * \brief Finalize the library
 * \ingroup ATOMLIB_WASAPI
 * \par Description: 
 * This function finalizes the library. <br>
 * \attention
 * This function calls the following functions internally: <br>
 * 	- ::criAtom_Finalize
 * 	- ::criAtomAsr_Finalize
 * 	- ::criAtomHcaMx_Finalize
 * 	.
 * Therefore, if you call this function, do not call the functions above. <br>
 * <br>
 * This function cannot be called before the ::criAtom_Initialize_WASAPI function is called. <br>
 * <br>
 * This function is for the low level API. <br>
 * When using the functions of the AtomEx layer, call
 * ::criAtomEx_Finalize_WASAPI instead. 
 * \sa criAtom_Initialize_WASAPI
 */
void CRIAPI criAtom_Finalize_WASAPI(void);

/*EN
 * \brief Get the mixer format
 * \ingroup ATOMLIB_WASAPI
 * \param[out]	format		Mixer format
 * \return		CriBool		Was the mixer format acquired? (CRI_TRUE = Success, CRI_FALSE = Failure)
 * \par Description: 
 * Gets the mixer format used in Shared Mode. <br>
 * \par Remarks: 
 * This function is a wrapper around the IAudioClient::GetMixFormat function. <br>
 * When it is called, an AudioClient is created within the function and the GetMixFormat function is executed. <br>
 * \attention
 * This function can only be used before the library's initialization. <br>
 * <br>
 * The usable formats differ between Shared Mode and Exclusive Mode. <br>
 * The WAVEFORMATEXTENSIBLE structure returned by this function corresponds to the IEEE float PCM data format,
 * but this format is mostly unusable in Exclusive Mode. <br>
 */
CriBool CRIAPI criAtom_GetAudioClientMixFormat_WASAPI(WAVEFORMATEXTENSIBLE *format);

/*EN
 * \brief Check whether the specified format is usable or not
 * \ingroup ATOMLIB_WASAPI
 * \param[in]	format		Format to be used
 * \return		CriBool		Is the specified format usable? (CRI_TRUE = Usable, CRI_FALSE = Not Usable)
 * \par Description: 
 * Checks whether the format specified in the argument is usable in Exclusive Mode or not. <br>
 * \par Remarks: 
 * This function is a wrapper around the IAudioClient::IsFormatSupported function. <br>
 * When it is called, an AudioClient is created within the function and the IsFormatSupported function is executed. <br>
 * \attention
 * This function can only be used before the library's initialization. <br>
 * <br>
 * On some devices and for some parameters, the WASAPI initialization may fail
 * even if this function returns successfully. <br>
 * If the library fails to initialize even when this function returns CRI_TRUE,
 * change the specified format or use the Shared Mode. <br>
 */
CriBool CRIAPI criAtom_GetAudioClientIsFormatSupported_WASAPI(const WAVEFORMATEX *format);

/*EN
 * \brief Sharing mode specification
 * \ingroup ATOMLIB_WASAPI
 * \param[in]	mode	Mode to be used
 * \par Description: 
 * Specifies whether to use WASAPI in Shared Mode or Exclusive Mode. <br>
 * <br>
 * If this function is not executed (or if it is executed by specifying AUDCLNT_SHAREMODE_SHARED),
 * the Atom library will initialize WASAPI in Shared Mode. <br>
 * If this function is executed by specifying AUDCLNT_SHAREMODE_EXCLUSIVE,
 * the Atom library will initialize WASAPI in Exclusive Mode. <br>
 * \attention
 * You must execute this function before initializing the library. <br>
 * <br>
 * To use the Exclusive Mode, the mode must be specified with this function and the
 * format must also be specified via the ::criAtom_SetAudioClientFormat_WASAPI function. <br>
 * \sa criAtom_SetAudioClientFormat_WASAPI
 */
void CRIAPI criAtom_SetAudioClientShareMode_WASAPI(AUDCLNT_SHAREMODE mode);

/*EN
 * \brief Output format specification
 * \ingroup ATOMLIB_WASAPI
 * \par Description: 
 * \param[in]	format		Format to be used
 * \par Description: 
 * Specifies the format to be used in Exclusive Mode. <br>
 * \par Remarks: 
 * The format specified is passed to the IAudioClient::Initialize function. <br>
 * \attention
 * You must call this function before initializing the library. <br>
 * <br>
 * To use the Exclusive Mode, the format must be specified with this function and the
 * mode must also be specified via the ::criAtom_SetAudioClientShareMode_WASAPI function. <br>
 * \sa criAtom_SetAudioClientShareMode_WASAPI
 */
void CRIAPI criAtom_SetAudioClientFormat_WASAPI(const WAVEFORMATEX *format);

/*EN
 * \brief Set the buffering time 
 * \ingroup ATOMLIB_WASAPI
 * \param[in]	ref_time	Buffering time
 * \par Description: 
 * Specifies the buffering time (before the WASAPI initialization). <br>
 * The Atom library will allocate a sound buffer large enough to hold data for the amount of time specified by this function. <br>
 * \par Remarks: 
 * The buffering time is passed to the IAudioClient::Initialize function. <br>
 * <br>
 * If this function is not used, the Atom library will calculate the appropriate buffering time based on the
 * server process frequency specified during initialization. <br>
 * \attention
 * You must call this function before initializing the library. <br>
 * <br>
 * If the buffering time is too short, problems such as audio dropouts may occur. <br>
 */
void CRIAPI criAtom_SetAudioClientBufferDuration_WASAPI(REFERENCE_TIME ref_time);

/*EN
 * \brief Get the AudioClient
 * \ingroup ATOMLIB_WASAPI
 * \return IAudioClient	AudioClient
 * \par Description: 
 * Get the AudioClient created within the Atom library. 
 * \par Remarks: 
 * This function will return NULL if executed on a PC that does not
 * have a sound device. 
 * \par Note: 
 * You must initialize the library before calling this function. 
 */
IAudioClient * CRIAPI criAtom_GetAudioClient_WASAPI(void);

/*EN
 * \brief Check if the audio device is disabled 
 * \ingroup ATOMLIB_WASAPI
 * \return	CriBool	Has the device been disabled? (CRI_TRUE = Disabled, CRI_FALSE = Operating Normally)
 * \par Description: 
 * Returns whether or not the audio device has been disabled. 
 * \par Remarks: 
 * This function only returns CRI_TRUE when the sound device has been disabled while the application was running. <br>
 * This function will return CRI_FALSE if executed on a PC that does not have a sound device at all. <br>
 * (Use the ::criAtom_GetAudioClient_WASAPI function to check whether or not a sound device exists.) 
 * \sa criAtom_GetAudioClient_WASAPI
 */
CriBool CRIAPI criAtom_IsDeviceInvalidated_WASAPI(void);

/*EN
 * \brief Set sound device
 * \ingroup ATOMLIB_WASAPI
 * \param[in]	type		Sound renderer type
 * \param[in]	device_id	Device ID
 * \par Description: 
 * Link the sound renderer type to the sound device.<br>
 * <br>
 * If set the device ID for the sound renderer with this function,
 * all sounds specified by specifying the sound renderer will be output
 * from the sound device that matches the specified ID.
 * <br>
 * The following values can be specified for "type".<br>
 * 	- CRIATOM_SOUND_RENDERER_HW1
 * 	- CRIATOM_SOUND_RENDERER_HW2
 * 	- CRIATOM_SOUND_RENDERER_HW3
 * 	- CRIATOM_SOUND_RENDERER_HW4
 * 	.
 * If NULL or a character string of length 0 is specified for "device_id",
 * the link between the sound renderer and the device ID is canceled.
 * \par Remarks:
 * The ID of the sound device needs to be acquired with IMMDevice::GetId.<br>
 * If a sound device that matches the specified ID can not be found,
 * the sound that was played with the device specified is output from the default device.<br>
 * \attention
 * This function must be executed before library initialization.<br>
 */
void CRIAPI criAtom_SetDeviceId_WASAPI(CriAtomSoundRendererType type, LPCWSTR device_id);

/*EN
 * \brief Enumerate audio endpoints
 * \ingroup ATOMLIB_WASAPI
 * \param[in]	callback	Audio endpoint callback function
 * \param[in]	object		User Object
 * \return		CriSint32	Number of enumerated ACB handles
 * \par Description: 
 * Enumerate audio endpoints.<br>
 * <br>
 * When this function is executed, the callback function set in "call_back" is called up by the number of audio endpoints.<br>
 * An IMMDevice instance is passed as an argument to the callback function.<br>
 * \par Remarks:
 * The value set for "object" is passed as the argument of the callback function.<br>
 * For other arguments of the callback function, see the explanation of ::CriAtomAudioEndpointCbFunc_WASAPI .<br>
 * <br>
 * The return value is the number of enumerated audio endpoints (the number of times the registered callback function was called).<br>
 * If there is no audio endpoint, this function returns 0.<br>
 * If an error occurs, -1 is returned.<br>
 * \attention
 * IMMDevice instances MUST NOT be discarded within the callback function.<br>
 * \sa CriAtomAudioEndpointCbFunc_WASAPI
 */
CriSint32 CRIAPI criAtom_EnumAudioEndpoints_WASAPI(CriAtomAudioEndpointCbFunc_WASAPI callback, void *object);

/*EN
 * \brief Register device update notification
 * \ingroup ATOMLIB_WASAPI
 * \param[in]	callback	Device Update callback function
 * \param[in]	object		User Object
 * \par Description: 
 * Set up a callback to receive device update notifications. <br>
 * <br>
 * When this function is executed, when the device is updated, the callback function set with the first argument (callback) will be called. <br>
 * \par Remarks:
 * The value set for the second argument (object) is passed as the argument of the callback function. <br>
 * \sa CriAtomAudioEndpointCbFunc_WASAPI
 */
void CRIAPI criAtom_SetDeviceUpdateCallback_WASAPI(CriAtomDeviceUpdateCbFunc_WASAPI callback, void *object);

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*EN
 * \brief Calculate the size of the work buffer required to initialize the library
 * \ingroup ATOMLIB_WASAPI
 * \param[in]	config		Configuration structure for initialization
 * \return		CriSint32	Work buffer size
 * \par Description: 
 * This function retrieves the size of the work buffer needed to use the library. <br>
 * \par Remarks: 
 * The work buffer size needed by the library's initialization depends on the values of the parameters in
 * the ::CriAtomExConfig_WASAPI structure.<br>
 * The information passed in the config argument is only referenced within this function.<br>
 * Therefore the memory it uses can be released after executing the function.
 * \sa CriAtomExConfig_WASAPI, criAtomEx_Initialize_WASAPI
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSize_WASAPI(const CriAtomExConfig_WASAPI *config);

/*EN
 * \brief Library initialization
 * \ingroup ATOMLIB_WASAPI
 * \param[in]	config		Configuration structure for initialization
 * \param[in]	work		Work area
 * \param[in]	work_size	Work area size
 * \par Description: 
 * Initializes the library. <br>
 * In order to be able to use the features of the library, you must first call this function. <br>
 * (Once this function is called, the features of the library are available until the ::criAtomEx_Finalize_WASAPI function
 * is called.) <br>
 * <br>
 * To initialize the library, you must allocate the memory (work buffer)
 * used internally by the library. <br>
 * The size of the work buffer needed by the library depends on the values of the parameters in the configuration structure
 * used for initialization. <br>
 * Use the ::criAtomEx_CalculateWorkSize_WASAPI function to calculate
 * the size of the work buffer. <br>
 * \par Remarks: 
 * If an allocator has already been registered by using the ::criAtomEx_SetUserAllocator macro,
 * you do not need to specify a work buffer to this function. <br>
 * (By passing NULL for work and 0 for work_size, the amount of memory corresponding to the work buffer size
 * is dynamically allocated by the registered allocator.) 
 * <br>
 * The information passed in the config argument is only referenced within this function.<br>
 * Therefore the memory it uses can be released after executing the function.
 * \attention
 * This function internally calls: <br>
 * 	- ::criAtomEx_Initialize
 * 	- ::criAtomExAsr_Initialize
 * 	- ::criAtomExHcaMx_Initialize
 * 	.
 * Therefore, if you call this function, do not call the functions listed above. <br>
 * <br>
 * If you call this function, you must always call the ::criAtomEx_Finalize_WASAPI function later. <br>
 * Do call this function again before having called ::criAtomEx_Finalize_WASAPI. <br>
 * \sa CriAtomExConfig_WASAPI, criAtomEx_Finalize_WASAPI,
 * criAtomEx_SetUserAllocator, criAtomEx_CalculateWorkSize_WASAPI
 */
void CRIAPI criAtomEx_Initialize_WASAPI(
	const CriAtomExConfig_WASAPI *config, void *work, CriSint32 work_size);

/*EN
 * \brief Finalize the library
 * \ingroup ATOMLIB_WASAPI
 * \par Description: 
 * This function finalizes the library. <br>
 * \attention
 * This function internally calls: <br>
 * 	- ::criAtomEx_Finalize
 * 	- ::criAtomExAsr_Finalize
 * 	- ::criAtomExHcaMx_Finalize
 * 	.
 * Therefore, if you call this function, do not call the functions above. <br>
 * <br>
 * This function cannot be executed before the ::criAtomEx_Initialize_WASAPI function is called. <br>
 * \sa criAtomEx_Initialize_WASAPI
 */
void CRIAPI criAtomEx_Finalize_WASAPI(void);

#ifdef __cplusplus
}
#endif

/***************************************************************************
 *      For compatibility with older versions
 ***************************************************************************/
#define criAtom_ControlComInitialization_WASAPI(sw)

#endif	/* CRI_INCL_CRI_ATOM_WASAPI_H */

/* --- end of file --- */
