#ifndef DEV_ZJ_FUNREG_H_
#define DEV_ZJ_FUNREG_H_


#include "dev_funReg_type.h"  


typedef struct stru_DEVZJ_FUNREG_AUDIO_TABLE{
	DFTYPE_Audio_WriteFrame f_Audio_WriteFrame;

	DFTYPE_GtMediaAudioData f_GtMediaAudioData;
	DFTYPE_GetMediaAudioParam f_GetMediaAudioParam;

}ST_DEVZJ_FUNREG_AUDIO_TABLE;


typedef struct stru_DEVZJ_FUNREG_VIDEO_TABLE{
	DFTYPE_Video_WriteFrame f_Video_WriteFrame;

}ST_DEVZJ_FUNREG_VIDEO_TABLE;

typedef struct stru_DEVZJ_FUNREG_CAMIOT_TABLE{
	DFTYPE_IoTEventInPut f_IoTEventInPut;

}ST_DEVZJ_FUNREG_CAMIOT_TABLE;


typedef struct stru_DEVZJ_FUNREG_POWER_TABLE{
	DFTYPE_SetPowerLevel f_SetPowerLevel;

}ST_DEVZJ_FUNREG_POWER_TABLE;

typedef struct stru_DEVZJ_FUNREG_OTA_TABLE{
	DFTYPE_SetBurnningProgress f_SetBurnningProgress;

}ST_DEVZJ_FUNREG_OTA_TABLE;

typedef struct stru_DEVZJ_FUNREG_IOTHUB_TABLE{
	DFTYPE_IoTHubWriteData f_IoTHubWriteData;

}ST_DEVZJ_FUNREG_IOTHUB_TABLE;

typedef struct stru_DEVZJ_FUNREG_CHANNEL_TABLE{
	DFTYPE_SendCustomData f_SendCustomData;

}ST_DEVZJ_FUNREG_CHANNEL_TABLE;

typedef struct stru_DEVZJ_FUNREG_NETWORK_TABLE{
	DFTYPE_SetQRCodeString f_SetQRCodeString;
	DFTYPE_SetNetWorkType f_SetNetWorkType;

}ST_DEVZJ_FUNREG_NETWORK_TABLE;




ST_DEVZJ_FUNREG_AUDIO_TABLE *dj_audio_GtFTbl();
ST_DEVZJ_FUNREG_VIDEO_TABLE *dj_video_GtFTbl();
ST_DEVZJ_FUNREG_CAMIOT_TABLE *dj_camIot_GtFTbl();


ST_DEVZJ_FUNREG_POWER_TABLE *dj_power_GtFTbl();
ST_DEVZJ_FUNREG_OTA_TABLE *dj_ota_GtFTbl();
ST_DEVZJ_FUNREG_IOTHUB_TABLE *dj_iothub_GtFTbl();
ST_DEVZJ_FUNREG_CHANNEL_TABLE *dj_channel_GtFTbl();
ST_DEVZJ_FUNREG_NETWORK_TABLE *dj_network_GtFTbl();





int dev_zj_funcbReg();



#endif




