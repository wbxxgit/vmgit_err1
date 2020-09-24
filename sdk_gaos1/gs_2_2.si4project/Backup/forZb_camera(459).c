#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "device_log.h"
#include "zj_type.h"
#include "zj_log.h"


#include "dev_zj_funReg.h"
#include "forZb_comCfg.h"
#include "forZb_camera.h"
#include "forZbSeg_camera.h" 

#include "sdk_commonstruct.h"
#include "sdkout_impl.h" 
#include "CommonUtils.h"

#include "dev_ptz.h"




static char *PcSnapPic = NULL;
static ST_H_VOICEPLAY st_H_audio = {0};


ST_H_VOICEPLAY *stH_glget_audio(){
    return  &st_H_audio;
}



#define VIDEOMIRROR_NONE       0
#define VIDEOMIRROR_HORIZONTAL 1
#define VIDEOMIRROR_VERTICAL   2
#define VIDEOMIRROR_H_V        3

static int getMap_videoMir(int state){
	if(state == 1)
		return VIDEOMIRROR_NONE;
	if(state == 2)
		return VIDEOMIRROR_H_V;
	return -1;
}
int fzb_ImageInversion(int iState){
	DPRI_INFO("ImageInversion exe,istate:%d\n",iState);
	int para_mirror;

	para_mirror = getMap_videoMir(iState);
	if(para_mirror == -1)
		return -1;
	
	if (0 != SDK_Cmd_Impl(SDKCMD_SET_VIDEO_ENCODE_MIRROR,(void *)&para_mirror))	{
	   DPRI_INFO("callSDKCMD_SET_SNAPSHOT_PATH fail .\n");           
	   return -1;
	} 	

	DPRI_INFO("para_mirror:%d",para_mirror); 
	return 0;
}

int fzb_VideoNeedIFrame(int iStreamID,unsigned int uiKeyQuality){
	return 0;
}

int fzb_VideoSwitch(int iStreamID, int iState){
	DPRI_INFO("VideoSwitch iStreamID[%d],iState[%d]\n",iStreamID,iState);
	
	if(SegCam_setVideoArrSw(iStreamID,iState) != 0)
		return -1;
	
	return 0;
}

static int SDK_SnapShot()
{
	T_SDK_PIC_PATH un_snap_path;
	memset(&un_snap_path, 0, sizeof(un_snap_path));
	strcpy((un_snap_path.pic_path), "/mnt/app/1.jpg"); //the folder must exist and can be write.
	DPRI_INFO("SDK_SnapShot pic_path >>>>>>>>>>%s\n",un_snap_path.pic_path);
	if (0 != SDK_Cmd_Impl(SDKCMD_SET_SNAPSHOT_PATH,(void *)&un_snap_path))
	{
	   DPRI_INFO("callSDKCMD_SET_SNAPSHOT_PATH fail .\n");           
	   return -1;
	} 	
	return 0;
}

int fzb_VideoGetJpeg(EN_ZJ_PICTURE_TYPE enPicType, unsigned char **ppucJpegBuf){

	FILE *fjge  = NULL;
	char *filepath = NULL;
	unsigned int filesize = 0;
	char *tmpmallocp = NULL;

	DPRI_INFO("GetJpeg callback exe !enPicType:%d\n",enPicType);
	if( SDK_SnapShot() != 0){
		DPRI_INFO("SDK_SnapShot err!\n");
		return -1;
	}

	filepath = "/mnt/app/1.jpg";
	fjge  = fopen(filepath,"rb"); 
	if(NULL==fjge){
		DPRI_INFO("fopen PATH error!\n");
		return -1;
	}   
	fseek(fjge,0, SEEK_END);
	filesize = ftell(fjge);//读取图片的大小长度
	fseek(fjge, 0, SEEK_SET);
	DPRI_INFO("ftell filesize:%d\n",filesize);
	if(0 == filesize)
		return -1;
	tmpmallocp = (char *)realloc(PcSnapPic, filesize);
	if(tmpmallocp == NULL){
		DPRI_INFO("device video snap realloc buff failed\n");
		return -1;
	}
	PcSnapPic = tmpmallocp;
	if(0 == fread(PcSnapPic, 1, filesize, fjge)){
		fclose(fjge);
		DPRI_INFO("fread err\n");
		return -1;
	}
	*ppucJpegBuf = (unsigned char *)PcSnapPic;
	DPRI_INFO("*ppucJpegBuf :%p\n",*ppucJpegBuf);
	fclose(fjge);	
    return filesize;  
}

int fzb_VideoGetJpeg_destorySP(){
	free(PcSnapPic);
	PcSnapPic = NULL;	
	return 0;
}


//audio
int fzb_AudioSwitch(int iState){
	DPRI_INFO("AudioSwitch iState[%d]\n",iState);
	SegCam_setAudioSw(iState);
	return 0;
}

