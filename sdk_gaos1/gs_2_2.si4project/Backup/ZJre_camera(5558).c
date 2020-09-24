#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "device_log.h"
#include "zj_type.h"
#include "zj_log.h"
#include "zj_camera.h" 

#include "ZJre_comCfg.h" 
#include "forZb_camera.h"  

typedef struct stru_STRE_CAMERA_MSG{

	int vStreamid;
	int vResolutionAbility;
	int vEncAbility;
	int vStreamCount;
	ST_ZJ_VIDEO_PARAM vstVideoParam;
	ST_ZJ_VIDEO_PARAM vstVideoParam_1;
	int vEncAbility_1;
	int vResolutionAbility_1;

	ST_ZJ_AUDIO_PARAM astAudioParam;
	int aVolumn;
	int aOpenFlag;
	char *aStoragePath;

	char *sStoragePath;
	int sSDCardAbility;

	//iot
	int IRLedAbility;
	int CurWorkMode;
	//extend
//	int iLensCount;
}STRE_CAMERA_MSG;

static STRE_CAMERA_MSG  g_ST_camera_msg = {0};

static int member_init(STRE_CAMERA_MSG *p_cam){

	p_cam->vStreamCount = 2;
	
	p_cam->vStreamid = 0;
//	p_cam->vResolutionAbility = EN_ZJ_CARERA_RESOLUTION_ABILITY_480P;
	p_cam->vEncAbility = EN_ZJ_VIDEOENC_TYPE_H265;	
	p_cam->vstVideoParam.uiBitrate = EN_ZJ_CAMERA_BITRATE_TYPE_1024K;
	p_cam->vstVideoParam.uiEncodeType = EN_ZJ_VIDEOENC_TYPE_H265;
	p_cam->vstVideoParam.uiQuality = EN_ZJ_KEYFRAME_QUALITY_NORMAL;
	p_cam->vstVideoParam.uiResolution = EN_ZJ_CARERA_RESOLUTION_ABILITY_300W;
	p_cam->vstVideoParam.uiSmartEncFlag = 1;
	p_cam->vstVideoParam.uiRateType = 0;
	p_cam->vstVideoParam.uiFrameInterval = 15;
	p_cam->vstVideoParam.uiFramerate = 15;
	p_cam->vstVideoParam.uiHeight = 1296;
	p_cam->vstVideoParam.uiWidth = 2304;

	p_cam->vEncAbility_1 = EN_ZJ_VIDEOENC_TYPE_H265;	
	p_cam->vstVideoParam_1.uiBitrate = EN_ZJ_CAMERA_BITRATE_TYPE_256K;
	p_cam->vstVideoParam_1.uiEncodeType = EN_ZJ_VIDEOENC_TYPE_H265;
	p_cam->vstVideoParam_1.uiQuality = EN_ZJ_KEYFRAME_QUALITY_NORMAL;
	p_cam->vstVideoParam_1.uiResolution = EN_ZJ_CARERA_RESOLUTION_ABILITY_360P;
	p_cam->vstVideoParam_1.uiSmartEncFlag = 1;
	p_cam->vstVideoParam_1.uiRateType = 0;
	p_cam->vstVideoParam_1.uiFrameInterval = 15;
	p_cam->vstVideoParam_1.uiFramerate = 15;
	p_cam->vstVideoParam_1.uiHeight = 360;
	p_cam->vstVideoParam_1.uiWidth = 640;	

	p_cam->astAudioParam.uiEncodeType = EN_ZJ_AUDIOENC_TYPE_G711A;
	p_cam->astAudioParam.uiSampleRate = 8000;
	p_cam->astAudioParam.uiChannel = 1;
	p_cam->astAudioParam.uiDepth = 16;
	p_cam->aVolumn = 5;
	p_cam->aOpenFlag = 1;

	if( !access(SD_PATH,0)){
		DPRI_INFO("[systemInit]checkPath exist:%s\n",SD_PATH);
		p_cam->aStoragePath = AUDIO_SAVEFILE_PATH;
		p_cam->sStoragePath = SD_PATH;
		p_cam->sSDCardAbility = 1;		
	}else{
		DPRI_INFO("[systemInit]checkPath NO exist:%s\n",SD_PATH);
		p_cam->aStoragePath = NULL;
		p_cam->sStoragePath = NULL;
		p_cam->sSDCardAbility = 0;	
	}	
//	p_cam->aStoragePath = AUDIO_SAVEFILE_PATH;
//	p_cam->sStoragePath = SD_PATH;
//	p_cam->sSDCardAbility = 1;
	//iot
	p_cam->IRLedAbility = 1;
	p_cam->CurWorkMode = EN_ZJ_IRMODE_AUTO;
	return 0;
}

