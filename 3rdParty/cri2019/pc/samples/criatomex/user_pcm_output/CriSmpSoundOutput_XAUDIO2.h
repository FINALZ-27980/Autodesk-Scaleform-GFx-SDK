/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2008-2010 CRI Middleware Co., Ltd.
 *
 * Library  : Sample Library
 * Module   : Sound Output using XAudio2
 * File     : CriSmpSoundOuput_XAUDIO2.h
 * Date     : 2010-02-04
 * Version  : 1.09
 *
 ****************************************************************************/

#if !defined(CRISMPSOUNDOUTPUT_XAUDIO2_H_INCLUDED)
#define CRISMPSOUNDOUTPUT_XAUDIO2_H_INCLUDED

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
#include "cri_xpt.h"
#include "CriSmpSoundOutput.h"

#if defined(_XBOX)
#include <xtl.h>
#else
#define _WIN32_DCOM
#include <windows.h>
#include <process.h>
#endif

#if !defined(_XBOX)
#define INITGUID
#endif

#include <XAudio2.h>

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/

/***************************************************************************
 *      処理マクロ
 *      Macro Functions
 ***************************************************************************/

/***************************************************************************
 *      データ型宣言
 *      Data Type Declarations
 ***************************************************************************/
/****
*			Sound Output Object
***/
class CriSmpSoundOutputXAudio2 : public CriSmpSoundOutput
{
public:
	static const CriUint32 SAMPLING_RATE = 48000;
	static const CriUint32 NUM_CHANNELS = 6;
	static const CriUint32 SAMPLE_SIZE = sizeof(CriFloat32);
	static const DWORD SPEAKER_CONFIG = (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT |
                                         SPEAKER_FRONT_CENTER | SPEAKER_LOW_FREQUENCY |
                                         SPEAKER_BACK_LEFT  | SPEAKER_BACK_RIGHT);	// 5.1ch

	/* Output matrix for downmixing */
	static const float DOWNMIX_MATRIX[NUM_CHANNELS * 2];
	
	/* NOTE) The precision of timer on PC is lower than Xbox360.	*/
	/*       Therefore, on PC, it is necessary to increase the 		*/
	/*       number of samples processed in single audio frame.		*/
#if defined(XPT_TGT_XBOX360)
	static const CriUint32 SAMPLES_PER_PACKET = 256;
	static const CriUint32 AUDIO_FRAME_INTERVAL = 4;
	static const CriUint32 MAX_PACKETS = 3;
#else
	static const CriUint32 SAMPLES_PER_PACKET = 512;
	static const CriUint32 AUDIO_FRAME_INTERVAL = 10;
	static const CriUint32 MAX_PACKETS = 4;
#endif
	
	static const CriUint32 PACKET_SIZE = (NUM_CHANNELS * SAMPLE_SIZE * SAMPLES_PER_PACKET);

	static CriBool Initialize(void);
	static void Finalize(void);
	static CriBool IsInitialized(void);
	
	static IXAudio2* GetXAudio2(void);
	static IXAudio2MasteringVoice* GetXAudio2MasteringVoice(void);
	
	static CriSmpSoundOutputXAudio2* Create(void);
	
	virtual void Destroy(void);
	virtual void SetNotifyCallback(CriUint32 (*func)(void *obj, CriUint32 nch, CriFloat32 *sample[], CriUint32 nsmpl), void *obj);
	virtual void Start(void);
	virtual void Stop(void);
	virtual void ExecuteMain(void);
	virtual void SetFrequency(CriUint32 frequency);
	
	void ExecuteAudioFrame(void);
	
private:
	// Initialization counter
	static LONG s_init_count;
	
	// XAudio2 object
	static IXAudio2* s_xa2;
	
	// Mastering voice
	static IXAudio2MasteringVoice* s_mastering_voice;
	
	// Number of output
	static XAUDIO2_VOICE_DETAILS s_mv_details;
	
	// Function for getting PCM data
	CriUint32 (*func)(void *obj, CriUint32 nch, CriFloat32 *sample[], CriUint32 nsmpl);
	void *obj;
	
	// Source voice
	IXAudio2SourceVoice* m_source_voice;
	
	// Temporary buffer to receive PCM data
	CriFloat32 temp_buffer[NUM_CHANNELS][SAMPLES_PER_PACKET];
	
	// Buffers to submit to source voice
	CriFloat32 sound_buffer[MAX_PACKETS][PACKET_SIZE];
	
	// Write position
	CriUint32 write_position;
	
	CRITICAL_SECTION cs;
	CriBool cs_initialized;
	
	HANDLE hthread;
	volatile CriBool thread_exit_flag;
	
#if defined(_XBOX)
	static DWORD WINAPI AudioProc(void *arg);
#else
	static unsigned WINAPI AudioProc(void *arg);
#endif

	CriUint32 GetTime();

protected:
	CriSmpSoundOutputXAudio2(void);
	virtual ~CriSmpSoundOutputXAudio2(void);
};

/***************************************************************************
 *      変数宣言
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

#endif		//	CRISMPSOUNDOUTPUT_XAUDIO2_H_INCLUDED

/* --- end of file --- */
