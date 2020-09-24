#ifndef FORZB_SYSTEM_H_
#define FORZB_SYSTEM_H_

#include "zj_type.h"


int fzb_SystemStatusCB(EN_ZJ_SERVER_STATUS enDeviceStatus, int iErrCode);

int fzb_SetDeviceRebootCbFunc();
int fzb_funSetTimeZone(int iSyncFlag, int iZone, char* pcDatetime);
int fzb_funSetTimeZone_PZJ(int iSyncFlag, int iZone, char* pcDatetime,char *pucDst);

int fzb_funGetTimeZone(int *piZone,unsigned char *pucTime,int *piSyncFlag);
int fzb_funRestoreFactorySetting();
int fzb_funCfgItemChangeCb(unsigned int uiCfgItem);
//log
int fzb_SetDevCollectLogFilesFunc(unsigned char *pucPeerId,unsigned int iSessionId,unsigned char *pcDesInfo);









#endif




