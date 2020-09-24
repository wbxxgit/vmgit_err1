/*
cjb add 20140803
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <dlfcn.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/signal.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <ctype.h>
#include "sdk_define.h"
#include "sdkout_impl.h" 
#include "sdk_commonstruct.h"
#include "IPC_MediaBuff.h"

#include "zjsdk_inc.h"
#include "sAuxiliary.h"
#include "forZbSeg_camera.h"
#include "device_log.h"

#include "devCfg.h"
#include "dev_alarm.h"


#define TUTK_PLATFORM			0		//TUTK平台宏定义开关
#define ULIFE_SERVER			1
#include "global.h"
#include "api_system.h"
#include "api_sensor.h"

#if GOS_21CN_V2

#if !Make_SDK
#include "CNV2_Iot.h"
#endif
#else
#include "IPC_Main.h"
#include "IPC_ParamInfo.h"
#endif
#include "stream_manager.h"
#include "stream_define.h"
#include "media_fifo.h"



#if !GOS_21CN_V2
alarm_callback func_AlarmCallback = NULL;
#endif

#define TEST_OSD_CONFIG 0
#define TEST_VIDEO_CONFIG 0
#define TEST_RECORD 0  
#define TEST_SNAPSHOT 0
#define TEST_PTZ 0
#define TEST_INTERCOME 0
#define TEST_NETWORK_NTP_WIFI 0
#define TEST_SYSTEM_INFO 0

//==========================================================================================
//音视频消息回调
//==========================================================================================
#if 1
int IPC_MediaBuff_WirteFrame(unsigned int nEncType, unsigned int nChn, void * pHead, unsigned char* data, int frame_size)
{
	if(NULL == data || NULL == pHead)
	{
		return -1;
	}
	frame_info * p = (frame_info *)pHead;
	GK_NET_FRAME_HEADER gk_header;
	memset(&gk_header, 0, sizeof(GK_NET_FRAME_HEADER));
	gk_header.frame_size = frame_size;
	gk_header.frame_no = p->seq;

	//video	
	if(0 == p->type || 1 == p->type)
	{
//		LOGI_print("shm_stream_remains:%d info.type:%d  info.seq:%d length:%d \n", shm_stream_remains(pUserReadId), info.type, info.seq, length);
		if(p->key)
		{
			gk_header.frame_type = GK_NET_FRAME_TYPE_I;
		}else
		{
			gk_header.frame_type = GK_NET_FRAME_TYPE_P;
		}
	}

	//audio
	if(2 == p->type)
	{
		gk_header.frame_type = GK_NET_FRAME_TYPE_A;
	}
	
	gk_header.sec = p->t_time;
	gk_header.pts = p->pts;
	gk_header.reserved = p->reserved[0];

	if(1 == nEncType)
	{
		if(0 == nChn)
		{
			mediabuf_write_frame(g_stMediaHandle.pUserWirteMain, data, frame_size, &gk_header); 
		}else
		{
			mediabuf_write_frame(g_stMediaHandle.pUserWirteSub, data, frame_size, &gk_header); 
		}
//		LOGD_print(" enc type:%d nChn:%d info.type:%d frame_size:%d \n", nEncType, nChn, info.type, frame_size);
	}
	
	if(2 == nEncType)
	{	
		mediabuf_write_frame(g_stMediaHandle.pUserWirteMain, data, frame_size, &gk_header); 
		mediabuf_write_frame(g_stMediaHandle.pUserWirteSub, data, frame_size, &gk_header); 
	}
	return 0;
}
#endif



int IPC_MediaBuff_WirteFrame_v(unsigned int nEncType, unsigned int nChn, void * pHead, unsigned char* data, int frame_size)
{
	if(NULL == data || NULL == pHead)	
		return -1;	
//	printf("before SegCam_getVideoSw:%d\n",SegCam_getVideoSw());
	if(SegCam_getVideoArrSw_cmpRet(nChn) != 1 )
		return -2;	 //sw off
	
	if( NULL == dj_video_GtFTbl()->f_Video_WriteFrame){
		printf("f_Video_WriteFrame no register!\n");
		return -1;			
	}
	frame_info * p = (frame_info *)pHead;
	GK_NET_FRAME_HEADER gk_header;
	memset(&gk_header, 0, sizeof(GK_NET_FRAME_HEADER));
	gk_header.frame_size = frame_size;
	gk_header.frame_no = p->seq;
	//video	
	if(0 == p->type || 1 == p->type)
	{
		if(p->key)
		{
			gk_header.frame_type = 1;  //GK_NET_FRAME_TYPE_I
		}else
		{
			gk_header.frame_type = 0;  //GK_NET_FRAME_TYPE_P
		}
	}	
	gk_header.sec = p->t_time;
	gk_header.pts = p->pts;
	gk_header.reserved = p->reserved[0];	

	if(! (0 == nChn||1 == nChn) ){
		ZJ_LOG_INF("nChn is not Within rang\n");
		return -1;
	}
	dj_video_GtFTbl()->f_Video_WriteFrame(nChn,data,frame_size,lin_GetTickCount(),
											gk_header.frame_type);
	return 0;
}
int IPC_MediaBuff_WirteFrame_A(unsigned int nEncType, unsigned int nChn, void * pHead, unsigned char* data, int frame_size)
{
	if(NULL == data || NULL == pHead)
		return -1;
	if(2 != nEncType)
		return -1;
	
	if(SegCam_getAudioSw() != ALLOW_AUDIOSTREAM)
		return -2;	 //sw off
	if( NULL == dj_audio_GtFTbl()->f_Audio_WriteFrame){
		printf("f_Audio_WriteFrame no register!\n");
		return -1;			
	}	
	frame_info * p = (frame_info *)pHead;
	GK_NET_FRAME_HEADER gk_header;
	memset(&gk_header, 0, sizeof(GK_NET_FRAME_HEADER));
	gk_header.frame_size = frame_size;
	gk_header.frame_no = p->seq;
	
	if(2 == p->type) //audio	
		gk_header.frame_type = GK_NET_FRAME_TYPE_A;	
	
	gk_header.sec = p->t_time;
	gk_header.pts = p->pts;
	gk_header.reserved = p->reserved[0];	

	dj_audio_GtFTbl()->f_Audio_WriteFrame(data,frame_size,lin_GetTickCount());
//	printf("f_Audio_WriteFrame nEncType:%d!\n",nEncType);	
	return 0;
}


int AV_FarmeCallback_0(T_SDK_STREAM_CALLBACK_PARAM *encodeData)
{
	if (NULL == encodeData) return -1;
	frame_info info;
	memset(&info,0,sizeof(frame_info));
	
	info.seq = encodeData->un_sequence;
	info.pts = encodeData->un_timestamp;	
	info.t_time = encodeData->un_sec;
	info.type = encodeData->un_frame_type;
	info.length = encodeData->un_data_len;
	info.reserved[0] = encodeData->n_reserve;
	if(0 == encodeData->un_frame_type)
	{
		info.type = 0;		//p帧
	}else if(1 == encodeData->un_frame_type)
	{
		info.type = 1;		//i帧
		info.key = 1;
	}
	
	#if 0
	if(NULL == encodeData)
	{
		printf("T_SDK_STREAM_CALLBACK_PARAM is NULL\n");
		return -1;
	} 
	return 0;
	#else
//	printf("AV_FarmeCallback_0 exe un_steam_type:%d,un_encode_channel_id:%d,un_data_len:%d\n",encodeData->un_steam_type, encodeData->un_encode_channel_id, encodeData->un_data_len);
	return IPC_MediaBuff_WirteFrame_v(encodeData->un_steam_type, encodeData->un_encode_channel_id, (void *)&info, encodeData->uncp_data, encodeData->un_data_len);
	#endif
	
}
/* Audio Data Callback */
int AV_FarmeCallback_1(T_SDK_STREAM_CALLBACK_PARAM *encodeData)
{
	if (NULL == encodeData) return -1;
	frame_info info;
	memset(&info,0,sizeof(frame_info));
	info.seq = encodeData->un_sequence;
	info.pts = encodeData->un_timestamp;
	info.t_time = encodeData->un_sec;
	info.type = encodeData->un_steam_type;
	info.length = encodeData->un_data_len;
	info.reserved[0] = encodeData->n_reserve;
	//printf("----->audio data:%ld, %llu\n", info.t_time);
	#if 0
	if(NULL == encodeData)
	{
		printf("T_SDK_STREAM_CALLBACK_PARAM is NULL\n");
		return -1;
	} 
	return 0;
	#else
//	printf("AV_FarmeCallback_1 exe un_steam_type:%d,un_encode_channel_id:%d,un_data_len:%d\n",encodeData->un_steam_type, encodeData->un_encode_channel_id, encodeData->un_data_len);
	return IPC_MediaBuff_WirteFrame_A(encodeData->un_steam_type, encodeData->un_encode_channel_id, (void *)&info, encodeData->uncp_data, encodeData->un_data_len);
	#endif
	
}
int AV_FarmeCallback_2(T_SDK_STREAM_CALLBACK_PARAM *encodeData)	//PCM 数据回调函数
{ 
	   if(NULL == encodeData)
		{
			printf("T_SDK_STREAM_CALLBACK_PARAM is NULL\n");
			return -1;
		} 
		return 0;

}
int AV_FarmeCallback_3(T_SDK_STREAM_CALLBACK_PARAM *parm)
{ 
    if(NULL == parm)
    {
        return -1;
    }  
    printf("3 stream\n");    
    return 0;
}


