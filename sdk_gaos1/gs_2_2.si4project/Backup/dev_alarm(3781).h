#ifndef DEV_ALARM_H_
#define DEV_ALARM_H_

#include "basetypesJX.h" 

//reset del path
#define PATH_RESETDELETE_LONG  "/mnt/testconfig/config/config"
#define PATH_RESETDELETE_SHORT  "/mnt/testconfig/system"



typedef struct stru_alarmExe{
	u8 al_type;
	int (*pfun)(void);
	
} ST_alarmExe;



ST_alarmExe *getAlarmArr();

extern ST_alarmExe gAlarmExe[];
u8 alarmExe_memSize();

int sysClrCmdByPath(char *path);



#endif




