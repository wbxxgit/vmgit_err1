
/*
Description: 
              ...
*/

#ifndef _SDKOUT_IMPL_H
#define _SDKOUT_IMPL_H

#include "sdk_commonstruct.h"
#include "global.h"
#if defined (__cplusplus)
extern "C" {
#endif


#define SDKOUT_IMPL_VERSION "V1.00.000"
#define SDK_DEVICE_ABILITY_VERSION 2


//********************************************************************
//************** command list ***********************************
//********************************************************************
/*
Command definition format
----------------------------------------------------
|31              24 |23                  16  | 15        12 | 11               0|
| Command Type |    module type|   Reserved   |    command number |
----------------------------------------------------
Command type(31-24): 
	         0x00 SDK command for LAN and WLAN 
             0x01 SDK command for LAN only
             0x02 SDK command for WLAN only
 
module type (23-16): Define command for module type, so it can Easy to find

Command number:(15-0):15-12 retain temporary
                      11-0 definite command 
*/

//********************************************************************
//********module type: System (a1)*******************************
//********************************************************************
//System initialization:
#define SDKCMD_SYS_INIT	0x00a10001

//system run
#define SDKCMD_SYS_RUN	(SDKCMD_SYS_INIT + 1)

//system exit:
#define SDKCMD_SYS_EXIT	(SDKCMD_SYS_RUN + 1)

//Get device type number, The same solution for different products , should have different models
//Implement further subdivided: 4 bit  of high bit partion in second bytes representation solution type,  4 bit  of low bit partion representation the product type
//example:0x00a1c903  ---->0xc9=0201---->hisi solution+ outdoor bullet camera 

//param:struct*	T_SDK_DEVICE_INFO
#define SDKCMD_GET_DEVICE_INFO	(SDKCMD_SYS_EXIT + 1)

//param: none 
#define SDKCMD_SAVE_ALL_PARAM	(SDKCMD_GET_DEVICE_INFO + 1)

//param: none
#define SDKCMD_REBOOT_DEVICE	(SDKCMD_SAVE_ALL_PARAM + 1)

//param: none
#define SDKCMD_RESET_DEVICE	(SDKCMD_REBOOT_DEVICE + 1)

//param:struct*	T_SDK_DEVICE_TIME 
#define SDKCMD_SET_DEVICE_TIME	(SDKCMD_RESET_DEVICE + 1)

//param:struct*	T_SDK_NIGHT_VISION 
#define SDKCMD_SET_NIGHT_VISION	(SDKCMD_SET_DEVICE_TIME + 1)

#define SDKCMD_GET_NIGHT_VISION	(SDKCMD_SET_NIGHT_VISION + 1)
////param:unsigned int*	un_connected;	//value range(0:disconnected 1:connected)	
#define SDKCMD_SET_CONNECTED_PLATFORM_STATUS	(SDKCMD_GET_NIGHT_VISION + 1)

////param:struct*	T_SDK_LED;	
#define SDKCMD_SET_LED_STATUS	(SDKCMD_SET_CONNECTED_PLATFORM_STATUS + 1)

//设置IPC接入TUTK平台的鉴权信息  param:struct*	T_SDK_DEVICE_AUTHENTICATION_INFO
#define SDKCMD_SET_DEVICE_AUTHENTICATION	(SDKCMD_SET_LED_STATUS + 1)

//获取IPC接入TUTK平台的鉴权信息  param:struct*	T_SDK_DEVICE_AUTHENTICATION_INFO
#define SDKCMD_GET_DEVICE_AUTHENTICATION	(SDKCMD_SET_DEVICE_AUTHENTICATION + 1)

//获取IPC能力集   				param:struct*	T_SDK_DEVICE_ABILITY_INFO
#define SDKCMD_GET_DEVICE_ABILITY			(SDKCMD_GET_DEVICE_AUTHENTICATION + 1)

//获取电池信息
#define SDKCMD_GET_BATERRY_INFO			(SDKCMD_GET_DEVICE_ABILITY + 1)

//设置灯开关
#define SDKCMD_SET_LIGHT_SWITCH		(SDKCMD_GET_BATERRY_INFO + 1)

//获取灯开关
#define SDKCMD_GET_LIGHT_SWITCH		(SDKCMD_SET_LIGHT_SWITCH + 1)

//设置灯照时长，包括手动开灯时长、触发亮灯时长
#define SDKCMD_SET_LIGHT_DURATION		(SDKCMD_GET_LIGHT_SWITCH + 1)

//获取灯照时长，包括手动开灯时长、触发亮灯时长
#define SDKCMD_GET_LIGHT_DURATION		(SDKCMD_SET_LIGHT_DURATION + 1)

//设置定时亮灯时间点(晚上开灯、早晨灭灯时间点，以及一周生效的天数)
#define SDKCMD_SET_LIGHT_TIMING_INFO		(SDKCMD_GET_LIGHT_DURATION + 1)

//获取定时亮灯时间点(晚上开灯、早晨灭灯时间点，以及一周生效的天数)
#define SDKCMD_GET_LIGHT_TIMING_INFO		(SDKCMD_SET_LIGHT_TIMING_INFO + 1)

//设置白光灯开关
#define SDKCMD_SET_WHITE_LED_STATUS			(SDKCMD_GET_LIGHT_TIMING_INFO + 1)

//设置红外灯开关
#define SDKCMD_SET_IRCUT_LED_STATUS			(SDKCMD_SET_WHITE_LED_STATUS + 1)

//SD卡自检测接口
#define SDKCMD_GET_SD_CARD_SELF_TEST		(SDKCMD_SET_IRCUT_LED_STATUS + 1)
//SD卡格式化

#define SDKCMD_GET_SD_CARD_INFO				(SDKCMD_GET_SD_CARD_SELF_TEST + 1)

#define SDKCMD_THREE_DEVICE_INFO			(SDKCMD_GET_SD_CARD_INFO + 1)

#define SDKCMD_GET_SD_CARD_MOUNT			(SDKCMD_THREE_DEVICE_INFO + 1)

#define SDKCMD_SET_QR_NETWORK				(SDKCMD_GET_SD_CARD_MOUNT + 1)

#define SDKCMD_SET_AP_NETWORK				(SDKCMD_SET_QR_NETWORK + 1)

#define SDKCMD_SET_PLAY_AUDIO				(SDKCMD_SET_AP_NETWORK + 1)

#define SDKCMD_SET_QLINK_FAILED				(SDKCMD_SET_PLAY_AUDIO + 1)



//********************************************************************
//********module type: video (a2)*******************************
//********************************************************************

//param: none
#define SDKCMD_SET_VIDEO_ENCODE_DEFAULT_PARAM	(0x00a20001)

//param:struct*	T_SDK_STREAM_REGISTER_CALLBACK
#define SDKCMD_REGISTER_STREAM_DATA_CALLBACK	(SDKCMD_SET_VIDEO_ENCODE_DEFAULT_PARAM + 1)

//param:struct*	T_SDK_FORCE_I_FARME 
#define SDKCMD_FORCE_VIDEO_ENCODE_I_FRAME	(SDKCMD_REGISTER_STREAM_DATA_CALLBACK + 1)

//param:struct*	T_SDK_VIDEO_ENCODE_SWITCH 
#define SDKCMD_SET_VIDEO_ENCODE_SWITCH	(SDKCMD_FORCE_VIDEO_ENCODE_I_FRAME + 1)

//param:struct*	T_SDK_VIDEO_ENCODE_TYPE 
#define SDKCMD_SET_VIDEO_ENCODE_TYPE	(SDKCMD_SET_VIDEO_ENCODE_SWITCH + 1)

//param:struct*	T_SDK_VIDEO_ENCODE_RESOLUTION 
#define SDKCMD_SET_VIDEO_ENCODE_RESOLUTION	(SDKCMD_SET_VIDEO_ENCODE_TYPE + 1)

//param:struct*	T_SDK_VIDEO_ENCODE_I_FRAME_INTERVAL 
#define SDKCMD_SET_VIDEO_ENCODE_I_FRAME_INTERVAL	(SDKCMD_SET_VIDEO_ENCODE_RESOLUTION + 1)

//param:struct*	T_SDK_VIDEO_ENCODE_BITRATE 
#define SDKCMD_SET_VIDEO_ENCODE_BITRATE	(SDKCMD_SET_VIDEO_ENCODE_I_FRAME_INTERVAL + 1)

//(not support yet)
//param:struct*	T_SDK_VENC_LOWER_BIT_CONTORL 
#define SDKCMD_SET_VIDEO_ENCODE_LOWER_BITRATE_CONTORL	(SDKCMD_SET_VIDEO_ENCODE_BITRATE + 1) 

//param:struct*	T_SDK_VIDEO_ENCODE_FRAMERATE 
#define SDKCMD_SET_VIDEO_ENCODE_FRAMERATE	(SDKCMD_SET_VIDEO_ENCODE_LOWER_BITRATE_CONTORL + 1)

//param:struct*	T_SDK_VIDEO_ENCODE_QUALITY 
#define SDKCMD_SET_VIDEO_ENCODE_QUALITY	(SDKCMD_SET_VIDEO_ENCODE_FRAMERATE + 1)

//param:struct*	T_SDK_VIDEO_ENCODE_LEVEL 
#define SDKCMD_SET_VIDEO_ENCODE_LEVEL	(SDKCMD_SET_VIDEO_ENCODE_QUALITY + 1)

//param:struct*	T_SDK_VIDEO_ENCODE_QP 
#define SDKCMD_SET_VIDEO_ENCODE_QP	(SDKCMD_SET_VIDEO_ENCODE_LEVEL + 1)

//param:struct*	T_SDK_VIDEO_ENCODE_PARAM 
#define SDKCMD_GET_VIDEO_ENCODE_PARAM	(SDKCMD_SET_VIDEO_ENCODE_QP + 1)

//设置翻转镜像的值   param:unsigned int*	un_type	    //value range(0:none,1:horizontal,2:vertical,3:horizonta+vertical)
#define SDKCMD_SET_VIDEO_ENCODE_MIRROR	(SDKCMD_GET_VIDEO_ENCODE_PARAM + 1)

//获取翻转镜像的值   param:unsigned int*	un_type	    //value range(0:none,1:horizontal,2:vertical,3:horizonta+vertical)
#define SDKCMD_GET_VIDEO_ENCODE_MIRROR	(SDKCMD_SET_VIDEO_ENCODE_MIRROR + 1)

//param:struct*	T_SDK_VIDEO_ENCODE_QUALITY 
#define SDKCMD_GET_VIDEO_ENCODE_QUALITY	(SDKCMD_GET_VIDEO_ENCODE_MIRROR + 1)

//设置当前码流的质量(高清/标清)
#define SDKCMD_SET_CURR_STREAM_QUALITY	(SDKCMD_GET_VIDEO_ENCODE_QUALITY + 1)

//获取当前码流的质量(高清/标清)
#define SDKCMD_GET_CURR_STREAM_QUALITY	(SDKCMD_SET_CURR_STREAM_QUALITY + 1)

//设置当前抓拍图片的质量(主/次码流)
#define SDKCMD_SET_SNAPSHOT_QUALITY	(SDKCMD_GET_CURR_STREAM_QUALITY + 1)

//获取当前抓拍图片的质量(0主码流 1次码流)
#define SDKCMD_GET_SNAPSHOT_QUALITY	(SDKCMD_SET_SNAPSHOT_QUALITY + 1)

//param:struct*	T_SDK_YUV_REGISTER_CALLBACK
#define SDKCMD_REGISTER_YUV_DATA_CALLBACK (SDKCMD_GET_SNAPSHOT_QUALITY + 1)//yym


//********************************************************************
//********module type: audio (a3)*******************************
//********************************************************************

//param: none
#define SDKCMD_SET_AUDIO_ENCODE_DEFAULT_PARAM	(0x00a30001)

//(not support yet)
#define SDKCMD_REGISTER_AUDIO_PCM_DATA_CALLBACK	(SDKCMD_SET_AUDIO_ENCODE_DEFAULT_PARAM + 1)

//param:struct*	T_SDK_AUDIO_ENCODE_PARAM 
#define SDKCMD_GET_AUDIO_ENCODE_PARAM	(SDKCMD_REGISTER_AUDIO_PCM_DATA_CALLBACK + 1)

//param:unsigned int*	un_switch;	//value range(0:off 1:on)
#define SDKCMD_SET_AUDIO_ENCODE_SWITCH	(SDKCMD_GET_AUDIO_ENCODE_PARAM + 1)

//param:unsigned int*	un_mode;	//value range(0:single 1:stereo)				
#define SDKCMD_SET_SOUND_MODE	(SDKCMD_SET_AUDIO_ENCODE_SWITCH + 1)

//param:enum*	E_SDK_AUDIO_ENCODE_TYPE;
#define SDKCMD_SET_AUDIO_ENCODE_TYPE	(SDKCMD_SET_SOUND_MODE + 1)

//param:unsigned int*	un_bitrate;				
#define SDKCMD_SET_AUDIO_ENCODE_BITRATE	(SDKCMD_SET_AUDIO_ENCODE_TYPE + 1)

//param:unsigned int*	un_samplerate;	
#define SDKCMD_SET_AUDIO_ENCODE_SAMPLERATE	(SDKCMD_SET_AUDIO_ENCODE_BITRATE + 1)

//param:unsigned int*	un_volume;	
#define SDKCMD_SET_AUDIO_INPUT_VOLUME	(SDKCMD_SET_AUDIO_ENCODE_SAMPLERATE + 1)
  
//param:unsigned int*	un_volume;	
#define SDKCMD_SET_AUDIO_OUTPUT_VOLUME		(SDKCMD_SET_AUDIO_INPUT_VOLUME	 + 1)

//( not support Ambarella yet)
// param:unsigned int*	un_mic_line_input;	//value range(0: mic input 1:line input)	
#define SDKCMD_SET_AUDIO_MIC_LINE	(SDKCMD_SET_AUDIO_OUTPUT_VOLUME	 + 1)

//( not support Ambarella yet)
// param:unsigned int*	un_audio_echo_cancell;		//Automatic Echo Cancellation value range(0:off 1:on)
#define SDKCMD_SET_AUDIO_ECHO_CANCELL	(SDKCMD_SET_AUDIO_MIC_LINE + 1)

//(not support yet)
#define SDKCMD_SET_INTERCOM_PARAM	(SDKCMD_SET_AUDIO_ECHO_CANCELL + 1)

//param:none
#define SDKCMD_INTERCOM_START	(SDKCMD_SET_INTERCOM_PARAM + 1)

//param:none
#define SDKCMD_INTERCOM_STOP	(SDKCMD_INTERCOM_START + 1)

//param:struct*	T_SDK_INTERCOM_DATA */
#define SDKCMD_SEND_INTERCOM_DATA	(SDKCMD_INTERCOM_STOP + 1)


//********************************************************************
//******module type: sensor (a4)******************************
//********************************************************************
// param: none
#define SDKCMD_SET_SENSOR_DEFAULT_PARAM	0x00a40001

//param:struct*	T_SDK_SENSOR_PARAM 
#define SDKCMD_GET_SENSOR_PARAM	(SDKCMD_SET_SENSOR_DEFAULT_PARAM + 1)

//param:struct*	T_SDK_SENSOR_SHARP 
#define SDKCMD_SET_SENSOR_SHARP	(SDKCMD_GET_SENSOR_PARAM + 1)

//param:unsigned int*	un_brightness;	//value range(0-100)
#define SDKCMD_SET_SENSOR_BRIGHTNESS	(SDKCMD_SET_SENSOR_SHARP + 1)


//param:unsigned int*	un_contrast;	//value range(0-100)
#define SDKCMD_SET_SENSOR_CONTRAST	(SDKCMD_SET_SENSOR_BRIGHTNESS + 1)

//param:unsigned  int*	un_hue;	//value range(0-100)
#define SDKCMD_SET_SENSOR_HUE	(SDKCMD_SET_SENSOR_CONTRAST + 1)

//param:unsigned int*	un_saturation;	//value range(0-100)
#define SDKCMD_SET_SENSOR_SATURATION	(SDKCMD_SET_SENSOR_HUE + 1)

//(not support Ambarella yet)
// param:unsigned int*	un_day_night	//value range(0:day 1:night)
#define SDKCMD_GET_SENSOR_NIGHT_DAY_STATUE	(SDKCMD_SET_SENSOR_SATURATION + 1)

//(not support Ambarella yet)
//param:unsigned int*	un_level	//value range(0-2)
#define SDKCMD_SET_SENSOR_GAMMA_LEVEL	(SDKCMD_GET_SENSOR_NIGHT_DAY_STATUE + 1)

//(not support Ambarella yet)
//param:unsigned int*	un_switch	//value range(0:off 1:on)
#define SDKCMD_SET_SENSOR_SHADING_SWITCH	(SDKCMD_SET_SENSOR_GAMMA_LEVEL + 1)

//(not support Ambarella yet)
//param:unsigned int*	un_NTSC_PAL	//value range(30:NTSC 25:PAL)
#define SDKCMD_GET_SENSOR_NTSC_PAL	(SDKCMD_SET_SENSOR_SHADING_SWITCH + 1)
#define SDKCMD_SET_SENSOR_NTSC_PAL	(SDKCMD_GET_SENSOR_NTSC_PAL + 1)

//param:struct*	T_SDK_SENSOR_AUTO_EXPOSURE
#define SDKCMD_GET_SENSOR_AUTO_EXPOSURE	(SDKCMD_SET_SENSOR_NTSC_PAL + 1)
#define SDKCMD_SET_SENSOR_AUTO_EXPOSURE	(SDKCMD_GET_SENSOR_AUTO_EXPOSURE + 1)

//param:struct*	T_SDK_SENSOR_2D
#define SDKCMD_SET_SENSOR_2D	(SDKCMD_SET_SENSOR_AUTO_EXPOSURE + 1)

//param:struct*	T_SDK_SENSOR_3D
#define SDKCMD_SET_SENSOR_3D	(SDKCMD_SET_SENSOR_2D + 1)


//********************************************************************
//**********module type: alarm (a5)******************************
//********************************************************************
/* param:none */
#define SDKCMD_SET_ALARM_DEFAULT_PARAM	0x00a50001

//param:struct*	T_SDK_ALARM_REGISTER_CALLBACK
#define SDKCMD_RIGISTER_ALARM_CALLBACK	(SDKCMD_SET_ALARM_DEFAULT_PARAM + 1)

// param:struct*	T_SDK_ALARM_PARAM
#define SDKCMD_GET_ALARM_PARAM	(SDKCMD_RIGISTER_ALARM_CALLBACK + 1)

// param:struct*	T_SDK_PIR_ALARM
#define SDKCMD_SET_PIR_ALARM_PARAM	(SDKCMD_GET_ALARM_PARAM + 1) 

// param:struct*	T_SDK_VIDEO_MOTION_ALARM
#define SDKCMD_SET_MOTION_ALARM_PARAM	(SDKCMD_SET_PIR_ALARM_PARAM + 1)

// param:struct*	T_SDK_AUDIO_ALARM
#define SDKCMD_SET_AUDIO_ALARM_PARAM	(SDKCMD_SET_MOTION_ALARM_PARAM + 1)

#define SDKCMD_GET_AUDIO_ALARM_PARAM	(SDKCMD_SET_AUDIO_ALARM_PARAM + 1)

// param:struct*	T_SDK_SHELTER_ALARM
#define SDKCMD_SET_SHELTER_ALARM_PARAM	(SDKCMD_GET_AUDIO_ALARM_PARAM + 1)

// param:struct*	T_SDK_DOORBELL_ALARM
#define SDKCMD_SET_DOORBELL_ALARM_PARAM	(SDKCMD_SET_SHELTER_ALARM_PARAM + 1)

// param:struct*	T_SDK_IO_ALARM
#define SDKCMD_SET_IO_ALARM_PARAM	(SDKCMD_SET_DOORBELL_ALARM_PARAM + 1)

//设置IPC一键布防的参数
#define SDKCMD_SET_ONEKEY_ALARM_CONTROL_PARAM	(SDKCMD_SET_IO_ALARM_PARAM + 1)

//获取IPC一键布防的参数
#define SDKCMD_GET_ONEKEY_ALARM_CONTROL_PARAM	(SDKCMD_SET_ONEKEY_ALARM_CONTROL_PARAM + 1)

//设置IPC报警铃声的参数
#define SDKCMD_SET_ALARM_RING_PARAM	(SDKCMD_GET_ONEKEY_ALARM_CONTROL_PARAM + 1)

//获取IPC报警铃声的参数
#define SDKCMD_GET_ALARM_RING_PARAM	(SDKCMD_SET_ALARM_RING_PARAM + 1)

//开始播放报警铃声
#define SDKCMD_PLAY_ALARM_RING_START (SDKCMD_GET_ALARM_RING_PARAM + 1)

//停止播放报警铃声
#define SDKCMD_PLAY_ALARM_RING_STOP	(SDKCMD_PLAY_ALARM_RING_START + 1)

//设置温度报警参数
#define SDKCMD_SET_TEMPERATURE_ALARM_PARAM	(SDKCMD_PLAY_ALARM_RING_STOP + 1)

//获取温度报警参数
#define SDKCMD_GET_TEMPERATURE_ALARM_PARAM	(SDKCMD_SET_TEMPERATURE_ALARM_PARAM + 1)

//设置电量报警参数
#define SDKCMD_SET_BATTERY_ALARM_PARAM	(SDKCMD_GET_TEMPERATURE_ALARM_PARAM + 1)

//获取电量报警参数
#define SDKCMD_GET_BATTERY_ALARM_PARAM	(SDKCMD_SET_BATTERY_ALARM_PARAM + 1)


//********************************************************************
//**********module type: OSD (a6)********************************
//********************************************************************
//param: none
#define SDKCMD_SET_OSD_DEFAULT_PARAM	0x00a60001

//param:struct*	T_SDK_ALL_OSD_PARAM
#define SDKCMD_GET_OSD_PARAM	(SDKCMD_SET_OSD_DEFAULT_PARAM + 1)

//param:struct*	T_SDK_OSD_SWITCH
#define SDKCMD_SET_OSD_SHOW_SWITCH	(SDKCMD_GET_OSD_PARAM + 1)

//param:struct*	T_SDK_OSD_COLOR
#define SDKCMD_SET_OSD_COLOR	(SDKCMD_SET_OSD_SHOW_SWITCH + 1)

//param:struct*	T_SDK_OSD_POS
#define SDKCMD_SET_OSD_POS	(SDKCMD_SET_OSD_COLOR + 1)

//param:struct*	T_SDK_OSD_TITLE
#define SDKCMD_SET_OSD_TITLE	(SDKCMD_SET_OSD_POS + 1)


//********************************************************************
//**********module type: Record (a7)******************************
//********************************************************************
//param: none
#define SDKCMD_SET_RECORD_DEFAULT_PARAM	0x00a70001

//param:struct*	T_SDK_RECORD_PARAM
#define SDKCMD_GET_RECORD_PARAM	(SDKCMD_SET_RECORD_DEFAULT_PARAM + 1)

//param:unsigned int* 	un_switch;
#define SDKCMD_SET_RECORD_SWITCH	(SDKCMD_GET_RECORD_PARAM + 1)

//param:none
#define SDKCMD_CLEAR_RECORD_FILE	(SDKCMD_SET_RECORD_SWITCH + 1)

//param:struct*	T_SDK_RECORD_LOCK_FILE
#define SDKCMD_LOCK_UNLOCK_RECORD_FILE	(SDKCMD_CLEAR_RECORD_FILE + 1)

//param:struct*	T_SDK_RECORD_MONTH_LIST
#define SDKCMD_GET_MONTH_RECORD_LIST	(SDKCMD_LOCK_UNLOCK_RECORD_FILE + 1)

//param:struct*	T_SDK_RECORD_DAY_LIST
#define SDKCMD_GET_DAY_RECORD_LIST	(SDKCMD_GET_MONTH_RECORD_LIST + 1)

#define SDKCMD_GET_DAY_ASSIGNTIME_RECORD_LIST  (SDKCMD_GET_DAY_RECORD_LIST + 1)

//param:struct*	T_SDK_RECORD_FILE_PATH
#define SDKCMD_GET_RECORD_FILE_FULL_PATH	(SDKCMD_GET_DAY_ASSIGNTIME_RECORD_LIST + 1)

//param:unsigned int*	un__switch;
#define SDKCMD_SET_LOOP_RECORD_SWITCH	(SDKCMD_GET_RECORD_FILE_FULL_PATH + 1)

//param:unsigned int*	un__switch;
#define SDKCMD_SET_AUDIO_RECORD_SWITCH	(SDKCMD_SET_LOOP_RECORD_SWITCH + 1)

//param:unsigned int*	un_duration
#define SDKCMD_SET_RECORD_FILE_DURATION	(SDKCMD_SET_AUDIO_RECORD_SWITCH + 1)

//param:unsigned int*	un_filetype  //value range(0:ts 1:mp4 2:flv)
#define SDKCMD_SET_RECORD_FILE_TYPE	(SDKCMD_SET_RECORD_FILE_DURATION + 1)

//param: T_SDK_RECORD_FILE_PATH
#define SDKCMD_DEL_RECORD_FILE	(SDKCMD_SET_RECORD_FILE_TYPE + 1)

//param: unsigned int*	un__switch;
#define SDKCMD_MANUAL_RECORD_SWITCH	(SDKCMD_DEL_RECORD_FILE + 1)

//param:struct* T_SDK_STORAGE_INFO
#define SDKCMD_GET_STORAGE_INFO	(SDKCMD_MANUAL_RECORD_SWITCH + 1)

//param: 
#define SDKCMD_FORMAT_STORAGE_REQ	(SDKCMD_GET_STORAGE_INFO + 1)
//param 
#define SDKCMD_GET_ALL_RECORD_FILETIME	(SDKCMD_FORMAT_STORAGE_REQ + 1)
//param: 
#define SDKCMD_GET_ALL_ALARM_RECORD_FILETIME	(SDKCMD_GET_ALL_RECORD_FILETIME + 1)
//param 
#define SDKCMD_GET_REFRESH_RECORD_LIST	(SDKCMD_GET_ALL_ALARM_RECORD_FILETIME + 1)
//param
#define SDKCMD_GET_REFRESH_ALARM_RECORD_LIST (SDKCMD_GET_REFRESH_RECORD_LIST+1)
//param 
#define SDKCMD_GET_RECORD_LIST_OLDEST_TIME (SDKCMD_GET_REFRESH_ALARM_RECORD_LIST+1)
//param 
#define SDKCMD_GET_RECORD_FILE_DURATION (SDKCMD_GET_RECORD_LIST_OLDEST_TIME + 1)

//new_reord
#define SDK_CMD_RECORD_DAY_EVENT_RELEASE  (SDKCMD_GET_RECORD_FILE_DURATION+1)
#define SDK_CMD_RECORD_DAY_EVENT   (SDK_CMD_RECORD_DAY_EVENT_RELEASE+1)

#define SDK_CMD_RECORD_DAY_LIST_RELEASE  (SDK_CMD_RECORD_DAY_EVENT+1)
#define SDK_CMD_RECORD_DAY_LIST   (SDK_CMD_RECORD_DAY_LIST_RELEASE+1)

#define SDK_CMD_RECORD_SPLIT  (SDK_CMD_RECORD_DAY_LIST+1)
#define SDK_CMD_RECORD_SPLIT_BUFFERRING  (SDK_CMD_RECORD_SPLIT+1)
#define SDK_CMD_RECORD_SPLIT_BUFFERRING_RELEASE (SDK_CMD_RECORD_SPLIT_BUFFERRING+1)

//(not support yet)
//********************************************************************
//**********module type: snapshot(a8) ****************************
//********************************************************************
//param: none
#define SDKCMD_SET_SNAPSHOT_DEFAULT_PARAM	0x00a80001

//param:struct*	T_SDK_SNAPSHOT_PARAM
#define SDKCMD_GET_SNAPSHOT_PARAM	(SDKCMD_SET_SNAPSHOT_DEFAULT_PARAM + 1)

//param:unsigned int*	un_switch;
#define SDKCMD_SET_SNAPSHOT_SWITCH	(SDKCMD_GET_SNAPSHOT_PARAM + 1)

//param:char*	un_snap_path;	
#define SDKCMD_SET_SNAPSHOT_PATH	(SDKCMD_SET_SNAPSHOT_SWITCH + 1)


//********************************************************************
//**********module type: upgrade (a9)****************************
//********************************************************************
//param:struct*	T_SDK_UPGRADE_PARAMS
#define SDKCMD_SET_UPGRADE_PARAM	0x00a90001

//param:struct* T_SDK_UPGRADE_BYLOCAL_PARAMS
#define SDKCMD_UPGRADE_BYLOCAL	(SDKCMD_SET_UPGRADE_PARAM + 1)

//param:struct* T_SDK_UPGRADE_BYSELF_PARAMS
#define SDKCMD_UPGRADE_BYSELF		(SDKCMD_UPGRADE_BYLOCAL+1)


//********************************************************************
//**********module type: network (aa)****************************
//********************************************************************
#define SDKCMD_SET_NETWORK_DEFAULT_PARAM	0x00aa0001

#define SDKCMD_SEARCH_SSID_NEARBY	SDKCMD_SET_NETWORK_DEFAULT_PARAM+1
//param:struct*	T_SDK_WIRELESS_PARAMS
#define SDKCMD_SET_WIRELESS_PARAM	(SDKCMD_SEARCH_SSID_NEARBY + 1)

//param:unsigned int*	un_dhcp_type;	//value range(0:static 1:dhcp)
#define SDKCMD_SET_NETWORK_DHCP	(SDKCMD_SET_WIRELESS_PARAM + 1)

//param:struct*	T_SDK_IPADDR
#define SDKCMD_SET_STATIC_IPADDR_PARAM	(SDKCMD_SET_NETWORK_DHCP + 1)

//(not support yet)
//param:struct*	T_SDK_DDNS	
#define SDKCMD_SET_DDNS_PARAM	(SDKCMD_SET_STATIC_IPADDR_PARAM + 1)

//param:struct*	T_SDK_DNS
#define SDKCMD_SET_STATIC_DNS_PARAM	(SDKCMD_SET_DDNS_PARAM + 1)

//param:struct*	T_SDK_NTP_CFG_PARAMS
#define SDKCMD_SET_NTP_PARAM	(SDKCMD_SET_STATIC_DNS_PARAM + 1)

//param:struct*	T_SDK_GATEWAY
#define SDKCMD_SET_STATIC_NETGATEWAY_PARAM	(SDKCMD_SET_NTP_PARAM + 1)

//param:struct*	T_SDK_NET_MASK
#define SDKCMD_SET_STATIC_NETMASK_PARAM	(SDKCMD_SET_STATIC_NETGATEWAY_PARAM + 1)


//param:struct*	T_SDK_NET_MAC
#define SDKCMD_SET_MAC_PARAM	(SDKCMD_SET_STATIC_NETMASK_PARAM + 1)

//param:struct*	T_SDK_HOSTNAME
#define SDKCMD_SET_HOSTNAME	(SDKCMD_SET_MAC_PARAM + 1)

//param:struct*	T_SDK_NETWORK_PARAMS
#define SDKCMD_GET_NETWORK_PARAM	(SDKCMD_SET_HOSTNAME + 1)

//param:struct*	T_SDK_NTP_CFG_PARAMS
#define SDKCMD_GET_NTP_PARAM	(SDKCMD_GET_NETWORK_PARAM + 1)

//param:
#define SDKCMD_GET_NVR_IP_ADDR	(SDKCMD_GET_NTP_PARAM + 1)

//param:
#define SDKCMD_SET_NVR_IP_ADDR	(SDKCMD_GET_NVR_IP_ADDR + 1)

//param:
#define SDKCMD_GET_SERVER_INFO	(SDKCMD_SET_NVR_IP_ADDR + 1)


// (not support yet)
//********************************************************************
//**********module type: PTZ(ab)****************************
//********************************************************************
//param: 
#define SDKCMD_SET_PTZ_DEFAULT_PARAMS		0x00ab0001

//param:
#define SDKCMD_GET_PTZ_PARAMS		(SDKCMD_SET_PTZ_DEFAULT_PARAMS + 1)

//param:
#define SDKCMD_SET_PTZ_TURN_LEFT	(SDKCMD_GET_PTZ_PARAMS + 1)

//param:
#define SDKCMD_SET_PTZ_TURN_RIGHT	(SDKCMD_SET_PTZ_TURN_LEFT + 1)

//param:
#define SDKCMD_SET_PTZ_TURN_UP		(SDKCMD_SET_PTZ_TURN_RIGHT + 1)

//param:
#define SDKCMD_SET_PTZ_TURN_DOWN	(SDKCMD_SET_PTZ_TURN_UP + 1)

//param:
#define SDKCMD_SET_PTZ_STOP			(SDKCMD_SET_PTZ_TURN_DOWN + 1)

//param:
#define SDKCMD_SET_PTZ_KEEP_LEFT	(SDKCMD_SET_PTZ_STOP + 1)

//param:
#define SDKCMD_SET_PTZ_KEEP_RIGHT	(SDKCMD_SET_PTZ_KEEP_LEFT + 1)

//param:
#define SDKCMD_SET_PTZ_KEEP_UP		(SDKCMD_SET_PTZ_KEEP_RIGHT + 1)

//param:
#define SDKCMD_SET_PTZ_KEEP_DOWN	(SDKCMD_SET_PTZ_KEEP_UP + 1)


//param: 
#define SDKCMD_SET_CONFIG_URATION_PARAMS	(SDKCMD_SET_PTZ_KEEP_DOWN + 1)

//param: 
#define SDKCMD_SET_ABSOLUTE_MOVE_PARAMS	(SDKCMD_SET_CONFIG_URATION_PARAMS + 1)

//param: 
#define SDKCMD_SET_RELATIVE_MOVE_PARAMS	(SDKCMD_SET_ABSOLUTE_MOVE_PARAMS + 1)

//param: 
#define SDKCMD_SET_CONTINUOUS_MOVE_PARAMS	(SDKCMD_SET_RELATIVE_MOVE_PARAMS + 1)

//param: 
#define SDKCMD_SET_STOP_PARAMS	(SDKCMD_SET_CONTINUOUS_MOVE_PARAMS + 1)

//param: 
#define SDKCMD_SET_PRESET_PARAMS	(SDKCMD_SET_STOP_PARAMS + 1)

//param: 
#define SDKCMD_SET_PRESET_POSITION_PARAMS	(SDKCMD_SET_PRESET_PARAMS + 1)

//param: 
#define SDKCMD_SET_SENDAUXCMD_PARAMS	(SDKCMD_SET_PRESET_POSITION_PARAMS + 1)

//param: 
#define SDKCMD_SET_GOTO_HOME_POSITION_PARAMS	(SDKCMD_SET_SENDAUXCMD_PARAMS + 1)

//param: 
#define SDKCMD_SET_GOTO_PRESET_PARAMS	(SDKCMD_SET_GOTO_HOME_POSITION_PARAMS + 1)

//param: 
#define SDKCMD_SET_REMOVE_PRESET_PARAMS	(SDKCMD_SET_GOTO_PRESET_PARAMS + 1)

//param: 
#define SDKCMD_SET_PRESET_TUOR_PARAMS	(SDKCMD_SET_REMOVE_PRESET_PARAMS + 1)

//param: 
#define SDKCMD_SET_IMAGE_SETTING_PARAMS	(SDKCMD_SET_PRESET_TUOR_PARAMS + 1)

//param:
#define SDKCMD_SET_FOCUS_MOVE_PARAMS	(SDKCMD_SET_IMAGE_SETTING_PARAMS + 1)

//param:
#define SDKCMD_STOP_FOCUS_MOVE_PARAMS	(SDKCMD_SET_FOCUS_MOVE_PARAMS + 1)

//param:
#define SDKCMD_SET_VISOURCE_CFGFOCUS_PARAMS	(SDKCMD_STOP_FOCUS_MOVE_PARAMS + 1)

//param:
#define SDKCMD_SET_REMOVE_ALL_PRESET_PARAMS	(SDKCMD_SET_VISOURCE_CFGFOCUS_PARAMS + 1)

//param:
#define SDKCMD_GET_PTZ_CURRENT_POSI	(SDKCMD_SET_REMOVE_ALL_PRESET_PARAMS + 1)

//param:
#define SDKCMD_SET_PTZ_CURRENT_POSI	(SDKCMD_GET_PTZ_CURRENT_POSI + 1)

//param:
#define SDKCMD_SET_PTZ_AUTO	(SDKCMD_SET_PTZ_CURRENT_POSI + 1)

#define SDKCMD_SET_GOTO_PRESET_POINTER (SDKCMD_SET_PTZ_AUTO + 1)

#define SDKCMD_GET_PTZ_POINTER	(SDKCMD_SET_GOTO_PRESET_POINTER + 1)



//********************************************************************
//**********module type: SDK DEBUG (ff)**************************
//********************************************************************
//param:none 
#define SDKCMD_SET_DEBUG_DEFAULT_PARAMS	0x00ff0001

//param:enum*	E_SDK_DEBUG_LEVEL
#define SDKCMD_SET_DEBUG_LEVEL	(SDKCMD_SET_DEBUG_DEFAULT_PARAMS + 1)



//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


/*******************************************************************************************
* Function name:SDK_Cmd_Impl
* Describe:use this function to communication with the SDK , including get and set configuration 
* Input param:unsigned int uiCmd    :communication command
*			    void* pConfigParam    :Configuration  structure param		
* Output  param:void* pConfigParam   :Configuration  structure param
* return  value: 0success -1:failure
* other details:
* modification date: 2014/07/22  version:V1.0 
* ******************************************************************************************/
int  SDK_Cmd_Impl(unsigned int un_cmd, void* p_config_param);
int Init_21CN_video_ringbuf();


extern void *thread_vavpis_server(void *arg);
extern int TUTK_Check_Vavpis_Server_Thread();

extern int SendPushMessageProcess(int eventType, char *alarm_pic_url);

#if defined (__cplusplus)
}
#endif

#endif

