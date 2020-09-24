#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "zj_type.h"
#include "zj_log.h"
#include "zj_camera.h"  
//#include "zj_cameraiot.h"



#include "dev_zj_funReg.h"

#include "forZb_camera.h"  

#include "IPC_MediaBuff.h"
#include "sdk_commonstruct.h"
#include "sdkout_impl.h" 


static pthread_t tid_dev_audio = 0;

/*
//static unsigned char picSel;
static char *PcSnapPic = NULL;
static char *g_pbuf = NULL; 
static char *g_pbufCfg = NULL;
static FILE *videoFile = NULL;
static FILE *videoCfgFile = NULL; */
/*
void *lan_reader[2];

void add_stream(void){
	lan_reader[0] = IPC_MediaBuff_AddRead(0, 0, "tlib_m");
	lan_reader[1] = IPC_MediaBuff_AddRead(0, 0, "tlib_s");
} */
static void *dev_audio_loop(){

    int iDataLen;
    unsigned char *ucAudioData;
    unsigned int uiTimestamp;
//	unsigned char s_talk_data[2048] = {0};
	T_SDK_INTERCOM_DATA t_inercom_data;
	printf("enter loop_dev_audio");
	while(1){
		usleep(40000);
	//	printf("loop_dev_audio sleep");
		if(dj_audio_GtFTbl()->f_GtMediaAudioData == NULL){
			printf("f_GtMediaAudioData no register\n");
			continue;
		}

		if(stH_glget_audio()->iRun == 1){
			
#if 0
			if(stH_glget_audio()->openflag !=1){  
				stH_glget_audio()->openflag = 1;
				if(SDK_Cmd_Impl(SDKCMD_INTERCOM_START, NULL)){
					printf("AMBA_AUDIO_CreatTrdSocketAdec fail\n");
					continue;
				}			
			}
#endif
	        dj_audio_GtFTbl()->f_GtMediaAudioData(stH_glget_audio()->hPlayHandle, &ucAudioData, &iDataLen, &uiTimestamp);
	        if(iDataLen > 0)
	        {
			//	int retcode;
				
				memset(&t_inercom_data, 0, sizeof(T_SDK_INTERCOM_DATA));
				t_inercom_data.cp_data = ucAudioData;
				t_inercom_data.un_data_len = iDataLen;
	            printf("device audio recv voice data, size [%d] uiTimestamp[%u]\n", iDataLen, uiTimestamp);
			//	retcode = SDK_Cmd_Impl(SDKCMD_SEND_INTERCOM_DATA, &t_inercom_data);
				if(SDK_Cmd_Impl(SDKCMD_SEND_INTERCOM_DATA, &t_inercom_data) != 0)			
					printf("SDKCMD_SEND_INTERCOM_DATA faile\n");				
	        }

			
		}	
#if 0
		else{
			if(stH_glget_audio()->openflag !=0){
				stH_glget_audio()->openflag = 0;
				if(SDK_Cmd_Impl(SDKCMD_INTERCOM_STOP, NULL))				
					printf("AMBA_AUDIO_StopTrdSocketAdec fail\n");						
			}
		}
#endif
	}
	return 0;
}

int dev_audio_init(void){
	printf("dev_audio_init exe");

	if(SDK_Cmd_Impl(SDKCMD_INTERCOM_START, NULL))
	{
		printf("AMBA_AUDIO_CreatTrdSocketAdec fail\n");
		return -1;
	}
//	add_stream();
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

int dev_audio_start(void){
	printf("dev_audio_start exe");
	if(-1 == pthread_create(&tid_dev_audio, NULL, dev_audio_loop, NULL)){
		printf("create error!\n");
		return -1;
	}	
	return 0;
} 
int dev_audio_destory(void){
	void *ret;
	pthread_t tid_tmp = tid_dev_audio;
	printf("dev_audio_destory exe\n");
	
	
	pthread_cancel(tid_tmp);	
	pthread_join(tid_tmp,&ret);//等待线程2的返回状况，获取返回值
	if(ret==PTHREAD_CANCELED)
		return 0;			
	else{
		printf("thread return,id is:%ld,return code:NULL\n",tid_tmp);	
		return -1;
	}	
} 