int fzb_MediaToPlay(const char* pcPeerID, ZJ_HANDLE hPlayHandle, int iStreamType, int iStatus){

	ST_ZJ_AUDIO_PARAM stAudioParam = {0};
	stH_glget_audio()->pcPeerID = pcPeerID;
	stH_glget_audio()->hPlayHandle  =  hPlayHandle;
	stH_glget_audio()->iRun = iStatus;
	DPRI_INFO("audio start voice to play , iStreamType [%d], iStatus [%d]\n", iStreamType,iStatus);

	if( NULL == dj_audio_GtFTbl()->f_GetMediaAudioParam){
		DPRI_INFO("f_GetMediaAudioParam no register!\n");
		return -1;			
	}	
	dj_audio_GtFTbl()->f_GetMediaAudioParam(stH_glget_audio()->hPlayHandle , &stAudioParam);
	DPRI_INFO("device audio encode param:\n");
	DPRI_INFO(" 			uiEncodeType: %u\n", stAudioParam.uiEncodeType);
	DPRI_INFO(" 			uiSampleRate: %u\n", stAudioParam.uiSampleRate);
	DPRI_INFO(" 			   uiChannel: %u\n", stAudioParam.uiChannel);
	DPRI_INFO(" 				 uiDepth: %u\n", stAudioParam.uiDepth);
	return 0;
}

//sd
int fzb_FormatSDCard(){
    DPRI_INFO("FormatSDCard exe...\n");
	int retcode = SDK_Cmd_Impl(SDKCMD_FORMAT_STORAGE_REQ, NULL);
	if(retcode < 0)
	{
		DPRI_INFO("SDKCMD_FORMAT_STORAGE_REQ fail\n");
		return -1;
	}
	DPRI_INFO("SDKCMD_FORMAT_STORAGE_REQ succeed\n");
    return 0;
}

int fzb_GetSDCardInfo(unsigned int *piTotalSize, unsigned int *piFreeSize){  

	T_SDK_STORAGE_INFO storage_info;
	memset(&storage_info, 0, sizeof(T_SDK_STORAGE_INFO));
	if(SDK_Cmd_Impl(SDKCMD_GET_STORAGE_INFO, (void *)&storage_info) < 0)
	{
		DPRI_INFO("SD CARD NULL\n");
		*piTotalSize = 0;
		*piFreeSize = 0;
		DPRI_INFO("retsdd ,total:%d,free:%d\n",*piTotalSize,*piFreeSize);

	}else{
		DPRI_INFO("ret1 ,total:%d,free:%d,USED:%d\n",storage_info.a_total_size,storage_info.a_free_size,storage_info.a_used_size);
		*piTotalSize = storage_info.a_total_size;
		*piFreeSize = storage_info.a_free_size;
		DPRI_INFO("retsdd ,total:%d,free:%d\n",*piTotalSize,*piFreeSize);	
	}	
	return 0;
/*
	tf_info info2;
	memset(&info2,0,sizeof(tf_info));
	DPRI_INFO("fzb_GetSDCardInfo ret -1\n");
	int retcode = SDK_Cmd_Impl(SDKCMD_GET_SD_CARD_INFO,(void*)(&info2));
	if(retcode != 0)
	{
		return -1;
	}
	DPRI_INFO("ret1 ,total:%lld,free:%lld,USED:%lld\n",info2.a_total_size,info2.a_free_size,info2.a_used_size);
	*piTotalSize = info2.a_total_size/1024;
	*piFreeSize = info2.a_free_size/1024;

	DPRI_INFO("retsdd ,total:%d,free:%d\n",*piTotalSize,*piFreeSize);
	return 0; */

}

int fzb_CheckSDCard(int *piErrCode){
    DPRI_INFO("CheckSDCard normal,return 0\n");
	*piErrCode = 0;
	return 0;
}

//extend

int fzb_IRLedSwitch(int iState){
	return 0;
}
int fzb_CameraSwitch(int iState){
	DPRI_INFO("fzb_CameraSwitch iState:%d\n",iState);	
	return 0;
}

