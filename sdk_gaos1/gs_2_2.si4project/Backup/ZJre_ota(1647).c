#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "device_log.h"
#include "zj_type.h"
#include "zj_log.h"

#include "ZJre_comCfg.h" 

#include "zj_ota.h" 

#include "forZb_ota.h"  

typedef struct stru_STRE_OTA_MSG{

	//unsigned int SetWifiAbility;
	unsigned int Percentage;
	unsigned int OTAAbility;

}STRE_OTA_MSG;

static STRE_OTA_MSG  g_ST_ota_msg = {0};

static int member_init(STRE_OTA_MSG *p_cam){
	p_cam->Percentage = 0;
	p_cam->OTAAbility = 1;

	return 0;
}

static int configure_init(STRE_OTA_MSG *pcam){
//	ZJ_SetWifiSetAbility(pcam->SetWifiAbility);
	ZJ_SetBurnningProgress(pcam->Percentage);
	ZJ_SetOTAAbility(pcam->OTAAbility);

	return 0;
}

static int cbfun_register(void){

	ZJ_SetOtaCBFuncs( fzb_NewVersionCb,fzb_VersonDataDownCb, 
			fzb_StopUpgrade ,fzb_CoverImageNotice );

//	ZJ_SetWifiCB(fzb_SetWifi,fzb_GetWifi,fzb_GetNetInfo);	
	return 0;
}

int zjre_otaInit(void){
	member_init(&g_ST_ota_msg);
	configure_init(&g_ST_ota_msg);
	cbfun_register();
	return 0;
}



