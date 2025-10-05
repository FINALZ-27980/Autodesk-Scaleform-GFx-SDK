/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2008-2010 CRI Middleware Co., Ltd.
 *
 * Library  : Sample Library
 * Module   : Utility
 * File     : smp_utl_monitor_PC.c
 * Date     : 2011-06-03
 * Version  : 1.00
 *
 ****************************************************************************/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cri_xpt.h>
#include <cri_framework.h>
#include <cri_atom_pc.h>
#include <cri_atom_ex.h>
#include "smp_utl_monitor.h"

/***************************************************************************
 *		定数マクロ
 *		Constant Macros
 ***************************************************************************/

/***************************************************************************
 *		処理マクロ
 *		Process Macros
 ***************************************************************************/

/***************************************************************************
 *      変数定義
 *      Variable Definitions
 ***************************************************************************/

/***************************************************************************
 *		関数宣言
 *		Function Declaration
 ***************************************************************************/

/***************************************************************************
 *		関数定義
 *		Function Definitions
 ***************************************************************************/

CriSint32 smputl_monitor_calculate_work_size(const CriAtomExMonitorConfig *in_config)
{
	CriAtomExMonitorConfig config;
	criAtomExMonitor_SetDefaultConfig(&config);
	if (in_config != NULL) {
		memcpy_s(&config, sizeof(CriAtomExMonitorConfig), in_config, sizeof(CriAtomExMonitorConfig));
	}
	return criAtomExMonitor_CalculateWorkSize(&config);
}

CriBool smputl_monitor_initialize(const CriAtomExMonitorConfig *in_config, void *work, CriSint32 work_size)
{
	CriAtomExMonitorConfig config;
	CriAtomExAsrBusAnalyzerConfig analyze_config;
	CriSint32 bus_no;

	criAtomExMonitor_SetDefaultConfig(&config);

	if (in_config != NULL) {
		memcpy_s(&config, sizeof(CriAtomExMonitorConfig), in_config, sizeof(CriAtomExMonitorConfig));
	}
	criAtomExMonitor_Initialize(&config, work, work_size);

	/* バスの解析機能を追加 */
	/* Add the bus analysis function */
	analyze_config.interval = 50;
	analyze_config.peak_hold_time = 1000;
	for ( bus_no=0;bus_no<8;bus_no++) {
		criAtomExAsr_AttachBusAnalyzer(bus_no, &analyze_config);
	}
	return TRUE;
}

void smputl_monitor_finalize(void)
{
	criAtomExMonitor_Finalize();
}

void smputl_monitor_execute(void)
{
	CriAtomExAsrBusAnalyzerInfo analyze_info;
	CriSint32 bus_no;
	/* バス解析情報の取得 */
	/* Get the bus analysis information */
	for ( bus_no=0;bus_no<8;bus_no++) {
		criAtomExAsr_GetBusAnalyzerInfo(bus_no, &analyze_info);
	}
}

/* --- end of file --- */