int AlarmCallback(T_SDK_ALARM_CALLBACK_PARAM *param)
{
	if(NULL == param)
	{
		printf("T_SDK_ALARM_CALLBACK_PARAM is null\n");
		return -1;
	}	
	if(param->e_alarm_type == E_SCAN_SUCCEED)
	{
		printf("scan:%s\n", param->alarm_pic_url);
	}	
	// zj motion alarm 	//alarm array process
	ZJ_LOG_INF("param->e_alarm_type = %d",param->e_alarm_type);
	if(0 != alarmcb_process(param))
		ZJ_LOG_INF("0 != alarmcb_process");

	return 0;
}

int SDK_TEST_OSD_Get_Param(void)
{
	int retcode = 0;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_OSD_DEFAULT_PARAM, NULL);
	if(retcode != 0)
	{
		return -1;
	}

    T_SDK_ALL_OSD_PARAM pGetData;
    int streamId = 0;
    
    for(streamId = 0; streamId <= 3; streamId ++)
    {
        memset(&pGetData, 0, sizeof(T_SDK_ALL_OSD_PARAM));
        printf("======streamId:%d=================get osd param===========================\n> ",streamId);   
        pGetData.un_encode_channel_id = streamId;             
        if (0 != SDK_Cmd_Impl(SDKCMD_GET_OSD_PARAM,(void *)&pGetData))
        {
           printf("call set osd SDK_Cmd_Impl fail .\n");           
           return -1;
        } 

  		printf("channel:%d\ntime_switch:%d,time_x:%d,time_y:%d,time_color:%d\n\
			title1_switch:%d,title1:%s,title1_x:%d,title1_y:%d,title1_color:%d\n\
			title2_switch:%d,title2:%s,title2_x:%d,title2_y:%d,title2_color:%d\n",
			streamId, 
			pGetData.t_time.un_show, pGetData.t_time.un_x_coordinate, pGetData.t_time.un_y_coordinate, pGetData.t_time.un_color,
			pGetData.t_title1.un_show, pGetData.a_title1, pGetData.t_title1.un_x_coordinate, pGetData.t_title1.un_y_coordinate, pGetData.t_title1.un_color,
			pGetData.t_title2.un_show, pGetData.a_title2, pGetData.t_title2.un_x_coordinate, pGetData.t_title2.un_y_coordinate, pGetData.t_title2.un_color);
    }
       
    return 0;
}

int SDK_TEST_OSD_SWITCH(void)
{
    T_SDK_OSD_SWITCH pSetData;
    int streamId = 0;
    
    for(streamId = 0; streamId <= 3; streamId ++)
    {
        memset(&pSetData, 0, sizeof(T_SDK_OSD_SWITCH));
        printf("======streamId:%d=================disable osd set===========================\n> ",streamId);   
        pSetData.un_encode_channel_id = streamId; 
        pSetData.un_show_Time = 0; 
		pSetData.un_show_Date = 0;
        pSetData.un_show_Title1 = 0;
        pSetData.un_show_Title2 = 0;                  
        if (0 != SDK_Cmd_Impl(SDKCMD_SET_OSD_SHOW_SWITCH,(void *)&pSetData))
        {
           printf("call set osd SDK_Cmd_Impl fail .\n");           
           return -1;
        } 
	}
	
    sleep(20);
	
	for(streamId = 0; streamId <= 3; streamId ++)
	{
        memset(&pSetData, 0, sizeof(T_SDK_OSD_SWITCH));
        printf("======streamId:%d=================enable osd set===========================\n> ",streamId);   
        pSetData.un_encode_channel_id = streamId; 
        pSetData.un_show_Time = 1; 
		pSetData.un_show_Date = 1;
        pSetData.un_show_Title1 = 1;
        pSetData.un_show_Title2 = 1;                  
        if (0 != SDK_Cmd_Impl(SDKCMD_SET_OSD_SHOW_SWITCH,(void *)&pSetData))
        {
           printf("call set osd SDK_Cmd_Impl fail .\n");
           return -1;
        }    
    }
    
    
    return 0;
}

