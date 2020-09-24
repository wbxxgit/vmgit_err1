#ifndef FORZB_POWER_H_
#define FORZB_POWER_H_

#include "zj_type.h"


/*
int fzb_SetWifi(EN_ZJ_NETWORK_TYPE enWifiType, char* pcSSID, char* pcPwd, int iEncrytType);
int fzb_GetWifi(ST_ZJ_WIFI_INFO stWifiInfo[16], unsigned int *puiWifiCount);
int fzb_GetNetInfo(ST_ZJ_NETWORK_INFO* pstNetInfo);
*/


int fzb_StartSleep(int iWaitSecond);


#endif




