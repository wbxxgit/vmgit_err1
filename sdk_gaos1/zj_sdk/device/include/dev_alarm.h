#ifndef DEV_ALARM_H_
#define DEV_ALARM_H_

#include "basetypesJX.h" 
#include "ZJre_comCfg.h" 
#include "sdk_commonstruct.h" 



//reset del path
#define PATH_RESETDELETE_LONG    DEVICE_SYSTEM_PATH  //  
#define PATH_RESETDELETE_SHORT   DEVICE_CONFIG_PATH



typedef struct stru_alarmExe{
	u8 al_type;
	int (*pfun)(void *a);
	
} ST_alarmExe;



ST_alarmExe *getAlarmArr();

//extern ST_alarmExe gAlarmExe[];
//u8 alarmExe_memSize();

//int sysClrCmdByPath(char *path);

int alarmcb_process(T_SDK_ALARM_CALLBACK_PARAM *param);




#endif