int SDK_TEST_OSD_COLOR(void)
{
    T_SDK_OSD_COLOR pSetData;
    int streamId = 0;
    for(streamId = 0; streamId <= 3; streamId ++)
    {
       
        memset(&pSetData, 0, sizeof(T_SDK_OSD_COLOR));
        printf("======streamId:%d=================set osd color===========================\n> ",streamId);   
        pSetData.un_encode_channel_id = streamId; 
        pSetData.un_color = 0;
        if (0 != SDK_Cmd_Impl(SDKCMD_SET_OSD_COLOR,(void *)&pSetData))
        {
           printf("call set osd SDKCMD_SET_OSD_COLOR fail .\n");           
           return -1;
        } 
#if 1

 
        sleep(2);
      
        memset(&pSetData, 0, sizeof(T_SDK_OSD_COLOR));
        printf("======streamId:%d=================change set osd color===========================\n> ",streamId);   
        pSetData.un_encode_channel_id = streamId; 
        pSetData.un_color = 4;              
        if (0 != SDK_Cmd_Impl(SDKCMD_SET_OSD_COLOR,(void *)&pSetData))
        {
           printf("call set osd SDKCMD_SET_OSD_COLOR fail .\n");
           return -1;
        }    
  #endif      
        sleep(2);
    }
    
    
    return 0;
}

int SDK_TEST_OSD_POS(void)
{
    T_SDK_OSD_POS pSetData;
    int streamId = 0;
   // for(streamId = 0; streamId <= 3; streamId ++)
    {
       
        memset(&pSetData, 0, sizeof(T_SDK_OSD_POS));
        printf("======streamId:%d=================set osd POS===========================\n> ",streamId);   
        pSetData.un_encode_channel_id = streamId; 
        pSetData.un_x_time     = 0;
        pSetData.un_y_time     = 0;
        pSetData.un_x_title1   = 50;
        pSetData.un_y_title1   = 100;
        pSetData.un_x_title2   = 0;
        pSetData.un_y_title2   = 0;
        if (0 != SDK_Cmd_Impl(SDKCMD_SET_OSD_POS,(void *)&pSetData))
        {
           printf("call set osd SDKCMD_SET_OSD_POS fail .\n");           
           return -1;
        }  
        sleep(6);
      
        memset(&pSetData, 0, sizeof(T_SDK_OSD_POS));
        pSetData.un_encode_channel_id = streamId; 
        pSetData.un_x_time     = 0;
        pSetData.un_y_time     = 0;
        pSetData.un_x_title1   = 50;
        pSetData.un_y_title1   = 50;
        pSetData.un_x_title2   = 0;
        pSetData.un_y_title2   = 0;
        printf("======streamId:%d=================change set osd POS===========================\n> ",streamId);   
        if (0 != SDK_Cmd_Impl(SDKCMD_SET_OSD_POS,(void *)&pSetData))
        {
           printf("call set osd SDKCMD_SET_OSD_POS fail .\n");
           return -1;
        }    
        sleep(2);
    }
    
    
    return 0;
}

int SDK_TEST_OSD_Title(void)
{
    T_SDK_OSD_TITLE pSetData;
    int streamId = 0;
    for(streamId = 0; streamId <= 3; streamId ++)
    {
		if(0 != streamId)
		{
			memset(&pSetData, 0, sizeof(T_SDK_OSD_TITLE));
			printf("======streamId:%d=================set osd title===========================\n> ",streamId);   
			pSetData.un_encode_channel_id = streamId; 
			strcpy(pSetData.a_title1, "收到"); 
			strcpy(pSetData.a_title2, "osd");
			if (0 != SDK_Cmd_Impl(SDKCMD_SET_OSD_TITLE,(void *)&pSetData))
			{
			   printf("call set osd SDKCMD_SET_OSD_TITLE fail .\n");           
			   return -1;
			} 
		}
#if 1
 
        sleep(6);
      
        memset(&pSetData, 0, sizeof(T_SDK_OSD_TITLE));
        printf("======streamId:%d=================set osd title change===========================\n> ",streamId);   
        pSetData.un_encode_channel_id = streamId; 
        strcpy(pSetData.a_title1, "dog"); 
		strcpy(pSetData.a_title2, "dog"); 
        if (0 != SDK_Cmd_Impl(SDKCMD_SET_OSD_TITLE,(void *)&pSetData))
        {
           printf("call set osd SDKCMD_SET_OSD_TITLE fail .\n");           
           return -1;
        }    
#endif      
        sleep(2);
    }
    
    
    return 0;
}

int SDK_TEST_VIDEO_CONFIG()
{	
	int retcode = 0;
	T_SDK_VIDEO_ENCODE_PARAM t_image_param;
	t_image_param.un_encode_channel_id = 0;
	retcode = SDK_Cmd_Impl(SDKCMD_GET_VIDEO_ENCODE_PARAM, &t_image_param);
	if(retcode != 0)
	{
		return -1;
	}
	printf("s:%d e:%d w:%d h:%d k:%d bv:%d bi:%d bx:%d f:%d b:%d t:%d q:%d p:%d xi:%d ni%d xp:%d np:%d \n",
						t_image_param.un_encode_switch, //
						t_image_param.e_encode_type,
						t_image_param.un_width,					
						t_image_param.un_height,					
						t_image_param.un_I_frame_interval,	//		
						t_image_param.t_bitrate.un_average_bitrate,	
						t_image_param.t_bitrate.un_min_bitrate,//
						t_image_param.t_bitrate.un_max_bitrate,//
						t_image_param.un_framerate,				
						t_image_param.t_bitrate.un_bitrate_type, 	//		
						t_image_param.t_lower_bitrate_control.un_switch,
						t_image_param.un_quality,		//			
						t_image_param.un_profile,		// 1	  
						t_image_param.t_QP.un_I_frame_max_Qp,  //           
						t_image_param.t_QP.un_I_frame_min_Qp, //            
						t_image_param.t_QP.un_P_frame_max_Qp, //            
						t_image_param.t_QP.un_P_frame_min_Qp);

	printf("config bit rate0_____________________________________start\n");

	T_SDK_VIDEO_ENCODE_RESOLUTION t_resolution;

	printf("set stream0 resolution : 1280*720\n");

	t_resolution.un_encode_channel_id = 0;
	t_resolution.un_width = 1280;
	t_resolution.un_height = 720;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_VIDEO_ENCODE_RESOLUTION, &t_resolution);
	if(retcode != 0)
	{
		return -1;
	}
	sleep(20);
	printf("set stream0 resolution :320*180\n");
	t_resolution.un_encode_channel_id = 0;
	t_resolution.un_width = 320;
	t_resolution.un_height = 180;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_VIDEO_ENCODE_RESOLUTION, &t_resolution);
	if(retcode != 0)
	{
		return -1;
	}
	sleep(20);
	printf("set stream0 resolution :320*240\n");
	t_resolution.un_encode_channel_id = 0;
	t_resolution.un_width = 320;
	t_resolution.un_height = 240;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_VIDEO_ENCODE_RESOLUTION, &t_resolution);
	if(retcode != 0)
	{
		return -1;
	}
	sleep(20);

	printf("set stream0 resolution : 640*480\n");
	t_resolution.un_encode_channel_id = 0;
	t_resolution.un_width = 640;
	t_resolution.un_height = 480;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_VIDEO_ENCODE_RESOLUTION, &t_resolution);
	if(retcode != 0)
	{
		return -1;
	}
	sleep(20);
	printf("set stream0 resolution : 720*576\n");
	t_resolution.un_encode_channel_id = 0;
	t_resolution.un_width = 720;
	t_resolution.un_height = 576;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_VIDEO_ENCODE_RESOLUTION, &t_resolution);
	if(retcode != 0)
	{
		return -1;
	}
	sleep(20);

