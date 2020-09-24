#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "zj_type.h"
#include "zj_log.h"
#include "forZb_comCfg.h"

#include "forZb_ota.h"

/*
int fzb_SetWifi(EN_ZJ_NETWORK_TYPE enWifiType, char* pcSSID, char* pcPwd, int iEncrytType){
	return 0;
}

int fzb_GetWifi(ST_ZJ_WIFI_INFO stWifiInfo[16], unsigned int *puiWifiCount){
	return 0;
}
int fzb_GetNetInfo(ST_ZJ_NETWORK_INFO* pstNetInfo){
	return 0;
} */


int fzb_NewVersionCb(unsigned char *pucNewVersion,unsigned int uiFileSize){
	return 0;
}
int fzb_VersonDataDownCb(unsigned char *pucPackage,unsigned int uiPacklen,unsigned int uiEndFlag){
	return 0;
}
int fzb_StopUpgrade(){
	return 0;
}
int fzb_CoverImageNotice(unsigned int uiCoverFlag){
	return 0;
}























