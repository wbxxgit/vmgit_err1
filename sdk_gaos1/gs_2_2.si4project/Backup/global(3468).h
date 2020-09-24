/**************************************************************************
 * 	FileName:	global.h
 *	Description:	系统级数据结构与宏开关的定义，需全工程包含
 *	Copyright(C):	2014-2020 Gos Inc.
 *	History:		基于之前Hi3518系列文件修改了结构体的命名规则
 *	Author:		johnny
 *	Created:		2015-12-11
 *	Updated:		
 *					
 **************************************************************************/
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

//#include "GVAP_deviceDiscover.h"
#include "adi_gpio.h"

#define     HI3516_ARCH             1
//
/*----------------------------------------------*
  自定义基本数据类型定义
 *----------------------------------------------*/
typedef unsigned long long      UInt64;
typedef long long      			Int64;
typedef unsigned char           UInt8;
typedef unsigned short          UInt16;
typedef unsigned int            UInt32;
typedef char                    Int8;
typedef short                   Int16;
typedef int                     Int32;
;
//基本常用的头文件 统一包含进来
#define PACKED		__attribute__((packed, aligned(1)))
#define PACKED4		__attribute__((packed, aligned(4)))

//==========版本控制==========
#define GOS_SDK_VERSION				1  //默认一定开启


//基础几表示后面还会依赖这个宏
#define GOS_gk7102_T5886GAA_VERSION		0  //100W 摇头机 gc1024	请在下面选择带不带温度
#define GOS_gk7102_T5820GBA_VERSION		0  //130W 卡片机 sc1035		
#define GOS_gk7102_T5881GBA_VERSION		0  //130W 摇头机 sc1035
#define GOS_gk7102_T2858GBA_VERSION		0  //130W 摇头机 sc1035 头盔
#define GOS_gk7101_T2858GCA_VERSION		0  //200W 摇头机 ov2710 头盔
#define GOS_gk7101_T5820GCA_VERSION		0  //200W 卡片机 ov2710
#define GOS_gk7101_T5886GCA_VERSION		0  //200w 摇头机 ov2710 
#define GOS_gk7101_T5881GCA_VERSION		0  //200w 摇头机 ov2710
#define GOS_gk7101_T5925GCA_VERSION		0  //200w 户外机 ov2710
#define GOS_gk7102_T5703GAA_VERSION		0  //100w 卡片机 gc1034 虹软降成本送样机型
#define GOS_gk7102_T5703GAB_VERSION		0  //100w 卡片机 h62   
#define GOS_gk7102s_T5830GAA_VERSION	0  //100w 摇头机 h62 GOS_PHOTOSENSITIVE=5
#define GOS_gk7102s_T5708GAA_VERSION	0  //100w 卡片机 h62 GOS_PHOTOSENSITIVE=3
#define GOS_gk7102s_T5825GAB_VERSION	0  //100w 卡片机 h62
#define GOS_gk7102s_T5821GAA_VERSION	0  //100w 卡片机 h62
#define GOS_gk7102s_T5826GAA_VERSION	0  //100w 卡片机 h62
#define GOS_gk7102s_T5703GCA_VERSION	0  //200w 卡片机 f23
#define GOS_gk7102s_T5830GCA_VERSION	0  //200w 云台机 f23
#define GOS_gk7102s_T5830GCB_VERSION	0  //200w 云台机 f23 GOS_gk7102s_T5830GCA_VERSION 有线
#define GOS_gk7102c_C5833GCA_VERSION	0  //200w 云台机 f23 GOKE_CHIP_7102C_A
#define GOS_gk7102c_C5925GCA_VERSION	0  //200w 户外机 f23 GOKE_CHIP_7102C_A
#define GOS_gk7102c_C5929GCA_VERSION	0  //200w 户外机 f23 GOKE_CHIP_7102C_A

#define GOS_gk7102c_C5931GCA_VERSION	0  //200w 户外机 f23 GOKE_CHIP_7102C_A
#define GOS_gk7102c_C5931GCB_VERSION	0  //200w 户外机 f23 GOKE_CHIP_7102C_A GOS_gk7102c_C5931GCA_VERSION
#define GOS_gk7102c_C5931GCC_VERSION	0  //200w 户外机 f23 GOKE_CHIP_7102C_A GOS_gk7102c_C5931GCA_VERSION
#define GOS_gk7102c_C5931GCD_VERSION	0  //200w 户外机 f23 GOKE_CHIP_7102C_A GOS_gk7102c_C5931GCA_VERSION
#define GOS_gk7102c_C5931GCE_VERSION	0  //200w 户外机 f23 GOKE_CHIP_7102C_A GOS_gk7102c_C5931GCA_VERSION

