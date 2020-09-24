#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "zj_type.h"
#include "zj_log.h"

#include "dev_zj_funReg.h"
#include "forZb_comCfg.h"
#include "forZb_camera.h"
#include "forZbSeg_camera.h" 

#include "sdk_commonstruct.h"
#include "sdkout_impl.h" 


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
	ZJ_LOG_INF("ImageInversion exe,istate:%d\n",iState);
	int para_mirror;

	para_mirror = getMap_videoMir(iState);
	if(para_mirror == -1)
		return -1;
	
	if (0 != SDK_Cmd_Impl(SDKCMD_SET_VIDEO_ENCODE_MIRROR,(void *)&para_mirror))	{
	   ZJ_LOG_INF("callSDKCMD_SET_SNAPSHOT_PATH fail .\n");           
	   return -1;
	} 	

	ZJ_LOG_INF("para_mirror:%d",para_mirror); 
	return 0;
}

int fzb_VideoNeedIFrame(int iStreamID,unsigned int uiKeyQuality){
	return 0;
}

int fzb_VideoSwitch(int iStreamID, int iState){
	printf("VideoSwitch iStreamID[%d],iState[%d]\n",iStreamID,iState);
	
	if(SegCam_setVideoArrSw(iStreamID,iState) != 0)
		return -1;
	
	return 0;
}

static int SDK_SnapShot()
{
	T_SDK_PIC_PATH un_snap_path;
	memset(&un_snap_path, 0, sizeof(un_snap_path));
	strcpy((un_snap_path.pic_path), "/mnt/app/1.jpg"); //the folder must exist and can be write.
	ZJ_LOG_INF("SDK_SnapShot pic_path >>>>>>>>>>%s",un_snap_path.pic_path);
	if (0 != SDK_Cmd_Impl(SDKCMD_SET_SNAPSHOT_PATH,(void *)&un_snap_path))
	{
	   ZJ_LOG_INF("callSDKCMD_SET_SNAPSHOT_PATH fail .\n");           
	   return -1;
	} 	
	return 0;
}

int fzb_VideoGetJpeg(EN_ZJ_PICTURE_TYPE enPicType, unsigned char **ppucJpegBuf){

	FILE *fjge  = NULL;
	char *filepath = NULL;
	unsigned int filesize = 0;
	char *tmpmallocp = NULL;

	ZJ_LOG_INF("GetJpeg callback exe !enPicType:%d",enPicType);
	if( SDK_SnapShot() != 0){
		ZJ_LOG_INF("SDK_SnapShot err!\n");
		return -1;
	}

	filepath = "/mnt/app/1.jpg";
	fjge  = fopen(filepath,"rb"); 
	if(NULL==fjge){
		ZJ_LOG_INF("fopen PATH error!\n");
		return -1;
	}   
	fseek(fjge,0, SEEK_END);
	filesize = ftell(fjge);//读取图片的大小长度
	fseek(fjge, 0, SEEK_SET);
	ZJ_LOG_INF("ftell filesize:%d",filesize);
	if(0 == filesize)
		return -1;
	tmpmallocp = (char *)realloc(PcSnapPic, filesize);
	if(tmpmallocp == NULL){
		ZJ_LOG_INF("device video snap realloc buff failed\n");
		return -1;
	}
	PcSnapPic = tmpmallocp;
	if(0 == fread(PcSnapPic, 1, filesize, fjge)){
		fclose(fjge);
		ZJ_LOG_INF("fread err\n");
		return -1;
	}
	*ppucJpegBuf = (unsigned char *)PcSnapPic;
	ZJ_LOG_INF("*ppucJpegBuf :%p",*ppucJpegBuf);
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
	ZJ_LOG_INF("AudioSwitch iState[%d]\n",iState);
	SegCam_setAudioSw(iState);
	return 0;
}

