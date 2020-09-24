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

	
	printf("enter video_loop\n");
	while(1){
		usleep(4000000);
	//	printf("video_loop......\n");	

	}
	return 0;
}

int testD_video_init(void){
	printf("testD_video_init exe");
	printf("Video Init OK\n");

	add_stream();

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