static int configure_init(STRE_CAMERA_MSG *pcam){
	ZJ_SetStreamCount(pcam->vStreamCount);
	ZJ_SetResolutionAbility(pcam->vStreamid, pcam->vResolutionAbility);/*主码流，设置分辨率能力集；支持多种按位与 EN_ZJ_CARERA_RESOLUTION_ABILITY 必须设置*/	 
	ZJ_SetVideoEncodeAbility(pcam->vStreamid, pcam->vEncAbility);	
	ZJ_SetVideoEncParam(pcam->vStreamid,  &pcam->vstVideoParam);	

	ZJ_SetResolutionAbility(1, pcam->vResolutionAbility_1);/*主码流，设置分辨率能力集；支持多种按位与 EN_ZJ_CARERA_RESOLUTION_ABILITY 必须设置*/	 
	ZJ_SetVideoEncodeAbility(1, pcam->vEncAbility_1);	
	ZJ_SetVideoEncParam(1,  &pcam->vstVideoParam_1);		

	ZJ_SetAudioEncParm(&pcam->astAudioParam);
	ZJ_SetAudioVolumn(pcam->aVolumn);
	ZJ_SetCamerMicOpenFlag(pcam->aOpenFlag);
	
	ZJ_SetDevSoudFilePath(pcam->aStoragePath);
	ZJ_SetStoragePath(pcam->sStoragePath);
	ZJ_SetSDCardAbility(pcam->sSDCardAbility);

	//iot 	// 设置IRLed红外灯控制模式 ：EN_ZJ_IRMODE；
	ZJ_SetIRLedAbility(pcam->IRLedAbility);   
	ZJ_SetCamerCurIRWorkMode(pcam->CurWorkMode);

	//ptz	
#ifdef MMACRO_NOFLASH_T3_E1102
	ZJ_SetPTZAbility(0x03);
	ZJ_SetPTZSpeedAbility(0);
#endif



	return 0;
}

static int cbfun_register(void){

	ZJ_SetImageInversionCB(fzb_ImageInversion);/*画面翻转回调接口注册，告诉设备画面进行翻转*/	 
	ZJ_SetVideoNeedIFrameCB(fzb_VideoNeedIFrame);/*强制I帧回调接口*/	 
	ZJ_SetVideoEncSwitchCB(fzb_VideoSwitch);/*视频编码开关回调接口注册 通过该接口控制视频是否编码*/
	ZJ_Video_SetGetJpegCB(fzb_VideoGetJpeg);	

    ZJ_SetAudioEncSwitchCB(fzb_AudioSwitch);/*设置音频编码开关*/    
    ZJ_SetMediaToPlayCB(fzb_MediaToPlay);  /*语音对讲接收回调接口*/  

    ZJ_SetSDCardCB(fzb_FormatSDCard, fzb_GetSDCardInfo, fzb_CheckSDCard);
	//extend
	ZJ_SetIRLedSwitchCB(fzb_IRLedSwitch);
	ZJ_SetCameraSwitchCB(fzb_CameraSwitch);
	ZJ_SetCameraPTZCB( fzb_OnPTZ,  fzb_PTZGetPoint,
                fzb_PTZGotoPoint , fzb_PTZAutoCheck ,
                 fzb_CruiseStart,fzb_PtzStop );

	ZJ_SetRecordStatusCB(fzb_RecordStatus );
//	ZJ_SetCameraScanFrequeryCB( fzb_ScanFrequery);
	ZJ_SetOSDSettingCB(fzb_OSDSetting );
	ZJ_SetShowTimeOSDCB( fzb_CtrlTimeOSD,fzb_CtrlCustomOsd );

//	ZJ_SetAudioVolumnCB(fzb_AudioVolumnAdjust );
#ifndef MACRO_ZJ
	ZJ_SetAudioVolumnCB(fzb_AudioVolumnAdjust );
#else
	ZJ_SetAudioVolumnCB(fzb_AudioVolumnAdjust_PZJ );
#endif


	
	ZJ_SetVideoEncParamCB( fzb_SetVideoParm);
//	ZJ_SetVideoAdjustCB(fzb_VideoAdjust );
	ZJ_SetSwitchLenCB( fzb_SwitchLen);
	ZJ_SetCamWdrOpenFlagCB(fzb_SetWideDynamicCam );

#ifndef MACRO_ZJ
	ZJ_SetCamAlarmSoundFileCB( fzb_DelSoundFile , fzb_GetSoudFiles );
#else
	ZJ_SetCamAlarmSoundFileCB( fzb_DelSoundFile , fzb_GetSoudFiles_PZJ );
#endif	

//ptz
#ifdef MMACRO_NOFLASH_T3_E1102
//	ZJ_SetPTZAbility(0x03);
	ZJ_SetCameraPTZCB( fzb_OnPTZ,fzb_PTZGetPoint,fzb_PTZGotoPoint,fzb_PTZAutoCheck,fzb_CruiseStart,fzb_PtzStop);
#endif

//	ZJ_SetRelayDevAwakeCB( fzb_SetRelayDevAwakeStatus);
	
	return 0;
}

int zjre_cameraInit(void){
	member_init(&g_ST_camera_msg);
	configure_init(&g_ST_camera_msg);
	cbfun_register();
	return 0;
}

int zjre_cameraDestory(void){
	fzb_VideoGetJpeg_destorySP();
	return 0;
}

int zjre_packF_sdMountPro(int mountFlag){

	if(mountFlag == 1){
		ZJ_SetDevSoudFilePath(AUDIO_SAVEFILE_PATH);
		ZJ_SetStoragePath(SD_PATH);
		ZJ_SetSDCardAbility(1);	
		return 0;
	}else if(mountFlag == 0){
		ZJ_SetDevSoudFilePath(NULL);
		ZJ_SetStoragePath(NULL);
		ZJ_SetSDCardAbility(0); 
		return 0;
	}else{
		return -1;
	}

}

