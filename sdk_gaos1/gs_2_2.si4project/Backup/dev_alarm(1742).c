#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "zj_type.h"
#include "zj_log.h"

#include "devCfg.h"
#include "dev_alarm.h"

#include "dev_zj_funReg.h"

#include "IPC_MediaBuff.h"
#include "sdk_commonstruct.h"
#include "sdkout_impl.h" 

#include "dev_network.h" 



int sysClrCmdByPath(char *path){
	if( access(path,F_OK) != 0){
		ZJ_LOG_INF("path not exist");		
		return -1;
	}
	char acCmdBuf[256] = {0};

	snprintf(acCmdBuf, sizeof(acCmdBuf), "rm -r %s", path);
	system(acCmdBuf);	
	return 0;
}


int AlarmExeBy_123(void){
	printf("test alarm exe1\n");
	return 0;
}


int AlarmExeBy_motion(void){
	if( NULL == dj_camIot_GtFTbl()->f_IoTEventInPut){
		ZJ_LOG_INF("f_IoTEventInPut no register!\n");
		return -1;			
	}	
	dj_camIot_GtFTbl()->f_IoTEventInPut(EN_ZJ_AIIOT_TYPE_MOTION, 0, EN_ZJ_MOTION_EVENT_MOTION);
	ZJ_LOG_INF("AlarmExeBy_motion exe!");
	return 0;
}

int AlarmExeBy_motion_body(void){
	if( NULL == dj_camIot_GtFTbl()->f_IoTEventInPut){
		ZJ_LOG_INF("f_IoTEventInPut no register!\n");
		return -1;			
	}	
	dj_camIot_GtFTbl()->f_IoTEventInPut(EN_ZJ_AIIOT_TYPE_MOTION, 0, EN_ZJ_MOTION_EVENT_HUMAN);
	ZJ_LOG_INF("AlarmExeBy_motion_body exe!");
	return 0;
}

int AlarmExeBy_shortPre(void){
	ZJ_LOG_INF("AlarmExeBy_shortPress:short reset");	
	sysClrCmdByPath(PATH_RESETDELETE_SHORT);
	d_triggerSetNet();//reset and set net flag to save	
	if(dj_system_GtFTbl()->f_CtrlDeviceId == NULL)
		return -1;
	dj_system_GtFTbl()->f_CtrlDeviceId(EN_ZJ_CTRLDID_EXITGROUP);
	return 0;
}
int AlarmExeBy_longPre(void){
	ZJ_LOG_INF("AlarmExeBy_longPress:long reset");
	sysClrCmdByPath(PATH_RESETDELETE_LONG);
	if(dj_system_GtFTbl()->f_CtrlDeviceId == NULL)
		return -1;
	dj_system_GtFTbl()->f_CtrlDeviceId(EN_ZJ_CTRLDID_CLEAR);
	return 0;
}


static ST_alarmExe gAlarmExe[] = {
{100,AlarmExeBy_123},
{E_VIDEO_MOTION,AlarmExeBy_motion},
{E_KEY_LONG_PRESS,AlarmExeBy_longPre},
{E_KEY_SHORT_PRESS,AlarmExeBy_shortPre},
{E_BODY_DETECT,AlarmExeBy_motion_body},

};

ST_alarmExe *getAlarmArr(){
    return  &gAlarmExe[0];
}


u8 alarmExe_memSize(){
	return sizeof(gAlarmExe) / sizeof(ST_alarmExe);
}


int alarmcb_process(u8 alarmType){
	int i;
//	ZJ_LOG_INF("alarmExe_memSize() = %d",alarmExe_memSize());
	for (i = 0; i < alarmExe_memSize(); ++i){
	    if(  (getAlarmArr()+i)->al_type == alarmType){
			(getAlarmArr()+i)->pfun();
			ZJ_LOG_INF("has been alarmcb_process");
			return 0;
		}	 		
	}	
	ZJ_LOG_INF("not exe alarmcb_process");
	return -1;
}





