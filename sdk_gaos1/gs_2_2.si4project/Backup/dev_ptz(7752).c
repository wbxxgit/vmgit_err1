#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "basetypesJX.h"

#include "devCfg.h"
#include "device_log.h"
#include "zj_type.h"
#include "zj_log.h"

#include "dev_zj_funReg.h"

#include "forZb_camera.h"  


#include "IPC_MediaBuff.h"
#include "sdk_commonstruct.h"
#include "sdkout_impl.h" 

#include "dev_network.h" 
#include "ptz_queue.h" 


#define PIECE_EXETIME 200000   //400ms

static pthread_t tid_ptz_iot = 0;

static Queue que_rotateCmd;
static u8 exe_state = 0;


static u8 rotateState = 0; 


static int dev_ptz_setRotate(EN_ZJ_CAMERA_PTZ_CONTROL direction){
	long tmpcmd;
	switch (direction)
		{
		case EN_ZJ_CAMERA_PTZ_CONTROL_LEFT:
			tmpcmd = SDKCMD_SET_PTZ_KEEP_LEFT;
			break;
		case EN_ZJ_CAMERA_PTZ_CONTROL_RIGHT:
			tmpcmd = SDKCMD_SET_PTZ_KEEP_RIGHT;
			break;
		case EN_ZJ_CAMERA_PTZ_CONTROL_UP:
			tmpcmd = SDKCMD_SET_PTZ_KEEP_UP;
			break;
		case EN_ZJ_CAMERA_PTZ_CONTROL_DOWN:
			tmpcmd = SDKCMD_SET_PTZ_KEEP_DOWN;
			break;		
		default:tmpcmd = -1;break;			
		}
	if(tmpcmd == -1)
		return -1;	
	int retcode = SDK_Cmd_Impl(tmpcmd, NULL);
	if(retcode != 0)
	{
		DPRI_INFO("SDKCMD_SET_PTZ_TURN_LEFT tmpcmd error\n");
		return -1;
	}	
	DPRI_INFO("dev_ptz_setRotate exe:%d\n",direction);
	return 0;
}

static int dev_ptz_stopRotate(){	
	int retcode = SDK_Cmd_Impl(SDKCMD_SET_PTZ_STOP, NULL);  //SDKCMD_SET_PTZ_STOP
	if(retcode != 0)
	{
		DPRI_INFO("SDKCMD_SET_RECORD_DEFAULT_PARAM error\n");
		return -1;
	}
	DPRI_INFO("dev_ptz_stopRotate exe\n");
	return 0;
}


static int dev_checkOrProcess(){

	if( (exe_state == 0)&&( QueueEmpty(&que_rotateCmd) == 1 )){
		DPRI_INFO("double is empty\n");
		return 0;
	}
	if( QueueEmpty(&que_rotateCmd) == 1 ){
		exe_state = 0;
		//stop exe
		dev_ptz_stopRotate();
		DPRI_INFO("only queueIsEmpty is 0,stoped action\n");		
		return 0;		
	}
	//que is not empty
	//get val
	//	u8 getval;
	u8 getval = (u8)QueueFront(&que_rotateCmd);
	QueuePop(&que_rotateCmd);	
	
	if(getval == 0){
		DPRI_INFO("getval is 0,queer\n");
		return -1;
	}	
	
	if( getval != exe_state ){  // is different
		exe_state = getval;
		//close action
		//exe action
		dev_ptz_stopRotate();
		usleep(30000);
		dev_ptz_setRotate(exe_state);
		DPRI_INFO("switch the action:%d\n",exe_state);
	}else{//is same ,
		DPRI_INFO("is same,nothing to do:%d\n",exe_state);
	} 
	return 0;	

/*	if(  (rotateState_last == 0)&&( rotateState == 0))
		return -1;

	DPRI_INFO("dev_checkOrProcess,rotateState:%d,rotateState_last:%d\n",rotateState,rotateState_last);
	if(rotateState_last != rotateState){

		if(rotateState_last == 0){
			dev_ptz_setRotate(rotateState);
		}else if(rotateState == 0){
			dev_ptz_stopRotate();
		}else {
			dev_ptz_stopRotate();
			dev_ptz_setRotate(rotateState);
		}
		rotateState_last = rotateState;			
	}else{
		if(rotateState_last !=0)
			dev_ptz_setRotate(rotateState_last);
	}
	rotateState = 0;	
	return 0;  */
}

/*
int devd_PTZrotate(EN_ZJ_CAMERA_PTZ_CONTROL direction,u32 durationMs){

	if(durationMs > 4000)
		return -1;
	int retcode = 0;
	long tmpcmd;
	switch (direction)
		{
		case EN_ZJ_CAMERA_PTZ_CONTROL_LEFT:
			tmpcmd = SDKCMD_SET_PTZ_KEEP_LEFT;
			break;
		case EN_ZJ_CAMERA_PTZ_CONTROL_RIGHT:
			tmpcmd = SDKCMD_SET_PTZ_KEEP_RIGHT;
			break;
		case EN_ZJ_CAMERA_PTZ_CONTROL_UP:
			tmpcmd = SDKCMD_SET_PTZ_KEEP_UP;
			break;
		case EN_ZJ_CAMERA_PTZ_CONTROL_DOWN:
			tmpcmd = SDKCMD_SET_PTZ_KEEP_DOWN;
			break;		
		default:tmpcmd = -1;break;			
		}
	if(tmpcmd == -1)
		return -1;
	
	retcode = SDK_Cmd_Impl(tmpcmd, NULL);
	if(retcode != 0)
	{
		DPRI_INFO("SDKCMD_SET_PTZ_TURN_LEFT tmpcmd error\n");
		return -1;
	}
	usleep(durationMs*1000);
	retcode = SDK_Cmd_Impl(SDKCMD_SET_PTZ_STOP, NULL);
	if(retcode != 0)
	{
		DPRI_INFO("SDKCMD_SET_RECORD_DEFAULT_PARAM error\n");
		return -1;
	}
	DPRI_INFO("dev_PTZrotate exe\n");
	return 0;
} */


