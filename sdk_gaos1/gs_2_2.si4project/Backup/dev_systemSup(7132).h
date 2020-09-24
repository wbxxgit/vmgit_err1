#ifndef DEV_SYSTEMSUP_H_
#define DEV_SYSTEMSUP_H_

#include "basetypesJX.h"


typedef int DataType;
typedef struct Node
{
    DataType data;//数据域
    struct Node *next;//指针域
}Node;


typedef struct ST_ota_message{
	u8 endflag;
	u8 triggerStaTsk;
	u8 interruptTsk;
	u8 expectUpgrade;

	u8 *omNewVersion;
	u32 omFileSize;
	u32 omRecFileSize;
	u32 omEndFlag; 
	u8 *omSelfVersion;

	FILE	*fHandle; 
	char    *fmFileName;

	u32 timeout_loop;
	int (*pFun_destory)(struct ST_ota_message *pOtaMsg);
	
} ST_ota_message;



int dev_systemSup_init(void);
int dev_systemSup_start(void);
int dev_systemSup_destory(void);

ST_ota_message *RetG_ota_msg();

int inter_getSyncFlag();
int inter_setSyncFlag(int setVal);



#endif




