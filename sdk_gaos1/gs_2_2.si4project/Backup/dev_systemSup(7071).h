#ifndef DEV_SYSTEMSUP_H_
#define DEV_SYSTEMSUP_H_

#include "basetypesJX.h"


typedef struct stru_ota_message{
	u8 endflag;
	u8 triggerTsk;
	u8 interruptTsk;
} ST_ota_message;


int dev_systemSup_init(void);
int dev_systemSup_start(void);
int dev_systemSup_destory(void);


#endif