static void *dev_ptz_loop(){
	
	DPRI_INFO("enter dev_ptz_loop\n");

	DPRI_INFO("devd_PTZrotate test begin\n");
//	dev_ptz_setRotate(1);

	if (0 != SDK_Cmd_Impl(SDKCMD_SET_PTZ_KEEP_LEFT, NULL))
	{
	   printf("call SDKCMD_SET_PTZ_TURN_LEFT fail .\n");           
	  // return -1;
	} 		
	usleep(4500000);
//	if (0 != SDK_Cmd_Impl(SDKCMD_SET_PTZ_STOP, NULL))
	{
//	   printf("call SDKCMD_SET_PTZ_TURN_LEFT fail .\n");           
	  // return -1;
	} 		

	if (0 != SDK_Cmd_Impl(SDKCMD_SET_PTZ_KEEP_RIGHT, NULL))
	{
	   printf("call SDKCMD_SET_PTZ_TURN_LEFT fail .\n");           
	  // return -1;
	} 		
	usleep(4500000);
//	if (0 != SDK_Cmd_Impl(SDKCMD_SET_PTZ_STOP, NULL))
	{
//	   printf("call SDKCMD_SET_PTZ_TURN_LEFT fail .\n");           
	  // return -1;
	} 		
	if (0 != SDK_Cmd_Impl(SDKCMD_SET_PTZ_KEEP_DOWN, NULL))
	{
	   printf("call SDKCMD_SET_PTZ_TURN_LEFT fail .\n");		   
	  // return -1;
	}		
	usleep(4500000);
//	if (0 != SDK_Cmd_Impl(SDKCMD_SET_PTZ_STOP, NULL))
	{
//	   printf("call SDKCMD_SET_PTZ_TURN_LEFT fail .\n");		   
	  // return -1;
	}	

	if (0 != SDK_Cmd_Impl(SDKCMD_SET_PTZ_KEEP_UP, NULL))
	{
	   printf("call SDKCMD_SET_PTZ_TURN_LEFT fail .\n");           
	  // return -1;
	} 		
	usleep(4500000);
	if (0 != SDK_Cmd_Impl(SDKCMD_SET_PTZ_STOP, NULL))
	{
	   printf("call SDKCMD_SET_PTZ_TURN_LEFT fail .\n");           
	  // return -1;
	} 		
//	dev_ptz_stopRotate();
//	dev_ptz_setRotate(2);
//	usleep(4500000);
//	dev_ptz_stopRotate();
//	devd_PTZrotate(1,4500);
//	devd_PTZrotate(2,4500);
//	devd_PTZrotate(3,4500);
//	devd_PTZrotate(4,4500);
	DPRI_INFO("devd_PTZrotate test over\n");
	
	while(1){
		usleep(PIECE_EXETIME);
	//	DPRI_INFO("dev_ptz_loop....\n");
		dev_checkOrProcess();		
		
	/*	if( NULL == dj_camIot_GtFTbl()->f_IoTEventInPut){
			DPRI_INFO("f_IoTEventInPut no register!\n");
			continue;			
		}		*/	
	//	dj_camIot_GtFTbl()->f_IoTEventInPut(EN_ZJ_AIIOT_TYPE_MOTION, 0, EN_ZJ_MOTION_EVENT_MOTION);//EN_ZJ_MOTION_EVENT_HUMAN

	}
	return 0;
}

int dev_ptz_init(void){
	DPRI_INFO("dev_iot_init exe\n");
	QueueInit(&que_rotateCmd);
	return 0;	
} 

int dev_ptz_start(void){
	DPRI_INFO("dev_ptz_start exe\n");
	if(-1 == pthread_create(&tid_ptz_iot, NULL, dev_ptz_loop, NULL)){
		DPRI_INFO("create error!\n");
		return -1;
	}	
	return 0;
} 
int dev_ptz_destory(void){
	void *ret;
	pthread_t tid_tmp = tid_ptz_iot;
	DPRI_INFO("dev_ptz_destory exe\n");	

	QueueDestory(&que_rotateCmd);
	pthread_cancel(tid_tmp);	
	pthread_join(tid_tmp,&ret);//等待线程2的返回状况，获取返回值
	if(ret==PTHREAD_CANCELED)
		return 0;			
	else{
		DPRI_INFO("thread return,id is:%ld,return code:NULL\n",tid_tmp);	
		return -1;
	}	
} 



void dev_pushRotateCmd(int v){
	QueuePush(&que_rotateCmd,v);
}


int dev_setRotateSta(EN_ZJ_CAMERA_PTZ_CONTROL orien){
	rotateState = orien;
	return 0;
}


