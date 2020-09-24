#ifndef DEV_ALARM_H_
#define DEV_ALARM_H_

#include "basetypesJX.h" 

//reset del path
#define PATH_RESETDELETE_LONG   "/mnt/testconfig/system"   //  
#define PATH_RESETDELETE_SHORT   "/mnt/testconfig/config/config"



typedef struct stru_alarmExe{
	u8 al_type;
	int (*pfun)(void);
	
} ST_alarmExe;



ST_alarmExe *getAlarmArr();

//extern ST_alarmExe gAlarmExe[];
//u8 alarmExe_memSize();

//int sysClrCmdByPath(char *path);

int alarmcb_process(u8 alarmType);




#endif




