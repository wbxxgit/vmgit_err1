#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "zj_type.h"
#include "zj_log.h"

#include "ZJre_comCfg.h" 

#include "zj_network.h" 

#include "forZb_network.h"  

typedef struct stru_STRE_NETWORK_MSG{

	unsigned int SetWifiAbility;

}STRE_NETWORK_MSG;

static STRE_NETWORK_MSG  g_ST_networ_msg = {0};

static int member_init(STRE_NETWORK_MSG *p_cam){
	p_cam->SetWifiAbility = 1;


	return 0;
}

static int configure_init(STRE_NETWORK_MSG *pcam){

	ZJ_SetWifiSetAbility(pcam->SetWifiAbility);

	return 0;
}

static int cbfun_register(void){

	ZJ_SetWifiCB(fzb_SetWifi,fzb_GetWifi,fzb_GetNetInfo);	
	return 0;
}

int zjre_networkInit(void){
	member_init(&g_ST_networ_msg);
	configure_init(&g_ST_networ_msg);
	cbfun_register();
	return 0;
}