#if 0
	T_SDK_VIDEO_ENCODE_BITRATE t_bit_rate;
	t_bit_rate.un_encode_channel_id = 2;
	t_bit_rate.un_bitrate_type = 1;
	t_bit_rate.un_average_bitrate = 600;
	t_bit_rate.un_min_bitrate = 200;
	t_bit_rate.un_max_bitrate = 600;	
	retcode = SDK_Cmd_Impl(SDKCMD_SET_VIDEO_ENCODE_BITRATE, &t_bit_rate);	
	if(retcode != 0)
	{
		return -1;
	}	
	printf("config bit rate0_____________________________________end\n");

	sleep(50);
	

	printf("config bit rate1_____________________________________start\n");
	t_bit_rate.un_encode_channel_id = 2;
	t_bit_rate.un_bitrate_type = 1;	
	t_bit_rate.un_average_bitrate = 1000;
	t_bit_rate.un_min_bitrate = 200;
	t_bit_rate.un_max_bitrate = 2000; 
	retcode = SDK_Cmd_Impl(SDKCMD_SET_VIDEO_ENCODE_BITRATE, &t_bit_rate);	
	if(retcode != 0)
	{
		return -1;
	}	
	printf("config bit rate1_____________________________________end\n");

	sleep(50);
	

	printf("config bit rate2_____________________________________start\n");
	t_bit_rate.un_encode_channel_id = 2;
	t_bit_rate.un_bitrate_type = 1;
	t_bit_rate.un_average_bitrate = 300;
	t_bit_rate.un_min_bitrate = 200;
	t_bit_rate.un_max_bitrate = 2000; 
	retcode = SDK_Cmd_Impl(SDKCMD_SET_VIDEO_ENCODE_BITRATE, &t_bit_rate);	
	if(retcode != 0)
	{
		return -1;
	}	
	printf("config bit rate2_____________________________________end\n");
				

	T_SDK_VIDEO_ENCODE_RESOLUTION t_resolution;
	t_resolution.un_encode_channel_id = 0;
	t_resolution.un_width = 1280;
	t_resolution.un_height = 720;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_VIDEO_ENCODE_RESOLUTION, &t_resolution);
	if(retcode != 0)
	{
		return -1;
	}

	T_SDK_VIDEO_ENCODE_I_FRAME_INTERVAL t_I_interval;
	t_I_interval.un_encode_channel_id = 1;
	t_I_interval.un_interval = 10;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_VIDEO_ENCODE_I_FRAME_INTERVAL, &t_I_interval);
	if(retcode != 0)
	{
		return -1;
	}

	T_SDK_FORCE_I_FARME t_I_key;
	t_I_key.un_encode_channel_id = 1;
	t_I_key.un_force_num = 1;
	retcode = SDK_Cmd_Impl(SDKCMD_FORCE_VIDEO_ENCODE_I_FRAME, &t_I_key); 
	if(retcode != 0)
	{
		return -1;
	}	
	printf("force I/n");

	T_SDK_VIDEO_ENCODE_QP t_qp;
	t_qp.un_encode_channel_id = 1;
	t_qp.un_I_frame_max_Qp = 30;
	t_qp.un_I_frame_min_Qp = 28;
	t_qp.un_P_frame_max_Qp = 32;
	t_qp.un_P_frame_min_Qp = 28;	
	retcode = SDK_Cmd_Impl(SDKCMD_SET_VIDEO_ENCODE_QP, &t_qp); 
	if(retcode != 0)
	{
		return -1;
	}	
	
	T_SDK_VIDEO_ENCODE_FRAMERATE t_fr;
	t_fr.un_encode_channel_id = 0;
	t_fr.un_framerate = 25;	
	retcode = SDK_Cmd_Impl(SDKCMD_SET_VIDEO_ENCODE_FRAMERATE, &t_fr); 
	if(retcode != 0)
	{
		return -1;
	}

	/*
	T_SDK_VIDEO_ENCODE_SWITCH t_encode_switch;
	t_encode_switch.un_encode_channel_id = 1;
	t_encode_switch.un_switch = 0;	
	retcode = SDK_Cmd_Impl(SDKCMD_SET_VIDEO_ENCODE_SWITCH, &t_encode_switch); 
	if(retcode != 0)
	{
		return -1;
	}*/

	unsigned int un_mirror;
	un_mirror = 3;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_VIDEO_ENCODE_MIRROR,  (void*)(&un_mirror));
	if(retcode != 0)
	{
		return -1;
	}
#endif

	return 0;

}