int fzb_MediaToPlay(const char* pcPeerID, ZJ_HANDLE hPlayHandle, int iStreamType, int iStatus){

	ST_ZJ_AUDIO_PARAM stAudioParam = {0};
	stH_glget_audio()->pcPeerID = pcPeerID;
	stH_glget_audio()->hPlayHandle  =  hPlayHandle;
	stH_glget_audio()->iRun = iStatus;
	ZJ_LOG_INF("audio start voice to play , iStreamType [%d], iStatus [%d]", iStreamType,iStatus);

	if( NULL == dj_audio_GtFTbl()->f_GetMediaAudioParam){
		ZJ_LOG_INF("f_GetMediaAudioParam no register!\n");
		return -1;			
	}	
	dj_audio_GtFTbl()->f_GetMediaAudioParam(stH_glget_audio()->hPlayHandle , &stAudioParam);
	ZJ_LOG_INF("device audio encode param:");
	ZJ_LOG_INF(" 			uiEncodeType: %u", stAudioParam.uiEncodeType);
	ZJ_LOG_INF(" 			uiSampleRate: %u", stAudioParam.uiSampleRate);
	ZJ_LOG_INF(" 			   uiChannel: %u", stAudioParam.uiChannel);
	ZJ_LOG_INF(" 				 uiDepth: %u", stAudioParam.uiDepth);
	return 0;
}

//sd
int fzb_FormatSDCard(){
    ZJ_LOG_INF("FormatSDCard exe...\n");
	int retcode = SDK_Cmd_Impl(SDKCMD_FORMAT_STORAGE_REQ, NULL);
	if(retcode < 0)
	{
		ZJ_LOG_INF("SDKCMD_FORMAT_STORAGE_REQ fail\n");
		return -1;
	}
	ZJ_LOG_INF("SDKCMD_FORMAT_STORAGE_REQ succeed\n");
    return 0;
}

int fzb_GetSDCardInfo(unsigned int *piTotalSize, unsigned int *piFreeSize){  
	FILE *fstream = NULL;
	char buff[1024];	
	
	memset(buff,0,sizeof(buff));	
	if(NULL == ( fstream = popen("df -m","r"))){	
			fprintf(stderr,"execute command failed:%s",strerror(errno));
			pclose(fstream);
			return -1;
	}	
	while( NULL != fgets(buff,sizeof(buff),fstream))	
			printf("%s",buff);	
	pclose(fstream);

	memset(buff,0,sizeof(buff));
	if(NULL == ( fstream = popen("df -m|grep sd|awk '{print $2}'","r"))){	
			fprintf(stderr,"execute command failed:%s",strerror(errno));
			pclose(fstream);
			return -1;
	}		
	while( NULL != fgets(buff,sizeof(buff),fstream)){
		ZJ_LOG_INF("$2:%s",buff);
		if( buff[0]=='\r' ||buff[0]=='\n')
			continue;
		else
			break;	
			
	}	

	pclose(fstream);
	*piTotalSize = atoi(buff);
	
	memset(buff,0,sizeof(buff));
	if(NULL == ( fstream = popen("df -m|grep sd|awk '{print $4}'","r"))){	
			fprintf(stderr,"execute command failed:%s",strerror(errno));
			pclose(fstream);
			return -1;
	}	

	while( NULL != fgets(buff,sizeof(buff),fstream)){
		ZJ_LOG_INF("$4:%s",buff);
		if( buff[0]=='\r' ||buff[0]=='\n')
			continue;
		else
			break;	
	}	

	pclose(fstream);
	*piFreeSize = atoi(buff);
	ZJ_LOG_INF("GetSDCardInfo piTotalSize:%d,piFreeSize_1118:%d",*piTotalSize,*piFreeSize);	
	return 0;
}

int fzb_CheckSDCard(int *piErrCode){
    ZJ_LOG_INF("CheckSDCard normal,return 0");
	*piErrCode = 0;
	return 0;
}

//extend

int fzb_IRLedSwitch(int iState){
	return 0;
}
int fzb_CameraSwitch(int iState){
	ZJ_LOG_INF("fzb_CameraSwitch iState:%d",iState);	
	return 0;
}
int fzb_OnPTZ(EN_ZJ_CAMERA_PTZ_CONTROL enPTZControl, int iSpeed, int iPTZStep){
	return 0;
}
int fzb_PTZGetPoint(int* piX, int* piY){
	return 0;
}

int fzb_PTZGotoPoint(int iX, int iY){
	return 0;
}
int fzb_PTZAutoCheck(){
	return 0;
}
int fzb_CruiseStart(int iPresetPointNum, ST_ZJ_CAMERA_CRUISE_PRESET* pstPresets){
	return 0;
}
int fzb_PtzStop(){
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
















