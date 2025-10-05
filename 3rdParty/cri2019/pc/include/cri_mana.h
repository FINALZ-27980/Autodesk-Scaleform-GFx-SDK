/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010-2019 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Mana (Sofdec2)
 * Module   : Library User's Header
 * File     : cri_mana.h
 * Date     : 2019-02-05
 * Version  : (see CRIMANA_VERSION)
 *
 ****************************************************************************/
/*!
 *	\file		cri_mana.h
 */
 
/* Prevention of redefinition */
#ifndef CRI_INCL_CRI_MANA_H
#define CRI_INCL_CRI_MANA_H

/***************************************************************************
 *      Include files
 ***************************************************************************/
#include <cri_xpt.h>
#include <cri_file_system.h>
#include <cri_atom_ex.h>

/***************************************************************************
 *      Macro Constants
 ***************************************************************************/
/* Version Number */
#define CRIMANA_VERSION				(0x02180000)
#define CRIMANA_VER_NUM				"2.18.00"
#define CRIMANA_VER_NAME			"CRI Mana"
#define CRIMANA_VER_OPTION


/*EN
 * \brief Maximum number of video streams in a movie file
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * 
 * \sa CriManaMovieInfo, criManaPlayer_GetMovieInfo
 */
#define CRIMANA_MAX_VIDEO_NUM			(1)

/*EN
 * \brief	Maximum number of audio streams in a movie file
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * 
 * \sa CriManaMovieInfo, criManaPlayer_GetMovieInfo
 */
#define CRIMANA_MAX_AUDIO_NUM			(32)

/*EN
 * \brief	Maximum number of alpha streams in a movie file
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * 
 * \sa CriManaMovieInfo, criManaPlayer_GetMovieInfo
 */
#define CRIMANA_MAX_ALPHA_NUM			(1)

/*EN
 * \brief	Specified value for turning off audio playback
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * 
 * \sa criManaPlayer_SetAudioTrack
 */
#define CRIMANA_AUDIO_TRACK_OFF			(-1)

/*EN
 * \brief	Default value for audio tracks
 * \ingroup MDL_MANALIB_PLAYER
 * \sa criManaPlayer_SetAudioTrack
 */
#define CRIMANA_AUDIO_TRACK_AUTO	(100)

/*EN
 * \brief   Maximum number of subtitle channels
 * \ingroup MDL_MANALIB_PLAYER
 * \sa CRIMANA_MAX_VIDEO_NUM, CRIMANA_MAX_AUDIO_NUM
 */
#define	CRIMANA_MAX_SUBTITLE_NUM	(16)

/*EN
 * \brief	Specified value for turning off subtitle playback
 * \ingroup 
 * \sa criManaPlayer_SetSubtitleChannel
 */
#define CRIMANA_SUBTITLE_CHANNEL_OFF	(-1)

/*EN
 * \brief	Maximum file name length that can be specified in the Mana player
 * \ingroup MDL_MANALIB_PLAYER
 * \sa criManaPlayer_SetFile
 */
#define CRIMANA_MAX_FILE_NAME			(256)

/* Number of platform-specific frame information items */
#define CRIMANA_FRAME_DETAILS_NUM		(2)

/***************************************************************************
 *      Macro Functions
 ***************************************************************************/
/* Replacement macro for retaining compatibility */
#define criManaPlayer_CalculateHanldeWorkSize criManaPlayer_CalculateHandleWorkSize

/*==========================================================================
 *      CRI Mana API
 *=========================================================================*/
/*EN
 * \brief Set default values for the library initialization config structure
 * \ingroup MDL_MANALIB_GLOBAL
 * \param[out] p_config	Pointer to the initialization config structure
 * \par Description: 
 * Sets the default values for the config structure ( ::CriManaLibConfig )
 * that will be set to the ::criMana_Initialize function. <br>
 * \par Notes: 
 * Platform specific functions may exist on each platform. See the reference for each platform for more information. 
 * \sa
 * CriManaLibConfig
 */
#define criMana_SetDefaultLibConfig(p_config)	\
{\
	(p_config)->max_decoder_handles	= 4;\
	(p_config)->thread_model		= CRIMANA_THREAD_MODEL_MULTI;\
	(p_config)->version				= CRIMANA_VERSION;\
}

/*==========================================================================
 *      CRI Mana Player API
 *=========================================================================*/
/*EN
 * \brief Set default values for the player creation config structure
 * \ingroup MDL_MANALIB_PLAYER
 * \param[out] p_config	Pointer to the player creation config structure
 * \par Description: 
 * Sets the default values for the config structure ( ::CriManaPlayerConfig ) 
 * that will be set to the ::criManaPlayer_CreateWithConfig function. <br>
 * \sa
 * criManaPlayer_CreateWithConfig
 */
#define criManaPlayer_SetDefaultHandleConfig(p_config)	\
{\
	(p_config)->readbuf_size_byte	= 0;\
	(p_config)->use_atomex_player	= CRI_FALSE;\
}

/***************************************************************************
 *      Enum Declarations
 ***************************************************************************/
/*EN
 * \brief Player status
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * This value shows the status of the Mana player playback. 
 * You can get the handle status anytime with the ::criManaPlayer_GetStatus function. <br>
 * The handle will be in CRIMANAPLAYER_STOP status directly after creation. <br>
 * <br>
* The handle status will transition in order from CRIMANAPLAYER_STATUS_STOP to CRIMANAPLAYER_STATUS_PLAYEND. <br>
 * The application will not necessarily need to check the status of everything when playing a movie. <br>
 * As long as it at least checks CRIMANAPLAYER_STATUS_STOP, CRIMANAPLAYER_STATUS_PLAYING, CRIMANAPLAYER_STATUS_PLAYEND, and CRIMANAPLAYER_STATUS_ERROR,
 * then the movie can be played back. <br>
 * <br>
* If the movie resolution has already been determined after the Mana player has been created,
 * then the application can directly call the ::criManaPlayer_Start function. In this situation, the handle status will automatically transition to 
 * CRIMANAPLAYER_STATUS_PLAYEND. <br>
 * <br>
* When the ::criManaPlayer_DecodeHeader function is first called, the handle status will become
 * CRIMANAPLAYER_STATUS_WAIT_PREP after header analysis is complete. The application will then wait until the ::criManaPlayer_Prepare function
 * or the ::criManaPlayer_Start function can be called from the application. <br>
 * <br>
* You can get movie information using the ::criManaPlayer_GetMovieInfo function once it is in the CRIMANAPLAYER_STATUS_WAIT_PREP status. <br>
 * When calling the ::criManaPlayer_Prepare function, once header analysis and data buffering is complete
 * the handle status will become CRIMANAPLAYER_STATUS_READY and it will wait until the ::criManaPlayer_Start function
 * can be called from the application. You can use this to adjust the start playback timing. <br>
 * <br>
 * The status will automatically become CRIMANAPLAYER_STATUS_PLAYEND once playback is finished. <br>
 * <br>
* When the ::criManaPlayer_Stop function is called, it will become the CRIMANAPLAYER_STATUS_STOP status
 * once the decoder has stopped.  It will not always stop directly after the ::criManaPlayer_Stop function is finished. <br>
 * <br>
* If a problem such as insufficient memory or a data error occurs, it will become the CRIMANAPLAYER_STATUS_ERROR status. <br>
 * If it has become CRIMANAPLAYER_STATUS_ERROR status, call the ::criManaPlayer_Stop function and let the
 * handle status transition to CRIMANAPLAYER_STATUS_STOP. <br>
 * <br>
 * The ::criManaPlayer_Destroy function can be called only when in the CRIMANAPLAYER_STATUS_STOP or
 * CRIMANAPLAYER_STATUS_PLAYEND status. 
 * 
 * \sa criManaPlayer_GetStatus
 */
