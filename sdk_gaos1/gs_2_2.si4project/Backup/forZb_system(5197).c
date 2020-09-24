
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "zj_type.h"
#include "zj_log.h"

#include "forZb_comCfg.h"
#include "forZb_system.h"
#include "ZJre_comCfg.h" 




int fzb_SystemStatusCB(EN_ZJ_SERVER_STATUS enDeviceStatus, int iErrCode){
	return 0;
}

int fzb_SetDeviceRebootCbFunc(){
	return 0;
}

int fzb_funSetTimeZone(int iSyncFlag, int iZone, char* pcDatetime){
	return 0;
}

int fzb_funGetTimeZone(int *piZone,unsigned char *pucTime,int *piSyncFlag){
	return 0;
}

int fzb_funRestoreFactorySetting(){
	return 0;
}

int fzb_funCfgItemChangeCb(unsigned int uiCfgItem){
	return 0;
}

//log
int fzb_SetDevCollectLogFilesFunc(unsigned char *pucPeerId,unsigned int iSessionId,unsigned char *pcDesInfo){
	int state;
	char acFileName[224] = {0};
	char acCmdBuf[256] = {0};

	snprintf(acFileName ,sizeof(acFileName), "%s/../log.tar.gz",DEVICE_CONFIG_PATH);
	if( access(DEVICE_CONFIG_PATH,F_OK) == 0 ){
		snprintf(acCmdBuf , sizeof(acCmdBuf), "tar zcvf %s %s", acFileName, DEVICE_CONFIG_PATH);
		state = system(acCmdBuf);
		if(state != 0){
			printf("system err!state:%d\n",state);
			return -1;
		}
	}else{
		printf("accessDEVICE_CONFIG_PATH err!\n");
		return -1;
	}	
	ZJ_SetCollectLogFilesStatus( pucPeerId, iSessionId, state, pcDesInfo, (unsigned char *) acFileName);
	printf("SetDevCollectLogFilesFunc succeed!\n");
	return 0;
}






