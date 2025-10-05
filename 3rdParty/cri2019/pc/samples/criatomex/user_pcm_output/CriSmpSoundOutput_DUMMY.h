/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2006-2009 CRI Middleware Co., Ltd.
 *
 * Library  : Sample Library
 * Module   : Sound Output for PC without sound device
 * File     : CriSmpSoundOuput_DUMMY.h
 * Date     : 2009-04-09
 * Version  : 1.02
 *
 ****************************************************************************/

#if !defined(CRISMPSOUNDOUTPUT_DUMMY_H_INCLUDED)
#define CRISMPSOUNDOUTPUT_DUMMY_H_INCLUDED

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
#include "cri_xpt.h"
#include "CriSmpSoundOutput.h"

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
class CriSmpSoundOutputDummy : public CriSmpSoundOutput
{
public:
	static const CriUint32 SAMPLING_RATE = 48000;
	static const CriUint32 NUM_CHANNELS = 6;
	static const CriUint32 TIMER_INTERVAL = 10;
	static const CriUint32 BUFFER_SAMPLES = 4096;
	
	static CriSmpSoundOutputDummy* Create(void);
	
	virtual void Destroy(void);
	virtual void SetNotifyCallback(CriUint32 (*func)(void *obj, CriUint32 nch, CriFloat32 *sample[], CriUint32 nsmpl), void *obj);
	virtual void Start(void);
	virtual void Stop(void);
	virtual void ExecuteMain(void);
	virtual void SetFrequency(CriUint32 frequency);
	
	void ExecuteAudioFrame(void);
	
private:
	// Function for getting PCM data
	CriUint32 (*func)(void *obj, CriUint32 nch, CriFloat32 *sample[], CriUint32 nsmpl);
	void *obj;
	
	// Variable to store previous timer count
	DWORD prev;
	
	// Variable to control speed of removing samples
	CriSint32 frequency;
	CriUint32 remain_samples;
	
	// Temporary buffer to receive PCM data
	CriFloat32 temp_buffer[MAX_NCH][BUFFER_SAMPLES];
	
	CRITICAL_SECTION cs;
	CriBool cs_initialized;
	HANDLE hevent;
	
	HANDLE hthread;
	volatile CriBool thread_exit_flag;
	
	MMRESULT timer_id;
	
	static unsigned WINAPI SoundOutputTimerProc(LPVOID param);
	
protected:
	CriSmpSoundOutputDummy(void);
	virtual ~CriSmpSoundOutputDummy(void);
};

/***************************************************************************
 *      変数宣言
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

#endif		//	CRISMPSOUNDOUTPUT_DUMMY_H_INCLUDED

/* --- end of file --- */