int SDK_TEST_Intercome()
{
	FILE * crosstalk_fd = NULL;
	int retcode = 0;
	crosstalk_fd = fopen("/opt/ipnc/aac/turn_on.aac", "r");
	if(NULL == crosstalk_fd)
	{
		printf("talk fopen fail\n");
		return -1;
	}

	unsigned char s_talk_data[2048] = {0};
	int ret = 0;
	int time1 = 0;
	printf("2fread start======================\n");
	while(1)
	{
		ret = fread(s_talk_data, 1, sizeof(s_talk_data), crosstalk_fd);
		if(ret <= 0)
		{
			printf("talk fread %dfail%d\n", time1, ret);
			fseek(crosstalk_fd, 0, SEEK_SET);/*read file again*/
			break;			
		}
		time1++;
		T_SDK_INTERCOM_DATA t_inercom_data;
		memset(&t_inercom_data, 0, sizeof(T_SDK_INTERCOM_DATA));
		t_inercom_data.cp_data = s_talk_data;
		t_inercom_data.un_data_len = ret;
		usleep(40000);
		retcode = SDK_Cmd_Impl(SDKCMD_SEND_INTERCOM_DATA, &t_inercom_data);
		if(retcode != 0)
		{
			printf("SDKCMD_SEND_INTERCOM_DATA faile\n");
			//fclose(crosstalk_fd);
			//return -1;
		}		
	}
	
	//sleep(1);
	if(SDK_Cmd_Impl(SDKCMD_INTERCOM_START, NULL))
	{
		printf("AMBA_AUDIO_CreatTrdSocketAdec fail\n");
		return -1;
	}

	fclose(crosstalk_fd);
	sleep(100);
	if(SDK_Cmd_Impl(SDKCMD_INTERCOM_STOP, NULL))
	{
		printf("AMBA_AUDIO_StopTrdSocketAdec fail\n");
	}

	return 0;

}

int SDK_TEST_NTP_Wifi_Network()
{	
	int retcode = 0;
	T_SDK_WIRELESS_PARAMS t_wireless_param;
	memset(&t_wireless_param, 0, sizeof(T_SDK_WIRELESS_PARAMS));
	t_wireless_param.un_encrypt = 1;
	t_wireless_param.e_wifi_connect_status = E_SDK_DISCONNECT;
	t_wireless_param.e_wifi_mode = E_SDK_WIFI_WPS_MODE;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_WIRELESS_PARAM,  (void*)(&t_wireless_param));
	if(retcode != 0)
	{
		return -1;
	}

	memset(&t_wireless_param, 0, sizeof(T_SDK_WIRELESS_PARAMS));
	t_wireless_param.un_encrypt = 1;
	t_wireless_param.e_wifi_connect_status = E_SDK_DISCONNECT;
	strcpy(t_wireless_param.a_passwd, "goscamsoftsoft");
	strcpy(t_wireless_param.a_SSID, "lb-test");
	t_wireless_param.e_wifi_mode = E_SDK_WIFI_CLIENT_MODE;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_WIRELESS_PARAM,  (void*)(&t_wireless_param));
	if(retcode != 0)
	{
		return -1;
	}
	

	printf("before get net info\n");
	T_SDK_NETWORK_PARAMS t_net_param;
	memset(&t_net_param, 0, sizeof(T_SDK_NETWORK_PARAMS));
	retcode = SDK_Cmd_Impl(SDKCMD_GET_NETWORK_PARAM, &t_net_param);
	if(retcode != 0)
	{
		return -1;
	}	
	printf(" wifitype:%d\n status:%d\n wifissid:%s\n wifipasswd:%s\n wifiencrypt:%d\n ip:%s\n mask:%s\n gateway:%s\n eht0mac:%s\n ra0mac:%s\n dns1:%s\n dns2:%s \n hostname:%s\n", 
		t_net_param.t_wireless_param.e_wifi_mode,
		t_net_param.t_wireless_param.e_wifi_connect_status,
		t_net_param.t_wireless_param.a_SSID,
		t_net_param.t_wireless_param.a_passwd,
		t_net_param.t_wireless_param.un_encrypt,
		t_net_param.a_IP,
		t_net_param.a_mask,
		t_net_param.a_gateway,
		t_net_param.a_wire_MAC,
		t_net_param.a_wireless_MAC,
		t_net_param.a_DNS[0],
		t_net_param.a_DNS[1],
		t_net_param.a_hostname
		);
	printf("end get net info\n");	

	return 0;
}