#define GOS_gk7202_C5931GCF_VERSION		0  //200w 户外机 f23 GOKE_CHIP_7202
#define GOS_gk7202_C5933GCA_VERSION		1  //200w 户外机 f23 GOKE_CHIP_7202

#define GOS_gk7202_C5939GEA_VERSION		0  //400w 户外机 

#define GOKE_CHIP_7102C_A				0
#define GOKE_CHIP_7202					1
#define GOKE_CHIP_7205S					0

#define GOS_H265                  		1  // 0:H264 1:H265
#define GOS_VIDEO_2304_1296             1  // 插值300万

#define Make_SDK						1


/* 设备宏分类,根据主控区分是否有意义,7101,7102,7102s对应用来说是否有区别,sensor的区分还是有意义的 */
/*============ sensor =============*/
#if (GOS_gk7102_T5703GAB_VERSION || GOS_gk7102s_T5830GAA_VERSION || GOS_gk7102s_T5708GAA_VERSION || GOS_gk7102s_T5825GAB_VERSION || GOS_gk7102s_T5821GAA_VERSION || GOS_gk7102s_T5826GAA_VERSION)
#define SENSOR_SOIH62           1
#elif (GOS_gk7102s_T5703GCA_VERSION || GOS_gk7102s_T5830GCA_VERSION ||GOS_gk7102c_C5929GCA_VERSION || GOS_gk7102c_C5833GCA_VERSION || GOS_gk7102c_C5925GCA_VERSION || GOS_gk7102c_C5931GCA_VERSION || GOS_gk7202_C5933GCA_VERSION || GOS_gk7202_C5931GCF_VERSION)
#define SENSOR_JXF23            1
#endif

//============configuration===========
#define DOMESTIC_SERVER			1		// 0 国外     1国内（只针对ulife平台)
#define VOIC_LANGUAGE			1		// 0 简单提示 1中文  2英文
#if DOMESTIC_SERVER
#define Amazon_AVS				0       // Amazon Alexa Voice Service
#define Amazon_ASK				0       // Amazon Alexa Skills Kit
#else
#define Amazon_AVS				0       // Amazon Alexa Voice Service
#define Amazon_ASK				3       // Amazon Alexa Skills Kit  0:none 1:Alexa 2:Google 3:Alexa&Google
#endif
#define SOUND_PLAY				1		//语音播报开关 0 off 1 on
#define GOS_21CN				0       //和 GOS_21CN_V2不兼容 关闭GOS_21CN_V2
#define GOS_21CN_V2             1       //新版SDK 和 GOS_21CN不兼容 关闭GOS_21CN

#define GOS_21CN_TEST_ENV       0       //0:formal environment 1:test environment
#define GOS_21CN_MUSIC          1

#if GOS_gk7202_C5939GEA_VERSION || GOS_gk7202_C5933GCA_VERSION
#define GOS_21CN_QLINK          0		//21cn无感配网功能
#else
#define GOS_21CN_QLINK          1		//21cn无感配网功能
#endif
#define GOS_PERSON_BODY_DETECT  1       //人形侦测功能
#define MOTION_TRACKING     	1		//移动追踪



#define AEC_OPEN				0       // 回声消除的宏
#define VOICE_MODE_SWITCH		0       // APP是否支持全双工和半双工切换 依赖AEC_OPEN

#define SELECT_RECORD_LIB		4       //选择录像库，1:预分配存储库；2:公版tutk单独的录像方式；3:不预分配
#if (SELECT_RECORD_LIB == 1)
#define DISK_MANAGER              
#elif(SELECT_RECORD_LIB == 2)
#define PUBLIC_TUTK_PALYBACK_SUPPORT
#elif(SELECT_RECORD_LIB == 3)
#define RECORD_LJJ 				1
#endif

#if (GOS_gk7202_C5931GCF_VERSION || GOS_gk7202_C5933GCA_VERSION || GOS_gk7202_C5939GEA_VERSION)
#define GOS_Full_Color_Night_Vision		1
#endif

#if GOS_gk7102c_C5931GCA_VERSION
#define IRCUT_5931
#endif

