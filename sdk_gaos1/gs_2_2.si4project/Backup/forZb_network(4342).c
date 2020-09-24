#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "zj_type.h"
#include "zj_log.h"
#include "forZb_comCfg.h"

#include "forZb_network.h"
#include "dev_network.h"


int fzb_SetWifi(EN_ZJ_NETWORK_TYPE enWifiType, char* pcSSID, char* pcPwd, int iEncrytType){

	if(enWifiType != EN_ZJ_NETWORK_TYPE_WIFI){
		ZJ_LOG_INF("enWifiType not match:%d",enWifiType);
		return -1;
	}	

//	devS_SetWifi(pcSSID,pcPwd,iEncrytType);
	if( 0 != d_setWifi(pcSSID,pcPwd,iEncrytType) ){
		ZJ_LOG_INF("d_setWifi err");
		return -1;		
	}
	return 0;
}

int fzb_GetWifi(ST_ZJ_WIFI_INFO stWifiInfo[16], unsigned int *puiWifiCount){
	return 0;
}
int fzb_GetNetInfo(ST_ZJ_NETWORK_INFO* pstNetInfo){
	return 0;
}




