int SDK_TEST_Record()
{
	printf("===============record test==============================\n");

	int retcode = 0;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_RECORD_DEFAULT_PARAM, NULL);
	if(retcode != 0)
	{
		printf("SDKCMD_SET_RECORD_DEFAULT_PARAM error\n");
		return -1;
	}

	retcode = SDK_Cmd_Impl(SDKCMD_CLEAR_RECORD_FILE, NULL);
	if(retcode != 0)
	{
		printf("SDKCMD_CLEAR_RECORD_FILE error\n"); 
		return -1;
	}

	system("ls -l /opt/httpServer/lighttpd/htdocs/sd/ipc");

	T_SDK_RECORD_PARAM t_record_param;
	retcode = SDK_Cmd_Impl(SDKCMD_GET_RECORD_PARAM, &t_record_param);
	if(retcode != 0)
	{
		printf("SDKCMD_GET_RECORD_PARAM error\n");	
		return -1;
	}	
	printf("switch:%d,audio:%d,ch:%d,dur:%d,loop:%d,type:%d\n", 
			t_record_param.un_switch,
			t_record_param.un_audio_switch,
			t_record_param.un_encode_channel_id,	
			t_record_param.un_file_duration, 
			t_record_param.un_loop,
			t_record_param.un_file_type);

	unsigned int un_duration = 30;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_RECORD_FILE_DURATION, &un_duration);
	if(retcode != 0)
	{
		printf("SDKCMD_SET_RECORD_FILE_DURATION error\n");	
		return -1;
	}

	unsigned int un_filetype = 1;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_RECORD_FILE_TYPE, &un_filetype);
	if(retcode != 0)
	{
		printf("SDKCMD_SET_RECORD_FILE_TYPE error\n");	
		return -1;
	}

	unsigned int un_loop = 0;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_LOOP_RECORD_SWITCH, &un_loop);
	if(retcode != 0)
	{
		printf("SDKCMD_SET_LOOP_RECORD_SWITCH error\n");	
		return -1;
	}

	unsigned int un_audio = 0;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_AUDIO_RECORD_SWITCH, &un_audio);
	if(retcode != 0)
	{
		printf("SDKCMD_SET_AUDIO_RECORD_SWITCH error\n");	
		return -1;
	}

	retcode = SDK_Cmd_Impl(SDKCMD_GET_RECORD_PARAM, &t_record_param);
	if(retcode != 0)
	{
		printf("SDKCMD_GET_RECORD_PARAMS error\n"); 
		return -1;
	}	
	printf("switch:%d,audio:%d,ch:%d,dur:%d,loop:%d,type:%d\n", 
			t_record_param.un_switch,
			t_record_param.un_audio_switch,
			t_record_param.un_encode_channel_id,	
			t_record_param.un_file_duration, 
			t_record_param.un_loop,
			t_record_param.un_file_type);

	printf("record start\n");
	unsigned int n_record = 1;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_RECORD_SWITCH, &n_record);
	if(retcode != 0)
	{
		printf("SDKCMD_SET_RECORD_SWITCH error\n"); 
		return -1;
	}


	sleep(40);

	n_record = 0;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_RECORD_SWITCH, &n_record);
	if(retcode != 0)
	{
		printf("SDKCMD_SET_RECORD_SWITCH error\n"); 
		return -1;
	}	
	printf("record stop\n");


	char s_month_list[1024] = {0};
	T_SDK_RECORD_MONTH_LIST t_moth;
	memset(&t_moth, 0, sizeof(T_SDK_RECORD_MONTH_LIST));
	strcpy(t_moth.a_month, "201501");
	t_moth.cp_list = s_month_list;
	t_moth.un_list_len = sizeof(s_month_list);
	retcode = SDK_Cmd_Impl(SDKCMD_GET_MONTH_RECORD_LIST, &t_moth);
	if(retcode != 0)
	{
		printf("SDKCMD_GET_MONTH_RECORD_LIST error\n"); 
		return -1;
	}	
	printf("monthlist:%s \n", t_moth.cp_list);
	int record_i = 0;
	int record_j = 0;
	int record_k = 0;
	char moth[31][11];
	memset(moth, 0, sizeof(moth));
	while('\0' != t_moth.cp_list[record_i])
	{
		if(' ' == t_moth.cp_list[record_i])
		{
			record_i++;
			continue;
		}
		if('|' == t_moth.cp_list[record_i])
		{
			record_i++;
			record_j++;
			if(31 == record_j)
			{
				break;
			}
			
			record_k = 0;
			continue;
		}
		moth[record_j][record_k] = t_moth.cp_list[record_i];
		record_k++;
		record_i++;
	}
	for(record_i = 0; record_i < 31; record_i++)
	{
		printf("moth%d:%s\n", record_i, moth[record_i]);
	}

	char s_day_list[1024] = {0};
	T_SDK_RECORD_DAY_LIST t_day;
	memset(&t_day, 0, sizeof(T_SDK_RECORD_DAY_LIST));
	strncpy(t_day.a_day, moth[0], 8);
	t_day.cp_list = s_day_list;
	t_day.un_list_len = sizeof(s_day_list);
	retcode = SDK_Cmd_Impl(SDKCMD_GET_DAY_RECORD_LIST, &t_day);
	if(retcode != 0)
	{
		printf("SDKCMD_GET_DAY_RECORD_LIST error\n");	
		return -1;
	}	
	printf("daylist:%s \n", t_day.cp_list);
	record_i = 0;
	record_j = 0;
	record_k = 0;
	char day[50][26];
	memset(day, 0, sizeof(day));
	while(0 != t_day.cp_list[record_i])
	{
		if(' ' == t_day.cp_list[record_i])
		{
			record_i++;
			continue;
		}
		if('|' == t_day.cp_list[record_i])
		{
			record_i++;
			record_j++;
			if(50 == record_j)
			{
				break;
			}
			
			record_k = 0;
			continue;
		}
		day[record_j][record_k] = t_day.cp_list[record_i];
		record_k++;
		record_i++;
	}
	for(record_i = 0; record_i < 50; record_i++)
	{
		printf("day%d:%s\n", record_i, day[record_i]);
	}

	T_SDK_RECORD_FILE_PATH t_full_path;
	memset(&t_full_path, 0, sizeof(T_SDK_RECORD_FILE_PATH));
	strcpy(t_full_path.a_file_name, day[0]);
	retcode = SDK_Cmd_Impl(SDKCMD_GET_RECORD_FILE_FULL_PATH, &t_full_path);
	if(retcode != 0)
	{
		printf("SDKCMD_GET_RECORD_FILE_FULL_PATH error\n"); 
		return -1;
	}	
	printf("full:%s\n", t_full_path.a_path);


	T_SDK_RECORD_LOCK_FILE t_lock;
	memset(&t_lock, 0, sizeof(T_SDK_RECORD_LOCK_FILE));
	strcpy(t_lock.a_file_name, day[0]);
	t_lock.un_lock = 1;
	retcode = SDK_Cmd_Impl(SDKCMD_LOCK_UNLOCK_RECORD_FILE, &t_lock);
	if(retcode != 0)
	{
		printf("SDKCMD_LOCK_UNLOCK_RECORD_FILE error\n");	
		return -1;
	}	
	char sDir[256] = {0};
	char sDirInfoTmp[64] = {0};
	strncpy(sDirInfoTmp, day[0], 6);
	snprintf(sDir, 256, "ls -l %s/%6s/%c%c/", "/sdcard/ipc", sDirInfoTmp, day[0][6], day[0][7]);
	system(sDir);

	return 0;
}

int SDK_TEST_SnapShot()
{
	T_SDK_PIC_PATH un_snap_path;
	memset(&un_snap_path, 0, sizeof(un_snap_path));
	strcpy(un_snap_path.pic_path, "/mnt/app/1.jpg"); //the folder must exist and can be write.
	printf("un_snap_path.pic_path >>>>>>>>>>%s\n",un_snap_path.pic_path);
	if (0 != SDK_Cmd_Impl(SDKCMD_SET_SNAPSHOT_PATH,(void *)&un_snap_path))
	{
	   printf("callSDKCMD_SET_SNAPSHOT_PATH fail .\n");           
	   return -1;
	} 	
	return 0;
}

int SDK_TEST_SnapShot_test(unsigned int namei)
{
	T_SDK_PIC_PATH un_snap_path;	
//	char nametmp[30]="/mnt/app/"; ///opt/httpServer/lighttpd/htdocs/sd/sound
	char nametmp[100]="/opt/httpServer/lighttpd/htdocs/sd/sound/";
	char namechar[5] = {0};

	sprintf(namechar, "%d", namei);
//	_itoa(namei,namechar,5);
	strcat(nametmp,namechar);
	strcat(nametmp,".jpg");
	printf("path:%s\n",nametmp);
	
	memset(&un_snap_path, 0, sizeof(un_snap_path));
	strcpy(un_snap_path.pic_path, nametmp); //the folder must exist and can be write.
	printf("un_snap_path.pic_path >>>>>>>>>>%s\n",un_snap_path.pic_path);
	if (0 != SDK_Cmd_Impl(SDKCMD_SET_SNAPSHOT_PATH,(void *)&un_snap_path))
	{
	   printf("callSDKCMD_SET_SNAPSHOT_PATH fail .\n");           
	   return -1;
	} 	
	return 0;
}


