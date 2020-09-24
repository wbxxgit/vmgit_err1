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

#include "dev_systemSup.h" 

#include "sdkout_impl.h" 



int fzb_SystemStatusCB(EN_ZJ_SERVER_STATUS enDeviceStatus, int iErrCode){
	return 0;
}

int fzb_SetDeviceRebootCbFunc(){
	DPRI_INFO("SetDeviceRebootCbFunc exe");
	system("reboot");
	return 0;
}


static int timezoneSet(int zone,int SyncFlag){
	T_SDK_NTP_CFG_PARAMS t_ntp_cfg;
	memset(&t_ntp_cfg,0,sizeof(T_SDK_NTP_CFG_PARAMS));
//	t_ntp_cfg.a_NtpServer = "";	
	t_ntp_cfg.un_NtpOpen = SyncFlag;  //un_EuroTime
	t_ntp_cfg.un_EuroTime = 0;
	t_ntp_cfg.un_NtpRefTime = 300;	
	t_ntp_cfg.un_TimeZone = zone/3600;
//	strcpy(t_ntp_cfg.a_NtpServer,"server 3.cn.pool.ntp.org");  //1.cn.pool.ntp.org
	strcpy(t_ntp_cfg.a_NtpServer,"1.cn.pool.ntp.org");
	t_ntp_cfg.un_ntp_port = 123;
//	t_ntp_cfg.un_Res[0] = SyncFlag;
	DPRI_INFO("un_TimeZone:%d",t_ntp_cfg.un_TimeZone);
	if(0 != SDK_Cmd_Impl(SDKCMD_SET_NTP_PARAM,  &t_ntp_cfg) ){
		DPRI_INFO("SDKCMD_SET_NTP_PARAM fail");
		return -1;
	}
	return 0;
}

static int getZone_ntp(int *timezone,int *syncflag){
	T_SDK_NTP_CFG_PARAMS t_ntp_cfg;
	if(0 != SDK_Cmd_Impl(SDKCMD_GET_NTP_PARAM,  &t_ntp_cfg) ){
		DPRI_INFO("SDKCMD_GET_NTP_PARAM fail");
		return -1;
	}	
	printf("getZone_ntp:\n");
	printf("%d\n",t_ntp_cfg.un_NtpOpen);
	printf("%d\n",t_ntp_cfg.un_EuroTime);
	printf("%d\n",t_ntp_cfg.un_NtpRefTime);
	printf("%d\n",t_ntp_cfg.un_TimeZone);
	printf("%s\n",t_ntp_cfg.a_NtpServer);
	printf("%d\n",t_ntp_cfg.un_ntp_port);
	printf("%d\n",t_ntp_cfg.un_Res[0]);	
	printf("%d\n",t_ntp_cfg.un_Res[1]);	
	*timezone = t_ntp_cfg.un_TimeZone * 3600;
	*syncflag = t_ntp_cfg.un_NtpOpen;
	return 0;	
}


int fzb_funSetTimeZone(int iSyncFlag, int iZone, char* pcDatetime){
	DPRI_INFO("b_funSetTimeZone_qx exe,syncflag [%d] zone [%d] datetime [%s]",iSyncFlag, iZone, pcDatetime);
	if(0 != timezoneSet(iZone,iSyncFlag))	
		return -1;
	if(iSyncFlag == 0){
		T_SDK_DEVICE_TIME dtTmp;  //2020-08-26 11:08:06
		if( EOF == 	sscanf( pcDatetime, "%d-%d-%d %d:%d:%d", &dtTmp.un_year, &dtTmp.un_month, &dtTmp.un_day,
				&dtTmp.un_hour,&dtTmp.un_minute,&dtTmp.un_second ) )
			return -1;
		DPRI_INFO("switch:%d,%d,%d,%d,%d,%d", dtTmp.un_year, dtTmp.un_month, dtTmp.un_day,
				dtTmp.un_hour,dtTmp.un_minute,dtTmp.un_second );
		if (0 != SDK_Cmd_Impl(SDKCMD_SET_DEVICE_TIME,(void *)&dtTmp))
		{
			DPRI_INFO("SDKCMD_SET_DEVICE_TIME fail");
			return -1;
		}
	}	
	
//	inter_setSyncFlag(iSyncFlag);
	return 0;
}

int fzb_funSetTimeZone_PZJ(int iSyncFlag, int iZone, char* pcDatetime,char *pucDst){
	DPRI_INFO("b_funSetTimeZone_PZJ exe, syncflag [%d] zone [%d] datetime [%s] pucDst [%s]", 
		iSyncFlag, iZone, pcDatetime,pucDst);


	T_SDK_DEVICE_TIME dtTmp;  //2020-08-26 11:08:06
	if( EOF == 	sscanf( pcDatetime, "%d-%d-%d %d:%d:%d", &dtTmp.un_year, &dtTmp.un_month, &dtTmp.un_day,
			&dtTmp.un_hour,&dtTmp.un_minute,&dtTmp.un_second ) )
		return -1;
	DPRI_INFO("switch:%d,%d,%d,%d,%d,%d", dtTmp.un_year, dtTmp.un_month, dtTmp.un_day,
			dtTmp.un_hour,dtTmp.un_minute,dtTmp.un_second );

	if (0 != SDK_Cmd_Impl(SDKCMD_SET_DEVICE_TIME,(void *)&dtTmp))
	{
		DPRI_INFO("SDKCMD_SET_DEVICE_TIME fail");
		return -1;
	}

	return 0;
}

/*
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
} */





int fzb_funGetTimeZone(int *piZone,unsigned char *pucTime,int *piSyncFlag){
	DPRI_INFO("b_funGetTimeZone exe\n");	//需要组成固定字符串传递给SDK，YYYY-MM-DD hh:mm:ss
	
    char acStrTime[30] = "";
	struct	 tm 	*ptm;
	long	   ts;
	ts   =   time(NULL);
	ptm   =   localtime(&ts);
    snprintf(acStrTime, sizeof(acStrTime), "%04d-%02d-%02d %02d:%02d:%02d", 
			ptm-> tm_year+1900, ptm-> tm_mon+1, ptm-> tm_mday, ptm-> tm_hour, ptm-> tm_min, ptm-> tm_sec);
    strcpy((char *)pucTime,acStrTime);

	if(0 != getZone_ntp(piZone,piSyncFlag))
		return -1;
    DPRI_INFO("get device time and zone ok, zone [%d] time [%s] sync flag[%d] \n",
    				*piZone, pucTime, *piSyncFlag);	
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






