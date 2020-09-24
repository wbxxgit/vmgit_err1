#ifndef ZJRE_COMCFG_H_
#define ZJRE_COMCFG_H_

/******以下为测试ID*******/

#ifndef MACRO_ZJ
#define  DEVICE_OTA_VERSION			 "V1.2.123-00-200825"  //请更改为实际使用的CTEI ID
#define  DEVICE_CTEIID			   "doort0017VHYIyxL" //请更改为实际使用的CTEI ID
#define  DEVICE_COMPANYID            (unsigned char*)"4934611254891294" //请更改为实际使用的公司ID  
#define  DEVICE_APPID                (unsigned char*)"1597310717459589"	//请更改为实际使用的产品ID
#else
#define  DEVICE_OTA_VERSION			   "V1.2.123-00-200825" 
#define  DEVICE_CTEIID               "180004639251152" 
#define  DEVICE_DEVSN               "3ELB024112HSKA9" 
#define  DEVICE_DEVKEY               "6mVWyMn6mK"
#endif


//SDK相关配置文件存储路径
#define DEVICE_SYSTEM_PATH      "/mnt/testconfig/system"
#define DEVICE_CONFIG_PATH      "/mnt/testconfig/config"


#define AUDIO_SAVEFILE_PATH      "/opt/httpServer/lighttpd/htdocs/sd/sound"
#define SD_PATH      "/opt/httpServer/lighttpd/htdocs/sd" 

#endif




