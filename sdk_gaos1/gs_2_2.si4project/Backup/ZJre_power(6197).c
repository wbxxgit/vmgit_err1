#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "zj_type.h"
#include "zj_log.h"

#include "ZJre_comCfg.h" 

#include "zj_power.h" 

#include "forZb_power.h"  

typedef struct stru_STRE_POWER_MSG{

	
	unsigned int EngeryType;
	unsigned int AwakeAbility;
	unsigned int SupplyFlag;
	unsigned int PowerLevel;

}STRE_POWER_MSG;

static STRE_POWER_MSG  g_ST_power_msg = {0};

static int member_init(STRE_POWER_MSG *p_cam){
	p_cam->EngeryType = 0;
	p_cam->AwakeAbility = 0;
	p_cam->SupplyFlag = 0;
	p_cam->PowerLevel = 0;
	

	return 0;
}

static int configure_init(STRE_POWER_MSG *pcam){

//	ZJ_SetWifiSetAbility(pcam->SetWifiAbility);
	ZJ_SetEnergySavingType(pcam->EngeryType);
	ZJ_SetAwakeAbility(pcam->AwakeAbility);
	ZJ_SetPowerSupply(pcam->SupplyFlag);
	ZJ_SetPowerLevel(pcam->PowerLevel);

	return 0;
}

static int cbfun_register(void){

	ZJ_SetStartSleepCb(fzb_StartSleep);
//	ZJ_SetWifiCB(fzb_SetWifi,fzb_GetWifi,fzb_GetNetInfo);	
	return 0;
}

int zjre_powerInit(void){
	member_init(&g_ST_power_msg);
	configure_init(&g_ST_power_msg);
	cbfun_register();
	return 0;
}



