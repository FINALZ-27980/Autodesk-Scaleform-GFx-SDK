/*===========================================================================*
 *  Header file for Atom Config File
 *  Project            : SampleProject
 *  Tool Ver.          : CRI Atom Craft Ver.2.35.09
 *  File Path          : E:/ws/adx2-smpdata/p4ws/CriMovieDepot/_cri_rake_temp/smpdata_build/PC/SampleProject.acf
 *  File Name          : SampleProject.acf
 *  File Size          : 6,880 bytes
 *  Date Time          : 2018/08/03 18:20
 *  Target             : PC
 *  Categories         : 5
 *  AISAC Controls     : 16
 *  Global AISACs      : 0
 *  Voice Limit Groups : 0
 *  DSP BUS Settings   : 1
 *  DSP BUS Settings Snapshot  : 2
 *  DSP BUS Name       : 8
 *  Game Variables     : 1
 *  Selectors          : 2
 *  REACTs             : 1
 *  Project Comment    : 
 *===========================================================================*/

#define CRI_SAMPLEPROJECT_ACF_NUM_CATEGORIES_PER_PLAYBACK (4)
#define CRI_SAMPLEPROJECT_ACF_CATEGORYNUM (5)
#define CRI_SAMPLEPROJECT_ACF_AISACCONTROLNUM (16)
#define CRI_SAMPLEPROJECT_ACF_GLOBALAISACNUM (0)
#define CRI_SAMPLEPROJECT_ACF_VOICELIMITGROUPNUM (0)
#define CRI_SAMPLEPROJECT_ACF_DSPSETTINGNUM (1)
#define CRI_SAMPLEPROJECT_ACF_DSPSETTINGSNAPSHOTNUM (2)
#define CRI_SAMPLEPROJECT_ACF_DSPBUSNAMENUM (8)
#define CRI_SAMPLEPROJECT_ACF_GAMEVARIABLENUM (1)
#define CRI_SAMPLEPROJECT_ACF_SELECTORNUM (2)
#define CRI_SAMPLEPROJECT_ACF_REACTNUM (1)

/* Category List (Category ID) */
#define CRI_SAMPLEPROJECT_ACF_CATEGORY_MUSIC        ( 0) /* Category/Music  */
#define CRI_SAMPLEPROJECT_ACF_CATEGORY_SE           ( 1) /* Category/SE  */
#define CRI_SAMPLEPROJECT_ACF_CATEGORY_VOICE        ( 2) /* Category/Voice  */
#define CRI_SAMPLEPROJECT_ACF_CATEGORY_BGM_REACT    ( 3) /* Ducking/BGM_REACT  */
#define CRI_SAMPLEPROJECT_ACF_CATEGORY_VOICE_REACT  ( 4) /* Ducking/Voice_REACT  */

/* AISAC Control List (AISAC Control ID) */
#define CRI_SAMPLEPROJECT_ACF_AISACCONTROL_ANY             ( 0) /* Any  */
#define CRI_SAMPLEPROJECT_ACF_AISACCONTROL_DISTANCE        ( 1) /* Distance  */
#define CRI_SAMPLEPROJECT_ACF_AISACCONTROL_AISACCONTROL02  ( 2) /* AisacControl02  */
#define CRI_SAMPLEPROJECT_ACF_AISACCONTROL_AISACCONTROL03  ( 3) /* AisacControl03  */
#define CRI_SAMPLEPROJECT_ACF_AISACCONTROL_AISACCONTROL04  ( 4) /* AisacControl04  */
#define CRI_SAMPLEPROJECT_ACF_AISACCONTROL_AISACCONTROL05  ( 5) /* AisacControl05  */
#define CRI_SAMPLEPROJECT_ACF_AISACCONTROL_AISACCONTROL06  ( 6) /* AisacControl06  */
#define CRI_SAMPLEPROJECT_ACF_AISACCONTROL_AISACCONTROL07  ( 7) /* AisacControl07  */
#define CRI_SAMPLEPROJECT_ACF_AISACCONTROL_AISACCONTROL08  ( 8) /* AisacControl08  */
#define CRI_SAMPLEPROJECT_ACF_AISACCONTROL_AISACCONTROL09  ( 9) /* AisacControl09  */
#define CRI_SAMPLEPROJECT_ACF_AISACCONTROL_AISACCONTROL10  (10) /* AisacControl10  */
#define CRI_SAMPLEPROJECT_ACF_AISACCONTROL_AISACCONTROL11  (11) /* AisacControl11  */
#define CRI_SAMPLEPROJECT_ACF_AISACCONTROL_AISACCONTROL12  (12) /* AisacControl12  */
#define CRI_SAMPLEPROJECT_ACF_AISACCONTROL_AISACCONTROL13  (13) /* AisacControl13  */
#define CRI_SAMPLEPROJECT_ACF_AISACCONTROL_AISACCONTROL14  (14) /* AisacControl14  */
#define CRI_SAMPLEPROJECT_ACF_AISACCONTROL_AISACCONTROL15  (15) /* AisacControl15  */