/*
static int dev_PTZrotate(EN_ZJ_CAMERA_PTZ_CONTROL direction,u32 durationMs){

	if(durationMs > 2000)
		return -1;
	int retcode = 0;
	long tmpcmd;
	switch (direction)
		{
		case EN_ZJ_CAMERA_PTZ_CONTROL_LEFT:
			tmpcmd = SDKCMD_SET_PTZ_TURN_LEFT;
			break;
		case EN_ZJ_CAMERA_PTZ_CONTROL_RIGHT:
			tmpcmd = SDKCMD_SET_PTZ_TURN_RIGHT;
			break;
		case EN_ZJ_CAMERA_PTZ_CONTROL_UP:
			tmpcmd = SDKCMD_SET_PTZ_TURN_UP;
			break;
		case EN_ZJ_CAMERA_PTZ_CONTROL_DOWN:
			tmpcmd = SDKCMD_SET_PTZ_TURN_DOWN;
			break;		
		default:tmpcmd = -1;break;			
		}
	if(tmpcmd == -1)
		return -1;
	
	retcode = SDK_Cmd_Impl(tmpcmd, NULL);
	if(retcode != 0)
	{
		DPRI_INFO("SDKCMD_SET_PTZ_TURN_LEFT tmpcmd error\n");
		return -1;
	}
	usleep(durationMs*1000);
	retcode = SDK_Cmd_Impl(SDKCMD_SET_PTZ_STOP, NULL);
	if(retcode != 0)
	{
		DPRI_INFO("SDKCMD_SET_RECORD_DEFAULT_PARAM error\n");
		return -1;
	}
	DPRI_INFO("dev_PTZrotate exe\n");
	return 0;
}*/



int fzb_OnPTZ(EN_ZJ_CAMERA_PTZ_CONTROL enPTZControl, int iSpeed, int iPTZStep){
	DPRI_INFO("fzb_OnPTZ:enPTZControl[%d],iSpeed[%d],iPTZStep[%d]\n",enPTZControl,iSpeed,iPTZStep);

//	if(0 !=dev_PTZrotate(enPTZControl,100) )
//		DPRI_INFO("0 !=dev_PTZrotate \n");

	//int dev_setRotateSta(EN_ZJ_CAMERA_PTZ_CONTROL orien);
//	dev_setRotateSta(enPTZControl);
	dev_pushRotateCmd(enPTZControl);

//	DPRI_INFO("dev_pushRotateCmd exe \n");
	return 0;
}

int fzb_PTZGetPoint(int* piX, int* piY){
	DPRI_INFO("exe----fzb_PTZGetPoint,* piX[%d],* piY[%d]\n",*piX,*piY);
	return 0;
}

int fzb_PTZGotoPoint(int iX, int iY){
	DPRI_INFO("exe----fzb_PTZGotoPoint,iX[%d],iY[%d]\n",iX,iY);

	return 0;
}
int fzb_PTZAutoCheck(){
	DPRI_INFO("exe----fzb_PTZAutoCheck\n");

	return 0;
}
int fzb_CruiseStart(int iPresetPointNum, ST_ZJ_CAMERA_CRUISE_PRESET* pstPresets){
	DPRI_INFO("exe----fzb_CruiseStart,iPresetPointNum[%d]\n",iPresetPointNum);
	DPRI_INFO("fzb_CruiseStart:pstPresets->Idx[%d]\n",pstPresets->Idx);
	DPRI_INFO("fzb_CruiseStart:pstPresets->iX[%d]\n",pstPresets->iX);
	DPRI_INFO("fzb_CruiseStart:pstPresets->iY[%d]\n",pstPresets->iY);
	DPRI_INFO("fzb_CruiseStart:pstPresets->iDwellTime[%d]\n",pstPresets->iDwellTime);
	DPRI_INFO("fzb_CruiseStart:pstPresets->iSpeed[%d]\n",pstPresets->iSpeed);
	return 0;
}
int fzb_PtzStop(){
	DPRI_INFO("exe----fzb_PtzStop\n");
	return 0;
}


//13
int fzb_RecordStatus(int iStatus){
	return 0;
}
int fzb_ScanFrequery(unsigned int uiScanFrequery){
	return 0;
}
int fzb_OSDSetting(int iPosition, char* pcOSDName){
	return 0;
}
int fzb_CtrlTimeOSD(int iOpenFlag){
	return 0;
}
int fzb_CtrlCustomOsd(int iOpenFlag){
	return 0;
}
int fzb_AudioVolumnAdjust(int iVolumn){
	return 0;
}
int fzb_AudioVolumnAdjust_PZJ(int iSpeakerId,int iVolumn){
	return 0;
}

int fzb_SetVideoParm(int iStreamID,ST_ZJ_VIDEO_PARAM *pstVideoParm){
	return 0;
}
int fzb_VideoAdjust(int iStreamID, int iAdjust){
	return 0;
}
int fzb_SwitchLen(int iLenId){
	return 0;
}
int fzb_SetWideDynamicCam(unsigned int uiOpenFlag){
	return 0;
}
int fzb_DelSoundFile(unsigned char *pucSoundName){
	return 0;
}
int fzb_GetSoudFiles(unsigned int *piTotalSize, unsigned int *piFreeSize, unsigned char aucSoundList[32][64], unsigned int *uiSoundListCnt){
	return 0;
}

int fzb_GetSoudFiles_PZJ( unsigned int *piTotalSize, unsigned int *piFreeSize, 
		unsigned char aucSoundList[32][64], unsigned int *uiSoundListCnt,unsigned int uiRingType){
	return 0;
}

int fzb_SetRelayDevAwakeStatus(unsigned int iAwakeStatus){
	return 0;
}
















