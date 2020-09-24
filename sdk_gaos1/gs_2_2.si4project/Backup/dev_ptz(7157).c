#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "devCfg.h"
#include "device_log.h"
#include "zj_type.h"
#include "zj_log.h"

#include "dev_zj_funReg.h"

#include "forZb_camera.h"  


#include "IPC_MediaBuff.h"
#include "sdk_commonstruct.h"
#include "sdkout_impl.h" 


static pthread_t tid_dev_iot = 0;


static void *dev_iot_loop(){
	
	DPRI_INFO("enter dev_iot_loop\n");
	while(1){
		usleep(70000000);
		DPRI_INFO("dev_iot_loop....\n");
	/*	if( NULL == dj_camIot_GtFTbl()->f_IoTEventInPut){
			DPRI_INFO("f_IoTEventInPut no register!\n");
			continue;			
		}		*/	
	//	dj_camIot_GtFTbl()->f_IoTEventInPut(EN_ZJ_AIIOT_TYPE_MOTION, 0, EN_ZJ_MOTION_EVENT_MOTION);//EN_ZJ_MOTION_EVENT_HUMAN

	}
	return 0;
}

int dev_iot_init(void){
	DPRI_INFO("dev_iot_init exe\n");
	return 0;	
} 

int dev_iot_start(void){
	DPRI_INFO("dev_audio_start exe\n");
	if(-1 == pthread_create(&tid_dev_iot, NULL, dev_iot_loop, NULL)){
		DPRI_INFO("create error!\n");
		return -1;
	}	
	return 0;
} 
int dev_iot_destory(void){
	void *ret;
	pthread_t tid_tmp = tid_dev_iot;
	DPRI_INFO("dev_iot_destory exe\n");	
	pthread_cancel(tid_tmp);	
	pthread_join(tid_tmp,&ret);//等待线程2的返回状况，获取返回值
	if(ret==PTHREAD_CANCELED)
		return 0;			
	else{
		DPRI_INFO("thread return,id is:%ld,return code:NULL\n",tid_tmp);	
		return -1;
	}	
} 







