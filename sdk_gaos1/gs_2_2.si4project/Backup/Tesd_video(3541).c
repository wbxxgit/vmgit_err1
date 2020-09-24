#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "zj_type.h"
#include "zj_log.h"
#include "zj_camera.h"  
#include "zj_cameraiot.h"
#include "Tesd_systemCfg.h"

#include "dev_zj_funReg.h"

#include "IPC_MediaBuff.h"






static pthread_t tid_video = 0;
//static unsigned char picSel;
//static char *PcSnapPic = NULL;
static char *g_pbuf = NULL; 
static char *g_pbufCfg = NULL;
static FILE *videoFile = NULL;
static FILE *videoCfgFile = NULL;



void *lan_reader[2];

void add_stream(void){
	lan_reader[0] = IPC_MediaBuff_AddRead(0, 0, "tlib_m");
	lan_reader[1] = IPC_MediaBuff_AddRead(0, 0, "tlib_s");
}



static void *video_loop(){
//	int ret;
//	char *recv_buf = NULL;
//	int data_length;
//	IPC_MEDIABUFF_FRAME_HEADER header;
//	unsigned char  bIsIFrame = 0;
	
	printf("enter video_loop\n");
	while(1){
		usleep(4000000);
		printf("video_loop......\n");
	/*
		ret = IPC_MediaBuff_ReadFrame(lan_reader[0], (void **)&recv_buf, &data_length, (void *)&header);
		if(ret != 0)
		{
			printf("IPC_MediaBuff_ReadFrame err: ret:%d",ret);
			break;
		}	
		printf("data_length:%d\n",data_length);
	//	printf("frame_size:%d,frame_no:%d,frame_size:%d，frame_size:%d，frame_size:%d\n",header.frame_size,header.frame_no,header.frame_type,header.sec,header.pts,header.reserved);

		usleep(400 000);
		
		if( NULL == dj_video_GtFTbl()->f_Video_WriteFrame){
			ZJ_LOG_INF("f_Video_WriteFrame no register!\n");
			return -1;			
		}
		if(0x00 == header.frame_type)
			bIsIFrame = EN_ZJ_VIDEO_FRAME_TYPE_I;	//EN_ZJ_VIDEO_FRAME_TYPE_I
		else		
			bIsIFrame = EN_ZJ_VIDEO_FRAME_TYPE_P;			
		dj_video_GtFTbl()->f_Video_WriteFrame(0, (unsigned char *)recv_buf, data_length, 
												header.pts, bIsIFrame);		 */	

	}
	return 0;
}

int testD_video_init(void){
	printf("testD_video_init exe");
	printf("Video Init OK\n");

	add_stream();
/*
	g_pbuf = (char *)malloc(72000);
	if(NULL==g_pbuf){
		printf("malloc error!\n");
		return -1;
	}
	memset(g_pbuf,0,72000);
	g_pbufCfg = (char *)malloc(40);
	if(NULL==g_pbufCfg){
		printf("pbufCfg malloc error!\n");
		return -1;
	}
	memset(g_pbufCfg,0,40);

	videoFile  = fopen(VIDEO_PLAYFILE_PATH_FILE,"rb"); 
	if(NULL==videoFile){
		ZJ_LOG_INF("fopen PATH error!\n");
		return -1;
	}
	videoCfgFile  = fopen(VIDEO_PLAYFILE_PATH_CFG,"rb"); 
	if(NULL==videoCfgFile){
		ZJ_LOG_INF("fcfg PATH error!\n");
		return -1;
	}  */	
	return 0;	
} 

int testD_video_start(void){
	printf("testD_video_start exe");
	if(-1 == pthread_create(&tid_video, NULL, video_loop, NULL)){
		printf("create error!\n");
		return -1;
	}	
	return 0;
} 

int testD_video_destory(void){
	void *ret;
	pthread_t tid_tmp = tid_video;
	printf("testD_video_destory exe\n");
	
//	free(PcSnapPic);
//	PcSnapPic = NULL;
	free(g_pbuf);
	g_pbuf = NULL;
	free(g_pbufCfg);		
	g_pbufCfg = NULL;	

	if(videoFile != NULL ){
		fclose(videoFile);
		videoFile = NULL;
	}
	if(videoCfgFile != NULL ){
		fclose(videoCfgFile);
		videoCfgFile = NULL;
	}
	
	pthread_cancel(tid_tmp);	
	pthread_join(tid_tmp,&ret);//等待线程2的返回状况，获取返回值
	if(ret==PTHREAD_CANCELED)
		return 0;			
	else{
		printf("thread return,id is:%ld,return code:NULL\n",tid_tmp);	
		return -1;
	}	
} 