#define CLOUD_STORAGE			1		//能力集云存储定义:0. 不支持云存储; 1. 支持云存储; 2. 不支持云存储, 带进度条的SD卡回放; 3. 支持云存储, 不带进度条的SD卡回放;
#define P2P_PLATFORM			5       // 1. TUTK   2. 4.0_P2P   3. 4.0_TCP   4. 4.0_TCP&4.0_P2P
#define ULIFE_PUSH				1       // 0. tutk推送服务; 1. ulife推送服务
#define SDK_USE_TLIB			0		//Ulife1.0平台相关宏开关
#define TUTK_PLATFORM_FLAG		1		//TUTK平台相关宏开关
#define TUTK_SDK				0		//编SDK时打开，默认关闭
#define GK_MEDIA_BUF_RECORD		1		//使用国科media buf录像
#define TUTK_PLATFORM_WITH_40TCP 0      // TUTK是否带有TCP转发
//#define WIFI_AP_MODE_21CN		1 		//21CN AP模式

#define FFMPEG_MP4				0
#define MY_MP4					0		//200W
#define MP4_V2					0		//130W, 100W
#define GOS_VENC_CALCBITRATE	0		//帧率、码率统计
#define GOS_TEMP_HUM			0		//5886g专用 能力集温湿度开关
#if (GOS_gk7102s_T5830GAA_VERSION || GOS_gk7102s_T5830GCA_VERSION || GOS_gk7102c_C5833GCA_VERSION)        //FOR ircut
#define  GOS_PHOTOSENSITIVE		5       // CONS:5  
#else
#define  GOS_PHOTOSENSITIVE		3	    // PROS:3
#endif
#define HARD_UNBIND			 	1       // 是否支持硬解绑
#define AP_HARD_UNBIND			0       // AP模式机器是否支持硬解绑
#define _RECORD_TYPE_ALIYUN		1       //阿里云存储功能开关
#define AUDIO_ALL_IN_G711A		1

//============未调试过的功能模块,还没启用过==========
#define GOS_MODULE_RTSP         0
#define GOS_MODULE_ONVIF        0

//============usual function module==========
#if GOS_gk7102_T5886GAA_VERSION
#define GOS_MODULE_LOG		    	1
#define GOS_MODULE_RECORD	    	1
#define GOS_MODULE_SCHEDULES_RECORD	0
#define GOS_MODULE_COMM	        	1 
#define GOS_MODULE_UPGRADE			1
#define GOS_MODULE_MOTOR	        1
#define GOS_MODULE_ONVIF	        0
#define GOS_MODULE_VIDEO		    0	//暂时定义成0
#define GOS_MODULE_AUDIO	        1
#define GOS_MODULE_WIFI	        	1
#define GOS_MODULE_OSD	        	1
#define GOS_MODULE_ALARM	        1
#define GOS_MODULE_TEMP_HUM	    	0
#define GOS_MODULE_NIGHT_VISUAL		1
#define GOS_MODULE_LED	        	1
#define GOS_MODULE_SNAP	        	1
#define GOS_MODULE_MOTION	    	1
#define GOS_MODULE_WATCH_DOG     	1
#define GOS_SEGMENT_FAULT 			1
#define GOS_LINE				    0
#define GOS_WIFI 					1

#elif (GOS_gk7102s_T5830GCB_VERSION)
#define GOS_MODULE_LOG		    	1
#define GOS_MODULE_RECORD	    	1
#define GOS_MODULE_SCHEDULES_RECORD	0
#define GOS_MODULE_COMM	        	1
#define GOS_MODULE_UPGRADE			0
#define GOS_MODULE_MOTOR	        1
#define GOS_MODULE_ONVIF	        0
#define GOS_MODULE_VIDEO		    0	//暂时定义成0
#define GOS_MODULE_AUDIO	        1
#define GOS_MODULE_WIFI	        	1
#define GOS_MODULE_OSD	        	1
#define GOS_MODULE_ALARM	        1
#define GOS_MODULE_TEMP_HUM	    	0
#define GOS_MODULE_NIGHT_VISUAL		1
#define GOS_MODULE_LED	        	1
#define GOS_MODULE_SNAP	        	1
#define GOS_MODULE_MOTION	    	1
#define GOS_MODULE_WATCH_DOG    	1
#define GOS_SEGMENT_FAULT 			1
#define GOS_LINE					1
#define GOS_WIFI 					1

#elif (GOS_gk7102s_T5830GCA_VERSION)
#define GOS_MODULE_LOG		    	1
#define GOS_MODULE_RECORD	    	1
#define GOS_MODULE_SCHEDULES_RECORD	0
#define GOS_MODULE_COMM	        	1
#define GOS_MODULE_UPGRADE			0
#define GOS_MODULE_MOTOR	        1
#define GOS_MODULE_ONVIF	        0
#define GOS_MODULE_VIDEO		    0	//暂时定义成0
#define GOS_MODULE_AUDIO	        1
#define GOS_MODULE_WIFI	        	1
#define GOS_MODULE_OSD	        	1
#define GOS_MODULE_ALARM	        1
#define GOS_MODULE_TEMP_HUM	    	0
#define GOS_MODULE_NIGHT_VISUAL		1
#define GOS_MODULE_LED	        	1
#define GOS_MODULE_SNAP	        	1
#define GOS_MODULE_MOTION	    	1
#define GOS_MODULE_WATCH_DOG    	1
#define GOS_SEGMENT_FAULT 			1
#define GOS_LINE					0
#define GOS_WIFI 					1

