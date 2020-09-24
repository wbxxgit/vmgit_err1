
#include "dev_alarm.h"
#include "dev_audio.h"
#include "dev_iot.h"
#include "dev_systemSup.h"




int dev_all_init(){
	dev_audio_init();
	dev_iot_init();
	dev_systemSup_init();

	return 0;
}

int dev_all_statr(){
	dev_audio_start();
	dev_iot_start();
	dev_systemSup_start();

	return 0;
}

int dev_all_destory(){
	dev_audio_destory();
	dev_iot_destory();	
	dev_systemSup_destory();

	return 0;
}







/*

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "devCfg.h"
#include "zj_type.h"
#include "zj_log.h"

#include "dev_zj_funReg.h"

#include "forZb_camera.h"  


#include "IPC_MediaBuff.h"
#include "sdk_commonstruct.h"
#include "sdkout_impl.h" 


static pthread_t tid_dev_iot = 0;


static void *dev_iot_loop(){
	
	printf("enter dev_iot_loop\n");
	while(1){
		usleep(70000000);
		printf("dev_iot_loop....\n");

	//	dj_camIot_GtFTbl()->f_IoTEventInPut(EN_ZJ_AIIOT_TYPE_MOTION, 0, EN_ZJ_MOTION_EVENT_MOTION);//EN_ZJ_MOTION_EVENT_HUMAN

	}
	return 0;
}

int dev_iot_init(void){
	printf("dev_iot_init exe\n");
	return 0;	
} 

int dev_iot_start(void){
	printf("dev_audio_start exe\n");
	if(-1 == pthread_create(&tid_dev_iot, NULL, dev_iot_loop, NULL)){
		printf("create error!\n");
		return -1;
	}	
	return 0;
} 
int dev_iot_destory(void){
	void *ret;
	pthread_t tid_tmp = tid_dev_iot;
	printf("dev_iot_destory exe\n");	
	pthread_cancel(tid_tmp);	
	pthread_join(tid_tmp,&ret);//等待线程2的返回状况，获取返回值
	if(ret==PTHREAD_CANCELED)
		return 0;			
	else{
		printf("thread return,id is:%ld,return code:NULL\n",tid_tmp);	
		return -1;
	}	
} 
 */






