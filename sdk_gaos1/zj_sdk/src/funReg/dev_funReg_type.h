#ifndef DEV_FUNREG_TYPE_H_
#define DEV_FUNREG_TYPE_H_


#include "zj_type.h"
//ZJ_PFUN_SET_VIDEO_PARM

typedef int (*DFTYPE_Audio_WriteFrame)(unsigned char* pucFrame, int iLen, unsigned int uiTimestamp);
typedef int (*DFTYPE_GtMediaAudioData)(ZJ_HANDLE hHandle, unsigned char** ppucDataBuf, int* iDataLen, unsigned int* puiTimestamp);

typedef int (*DFTYPE_GetMediaAudioParam)(ZJ_HANDLE hHandle, ST_ZJ_AUDIO_PARAM* pstAudioParam);



typedef int (*DFTYPE_Video_WriteFrame)(int iStreamID, unsigned char* pucFrame, int iLen, unsigned int uiTimestamp, unsigned int uiFrameType);

typedef int (*DFTYPE_IoTEventInPut)(unsigned int uiAIIoTType, unsigned long long lluAIIoTID, int iEvent);





//power
typedef int (*DFTYPE_SetPowerLevel)(unsigned int uiPowerLevel);

//ota
typedef int (*DFTYPE_SetBurnningProgress)(unsigned int uiPercentage);

//iothub
typedef int (*DFTYPE_IoTHubWriteData)(unsigned char* pucData, int iLen);

//channel
typedef int (*DFTYPE_SendCustomData)(const unsigned char* pucPeerID, unsigned char* pucData, int iLen);


//network
typedef int (*DFTYPE_SetQRCodeString)(unsigned char *pstrQRCode);

typedef int (*DFTYPE_SetNetWorkType)(EN_ZJ_NETWORK_TYPE enNetType);


#endif