#elif (GOS_gk7102c_C5833GCA_VERSION)
#define GOS_MODULE_LOG		    		1
#define GOS_MODULE_RECORD	    		1
#define GOS_MODULE_SCHEDULES_RECORD		0
#define GOS_MODULE_COMM	        		1	//////////////////////////////////////////////////////////
#define GOS_MODULE_UPGRADE				0
#define GOS_MODULE_MOTOR	        	1	//////////////////////////////////////////////////////////
#define GOS_MODULE_ONVIF	        	0
#define GOS_MODULE_VIDEO		    	0	//暂时定义成0
#define GOS_MODULE_AUDIO	        	1
#define GOS_MODULE_WIFI	        		1
#define GOS_MODULE_OSD	        		1
#define GOS_MODULE_ALARM	        	1
#define GOS_MODULE_TEMP_HUM	    		0
#define GOS_MODULE_NIGHT_VISUAL			1
#define GOS_MODULE_LED	        		1
#define GOS_MODULE_SNAP	        		1
#define GOS_MODULE_MOTION	    		1
#define GOS_MODULE_WATCH_DOG     		1
#define GOS_SEGMENT_FAULT 				0
#define GOS_LINE				    	0
#define GOS_WIFI 						1

#elif (GOS_gk7102c_C5929GCA_VERSION || GOS_gk7102c_C5925GCA_VERSION || GOS_gk7102c_C5931GCA_VERSION || GOS_gk7202_C5933GCA_VERSION || GOS_gk7202_C5931GCF_VERSION || GOS_gk7202_C5939GEA_VERSION)
#define GOS_MODULE_LOG		    		1
#define GOS_MODULE_RECORD	    		0
#define GOS_MODULE_SCHEDULES_RECORD		0
#define GOS_MODULE_COMM	        		0
#define GOS_MODULE_UPGRADE				0
#define GOS_MODULE_MOTOR	        	0
#define GOS_MODULE_ONVIF	        	0
#define GOS_MODULE_VIDEO		    	0	//暂时定义成0
#define GOS_MODULE_AUDIO	        	1
#define GOS_MODULE_WIFI	        		1
#define GOS_MODULE_OSD	        		1
#define GOS_MODULE_ALARM	        	1
#define GOS_MODULE_TEMP_HUM	    		0
#define GOS_MODULE_NIGHT_VISUAL			1
#define GOS_MODULE_LED	        		1
#define GOS_MODULE_SNAP	        		1
#define GOS_MODULE_MOTION	    		1
#define GOS_MODULE_WATCH_DOG     		1
#define GOS_SEGMENT_FAULT 				1
#define GOS_LINE				   		1
#if GOS_gk7202_C5939GEA_VERSION || GOS_gk7202_C5933GCA_VERSION
#define GOS_WIFI 						0
#else
#define GOS_WIFI 						1
#endif

#elif (GOS_gk7102s_T5703GCA_VERSION)
#define GOS_MODULE_LOG		    	1
#define GOS_MODULE_RECORD	    	1
#define GOS_MODULE_SCHEDULES_RECORD	0
#define GOS_MODULE_COMM	        	0
#define GOS_MODULE_UPGRADE			0
#define GOS_MODULE_MOTOR	        0
#define GOS_MODULE_ONVIF	        0
#define GOS_MODULE_VIDEO		    0	//暂时定义成0
#define GOS_MODULE_AUDIO	        1
#define GOS_MODULE_WIFI	        	1
#define GOS_MODULE_OSD	        	1
#define GOS_MODULE_ALARM	        1
#define GOS_MODULE_TEMP_HUM	    	0
#define GOS_MODULE_NIGHT_VISUAL		1
#define GOS_MODULE_LED	        	1
#define GOS_MODULE_SNAP	        	1
#define GOS_MODULE_MOTION	    	1
#define GOS_MODULE_WATCH_DOG     	1
#define GOS_SEGMENT_FAULT 			0
#define GOS_LINE				    0
#define GOS_WIFI 					1

