#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "basetypesJX.h"
#include "device_log.h"
#include "zj_type.h"
#include "zj_log.h"
#include "forZb_comCfg.h"

#include "forZb_network.h"
#include "dev_network.h"

#include "sdk_commonstruct.h"
#include "sdkout_impl.h" 


int fzb_SetWifi(EN_ZJ_NETWORK_TYPE enWifiType, char* pcSSID, char* pcPwd, int iEncrytType){

	if(enWifiType != EN_ZJ_NETWORK_TYPE_WIFI){
		DPRI_INFO("enWifiType not match:%d",enWifiType);
		return -1;
	}	

#ifdef MMACRO_NOFLASH_T3_E1102
	if( 0 != d_setWifi(pcSSID,pcPwd,iEncrytType) ){
		DPRI_INFO("d_setWifi err");
		return -1;		
	}
#endif

	return 0;
}

int fzb_GetWifi(ST_ZJ_WIFI_INFO stWifiInfo[16], unsigned int *puiWifiCount){
	return 0;
}

int fzb_GetNetInfo(ST_ZJ_NETWORK_INFO* pstNetInfo){
	T_SDK_NETWORK_PARAMS t_net_param = {0};

	if(0 != SDK_Cmd_Impl(SDKCMD_GET_NETWORK_PARAM, &t_net_param)){
		DPRI_INFO("SDKCMD_GET_NETWORK_PARAM err\n");
		return -1;
	}

	DPRI_INFO("fzb_GetNetInfo: wifitype:%d\n \
status:%d\n wifissid:%s\n wifipasswd:%s\n wifiencrypt:%d\n \
ip:%s\n mask:%s\n gateway:%s\n eht0mac:%s\n ra0mac:%s\n \
dns1:%s\n dns2:%s \n hostname:%s\n", 
		t_net_param.t_wireless_param.e_wifi_mode,
		t_net_param.t_wireless_param.e_wifi_connect_status,
		t_net_param.t_wireless_param.a_SSID,
		t_net_param.t_wireless_param.a_passwd,
		t_net_param.t_wireless_param.un_encrypt,
		t_net_param.a_IP,
		t_net_param.a_mask,
		t_net_param.a_gateway,
		t_net_param.a_wire_MAC,
		t_net_param.a_wireless_MAC,
		t_net_param.a_DNS[0],
		t_net_param.a_DNS[1],
		t_net_param.a_hostname
		);


	strncpy((char *)pstNetInfo->aucNetmask,t_net_param.a_mask,sizeof(pstNetInfo->aucNetmask));
	strncpy((char *)pstNetInfo->aucGateway,t_net_param.a_gateway,sizeof(pstNetInfo->aucGateway));
	strncpy((char *)pstNetInfo->aucIPAddr,t_net_param.a_IP,sizeof(pstNetInfo->aucIPAddr));
	strncpy((char *)pstNetInfo->aucMacAddr,t_net_param.a_wire_MAC,sizeof(pstNetInfo->aucMacAddr));
	strncpy((char *)pstNetInfo->aucWIFISSID,t_net_param.t_wireless_param.a_SSID,sizeof(pstNetInfo->aucWIFISSID));
	pstNetInfo->iNetType = 0;
//	pstNetInfo->iSignalType = 0;
//	pstNetInfo->iSigStrength = 0;
	return 0;
}





