/* Global AISAC List (Global AISAC Name) */
// No Global AISAC 


/* DspSetting List (DspSetting Name) */
#define CRI_SAMPLEPROJECT_ACF_DSPSETTING_DSPBUSSETTING_0  "DspBusSetting_0" /*   */

/* DspSettingSnapshot List (DspSettingSnapshot Name) */
#define CRI_SAMPLEPROJECT_ACF_DSPSETTINGSNAPSHOT_DSPBUSSETTING_0_SNAPSHOT1  "Snapshot1" /*   */
#define CRI_SAMPLEPROJECT_ACF_DSPSETTINGSNAPSHOT_DSPBUSSETTING_0_SNAPSHOT2  "Snapshot2" /*   */

/* DspBusName List (DspBus Name) */
#define CRI_SAMPLEPROJECT_ACF_DSPBUSNAME_MASTEROUT  "MasterOut"
#define CRI_SAMPLEPROJECT_ACF_DSPBUSNAME_BUS1       "BUS1"     
#define CRI_SAMPLEPROJECT_ACF_DSPBUSNAME_BUS2       "BUS2"     
#define CRI_SAMPLEPROJECT_ACF_DSPBUSNAME_BUS3       "BUS3"     
#define CRI_SAMPLEPROJECT_ACF_DSPBUSNAME_BUS4       "BUS4"     
#define CRI_SAMPLEPROJECT_ACF_DSPBUSNAME_BUS5       "BUS5"     
#define CRI_SAMPLEPROJECT_ACF_DSPBUSNAME_BUS6       "BUS6"     
#define CRI_SAMPLEPROJECT_ACF_DSPBUSNAME_BUS7       "BUS7"     

/* Game Variable (Game Variable Index) */
#define CRI_SAMPLEPROJECT_ACF_GAMEVARIABLE_DEFAULT  "Default" /*   */

/* Selector/Selector Label List (Selector/Selector Label Name) */
#define CRI_SAMPLEPROJECT_ACF_SELECTOR_TEMPOCHANGE      "TempoChange"     /*   */
#define CRI_SAMPLEPROJECT_ACF_SELECTORLABEL_TEMPOCHANGE_TEMPO40   "Tempo40"  /*   */
#define CRI_SAMPLEPROJECT_ACF_SELECTORLABEL_TEMPOCHANGE_TEMPO100  "Tempo100" /*   */
#define CRI_SAMPLEPROJECT_ACF_SELECTORLABEL_TEMPOCHANGE_TEMPO120  "Tempo120" /*   */
#define CRI_SAMPLEPROJECT_ACF_SELECTORLABEL_TEMPOCHANGE_TEMPO140  "Tempo140" /*   */
#define CRI_SAMPLEPROJECT_ACF_SELECTORLABEL_TEMPOCHANGE_TEMPO160  "Tempo160" /*   */
#define CRI_SAMPLEPROJECT_ACF_SELECTORLABEL_TEMPOCHANGE_TEMPO200  "Tempo200" /*   */

#define CRI_SAMPLEPROJECT_ACF_SELECTOR_TRACKTRANSITION  "TrackTransition" /*   */
#define CRI_SAMPLEPROJECT_ACF_SELECTORLABEL_TRACKTRANSITION_ARP    "Arp"   /*   */
#define CRI_SAMPLEPROJECT_ACF_SELECTORLABEL_TRACKTRANSITION_BRASS  "Brass" /*   */
#define CRI_SAMPLEPROJECT_ACF_SELECTORLABEL_TRACKTRANSITION_DRUM   "Drum"  /*   */
#define CRI_SAMPLEPROJECT_ACF_SELECTORLABEL_TRACKTRANSITION_EP     "EP"    /*   */


/* end of file */