#elif (GOS_gk7102_T5703GAA_VERSION || GOS_gk7102s_T5830GAA_VERSION )
#define GOS_MODULE_LOG		    	1
#define GOS_MODULE_RECORD	    	1
#define GOS_MODULE_SCHEDULES_RECORD	0
#define GOS_MODULE_COMM	        	1
#define GOS_MODULE_UPGRADE			0
#define GOS_MODULE_MOTOR	        1
#define GOS_MODULE_ONVIF	        0
#define GOS_MODULE_VIDEO		    0	//暂时定义成0
#define GOS_MODULE_AUDIO	        1
#define GOS_MODULE_WIFI	        	1
#define GOS_MODULE_OSD	        	1
#define GOS_MODULE_ALARM	        1
#define GOS_MODULE_TEMP_HUM	    	0
#define GOS_MODULE_NIGHT_VISUAL		1
#define GOS_MODULE_LED	        	1
#define GOS_MODULE_SNAP	        	1
#define GOS_MODULE_MOTION	    	1
#define GOS_MODULE_WATCH_DOG     	1
#define GOS_SEGMENT_FAULT 			0
#define GOS_LINE				    0
#define GOS_WIFI 					1

#elif (GOS_gk7102s_T5708GAA_VERSION || GOS_gk7102_T5703GAB_VERSION || GOS_gk7102s_T5825GAB_VERSION || GOS_gk7102s_T5821GAA_VERSION || GOS_gk7102s_T5826GAA_VERSION)
#define GOS_MODULE_LOG		    	1
#define GOS_MODULE_RECORD	    	1
#define GOS_MODULE_SCHEDULES_RECORD	0
#define GOS_MODULE_COMM	        	0
#define GOS_MODULE_UPGRADE			0
#define GOS_MODULE_MOTOR	        0
#define GOS_MODULE_ONVIF	        0
#define GOS_MODULE_VIDEO		    0	//暂时定义成0
#define GOS_MODULE_AUDIO	        1
#define GOS_MODULE_WIFI	        	1
#define GOS_MODULE_OSD	        	1
#define GOS_MODULE_ALARM	        1
#define GOS_MODULE_TEMP_HUM	    	0
#define GOS_MODULE_NIGHT_VISUAL		1
#define GOS_MODULE_LED	        	1
#define GOS_MODULE_SNAP	        	1
#define GOS_MODULE_MOTION	    	1
#define GOS_MODULE_WATCH_DOG     	1
#define GOS_SEGMENT_FAULT 			0
#define GOS_LINE				    0
#define GOS_WIFI 					1

#elif GOS_gk7102_T5820GBA_VERSION
#define GOS_MODULE_LOG		    	1
#define GOS_MODULE_RECORD	    	1
#define GOS_MODULE_SCHEDULES_RECORD	0
#define GOS_MODULE_COMM	        	0 
#define GOS_MODULE_MOTOR	        0
#define GOS_MODULE_ONVIF	        0
#define GOS_MODULE_VIDEO		    0		//暂时定义成0
#define GOS_MODULE_AUDIO	        1
#define GOS_MODULE_WIFI	        	1
#define GOS_MODULE_OSD	        	1
#define GOS_MODULE_ALARM	        1
#define GOS_MODULE_TEMP_HUM	    	0
#define GOS_MODULE_NIGHT_VISUAL		1
#define GOS_MODULE_LED	        	1
#define GOS_MODULE_SNAP	        	1
#define GOS_MODULE_MOTION	    	1
#define GOS_MODULE_WATCH_DOG     	1
#define GOS_SEGMENT_FAULT 			0
#define GOS_LINE				    0
#define GOS_WIFI 					1

#elif GOS_gk7101_T5886GCA_VERSION
#define GOS_MODULE_LOG		    	1
#define GOS_MODULE_RECORD	    	1
#define GOS_MODULE_SCHEDULES_RECORD	0
#define GOS_MODULE_COMM	        	1 
#define GOS_MODULE_MOTOR	        1
#define GOS_MODULE_ONVIF	        0
#define GOS_MODULE_VIDEO		    0
#define GOS_MODULE_AUDIO	        1
#define GOS_MODULE_WIFI	        	1
#define GOS_MODULE_OSD	        	1
#define GOS_MODULE_ALARM	        1
#define GOS_MODULE_TEMP_HUM	    	1
#define GOS_MODULE_NIGHT_VISUAL		1
#define GOS_MODULE_LED	        	1
#define GOS_MODULE_SNAP	        	1
#define GOS_MODULE_MOTION	    	1
#define GOS_MODULE_WATCH_DOG     	1
#define GOS_SEGMENT_FAULT 			1
#define GOS_LINE				    0
#define GOS_WIFI 					1

