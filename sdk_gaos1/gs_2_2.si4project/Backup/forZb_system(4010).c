
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



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
	ZJ_LOG_INF("b_funSetTimeZone exe\n");

	return 0;
}

static int getZone(){

//	unsigned int timezone = 0;
	time_t t1, t2 ;
	struct tm *tm_local, *tm_utc;

	time(&t1);
	t2 = t1;
	printf("t1=%ld,t2=%ld\n", t1, t2);

	tm_local = localtime(&t1);
	printf("localtime=%d:%d:%d\n", tm_local->tm_hour, tm_local->tm_min, tm_local->tm_sec);
	t1 = mktime(tm_local) ;
	tm_utc = gmtime(&t2);
	printf("utcutctime=%d:%d:%d\n", tm_utc->tm_hour, tm_utc->tm_min, tm_utc->tm_sec);
	t2 = mktime(tm_utc);
	printf("***\n");
	printf("t1=%ld\nt2=%ld\n", t1, t2);

	printf("%ld\n", (t1 - t2));
	return (t1 - t2);
//	timezone = (t1 - t2) / 3600;
//	printf("%d\n", timezone);	
	
	
}

int fzb_funGetTimeZone(int *piZone,unsigned char *pucTime,int *piSyncFlag){
	ZJ_LOG_INF("b_funGetTimeZone exe\n");	
	
    char acStrTime[30] = "";
    /**
     * 需要组成固定字符串传递给SDK，YYYY-MM-DD hh:mm:ss
    */
	struct	 tm 	*ptm;
	long	   ts;
	ts   =   time(NULL);
	ptm   =   localtime(&ts);
    snprintf(acStrTime, sizeof(acStrTime), "%04d-%02d-%02d %02d:%02d:%02d", 
			ptm-> tm_year+1900, ptm-> tm_mon+1, ptm-> tm_mday, ptm-> tm_hour, ptm-> tm_min, ptm-> tm_sec);
    strcpy((char *)pucTime,acStrTime);

	*piZone=	getZone();
	*piSyncFlag = 1;
	
    ZJ_LOG_INF("get device time and zone ok, zone [%d] time [%s] sync flag[%d] \n", *piZone, pucTime, *piSyncFlag);

	
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