int SDK_TEST_PTZ()
{
	sleep(30);
	printf("turn left\n"); 
	if (0 != SDK_Cmd_Impl(SDKCMD_SET_PTZ_TURN_LEFT, NULL))
	{
	   printf("call SDKCMD_SET_PTZ_TURN_LEFT fail .\n");           
	   return -1;
	} 	

	sleep(5);
	printf("turn right\n"); 
	if (0 != SDK_Cmd_Impl(SDKCMD_SET_PTZ_TURN_RIGHT, NULL))
	{
	   printf("call SDKCMD_SET_PTZ_TURN_LEFT fail .\n");           
	   return -1;
	}	

	sleep(5);	
	printf("turn up\n"); 
	if (0 != SDK_Cmd_Impl(SDKCMD_SET_PTZ_TURN_UP, NULL))
	{
	   printf("call SDKCMD_SET_PTZ_TURN_LEFT fail .\n");           
	   return -1;
	}	

	sleep(5);	
	printf("turn down\n"); 
	if (0 != SDK_Cmd_Impl(SDKCMD_SET_PTZ_TURN_DOWN, NULL))
	{
	   printf("call SDKCMD_SET_PTZ_TURN_LEFT fail .\n");           
	   return -1;
	}	

	return 0;

}

int SDK_TEST_System_Info()
{
	int retcode = 0;
	T_SDK_DEVICE_INFO deviceInfo;
	printf("======================SDK_TEST_System_Info start========================\n");
	retcode = SDK_Cmd_Impl(SDKCMD_GET_DEVICE_INFO,  (void*)(&deviceInfo));
	if(retcode != 0)
	{
		return -1;
	}
	printf("DEVICE TYPE is: %s\n software:%s\n hardwar:%s id:%s\n", deviceInfo.a_type
		, deviceInfo.a_software_version
		, deviceInfo.a_hardware_version, deviceInfo.a_id);


	T_SDK_DEVICE_TIME t_date;
	t_date.un_year = 2013;
	t_date.un_month = 9;
	t_date.un_day = 9;
	t_date.un_hour = 9;
	t_date.un_minute = 9;
	t_date.un_second = 9;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_DEVICE_TIME,  (void*)(&t_date));
	if(retcode != 0)
	{
		return -1;
	}	

	retcode = SDK_Cmd_Impl(SDKCMD_SAVE_ALL_PARAM,  NULL);
	if(retcode != 0)
	{
		return -1;
	}
#if 0
	retcode = SDK_Cmd_Impl(SDKCMD_REBOOT_DEVICE,  NULL);
	if(retcode != 0)
	{
		return -1;
	}

	retcode = SDK_Cmd_Impl(SDKCMD_RESET_DEVICE,  NULL);
	if(retcode != 0)
	{
		return -1;
	}
#endif
	//change to night vision
	T_SDK_NIGHT_VISION t_night_vision;
	t_night_vision.un_auto = 0;
	t_night_vision.un_day_night = 1;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_NIGHT_VISION,  &t_night_vision);
	if(retcode != 0)
	{
		return -1;
	}

	sleep(3);
	t_night_vision.un_auto = 0;
	t_night_vision.un_day_night = 0;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_NIGHT_VISION,  &t_night_vision);
	if(retcode != 0)
	{
		return -1;
	}
	unsigned int un_connected = 1;
	retcode = SDK_Cmd_Impl(SDKCMD_SET_CONNECTED_PLATFORM_STATUS,  &un_connected);
	if(retcode != 0)
	{
		return -1;
	}
	printf("==============SDK_TEST_System_Info end==================\n");
#if 0
	T_SDK_LED s_led;
	while(1)
	{

		s_led.un_gpio_0 = 2;
		s_led.un_gpio_1 = 5;
		s_led.un_value = 0;
		retcode = SDK_Cmd_Impl(SDKCMD_SET_LED_STATUS,  &s_led);
		if(retcode != 0)
		{
			printf("SDKCMD_SET_LED_STATUS fail\n");
			return -1;
		}
		s_led.un_gpio_0 = 5;
		s_led.un_gpio_1 = 2;
		s_led.un_value = 0;
		retcode = SDK_Cmd_Impl(SDKCMD_SET_LED_STATUS,  &s_led);
		if(retcode != 0)
		{
			printf("SDKCMD_SET_LED_STATUS fail\n");
			return -1;
		}	
		sleep(2);

		s_led.un_gpio_0 = 5;
		s_led.un_gpio_1 = 2;
		s_led.un_value = 1;
		retcode = SDK_Cmd_Impl(SDKCMD_SET_LED_STATUS,  &s_led);
		if(retcode != 0)
		{
			printf("SDKCMD_SET_LED_STATUS fail\n");
			return -1;
		}	
		s_led.un_gpio_0 = 2;
		s_led.un_gpio_1 = 5;
		s_led.un_value = 0;
		retcode = SDK_Cmd_Impl(SDKCMD_SET_LED_STATUS,  &s_led);
		if(retcode != 0)
		{
			printf("SDKCMD_SET_LED_STATUS fail\n");
			return -1;
		}		
		sleep(2);

		s_led.un_gpio_0 = 5;
		s_led.un_gpio_1 = 2;
		s_led.un_value = 0;
		retcode = SDK_Cmd_Impl(SDKCMD_SET_LED_STATUS,  &s_led);
		if(retcode != 0)
		{
			printf("SDKCMD_SET_LED_STATUS fail\n");
			return -1;
		}

		s_led.un_gpio_0 = 2;
		s_led.un_gpio_1 = 5;
		s_led.un_value = 1;
		retcode = SDK_Cmd_Impl(SDKCMD_SET_LED_STATUS,  &s_led);
		if(retcode != 0)
		{
			printf("SDKCMD_SET_LED_STATUS fail\n");
			return -1;
		}	
		sleep(2);		
	}
#endif
	return 0;
}

void testProce_native(void){	
#if TEST_VIDEO_CONFIG
		//SDK_TEST_VIDEO_CONFIG();	
		sleep(60);
		while(1)
			{
				SDK_TEST_VIDEO_CONFIG();
				//break;
			}	
#endif	
#if TEST_OSD_CONFIG
		printf("====================osd test==start====================\n");
		//SDK_TEST_OSD_Get_Param();
		SDK_TEST_OSD_SWITCH();	
		//sleep(5);
		//SDK_TEST_OSD_COLOR();
		SDK_TEST_OSD_POS();
		sleep(5);
		SDK_TEST_OSD_Title();
		//sleep(5);
		printf("====================osd test==end======================\n");
#endif	
#if	TEST_RECORD
		SDK_TEST_Record();
#endif	
#if TEST_SNAPSHOT 
		SDK_TEST_SnapShot();
#endif	
#if TEST_PTZ 
		SDK_TEST_PTZ();
#endif	
#if TEST_INTERCOME	
		sleep(20);
		SDK_TEST_Intercome();	
#endif	
#if TEST_NETWORK_NTP_WIFI
		SDK_TEST_NTP_Wifi_Network();
#endif		
#if TEST_SYSTEM_INFO
		SDK_TEST_System_Info();
#endif
}