typedef enum {
	CRIMANAPLAYER_STATUS_STOP		= 0,		/*EN< Stopped					*/
	CRIMANAPLAYER_STATUS_DECHDR		= 1,		/*EN< Header analysis				*/
	CRIMANAPLAYER_STATUS_WAIT_PREP	= 2,		/*EN< Buffering start or stop	*/
	CRIMANAPLAYER_STATUS_PREP		= 3,		/*EN< Preparing for playback				*/
	CRIMANAPLAYER_STATUS_READY		= 4,		/*EN< Waiting for playback				*/
	CRIMANAPLAYER_STATUS_PLAYING	= 5,		/*EN< Playing					*/
	CRIMANAPLAYER_STATUS_PLAYEND	= 6,		/*EN< Playback is finished					*/
	CRIMANAPLAYER_STATUS_ERROR		= 7,		/*EN< Error					*/

	CRIMANAPLAYER_STATUS_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriManaPlayerStatus;

/*EN
 * \brief Timer type
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * The type of reference timer (master timer) that the Mana synchronizes as internal time. 
 * 
 * \sa criManaPlayer_SetMasterTimerType, criManaPlayer_GetMasterTimerType
 */
typedef enum {
	CRIMANAPLAYER_TIMER_NONE	=0,		/*EN< It does not synchronize video frame times. 	                   */
									/*    You can immediately retrieve a frame that has been decoded.*/ 
	CRIMANAPLAYER_TIMER_SYSTEM	=1,		/*EN< The video frame is synchronized to the system time used within the */
	                                /*    Mana player.                                                 */
	CRIMANAPLAYER_TIMER_AUDIO	=2,		/*EN< The video frame is synchronized to the audio time played by the main audio track.*/
 
	                                /*    If there is no audio in the movie data, then the video will synchronize to the system time.  */
	CRIMANAPLAYER_TIMER_USER	=3,		/*EN< Unsupported. Synchronizes to the user's own timer specified by the application.*/ 
	CRIMANAPLAYER_TIMER_MANUAL	=4,		/*EN< Manual type: This mode sets the unit of time advancement from the application */
									/* and advances time.*/ 

	CRIMANAPLAYER_TIMER_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriManaTimerType;

/*EN
 * \brief Thread model
 * \ingroup MDL_MANALIB_GLOBAL
 * \par Description: 
 * Displays what kind of thread model the CRI Mana library operates on. 
 * 
 * \sa CriManaLibConfig, criMana_CalculateLibWorkSize, criMana_Initialize
 */
typedef enum {
	CRIMANA_THREAD_MODEL_MULTI = 0,		/*EN< Multi-thread operation model.  */
									/*    The library creates internal threads for multi-thread operation.  */
	CRIMANA_THREAD_MODEL_SINGLE = 1,	/*EN< Single thread operation model.  */
									/*    The library does not create internal threads.  */
	
	/* Keep enum 4bytes */
	CRIMANA_THREAD_MODEL_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriManaThreadModel;

/*EN
 * \brief Video codec types
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Types of video codecs that can be included in movies that are played back. 
 * Only Sofdec.Prime (previously the Sofdec codec) is currently supported. 
 * 
 * \sa CriManaVideoInfo, CriManaMovieInfo, criManaPlayer_GetMovieInfo
 */
typedef enum {
	CRIMANA_VIDEO_CODEC_UNKNOWN = 0,			/*EN< Unknown */
	CRIMANA_VIDEO_CODEC_SOFDEC_PRIME = 1,		/*EN< Sofdec.Prime */
	CRIMANA_VIDEO_CODEC_H264 = 5,				/*EN< H.264/AVC     */
	CRIMANA_VIDEO_CODEC_VP9 = 9,				/*EN< VP9 */

	/* Keep enum 4bytes */
	CRIMANA_VIDEO_CODEC_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriManaVideoCodecType;

/*EN
 * \brief Audio codec types
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Types of audio codecs that can be included in movies that are played back. 
 * Only the ADX codec is currently supported. 
 * 
 * \sa CriManaAudioInfo, CriManaMovieInfo, criManaPlayer_GetMovieInfo
 */
typedef enum {
	CRIMANA_AUDIO_CODEC_UNKNOWN = 0,	/*EN< Unknown */
	CRIMANA_AUDIO_CODEC_ADX = 2,		/*EN< Advanced ADX */
	CRIMANA_AUDIO_CODEC_HCA = 4,		/*EN< HCA          */

	/* Keep enum 4bytes */
	CRIMANA_AUDIO_CODEC_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriManaAudioCodecType;

/*EN
 * \brief Alpha movie composition mode
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * 
 * \sa CriManaPlaybackAlphaParams, CriManaAlphaInfo, CriManaFrameInfo, 
 * criManaPlayer_IsFrameOnTime, criManaPlayer_ReferFrame, criManaPlayer_DiscardFrame
 * criManaPlayer_CopyFrameToBufferARGB32, criManaPlayer_CopyFrameToBuffersYUV
 */
typedef enum {
	CRIMANA_COMPO_OPAQ		 = 0,	/*EN< Opaque, no alpha information							*/
	CRIMANA_COMPO_ALPHFULL	 = 1,	/*EN< Full Alpha composition (alpha data is 8 bit)				*/
	CRIMANA_COMPO_ALPH3STEP	 = 2,	/*EN< 3  alpha											*/
	CRIMANA_COMPO_ALPH32BIT	 = 3,	/*EN< Full Alpha, (color and alpha data is 32 bit)		*/
	CRIMANA_COMPO_ALPH1BIT	 = 4,	/*EN< Full Alpha, (color and alpha data is 32 bit, a value is 2)	*/
	CRIMANA_COMPO_ALPH2BIT	 = 5,	/*EN< Full Alpha, (color and alpha data is 32 bit, a value is 4)	*/
	CRIMANA_COMPO_ALPH3BIT	 = 6,	/*EN< Full Alpha, (color and alpha data is 32 bit, a value is 8)	*/
	CRIMANA_COMPO_ALPH4BIT	 = 7,	/*EN< Full Alpha, (color and alpha data is 32 bit, a value is 16)	*/

	/* Keep enum 4bytes */
	CRIMANA_COMPO_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriManaAlphaType;

/*EN
 * \brief Flags used by meta data [currently not supported]
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * These flags control what class of meta data you want to use. 
 *Currently control for each type of flag is not supported. When using seek play back or Cuepoints,
 * specify the CRIMANA_META_FLAG_ALL. 
 * 
 * \sa criManaPlayer_SetMetaDataWorkAllocator
 */
typedef enum {
	CRIMANA_META_FLAG_NONE	= 0x0000,	/*EN< Do not use meta data */
	CRIMANA_META_FLAG_CUE	= 0x0001,	/*EN< Unsupported */
	CRIMANA_META_FLAG_SEEK	= 0x0002,	/*EN< Unsupported */
	CRIMANA_META_FLAG_ALL	= CRIMANA_META_FLAG_CUE | CRIMANA_META_FLAG_SEEK,	/*EN< Use all meta data formats */

	/* Keep enum 4bytes */
	CRIMANA_META_FLAG_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriManaMetaFlag;

/*EN
 * \brief ReferFrame frame reference results (debug information)
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Displays reference results for decoded video frames. 
 * Use these parameters as references when debugging. 
 *
 * \sa CriManaFrameInfo
 * criManaPlayer_IsFrameOnTime, criManaPlayer_ReferFrame, criManaPlayer_DiscardFrame, 
 * criManaPlayer_CopyFrameToBufferARGB32, criManaPlayer_CopyFrameToBuffersYUV
 */
typedef enum {
	CRIMANA_REFER_RESULT_OK				= 0,	/*EN< Successful frame reference */
	CRIMANA_REFER_RESULT_SHORT_INPUT	= 1,	/*EN< Insufficient data in input buffer */
	CRIMANA_REFER_RESULT_SHORT_CPUTIME	= 2,	/*EN< Insufficient CPU time for decoding  */
	CRIMANA_REFER_RESULT_NO_MORE_KEEP   = 3,	/*EN< There are no frames that can be kept */

	/* Keep enum 4bytes */
	CRIMANA_REFER_RESULT_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriManaReferFrameResult;


/*EN
 * \brief Color conversion types
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * 
 * \sa CriManaVideoInfo,CriManaAlphaInfo,CriManaFrameInfo
 */
typedef enum {
	CRIMANA_COLORSPACE_CONVERSION_TYPE_ITU_R_BT601_LIMITED = 0,
	CRIMANA_COLORSPACE_CONVERSION_TYPE_ITU_R_BT601_FULLRANGE = 1,

	/* Keep enum 4bytes */
	CRIMANA_COLORSPACE_CONVERSION_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriManaColorSpaceConversionType;

/*EN
 * \brief Decoder operation mode
 * \ingroup MDL_MANALIB_GLOBAL
 * \par Description: 
 * Displays the decoder operation mode
 *
 * \sa criManaPlayer_SetDecodeMode
 */
typedef enum {
	/*EN
	 *	\brief Normal decoding mode
	 *	\par Description: 
	 *  Executes normal decoding. <br>
	 *  Default values for the Mana library and Mana player.
	 */
	CRIMANA_DECODE_MODE_NORMAL	= 0,		

	/*EN
	 *	\brief Forced B picture skip mode
	 *	\par Description: 
	 *  Decoding will not be executed on B pictures
	 *  if they are included in the video stream of the movie data being played. <br>
	 *  Specify this operation mode if you want to decrease the load during movie play back. 
	 *
	 *  \par Notes: 
	 *  Only the Sofdec.Prime codec is supported.
	 */
	CRIMANA_DECODE_MODE_B_SKIP	= 1,

	CRIMANA_DECODE_MODE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF

} CriManaDecodeMode;

/* CriManaPlayerMovieEventSyncMode */
/*EN
 * \brief Sync mode for movie events (cue points, subtitles)
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 *  Sync mode for movie events.
 * 
 * \sa criManaPlayer_SetMovieEventSyncMode
 */
typedef enum {
	/* CriManaPlayerMovieEventSyncMode.CRIMANAPLAYER_EVENT_SYNC_FRAME_TIME */
	/*EN
	 * Movie events are synchronized to the frame time (getting video frame).
	 */
	CRIMANAPLAYER_EVENT_SYNC_FRAME_TIME		= 0,

	/* CriManaPlayerMovieEventSyncMode.CRIMANAPLAYER_EVENT_SYNC_PLAYBACK_TIME */
	/*EN
	 * Movie events are synchronized to the playback time (playback time based on timer type).
	 */
	CRIMANAPLAYER_EVENT_SYNC_PLAYBACK_TIME	= 1,

	CRIMANAPLAYER_EVENT_SYNC_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriManaPlayerMovieEventSyncMode;

/***************************************************************************
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI Mana API
 *=========================================================================*/
/*EN
 * \brief Mana library initialization parameters
 * \ingroup MDL_MANALIB_GLOBAL
 * \par Description: 
 * Structure for specifying the CRI Mana library operation specifications. 
 * \par Notes: 
 * Each platform may have specific initialization parameters. See the reference for each platform for more information. 
 * \sa criMana_CalculateLibWorkSize, criMana_Initialize
 */
typedef struct {
	CriUint32			max_decoder_handles;	/*EN< Max number of decoder handles consumed. Two handle resources are consumed for alpha movie playback.*/ 
	CriManaThreadModel	thread_model;			/*EN< Thread model */
	CriUint32			version;				/*EN< Header version number */
} CriManaLibConfig;

/*EN
 * \brief Event point information
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Individual timing information embedded in movie data using the Cuepoint function. 
 * \sa criManaPlayer_GetCuePointInfo, CriManaCuePointInfo
 */
typedef struct {
	CriChar8		*cue_name;			/*EN< Event point name. Character codes follow the Cuepoint information text.  */
	CriUint32		size_name;			/*EN< Event point name data size */
	CriUint64		time;				/*EN< Timer count */
	CriUint64		tunit;				/*EN< Timer count value per second. Time is in second units because count / unit.  */
	CriSint32		type;				/*EN< Event point type */
	CriChar8		*param_string;		/*EN< User parameter string. Character codes follow the Cuepoint information text.  */
	CriUint32		size_param;			/*EN< User parameter string data size*/
	CriUint32		cnt_callback;		/*EN< Cuepoint callback call counter */
} CriManaEventPoint;

/*EN
 * \brief Cuepoint information
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Cuepoint information is the number and list of event points. 
 * \sa criManaPlayer_GetCuePointInfo, CriManaCuePointInfo
 */
typedef struct {
	CriUint32			num_eventpoint;		/*EN< Number of event points */
	CriManaEventPoint		*eventtable;	/*EN< List of event points */
} CriManaCuePointInfo;

/*==========================================================================
 *      CRI Mana Player API
 *=========================================================================*/
/*EN
 * \brief Configuration structure for player creation
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * This is a data type for specifying operation specifications when the Mana player is used for movie playback.<br>
 * Specifies the ::criManaPlayer_CreateWithConfig function argument. <br>
 * <br>
* The player that was created will allocate only as many internal resources as are necessary according to the settings
 * specified by the structure during handle creation. <br>
 * <br>
* When the config structure is not used in handle creation, internal resources are allocated
 * as playback work after playback begins. Only use this structure when the specs of the
 * movie to be played back have been determined beforehand. 
 * \sa criManaPlayer_CreateWithConfig
 */
typedef struct {
	/*EN
		\brief Input buffer size (unit: byte)
		\par Description: 
		You can specify the size of the input buffer allocated internally by the Mana player for playback. <br>
		<br>
		Specifying anything but zero will create an input buffer with a size specified during handle creation.<br>
		If you specify zero, an input buffer will not be created during handle creation but rather allocated when playback work is allocated. <br>
		\par Calculation method: 
		- Input buffer size = Max bit rate (bps) of the movie to be played back / 8 * buffering time (secs)<br>
		  Ex.) When playing a movie with a max 2Mbps: 2*1000*1000 / 8 * 1.0f = 250000<br>
		\par Caution: 
		Making the input buffer size too small may delay playback. Allocate more than one second,
		even if the buffering time is small. <br>
		We recommend making the size a little larger to match this number during multi-streaming playback.
	*/
	CriUint32	readbuf_size_byte;		
	/*EN
	    \brief Flag to use ::criAtomExPlayer for sound playback
		\par Description:
		By specifying CRI_TRUE for this flag, ::criAtomExPlayer is used for player's sound playback.
		It is possible to obtain this criAtomExPlayer handle with ::criManaPlayer_GetAtomExPlayer function.
	*/
	CriBool use_atomex_player;	
} CriManaPlayerConfig;

struct CriManaPlayerTag;
typedef struct CriManaPlayerTag CriManaPlayerObj;
/*EN
 * \brief Player handle
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * CriManaPlayerHn is a handle to operate the player that was created for video playback. <br>
 * When you create a player for video playback using the ::criManaPlayer_Create function
 * the function will return this "Mana player handle" for player operation. 
 * <br>
 * Operations for the player, such as setting data, start playback, and getting the status
 * are all executed through the Mana player handle. <br>
 * \sa criManaPlayer_Create
 */
typedef CriManaPlayerObj *CriManaPlayerHn;

/*==========================================================================
 *      Structure for playback work size adjustment
 *=========================================================================*/

/*EN
 * \brief Basic parameters for playback work
 * \ingroup MDL_MANALIB_GLOBAL
 * \par Description: 
 * These are reference parameters when allocating the basic playback work area necessary for movie playback. 
 *
 * \sa CriManaPlaybackBasicWorkConfig, criManaPlayer_GetPlaybackWorkParam, 
 * criManaPlayer_CalculatePlaybackWorkSize, criManaPlayer_SetPlaybackWork
 */
typedef struct {
	CriSint32 readbuf_size_byte;	/*EN< Input buffer size (unit: byte) */
	CriUint32 max_audio_tracks;		/*EN< Number of audio tracks that can be contained in the movie */
} CriManaPlaybackCommonParams;

/*EN
 * \brief Video-related playback parameters
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Displays the parameters necessary for video playback. 
 * The work area necessary for video playback is calculated based on these parameters, and added to the
 * final work size. 
 *
 * \sa CriManaPlaybackBasicWorkConfig, criManaPlayer_GetPlaybackWorkParam, 
 * criManaPlayer_CalculatePlaybackWorkSize, criManaPlayer_SetPlaybackWork
 */
typedef struct {
	CriBool		video_flag;				/*EN< [Not used] Flags used by videos */
	CriSint32	max_width;				/*EN< Max movie width (multiple of 8) */
	CriSint32	max_height;				/*EN< Max movie height (multiple of 8) */
	CriSint32	num_frame_pools;		/*EN< Number of frame pools */
	CriManaVideoCodecType codec_type;	/*EN< Type of codec (Assumed to be Sofdec.Prime when CRIMANA_VIDEO_CODEC_UNKNOWN is specified) */ 
	CriSint32	capacity_of_picsize;	/*EN< Upper picture size limit */
	CriSint32	framerate_n;				/*EN< Frame rate (numerator) in rational number format framerate [x1000] = framerate_n / framerate_d */
	CriSint32	framerate_d;				/*EN< Frame rate (denominator) in rational number format framerate [x1000] = framerate_n / framerate_d */
	// CriManaVideoLevel level;			/* Not used */
} CriManaPlaybackVideoParams;

/*EN
 * \brief Audio-related playback parameters
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Displays the parameters necessary for audio playback. 
 * The work area necessary for audio playback is calculated based on these parameters, and added to the
 * final work size. 
 *
 * \sa CriManaPlaybackBasicWorkConfig, criManaPlayer_GetPlaybackWorkParam, 
 * criManaPlayer_CalculatePlaybackWorkSize, criManaPlayer_SetPlaybackWork
 */
typedef struct {
	CriBool		audio_flag;				/*EN< Flags used by audio */
	CriUint32	sampling_rate;			/*EN< Sampling frequency (unit: Hz)*/
	CriUint32	num_channels;			/*EN< Number of channels */
	CriSint32	output_buffer_samples;	/*EN< Specify output buffer size (unit: number of samples) */
	CriManaAudioCodecType codec_type;	/*EN< Codec type (Assumed to be ADX when CRIMANA_AUDIO_CODEC_UNKNOWN is specified) */ 
} CriManaPlaybackAudioParams;

/*EN
 * \brief Subtitle-related playback parameters
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Displays the parameters necessary for subtitle playback. 
 * The work area necessary for subtitle playback is calculated based on these parameters, and added to the
 * final work size. 
 * 
 * \sa CriManaPlaybackBasicWorkConfig, criManaPlayer_GetPlaybackWorkParam, 
 * criManaPlayer_CalculatePlaybackWorkSize, criManaPlayer_SetPlaybackWork
 */
typedef struct {
	CriBool		subtitle_flag;			/*EN< Flags used by subtitles */
	CriSint32	max_datasize;			/*EN< Max subtitle data size */
} CriManaPlaybackSubtitleParams;

/*EN
 * \brief Alpha channel parameters
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Displays the parameters necessary for decoding alpha channels. 
 * The work area necessary for alpha channel decoding is calculated based on these parameters, and added to the
 * final work size. 
 *
 * \sa CriManaPlaybackBasicWorkConfig, criManaPlayer_GetPlaybackWorkParam, 
 * criManaPlayer_CalculatePlaybackWorkSize, criManaPlayer_SetPlaybackWork
 */
typedef struct {
	CriBool				alpha_flag;				/*EN< Flags used by alpha channels */
	CriManaAlphaType	alpha_type;				/*EN< Alpha movie composition mode */
	CriSint32			max_width;				/*EN< Max movie width (multiple of 8) */
	CriSint32			max_height;				/*EN< Max movie height (multiple of 8) */
	CriManaVideoCodecType codec_type;			/*EN<Codec type (Assumed to be Sofdec.Prime when CRIMANA_VIDEO_CODEC_UNKNOWN is specified) */ 
	CriSint32			capacity_of_picsize;	/*EN< Upper picture size limit */
} CriManaPlaybackAlphaParams;

/*EN
 * \brief Playback work parameter structure (basic) 
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Playback parameters necessary for movie playback. 
 * Pass into the ::criManaPlayer_SetPlaybackWork function together with the work area as an argument. 
 *
 * \sa CriManaPlaybackBasicWorkConfig, criManaPlayer_GetPlaybackWorkParam, 
 * criManaPlayer_CalculatePlaybackWorkSize, criManaPlayer_SetPlaybackWork
 */
typedef struct {
	CriManaPlaybackCommonParams common_params;		/*EN< Basic parameters for adjusting buffer size */
	CriManaPlaybackVideoParams  video_params;		/*EN< Video playback work parameters */
	CriManaPlaybackAudioParams  main_audio_params;	/*EN< Main audio playback work parameters */
	CriManaPlaybackSubtitleParams subtitle_params;	/*EN< Subtitle playback work parameters */
} CriManaPlaybackBasicWorkConfig;


/*EN
 * \brief Playback work parameter structure (extended)
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Extended control parameters for adjusting the work buffer size necessary for special playback. 
 * Pass this parameter structure together with the
 * CriManaPlaybackBasicWorkConfig structure into the ::criManaPlayer_SetPlaybackWork function during
 * subaudio and alpha movie playback. 
 *
 * \sa criManaPlayer_GetPlaybackWorkParam, criManaPlayer_CalculatePlaybackWorkSize, 
 * criManaPlayer_SetPlaybackWork
 */
typedef struct {
	CriManaPlaybackAudioParams      sub_audio_params;	/*EN< SubAudio */
	CriManaPlaybackAudioParams      extra_audio_params;	/*EN< ExtraAudio */
	CriManaPlaybackAlphaParams      alpha_params;		/*EN< Alpha */
	//CriManaPlaybackZmovieParams	zmovie_params;		/* Z Movie */
	//CriManaPlaybackStereo3DParams stereo3d_params;	/* Stereo 3D */
} CriManaPlaybackExWorkConfig;


/*==========================================================================
 *      Detailed movie file information
 *=========================================================================*/

/*EN 
 * \brief Audio parameters
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Analysis information on the audio data that can be included in a movie file. 
 *
 * \sa CriManaMovieInfo, criManaPlayer_GetMovieInfo
 */
typedef struct {
	CriManaAudioCodecType	codec_type;				/*EN< Codec type */
	CriUint32				sampling_rate;			/*EN< Sampling frequency */
	CriUint32				num_channels;			/*EN< Number of audio channels */
	CriUint32				total_samples;			/*EN< Total number of samples */
	CriUint32				output_buffer_samples;	/*EN< Number of sound output buffer samples */
	CriUint8				ambisonics;				/*EN< Ambisonics mode */
} CriManaAudioInfo;

/*EN 
 * \brief Video parameters
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Analysis information on the video data that can be included in a movie file. 
 * 
 * \sa CriManaMovieInfo, criManaPlayer_GetMovieInfo
 */
typedef struct {
	CriUint32				width;				/*EN< Max movie width (multiple of 8) */
	CriUint32				height;				/*EN< Max movie height (multiple of 8) */
	CriUint32				disp_width;			/*EN< Number of horizontal pixels (from the left side) in the image that you want to display */
	CriUint32				disp_height;		/*EN< Number of vertical pixels (from the top) in the image that you want to display */
	CriUint32				framerate;			/*EN< Frame rate [x1000] */
	CriUint32				framerate_n;		/*EN< Frame rate (numerator) in a rational number format framerate [x1000] = framerate_n / framerate_d */
	CriUint32				framerate_d;		/*EN< Frame rate (denominator) in a rational number format framerate [x1000] = framerate_n / framerate_d */
	CriUint32				total_frames;		/*EN< Total number of frames */
	CriUint32				material_width;		/*EN< Number of horizontal pixels in the video footage before encoding */
	CriUint32				material_height;	/*EN< Number of vertical pixels in the video footage before encoding */
	CriManaVideoCodecType	codec_type;			/*EN< Video codec type */
	CriManaColorSpaceConversionType color_conv;	/*EN< Color conversion type */
	CriSint32				max_picture_size;	/*EN< Max picture size (when invalid -1) */
	CriSint32				average_bitrate;	/*EN< Average bit rate */
} CriManaVideoInfo;

/*EN 
 * \brief Alpha parameters
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Analysis information on the alpha channel data that can be included in a movie file. 
 * 
 * \sa CriManaMovieInfo, criManaPlayer_GetMovieInfo
 */
typedef struct {
	CriUint32			width;				/*EN< Max alpha frame width */
	CriUint32			height;				/*EN< Max alpha movie height */
	CriUint32			disp_width;			/*EN< Actual alpha movie effective width */
	CriUint32			disp_height;		/*EN< Actual alpha movie effective height */
	CriUint32			framerate;			/*EN< Alpha frame rate [x1000] */
	CriUint32			framerate_n;		/*EN< Frame rate (numerator) in a rational number format framerate [x1000] = framerate_n / framerate_d */
	CriUint32			framerate_d;		/*EN< Frame rate (denominator) in a rational number format framerate [x1000] = framerate_n / framerate_d */
	CriUint32			total_frames;		/*EN< Total number of frames */
	CriManaAlphaType	alpha_type;			/*EN< Alpha movie composition mode */
	CriManaVideoCodecType	codec_type;		/*EN< Codec type */
	CriManaColorSpaceConversionType color_conv;	/*EN< Color conversion type */
	CriSint32			max_picture_size;	/*EN< Max picture size */
	CriSint32			average_bitrate;	/*EN< Average bit rate */
} CriManaAlphaInfo;

/*EN
 * \brief Movie information structure
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Movie file information that can be gotten after header analysis. 
 *
 * \sa criManaPlayer_GetMovieInfo
 */
typedef struct {
	/* Stream */
	CriUint32			is_playable;		/*EN< Playable flag (1:  Playable, 0:  Not playable) */
	CriUint32			average_bitrate;	/*EN< Average bit rate (total for video and audio) */
	CriUint32			max_chunk_size;		/*EN< Maximum USF chunk size */
	CriUint32			min_buffer_size;	/*EN< Minimum required load buffer size. <br> Audio and video total. */
	/* Video */
	CriUint32			num_video_streams;					/*EN< Number of video streams. Currently fixed to 1.*/
	CriManaVideoInfo	video_prm[CRIMANA_MAX_VIDEO_NUM];	/*EN< Video parameters */
	/* Audio */
	CriUint32			num_audio_streams;					/*EN< Number of audio streams */
	CriManaAudioInfo	audio_prm[CRIMANA_MAX_AUDIO_NUM];	/*EN< Audio parameters */
	/* Subtitle */
	CriUint32			num_subtitle_channels;	/*EN< Number of subtitle channels */
	CriUint32			max_subtitle_size;		/*EN< Maximum subtitle data size*/
	/* Composite mode */
	CriUint32			num_alpha_streams;					/*EN< Number of alpha streams. Currently fixed to 1. */
	CriManaAlphaInfo	alpha_prm[CRIMANA_MAX_ALPHA_NUM];	/*EN< Alpha parameters */
	/* Seek */
	CriBool				seekinfo_flag;		/*EN< Seek information flags */
	/* Others */
	CriUint32			format_ver;			/*EN< Format version */
} CriManaMovieInfo;

/*==========================================================================
 *      Video frame information structure
 *=========================================================================*/
/*EN
 * \brief Image information
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Image information (plane information) of which video frame is referenced by frame retrieval API<br>
 * Composed of a combination of Y, U, V, and A as a member array of the CriManaFrameInfo structure. <br>
 * This image information is used by the CPU with criManaPlayer_CopyFrameToBufferARGB32 or the like<br>
 * for frame conversion (color conversion). Depending on the platform, this image information will<br>
 * be handled directly and the frames will be converted efficiently by hardware, pixel shaders,<br>
 * or the like. 
 *
 * \sa CriManaFrameInfo, criManaPlayer_CopyFrameToBufferARGB32
 */
typedef struct {
	CriUint8	*imageptr;	/*EN< Image information buffer pointer */
	CriUint32	bufsize;	/*EN< Image information buffer size [Byte] */
	CriUint32	line_pitch;	/*EN< Image information line pitch [Byte] */
	CriUint32	line_size;	/*EN< Image information line size [Byte] */
	CriUint32	num_lines;	/*EN< Image information number of lines */
} CriManaImageBufferInfo;

/*EN
 * \brief Video frame information
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Video frame information referenced by API that get frames. 
 * -1 is entered in frame_no when it fails to get the frame information. 
 *
 * \sa criManaPlayer_IsFrameOnTime, criManaPlayer_ReferFrame, criManaPlayer_DiscardFrame, 
 * criManaPlayer_CopyFrameToBufferARGB32, criManaPlayer_CopyFrameToBuffersYUV
 */
typedef struct {
	CriSint32						frame_no;				/*EN< Frame identification number (serial number starting from 0) */
	CriSint32						frame_no_per_file;		/*EN< Frame identification number (specific identification number for the movie file) */
	CriUint32						width;					/*EN< Movie width [pixel] (multiple of 8) */
	CriUint32						height;					/*EN< Movie height [pixel] (multiple of 8) */
	CriUint32						disp_width;				/*EN< Number of horizontal pixels (from the left side) in the image that you want to display */
	CriUint32						disp_height;			/*EN< Number of vertical pixels (from the top) of the image that you want to display */
	CriUint32						framerate;				/*EN< Value 1000 times the frame rate */
	CriUint32						framerate_n;			/*EN< Frame rate (numerator) in a rational number format framerate [x1000] = framerate_n / framerate_d */
	CriUint32						framerate_d;			/*EN< Frame rate (denominator) in a rational number format framerate [x1000] = framerate_n / framerate_d */
	CriUint32						total_frames_per_file;	/*EN< Total number of frames per file */
	CriUint64						time;					/*EN< Time. Displays seconds in time / tunit. Continually adds during loop playback and concatenated playback.  */
	CriUint64						time_per_file;			/*EN< [Unsupported] Playback time in file */
	CriUint64						tunit;					/*EN<Time unit */
	CriUint32						cnt_concatenated_movie;	/*EN< Number of movie concatenations */
	CriSint32						num_images;				/*EN< Number of decoded frame buffer images */
	CriManaImageBufferInfo			image_info[4];			/*EN< Image information (plain information) for Y, U, V, and A are stored as arrays when the frame is grabbed. */
	CriBool							csc_flag;				/*EN< Variable during testing. Do not access.  */
	CriManaAlphaType				alpha_type;				/*EN< Alpha composition mode*/
	CriManaReferFrameResult			ref_result;				/*EN< Frame reference results  */
	void							*details_ptr[CRIMANA_FRAME_DETAILS_NUM];	/*EN< Pointer to detailed information (for specific applications) */
	CriManaColorSpaceConversionType	color_conv;				/*EN< Color conversion type */
	CriUint32						cnt_skipped_frames;		/*EN< Number of frames whose decoding was skipped internally */
	CriUint32						reserved[1];			/*EN< Reserved region */
} CriManaFrameInfo;

/*EN
 * \brief Texture buffer structure
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Decoded video frame output buffer structure that the Mana player passes into the Mana player. 
 * The buffer address, size, and other information that the application needs to draw are included in this structure. 
 *
 * \sa criManaPlayer_CopyFrameToBufferARGB32
 */
typedef struct {
	CriUint8	*imagebuf;	/*EN< Texture buffer pointer */
	CriUint32	bufsize;	/*EN< Texture buffer size [byte] */
	CriUint32	pitch;		/*EN< Texture pitch [byte] */
} CriManaTextureBuffer;


/*EN
 * \brief YUV texture buffer structure
 * \ingroup MDL_MANALIB_PLAYER
 * \par Description: 
 * Output buffer structure for the criManaPlayer_CopyFrameToBuffersYUV function. 
 * Decoded Y, U, V, and Alpha plain are included as individual buffer information. 
 * The application will use a shader on these individual buffers to convert colors to RGB and draw. 
 * 
 * \sa criManaPlayer_CopyFrameToBuffersYUV
 */
 typedef struct {
	CriManaTextureBuffer y_plane;	/*EN< Y plane texture buffer structure */
	CriManaTextureBuffer u_plane;	/*EN< U plane texture buffer structure */
	CriManaTextureBuffer v_plane;	/*EN< V plane texture buffer structure */
	CriManaTextureBuffer a_plane;	/*EN< Alpha plane texture buffer structure */
} CriManaTextureBuffersYUV;

/*==========================================================================
 *      CRI Mana Decrypter API
 *=========================================================================*/
/*EN
 * \brief Configuration structure for decrypter creation
 * \ingroup MDL_MANALIB_DECRYPTER
 * \par Description: 
 * This structure stores the parameters required for decrypter creation.<br>
 * Specified as the ::criManaDecrypter_Create function argument. <br>
 * \attention
 * Because there may be more members in the future, always zero the structure before use. <br>
 * (Be careful not to enter undefined values in the structure.) 
 * \sa criManaDecrypter_Create
 */
typedef struct CriManaDecrypterConfigTag {
	/*EN
		\brief Decryption key
		\par Description: 
		Specifies the key number used in decryption. <br>
		When you decrypt data, you will need to specify the same value as the key used. <br>
		\attention
		You cannot specify zero in the decryption key.<br>
		(You will fail to create a decrypter if you specify zero.)<br>
		
	*/
	CriUint64 key;
} CriManaDecrypterConfig;

/*EN
 * \brief Decrypter handle
 * \ingroup MDL_MANALIB_DECRYPTER
 * \par Description: 
 * Handle to operate decrypters. <br>
 * Returns it as the ::criManaDecrypter_Create function return value. <br>
 * \sa criManaDecrypter_Create
 */
typedef void *CriManaDecrypterHn;

/***************************************************************************
 *      Prototype Callback
 ***************************************************************************/
/*EN
 * \brief Memory allocation function
 * \ingroup MDL_MANALIB_GLOBAL
 * \param[in]	obj		User specified object
 * \param[in]	size	Requested memory size (in bytes)
 * \return		void*	Allocated memory address (NULL if failed)
 * \par Description: 
 * Interface for registering the memory allocation function. <br>
 * Used when you want to replace memory allocation that the CRI Mana performs within the library with
 * the user's own memory allocation. <br>
 * \par Notes: 
 * The memory size needed for the size is set when the callback function 
 * is executed. <br>
 * Allocate memory for the size to the callback function and return the allocated memory address
 * as a return value. <br>
 * The user specified object registered by the ::criMana_SetUserAllocator function
 * will be passed into the argument obj. <br>
 * When you allocate memory and need to reference the memory manger,
 * set the said object into the ::criMana_SetUserAllocator function argument
 * and reference it through this callback function argument. <br>
 * \attention
 * Be aware that if memory allocation fails, an error callback may be returned and you
 * may fail to call the original function. 
 * \sa CriManaFreeFunc, criMana_SetUserAllocator
 */
typedef void *(CRIAPI *CriManaMallocFunc)(void *obj, CriUint32 size);

/*EN
 * \brief Memory release function
 * \ingroup MDL_MANALIB_GLOBAL
 * \param[in]	obj		User specified object
 * \param[in]	mem		Address of memory to release
 * \return				None
 * \par Description: 
 * Interface for registering the memory release function. <br>
 * Used when you want to replace the memory release that the CRI Mana performs within the library with 
 * the user's own memory release. <br>
 * \par Notes: 
 * The address of the memory to be released into mem will be set when the callback 
 * function is executed. <br>
 * Release the memory into the mem area with a callback function. 
 * The user specified object registered to the ::criMana_SetUserAllocator function
 * will be passed into the argument obj.
 <br>
 * When you allocate memory and need to reference the memory manger,
 * set the said object into the ::criMana_SetUserAllocator function argument
 * and reference it through this callback function argument. <br>
 * \sa CriManaMallocFunc, criMana_SetUserAllocator
 */
typedef void (CRIAPI *CriManaFreeFunc)(void *obj, void *mem);

/*EN
 * \brief Memory allocation function for meta data work
 * \ingroup MDL_MANALIB_GLOBAL
 * \par Description: 
 * Interface for allocating the meta data work area. 
 * 
 * \sa criManaPlayer_SetMetaDataWorkAllocator
 */
#define CriManaMetaMallocFunc CriManaMallocFunc

/*EN
 * \brief Memory release function for meta data work
 * \ingroup MDL_MANALIB_GLOBAL
 * \par Description: 
 * Interface for releasing the meta data work area. 
 * 
 * \sa criManaPlayer_SetMetaDataWorkAllocator
 */
#define CriManaMetaFreeFunc CriManaFreeFunc

/*EN
 * \brief Data request callback function
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	obj		User specified object
 * \param[in]	player	Mana player handle
 * \par Description: 
 * Callback function for specifying the next movie to play. 
 * Used to seamlessly concatenate multiple movie files to play. 
 * <br>
 * Use ::criManaPlayer_SetDataRequestCallback to register the callback function. 
 *
 */
typedef void (CRIAPI *CriManaPlayerDataRequestCbFunc)(void* obj, CriManaPlayerHn player);

/*EN
 * \brief Cuepoint callback function
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	obj			User specified object
 * \param[in]	player		Mana player handle
 * \param[in]	eventinfo	Cuepoint event information
 * \par Description: 
 * Callback function executed when a Cuepoint (timing information) embedded in
 * a movie occurs. 
 * <br>
 * Use the ::criManaPlayer_SetCuePointCallback function to register a callback function.
 */
typedef void (CRIAPI *CriManaPlayerCuePointCbFunc)(void* obj, CriManaPlayerHn player, CriManaEventPoint *eventinfo);


/***************************************************************************
 *      Prototype Functions
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*==========================================================================
 *      CRI Mana API
 *=========================================================================*/
/*EN
 * \brief Get the Mana library version number
 * \ingroup MDL_MANALIB_GLOBAL
 * \return		CriUint32	Version number
 * \par Call conditions: 
 * This is thread safe. 
 * \par Description: 
 * Gets the version number of the Mana library. <br>
 * If the value obtained by this function and the CRIMANA_VERSION
 * value shown in the header file ( cri_mana.h ) differ, the included header
 * and linked library version may not match. <br>
 * (Check the include path and library path set in the build environment.) <br>
 * \par Notes: 
 * You can detect discrepancies between the library and header when debugging by using the following code. <br>
 * \code
 * 		:
 * 	// Check consistency of library and header
 * 	assert(CRIMANA_VERSION == criMana_GetVersionNumber());
 * 		:
 * \endcode
 */
CriUint32 CRIAPI criMana_GetVersionNumber(void);

/*EN
 * \brief Returns the version number of the Mana library and build information. 
 * \ingroup MDL_MANALIB_GLOBAL
 * \return	const CriChar8 * Library information string
 * \par Call conditions: 
 * This is thread safe. 
 * \par Description: 
 * Displays the library information, build time, and platform information.
 */
const CriChar8* CRIAPI criMana_GetLibraryVersionString(void);

/*EN
 * \brief Register user allocator
 * \ingroup MDL_MANALIB_GLOBAL
 * \param[in]	malloc_func		Memory allocation function
 * \param[in]	free_func		Memory release function
 * \param[in]	obj				User object (optional)
 * \par Call conditions: 
 * Call this before the ::criMana_Initialize function. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Registers a memory allocator (memory allocation/release functions) in the CRI Mana library. <br>
 * Used when you want to replace the memory release that the CRI Mana performs within the library with
 * the user's own memory release. 
 * \par Notes: 
 * The registered memory allocator may be called by multiple threads. 
 * Register a multi-thread safe allocator. <br>
 * 
 * \sa CriManaMallocFunc, CriManaFreeFunc
 */
void CRIAPI criMana_SetUserAllocator(CriManaMallocFunc malloc_func, CriManaFreeFunc free_func, void *obj);

/*EN
 * \brief Calculate library initialization work area size
 * \ingroup MDL_MANALIB_GLOBAL
 * \param[in]	config	Initialization config structure
 * \return		CriSint32 Library work area size
 * \par Call conditions: 
 * This is thread safe. 
 * \par Description: 
 * Gets the work area size necessary for using the Mana library. <br>
 * The work area size that the library needs changes depending on the nature of the library's
 * initialization config structure. <br>
 * The argument config information is only referenced in the function. The config area can be released without problem
 * after the function is executed. 
 * \par Notes: 
 * Specific functions may exist on each platform. See the reference for each platform for more information.
 */
CriSint32 CRIAPI criMana_CalculateLibWorkSize(const CriManaLibConfig *config);

/*EN
 * \brief Library initialization
 * \ingroup MDL_MANALIB_GLOBAL
 * \param[in]	config	Initialization config structure
 * \param[in]	work	Work area address allocated on the app side (aligned internally)
 * \param[in]	work_size	Work area size (=criMana_CalculateLibWorkSize return value)
 * \par Call conditions: 
 * Call after the AtomEx library has been initialized and before all CRI Mana API. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Initializes the Mana library. <br>
 * You will always need to execute this function to use the library functions. <br>
 * <br>
 * When initializing the library, you will need to allocate the memory area (work area) so that
 * the library can use it internally. <br>
 * <br>
 * Specify the maximum number of handle resources that are used concurrently and the thread model with this function. 
 * If you want to adjust the number of handle resources midway, stop all playback and recall
 * this function once it is completed using the ::criMana_Finalize function. 
 * <br>
* When specifying NULL in work and zero in work_size, it will use the memory allocation function
 * registered by the ::criMana_SetUserAllocator function and allocate memory internally. 
 * <br>
 * \par Notes: 
 * The work area size that the library needs changes to meet the nature of the
 * initialization config structure. <br>
 * The size of the work area required will also differ depending on the platform. 
 * <br>
 * The argument config information will only be referenced in the function. <br>
 * It cannot be referenced after exiting this function, so releasing the config area after the function has been executed
 * will not cause problems 
 * \par Notes: 
 * Specific functions may exist on each platform. See the reference for each platform for more information. 
 *
 * \sa criMana_Finalize
 */
void CRIAPI criMana_Initialize(const CriManaLibConfig* config, void* work, CriSint32 work_size);

/*EN
 * \brief Initialize frame conversion (32bit ARGB8888 format)
 * \ingroup MDL_MANALIB_GLOBAL
 * \par Call conditions: 
 * Execute this function after initializing the CRI Mana library. 
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Initialization function necessary for grabbing a frame in 32bit ARGB8888 format. <br>
 * Always call this function before the grab function when grabbing a frame in the above format. <br>
 * <br>
 * \par Notes
  * Calling this function will link the static memory area (several hundred KB) required to the internal frame color conversion. 
 * Therefore, do not use this function with applications that grab frames in other formats that
 * do not use the above format. 
 *
 * \sa criManaPlayer_CopyFrameToBufferARGB32
 */
void CRIAPI criMana_InitializeFrameARGB32(void);

/*EN
 * \brief Finalize library
 * \ingroup MDL_MANALIB_GLOBAL
 * \par Call conditions: 
 * All handles will be in the CRIMANAPLAYER_STATUS_STOP or CRIMANAPLAYER_STATUS_PLAYEND status.  <br>
 * Call the AtomEx library finalization function after this function.<br>
 *  <br>
  * This is not thread safe. 
 * \par Description: 
 * Finalizes the Mana library. <br>
 * \par Notes: 
 * Specific functions may exist on each platform. See the reference for each platform for more information. 
 *
 * \sa criMana_Initialize
 */
void CRIAPI criMana_Finalize(void);

/*EN
* \brief Get library initialization status
* \ingroup MDL_MANALIB_GLOBAL
* \return	CriBool		True if the library was initialized, false otherwise
* \retval	CRI_FALSE	Uninitialized
* \retval	CRI_TRUE	Initialized
* \par Description:
* Check if the CRI Mana library has already been initialized.<br>
* \sa criMana_Initialize, criMana_Finalize
*/
CriBool CRIAPI criMana_IsInitialized(void);

/*EN
 * \brief Execute server processing
 * \ingroup MDL_MANALIB_GLOBAL
 * \par Call conditions: 
 * Library initialization is complete. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Updates the internal status of the Mana library. <br>
 * The application will need to periodically execute this function. <br>
 * <br>
 * Use the ::criManaPlayer_ExecuteMain function when you want to manage the updating of
 * the internal status of each handle. <br>
 * <br>
 * \attention
 * Unlike the CRI Atom library's criAtomEx_ExecuteMain function, this function
 * will not automatically execute itself periodically in the Mana library, even if CRIMANA_THREAD_MODEL_MULTI is set. Therefore, delaying the calling of this function
 * may cause stuttering during movie playback.
 */
void CRIAPI criMana_ExecuteMain(void);

/*EN
 * \brief Synchronize with the master timer
 * \ingroup MDL_MANALIB_GLOBAL
 * \par Call conditions: 
 * Library initialization is complete. <br>
 * <br>
 * This is not thread safe. Executing with a separate thread may cause a bad time returned by GetTime. 
 * \par Description: 
 * Synchronizes all Mana player handle playback times in the master timer. <br>
 * Use the ::criManaPlayer_SyncMasterTimer function if you want to manage the master timer time
 * synchronization for each handle. 
 * <br>
 * \attention
 * At a minimum, this function needs to be called in a shorter cycle than the frame rate.
 */
void CRIAPI criMana_SyncMasterTimer(void);

/*EN
 * \brief 
 * \ingroup MDL_MANALIB_GLOBAL
 * \par Call conditions: 
 * Library initialization is complete. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Advances the manual timer time of all Mana player handles. 
 * Refer to the criManaPlayer_AdvanceManualTimer function for each handle for more information
 * on its functions. 
 * 
 * \sa criManaPlayer_AdvanceManualTimer
 */
void CRIAPI criMana_AdvanceManualTimer(void);

/*EN
 * \brief Decode video (all handles at once)
 * \ingroup MDL_MANALIB_GLOBAL
 * \par Call conditions: 
 * Library initialization is complete. <br>
 * <br>
 * This is thread safe. 
 * \par Description: 
 * Executes the ::criManaPlayer_ExecuteVideoProcess function for each Mana player handle
 * that has been created. 
 * <br>
 * If CRIMANA_THREAD_MODEL_MULTI has been set using the ::criMana_Initialize function, then
 * this function will be automatically executed on top of the separate thread that was created in the Mana library. Therefore,
 * there is no need to call it from the application. Set it so that it has a lower priority
 * than the main thread.
 */
void CRIAPI criMana_ExecuteVideoProcess(void);

/*EN
 * \brief Set the decoding skip flag (all handles at once)
 * \ingroup MDL_MANALIB_GLOBAL
 * \par Call conditions: 
 * This is thread safe. 
 * \par Description: 
 * Enables the decoding skip function. <br>
 * Enables skipping if the argument flag is CRI_TRUE(1). * Disables skipping if the argument flag is CRI_FALSE(0). <br>
 * <br>
 * Enabling decoding skip will automatically skip the required number of frames internally
 * if slowdown occurs due to playback load. While there will be some visual stuttering, it will make it easier to prevent sound jumping. <br>
 * <br>
* Whether skipping is enabled by default depends on the platform. It is disabled by default on platforms with uniquely determined
 * device performance and enabled by default on platforms without.
 */
void CRIAPI criMana_SetDecodeSkipFlag(CriBool flag);


/*EN
 * \brief Set overall pause (all handles together)
 * \ingroup MDL_MANALIB_GLOBAL
 * \param[in]	flag	Overall pause flag (CRI_TRUE:Enable overall pause, CRI_FALSE:Disable overall pause)
 * \par Call conditions: 
 * Library initialization is complete. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Enables the overall pause function. <br>
 * Enables overall pause if the argument flag is CRI_TRUE(1). * Disables overall pause if the argument flag is CRI_FALSE(0). <br>
 * <br>
 * Switching overall pause from disabled to enabled will pause all handles. <br>
 * (Looking at it from the app side, all movies will be paused.)
 * However, information on whether the pause switch (user pause flag) individually specified
 * by the user with the criManaPlayer_Pause function is enabled or disabled will be kept internally. 
 * (It will refresh the user pause flag using the criManaPlayer_Pause
 * function even while overall pause is enabled.)<br>
 * The criManaPlayer_IsPaused function will return information on the user pause flag,
 * so information on whether the overall flag is enabled or disabled will be separate. 
 * <br>
 * When switching overall pause from enabled to disabled, handles enabled by the user pause flag will
 * continue to be paused, while handles disabled by the user pause flag
 * will restart the movie. 
 *
 * \sa criMana_GetAllPauseFlag, criManaPlayer_Pause, criManaPlayer_IsPaused
 */
void criMana_SetAllPauseFlag(CriBool flag);

/*EN
 * \brief Get the overall pause flag
 * \ingroup MDL_MANALIB_GLOBAL
 * \return	CriBool Overall pause flag
 * \par Call conditions: 
 * This is not thread safe. 
 * \par Description: 
 * Gets the overall pause flag. <br>
 * <br>
 * Be aware that the user pause flag that can be gotten with the criManaPlayer_IsPaused function is different. 
 *
 * \sa criMana_SetAllPauseFlag
 */
CriBool criMana_GetAllPauseFlag(void);

/*EN
 * \brief Prevent decoding interruptions
 * \ingroup MDL_MANALIB_GLOBAL
 * \par Description: 
 * Prevents decoding interruptions. <br>
 *Prevents the decoding operation from being interrupted after this function is executed until the ::criMana_Unlock function is executed. <br>
 * \sa criMana_Unlock
 */
void criMana_Lock(void);

/*EN
 * \brief Cancel decoding interruption prevention
 * \ingroup MDL_MANALIB_GLOBAL
 * \par Description: 
 * Cancels the decoding interruption prevention through using the ::criMana_Lock function. 
 * \sa criMana_Lock
 */
void criMana_Unlock(void);

/* criMana_UseStreamerManager */
/*EN
 * \brief Set control flag on whether to use the streaming management module
 * \ingroup MDL_MANALIB_GLOBAL
 * \param[in]	flag	Control flag (CRI_TRUE: use, CRI_FALSE: not use)
 * \par Call conditions: 
 * Callable even after library initialization. However, it can not be called while movies are playing.
 * \par Description: 
 * Specify whether to use common streaming management module with the ADX2. <br>
 * The default depends on the platform. For platforms that can ignore the seek load such as iOS and Android, it is not used as default.
 * \attention
 * All the platforms had used the module before this function was added. To return to the conventional behavior, specify CRI_TRUE with this function.
 * \sa criMana_IsStreamerManagerUsed
 */
void CRIAPI criMana_UseStreamerManager(CriBool flag);

/* criMana_IsStreamerManagerUsed */
/*EN
 * \brief Get the control flag as to whether or not to use the streaming management module
 * \ingroup MDL_MANALIB_GLOBAL
 * \return	Control flag (CRI_TRUE: use, CRI_FALSE: not use)
 * \par Call conditions: 
 * It is thread safe. 
 * \par Description: 
 * Obtain control flags on whether to use the streaming management module.
 * \sa criMana_UseStreamerManager
 */
CriBool CRIAPI criMana_IsStreamerManagerUsed(void);

/*==========================================================================
 *      CRI Mana Player API
 *=========================================================================*/
/*EN
 * \brief Calculate ManaPlayer work area size (no config specified)
 * \ingroup MDL_MANALIB_PLAYER
 * \return	CriSint32 Handle work size
 * \par Call conditions: 
 * This is thread safe. 
 * \par Description: 
 * Gets the work area size necessary for creating the Mana library. <br>
 * The work memory size necessary for creating the Mana player differs by platform. 
 *
 * \sa criManaPlayer_Create
 */
CriSint32 CRIAPI criManaPlayer_CalculateHandleWorkSize(void);

/*EN
 * \brief Calculate ManaPlayer work area size (config specified)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	config	Pointer to the config structure for creating a Mana player handle
 * \return	CriSint32 Handle work size
 * \par Call conditions: 
 * This is thread safe. 
 * \par Description: 
 * Gets the work area size necessary for creating the Mana library. <br>
 * Unlike the ::criManaPlayer_CalculateHandleWorkSize, calculates work size
 * based on the handle creation parameters. <br>
 * Allocate more memory than the work size calculated with this function and
 * specify it in criManaPlayer_CreateWithConfig. <br>
 * \par Notes: 
 * The work memory size necessary for creating the Mana player will differ by platform, even if the parameters are the same. 
 *
 * \sa criManaPlayer_CreateWithConfig, criManaPlayer_SetDefaultHandleConfig
 */
CriSint32 CRIAPI criManaPlayer_CalculateHandleWorkSizeWithConfig(const CriManaPlayerConfig *config);

/*EN
 * \brief Create Mana player (no config specified)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	work	Work area address (align internally)
 * \param[in]	work_size	Work area size
 * \return	CriManaPlayerHn Mana player handle
 * \par Call conditions: 
 * Library initialization is complete. <br>
 * <br>
 * This is not thread safe. <br>
 * \par Description: 
 * Creates a Mana player. <br>
 * <br>
 * When creating the player, you will need to allocate the memory area (work area) so that
 * the library can use it internally. <br>
 * When expressly allocating memory on the application side, confirm the 
 * necessary work size using the ::criManaPlayer_CalculateHandleWorkSize function and pass the allocated work memory into the argument. <br>
 * When specifying NULL in work and zero in work_size, it will use the memory allocation function
 * registered by the ::criMana_SetUserAllocator function and allocate memory internally. 
 * 
 * \sa criManaPlayer_CalculateHandleWorkSize, criManaPlayer_Destroy
 */
CriManaPlayerHn CRIAPI criManaPlayer_Create(void *work, CriSint32 work_size);

/*EN
 * \brief Create Mana player (config specified)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	config	Pointer to the config structure for creating a Mana player handle
 * \param[in]	work	Work area address (align internally)
 * \param[in]	work_size	Work area size
 * \return	CriManaPlayerHn Mana player handle
 * \par Call conditions: 
 * Library initialization is complete. <br>
 * <br>
 * This is not thread safe. <br>
 * \par Description: 
 * Specifies the handle creation parameters and creates the Mana player. <br>
 The player that was created will allocate only as many internal resources as are necessary according to the parameters. <br>
 * <br>
 * When creating the player, you will need to allocate the memory area (work area) so that
 * the library can use it internally. <br>
 * When expressly allocating memory on the application side, confirm the necessary work size using the ::criManaPlayer_CalculateHandleWorkSizeWithConfig
 * function and pass the allocated work memory into the argument. <br>
 * When specifying NULL in work and zero in work_size, it will use the memory allocation function
 * registered by the ::criMana_SetUserAllocator function and allocate memory internally. <br>
 * <br>
 * \attention
 * When adjusting the handle creation parameters and creating a Mana player handle, only movies that satisfy the
 * conditions of the handle creation parameters can be played using this handle. <br>
 * However, there are benefits to this, such as there being little delay in movies starting. <br>
 * 
 * \sa criManaPlayer_CalculateHandleWorkSizeWithConfig, criManaPlayer_Destroy
 */
CriManaPlayerHn CRIAPI criManaPlayer_CreateWithConfig(const CriManaPlayerConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Destroy the Mana player
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \par Call conditions: 
 * When player status is CRIMANAPLAYER_STSTUS_STOP or CRIMANAPLAYER_STSTUS_PLAYEND. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Destroys the Mana player. <br>
 * When this function is executed, it will destroy all resources allocated when the AtomEx player was created. <br>
 * It will also disable the Mana player handle that was specified in the argument. <br>
 * Release the work memory that was set with the ::criManaPlayer_Create function after executing this function. 
 * Release the memory internally with this function if the work memory was not passed on the application side and
 * memory was allocated on the library side. 
 * 
 * \sa criManaPlayer_Create
 */
void CRIAPI criManaPlayer_Destroy(CriManaPlayerHn player);

/*EN
 * \brief Register meta data allocator
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	allocfunc	Meta data work allocation callback function
 * \param[in]	freefunc	Meta data work release callback function
 * \param[in]	obj			User object (optional)
 * \param[in]	meta_flag	Used meta flag (unsupported)
 * \par Call conditions: 
 * Call this function before analyzing the header. <br>
 * <br>
 * This is not thread safe. <br>
 * \par Description: 
 * Set a memory allocator (memory allocation/release function) to allocate the meta data
 * necessary for seek and Cuepoint functions. 
 * <br>
* When registering a memory allocator with this function, the meta data work allocator registered
 * in the library when the header was analyzed will be used to allocate meta data work. <br>
 * <br>
* Conversely, it will automatically destroy the meta data if this function is not executed. In this situation, be aware
 * that seek and Cuepoint functions cannot be used. 
 * <br>
 * \par Notes: 
 * Currently, the setting by meta data type using meta_flag cannot be used. Use CRIMANA_META_FLAG_ALL. <br>
 * <br>
 * Also, you do not need to re-register an allocator when reusing a handle to play a movie. 
 * \par Caution: 
 * The registered memory allocator may be called by multiple threads. 
 * Register a multi-thread safe allocator. <br>
 *
 * \sa CriManaMetaMallocFunc, CriManaMetaFreeFunc
 */
void CRIAPI criManaPlayer_SetMetaDataWorkAllocator(
	CriManaPlayerHn player, CriManaMetaMallocFunc allocfunc, CriManaMetaFreeFunc freefunc, void *obj, CriManaMetaFlag meta_flag);

/*EN
 * \brief Get playback work parameter structure
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[out]	config_basic	Pointer to the basic playback work parameters (required)
 * \param[out]	config_ex	Pointer to the extended playback work parameters (additional) - can be specified as NULL
 * \return	CriBool indicating wether the work parameters have been retrieved.<br>
 * Will return CRI_FALSE if the header has not been analyzed. 
 * \par Call conditions: 
 * Finish header analysis and call when the status is CRIMANAPLAYER_STATUS_WAIT_PREP. <br>
 * <br>
 * This function is not thread safe. 
 * \par Description: 
 * Gets the default playback parameters for movie playback based on the movie file header data. <br>
 * <br>
 * Calling this function when the header has not yet been analyzed will clear the content of config_basic and config_ex. <br>
 * <br>
 * When not playing sub audio or alpha movies, you can set config_ex to NULL and omit this.
 * \par Caution: 
 * When sub audio playback is performed, please set the audio track before calling this API.<br>
 * If you set the audio track after calling this API, the playback work size of the audio can not be calculated correctly,
 * and setting the playback work area may fail.
 */
CriBool CRIAPI criManaPlayer_GetPlaybackWorkParam(
	CriManaPlayerHn player, CriManaPlaybackBasicWorkConfig *config_basic, CriManaPlaybackExWorkConfig *config_ex);


/*EN
 * \brief Calculate playback work area size
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	config_basic	Pointer to the basic playback work parameters (required)
 * \param[in]	config_ex		Pointer to the extended playback work parameters (additional) can be specified as NULL
 * \return	CriSint32 Playback work size
 * \par Call conditions: 
 * This is thread safe. 
 * \par Description: 
 * Calculates the size of the work memory required to play the specified movie file. <br>
 * When config_ex is passed as NULL, it will return a size that excludes the extended play work memory.
 */
CriSint32 CRIAPI criManaPlayer_CalculatePlaybackWorkSize(
	CriManaPlayerHn player, const CriManaPlaybackBasicWorkConfig *config_basic, const CriManaPlaybackExWorkConfig *config_ex);


/*EN
 * \brief Set playback work area
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	config_basic	Pointer to the basic playback work parameters (required)
 * \param[in]	config_ex		Pointer to the extended playback work parameters (additional) can be specified as NULL
 * \param[in]	work			Work area allocated by the app (automatically aligned internally)
 * \param[in]	work_size		Work size
 * \par Call conditions: 
 *Call when the status is CRIMANAPLAYER_STATUS_WAIT_PREP or before. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Sets the work memory required to play the specified movie file. <br>
 * <br>
* When memory has been expressly allocated on the application side, check
 * the necessary work size with the ::criManaPlayer_CalculatePlaybackWorkSize function and pass the allocated work memory into the argument. <br>
 * When specifying NULL in work and zero in work_size, it will use the memory allocation function
 * registered by the ::criMana_SetUserAllocator function and allocate memory internally. 
 * <br>
 * Starting a playback without executing this function will automatically use the default play parameters internally
 * to play. In this case, a memory allocator needs to be registered with the ::criMana_SetUserAllocator function in advance. 
 * <br>
 * Release the set work area after destroying the player handle. When releasing the work area after
 * finishing playback or stopping playback, call the ::criManaPlayer_FreePlaybackWork function and then release 
 * the memory. <br>
 * 
 * \sa criManaPlayer_CalculatePlaybackWorkSize
 */
void CRIAPI criManaPlayer_SetPlaybackWork(
	CriManaPlayerHn player, const CriManaPlaybackBasicWorkConfig *config_basic, const CriManaPlaybackExWorkConfig *config_ex, 
	void *work, CriSint32 work_size);


/*EN
 * \brief Release playback work
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \par Call conditions: 
 * Execute this function when in the MANAPLAYER_STATUS_STOP or CRIMANAPLAYER_STATUS_PLAYEND status. <br>
 * Calling this function during playback will result in error. 
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Releases the playback work memory and internal resources when allocating or keeping player handles internally. <br>
 * <br>
 * When registering a user allocator and allocating playback work, release the playback work memory internally with this
 * function through the allocator. <br>
 * <br>
 * Executing this function will prevent access to the playback work memory from the player handle. 
 * When passing the playback work memory from the applications, it is possible to release the memory after calling
 * this function.
 */
void CRIAPI criManaPlayer_FreePlaybackWork(CriManaPlayerHn player);

/*EN
 * \brief Get the Mana player status
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \return	CriManaPlayerStatus Mana player handle status
 * \par Call conditions: 
 * This is not thread safe. 
 * \par Description: 
 * Gets the Mana player status. 
 * 
 * \sa CriManaPlayerStatus
 */
CriManaPlayerStatus CRIAPI criManaPlayer_GetStatus(CriManaPlayerHn player);


/*EN
 * \brief Execute Mana player server processing
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \par Call conditions: 
 * This is not thread safe. 
 * \par Description: 
 * Updates the internal status of the Mana player handle. <br>
 * <br>
 * When calling the ::criMana_ExecuteMain function with the application, this function will automatically be called internally so there
 * is no need to execute it.
 */
void CRIAPI criManaPlayer_ExecuteMain(CriManaPlayerHn player);

/*EN
 * \brief Synchronize with the master timer
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \par Call conditions: 
 * This is not thread safe. 
 * \par Description: 
 * Synchronizes the Mana player handle time with the master timer. <br>
 * At a minimum, this function needs to be called in a shorter cycle than the
 * video frame rate. 
 * <br>
 * When calling the ::criMana_SyncMasterTimer function with the application, this function will automatically be called internally
 * so there is no need to execute it.
 */
void CRIAPI criManaPlayer_SyncMasterTimer(CriManaPlayerHn player);

/*EN
 * \brief Set master timer type
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	type    Master timer type
 * \par Call conditions: 
 * This is thread safe. 
 * \par Description: 
 * Sets the timer type used in managing video frame time. <br>
 * The default is the system timer specified during handle creation. <br>
 * Specify the audio timer if you want to synchronize the video frame display timing with the audio time. <br>
 * Even if you specify the audio timer, if there is no audio included in the movie to play back then it will synchronize with the system timer.
 */
void  CRIAPI criManaPlayer_SetMasterTimerType(CriManaPlayerHn player, CriManaTimerType type);

/*EN
 * \brief Get master timer type
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \return	CriManaTimerType Current master timer type
 * \par Call conditions: 
 * This is thread safe. 
 * \par Description: 
 * Gets the master timer type that is currently set.
 */
CriManaTimerType CRIAPI criManaPlayer_GetMasterTimerType(CriManaPlayerHn player);

/*EN
 * \brief Set unit of manual timer time advancement (rational number format)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	timer_manual_unit_n	Numerator of unit of time advancement. 
 * \param[in]	timer_manual_unit_d	Denominator of unit of time advancement. 
 * \par Call conditions: 
 * This is not thread safe. 
 * \par Description: 
 * Sets the unit of time advancement in the manual timer in a rational number format. 
 * It will be "Numerator (timer_manual_unit_n) / Denominator (timer_manual_unit_d) = Unit of time advancement (second)." 
 * See the following setting example. 
  <br>
  \table "Setting example" align=center width=90% border=1 cellspacing=0 cellpadding=4
  {Main loop (app refresh rate)     |Numerator (timer_manual_unit_n) |Denominator (timer_manual_unit_d) |Unit of time advancement               }
  [60    fps                          |1                           |60                          |1    / 60    (=~ 16.6 msec)]
  [59.94 fps                          |1001                        |60000                       |1001 / 60000 (=~ 16.7 msec)]
  [30    fps                          |1                           |30                          |1    / 30    (=~ 33.3 msec)]
  [29.97 fps                          |1001                        |30000                       |1001 / 30000 (=~ 33.4 msec)]
  \endtable
 * 
 * Internal Mana player time will be calculated using the values set with this function and the count value advanced by
 * the criMana_AdvanceManualTimer function or
 * the criManaPlayer_AdvanceManualTimer function.
 
 * 
 * \sa criMana_AdvanceManualTimer, criManaPlayer_AdvanceManualTimer
 */
void CRIAPI criManaPlayer_SetManualTimerUnit(CriManaPlayerHn player, CriUint64 timer_manual_unit_n, CriUint64 timer_manual_unit_d);

/*EN
 * \brief Advance manual timer time (count value)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \par Call conditions: 
 * This is not thread safe. 
 * \par Description: 
 * Advances individual handle time (count time) in the manual timer. 
 * You will need to periodically call this function with the application to proceed with movie playback in the master timer. 
 * - Advances time when the player status is PLAYING. 
 * - Time will not advance if paused, even if this function is called. 
 * - Time (count value) will reset to zero when starting or stopping movie playback. 
 * 
 * \sa criManaPlayer_SetManualTimerUnit
 */
void CRIAPI criManaPlayer_AdvanceManualTimer(CriManaPlayerHn player);

/*EN
 * \brief Video decoding
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \return	CriBool CRI_TRUE during movie playback and CRI_FALSE when playback finishes or stops
 * \par Call conditions: 
 * This is thread safe. 
 * \par Description: 
 * Will decode one picture of the Mana player handle. <br>
 * Picture decoding is a heavy load process, so processing slowdown may occur if it is called from the application's main thread. <br>
 * In this situation, either set it to a multi-thread framework or call this function from a different low priority thread. <br>
 * <br>
  * When calling the ::criMana_ExecuteVideoProcess function, this function is automatically called internally
 * so you do not need to use it. Also, when it is operating on a multi-thread framework, no decoding will occur even if
 * this function is called. 
 * <br>
* The return value for this function will show whether the movie is being played or not. <br>
 * If you call this function with a different thread on the application side, always continue to call it until it becomes CRI_FALSE. <br>
 * Finishing thread decoding while the return value is CRI_TRUE will not let the handle status transition to
 * CRIMANAPLAYER_STATUS_STOP or CRIMANAPLAYER_STATUS_PLAYEND, and the handle will not be able to be destroyed.<br> 
 */
CriBool CRIAPI criManaPlayer_ExecuteVideoProcess(CriManaPlayerHn player); 

/*EN
 * \brief Set movie file
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	bndrhn	Binder handle for bound CPK files
 * \param[in]	path	Content path in CPK file
 * \par Call conditions: 
 * Execute this function when in the CRIMANAPLAYER_STATUS_STOP or CRIMANAPLAYER_STATUS_PLAYEND status. <br>
 * Or, you can call it within the data request callback. <br> 
 * This is not thread safe. <br>
 * \par Description: 
 * Sets the file path for streaming. <br>
 * You can play a movie from a CPK file by specifying the binder handle for the bound CPK file to the second argument bndhn. 
 * Specify NULL to the bndhn to stream directly from a file instead of from the CPK. <br>
 * <br>
 * Repeatedly calling this function will overwrite the memory information. <br>
 * Calling the ::criManaPlayer_SetData function will erase the memory information specified by this function from the handle. <br>
 * <br>
 * You can omit calling this function if you are repeatedly playing the same movie data with the same handle. <br>
 * <br>
 * Actual access to the specified memory area will be after either the ::criManaPlayer_DecodeHeader function, the ::criManaPlayer_Prepare function,
 * or the ::criManaPlayer_Start function is called.<br>
 */
void CRIAPI criManaPlayer_SetFile(
	CriManaPlayerHn player, CriFsBinderHn bndrhn, const CriChar8 *path);

/*EN
 * \brief Set data for memory playback
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[in]	dataptr		Buffer address for all the movie data that has finished loading
 * \param[in]	datasize	Buffer size
 * \par Call conditions: 
 * Execute this function when in the CRIMANAPLAYER_STATUS_STOP or CRIMANAPLAYER_STATUS_PLAYEND status. <br>
 * You can also call it from within the data request callback. <br> 
 * <br>
 * This function is not thread safe. <br>
 * \par Description: 
 * Sets the address of the data to use for memory playback. <br>
 * <br>
 * Repeatedly calling this function will overwrite the memory information. <br>
 * Calling the ::criManaPlayer_SetFile function , the ::criManaPlayer_SetFileRange function or the ::criManaPlayer_SetContentId function will
 * erase the memory information specified with this function. <br>
 * <br>
 * It is not necessary to call this function if you are repeatedly playing the same movie data with the same handle. <br>
 * <br>
 * Actual access to the specified memory area will happen after either the ::criManaPlayer_DecodeHeader function, the ::criManaPlayer_Prepare function,
 * or the ::criManaPlayer_Start function is called. <br>
 * 
 * \par Notes: 
 * If the specified buffer is larger than the movie data size, it will skip reading any non-movie data at the end of the buffer. 
 * However, you always have to specify the correct begining of the movie data for the buffer address.
 */
void CRIAPI criManaPlayer_SetData(
	CriManaPlayerHn player, const void *dataptr, CriSint64 datasize);

/*EN
 * \brief Set movie file to play (specify CPK Content ID)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	bndrhn	Binder handle for bound CPK
 * \param[in]	id		Content ID in CPK file
 * \par Call conditions: 
 * Execute this function when in the CRIMANAPLAYER_STATUS_STOP or CRIMANAPLAYER_STATUS_PLAYEND status. <br>
 * Or, you can call it within the data request callback. <br> 
 * This is not thread safe. <br>
 * \par Description: 
 * Sets the file path for streaming. <br>
 * You can play a movie from a CPK file by specifying the binder handle for the bound CPK file to the second argument bndhn. 
 * Specify NULL to the bndhn to stream directly from a file instead of from the CPK. <br>
 * <br>
 * Repeatedly calling this function will overwrite the memory information. <br>
 * Calling the ::criManaPlayer_SetData function will erase the memory information specified by this function from the handle. <br>
 * <br>
 * You can omit calling this function if you are repeatedly playing the same movie data with the same handle. <br>
 * <br>
 * Actual access to the specified memory area will be after either the ::criManaPlayer_DecodeHeader function, the ::criManaPlayer_Prepare function,
 * or the ::criManaPlayer_Start function is called.<br>
 */
void CRIAPI criManaPlayer_SetContentId(
	CriManaPlayerHn player, CriFsBinderHn bndrhn, CriSint32 id);

/*EN
 * \brief Specify the movie file in the pack file (specify file range)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	fname	Buffer file path that includes the movie file
 * \param[in]	offset	Offset to the movie from the pack file beginning
 * \param[in]	range	Movie data range (unit: byte)
 * \par Call conditions: 
 * Execute this function when in the CRIMANAPLAYER_STATUS_STOP or CRIMANAPLAYER_STATUS_PLAYEND status. <br>
 * Or, you can call it within the data request callback. <br> 
 * <br>
 * This is not thread safe. <br>
 * \par Description: 
 * Specifies the packed file for the movie file that you want to stream. By specifying the offset position and data range in the argument,
 * you can set any movie data in the buffer file as the read source. 
 * The maximum length of the string that you can specify as a file path is CRIMANA_MAX_FILE_NAME bytes. <br>
 * <br>
 * Repeatedly calling this function will overwrite the memory information. <br>
 * Calling the ::criManaPlayer_SetData function will erase the memory information specified by this function from the handle. <br>
 * <br>
 * You can omit calling this function if you are repeatedly playing the same movie data with the same handle. 
 * 
 * \par Notes: 
 * A file open request is not made within this function. To open a file, call either the ::criManaPlayer_DecodeHeader function, the ::criManaPlayer_Prepare function, 
 * or the ::criManaPlayer_Start function and open it in the ::criManaPlayer_ExecuteMain function.
 */
void CRIAPI criManaPlayer_SetFileRange(CriManaPlayerHn player, const CriChar8 *fname, CriUint64 offset, CriSint64 range);

/*EN
 * \brief Reset the same movie data
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \par Description: 
 * Instructs the Mana player to replay the previously played data. <br>
 * \par Example: 
 * The following process will also enable you to play the same audio data in an unlimited loop. <br>
 * \code
 * // Data request callback function
 * void on_data_request(void *obj, CriManaPlayerHn player)
 * {
 * 	// Reset previously played data
 * 	criManaPlayer_SetPreviousDataAgain(player);
 * }
 * 
 * main()
 * {
 * 		:
 * 	// Register data request callback function
 * 	criManaPlayer_SetDataRequestCallback(player, on_data_request, NULL);
 * 	
 * 	// First, set the initial movie data
 * 	criManaPlayer_SetData(player, buffer, buffer_size);
 * 	// [MEMO] The following movie sources can be used in the same way
 * 	// criManaPlayer_SetFile(player, NULL, movie_path);
 *  // criManaPlayer_SetFileRange(player, movie_path, offset, range);
 *
 * 	// Play set audio data
 * 	criManaPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * \attention
 * This function can only be used in the data request callback function.
 <br>
 * (It can be executed apart from the data request callback function, but nothing will happen.) <br>
 * 
 * \par Notes: 
 * For just loop playback, you can also use the ::criManaPlayer_Loop function. 
 *
 * \sa criManaPlayer_SetDataRequestCallback
 */
void CRIAPI criManaPlayer_SetPreviousDataAgain(CriManaPlayerHn player);


/*EN
 * \brief Get movie header information
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[out]	mvinf	Address to the movie information structure
 * \return	Whether or not CriBool movie information is retrieved.
 * \par Call conditions: 
 * You can get information when called after the Mana player is in CRIMANAPLAYER_STATUS_WAIT_PREP status. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Gets the CriManaMovieInfo movie information. <br>
 * Mainly determine bit rate, resolution, the number of audio, and so on from the movie information. <br>
 * Call the ::criManaPlayer_DecodeHeader function and analyze the header if you want to determine movie information before playback begins. <br>
 * <br>
 * With concatenated play, it will return information on the movie file including the last frame that was grabbed. 
 * 
 * \sa criManaPlayer_DecodeHeader
 */
CriBool CRIAPI criManaPlayer_GetMovieInfo(CriManaPlayerHn player, CriManaMovieInfo *mvinf);

/*EN
 * \brief Request header decoding
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \par Call conditions: 
 * Execute this function when in the CRIMANAPLAYER_STATUS_STOP or CRIMANAPLAYER_STATUS_PLAYEND status. <br>
 * Also, specify the playback file and playback data before executing this function. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * This function is to only analyze the header and then wait for starting a playback. <br>
 * By using this function and finishing header analysis beforehand, you can get information on movie resolution and audio
 * before playback begins. <br>
 * Calling this function will transition the Mana player handle status from CRIMANAPLAYER_STATUS_STOP to CRIMANAPLAYER_STATUS_DECHDR.
 * When header analysis is complete it will become CRIMANAPLAYER_STATUS_WAIT_PREP. <br>
 * When getting the movie information, execute the ::criManaPlayer_GetMovieInfo function after the handle status becomes
 * CRIMANAPLAYER_STATUS_WAIT_PREP. <br>
 * <br>
 * You can continue with movie playback by calling the ::criManaPlayer_Prepare function or the ::criManaPlayer_Start function
 * when the handle status is CRIMANAPLAYER_STATUS_WAIT_PREP. <br>
 * 
 * \par Notes: 
 * If you have registered a data request callback function, you can omit presetting the movie data. 
 * 
 * \sa criManaPlayer_GetStatus, criManaPlayer_Prepare, criManaPlayer_Start, criManaPlayer_SetDataRequestCallback
 */
void CRIAPI criManaPlayer_DecodeHeader(CriManaPlayerHn player);

/*EN
 * \brief Request playback preparation
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \par Call conditions: 
 * Specify the playback file and playback data before executing this function. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * This function is to only analyze the header, prepare for playback, and then wait for starting a playback. <br>
 * You can precisely control the timing of starting movie playback by using this function and finishing playback preparations beforehand. <br>
 * (Calling the start playback function without preparing for play will cause a time lag until playback actually begins.) <br>
 * Calling this function will cause the Mana player handle status to transition from CRIMANAPLAYER_STATUS_STOP to CRIMANAPLAYER_STATUS_DECHDR to CRIMANAPLAYER_STATUS_PREP.
 * When playback preparation is complete, it will become CRIMANAPLAYER_STATUS_READY. <br>
 * <br>
 * You can start playback by calling the ::criManaPlayer_Start function when the handle status is CRIMANAPLAYER_STATUS_READY. <br>
 * <br>
 * Calling this function without calling the ::criManaPlayer_DecodeHeader function will prevent the Mana player handle status from becoming 
 * CRIMANAPLAYER_STATUS_STOP or CRIMANAPLAYER_STATUS_PLAYEND. 
 * 
 * \par Notes: 
 * If you have registered a data request callback function, you can omit presetting the movie data. 
 * 
 * \sa criManaPlayer_GetStatus, criManaPlayer_DecodeHeader, criManaPlayer_Start,
 *     criManaPlayer_SetBufferingTime
 */
void CRIAPI criManaPlayer_Prepare(CriManaPlayerHn player);

/*EN
 * \brief Start playback
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \par Call conditions: 
 * Specify the playback file and playback data before executing this function. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Starts movie playback. <br>
 * When calling this function without calling the ::criManaPlayer_Prepare function, there will be a time lag until the movie actually
 * starts to play in order to prepare for movie analysis and playback. <br>
 * If you call the ::criManaPlayer_Prepare function first and the handle status becomes CRIMANAPLAYER_STATUS_READY,
 * then play will start immediately when this function is called. <br>
 * <br>
  * Calling this function without calling the ::criManaPlayer_DecodeHeader or ::criManaPlayer_Prepare function
 * will prevent the Mana player handle status from becoming CRIMANAPLAYER_STATUS_STOP or CRIMANAPLAYER_STATUS_PLAYEND. 
 * 
 * \par Notes: 
 * If you have registered a data request callback function, you can omit presetting the movie data. 
 * 
 * \sa criManaPlayer_GetStatus, criManaPlayer_DecodeHeader, criManaPlayer_Prepare
 */
void CRIAPI criManaPlayer_Start(CriManaPlayerHn player);

/*EN
 * \brief Requests play to stop
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \par Call conditions: 
 * This is not thread safe. 
 * \par Description: 
 * Requests to stop movie playback. This is a non-blocking function. Not all stop processes will be executed with this function. <br>
 * Once this function is called, operate the normal main loop until the playback status becomes CRIMANAPLAYER_STATUS_STOP. <br>
 * More specifically, you will need to call the ::criMana_ExecuteMain function, ::criMana_ExecuteVideoProcess function, and so on as normal. <br>
 * <br>
 * When the playback status becomes CRIMANAPLAYER_STATUS_ERROR, call this function and wait for CRIMANAPLAYER_STATUS_STOP. <br>
 * 
 * \par Notes: 
 * The API name from the criManaPlayer_RequestStop was changed from Ver.1.10. 
 *
 * \sa criManaPlayer_GetStatus
 */
void CRIAPI criManaPlayer_Stop(CriManaPlayerHn player);

/*EN
 * \brief Stop playback (complete return API)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \par Call conditions: 
 * This is not thread safe. 
 * \par Description: 
 * Stops movie playback. This function is a blocking function. When the process returns from this function the player will be in the stopped status. <br>
 * Streaming stop standby will occur in this function, so it may block the process for several dozen milliseconds. <br>
 * Only implement this function if you do not mind the timing of scene transitions and other game processes to be delayed. <br>
 * <br>
 * Use the ::criManaPlayer_Stop function if there will be problems with main processes being blocked. <br>
 *
 * \sa criManaPlayer_GetStatus
 */
void CRIAPI criManaPlayer_StopAndWaitCompletion(CriManaPlayerHn player);

/*EN
 * \brief Switch play pause
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	sw	Pause switch (CRI_ON:Pause, CRI_OFF:Unpause)
 * \par Call conditions: 
 * This is thread safe. 
 * \par Description: 
 * The operation of this function depends on the argument. <br>
 * If the argument sw is CRI_ON(1), then it will pause. If the argument sw is CRI_OFF(0), then it will resume playback. <br>
 * <br>
 * File reading and decoding stop will not occur immediately after this function is called. <br>
 * Calling ::criManaPlayer_Stop will cancel the pause status.
 */
void CRIAPI criManaPlayer_Pause(CriManaPlayerHn player, CriBool sw);

/*EN
 * \brief Get play pause status
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \return CriBool Pause status
 * \par Call conditions: 
 * This is thread safe. 
 * \par Description: 
 * Gets the current Mana player pause status. 
 * If the return value is CRI_ON(1), then it is paused. If the argument sw is CRI_OFF(0), then pause has been cancelled. <br>
 * <br>
 */
CriBool CRIAPI criManaPlayer_IsPaused(CriManaPlayerHn player);

/*EN
 * \brief Switch play loop
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	sw		Loop switch (CRI_FALSE:No loop, CRI_TRUE:Loop present)
 * \par Call conditions: 
 * This is thread safe. 
 * \par Description: 
 * Sets whether there is loop play. Loop play is OFF by default. <br>
 * When turning loop play ON, the handle status will not become CRIMANAPLAYER_STATUS_PLAYEND, even if the movie is played to the end.
 * Rather, the movie still repeats playback from the beginning. <br>
 * <br>
 * When loop play is set to OFF, the handle status will transition to CRIMANAPLAYER_STATUS_PLAYEND
 * when the loaded movie is played to the end. <br>
 * If you turn loop play OFF during playback, depending on the timing it will be executed by the next repeat playback,
 * and the movie being played will not stop at the end.
 */
void CRIAPI criManaPlayer_Loop(CriManaPlayerHn player, CriBool sw);

/*EN
 * \brief Get playback time
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[out]	count	Timer count
 * \param[out]	unit	Number of timer counts per second.  Time is in second units because count / unit. 
 * \par Call conditions: 
 * This is not thread safe. 
 * \par Description: 
 * Gets timer time. Time is displayed in either count or unit variables. <br>
 * Time is returned in second units because count / unit. <br>
 * Time will be returned as zero (timer count will be zero) before playback begins or after playback ends. <br>
 * This function will only return the timer time specified by the master timer. It does not return video frame time. <br>
 * Reference the CriManaFrameInfo structure of the original display time of the video frame when it was grabbed.
 */
void CRIAPI criManaPlayer_GetTime(CriManaPlayerHn player, CriUint64 *count, CriUint64 *unit);

/*EN
 * \brief Get input buffer size
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \return		CriSint32	Input buffer size [byte]
 * \par Call conditions: 
 * This is not thread safe. 
 * \par Description: 
 * Gets the input buffer size of the Mana player. <br>
 * You can get a valid input buffer size value after CRIMANAPLAYER_STATUS_PREP. <br>
 * \par Notes: 
 * This function is a debug function that can only be used in applications to get information. <br>
 *
 * \sa criManaPlayer_SetBufferingTime, criManaPlayer_GetInputBufferRemainSize
 */
CriSint32 CRIAPI criManaPlayer_GetInputBufferSize(CriManaPlayerHn player);

/*EN
 * \brief Get amount of remaining data in input buffer
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \return		CriSint32	Amount of remaining data in input buffer [byte]
 * \par Call conditions: 
 * This is not thread safe. 
 * \par Description: 
 * Gets the amount of data remaining in the input buffer. <br>
 * You can get a valid value after CRIMANAPLAYER_STATUS_PREP. <br>
 * \par Notes: 
 * This function is a debug function that can only be used in applications to get information. <br>
 * <br>
 * When there is time lapse or time skipping in a video, you can use this function to check whether there is any data
 * remaining in the player's input buffer during playback. <br>
 * If the amount of data remaining is zero for an extended time, even during playback, then some error may be delaying
 * the supply of data. <br>
 *
 * \sa criManaPlayer_SetBufferingTime, criManaPlayer_GetInputBufferRemainSize
 */
CriSint32 CRIAPI criManaPlayer_GetInputBufferRemainSize(CriManaPlayerHn player);

/*EN
 * \brief Specify the number of internal video buffers (frame pools)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	npools	Number of internal video buffers (minimum of one)
 * \par Call conditions: 
 * Call before the Mana player handle status is CRIMANAPLAYER_STATUS_WAIT_PREP. <br>
 * This function will affect the playback work parameters, so call before the ::criManaPlayer_GetPlaybackWorkParam function. <br>
 * <br>
 * This is not thread safe. <br>
 * \par Description: 
 * Specifies the number of video buffers in the Mana player. <br>
 * These internal buffers are for storing the results of decoding and are called frame pools. <br>
 * You can precede with video decoding early the more frame pools there are,
 * which more easily allows for smooth playback when decoding load fluctuations are
 * large or when there are large fluctuations in the CPU time that can be used for decoding. <br>
 * <br>
 * The number of default frame pools is one.<br>
 */
void CRIAPI criManaPlayer_SetNumberOfFramePools(CriManaPlayerHn player, CriUint32 npools);

/*EN
 * \brief Specify input data buffering time
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	sec		Buffering time. The unit is seconds. 
 * \par Call conditions: 
 * Call before the Mana player handle status is CRIMANAPLAYER_STATUS_WAIT_PREP. <br>
 * This function will affect the playback work parameters, so call before the ::criManaPlayer_GetPlaybackWorkParam function. <br>
 * <br>
 * This is not thread safe. <br>
 * \par Description: 
 * Specifies seconds as the unit of time for the amount of input data being buffered during streaming. <br>
 * The Mana player determines the size of the reading buffer from the buffering time, movie bit rate, and so on. <br>
 * <br>
 * The default buffering time is one second. <br>
 * <br>
 * When the buffering time is specified as 0.0f, the buffering time will be the library's default value.<br>
 */
void CRIAPI criManaPlayer_SetBufferingTime(CriManaPlayerHn player, CriFloat32 sec);

/*EN
 * \brief Specify minimum buffer size
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	min_buffer_size		Minimum buffer size [byte]
 * \par Call conditions: 
 * Call before the Mana player handle status is CRIMANAPLAYER_STATUS_WAIT_PREP. <br>
 * This function will affect the playback work parameters, so call before the ::criManaPlayer_GetPlaybackWorkParam function. <br>
 * <br>
 * This is not thread safe. <br>
 * \par Description: 
 * Specifies the minimum buffer size for the movie data. <br>
 * When the minimum buffer size is specified, any input buffer larger than the specified size is guaranteed to be allocated in the Mana player. <br>
 * <br>
 * You do not need to use this function for simple playback. Use it for concatenated play of movies with extreme differences in bit rates. <br>
 * <br>
 * When the minimum buffer size has been specified as zero, its value will be what the movie data contains. (Default)<br>
 * \par Notes: 
 * The minimum buffer size set by this function will not be reflected in the movie data obtained by the ::criManaPlayer_GetMovieInfo function. <br>
 * The ::criManaPlayer_GetMovieInfo function can get the original movie data information. <br>
 *
 * \sa criManaPlayer_GetInputBufferSize
 */
void CRIAPI criManaPlayer_SetMinBufferSize(CriManaPlayerHn player, CriUint32 min_buffer_size);

/*EN
 * \brief Set streaming flag
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	streaming_flag	Streaming flag
 * \par Call conditions: 
 * This function can be called only when the Mana player handle status is in the STOP or PLAYEND. <br>
 * <br>
 * This is thread safe. <br>
 * \par Description: 
 * Determines whether there will be streaming in the specified Mana player. <br>
 * The default is CRI_TRUE. When CRI_FALSE is specified, the Mana player will be exclusively on-memory playback.  <br>
 * <br>
 * \par Notes: 
 * A playback error will occur when streaming begins if the streaming flag is disabled.
 */
void CRIAPI criManaPlayer_SetFileStreamingFlag(CriManaPlayerHn player, CriBool streaming_flag);

/*EN
 * \brief Specify maximum resolution
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	max_width	Maximum movie width
 * \param[in]	max_height	Maximum movie height
 * \par Call conditions: 
 * This function can be called only when the Mana player handle status is in the STOP or PLAYEND. <br>
 * <br>
 * This is thread safe. <br>
 * \par Description: 
 * Specifies the maximum resolution of the movie to be played by the player.<br>
 */
void CRIAPI criManaPlayer_SetMaxMovieSize(CriManaPlayerHn player, CriSint32 max_width, CriSint32 max_height);

/*EN
 * \brief Specify maximum resolution
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	max_data_size	Maximum resolution [byte]
 * \par Call conditions: 
 * Call this function before starting playback (::criManaPlayer_Prepare function or ::criManaPlayer_Start function). <br>
 * <br>
 * This is thread safe. <br>
 * \par Description: 
 * Specifies the maximum picture data size of the movie data to be played by the player. <br>
 * Only use this API for concatenated play of a specific codec. (Unnecessary for the Sofdec.Prime codec)<br>
 * <br>
 * When the maximum picture data size is specified as zero, its value will be what the maximum picture data size contains. <br>
 * <br>
 * \sa criManaPlayer_SetDataRequestCallback
 */
void CRIAPI criManaPlayer_SetMaxPictureDataSize(CriManaPlayerHn player, CriUint32 max_data_size);

/*EN
 * \brief Execute decision to automatically skip a decoded frame
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[in]	frame_info	Frame information structure
 * \par Call conditions: 
 * This function can be called only when the Mana player handle status is in the STOP or PLAYEND. <br>
 * <br>
 * This is not thread safe. <br>
 * \par Description: 
 * Decides to skip decoded frames on the app side. 
 * The frame will automatically skip internally when it is decided by the 
 * function that slowdown will occur due to playback load. 
 While visually there will be stuttering, it will make it easier to prevent sound jumping. 
 * \par Caution: 
 * - Do not use together with the criMana_SetDecodeSkipFlag function. 
 *   (Set so that the criMana_SetDecodeSkipFlag function is not called or so that it is CRI_FALSE)<br>
 * - Calling the function multiple times for the same frame information structure will implement the request for skipping multiple times,
 *   so be sure that the information for each frame
 *   is called only one time.
<br>
 */
void criManaPlayer_ExecuteAutoSkip(CriManaPlayerHn player, CriManaFrameInfo *frame_info);

/***********************************/
/*         Audio related          */
/***********************************/

/*EN
 * \brief Set the main audio track number
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	track	Track number
 * \par Call conditions: 
 * Call this function before starting playback (::criManaPlayer_Prepare function or ::criManaPlayer_Start function). <br>
 * <br>
 * This function is not thread safe. 
 * \par Description: 
 * Sets the audio to be played when a movie has multiple audio tracks. <br>
 * It will play the lowest numbered audio track if this function is not executed. <br>
 * Audio will not play if a track number for which there is no data is specified. <br>
 * <br>
 * If you specify CRIMANA_AUDIO_TRACK_OFF as the track number, then audio will not play
 * even if audio is included in the movie. <br>
 * <br>
 * If you want to set defaults (to play the lowest numbered audio channel),
 * then specify CRIMANA_AUDIO_TRACK_AUTO as the channel. <br>
 * <br>
 * Audio track information is analyzed by the header before playback begins, so the information can be obtained at random times. 
 *
 * \par Notes: 
 * Changing tracks during playback is not supported. Register the frame number before changing the track and
 * use seek playback. 
 *
 * \sa criManaPlayer_GetMovieInfo, criManaPlayer_DecodeHeader
 */
void  CRIAPI criManaPlayer_SetAudioTrack(CriManaPlayerHn player, CriSint32 track);

/*EN
 * \brief Set the subaudio track number
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	track	Subaudio track number
 * \par Call conditions: 
 * Call this function before starting playback (::criManaPlayer_Prepare function or ::criManaPlayer_Start function). <br>
 * <br>
 * This function is not thread safe. 
 * \par Description: 
 * Sets the subaudio track number. 
 * <br>
 * In playing the subaudio, you will need to enable the sub_audio_params parameters of the CriManaPlaybackExWorkConfig structure specified by
 * the ::criManaPlayer_SetPlaybackWork function after specifying the track number with this function. <br>
 * <br>
 * Nothing from the subaudio will play if the main audio is specified as the same track as the subaudio track. <br>
 * If there is no audio in the specified track number, then it is OFF.
 */
void CRIAPI criManaPlayer_SetSubAudioTrack(CriManaPlayerHn player, CriSint32 track);

/*EN
 * \brief Set the extra audio track index
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	track	Extra audio track index
 * \par Calling condition:
 * Please call this function before starting playback.<br>
 * <br>
 * This function is not thread-safe.
 * \par Description: 
 * Sets the index of the track containing the extra audio.
 * <br>
 * To play the extra audio, after specifying the track index with this function, you need to activate
 * the "extra_audio_params" of the CriManaPlaybackExWorkConfig structure specified by the ::criManaPlayer_SetPlaybackWork function.<br>
 * <br>
 * If you specify the same track as the main audio track, nothing will be played from the extra audio.<br>
 * It turns it OFF if there is no audio at the specified track index.
 */
void CRIAPI criManaPlayer_SetExtraAudioTrack(CriManaPlayerHn player, CriSint32 track);

/*EN
 * \brief Set audio volume (main audio track)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	volume	Volume
 * \par Call conditions: 
 * This function is not thread safe. 
 * \par Description: 
 * Sets the output sound volume of the movie's main audio track. <br>
 * <br>
 * Specifies the volume at an actual value between a range of 0.0F and 1.0f. <br>
 * The volume is a scaling factor of the amplitude of the sound data. (Not in decibel units.) <br>
 * For example, specifying 1.0f will output the original sound at its original volume. <br>
 * Specifying 0.0f will mute the sound. (There will be no sound.) <br>
 * The default value for volume is 1.0f. <br>
 * <br>
 * Specifying a value outside the 0.0f to 1.0f range will clip at the minimum and maximum values. 
 *
 * \sa criManaPlayer_GetVolume
 */
void CRIAPI criManaPlayer_SetVolume(CriManaPlayerHn player, CriFloat32 volume);

/*EN
 * \brief Get audio volume (main audio track)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \return CriFloat32 Volume
 * \par Description: 
 * Gets the output sound volume of the movie's main audio track. 
 * Volume range is 0.0f to 1.0f. 
 * 
 * \sa criManaPlayer_SetVolume
 */
CriFloat32 CRIAPI criManaPlayer_GetVolume(CriManaPlayerHn player);

/*EN
 * \brief Get AtomExPlayerHn (main audio track)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \return CriAtomExPlayerHn CriAtomExPlayer handle
 * \par Description: 
 * Get the ::criAtomExPlayerHn that CriManaPlayer uses for audio playback.
 * If CRI_TRUE is specified for the "use_atomex_player" member of the CriManaPlayerConfig structure,
 * this function will return NULL except for a CriManaPlayerHn created with the ::criManaPlayer_CreateWithConfig function.
 * \attention
 * Do not discard the ::CriAtomExPlayerHn acquired by this function.
 */
CriAtomExPlayerHn CRIAPI criManaPlayer_GetAtomExPlayer(CriManaPlayerHn player);

/*EN
 * \brief Get AtomExPlaybackId (main audio track)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \return CriAtomExPlaybackId CriAtomExPlaybackId
 * \par Description: 
 * Get the ::CriAtomExPlaybackId of the main audio track of the movie.
 * If CRI_TRUE is specified for the "use_atomex_player" member of the CriManaPlayerConfig structure,
 * this function will return CRIATOMEX_INVALID_PLAYBACK_ID except for a CriManaPlayerHn created with the ::criManaPlayer_CreateWithConfig function.
 * \attention
 * Calling this function is deprecated.
 */
CriAtomExPlaybackId criManaPlayer_GetAtomExPlaybackId(CriManaPlayerHn player);

/*EN
 * \brief Set audio volume (subaudio track)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	volume	Volume
 * \par Call conditions: 
 * This function is not thread safe. 
 * \par Description: 
 * Specifies the output sound volume of the movie's subaudio track. <br>
 * <br>
 * Specifies the volume at an actual value between a range of 0.0F and 1.0f. <br>
 * The volume is a scaling factor of the amplitude of the sound data. (Not in decibel units.) <br>
 * For example, specifying 1.0f will output the original sound at its original volume. <br>
 * Specifying 0.0f will mute the sound. (There will be no sound.) <br>
 * The default value for volume is 1.0f. <br>
 * <br>
 * Specifying a value outside the 0.0f to 1.0f range will clip the minimum and maximum values. 
 *
 * \sa criManaPlayer_GetSubAudioVolume
 */
void CRIAPI criManaPlayer_SetSubAudioVolume(CriManaPlayerHn player, CriFloat32 volume);

/*EN
 * \brief Get audio volume (subaudio track)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \return CriFloat32 Volume
 * \par Description: 
 * Gets the output sound volume of the movie's subaudio track. 
 * Volume range is 0.0f to 1.0f. 
 * 
 * \sa criManaPlayer_SetSubAudioVolume
 */
CriFloat32 CRIAPI criManaPlayer_GetSubAudioVolume(CriManaPlayerHn player);

/*EN
 * \brief Set the audio volume of the extra audio track
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	volume	Volume
 * \par Call conditions: 
 * This function is not thread safe. 
 * \par Description: 
 * Specifies the output volume of the movie's extra audio track. <br>
 * <br>
 * Specifies the volume in the range from 0.0F to 1.0f. <br>
 * The volume is a scaling factor of the amplitude of the sound data (i.e. it is not expressed in decibels). <br>
 * For example, specifying 1.0f will output the sound at its original volume. <br>
 * Specifying 0.0f will mute the sound. (There will be no sound.) <br>
 * The default value for the volume argument is 1.0f. <br>
 * <br>
 * Specifying a value outside of the 0.0f to 1.0f range will clip to the minimum and maximum values. 
 *
 * \sa criManaPlayer_GetExtraAudioVolume
 */
void CRIAPI criManaPlayer_SetExtraAudioVolume(CriManaPlayerHn player, CriFloat32 volume);

/*EN
 * \brief Get the audio volume of the extra audio track
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \return CriFloat32 Volume
 * \par Description: 
 * Gets the output sound volume of the movie's extra audio track. 
 * The volume is in the range from 0.0f to 1.0f. 
 * 
 * \sa criManaPlayer_SetExtraAudioVolume
 */
CriFloat32 CRIAPI criManaPlayer_GetExtraAudioVolume(CriManaPlayerHn player);

/*EN
 * \brief Get 2D pan (main audio track)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	ch			Channel number
 * \param[in]	pan			Pan setting (-1.0f~1.0f)
 * \par Call conditions: 
 * This function is not thread safe. 
 * \par Description: 
 *Specifies the 2D pan (left-right sound source localization) of the main audio track. <br>
 * You can freely control the sound source localization for monaural or stereo sounds 
 * by executing this function. <br>
 * <br>
 * Specifies the channel number of the second argument as the "sound data channel number." <br>
 * (When playing monaural sounds)<br>
 * <ul><li>Specifies the channel number as zero. </li></ul>
 * (When playing stereo sounds)<br>
 * <ul>
 *  <li>Channel number 0: Left sound
 *  <li>Channel number 1: Right sound
 * </ul><br>
 * Specifies in what position the specified channel number data will be localized in the pan setting
 * of the third argument. <br>
 * The pan setting is specified as an actual value between a range of -1.0f to 1.0f. <br>
 * Specifying the sound source as a negative value will localize the sound source on the left (the smaller the value, the farther left it will move). Specifying the sound 
 * source as 0.0f will localize it in the center, while specifying a positive value will localize it on the right (the larger the value, the farther right it will move). <br>
 * (A convenient value is -1.0f for the left, 0.0f for the center, and 1.0f for the right.) <br>
 * \par Notes: 
 * If the actual applicable value exceeds 1.0f, it will be clipped to 1.0f. <br>
 * In the same way, if the actual applicable value is less than -1.0f then it will be clipped to -1.0f. <br>
 * <br>
 * Specifying channel numbers that do not rely on sound data during playback will ignore these settings. <br>
 * In the same way, specifying anything above channel 2 will disable it. 
 *
 * \sa criManaPlayer_GetPan
 */
void CRIAPI criManaPlayer_SetPan(CriManaPlayerHn player, CriSint32 ch, CriFloat32 pan);

/*EN
 * \brief Get 2D pan (main audio track)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	ch			Channel number
 * \return CriFloat32 Pan setting
 * \par Description: 
 * Gets the pan settings of the specified channel number of the main audio track. <br>
 * Pan setting range is -1.0f to 1.0f. <br>
 * 
 * \sa criManaPlayer_SetPan
 */
CriFloat32 CRIAPI criManaPlayer_GetPan(CriManaPlayerHn player, CriSint32 ch);

/*EN
 * \brief Reset send level (main audio track)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \par Description: 
 * Resets the send level settings of the main audio track. <br>
 * You will clear all previously set send level settings by executing this function. <br>
 * <br>
 * Executing this function during movie playback will clear all send levels that were sent and will prevent all of the<br>
 * speakers from outputting sound. 
 * \par Notes: 
 * There are two send level settings: Automatic and Manual. <br>
 * Resetting the send level with this function directly after creating the Mana player
 * will change the send level setting to Automatic. <br>
 * (Refer to the ::criManaPlayer_SetSendLevel function 
 * explanation for routing when set to Automatic.) <br>
 * \sa criManaPlayer_SetSendLevel
 */
void CRIAPI criManaPlayer_ResetSendLevel(CriManaPlayerHn player);

/*EN
 * \brief Set send level (main audio track)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[in]	ch			Channel number
 * \param[in]	spk			Speaker ID
 * \param[in]	level		Volume setting (0.0f to 1.0f)
 * \par Description: 
 * Specifies the send level of the main audio track. <br>
 * The send level is a way to specify from which speaker and at what volume 
 * the sound from each sound data channel will be output. <br>
 * <br>
 * The "ch" argument specifies the sound data channel number. <br>
 * The "spk" argument specifies to which speaker the specified channel of sound data will be output.
 * The "level" argument specifies the volume at which the data of the specified sound channel will be output on that speaker. <br>
 * The volume is a value between 0.0f and 1.0f. <br>
 * It is expressed as a scaling factor of the amplitude of the sound data. (It is not expressed in decibel units.) <br>
 * For example, specifying 1.0f will output the original sound at its original volume. <br>
 * When 0.5f is specified, the sound will be output at half the amplitude of the waveform of
 * the original sound data (-6dB). <br>
 * Specifying 0.0f will mute the sound. (There will be no sound.) 
 * <br>
 * For example, specify the following arguments if you want to output the data from the first sound channel at
 * full volume (1.0f) on the right speaker. 
 * \code
 * criManaPlayer_SetSendLevel(player, 0, CRIATOM_SPEAKER_FRONT_RIGHT, 1.0f);
 * \endcode
 * <br>
 * Thanks to this function, you can output one channel of the audio data to multiple speakers at different 
 * volumes. <br>
 * For example, the code below shows what to do if you want to output the data from the second channel to the left speaker at a volume of 0.3f, 
 * to the right speaker at a volume of 0.5f, and to the center speaker at a volume 0.7f. 
 * \code
 * criManaPlayer_SetSendLevel(player, 1, CRIATOM_SPEAKER_FRONT_LEFT, 0.3f);
 * criManaPlayer_SetSendLevel(player, 1, CRIATOM_SPEAKER_FRONT_RIGHT, 0.5f);
 * criManaPlayer_SetSendLevel(player, 1, CRIATOM_SPEAKER_FRONT_CENTER, 0.7f);
 * \endcode
 * <br>
* You can reset the send level values you set with the
 * ::criManaPlayer_ResetSendLevel function. <br>
 * \par Notes: 
 * There are two send level settings: Automatic and Manual. <br>
 * Resetting the send level with the ::criManaPlayer_ResetSendLevel function directly after creating the Mana player
 * will cause the send level setting to change to Automatic. <br>
 * Executing this function will cause the send level setting to change to Manual. <br>
 * <br>
 * The Mana player will route sound as described below when set to Automatic. <br>
 * <br>
 * - (When playing monaural sound)<br>
 * Sound from channel zero will be output to the left speaker,
 * and sound from channel one will be output to the right speaker. <br>
 * <br>
 * - (When playing stereo sound)<br>
  * Sound from channel zero will be output to the left speaker,
 * and sound from channel one will be output to the right speaker. <br>
 * <br>
 * - (When playing 4ch sound)<br>
 * Sound from channel zero will be output to the left speaker, sound from channel one will be output to the right speaker,
 * sound from channel two will be output to the left surround speaker,
 * and sound from channel three will be output to the right surround speaker. <br>
 * <br>
 * - (When playing 5.1ch sound)<br>
 * Sound from channel zero will be output to the left speaker, sound from channel 1 will be output to the right speaker,
 * sound from channel two will be output to the center speaker, sound from channel three will be output to the LFE,
 * sound from channel four will be output to the left surround speaker,
 * and sound from channel five will be output to the right surround speaker. <br>
 * \par
 * Meanwhile, using this function on Manual will cause sound to be output with the specified routing, 
 * regardless of the number of sound data channels. <br>
 * (It will not output sound from channels for which the sound levels have not been set.) <br>
 * Execute the ::criManaPlayer_ResetSendLevel function if you want to clear the send levels and
 * return the routing to Automatic. <br>
 * <br>
 * You can use this function independently from the ::criManaPlayer_SetVolume function.
 * For example, if you set the volume to 0.5f in this function and also to 0.5f by using the ::criManaPlayer_SetVolume function,
 * then the resulting sound volume will be the multiplication of both values. <br>
 * (The operation is 0.5f x 0.5f = 0.25f.) 
 * \attention
 * If the send level has only been set for some channels, even
 * though the sound data contains multi-channel data, then no sound will be output from channels 
 * where send levels have not been set. <br>
 * <br>
 * Do not combine the use of this function with the ::criManaPlayer_SetPan function. <br>
 * Using both together may cause functions executed later to overwrite the settings. <br>
 * Use only either this function or the ::criManaPlayer_SetPan function when
 * controlling sound source localization. <br>
 * (Use this function when using 3D pan and the ::criManaPlayer_SetPan function when 
 * only using 2D pan.) 
 * <br>
 * This function may not be supported on some platforms. <br>
 * (Implementation of this function may be difficult depending on the sound library of the platform, so it
 * cannot be used on all operating systems.) <br>
 * Refer to the information contained in each platform's manual to know whether this function can be used or not. 
 * \sa criManaPlayer_SetVolume, criManaPlayer_SetPan, criManaPlayer_ResetSendLevel
 */
void CRIAPI criManaPlayer_SetSendLevel(
	CriManaPlayerHn player, CriSint32 ch, CriAtomSpeakerId spk, CriFloat32 level);

/*EN
 * \brief Reset send level (subaudio track)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \par Description: 
 * Resets the send level settings of the subaudio track. <br>
 * You will clear all previously set send level settings by executing this function. <br>
 * \par Notes: 
 * This function has the same operating specifications as ::criManaPlayer_ResetSendLevel. <br>
 * The settings for this function are only for subaudio tracks. 
 * \sa criManaPlayer_ResetSendLevel
 */
void CRIAPI criManaPlayer_ResetSubAudioSendLevel(CriManaPlayerHn player);

/*EN
 * \brief Set send level (subaudio track)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[in]	ch			Channel number
 * \param[in]	spk			Speaker ID
 * \param[in]	level		Volume (0.0f~1.0f)
 * \par Description: 
 * Specifies the send level of the subaudio track. <br>
 * Send level is a way of specifying from which speaker and at what volume 
 * sound from each sound data channel will be output. <br>
 * <br>
 * \par Notes: 
 * This function has the same operating specifications as ::criManaPlayer_SetSendLevel. <br>
 * The settings for this function are only for subaudio tracks. 
 * \sa criManaPlayer_SetSubAudioSendLevel
 */
void CRIAPI criManaPlayer_SetSubAudioSendLevel(
	CriManaPlayerHn player, CriSint32 ch, CriAtomSpeakerId spk, CriFloat32 level);

/*EN
 * \brief Reset the send level of the extra audio track
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \par Description: 
 * Resets the send level of the extra audio track. <br>
 * You will clear all previously send level settings by executing this function. <br>
 * \par Notes: 
 * This function works in the same way than ::criManaPlayer_ResetSendLevel. <br>
 * The settings for this function are only for extra audio tracks. 
 * \sa criManaPlayer_ResetSendLevel
 */
void CRIAPI criManaPlayer_ResetExtraAudioSendLevel(CriManaPlayerHn player);

/*EN
 * \brief Set the send level of the extra audio track
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[in]	ch			Channel number
 * \param[in]	spk			Speaker ID
 * \param[in]	level		Volume (0.0f~1.0f)
 * \par Description: 
 * Specifies the send level of the extra audio track. <br>
 * Setting the send level is a way to specify from which speaker and at what volume 
 * the sound from each channel will be output. <br>
 * <br>
 * \par Notes: 
 * This function works in the same way than ::criManaPlayer_SetSendLevel. <br>
 * The settings for this function are only for extra audio tracks. 
 * \sa criManaPlayer_SetSubAudioSendLevel
 */
void CRIAPI criManaPlayer_SetExtraAudioSendLevel(
	CriManaPlayerHn player, CriSint32 ch, CriAtomSpeakerId spk, CriFloat32 level);

/*EN
 * \brief Set bus send level (main audio track)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[in]	bus_name	Bus name
 * \param[in]	level		Send level value (0.0f to 1.0f)
 * \par Description: 
 * Specifies the bus send level of the main audio track. <br>
 * The bus send level is a way to specify how much sound is sent to a bus. <br>
 * The sound will begin to play according to prior bus send level settings. <br>
 * Any bus send level change during playback will be reflected immediately. <br>
 * <br>
 * The second argument of the function references the bus we want to send the sound through. <br>
 * The third argument of the function is the level (volume) of the sound sent through the specified bus. <br>
 * <br>
 * The range and the haof send level values and their handling are the same as with volume. Refer to the ::criManaPlayer_SetVolume function. 
 * \par Notes: 
 * You can send volume down multiple buses by calling this function multiple times. <br>
 * \sa criManaPlayer_SetVolume
 */
void CRIAPI criManaPlayer_SetBusSendLevelByName(
	CriManaPlayerHn player, const CriChar8* bus_name, CriFloat32 level);

/*EN
 * \brief Set bus send level (sub audio track)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[in]	bus_id		Bus ID
 * \param[in]	level		Send level (0.0f to 1.0f)
 * \par Description: 
 * Specifies the bus send level of the sub audio track. <br>
 * The bus send level is a way to specify how much sound is sent to a bus. <br>
 * The sound will begin to play according to prior bus send level settings. <br>
 * Any bus send level change during playback will be reflected immediately. <br>
 * <br>
 * \par Notes: 
 * This function has the same operating specifications as ::criManaPlayer_SetBusSendLevelByName. <br>
 * However this function only affects sub audio tracks. 
 * \sa criManaPlayer_SetBusSendLevelByName
 */
void CRIAPI criManaPlayer_SetSubAudioBusSendLevelByName(
	CriManaPlayerHn player, const CriChar8* bus_name, CriFloat32 level);

/*EN
 * \brief Set the bus send level of the extra audio track
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[in]	bus_id		Bus ID
 * \param[in]	level		Send level (0.0f to 1.0f)
 * \par Description: 
 * Specifies the bus send level of the extra audio track. <br>
 * The bus send level is a way to specify how much sound is sent to a bus. <br>
 * The sound will begin to play according to the prior bus send level. <br>
 * Any bus send level change during playback will be reflected immediately. <br>
 * <br>
 * \par Notes: 
 * This function works in the same way than ::criManaPlayer_SetBusSendLevelByName. <br>
 * However this function only affects extra audio tracks. 
 * \sa criManaPlayer_SetBusSendLevelByName
 */
void CRIAPI criManaPlayer_SetExtraAudioBusSendLevelByName(
	CriManaPlayerHn player, const CriChar8* bus_name, CriFloat32 level);

/* criManaPlayer_ResetBusSendLevelAll */
/*EN
 * \brief Bus send level reset (all tracks)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \par Description: 
 * Resets the bus send levels for all main, sub audio, and extra audio tracks. <br>
 * If you reset the bus send level during playback, the setting value will be reflected immediately. <br>
 * <br>
 * \par Notes: 
 * This function has no effect on a player created by setting CRI_TRUE to the CriManaPlayerConfig.use_atomex_player .
*/
void CRIAPI criManaPlayer_ResetBusSendLevelAll(
	CriManaPlayerHn player);

/*EN
 * \brief Set sound renderer type
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	sound_renderer_type	Set sound renderer type
 * \par Call conditions: 
 * This is not thread safe. 
 * 
 * \par Description: 
 * Specifies an output sound renderer for the sound that is played by the Mana player. <br>
 * Output sound renderer type settings are reflected in both the main audio and subaudio tracks. <br>
 * <br>
 * You cannot change the sound renderer type during playback. If you specify the sound renderer type during playback,
 * the settings will be reflected in the next movie to be played. <br>
 * <br>
 * \attention
 * You can only specify the following two when using a pre-CRI Mana Ver.1.68.02 version. 
 * <ul>
 *   <li>CRIATOM_SOUND_RENDERER_NATIVE
 *   <li>CRIATOM_SOUND_RENDERER_ASR
 * </ul><br>
 */
void criManaPlayer_SetSoundRendererType(CriManaPlayerHn player, CriAtomSoundRendererType sound_renderer_type);

/*EN
 * \brief Set the ASR rack ID
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[in]	asr_rack_id	ASR rack ID
 * \par Call conditions: 
 * This is not thread safe. 
 * 
 * \par Description: 
 * Specifies an output ASR rack ID for the sound that is played by the Mana player.. <br>
 * Output ASR rack settings are reflected in both the main audio and subaudio tracks. <br>
 * <br>
 * Enabled only when the output sound renderer type is CRIATOM_SOUND_RENDERER_ASR. <br>
 * You cannot change the ASR rack ID during playback. If you specify the ASR rack ID during playback,
 * the settings will be reflected in the next movie to be played.<br>
 */
void criManaPlayer_SetAsrRackId(CriManaPlayerHn player, CriSint32 asr_rack_id);

/***********************************/
/*     Frame acquisition related     */
/***********************************/

/*EN
 * \brief Refer to decoded frame information
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[out]	frame_info	Frame information structure
 * \return CriBool Frame information reference results (CRI_TRUE: Reference successful, CRI_FALSE: Reference failed)
 * \par Call conditions: 
 * Call this function when the Mana player handle status is CRIMANAPLAYER_STATUS_PLAYING. 
 * CRI_FALSE will always be returned in all other situations. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * References the frame information structure of a decoded video frame. 
 * You can get the following frame information if there is a decoded frame in the Mana player's frame pool. <br>
 * <br>
 * In order to grab the video frame, first use this function to determine whether there is a decoded frame.
 * Next, use the ::criManaPlayer_IsFrameOnTime function to check whether the frame has reached the playback time. <br>
 * <br>
 * As long as you do not call ::criManaPlayer_DiscardFrame, this function will get the same frame information. 
 *
 * \sa criManaPlayer_IsFrameOnTime
 */
CriBool CRIAPI criManaPlayer_ReferFrame(CriManaPlayerHn player, CriManaFrameInfo *frame_info);

/*EN
 * \brief Determine frame time
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[in]	frame_info	Frame information structure
 * \return CriBool Return CRI_TRUE(1) if the input frame information already has a time stamp. <br>
 * \par Call conditions: 
 * Call this function when the Mana player handle status is CRIMANAPLAYER_STATUS_PLAYING. 
 * CRI_FALSE will always be returned in all other situations. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Determines the time stamp of the frame referenced by the ::criManaPlayer_ReferFrame function. 
 * This time stamp is determined based on the master timer time. 
 * 
 * \sa criManaPlayer_ReferFrame
 */
CriBool CRIAPI criManaPlayer_IsFrameOnTime(CriManaPlayerHn player, const CriManaFrameInfo *frame_info);

/*EN
 * \brief Keep frame
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[out]	frame_info	Frame information structure
 * \return CriBool Whether or not frame information is kept.
 * \par Call conditions: 
 * This is not thread safe. 
 * \par Description: 
 * If there is a decoded video frame, then the application can keep the 
 * decoded frame. Calling this function will allow the next frame in the frame pool to be referenced without 
 * destroying the current frame. In this way, the application can manage multiple frames. <br>
 * <br>
 * The Mana player will maintain the decoding results as long as the kept frame is not destroyed with the ::criManaPlayer_Discard or 
 * ::criManaPlayer_DiscardOneKeepFrame function. Therefore, the frame can be used
 * as a drawing while kept. <br>
 * <br>
 * Use this function to grab multiple frames and use them as drawings, or when you want to 
 * temporarily keep frames on the system with drawing latency. 
 *
 * \sa criManaPlayer_ReferFrame, criManaPlayer_GetNumberOfKeepFrames, criManaPlayer_DiscardOneKeepFrame
 */
CriBool CRIAPI criManaPlayer_KeepFrame(CriManaPlayerHn player, CriManaFrameInfo *frame_info);

/*EN
 * \brief Get the number of kept frames
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \return CriSint32 Number of kept frames
 * \par Call conditions: 
 * This is not thread safe. 
 * \par Description: 
 * Gets the number of frames that the application is currently keeping using the ::criManaPlayer_KeepFrame function. 
 *
 * \sa criManaPlayer_KeepFrame
 */
CriSint32 CRIAPI criManaPlayer_GetNumberOfKeepFrames(CriManaPlayerHn player);

/*EN
 * \brief Get decoding results (32bit ARGB format)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[out]	frame_info	Frame information structure
 * \param[out]	frame_buf	Frame buffer (for drawing) at destination
 * \par Call conditions: 
 * Always call the ::criMana_InitializeFrameARGB32 function beforehand. 
 * <br>
 * Call this function when the Mana player handle status is CRIMANAPLAYER_STATUS_PLAYING. 
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Gets (copies) the time stamped video frame in 32bit ARGB format. <br>
 * You will first need to allocate an ARGB buffer entity when you call this function. <br>
 * <br>
 * The actual sequence of 32bit ARGB pixel data will be the most
 * standard format for that platform.  
 *
 * \attention
 * This function can even be used on the PS3 and Xbox360, but it will put an extremely high load on the CPU. <br>
 * Getting a movie with 1280x720 resolution with this function will take close to 1vsync time. <br>
 * On the PS3 and Xbox360, we recommend converting the frame through a combination of the 
 * ::criManaPlayer_CopyFrameToBuffersYUV function and a pixel shader. <br>
 *
 * \attention
 * This function is not supported during H.264 playback on the Wii U/XboxOne/VITA. 
 *
 * \sa criMana_InitializeFrameARGB32
 */
void CRIAPI criManaPlayer_CopyFrameToBufferARGB32(
	CriManaPlayerHn player, const CriManaFrameInfo *frame_info, CriManaTextureBuffer *frame_buf);

/*EN
 * \brief Get decoding results (YUV individual buffer format)
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[out]	frame_info	Frame information structure
 * \param[in]	frame_buf	Frame buffer (for drawing) at destination
 * \par Call conditions: 
 * Call this function when the Mana player handle status is CRIMANAPLAYER_STATUS_PLAYING. 
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Gets the time stamped video frame in a YUV individual buffer format. <br>
 * YUV individual buffer format is an output format for drawing frames with a pixel shader. <br>
 * When you call this function, you will need to allocate a YUV individual buffer entity first. <br>
 * The video frame is written in the specified YUV individual buffer by the argument frame_buf. <br>
 * <br>
 * It does not use the a_plane parameters of the argument frame_buf when an alpha movie is not being played.<br>
 */
void CRIAPI criManaPlayer_CopyFrameToBuffersYUV(
	CriManaPlayerHn player, const CriManaFrameInfo *frame_info, CriManaTextureBuffersYUV *frame_buf);

/*EN
 * \brief Release frame
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	frame_info	Frame information structure
 * \par Call conditions: 
 * This is not thread safe. 
 * \par Description: 
 * Releases the frame being referenced by the ::criManaPlayer_ReferFrame or ::criManaPlayer_KeepFrame function. <br>
 * Call this function or the ::criManaPlayer_DiscardOneKeepFrame function to release the referenced frame. <br>
 * <br>
 * When releasing the frame, the Mana player will consider the buffer of the released frame is empty and will use it for decoding.<br>
 */
void CRIAPI criManaPlayer_DiscardFrame(CriManaPlayerHn player, const CriManaFrameInfo *frame_info);

/*EN
 * \brief Release frame
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \par Call conditions: 
 * This is not thread safe. 
 * \par Description: 
 * Destroys the oldest frame being kept by the application with the ::criManaPlayer_KeepFrame function. 
 * <br>
 * Use the ::criManaPlayer_DiscardFrame function instead if you want the application to expressly specify
 * which frame to destroy. 
 *
 * \sa criManaPlayer_KeepFrame, criManaPlayer_GetNumberOfKeepFrames, criManaPlayer_DiscardFrame
 */
void CRIAPI criManaPlayer_DiscardOneKeepFrame(CriManaPlayerHn player);

/***********************************/
/*         Special playback related            */
/***********************************/

/*EN
 * \brief Register data request callback
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	func	Data request callback
 * \param[in]	obj		User data passed as a data request callback argument
 * \par Call conditions: 
 * This is not thread safe. 
 * \par Description: 
 * Registers the callback function of the movie files requested for concatenated movie playback. 
 * This callback function occurs at the following timing. <br>
 * - When the movie file has been read. <br>
 * - When playback begins with no file specified. <br>
 * <br>
 * You can combine and specify the next movie file in the data request callback function by calling the ::criManaPlayer_SetFile function,
 * the ::criManaPlayer_SetFileRange function, or the ::criManaPlayer_SetData function. <br>
 * If none of these are called, then playback will finish once the movie that has been read ends. <br>
 * <br>
 * Call the ::criManaPlayer_SetPreviousDataAgain function in the callback function if you want to replay
 * the previously specified movie source. <br>
 * <br>
 * When a data request callback occurs, the user object specified during registration will be passed into the
 * second argument usrobj of the callback function. Use this function to manage lists of registered files, etc. <br>
 * <br>
 * Movie files that can be played in concatenation have the following conditions. <br>
 * - Video resolution is the same
 * - Video frame rate is the same (except in instances where the master time is not synchronized)
 * -Video codec is the same
 * - Audio and subtitle track compositions are the same
 *
 * \par Notes: 
 * The API name from the ::criManaPlayer_SetFileRequestCallback function was changed from Ver.1.10. 
 *
 * \sa criManaPlayer_SetFile, criManaPlayer_SetData, criManaPlayer_SetFileRange, criManaPlayer_SetPreviousDataAgain, criManaPlayer_DeferCallback
 */
void CRIAPI criManaPlayer_SetDataRequestCallback(CriManaPlayerHn player, 
												 CriManaPlayerDataRequestCbFunc func, void* obj);

/*EN
 * \brief Request to re-execute the data request callback
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \par Call conditions: 
 * This function can only be used in the data request callback function. <br>
 * However, it cannot call the initial data request callback when a playback began without having registered the files. <br>
 * \par Description: 
 * When a registered data request callback occurs in the ::criManaPlayer_SetDataRequestCallback function,
 * calling it within the callback function will cause a data request callback in the next server processing. <br>
 * By using this function, if a movie file that should be registered cannot be determined as the data request callback occurs,
 * you can delay the timing of setting the movie file. <br>
 * <br>
 * \par Notes: 
 * The Mana player status will transition to CRIMANAPLAYER_STATUS_PLAYEND if nothing happens in the data request 
 * callback function. <br>
 * If this function is executed, then the Mana player status can be maintained as CRIMANAPLAYER_STATUS_PLAYING
 * until the next data request callback is issued. 
 * \attention
 * You cannot use this function for the initial data request callback called if the file was not registered. <br>
 * Always use when deferring specifying the second movie or later in concatenated playback. <br>
 * <br>
 * Ensure that the next movie is registered at the latest 100 milliseconds before the last frame of a registered movie
 * is displayed. Any later than that may be too late to load the next movie, preventing seamless concatenated play. <br>
 *
 * \sa criManaPlayer_SetFile, criManaPlayer_SetData, criManaPlayer_SetFileRange, criManaPlayer_SetPreviousDataAgain, criManaPlayer_SetDataRequestCallback
 */
void CRIAPI criManaPlayer_DeferCallback(CriManaPlayerHn player);

/*EN
 * \brief Set seek position
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	seek_frame_no	Seek frame number (change to seek_frame_no)
 * \par Call conditions: 
 * Call this function before starting playback (before calling the ::criManaPlayer_Prepare function or ::criManaPlayer_Start function). <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Specifies the frame number where seek play will begin. <br>
 * <br>
 * This function cannot be called during movie playback. To seek during playback, temporarily stop the playback
 * and call this function. <br>
 * <br>
 * The movie will begin playing from the beginning if this function is not executed or if frame number zero is specified. 
 * The movie will also play from the beginning if the specified frame number is greater than the total number of frames in the movie data or a negative value. <br>
 * <br>
 * Information on seek position settings will remain after this function is called, even if playback on the player is stopped or started. 
 * <br>
 * \par Caution: 
 * You will need to use the ::criManaPlayer_SetMetaDataWorkAllocator function and register a meta data memory 
 * allocator before seek playback. 
 *
 * \sa criManaPlayer_SetMetaDataWorkAllocator
 */
void CRIAPI criManaPlayer_SetSeekPosition(CriManaPlayerHn player, CriSint32 seek_frame_no); 

/* criManaPlayer_SetMovieEventSyncMode */
/*EN
 * \brief Set the sync mode of movie events
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	mode	Movie event synchronization mode
 * \par Call conditions: 
 * Execute this function before starting playback. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Set the sync mode of movie events (cue points, subtitles). <br>
 * The default is to synchronize to the movie playback time (CRIMANAPLAYER_EVENT_SYNC_PLAYBACK_TIME).
 * If you want to synchronize with the acquisition of video frames, please specify CRIMANAPLAYER_EVENT_SYNC_FRAME_TIME.<br>
 * \sa CriManaPlayerMovieEventSyncMode
 */
void CRIAPI criManaPlayer_SetMovieEventSyncMode(CriManaPlayerHn player, CriManaPlayerMovieEventSyncMode mode);


/*EN
 * \brief Get subtitle channel
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[in]	channel		Subtitle channel number
 * \par Call conditions: 
 * This is not thread safe. <br>
 * \par Description: 
 * Sets the subtitle channel to get. It is set to "no get subtitles" by default. 
 * <br>
 * You can find out how many subtitles are included in the movie to play before playback begins by using the
 * ::criManaPlayer_DecodeHeader or ::criManaPlayer_GetMovieInfo function. <br>
 * <br>
 * You cannot get subtitles if a channel number that does not exist in the data is specified. <br>
 * Specify CRIMANA_SUBTITLE_CHANNEL_OFF as the channel if you want to use default settings (not to get subtitles). <br>
 * <br>
 * Periodically execute the ::criManaPlayer_GetSubtitleOnTime function from the main loop if you specified a subtitle channel
 * with this function. The movie will stop playing midway if subtitles are not periodically gotten. <br>
 * <br>
 * You can switch subtitle channels during movie playback. However, the actual channel will switch from the 
 * next subtitle immediately after the one set. 
 *
 * \sa criManaPlayer_GetSubtitleOnTime
 */
void CRIAPI criManaPlayer_SetSubtitleChannel(CriManaPlayerHn player, CriSint32 channel);

/*EN
 * \brief Get subtitles
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[out]	bufptr		Subtitle buffer address of the write destination
 * \param[in]	bufsize		Size of the write subtitle buffer
 * \return CriUint32 Size of the written subtitle data (bytes)
 * \par Call conditions: 
 * Call this function when the Mana player handle status is CRIMANAPLAYER_STATUS_PLAYING. 
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Gets the time stamped subtitle data. 
 * Allocate a subtitle buffer entity when calling this function. <br>
 * Subtitle data is written to the specified buffer by the argument bufptr. <br>
 * If the subtitle data is larger than bufsize, then only the amount that can be stored in bufsize will be written, with the rest destroyed. <br>
 * <br>
 * The buffer contents will clear if there are no time stamped subtitles. <br>
 * <br>
 * Periodically execute this function from the main loop when specifying a subtitle channel that exists
 * in the ::criManaPlayer_SetSubtitleChannel function. <br>
 * The movie will stop midway if it is not executed. 
 * 
 * \sa criManaPlayer_GetSubtitleOnTime
 */
CriUint32 CRIAPI criManaPlayer_GetSubtitleOnTime(CriManaPlayerHn player, CriUint8 *bufptr, CriUint32 bufsize);

/*EN
 * \brief Get a list of Cuepoint information
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \return CriManaCuePointInfo*		Cuepoint information
 * \par Call conditions: 
 * Call this function after the Mana player handle status is CRIMANAPLAYER_STATUS_WAIT_PREP. 
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Gets Ccuepoint information (a list of event points). 
 * <br>
 * The Cuepoint information gotten by this function directly references the playback handle work buffer. <br>
 * While this information can be referenced when playback has stopped, reference will be prohibited after the next playback begins. <br>
 * These conditions will not change even if this Cuepoint information is copied to a different memory.
 * \attention
 * In order to acquire cue point information, it is necessary to register 
 * the memory allocator for metadata in advance using ::criManaPlayer_SetMetaDataWorkAllocator function.
 */
CriManaCuePointInfo* CRIAPI criManaPlayer_GetCuePointInfo(CriManaPlayerHn player);

/*EN
 * \brief Set Cuepoint callback
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	func	Get Cuepoint callback function
 * \param[in]	obj		User object (optional)
 * \par Call conditions: 
 * Call this function before movie playback begins. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Registers a Cuepoint callback function. 
 * This callback function will be called when the movie playback time passes the time specified by each event point. 
 * Whether the callback function should be called or not is determined by the ::criManaPlayer_ExecuteMain function. <br>
 * <br>
 * When a Cuepoint callback occurs, the event point information is passed into the second argument eventinfo of the callback function,
 * and the user object specified during registration is passed into the third argument usrobj. <br>
 * <br>
 * You must not call the movie playback control functions (such as the ::criManaPlayer_Stop function)
 * within the Cuepoint callback function.
 * \attention
 * In order to acquire cue point information, it is necessary to register 
 * the memory allocator for metadata in advance using ::criManaPlayer_SetMetaDataWorkAllocator function.
 */
void CRIAPI criManaPlayer_SetCuePointCallback(CriManaPlayerHn player, CriManaPlayerCuePointCbFunc func, void *obj);

/*EN
 * \brief Calculate frame number from playback time
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[in]	count		Timer count
 * \param[in]	unit		Timer count per second. Time is in second units because count / unit. 
 * \return		CriSint32	frame ID
 * \par Call conditions: 
 * You can use this function after the Mana player handle status becomes CRIMANAPLAYER_STATUS_WAIT_PREP. 
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Calculates the frame number from the playback time. 
 * <br>
 * Use when you want to calculate the seek play start position from the time. 
 * (For example, when determining the seek position from the Cuepoint information.) 
 * 
 * \sa criManaPlayer_CalcTimeFromFrameNo
 */
CriSint32 CRIAPI criManaPlayer_CalcFrameNoFromTime(CriManaPlayerHn player, 
													CriUint64 count, CriUint64 unit);

/*EN
 * \brief Calculate playback time from the frame number
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[in]	frame_no	Frame number
 * \param[in]	unit		Timer count per second. Time is in second units because count / unit. 
 * \return		Timer count
 * \par Call conditions: 
 * You can use this function after the Mana player handle status becomes CRIMANAPLAYER_STATUS_WAIT_PREP. 
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Calculates the playback time from the frame number. 
 * <br>
 * You do not need to calculate this if you actually got the frame. Refer to the frame information structure time. 
 * 
 * \sa criManaPlayer_CalcFrameNoFromTime
 */
CriUint64 CRIAPI criManaPlayer_CalcTimeFromFrameNo(CriManaPlayerHn player, CriSint32 frame_no, CriUint64 unit);

/*EN
 * \brief Search event point directly after a specified time
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[in]	count		Timer count
 * \param[in]	unit		Timer count per second. Time is in second units because count / unit. 
 * \param[in]	type		Type value of the event point to be searched
 * \param[in]	eventinfo	Information on the event point found
 * \return		CriSint32	Frame number
 * \par Call conditions: 
 * You can use this function after the Mana player handle status becomes CRIMANAPLAYER_STATUS_WAIT_PREP. 
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Searches for the next event point after the specified time and gets the frame number and event point information. 
 * <br>
 * It searches for event points by type that match the specified value. 
 * Specifying -1 as the type will search for all event points. 
 * <br>
 * The frame number will be returned as -1 if the event point that was searched for could not be found. 
 * 
 * \sa  criManaPlayer_SearchPrevEventPointByTime
 */
CriSint32 CRIAPI criManaPlayer_SearchNextEventPointByTime(CriManaPlayerHn player, 
														CriUint64 count, CriUint64 unit, CriSint32 type, CriManaEventPoint *eventinfo);

/*EN
 * \brief Search event point directly before a specified time
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player		Mana player handle
 * \param[in]	count		Timer count
 * \param[in]	unit		Timer count per second. Time is in second units because count / unit. 
 * \param[in]	type		Type value of the event point to be searched
 * \param[in]	eventinfo	Information on the event point found
 * \return		CriSint32	Frame number
 * \par Call conditions: 
 * You can use this function after the Mana player handle status becomes CRIMANAPLAYER_STATUS_WAIT_PREP. 
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Searches for the next event point before the specified time and gets the frame number and event point information. <br>
 * <br>
 * It searches for event points by type that match the specified value. 
 * Specifying -1 as the type will search for all event points. <br>
 * <br>
 * The frame number will be returned as -1 if the event point that was searched for could not be found. 
 *
 * \sa  criManaPlayer_SearchNextEventPointByTime
 */
CriSint32 CRIAPI criManaPlayer_SearchPrevEventPointByTime(CriManaPlayerHn player, 
														CriUint64 count, CriUint64 unit, CriSint32 type, CriManaEventPoint *eventinfo);

/***********************************/
/*         Special playback related            */
/***********************************/
/*EN
  \brief Set playback speed
  \ingroup MDL_MANALIB_PLAYER
  \param[in]	player	Mana player handle
  \param[in]	speed_numerator	Specified speed playback numerator. 
  \param[in]	speed_denominator	Specified playback speed denominator. 
  \par Call conditions: 
  * Call before the Mana player handle status is CRIMANAPLAYER_STATUS_WAIT_PREP. <br>
  However, the playback speed can be changed while the movie is playing as long as the movie being played has no sound. <br>
  <br>
  * This is not thread safe.<br> \par Description: 
  Specifies the movie playback speed as a rational number. How fast the movie can be fast-forwarded (how high the playback speed can be increased) depends on the
 decoding load and the data read rate. <br>
  Setting a speed that exceeds playback performance may cause video stuttering or audio dropout. <br>
  <br>
  \table "Example" align=center width=90% border=1 cellspacing=0 cellpadding=4
  {Numerator (numerator) | Denominator (denominator)  | Meaning                      }
  [1               | 1	                | Same speed playback (default)      ]
  [2               | 1                  | 2x playback                  ]
  [1               | 2                  | Half speed playback           ]
  [1000            | 1001               | Play 30fps videos at 29.97fps or 60fps videos at 59.94fps ]
  \endtable
  <br>
  \par Caution: 
  You cannot configure the speed settings while playing movies with sound. If you want to change the playback speed during playback, first stop playback,
  change the playback speed, and use seek playback from the desired frame number. <br>
  <br>
  \par Notes: 
  Some platforms will not let you set the playback speed of movies with audio. <br>
  <br>
  Speed will not change when unsynchronized mode (CRIMANAPLAYER_TIMER_NONE) is specified.
 */
 void CRIAPI criManaPlayer_SetSpeed(CriManaPlayerHn player, 
	CriSint32 speed_numerator, CriSint32 speed_denominator);

/*EN
  \brief Set decode operation mode
  \ingroup MDL_MANALIB_PLAYER
  \param[in]	player	Mana player handle
  \param[in]	mode	Decode operation mode
  \par Call conditions: 
  * Call before the Mana player handle status is CRIMANAPLAYER_STATUS_WAIT_PREP. <br>
  <br>
  This is thread safe.<br> \par Description: 
  Specifies the Mana player decode operation mode. 
  <br>
  \par Caution: 
  You cannot change the decode operation mode during playback. Operation mode settings made during playback will
  be reflected from the next playback. 

  \par Notes: 
  There are limits to what modes can be specified depending on the platform and codec.<br>
 */
 void CRIAPI criManaPlayer_SetDecodeMode(CriManaPlayerHn player, 
	 CriManaDecodeMode mode);

/*==========================================================================
 *      CRI Mana Decrypter API
 *=========================================================================*/
/*EN
 * \brief Calculate work area size for decrypter creation
 * \ingroup MDL_MANALIB_DECRYPTER
 * \param[in]	config				Structure for decrypter creation
 * \return		CriSint32			Work area size
 * \par Description: 
 * Calculates the size of the work area necessary for decrypter creation. <br>
 * You will need to pass the memory for the size calculated by this function
 * as a work area in order to create a decrypter with the
 * ::criManaDecrypter_Create function instead of registering an allocator with the ::criMana_SetUserAllocator macro. <br>
 * <br>
 * This function will return -1 if it fails to calculate the work area size. <br>
 * You can check the error callback message to find out why it failed to calculate the work area size. <br>
 * \par Notes: 
 * The argument config information is only referenced in the function. <br>
 * It cannot be referenced after exiting this function, so releasing the config area after the function has been executed
 * will not cause problems 
 * \sa CriManaDecrypterConfig, criManaDecrypter_Create, criMana_SetUserAllocator
 */
CriSint32 CRIAPI criManaDecrypter_CalculateWorkSize(
	const CriManaDecrypterConfig *config);

/*EN
 * \brief Create decrypter
 * \ingroup MDL_MANALIB_DECRYPTER
 * \param[in]	config				Structure for decrypter creation
 * \param[in]	work				Work area
 * \param[in]	work_size			Work area size
 * \return		CriManaDecrypterHn	Decrypter handle
 * \par Description: 
 * Creates a decrypter to decipher encrypted sound data. <br>
 * <br>
 * This function will return -1 if it fails to calculate the work area size. <br>
 * You can check the error callback message to find out why it failed to calculate the work area size. <br>
 * \par Notes: 
 * The decrypter is currently activated when it is created and globally applied. <br>
 * Therefore, "only encrypted data can be played back" once this function is executed. <br>
 * (A playback error will occur with any movie data that is not encrypted or with movie data that has a different encryption key.) <br>
 * <br>
 * The argument config information will only be referenced in the function. <br>
 * It cannot be referenced after exiting this function, so releasing the config area after the function has been executed
 * will not cause problems 
 * \par Example: 
 * \code
 * 	CriManaDecrypterConfig decrypter_config;
 * 	CriManaDecrypterHn decrypter;
 * 	CriManaPlayerHn player;
 * 	
 * 	// Zero the config structure for decrypter creation
 * 	memset(&decrypter_config, 0, sizeof(decrypter_config));
 * 	
 * 	// Set encryption key
 * 	decrypter_config.key = 123456789;
 * 	
 * 	// Create decrypter
 * 	decrypter = criManaDecrypter_Create(&decrypter_config, NULL, 0);
 * 	
 * 	// Create player
 * 	player = criManaPlayer_Create(NULL, NULL, 0);
 * \endcode
 * \attention
 * You will need to initialize the library before executing this function. <br>
 * <br>
 * Only one decrypter can currently be used simultaneously in the application. <br>
 * (You cannot simultaneously create multiple decrypters.) <br>
 * <br>
 * When creating a player after creating a decrypter,
 * do not destroy the decrypter until the player is destroyed. <br>
 * Destroying the decrypter while the player still remains
 * may cause the movie data to not play properly or cause an access violation. <br>
 * <br>
 * Always execute the appropriate ::criManaDecrypter_Destroy function after executing this function. <br>
 * Also, do not release the work area set to this function or
 * re-execute this function until the ::criManaDecrypter_Destroy function is executed. <br>
 * \sa CriManaDecrypterConfig, criManaDecrypter_CalculateWorkSize, criManaDecrypter_Destroy, criMana_SetUserAllocator
 */
CriManaDecrypterHn CRIAPI criManaDecrypter_Create(
	const CriManaDecrypterConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Destroy decrypter
 * \ingroup MDL_MANALIB_DECRYPTER
 * \par Description: 
 * Destroys the decrypter. <br>
 * Executing this function will stop decryption of encrypted data. <br>
 * It will release the memory area allocated during decrypter creation if the
 * ::criMana_SetUserAllocator macro is used and an allocator registered. <br>
 * (You can release the work area after this function is executed if the work area was passed
 * when the decrypter was created.) <br>
 * \attention
 * You will no longer be able to decrypt once this function is executed. <br>
 * Do not call this function while encrypted movies are playing. <br>
 * \sa criManaDecrypter_Create, criMana_SetUserAllocator
 */
void CRIAPI criManaDecrypter_Destroy(CriManaDecrypterHn decrypter);



/* OUTER_FRAMEPOOL_WORK */
/********************************************/
/* External frame pool (used only on some platforms) */
/********************************************/

/*EN
 * \brief Calculate extended decoder work area size
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	config_basic	Pointer to the basic playback work parameters (required)
 * \param[in]	config_ex		Pointer to the extended playback work parameters (additional) can be specified as NULL
 * \return	CriSint32 Extended decoder work size
 * \par Call conditions: 
 * This is thread safe. 
 * \par Description: 
 *Calculates the size of the extended decoder work area necessary to play the specified movie file. <br>
 * Returns 0 if extended decoder work is not necessary.
 */
CriSint32 CRIAPI criManaPlayer_CalculateExtDecoderWorkSize(
	CriManaPlayerHn player, const CriManaPlaybackBasicWorkConfig *config_basic, const CriManaPlaybackExWorkConfig *config_ex);

/*EN
 * \brief Set extended decoder work area
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	config_basic	Pointer to the basic playback work parameters (required)
 * \param[in]	config_ex		Pointer to the extended playback work parameters (additional) can be specified as NULL
 * \param[in]	work			Work size allocated by the app (automatically aligned internally)
 * \param[in]	work_size		Work size
 * \par Call conditions: 
 *Call when the status is CRIMANAPLAYER_STATUS_WAIT_PREP or before. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Sets the extended decoder work memory necessary to play the specified movie file. <br>
 * <br>
 * To expressly allocate memory on the application side, check the work size necessary with the ::criManaPlayer_CalculateExtDecoderWorkSize
 * function and pass the allocated work memory into the argument. <br>
 * When specifying NULL in work and zero in work_size, it will use the memory allocation function
 * registered by the ::criManaPlayer_SetExtDecoderWorkAllocator function and allocate memory internally. 
 * <br>
 * Starting a playback without executing this function will automatically use the default play parameters internally
 * to play. When this happens, one condition will be that a memory allocator will be registered with the ::criManaPlayer_SetExtDecoderWork function. 
 *
 */
void CRIAPI criManaPlayer_SetExtDecoderWork(
	CriManaPlayerHn player, const CriManaPlaybackBasicWorkConfig *config_basic, const CriManaPlaybackExWorkConfig *config_ex, 
	void *work, CriSint32 work_size);

/* Extended decoder work area allocate/release callback function type */
#define CriManaExtDecoderWorkMallocFunc CriManaMallocFunc
#define CriManaExtDecoderWorkFreeFunc   CriManaFreeFunc

/*EN
 * \brief Register callback for extended decoder work allocation
 * \ingroup MDL_MANALIB_GLOBAL
 * \param[in]	player			Mana player handle
 * \param[in]	allocfunc		Memory allocation function
 * \param[in]	freefunc		Memory release function
 * \param[in]	obj				User object (optional)
 * \par Call conditions: 
 * Call this before the ::criMana_Initialize function. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Registers a memory allocator (memory allocation/release functions) for extended decoder work in the CRI Mana library. <br>
 * Used when you want to replace the memory release that the CRI Mana performs within the library with
 * the user's own memory release.
 */
void CRIAPI criManaPlayer_SetExtDecoderWorkAllocator(
	CriManaPlayerHn player, CriManaExtDecoderWorkMallocFunc allocfunc, CriManaExtDecoderWorkFreeFunc freefunc, void *obj);

/*EN
 * \brief Audio track category setting
 * \ingroup MDL_MANALIB_GLOBAL
 * \param[in]	player			Mana player handle
 * \param[in]	track_id		Audio track number (0: Main, 1: Sub, 2: Extra)
 * \param[in]	category_name	Category Name
 * \par Description: 
 * By calling this function before the ::criManaPlayer_Start function, you can set the category to the audio track of the movie to be played back later. <br>
 * It is possible to apply different category settings to each audio track track. Specify the audio track with the value of the argument track_id. <br>
 * If track_id is 0, it is main, 1 is sub, 2 is extra audio track. <br>
 * To delete the set category information, use the ::criManaPlayer_UnsetSoundCategory function. <br>
 * Please refer to the CRI ADX2 manual for details of the category function.
 * 
 * \par Call conditions:
 * Please use the CriManaPlayerHn created by setting the value of the CriManaPlayerConfig.use_atomex_player to CRI_TRUE. <br>
 * This function can not be used with the CriManaPlayerHn created with default settings. <br>
 * <br>
 * Please set category setting before starting playback.
 * If you update the category setting for the sound being played back, the category playback count may become abnormal. <br>
 * <br>
 * In addition, it is necessary to perform ACF registration in advance. Because the available category information is described in the ACF. <br>
 * Please refer to the CRI ADX2 manual for details of the ACF.
 * <br>
 * This function is NOT thread-safe.
 * \sa criManaPlayer_CreateWithConfig, criManaPlayer_UnsetSoundCategory
 */
void CRIAPI criManaPlayer_SetSoundCategoryByName(CriManaPlayerHn player, CriUint32 track_id, const CriChar8* category_name);

/*EN
 * \brief Delete audio track category
 * \ingroup MDL_MANALIB_GLOBAL
 * \param[in]	player			Mana player handle
 * \param[in]	track_id		Audio track number (0: Main, 1: Sub, 2: Extra)
 * \par Description: 
 * Deletes the category information set for the audio track. <br>
 * If track_id is 0, it is main, 1 is sub, 2 is extra audio track. <br>
 * To set category, use the ::criManaPlayer_SetSoundCategoryByName function.
 * \par Call conditions:
 * Please use the CriManaPlayerHn created by setting the value of the CriManaPlayerConfig.use_atomex_player to CRI_TRUE. <br>
 * This function can not be used with the CriManaPlayerHn created with default settings. <br>
 * <br>
 * This function is NOT thread-safe.
 */
void CRIAPI criManaPlayer_UnsetSoundCategory(CriManaPlayerHn player, CriUint32 track_id);


/**********************/
/* Special settings           */
/**********************/
/*EN
 * \brief Set number of frames stored during playback preparation
 * \ingroup MDL_MANALIB_PLAYER
 * \param[in]	player	Mana player handle
 * \param[in]	num_frames	Number of frames determined when playback preparations are complete (number is less than the number of frame pools)
 * \par Description: 
 * Sets the number of decoder frames stored internally during playback preparation. <br>
 * Unlike the number of frame pools, this setting determines how many frames it needs to decode during CRIMANAPLAYER_STATUS_PREP
 * in order to become CRIMANAPLAYER_STATUS_READY status. 
 *
 * The number of frame pools will apply if nothing is set. Use this function when you want to increase the number of frame pools
 * but minimize the playback latency as much as possible. 
 
 */
void CRIAPI criManaPlayer_SetNumberOfFramesForPrep(CriManaPlayerHn player, CriUint32 num_frames);


/**********************/
/* Experimental       */
/**********************/
void CRIAPI criManaPlayer_SetVideoFramerate(CriManaPlayerHn player, CriUint32 framerate_n, CriUint32 framerate_d);

/**************************************************/
/* For debugging: User use prohibited functions. Specifications not guaranteed. */
/**************************************************/
/* Audio preparation judgment ignore flag */
void CRIAPI criMana_SetIgnoreAudioPrep(CriBool flag);

/**********************/
/* Seek table information */
/**********************/
typedef struct {
	CriSint32   top_frame_id;
} CriManaSeekBlockInfo;
/* Obtains the number of seek blocks. */
/* Returns 0 on failure. No information if 0 is returned while PLAYING. */
CriSint32 CRIAPI criManaPlayer_GetNumberOfSeekBlocks(CriManaPlayerHn player);
/* Obtains seek block information. */
/* <Input>
 * - num_seekblock : Number of output array elements
 * <Output>
 * - blockinfo : Pointer to seek block information array (allocate the size required for num_seekblock before passing)
 */
void CRIAPI criManaPlayer_GetSeekBlockInfo(CriManaPlayerHn player, CriSint32 num_seekblock, CriManaSeekBlockInfo *blockinfo);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/***************************************************************************
 *      For compatibility with old version
 ***************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

void CRIAPI criManaPlayer_SetBusSendLevel(
	CriManaPlayerHn player, CriSint32 bus_id, CriFloat32 level);

void CRIAPI criManaPlayer_SetSubAudioBusSendLevel(
	CriManaPlayerHn player, CriSint32 bus_id, CriFloat32 level);

#ifdef __cplusplus
}
#endif

#endif //CRI_INCL_CRI_MANA_H

/* end of file */
