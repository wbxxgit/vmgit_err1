#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#include "basetypesJX.h" 

#include "zj_type.h"
#include "zj_log.h"
#include "zj_system.h" 

#include "ZJre_comCfg.h"
#include "forZb_system.h"  

#include "forZb_system.h"  

#include "sdk_commonstruct.h"
#include "sdkout_impl.h" 


/*
typedef struct{

	char *SystemPath;
	char *ConfPath;
	int DebugMode;
	char *Version;
}ZE_SYSTEM_MSG; */


typedef struct stru_STRE_SYSTEM_MSG{
	char *SystemPath;
	char *ConfPath;
	int DebugMode;
	EN_ZJ_LOG_LVL Level;
	char *Version;

	unsigned char *CompanyId;
	unsigned char *AppId;
	char *CTEI;
	char *DevSn;
	char *DevKey;
}STRE_SYSTEM_MSG;

static STRE_SYSTEM_MSG  g_ST_system_msg = {0};

static int member_init(STRE_SYSTEM_MSG *p_system){
	p_system->SystemPath = DEVICE_SYSTEM_PATH;
	p_system->ConfPath = DEVICE_CONFIG_PATH;
	p_system->DebugMode = 1;
	p_system->Level = EN_ZJ_LOG_LVL_ALL;

#ifndef MACRO_ZJ
	p_system->Version = DEVICE_OTA_VERSION;	
	p_system->CTEI = DEVICE_CTEIID; 
	p_system->CompanyId = DEVICE_COMPANYID;
	p_system->AppId = DEVICE_APPID;	

	T_SDK_THREE_DevCfg info2;
	memset(&info2,0,sizeof(T_SDK_THREE_DevCfg));

	if(0 !=SDK_Cmd_Impl(SDKCMD_THREE_DEVICE_INFO,(void*)(&info2)) )
		printf("SDKCMD_THREE_DEVICE_INFO failed\n");
	else
		printf("test flash show: ret1===CTEI:%s,KEY:%s,SN:%s\n",
		info2.u8DevCTEI,info2.u8DevKey,info2.u8DevSN);

	#ifdef MMACRO_FLASHCTEI
		printf("MMACRO_FLASHCTEI ___ has been define\n");
	#endif

	//printf("ret1===CTEI:%s,KEY:%s,SN:%s\n",info2.u8DevCTEI,info2.u8DevKey,info2.u8DevSN);
#else
	p_system->Version = DEVICE_OTA_VERSION;	//DEVICE_OTA_VERSION
	
	#ifndef MMACRO_FLASHCTEI	
		p_system->CTEI = DEVICE_CTEIID;	
		p_system->DevSn = DEVICE_DEVSN;
		p_system->DevKey = DEVICE_DEVKEY;		
	#else
	//	printf("MMACRO_FLASHCTEI ___ has been define\n");
		T_SDK_THREE_DevCfg info2;
		memset(&info2,0,sizeof(T_SDK_THREE_DevCfg));
		if(0 !=SDK_Cmd_Impl(SDKCMD_THREE_DEVICE_INFO,(void*)(&info2)) )
			printf("SDKCMD_THREE_DEVICE_INFO failed\n");
		else{
			printf("MMACRO_FLASHCTEI ret1===CTEI:%s,KEY:%s,SN:%s\n",info2.u8DevCTEI,info2.u8DevKey,info2.u8DevSN);
			strcpy(p_system->CTEI,info2.u8DevCTEI);
			strcpy(p_system->DevSn,info2.u8DevSN);
			strcpy(p_system->DevKey,info2.u8DevKey);
		}		
	//	p_system->CTEI = DEVICE_CTEIID;	
	//	p_system->DevSn = DEVICE_DEVSN;
	//	p_system->DevKey = DEVICE_DEVKEY;		
	#endif
//	p_system->CTEI = DEVICE_CTEIID;	
//	p_system->DevSn = DEVICE_DEVSN;
//	p_system->DevKey = DEVICE_DEVKEY;	
#endif


	return 0;
}

static int configure_init(STRE_SYSTEM_MSG *psystem){

    ZJ_Init(psystem->SystemPath, psystem->ConfPath);   /*初始化SDK，并配置SDK配置文件存储路径*/  
    ZJ_SetDebugMode(psystem->DebugMode);/*开启SDK打印， 1打开 0 关闭*/    
//    ZJ_SetDebugLevel(psystem->Level); /*设置log等级*/    
    ZJ_SetAppVersion(psystem->Version);   /*设置固件版本号*/   
	printf("sdk version: %s\n", psystem->Version);
#ifndef MACRO_ZJ
	ZJ_SetCompanyInfo(psystem->CompanyId, psystem->AppId);/*企业信息*/ 
	ZJ_SetCTEIID((u8 *)psystem->CTEI); /*CTEI注册*/
#else
	ZJ_SetCTEIID((u8 *)psystem->CTEI); /*CTEI注册*/
	ZJ_SetDeviceUID((u8 *)(psystem->DevSn),(u8 *)(psystem->DevKey));
#endif 	
       
//    ZJ_SetCTEIID(psystem->CTEI); /*CTEI注册*/
//_ZJ_API int ZJ_SetDeviceUID(unsigned char *pucDevSn, unsigned char *pucDevKey);

	return 0;
}


static int cbfun_register(void){
	ZJ_Set_SystemStatusCB(fzb_SystemStatusCB);
	ZJ_SetDeviceRebootCbFunc(fzb_SetDeviceRebootCbFunc);
#ifndef MACRO_ZJ
	ZJ_SetZoneAndTimeCB(fzb_funSetTimeZone,fzb_funGetTimeZone);
#else
	ZJ_SetZoneAndTimeCB(fzb_funSetTimeZone_PZJ,fzb_funGetTimeZone);
#endif
//	ZJ_SetZoneAndTimeCB(fzb_funSetTimeZone,fzb_funGetTimeZone);
	ZJ_SetRestoreFactorySettingCB(fzb_funRestoreFactorySetting);
	ZJ_SetNoticeCfgChangeCbFun(fzb_funCfgItemChangeCb);

	//log
	ZJ_SetDevCollectLogFilesFunc(fzb_SetDevCollectLogFilesFunc);
	return 0;
}

int zjre_systemInit(void){
	member_init(&g_ST_system_msg);
	configure_init(&g_ST_system_msg);
	cbfun_register();
	return 0;
}

int zjre_system_start(void){
	ZJ_Start();/*启动SDK*/	
	return 0;
}

int zjre_system_destory(void){
	ZJ_Stop(); /*停止SDK运行*/
	ZJ_Destroy();	  /*释放占用资源*/
	return 0;
}






