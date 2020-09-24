#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "zj_type.h"
#include "zj_log.h"

#include "ZJre_comCfg.h" 

#include "zj_channel.h" 

#include "forZb_channel.h"  

typedef struct stru_STRE_CHANNEL_MSG{

	unsigned int SetWifiAbility;

}STRE_CHANNEL_MSG;

static STRE_CHANNEL_MSG  g_ST_channel_msg = {0};

static int member_init(STRE_CHANNEL_MSG *p_cam){
//	p_cam->SetWifiAbility = 1;


	return 0;
}

static int configure_init(STRE_CHANNEL_MSG *pcam){

//	ZJ_SetWifiSetAbility(pcam->SetWifiAbility);

	return 0;
}

static int cbfun_register(void){
	ZJ_SetRecvCustomDataFunc(fzb_OnRecvCustomData);
//	ZJ_SetWifiCB(fzb_SetWifi,fzb_GetWifi,fzb_GetNetInfo);	
	return 0;
}

int zjre_channelInit(void){
	member_init(&g_ST_channel_msg);
	configure_init(&g_ST_channel_msg);
	cbfun_register();
	return 0;
}



