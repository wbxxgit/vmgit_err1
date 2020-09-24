#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


#include "dev_zj_funReg.h"  
#include "zj_system.h"
#include "zj_camera.h"
#include "zj_cameraiot.h"

#include "zj_network.h"
#include "zj_power.h"
#include "zj_ota.h"
//#include "zj_iothub.h"
#include "zj_channel.h"









static ST_DEVZJ_FUNREG_AUDIO_TABLE   g_funReg_audio_t = {0};
static ST_DEVZJ_FUNREG_VIDEO_TABLE   g_funReg_video_t = {0};
static ST_DEVZJ_FUNREG_CAMIOT_TABLE  g_funReg_camIot_t = {0};

static ST_DEVZJ_FUNREG_POWER_TABLE    g_funReg_power_t = {0};
static ST_DEVZJ_FUNREG_OTA_TABLE      g_funReg_ota_t = {0};
static ST_DEVZJ_FUNREG_IOTHUB_TABLE   g_funReg_iothub_t = {0};
static ST_DEVZJ_FUNREG_CHANNEL_TABLE  g_funReg_channel_t = {0};

static ST_DEVZJ_FUNREG_NETWORK_TABLE  g_funReg_network_t = {0};



ST_DEVZJ_FUNREG_AUDIO_TABLE *dj_audio_GtFTbl(){
    return  &g_funReg_audio_t;
}

ST_DEVZJ_FUNREG_VIDEO_TABLE *dj_video_GtFTbl(){
    return  &g_funReg_video_t;
}

ST_DEVZJ_FUNREG_CAMIOT_TABLE *dj_camIot_GtFTbl(){
    return  &g_funReg_camIot_t;
}


ST_DEVZJ_FUNREG_POWER_TABLE *dj_power_GtFTbl(){
    return  &g_funReg_power_t;
}
ST_DEVZJ_FUNREG_OTA_TABLE *dj_ota_GtFTbl(){
    return  &g_funReg_ota_t;
}

ST_DEVZJ_FUNREG_IOTHUB_TABLE *dj_iothub_GtFTbl(){
    return  &g_funReg_iothub_t;
}
ST_DEVZJ_FUNREG_CHANNEL_TABLE *dj_channel_GtFTbl(){
    return  &g_funReg_channel_t;
}

ST_DEVZJ_FUNREG_NETWORK_TABLE *dj_network_GtFTbl(){
    return  &g_funReg_network_t;
}



int dev_zj_funcbReg(){
	g_funReg_audio_t.f_Audio_WriteFrame = ZJ_Audio_WriteFrame;
	g_funReg_audio_t.f_GtMediaAudioData = ZJ_GtMediaAudioData;
	g_funReg_audio_t.f_GetMediaAudioParam = ZJ_GetMediaAudioParam;
	//
	g_funReg_video_t.f_Video_WriteFrame = ZJ_Video_WriteFrame;

	g_funReg_camIot_t.f_IoTEventInPut = ZJ_IoTEventInPut;

	//power
	g_funReg_power_t.f_SetPowerLevel = ZJ_SetPowerLevel;

	//ota
	g_funReg_ota_t.f_SetBurnningProgress = ZJ_SetBurnningProgress;
	g_funReg_ota_t.f_StartUpdate = ZJ_StartUpdate;

	//iothub
//	g_funReg_iothub_t.f_IoTHubWriteData = ZJ_IoTHubWriteData;

	//channel
	g_funReg_channel_t.f_SendCustomData = ZJ_SendCustomData;
	//network
	g_funReg_network_t.f_SetQRCodeString = ZJ_SetQRCodeString;
	g_funReg_network_t.f_SetNetWorkType = ZJ_SetNetWorkType;
	return 0;
}





