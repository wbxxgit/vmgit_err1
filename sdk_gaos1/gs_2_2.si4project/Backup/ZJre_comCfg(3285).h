#ifndef ZJRE_COMCFG_H_
#define ZJRE_COMCFG_H_

/******以下为测试ID*******/

#define  DEVICE_TYPE			 1  //设置设备类型 1.摄像机；2.分体门铃；3.单体门铃；4.NVR
//EF1102
//EF-FH8632-0530-00
//#define  DEVICE_MODEL	  "EF1002" //设置设备的型号：EF-FH8632-0530-00  第一位 sdk 开发者 , 第二位厂商芯片信号 第三 产品型号 第四 省份

#ifdef MMACRO_NOFLASH_T3_E1102
#define  DEVICE_MODEL			 "EF1102"
#else
#define  DEVICE_MODEL			 "EF1002"
#endif


#ifndef MACRO_ZJ 
#define  DEVICE_OTA_VERSION			 "V1.2.123-00-200825"  //请更改为实际使用的CTEI ID
#define  DEVICE_CTEIID			   "doort0017VHYIyxL" //请更改为实际使用的CTEI ID
#define  DEVICE_COMPANYID            (unsigned char*)"4934611254891294" //请更改为实际使用的公司ID  
#define  DEVICE_APPID                (unsigned char*)"1597310717459589"	//请更改为实际使用的产品ID
#else



#ifdef MMACRO_FLASHCTEI	
	#define  DEVICE_OTA_VERSION			   "V1.2.123-00-200825" 		
#elif MMACRO_NOFLASH_T1_NT
#define  DEVICE_CTEIID               "180004639251152" 
#define  DEVICE_DEVSN               "3ELB024112HSKA9" 
#define  DEVICE_DEVKEY               "6mVWyMn6mK"
	#define  DEVICE_OTA_VERSION			   "V1.2.123-00-200818" 
//	#define  DEVICE_OTA_VERSION			   "V1.2.123-01-200917" 

#elif MMACRO_NOFLASH_T2_YT
#define  DEVICE_CTEIID               "XST6P8HA" 
#define  DEVICE_DEVSN               "3ELC0543334BE6V" 
#define  DEVICE_DEVKEY               "zCHpFzhszT"	
	#define  DEVICE_OTA_VERSION			   "V1.2.123-00-200818" 

#elif MMACRO_NOFLASH_T3_E1102_DEDICATED
//#elif MMACRO_NOFLASH_T3_E1102
//#define  DEVICE_CTEIID               "181695447999989"   //182343827999989

#if 1
#define  DEVICE_CTEIID               "182343827999989"
#define  DEVICE_DEVSN               "3ELB034333T9KEB" 
#define  DEVICE_DEVKEY               "XKkdNlx323"	
#define  DEVICE_OTA_VERSION			   "V1.2.123-00-200831" 
#else
#define  DEVICE_CTEIID               "182343827999991"
#define  DEVICE_DEVSN               "3ELB0343336NGUY" 
#define  DEVICE_DEVKEY               "gP5GGtjnMl"	
#define  DEVICE_OTA_VERSION			   "V1.2.123-00-200831" 
#endif


#else
#define  DEVICE_CTEIID               "180004639251152" 
#define  DEVICE_DEVSN               "3ELB024112HSKA9" 
#define  DEVICE_DEVKEY               "6mVWyMn6mK"
	#define  DEVICE_OTA_VERSION			   "V1.2.123-00-200818" 
#endif

#endif


//SDK相关配置文件存储路径
//#define DEVICE_SYSTEM_PATH_PARENT      "/mnt/SDKconfig"
//#define DEVICE_SYSTEM_PATH      "/mnt/SDKconfig/system"
//#define DEVICE_CONFIG_PATH      "/mnt/SDKconfig/config"
#define DEVICE_SYSTEM_PATH_PARENT      "/mnt/SDKconfig"
#define DEVICE_SYSTEM_PATH      DEVICE_SYSTEM_PATH_PARENT "/system"
#define DEVICE_CONFIG_PATH      DEVICE_SYSTEM_PATH_PARENT "/config"


#define AUDIO_SAVEFILE_PATH      "/opt/httpServer/lighttpd/htdocs/sd/sound"
#define SD_PATH      "/opt/httpServer/lighttpd/htdocs/sd" 

#endif