#elif GOS_gk7101_T5881GCA_VERSION
#define GOS_MODULE_LOG		    	1
#define GOS_MODULE_RECORD	    	1
#define GOS_MODULE_SCHEDULES_RECORD	0
#define GOS_MODULE_COMM	        	1 
#define GOS_MODULE_MOTOR	        1
#define GOS_MODULE_ONVIF	        0
#define GOS_MODULE_VIDEO		    0
#define GOS_MODULE_AUDIO	        1
#define GOS_MODULE_WIFI	        	1
#define GOS_MODULE_OSD	        	1
#define GOS_MODULE_ALARM	        1
#define GOS_MODULE_TEMP_HUM	    	0
#define GOS_MODULE_NIGHT_VISUAL		1
#define GOS_MODULE_LED	        	1
#define GOS_MODULE_SNAP	        	1
#define GOS_MODULE_MOTION	    	1
#define GOS_MODULE_WATCH_DOG     	0
#define GOS_SEGMENT_FAULT 			0
#define GOS_LINE				    0
#define GOS_WIFI 					1

#elif GOS_gk7101_T5820GCA_VERSION
#define GOS_MODULE_LOG		    	1
#define GOS_MODULE_RECORD	    	1
#define GOS_MODULE_SCHEDULES_RECORD	0
#define GOS_MODULE_COMM	        	0 
#define GOS_MODULE_MOTOR	        0
#define GOS_MODULE_ONVIF	        0
#define GOS_MODULE_VIDEO		    0
#define GOS_MODULE_AUDIO	        1
#define GOS_MODULE_WIFI	        	1
#define GOS_MODULE_OSD	        	1
#define GOS_MODULE_ALARM	        1
#define GOS_MODULE_TEMP_HUM	    	0
#define GOS_MODULE_NIGHT_VISUAL		1
#define GOS_MODULE_LED	        	1
#define GOS_MODULE_SNAP	        	1
#define GOS_MODULE_MOTION	    	1
#define GOS_MODULE_WATCH_DOG     	0
#define GOS_SEGMENT_FAULT 			0
#define GOS_LINE				    0
#define GOS_WIFI 					1

#elif GOS_gk7102_T5881GBA_VERSION
#define GOS_MODULE_LOG		    	1
#define GOS_MODULE_RECORD	    	1
#define GOS_MODULE_SCHEDULES_RECORD	0
#define GOS_MODULE_COMM	        	1 
#define GOS_MODULE_MOTOR	        1
#define GOS_MODULE_ONVIF	        0
#define GOS_MODULE_VIDEO		    0
#define GOS_MODULE_AUDIO	        1
#define GOS_MODULE_WIFI	        	1
#define GOS_MODULE_OSD	        	1
#define GOS_MODULE_ALARM	        1
#define GOS_MODULE_TEMP_HUM	    	0
#define GOS_MODULE_NIGHT_VISUAL		1
#define GOS_MODULE_LED	        	1
#define GOS_MODULE_SNAP	        	1
#define GOS_MODULE_MOTION	    	1
#define GOS_MODULE_WATCH_DOG     	0
#define GOS_SEGMENT_FAULT 			0
#define GOS_LINE				    0
#define GOS_WIFI 					1

#elif GOS_gk7101_T2858GCA_VERSION
#define GOS_MODULE_LOG		    1
#define GOS_MODULE_RECORD	    1
#define GOS_MODULE_SCHEDULES_RECORD	0
#define GOS_MODULE_COMM	        1 
#define GOS_MODULE_MOTOR	    1
#define GOS_MODULE_ONVIF	    0
#define GOS_MODULE_VIDEO		0
#define GOS_MODULE_AUDIO	    1
#define GOS_MODULE_WIFI	        1
#define GOS_MODULE_OSD	        1
#define GOS_MODULE_ALARM	    1
#define GOS_MODULE_TEMP_HUM	    0
#define GOS_MODULE_NIGHT_VISUAL	1
#define GOS_MODULE_LED	        1
#define GOS_MODULE_SNAP	        1
#define GOS_MODULE_MOTION	    1
#define GOS_MODULE_WATCH_DOG    0
#define GOS_SEGMENT_FAULT 		0
#define GOS_LINE				1
#define GOS_WIFI 				1

