#ifndef FORZB_OTA_H_
#define FORZB_OTA_H_

#include "zj_type.h"


/*
int fzb_SetWifi(EN_ZJ_NETWORK_TYPE enWifiType, char* pcSSID, char* pcPwd, int iEncrytType);
int fzb_GetWifi(ST_ZJ_WIFI_INFO stWifiInfo[16], unsigned int *puiWifiCount);
int fzb_GetNetInfo(ST_ZJ_NETWORK_INFO* pstNetInfo); */

int fzb_NewVersionCb(unsigned char *pucNewVersion,unsigned int uiFileSize);
int fzb_VersonDataDownCb(unsigned char *pucPackage,unsigned int uiPacklen,
								unsigned int uiEndFlag);
int fzb_StopUpgrade();
int fzb_CoverImageNotice(unsigned int uiCoverFlag);




#endif