int device_init(void){
	int retcode = -1;
    //必须先注册好
    T_SDK_STREAM_REGISTER_CALLBACK t_register_stream_fun;

	t_register_stream_fun.ta_callback_info[0].fp_callback = AV_FarmeCallback_0;	
	t_register_stream_fun.ta_callback_info[0].un_video_switch = 1;
	t_register_stream_fun.ta_callback_info[0].un_audio_switch = 1;
	t_register_stream_fun.ta_callback_info[0].un_video_channel = 0;
	t_register_stream_fun.ta_callback_info[0].un_audio_channel = 0;
									
	t_register_stream_fun.ta_callback_info[1].fp_callback = AV_FarmeCallback_1; 
	t_register_stream_fun.ta_callback_info[1].un_video_switch = 1;
	t_register_stream_fun.ta_callback_info[1].un_audio_switch = 1;
	t_register_stream_fun.ta_callback_info[1].un_video_channel = 1;
	t_register_stream_fun.ta_callback_info[1].un_audio_channel = 0;

	t_register_stream_fun.ta_callback_info[2].fp_callback = AV_FarmeCallback_2;	
	t_register_stream_fun.ta_callback_info[2].un_video_switch = 0;
	t_register_stream_fun.ta_callback_info[2].un_audio_switch = 0;
	t_register_stream_fun.ta_callback_info[2].un_video_channel = 2;
	t_register_stream_fun.ta_callback_info[2].un_audio_channel = 0;
	
	t_register_stream_fun.ta_callback_info[3].fp_callback = AV_FarmeCallback_3;	
	t_register_stream_fun.ta_callback_info[3].un_video_switch = 0;
	t_register_stream_fun.ta_callback_info[3].un_audio_switch = 0;
	t_register_stream_fun.ta_callback_info[3].un_video_channel = 3;
	t_register_stream_fun.ta_callback_info[3].un_audio_channel = 0;	
	t_register_stream_fun.n_reserve = 0;
//	printf("hello SDK!\n");	
    retcode = SDK_Cmd_Impl(SDKCMD_REGISTER_STREAM_DATA_CALLBACK, (void *)&t_register_stream_fun);
	if(retcode < 0)
	{
		printf("register stream callback fail\n");
		return -1;
	}	
	T_SDK_ALARM_REGISTER_CALLBACK t_alarm_callback;
	t_alarm_callback.fp_callbak = AlarmCallback;
    retcode = SDK_Cmd_Impl(SDKCMD_RIGISTER_ALARM_CALLBACK,  (void *)&t_alarm_callback);
	if(retcode < 0)
	{
		printf("register alarm callback fail\n");
		return -1;
	}	
	retcode = SDK_Cmd_Impl(SDKCMD_SYS_INIT, NULL);
	if(retcode < 0)
	{
		printf("system init fail\n");
		return -1;
	}
	//适当延时一下
	usleep(100*1000);
	retcode = SDK_Cmd_Impl(SDKCMD_SYS_RUN,  NULL);
	if(retcode < 0)
	{
		printf("system run fail\n");
		return -1;
	}
	return 0;
}

#if 0
static int waitNtpSucceed(){
    char acStrTime[30] = "";
	struct	 tm 	*ptm;
	long	   ts;
	ts   =   time(NULL);
	ptm   =   localtime(&ts);
    snprintf(acStrTime, sizeof(acStrTime), "%04d-%02d-%02d %02d:%02d:%02d", 
			ptm-> tm_year+1900, ptm-> tm_mon+1, ptm-> tm_mday, ptm-> tm_hour, ptm-> tm_min, ptm-> tm_sec);

    printf("waitNtpSucceed time:time [%s] \n", acStrTime);	

	if(ptm-> tm_year+1900 == 2020)
		return 0;
	else
		return -1;	
}
#endif
int zjsdk_init(void){
	sdk_file_check();

	zjre_systemInit();
	zjre_cameraInit();
	zjre_cameraiotInit();
	zjre_networkInit();
	zjre_otaInit();
//	zjre_powerInit();	
//	zjre_channelInit();

	dev_zj_funcbReg();//register dev callback function
	dev_all_init();

	return 0;
}

int zjsdk_start(void){
	zjre_system_start();

	dev_all_statr();
	
	return 0;
}
int zjsdk_destory(void){
	zjre_cameraDestory();
	zjre_system_destory();

	dev_all_destory();

	return 0;
}


int main(){

	RTC_TIME_DEF pshow_compiletm = GetSoftWareBuildTargetTime();
	DPRI_INFO("*******Get_Compile_Date--y:%d-M:%d-d:%d-h:%d-m:%d-s:%d\n",
		pshow_compiletm.nYear,pshow_compiletm.nMonth,pshow_compiletm.nDay,
		pshow_compiletm.nHour,pshow_compiletm.nMinute,pshow_compiletm.nSecond);

	if( device_init() != 0){
		DPRI_INFO("device_init fail\n");
		return -1;
	}	
    //sleep(5);//系统跑起来 大概需要5秒  
	testProce_native();
/*	while(waitNtpSucceed() != 0){
		printf("**wait ntp 1s\n");
		sleep(1);

		if(getipJudge() == 0)
			printf("getipJudge succeed\n");
		else
			printf("getipJudge fail\n");		
	}	  */  
	
	zjsdk_init();
	zjsdk_start();
	DPRI_INFO("zjsdk_start going on\n");
	while(1){	
	//	nameti++;		
		sleep(15);
		DPRI_INFO("main sleep(15).....\n");
	/*	if (para ==0)
			para = 1;
		else
			para =0;
		if(SDK_Cmd_Impl(SDKCMD_SET_IRCUT_LED_STATUS,(void *)&para) !=0 ){
			ZJ_LOG_INF("SDK_Cmd_Impl ctrlLed_white_ircut err\n");	
		}			
		ZJ_LOG_INF("SDKCMD_SET_IRCUT_LED_STATUS 1 times &&,para:%d.....\n",para);  */		
	}
	zjsdk_destory();
	IPC_MediaBuff_Exit();
	return 0;
}