#elif GOS_gk7102_T2858GBA_VERSION
#define GOS_MODULE_LOG		    1
#define GOS_MODULE_RECORD	    1
#define GOS_MODULE_SCHEDULES_RECORD	0
#define GOS_MODULE_COMM	        0 
#define GOS_MODULE_MOTOR	    0
#define GOS_MODULE_ONVIF	    0
#define GOS_MODULE_VIDEO		0
#define GOS_MODULE_AUDIO	    1
#define GOS_MODULE_WIFI	        1
#define GOS_MODULE_OSD	        1
#define GOS_MODULE_ALARM	    1
#define GOS_MODULE_TEMP_HUM	    0
#define GOS_MODULE_NIGHT_VISUAL	1
#define GOS_MODULE_LED	        1
#define GOS_MODULE_SNAP	        1
#define GOS_MODULE_MOTION	    1
#define GOS_MODULE_WATCH_DOG    0
#define GOS_SEGMENT_FAULT 		0
#define GOS_LINE				1
#define GOS_WIFI 				1

#elif GOS_gk7101_T5925GCA_VERSION
#define GOS_MODULE_LOG		    1
#define GOS_MODULE_RECORD	    1
#define GOS_MODULE_SCHEDULES_RECORD	0
#define GOS_MODULE_COMM	        0 
#define GOS_MODULE_MOTOR	    0
#define GOS_MODULE_ONVIF	    0
#define GOS_MODULE_VIDEO		0
#define GOS_MODULE_AUDIO	    1
#define GOS_MODULE_WIFI	        1
#define GOS_MODULE_OSD	        1
#define GOS_MODULE_ALARM	    1
#define GOS_MODULE_TEMP_HUM	    0
#define GOS_MODULE_NIGHT_VISUAL	1
#define GOS_MODULE_LED	        1
#define GOS_MODULE_SNAP	        1
#define GOS_MODULE_MOTION	    1
#define GOS_MODULE_WATCH_DOG    0
#define GOS_SEGMENT_FAULT 		0
#define GOS_LINE				1
#define GOS_WIFI 				1

#endif
//=========== 防止宏未定义的编译报错 ==========//
#ifndef SENSOR_SOIH62
#define SENSOR_SOIH62           0
#endif
#ifndef SENSOR_JXF23
#define SENSOR_JXF23           0
#endif

//===========wifi module config==========
#if (GOS_gk7102_T5703GAA_VERSION || GOS_gk7102_T5703GAB_VERSION|| GOS_gk7102s_T5830GAA_VERSION ||GOS_gk7102s_T5708GAA_VERSION || GOS_gk7102s_T5825GAB_VERSION || GOS_gk7102s_T5821GAA_VERSION || GOS_gk7102s_T5826GAA_VERSION || GOS_gk7102s_T5703GCA_VERSION  || GOS_gk7102s_T5830GCA_VERSION || GOS_gk7102_T5886GAA_VERSION || GOS_gk7102c_C5929GCA_VERSION || GOS_gk7102c_C5833GCA_VERSION || GOS_gk7102c_C5925GCA_VERSION || GOS_gk7102c_C5931GCA_VERSION || GOS_gk7202_C5931GCF_VERSION)
#define GOS_WIFI7601			 0
#define GOS_WIFI8188			 1
#elif GOS_gk7202_C5939GEA_VERSION || GOS_gk7202_C5933GCA_VERSION
#define GOS_WIFI7601			 0
#define GOS_WIFI8188			 0
#else
#define GOS_WIFI7601			 1
#define GOS_WIFI8188			 0
#endif

#if GOS_WIFI
#define WIFI_AP_MODE_21CN		1 		//21CN AP模式
#else
#define WIFI_AP_MODE_21CN		0 		//21CN AP模式
#endif

#if (GOS_WIFI8188 && GOS_gk7102_T5886GAA_VERSION)
#define GOS_WIFI8188EUS	     1
#else
#define GOS_WIFI8188FTV	     1
#endif
//===========sensor不支持翻转:sc1035,h62,需要用编码翻转;gc1024 & ov2710支持vi翻转==========//
#if (GOS_gk7102_T5820GBA_VERSION || GOS_gk7102_T5881GBA_VERSION || GOS_gk7102_T2858GBA_VERSION || SENSOR_SOIH62)
#define IMAGE_ENCODE_FLIP       1
#else
#define IMAGE_ENCODE_FLIP       0
#endif

//===========已经停用,后将完全舍弃的功能模块==========//
#define REBOOT_IN_AM2OCLOCK		0
//==================================================//
enum ALARM_TYPE
{
    UNKNOWN = 0,
    VIDEO_MOTION,
    PIR_MOTION,
    PIR_VIDEO_MOTION, 
    AUDIO_MOTION, 
    IO_ALARM,
    LOW_TEMP_ALARM,
    HIGH_TEMP_ALARM,
    LOW_HUM_ALARM,
    HIGH_HUM_ALARM,
    LOW_WBGT_ALARM,
    HIGH_WBGT_ALARM,
    CALLING,
    BODY_DETECT_ALARM
};

