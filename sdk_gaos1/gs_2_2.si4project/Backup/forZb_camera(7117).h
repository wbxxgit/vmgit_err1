#ifndef FORZB_CAMERA_H_
#define FORZB_CAMERA_H_

#include "zj_type.h"

typedef struct ST_STRU_VOICEPLAY
{
    int  iRun;
	unsigned char openflag;
    const char *pcPeerID;
    ZJ_HANDLE hPlayHandle;
}ST_H_VOICEPLAY;

ST_H_VOICEPLAY *stH_glget_audio();



int fzb_ImageInversion(int iState);
int fzb_VideoNeedIFrame(int iStreamID,unsigned int uiKeyQuality);
int fzb_VideoSwitch(int iStreamID, int iState);
int fzb_VideoGetJpeg(EN_ZJ_PICTURE_TYPE enPicType, unsigned char** ppucJpegBuf);
int fzb_VideoGetJpeg_destorySP();



int fzb_AudioSwitch(int iState);
int fzb_MediaToPlay(const char* pcPeerID, ZJ_HANDLE hPlayHandle, int iStreamType, int iStatus);

//sd
int fzb_FormatSDCard();
int fzb_GetSDCardInfo(unsigned int *piTotalSize, unsigned int *piFreeSize);
int fzb_CheckSDCard(int *piErrCode);

//extend

int fzb_IRLedSwitch(int iState);
int fzb_CameraSwitch(int iState);
int fzb_OnPTZ(EN_ZJ_CAMERA_PTZ_CONTROL enPTZControl, int iSpeed, int iPTZStep);
int fzb_PTZGetPoint(int* piX, int* piY);
int fzb_PTZGotoPoint(int iX, int iY);
int fzb_PTZAutoCheck();
int fzb_CruiseStart(int iPresetPointNum, ST_ZJ_CAMERA_CRUISE_PRESET* pstPresets);
int fzb_PtzStop();

int fzb_RecordStatus(int iStatus);
int fzb_ScanFrequery(unsigned int uiScanFrequery);
int fzb_OSDSetting(int iPosition, char* pcOSDName);
int fzb_CtrlTimeOSD(int iOpenFlag);
int fzb_CtrlCustomOsd(int iOpenFlag);
int fzb_AudioVolumnAdjust(int iVolumn);
int fzb_AudioVolumnAdjust_PZJ(int iSpeakerId,int iVolumn);

int fzb_SetVideoParm(int iStreamID,ST_ZJ_VIDEO_PARAM *pstVideoParm);
int fzb_VideoAdjust(int iStreamID, int iAdjust);
int fzb_SwitchLen(int iLenId);
int fzb_SetWideDynamicCam(unsigned int uiOpenFlag);
int fzb_DelSoundFile(unsigned char *pucSoundName);
int fzb_GetSoudFiles(unsigned int *piTotalSize, unsigned int *piFreeSize, 
					unsigned char aucSoundList[32][64], unsigned int *uiSoundListCnt);

int fzb_GetSoudFiles_PZJ( unsigned int *piTotalSize, unsigned int *piFreeSize, 
		unsigned char aucSoundList[32][64], unsigned int *uiSoundListCnt,unsigned int uiRingType);

int fzb_SetRelayDevAwakeStatus(unsigned int iAwakeStatus);








#endif




