/*
Description: 
              ...            
*/

#ifndef _SDK_COMMONSTRUCT_H
#define _SDK_COMMONSTRUCT_H

#if defined (__cplusplus)
extern "C" {
#endif
#include "cqueue.h"


//********************************************************************
//********Moudle type: System (a1)*******************************
//********************************************************************
typedef struct
{    
	char a_name[64];
	char a_type[64];
	char a_software_version[64];
	char a_hardware_version[64];
	char a_id[128];
	char a_wifi_mac[64];
	char a_line_mac[64];
}T_SDK_DEVICE_INFO;

typedef struct
{
	unsigned int un_year;	//value range  (1970~2055)
	unsigned int un_month;	//value range (1~12)
	unsigned int un_day;	//value range (1~31)
	unsigned int un_hour;	//value range(0~23)
	unsigned int un_minute;	//value range (0~59)
	unsigned int un_second;	//value range (0~59)
}T_SDK_DEVICE_TIME;

typedef struct
{
	unsigned int un_auto;	    //value range (0:off 1:on)
	unsigned int un_day_night;	//value range(0:day 1:night)
}T_SDK_NIGHT_VISION;


typedef struct
{
	char u8DevCTEI[128];
	char u8DevSN[128];	
	char u8DevKey[128];
}T_SDK_THREE_DevCfg;


typedef struct
{
	unsigned int un_gpio_0;	   
	unsigned int un_gpio_1;		
	unsigned int un_value;	
}T_SDK_LED;

// for amba 
typedef struct
{
	unsigned int un_battery_level;
	unsigned int un_charge_state;	//0:off 1:on
	unsigned int un_battery_state;  //0:full 1:middle 2:low 3.deep low
}T_SDK_BATTERY_INFO;

//电量报警参数结构体
typedef struct 
{	
	unsigned char alarm_switch[4];			//电量告警类型开关,(0:关闭推送，1:开启推送) alarm_type[0]:电量消息推送总开关, alarm_type[1]:满电, alarm_type[2]:低电，alarm_type[3]:电量过低
	unsigned char reserved[16];			
}T_SDK_BATTERY_ALARM_PARAM;


//IPC 接入TUTK平台 鉴权信息结构体
typedef struct
{
	int  index;					//输入参数0 ,1 ,2
	char user_name[64];	   
	char passwd[64];
	char reserved[4];
}T_SDK_DEVICE_AUTHENTICATION_INFO;


//IPC 能力集结构体，主要用于给APP端提供隐藏或显示相关件UI 的依据 
typedef struct
{
	unsigned int  encrypted_ic_flag;	//是否有加密IC 
	unsigned int  pir_flag; 			//是否有PIR传感器，0:无，1:有，下同
	unsigned int  ptz_flag; 			//是否有云台
	unsigned int  mic_flag; 			//是否有咪头				
	unsigned int  speaker_flag; 		//是否有喇叭
	unsigned int  sd_flag;				//是否有SD卡
	unsigned int  temperature_flag; 	//是否有温感探头	
	unsigned int  timezone_flag;		//是否支持同步时区
	unsigned int  night_vison_flag;		//是否支持夜视
	unsigned int  resolution_0_flag;	//主码流分辨率大小 Width:高16位 Height:低16位  Ming@2016.06.14
	unsigned int  resolution_1_flag;	//子码流分辨率大小 Width:高16位 Height:低16位  Ming@2016.06.14
	unsigned int  reserver[8];			
}T_SDK_DEVICE_ABILITY_INFO;

//IPC 能力集结构体，主要用于给APP端提供隐藏或显示相关件UI 的依据 
typedef struct 
{
	unsigned int   c_device_type; //设备类型   900中性版     101彩益     100海尔	    901高世安
	unsigned int   un_resolution_0_flag;	//主码流分辨率大小 Width:高16位 Height:低16位  Ming@2016.06.14
	unsigned int   un_resolution_1_flag;	//子码流	
	unsigned int   un_resolution_2_flag;	//第3路码流
	unsigned char  c_encrypted_ic_flag;	//是否有加密IC 
	unsigned char  c_pir_flag; 			//是否有PIR传感器，0:无，1:有，下同
	unsigned char  c_ptz_flag; 			//是否有云台
	unsigned char  c_mic_flag; 			//是否有咪头				
	unsigned char  c_speaker_flag; 		//是否有喇叭
	unsigned char  c_sd_flag;			//是否有SD卡
	unsigned char  c_temperature_flag; 	//是否有温感探头	
	unsigned char  c_timezone_flag;		//是否支持同步时区
	unsigned char  c_night_vison_flag;	//是否支持夜视
	unsigned char  ethernet_flag;	//是否带网卡0:wifi 1有线2wifi加有线
	unsigned char  c_smart_connect_flag;	//是否支持smart扫描	0代表不支持，1代表7601smart  2代表8188smart	
	unsigned char  c_motion_detection_flag; //是否支持移动侦测	
	unsigned char  c_record_duration_flag;
}T_SDK_DEVICE_ABILITY_INFO1;	

//IPC 能力集结构体，主要用于给APP端提供隐藏或显示相关件UI 的依据 
typedef struct 
{
	unsigned int   c_device_type; //设备类型   900中性版     101彩益     100海尔	    901高世安
	unsigned int   un_resolution_0_flag;	//主码流分辨率大小 Width:高16位 Height:低16位  Ming@2016.06.14
	unsigned int   un_resolution_1_flag;	//子码流	
	unsigned int   un_resolution_2_flag;	//第3路码流
	unsigned char  c_encrypted_ic_flag;	//是否有加密IC 
	unsigned char  c_pir_flag; 			//是否有PIR传感器，0:无，1:有，下同
	unsigned char  c_ptz_flag; 			//是否有云台
	unsigned char  c_mic_flag; 			//是否有咪头	
	
	unsigned char  c_speaker_flag; 		//是否有喇叭
	unsigned char  c_sd_flag;			//是否有SD卡
	unsigned char  c_temperature_flag; 	//是否有温感探头	
	unsigned char  c_timezone_flag;		//是否支持同步时区
	
	unsigned char  c_night_vison_flag;	//是否支持夜视	
	unsigned char  ethernet_flag;	//是否带网卡0:wifi 1有线2wifi加有线
	unsigned char  c_smart_connect_flag;	/* 是否支持smart扫描	
												0	代表不支持，
												1	代表7601smart  
												2	代表8188smart	
												3	代表ap6212 
												9	不支持二维码扫描
												10	只支持二维码扫描
												11代表二维码扫描+7601smart
												12代表二维码扫描+8188smart
												13代表二维码扫描+ap6212smart
										*/
	unsigned char  c_motion_detection_flag; //是否支持移动侦测
	
	unsigned char  c_record_duration_flag; // 是否有设置录像录像时长
	unsigned char  c_light_flag; // 是否有设置照明灯开关
	unsigned char  c_audio_alarm_detection_flag; //是否支持声音侦测报警
	unsigned char  align1;	 // 是否支持摇篮曲
	/*
	reserver_default_off[0]	 // 是否带电池 0. 无 ，1. 有
	reserver_default_off[1]	 // 是否支持WIFI远程唤醒 0.不支持， 1支持
	reserver_default_off[2]  // 是否支持状态灯开关 0.不支持， 1支持
	
	reserver_default_off[3]  // 是否支持摄像头开关 0.不支持， 1支持
	reserver_default_off[4]  // 是否支持摄像头麦克风开关 0.不支持， 1支持
	reserver_default_off[5]  // 是否支持云存储 0.不支持， 1支持
	reserver_default_off[6]	 // 是否支持打开流鉴权

	reserver_default_off[7]	 // 是否支持Alexa_Voice_Service
	reserver_default_off[8]	 // 是否支持Alexa_Skills_Kit
	*/
	unsigned char  reserver_default_off[32]; // 预留能力集默认关闭
	unsigned char  reserver_default_on[32]; // 预留能力集默认开启
}T_SDK_DEVICE_ABILITY_INFO2;	


typedef struct
{
	unsigned char  c_record_duration_flag;  //是否支持录像时长设定,
	unsigned char  c_alarm_audio_play_set_flag;   //是否支持报警铃音定制,  
	
	unsigned char  c_audio_alarm_detection_flag;	//是否支持声音报警（玻璃碎或者婴儿哭）
	unsigned char  c_temperature_detection_flag;	//是否支持测温报警,
	unsigned char  c_loop_record_flag;	//是否支持循环录像开关,
	unsigned char  c_manual_record_flag;	//是否支持手动录像, 
	unsigned char  c_ptz_auto_cruise_flag;	//是否支持云台自动循航路线控制
	unsigned char  c_ptz_preset_flag;	//是否支持云台预置点设置
	unsigned char  c_humidity_detection_flag;	//是否支持湿度传感器
	unsigned char  c_time_correct_flag;	//是否支持时间校准,
	unsigned char  c_WDR_flag;	//是否支持宽动态,
	unsigned char  c_key_for_all_alarm_flag;	//是否支持一键布防,
	unsigned char  c_share2friends_flag;	//是否支持好友分享,
	unsigned char  c_bitrat_auto_correct_flag;	//是否支持码流自适应
	unsigned char  c_wifi_channel_flag;	//是否可以改wifi信道
	unsigned char  c_OSD_switch_flag;	//是否支持osd开关
	unsigned char  c_OSD_string_add_flag;	//是否支持osd字符串添加
	unsigned char  c_bitrate_change_flag;	//是否支持码流切换
	unsigned char  c_wire_flag;	//是否支持有线
	unsigned char  c_wireless_flag;	//是否支持无线
	unsigned char  c_normal_battery_flag;	//是否带电池，电量显示
	unsigned char  c_solar_battery_flag;	//是否带太阳能电池，显示充电放点状态
	unsigned char  c_3D_denoise_flag;	//是否支持3D降噪
	unsigned char  c_hue_adjust_flag;	//是否支持色调调试


	unsigned char  c_saturation_debuggable_flag;	//是否支持饱和度调试
	unsigned char  c_brightness_debuggable_flag;	//是否支持亮度调试
	unsigned char  c_acutance_debuggable_flag;	//是否支持锐度调试
	unsigned char  c_have_anti_shaking_flag;	//是否支持防抖功能(Anti-Shaking/STABILIZER MODE)
	unsigned char  c_have_intelligent_tracking_flag;	//是否支持智能跟踪
	unsigned char  c_have_ota_upgrade_flag;	//是否支持网络自动升级(Over-the-Air)
	unsigned char  c_audio_encoder_selectable_flag;	//是否支持音频编码格式切换
	unsigned char  c_have_h265_flag;	//是否支持H265
	unsigned char  c_have_cloud_storage_flag;	//是否支持云存储
	unsigned char  c_auto_zoom_flag;	//是否支持自动变焦
	unsigned char  c_auto_diaphragm_flag;	//是否支持自动光圈
	unsigned char  c_motion_detection_alarm_zone_flag;	//是否支持移动侦测报警区域设置
	unsigned char  c_planning_recording_flag;	//是否支持计划录像
	unsigned char  c_privacy_masking_flag;	//是否支持隐私遮挡
	unsigned char  c_cross_the_line_alarm_flag;	//是否支持越线报警
	unsigned char  c_smoking_detection_flag;	//是否支持烟感
	unsigned char  c_door_contact_flag;	//是否支持门磁
	unsigned char  c_license_plate_recognition_flag;	//是否支持车牌识别
	unsigned char  c_digital_ptz_flag;	//是否支持数字云台
	unsigned char  c_cross_line_alram_flag;	//是否支持越线报警
	unsigned char  c_have_display_screen_flag;	//是否带屏
	unsigned char  c_wet_alarm_flag;	//是否支持浸湿报警
	unsigned char  c_have_bluetooth_flag;	//是否支持蓝牙
	unsigned char  c_intelligent_light_flag;	//是否支持智能灯开关
	unsigned char  c_door_curtain_flag;	//是否支持门帘控制


	unsigned char  c_air_cond_ctrl_flag;	//是否支持空调控制
	unsigned char  c_washing_ctrl_flag;	//是否支持洗衣机控制
	unsigned char  c_refrigerator_ctrl_flag;	//是否支持冰箱控制
	unsigned char  c_tv_ctrl_flag;	//是否支持电视机控制
	unsigned char  c_rice_cooker_ctrl_flag;	//是否支持电饭煲控制
	unsigned char  c_smart_plug_ctrl_flag;	//是否支持智能插座控制
	unsigned char  c_pm25_induction_flag;	//是否支持pm2.5感应
	unsigned char  c_heartbeat_detection_flag;	//是否支持心跳侦测
	unsigned char  c_breathe_detection_flag;	//是否支持呼吸侦测
	unsigned char  c_bp_detection_flag;	//是否支持血压侦测
	unsigned char  c_Blood_sugar_detection_flag;	//是否支持血糖侦测
	unsigned char  c_4g_flag;	//是否支持4G
	unsigned char  c_3g_flag;	//是否支持3G
	unsigned char  c_GPS_locating_flag;	//是否支持GPS定位
	unsigned char  c_wechart_pre_flag;	//是否支持微信查看
	unsigned char  c_qq_pre_flag;	//是否支持qq查看
	unsigned char  c_web_pre_flag;	//是否支持web查看，设置
	unsigned char  c_thief_alarm_flag;	//是否支持防盗报警
	unsigned char  c_intelligent_learn_flag;	//是否支持自主学习
	unsigned char  c_face_regi_flag;	//是否支持人脸识别
	unsigned char  c_sub_regi_flag;	//是否支持特殊物体识别，比如野狗
	unsigned char  c_ap_model_flag;	//是否支持ap模式
	unsigned char  c_money_check_flag;	//是否支持人民币防伪检测
	unsigned char  c_people_count_flag;	//是否支持人流统计
	unsigned char  c_demisting_func_flag;;	//是否支持去雾功能


	unsigned char  c_gesture_recognition_flag;	//是否支持手势识别
	unsigned char  c_speech_recognition_flag;	//是否支持智能语音识别
	unsigned char  c_wind_speed_flag;	//是否支持风速测速
	unsigned char  c_air_pressure_display_flag;	//是否支持气压显示
	unsigned char  c_seismic_survey_flag;	//是否支持地震勘测
	unsigned char  c_seafloor_depth_shows_flag;	//是否支持海底深度显示
	unsigned char  c_gas_content_test_flag;	//是否支持瓦斯含量测试
	unsigned char  c_Intensity_of_ultraviolet_detectiont_flag;	//是否支持紫外线强度侦测
	unsigned char  c_gyroscope_flag;	//是否支持陀螺仪
	unsigned char  c_data_encryption_flag;	//是否支持数据传输加密
	unsigned char  c_remote_control_flag;	//是否带遥控器
	unsigned char  c_wheel_mobile_capabilities_flag;	//是否支持轮子移动功能
	unsigned char  c_flight_flag ;	//是否支持飞行功能
	unsigned char  c_Laser_tease_cats_tease_dogs_flag;	//是否支持激光逗猫逗狗
	unsigned char  c_video_conference_flag;	//是否支持视频会议
	unsigned char  c_projection_flag;	//是否支持投影功能
	unsigned char  c_external_speaker_flag;	//是否支持外接音箱
	unsigned char  c_character_recognition_flag;	//是否支持文字识别
	unsigned char  c_open_parking_brake_machine_flag;	//是否支持停车场闸机开启功能
	unsigned char  c_probe_rotation_flag;	//是否支持探头转动
	unsigned char  c_dual_cameras_flag;	//是否支持双摄像头
	unsigned char  c_electronic_payment_flag;	//是否支持电子支付
	unsigned char  c_fingerprint_identification_flag;	//是否支持指纹识别
	unsigned char  c_Iris_recognition_flag;	//是否支持虹膜识别
	unsigned char  c_serial_snapshot_flag;	//是否支持连续类似一个月连续间隔拍图片最后组成动画的功能
	unsigned char  c_perspective_flag ;	//是否支持透视功能
}T_SDK_DEVICE_ABILITY_INFO100;


typedef struct 
{
    unsigned int	un_trigger_time;	//触发亮灯时间 pir / motion
    unsigned int	un_manual_time;	//手动开灯亮灯时间
	int	n_reserve;
}T_SDK_DEVICE_LIGHT_DURATION;

typedef struct 
{
    unsigned int	un_on_hour;	
    unsigned int	un_on_min;	
    unsigned int	un_off_hour;	
    unsigned int	un_off_min;	
	unsigned int 	un_wday_switch;	//按 0~6位表示，第0位表示星期天，第1位表示星期一 0->关闭 1->打开
	int	n_reserve;
}T_SDK_DEVICE_LIGHT_TIMING;//定时开灯时间点，开关

//********************************************************************
//******** module tpye: video (a2)*******************************
//********************************************************************
typedef enum  _E_VIDEO_ENCODER_TYPE
{
	E_VENC_NONE	= 0x00,
	E_VENC_H264	= 0x01,
	E_VENC_MPEG4	= 0x02,
	E_VENC_MJPEG	= 0x03,
	E_VENC_JPEG	= 0x04,
}E_SDK_VIDEO_ENCODER_TYPE;

typedef struct 
{
    unsigned int	un_encode_channel_id;
    unsigned char*	uncp_data;
    unsigned int	un_data_len;
	unsigned int	un_frame_type;	//value range (1:I frame 0:P frame)
	unsigned int	un_steam_type;	//1:means video,2:means audio
	unsigned int	un_timestamp;
    unsigned int 	un_sec;        /*usecond of frame*/
	unsigned int	un_sequence;
	int	n_reserve;
}T_SDK_STREAM_CALLBACK_PARAM;

typedef int (*F_SDK_Stream_Callback)(T_SDK_STREAM_CALLBACK_PARAM *pt_encode_data);

typedef struct 
{
	F_SDK_Stream_Callback	fp_callback;
	unsigned int un_video_switch;
	unsigned int un_audio_switch;
	unsigned int un_video_channel;
	unsigned int un_audio_channel;	
	int	n_reserve;	
}T_CALLBACK_INFO;

typedef struct 
{
	T_CALLBACK_INFO	ta_callback_info[4];		
	int	n_reserve;	
}T_SDK_STREAM_REGISTER_CALLBACK;

typedef struct 
{
	unsigned int	un_encode_channel_id;
	unsigned int	un_force_num;	
}T_SDK_FORCE_I_FARME;

typedef struct 
{
    unsigned int	un_encode_channel_id;     
    unsigned int	un_switch;	//value range (0:off 1:on)
}T_SDK_VIDEO_ENCODE_SWITCH;

typedef struct 
{
    unsigned int	un_encode_channel_id;  
    E_SDK_VIDEO_ENCODER_TYPE	e_type;		
}T_SDK_VIDEO_ENCODE_TYPE;

typedef struct 
{
	unsigned int	un_encode_channel_id;        
	unsigned int	un_width;				    
	unsigned int	un_height;					
}T_SDK_VIDEO_ENCODE_RESOLUTION;

typedef struct 
{
    unsigned int	un_encode_channel_id;              
    unsigned int	un_interval;			
}T_SDK_VIDEO_ENCODE_I_FRAME_INTERVAL;

typedef struct 
{
	unsigned int	un_encode_channel_id; 
	unsigned int	un_bitrate_type;	//value range (0: CBR; 1: VBR; 2: CBR keep quality; 3: VBR keep quality)
	unsigned int	un_average_bitrate;
	unsigned int	un_max_bitrate;
	unsigned int	un_min_bitrate;	
}T_SDK_VIDEO_ENCODE_BITRATE;

typedef struct 
{
	unsigned int	un_encode_channel_id;
	unsigned int	un_switch;	//value range (0:off 1:on)
}T_SDK_LOWER_BITRATE_CONTORL;	//only for  Ambarella

typedef struct 
{
	unsigned int	un_encode_channel_id;  
	unsigned int	un_framerate;	     
}T_SDK_VIDEO_ENCODE_FRAMERATE;

typedef struct 
{
	unsigned int	un_encode_channel_id; 
	unsigned int	un_quality;	//value range(0-5)
}T_SDK_VIDEO_ENCODE_QUALITY;

typedef struct 
{
	unsigned int	un_encode_channel_id;	
	unsigned int	un_profile;	//value range of Encode level ( 0: baseline; 1:MP; 2:HP)   HiSilicon not permitted set it
}T_SDK_VIDEO_ENCODE_LEVEL;

typedef struct 
{
	unsigned int	un_encode_channel_id;  				
	unsigned int	un_I_frame_max_Qp;                   
	unsigned int	un_I_frame_min_Qp;                   
	unsigned int	un_P_frame_max_Qp;                   
	unsigned int	un_P_frame_min_Qp;
	unsigned int	un_I_frame_Weight_Qp; //goke
	unsigned int	un_P_frame_Weight_Qp; //goke
}T_SDK_VIDEO_ENCODE_QP;

typedef struct 
{
	unsigned int	un_encode_channel_id;	//(input Param)
	unsigned int	un_encode_switch;	//value range(0:off 1:on)
	E_SDK_VIDEO_ENCODER_TYPE	e_encode_type;			  
	unsigned int	un_width;					
	unsigned int	un_height;					
	unsigned int	un_I_frame_interval;			  
	T_SDK_VIDEO_ENCODE_BITRATE	t_bitrate;					   
	unsigned int	un_framerate;					
	T_SDK_LOWER_BITRATE_CONTORL	t_lower_bitrate_control;	//only for  Ambarella
	unsigned int	un_quality;	//value range(0-5)
	unsigned int	un_profile;	//value range of Encode level ( 0: baseline; 1:MP; 2:HP)   HiSilicon not permitted set it
	T_SDK_VIDEO_ENCODE_QP t_QP;              
	unsigned int	un_mirro_type;	//value range 0:none,1:horizontal,2:vertical,3:horizonta+vertical
} T_SDK_VIDEO_ENCODE_PARAM;



//********************************************************************
//******** module tpye: Audio (a3)*******************************
//********************************************************************
typedef enum  _E_AUDIO_ENCODE_TYPE
{
	E_AENC_NONE	= 0x0,
	E_AENC_G726	= 0x01,
	E_AENC_G722	= 0x02,
	E_AENC_G711A	= 0x03,
	E_AENC_ADPCM	= 0x04,
	E_AENC_MP3	= 0x05,
	E_AENC_PCM	= 0x06,
	E_AENC_G711U	= 0x07,
	E_AENC_AACLC	= 0x08,
	E_AENC_AMRNB	= 0x09,
	E_AENC_PTAAC 	= 0x25,
}E_SDK_AUDIO_ENCODE_TYPE;

typedef struct 
{
	unsigned int	un_encode_switch;                     
	unsigned int	un_sound_mode;	//value range of soud_mode(0:single 1:stereo)
	unsigned int	un_mic_line_input;	//value range(0: mic input 1:line input)	
	E_SDK_AUDIO_ENCODE_TYPE	e_encode_type;					     
	unsigned int	un_audio_echo_canell_switch;	//(1:on 0:off)	
	unsigned int	un_bitrate;			            
	unsigned int	un_sample_rate;	                
	unsigned int	un_input_volume;	                     
	unsigned int	un_output_volume;                     
} T_SDK_AUDIO_ENCODE_PARAM;

typedef struct 
{
	unsigned char*	cp_data;			
	unsigned int	un_data_len;  
} T_SDK_INTERCOM_DATA;



//********************************************************************
//****** module tpye: sensor (a4)******************************
//********************************************************************	
typedef struct 
{
	unsigned int	un_brightness;
	unsigned int	un_contrast; 
	unsigned int	un_hue; 
	unsigned int	un_saturation; 
	unsigned int	una_sharp[4];	//sharp[0] for Ambarella
}T_SDK_SENSOR_PARAM;

typedef struct 
{
	unsigned int	una_sharp[4];	 //value range(0-100)
}T_SDK_SENSOR_SHARP;

#if 0
typedef struct
{
    unsigned int	un_encode_AE_mode;
    unsigned int	un_ExpTimeMax;
    unsigned int	un_ExpTimeMin;
    unsigned int	un_DGainMax;
    unsigned int	un_DGainMin;
    unsigned int	un_AGainMax;
    unsigned int	un_AGainMin;
    unsigned int	un_ISPDGainMax;
	unsigned int	un_SystemGainMax;
	unsigned int	un_GainThreshold;
	unsigned char	uc_ExpStep;
	short	s_ExpTolerance;
	unsigned char	uc_ExpCompensation;
	unsigned short	us_EVBias;
	unsigned int	un_AEStrategyMode;
	unsigned char	uc_MaxHistOffset;
	unsigned short	us_HistRatioSlope;
	unsigned int	un_FrameEndUpdateMode;
	unsigned int	un_ByPassAE;
}T_SDK_SENSOR_AUTO_EXPOSURE;
#else
typedef struct {
    unsigned int        speed;
    unsigned int        shutterTimeMin;
    unsigned int        shutterTimeMax;
    unsigned int        gainMax;
    unsigned int        gainMin;
    unsigned int        tagetRatio;
} T_SDK_SENSOR_AUTO_EXPOSURE;
#endif

typedef struct
{
    unsigned int	un_dain;
    unsigned int	un_value;
}T_SDK_SENSOR_2D;

typedef struct
{
    unsigned int	un_space_denoise;
    unsigned int	un_time_denoise;
    unsigned int	un_chroma_range;
}T_SDK_SENSOR_3D;




//********************************************************************
//********** module tpye: alarm (a5)******************************
//********************************************************************
typedef enum 
{
	E_UNKNOWN ,
	E_VIDEO_MOTION,
	E_PIR_MOTION,	//Passive Infrared Radiation  motion alarm
	E_PIR_VIDEO_MOTION, 
	E_AUDIO_MOTION, 
	E_IO_ALARM,
	E_LOW_TEMP_ALARM, //6
	E_HIGH_TEMP_ALARM,
	E_LOW_HUM_ALARM,
	E_HIGH_HUM_ALARM,
	E_LOW_WBGT_ALARM,
	E_HIGH_WBGT_ALARM, // 11
	E_CALLING,
	E_KEY_LONG_PRESS,
	E_KEY_SHORT_PRESS,
	E_KEY_ORDINARY_PRESS,
	E_WIFI_CONNECTED,
	E_WIFI_DISCONNECTED,
	E_SCAN_SUCCEED,
	E_RECORD_FINISHED,
	E_BODY_DETECT,
	E_QRCode_String,
	E_LINE_CONNECTION_MODE,
	E_WIFI_CONNECTION_MODE
}E_SDK_ALARM_TYPE;

typedef struct 
{
    E_SDK_ALARM_TYPE	e_alarm_type;
	char alarm_pic_url[256];
	char alarm_record_path[256];
	char QrString[128];
}T_SDK_ALARM_CALLBACK_PARAM;

typedef int	(*F_SDK_Alarm_Callback)(T_SDK_ALARM_CALLBACK_PARAM *pt_alarm);

typedef struct 
{
	F_SDK_Alarm_Callback	fp_callbak;	
	int	n_reserve;	
}T_SDK_ALARM_REGISTER_CALLBACK;

//********************************************************************
//********** module tpye: motion detection **************************
//********************************************************************

typedef struct {
   unsigned int	un_start_x;
   unsigned int	un_start_y;
   unsigned int	un_width;
   unsigned int	un_height;
   unsigned int	c_switch;
   unsigned int	c_sensitivity;		 //value range(1 ~100)，移动侦测等级阀值,值越小,灵敏度越高。1(max) ~ 100(min):  (关: 100,  低: 90  中: 60  高: 30)
   short	s_threshold;	 //when below threshold, not considered as motion; else, trigger motion   
}T_SDK_VIDEO_MOTION_SINGEL;

typedef enum {
  AM_MD_ALGO_MSE	= (0x01 << 0),
  AM_MD_ALGO_MOG2	= (0x01 << 1),
  AM_MD_ALGO_HYBRID	= AM_MD_ALGO_MSE | AM_MD_ALGO_MOG2,
  AM_MD_ALGO_NUM	= 2,
} E_SDK_VIDEO_MOTION_ALGO;

typedef struct 
{
	E_SDK_VIDEO_MOTION_ALGO e_algo_type;	//AM_MD_ALGO_MSE or AM_MD_ALGO_MOG2
	T_SDK_VIDEO_MOTION_SINGEL t_video_motion_rect; //手动划分时只划分一个区域坐标
	unsigned int un_mode;	// 手动划分坐标0 or 自动多分屏坐标1
	unsigned int un_submode; //多分屏下1x1=0, 2x2=1, 3x3=2, 4x4=3
	unsigned int un_enable;//根据多分屏模式下选择区域是否使能最多4x4=16;
}T_SDK_VIDEO_MOTION_ALARM;	 

//********************************************************************
typedef struct 
{
	unsigned int	un_switch;
	unsigned int	un_sensitivity;  //PIR侦测等级(1-10)，值越小，灵敏度越高  (低: 8, 中: 5, 高: 2)
}T_SDK_PIR_ALARM;         //(only for HiSilicon)

typedef struct 
{
	unsigned int	un_switch;
	unsigned int	un_sensitivity;
}T_SDK_DOORBELL_ALARM;    //(only for HiSilicon)

typedef struct 
{
	unsigned int	un_switch;
	unsigned int	un_sensitivity;
}T_SDK_AUDIO_ALARM;     

typedef struct 
{
	unsigned int	un_switch;
	unsigned int	un_sensitivity;
}T_SDK_SHELTER_ALARM;	//(not support yet)

typedef struct 
{
	unsigned int	un_switch;
	unsigned int	un_sensitivity;
}T_SDK_IO_ALARM;


//IPC一键布防配置结构体，暂时保留
typedef struct 
{
	unsigned int	un_switch;
	unsigned int	reserved[3];
}T_SDK_ONEKEY_ALARM_CONTROL;


typedef struct 
{
	T_SDK_VIDEO_MOTION_ALARM	t_motion;
	T_SDK_PIR_ALARM	t_PRI;	//(only for HiSilicon)
    T_SDK_DOORBELL_ALARM	t_doorbell;	//(only for HiSilicon)
	T_SDK_AUDIO_ALARM	t_audio;
	T_SDK_SHELTER_ALARM	t_shelter;	//(not support yet)
    T_SDK_IO_ALARM	t_IO;
}T_SDK_ALARM_PARAM;


//IPC报警铃声配置结构体，暂时保留
typedef struct 
{
	unsigned int	alarm_ring_no;
	unsigned int	reserved[3];
}T_SDK_ALARM_RING_PARAM;


//温度报警参数结构体
typedef struct 
{	
	unsigned int alarm_enale;			//上下限温度报警开关， 0:上下限全部关闭， 1:上限开启，下限关闭，2:上限关闭，下限开启，3:上下限全部开启
	unsigned int temperature_type;		//温度表示类型， 0:表示摄氏温度.C， 1；表示华氏温度.F
	double curr_temperature_value;		//当前温度
	double max_alarm_value;				//上限报警温度
	double min_alarm_value;				//下限报警温度
	unsigned char reserved[16];			//
}T_SDK_TEMPERATURE_ALARM_PARAM;


//********************************************************************
//********** module tpye: OSD on-screen display (a6)********************************
//********************************************************************
typedef struct 
{
	unsigned int	un_show;	//value range(1:display 0:close)
	unsigned int	un_color;	//value range(1:Black 2:Yelloow 3:Red 4:Blue 5:White Other default red)
	unsigned int	un_x_coordinate;					
	unsigned int	un_y_coordinate;
}T_SDK_SINGLE_OSD_PARAM;

typedef struct 
{
	unsigned int	un_encode_channel_id;	//(Input Param)
	char	a_title1[64];          
	char	a_title2[64];           
	T_SDK_SINGLE_OSD_PARAM	t_time;
	T_SDK_SINGLE_OSD_PARAM	t_title1;
	T_SDK_SINGLE_OSD_PARAM	t_title2;
}T_SDK_ALL_OSD_PARAM;

typedef struct 
{
	unsigned int	un_encode_channel_id;    
	unsigned int	un_show_Time;	//value range(1:display 0:close)
	unsigned int	un_show_Date;	//value range(1:display 0:close)
	unsigned int	un_show_Title1;	//value range(1:display 0:close)
	unsigned int	un_show_Title2;	//value range(1:display 0:close)
}T_SDK_OSD_SWITCH;

typedef struct 
{
	unsigned int	un_encode_channel_id;      
	unsigned int	un_color;	//goke :value range(// 0:Black, 1:Red, 2:Blue, 3:Green, 4:Yellow, 5:Magenta, 6:Cyan, 7:White)
}T_SDK_OSD_COLOR;

typedef struct 
{
	unsigned int	un_encode_channel_id; 
	unsigned int	un_x_time;   
	unsigned int	un_y_time;
	unsigned int	un_x_title1;   
	unsigned int	un_y_title1;
    unsigned int	un_x_title2;   
	unsigned int	un_y_title2;
}T_SDK_OSD_POS;

typedef struct 
{
	unsigned int	un_encode_channel_id;  
	char	a_title1[64];  
	char	a_title2[64]; 
}T_SDK_OSD_TITLE;



//********************************************************************
//********** module tpye: Record (a7)******************************
//********************************************************************
typedef cqueue P_QUEUE;	
typedef enum 
{
    SDK_UNKNOWN_RECORD = 0,
    SDK_EVENT_RECORD,
    SDK_MANUAL_RECORD,
}E_SDK_RECORD_TYPE;

typedef struct 
{
	unsigned int	un_switch;
	unsigned int	un_audio_switch;
	unsigned int 	un_manual_record_switch;	//手动录像开关
	unsigned int	un_encode_channel_id;   
	unsigned int	un_file_duration; 
	unsigned int	un_loop;	//value range of auto circulate record(0:on 1:off)
	unsigned int	un_file_type;	//record file type value range (0:ts 1:mp4 2:flv)
}T_SDK_RECORD_PARAM;

typedef struct 
{
	unsigned int	un_lock;
	char	a_file_name[64]; 
}T_SDK_RECORD_LOCK_FILE;

typedef struct 
{
	char	a_month[16];	//example:"201401"  (input Param. 2014 means year,01 means month)
	char*	cp_list;	//example:"201401013|201401021|201401122|" (Output Param. 2014 means year , in 201401013 01 means month ,3 meas how many files exist) 
	unsigned int	un_list_len;	
}T_SDK_RECORD_MONTH_LIST;

typedef struct 
{
	char	a_day[16];				//example:"20140112"(input Param. 2014 means year,01 means month,12 mens the day)
	unsigned int  file_type;		//请求文件类型 (视频: 0 , 图片: 1)
	unsigned int  file_counts;		//文件数
									/*example:"201401121132231bc0120.mp4|201401121133231bc0120.mp4|"
									(Output Param. in 201401121132231bc0120z.ts 2014 means year,01 means month ,
									12 meas the day,11 means hour, 32 means minute, 23 means second, 
									1 means the file can not remove when auto circulate record is open,
									b means record type (value frome enum RECORD_TYPE + 'a')
									c means alarm type (value frome enum E_SDK_ALARM_TYPE + 'a')) 
									012 means record time 
									.mp4 meas record file type*/
	char*	cp_list;						   
	unsigned int	un_list_len;	
}T_SDK_RECORD_DAY_LIST;

typedef struct 
{
	char	filename[32];			//example:"201401121132231bc0120.mp4"
	unsigned int  direction;		//查找方向,0:向上(向左); 1:向下(向右);
	unsigned int  file_counts;		//需要查找的文件数
	unsigned int  Counts;			//实际文件数
									/*example:"201401121132231bc0120.mp4|201401121133231bc0120.mp4|"
									(Output Param. in 201401121132231bc0120z.ts 2014 means year,01 means month ,
									12 meas the day,11 means hour, 32 means minute, 23 means second, 
									1 means the file can not remove when auto circulate record is open,
									b means record type (value frome enum RECORD_TYPE + 'a')
									c means alarm type (value frome enum E_SDK_ALARM_TYPE + 'a')) 
									012 means record time 
									.mp4 meas record file type*/
	char*	cp_list;						   
	unsigned int	un_list_len;	
}T_SDK_RECORD_ASSIGNTIME_DAY_LIST;

typedef struct 
{
	char	a_file_name[32]; 		 //example:"201401121132231bc0120.mp4"(input param)
    char	a_path[128];  //example:"/sdcard/ipc/201401/12/201401121132231bc0120.mp4"
}T_SDK_RECORD_FILE_PATH;
typedef struct
{
	unsigned int year;
	unsigned int month;
	unsigned int day;
}T_SDK_REC_DAY_NODE;

typedef struct
{
	unsigned int 	count;
	P_QUEUE 	 	info;
}T_SDK_REC_DAY_LIST;


typedef struct
{
	unsigned int start;
	unsigned int type;
	unsigned int duration;
}T_SDK_REC_EVENT_NODE;

typedef struct
{
	char					root[128];
	int						count;
	T_SDK_REC_EVENT_NODE*	info;
}T_SDK_REC_EVENT_LIST;

typedef struct
{
	unsigned int			time;
	T_SDK_REC_EVENT_LIST	list;
}T_SDK_REC_DAY_EVENT;

typedef struct
{
	unsigned int start;
	char		 name[256];
}T_SDK_REC_SPLIT_INFO;

typedef struct
{
	unsigned int			time;
	T_SDK_REC_SPLIT_INFO	info;
}T_SDK_REC_SPLIT;

typedef struct
{
	char	name[32];
}T_SDK_REC_SUB_NODE;

typedef struct
{
	char				root[128];
	int					count;
	T_SDK_REC_SUB_NODE*	info;
}T_SDK_REC_SUB_LIST;

typedef enum
{
	E_REC_SPLIT_FIND_TYPE_EXACT,
	E_REC_SPLIT_FIND_TYPE_NEXT,
	E_REC_SPLIT_FIND_TYPE_FFLUSH_NEXT,
}E_REC_SPLIT_FIND_TYPE;

typedef struct
{
	unsigned int			start;
	char 					file_name[128];
}T_SDK_REC_SPLIT_INFO_EX;

typedef struct
{		
	unsigned int		 	time;
	E_REC_SPLIT_FIND_TYPE 	type;
	
	T_SDK_REC_EVENT_LIST	event;
	T_SDK_REC_SUB_LIST		split;
	T_SDK_REC_SPLIT_INFO_EX split_info;		//单个分片的信息
	int 					event_index; 
	int 					splite_index;
}T_SDK_REC_SPLIT_BUFFERRING;

typedef struct
{
	unsigned int a_total_size;	//总容量
	unsigned int a_used_size;	//已用容量
	unsigned int a_free_size;	//未用容量
	unsigned int a_reserve[2];	//保留
}T_SDK_STORAGE_INFO;

typedef struct 
{
 	unsigned int StartTimeStamp;	//起始时间 
	unsigned int EndTimeStamp;		//结束时间
	unsigned int AlarmType;			//告警类型
}T_SDK_RECORD_LIST;

typedef struct 
{
	char* lastFd;						//上一次的索引的文件描述符
	unsigned int start_time;
	unsigned int end_time;			//jie
	T_SDK_RECORD_LIST record_list;
}T_SDK_GET_RECORD_LIST;


typedef struct 
{
	unsigned int reference_time;	//输入参数刷新时间
	char* lastFd;
	T_SDK_RECORD_LIST record_list;	//
}T_SDK_REFRESH_RECORD_LIST;

typedef struct 
{
	unsigned int oldest_time;	//获取索引最早的时间
}T_SDK_GET_RECORD_LIST_OLDEST_TIME;



//********************************************************************
//********** module tpye: snapshot (a8)****************************
//********************************************************************
typedef struct 
{
	unsigned int	un_switch;			
	char	a_save_file_path[128];		
}T_SDK_SNAPSHOT_PARAM;
typedef struct
{    
	char pic_path[128];
}T_SDK_PIC_PATH;
typedef struct
{    
	unsigned int	un_switch;			
}T_SDK_PIC_SWITCH;
//********************************************************************
//********** module tpye: upgrade (a9)****************************
//********************************************************************
typedef struct
{
    unsigned int	un_mode;     		//value range(0:Download but no upgrade 1:upgrade but no upgrade 2:Dowload and upgrade)
    char	a_package_name[128]; 
    char	a_server_path[128]; 	
}T_SDK_UPGRADE_PARAMS;

typedef struct
{
	char	a_ipaddr[128];	//ip address
	unsigned int	un_port;	//ip port
	unsigned int result;	//0 -> create upgrade thread success; 1->malloc failed;  2 -> create thread failed; 3 -> is upgrading
	unsigned int remoteFlag;	//是否是远程升级	 0:局域网升级;	1:服务器升级;
	unsigned int cancelFlag;	//取消升级标志默认为0不取消1时取消升级
}T_SDK_UPGRADE_BYSELF_PARAMS;

typedef struct
{
	unsigned int un_mode;				//0 -> app;	1 -> fw;	2 -> kernel;	3 -> uboot
	char a_current_ver[32];				//current version
	char a_local_path[256];				//upgrade package path
	long un_FileSize;
}T_SDK_UPGRADE_BYLOCAL_PARAMS;



//********************************************************************
//********** module tpye: network (aa)****************************
//********************************************************************
typedef enum _E_SDK_WIFI_MODE
{
	E_SDK_WIFI_AP_MODE = 0x00,
	E_SDK_WIFI_CLIENT_MODE,
	E_SDK_WIFI_AP_CLIENT_MODE,
	E_SDK_WIFI_WPS_MODE,
	E_SDK_WIFI_MODE_NUM
}E_SDK_WIFI_MODE;

typedef enum _E_SDK_NET_STATUS
{
	E_SDK_DISCONNECT,  
	E_SDK_CONNECT,  
	E_SDK_SETTING,  
	E_SDK_CONNECTING, 
}E_SDK_NET_STATUS;


typedef struct
{
	char	a_SSID[64];
	unsigned int  un_signal_level;
	unsigned int  un_ssid_flag;
}T_SDK_SEARCH_SSID_INFO;

typedef struct
{
	unsigned int	un_ssid_num;
	T_SDK_SEARCH_SSID_INFO	t_info[30];
}T_SDK_SEARCH_SSID_NEARBY;

/*
typedef struct
{
	E_SDK_WIFI_MODE	e_wifi_mode;
	E_SDK_NET_STATUS	e_wifi_connect_status;	
	char	a_SSID[64];
	char	a_passwd[64];
	unsigned int	un_encrypt;
}T_SDK_WIRELESS_PARAMS;
*/
typedef struct
{
	E_SDK_WIFI_MODE e_wifi_mode;
	E_SDK_NET_STATUS	e_wifi_connect_status;	
	char	a_SSID[64];
	char	a_passwd[64];
	unsigned int	un_encrypt;
	int     qlink_start;      //1无感配网开始，2无感配网失败，0默认值
}T_SDK_WIRELESS_PARAMS;



typedef struct
{
    char	a_IP[64];
}T_SDK_IPADDR;

typedef struct
{
    unsigned int	ddns_swicth;    //value range(1:enable 0:disable)
	char	a_username[50];  
	char	a_password[50];  
	char	a_server[128];   
	char	a_domain[128];  
	unsigned int	un_protocol_type;      //value range(:0: Oray  protocol 1:DYNDNS protocol)
}T_SDK_DDNS;


typedef struct
{
	char	a_DNS[2][64]; 
}T_SDK_DNS;


typedef struct _T_NTP_CONFIG_S
{
	unsigned int	un_switch;		//value range(0:close 1:open)
	unsigned int	un_cycle;          //value range(1~7*24 hour)
	unsigned int	un_timezone;	//value range(0-12: The west 12 zone - 0 zone ;13-24:East 1 zone - East 12 zone)
	char	a_host[128];	
	unsigned int	un_daylight;     
}T_SDK_NTP;

typedef struct
{
    char	a_gateway[64];
}T_SDK_GATEWAY;

typedef struct
{
    char	a_mask[64];
}T_SDK_NET_MASK;

typedef struct
{
	char	a_wire_MAC[19];
	char	a_wireless_MAC[19];	
}T_SDK_NET_MAC;  // not support

typedef struct
{
    char	a_hostname[64];
}T_SDK_HOSTNAME;

typedef struct
{
	unsigned int un_protocals_type;
	T_SDK_WIRELESS_PARAMS	t_wireless_param;
	unsigned int	un_dhcp_switch; 			//0:static 1:dhcp
	char	a_hostname[64];
	char	a_IP[64];
	char	a_DNS[2][64]; 
	T_SDK_NTP	t_NTP;
	char	a_gateway[64];
	char	a_mask[64];
	char	a_wire_MAC[19];
	char	a_wireless_MAC[19];	
	T_SDK_DDNS	t_DDNS_info;
}T_SDK_NETWORK_PARAMS;


//ntp 参数结构设置
typedef struct
{
	unsigned int	un_NtpOpen;						//ntp校时开关 (1:开启， 0:关闭)
	unsigned int	un_EuroTime;					//夏令时开关  (1:开启,  0:关闭)
	unsigned int	un_NtpRefTime;					//ntp校时间隔 (单位秒)
	int				un_TimeZone;					//时区 (-12~11)
	char     		a_NtpServer[64];		        //ntp校时服务器地址
	unsigned int	un_ntp_port; 					//ntp校时服务器端口
	unsigned int	un_Res[2];
}T_SDK_NTP_CFG_PARAMS;


//********************************************************************
//********** module tpye: SDK DEBUG (ff)**************************
//********************************************************************
typedef enum 
{
	FATAL, 	
	ERROR, 		
	WARING,		
	NOTE, 
	None,
}E_SDK_DEBUG_LEVEL;

/*
int yhp2p_data_build(T_SDK_STREAM_CALLBACK_PARAM *encodeData);
*/


typedef struct _PTZ_POSI_
{
	int s32X;
	int s32Y;
}PTZ_POSI_ST;

#if defined (__cplusplus)
}
#endif

#endif