//系统参数
typedef struct gsSYS_MAIN_S
{
    int                     day_night_switch;   		//1晚上 0白天
    int                     net_line_or_wifi;   		//0 line 1 wifi
    int                     search_resart;   			//bordcast discover rebuilt 0:off 1:on
    int                     platform_enable;			//0:close 1:open local and close platform 2:open all    
    int                     set_vi_flag_day;    		//切换夜视的控制
    int                     set_vi_flag_night;  		//切换夜视的控制
    int						Full_Color_Night_Vision;	//全彩夜视控制
    int						Full_Color_State;			//全彩夜视状态
    int						Body_Detect_State;			//人形识别状态
    int						Body_Track_State;			//人形追踪状态
    int						Alarm_Interval;				//告警间隔
    int                     onvif_compressing;  		//onvif是否解压完全
    int                     venc_max_farme;     		//vi编码最大帧率
    int                     audio_decode_control;		//声音报警控制
    int                     audio_yelp;         		//安抚音乐标示
    int                     alarm_control;      		//一键布放开关 
    int 					alarm_msg_push;				//报警消息推送开关
	int                     LowLightNoiseLvl;   		//低照度等级
    int                     alarm_flag_all;     		//所有报警标志  
    int                     alarm_pir;          		//pir报警开关
    int                     alarm_pir_check_sec;		//pir判定时长
    int                     alarm_pir_flag;
    int                     alarm_calling;      		//按门铃报警开关
    int                     alarm_io;           		//io报警开关
    int                     record_state;       		//录像状态  
    int						snap_quality;	    		//抓拍质量 0主码流 1次码流
    int						tutk;						//0不支持公版app  1支持
    int                     led_ir;
    int                     led_state;          		//灯状态
    int                     light_state;
    int                     Power;              		//p n
    int                     log_level;          		//日志等级
    int                     reboot_flag;        		//是否要重启
    int                     DevDhcpOpen;        		//0关 1开 
    int                     Aac_Enc_s32Handle;  		//音频句柄
    int                     Aaclc_Enc_s32Handle;		//音频句柄
    int                     Aac_Dec_s32Handle;  		//音频句柄
    int                     Aaclc_Dec_s32Handle;		//音频句柄
    int						app_get_stream_flag;		//0:客户端没连接  1:客户端已连接,取流中
    //升级用
    int                     upgrade_flag;
    unsigned int            upgrade_count;
    char *                  upgrade_buf;    
	int						device_switch;				//摄像头开关
	int						device_mic_switch;			//麦克风开关
	int						device_led_switch;			//状态灯开关
	int 					ulife_tool_switch;			//产测工具开关
    char                    bind_usrname[32];   		//绑定用户名   
    char                    qrcode_sum[32];     		//二维码扫描校验码  
    char                    TimerISRFlag[1][3];			//秒定时中断标识(用于编码器刷新时间OSD)
} PACKED SYS_MAIN_S;
							
extern SYS_MAIN_S g_sysMainInfo;//johnny.liu: defined in main.c

//=========gpio handle define========	//define in main.c
extern GADI_SYS_HandleT gpioHandle_ircut_l;
extern GADI_SYS_HandleT gpioHandle_ircut_r;
extern GADI_SYS_HandleT gpioHandle_speaker;
extern GADI_SYS_HandleT gpioHandle_key;
extern GADI_SYS_HandleT gpioHandle_led_red;
extern GADI_SYS_HandleT gpioHandle_led_green;
extern GADI_SYS_HandleT gpioHandle_m2b_n;
extern GADI_SYS_HandleT gpioHandle_m2b_p;
extern GADI_SYS_HandleT gpioHandle_m2a_n;
extern GADI_SYS_HandleT gpioHandle_m2a_p;
extern GADI_SYS_HandleT gpioHandle_m1b_n;
extern GADI_SYS_HandleT gpioHandle_m1b_p;
extern GADI_SYS_HandleT gpioHandle_m1a_n;
extern GADI_SYS_HandleT gpioHandle_m1a_p;
extern GADI_SYS_HandleT gpioHandle_ptz_power;
extern GADI_SYS_HandleT gpioHandle_white_led_power;
extern GADI_SYS_HandleT gpioHandle_ircut_led_power;


#define SAMPLE_PRT(fmt...)   \
    do {\
        printf("[%s]-%d: ", __FUNCTION__, __LINE__);\
        printf(fmt);\
       }while(0)
       
#define DEFAULT_AUDIO_FRAME_RATE_BPS 8000

#endif

