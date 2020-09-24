#ifndef ZJRE_COMCFG_H_
#define ZJRE_COMCFG_H_


/******以下为测试ID*******/
/*
#define  DEVICE_COMPANYID            (unsigned char*)"4934611254891294" //请更改为实际使用的公司ID  
#define  DEVICE_APPID                (unsigned char*)"1594176037759631"	//请更改为实际使用的产品ID
//#define  DEVICE_CTEIID               (unsigned char*)"doort0017VHYIyxL" //请更改为实际使用的CTEI ID

//#define  DEVICE_CTEIID               (unsigned char*)"180004639251118" 
//#define  DEVICE_DEVSN               "3ELB024112NTPFB" 
//#define  DEVICE_DEVKEY               "Hblh8XXYY6"

#define  DEVICE_DEVSN               "3ELB024112HSKA9" 
#define  DEVICE_DEVKEY               "6mVWyMn6mK"
#define  DEVICE_CTEIID               (unsigned char*)"180004639251152"   */

#ifndef MACRO_ZJ
#define  DEVICE_COMPANYID            (unsigned char*)"4934611254891294" //请更改为实际使用的公司ID  
#define  DEVICE_APPID                (unsigned char*)"1597310717459589"	//请更改为实际使用的产品ID
#define  DEVICE_CTEIID			   (unsigned char*)"doort0017VHYIyxL" //请更改为实际使用的CTEI ID
#else
#define  DEVICE_DEVSN               "3ELB024112HSKA9" 
#define  DEVICE_DEVKEY               "6mVWyMn6mK"
#define  DEVICE_CTEIID               (unsigned char*)"180004639251152" 
#endif




//SDK相关配置文件存储路径
//#define DEVICE_SYSTEM_PATH      "testconfig/system"
//#define DEVICE_CONFIG_PATH      "testconfig/config"
//#define AUDIO_SAVEFILE_PATH      "testconfig/sound"  

#define DEVICE_SYSTEM_PATH      "/mnt/testconfig/system"
#define DEVICE_CONFIG_PATH      "/mnt/testconfig/config"
  

//video relation
//#define VIDEO_PLAYFILE_PATH_CFG      "testconfig/video/DemovideoDesc.txt" 
//#define VIDEO_PLAYFILE_PATH_FILE     "testconfig/video/Demovideo.H264" 
//audio relation
//#define AUDIO_PLAYFILE_PATH          "testconfig/video/1.wav" 
//pic relation
//#define SNAP_FILEPATH_JPG1          "testconfig/pic/longmao.jpg" 
//#define SNAP_FILEPATH_JPG2          "testconfig/pic/timg.jpg" 

//#define SD_PATH      "/home/wb/btest/testconfig/sd"

//#define SD_PATH      "/mnt/testconfig/sd"  ///opt/httpServer/lighttpd/htdocs/sd

#define AUDIO_SAVEFILE_PATH      "/opt/httpServer/lighttpd/htdocs/sd/sound"
#define SD_PATH      "/opt/httpServer/lighttpd/htdocs/sd" 


#endif




