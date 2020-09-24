#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "zj_type.h"
#include "zj_log.h"
#include "zj_cameraiot.h" 

#include "ZJre_comCfg.h" 
#include "forZb_camera.h"  //
#include "forZb_cameraiot.h"  


typedef struct stru_STRE_CAMERAIOT_MSG{
	unsigned int LoopFlag;
	unsigned int FullFlag;
	unsigned int StreamId;

}STRE_CAMERAIOT_MSG;


typedef struct stru_STRE_CAMERAIOT_EVENT_MSG{

	unsigned int AIIoTType;
	unsigned long long AIIoTID;

	ZJ_PFUN_AIIOT_START pfAIIoTStart;
	ZJ_PFUN_AIIOT_STOP pfAIIoTStop;
	ZJ_PFUN_AIIOT_GETINPUT pfAIIoTGetInput;
	ZJ_PFUN_AIIOT_OUTPUT pfAIIoTOutPut;
	ZJ_PFUN_AIIOT_SETPROP pfAIIoTSetProp;
	ZJ_PFUN_AIIOT_CHECKEVENT pfAIIotCheckEvent;

	unsigned int EventId;
	unsigned int TraceFlag;
	unsigned int Senstive;
	
	unsigned int OpenFlag;
	unsigned int RecordFlag;
	unsigned int SnapFlag;
	unsigned int EventFlag;
	
	unsigned int Duration;
	char *prop_char;

}STRE_CAMERAIOT_EVENT_MSG;


static STRE_CAMERAIOT_MSG  g_ST_cameraiot_msg = {0};
/*
static STRE_CAMERAIOT_EVENT_MSG  g_ST_cameraiot_eventArr_msg_c1[] = 
{
	{EN_ZJ_AIIOT_TYPE_INNER_DOORBELL,0,NULL,NULL,NULL,NULL,NULL,NULL,1,1,1,  1,1,1,30},
	{EN_ZJ_AIIOT_TYPE_STAY,0,NULL,NULL,NULL,NULL,NULL,NULL,1,1,1,  1,1,1,30},
	{EN_ZJ_AIIOT_TYPE_FORCEREMOVE,0,NULL,NULL,NULL,NULL,NULL,NULL,1,1,1,  1,1,1,30},
	{EN_ZJ_AIIOT_TYPE_INNER_PIR,0,NULL,NULL,NULL,NULL,NULL,NULL,1,1,1,  1,1,1,30},
}; */

#define IOT_PROP_STR_MOTION   "{\"Motion\":{\"Sensitive\":\"20\",\"Status\":\"0\",\"Trace\":\"0\",\"Interval\":\"30\"},\
\"Human\":{\"Sensitive\":\"20\",\"Status\":\"0\",\"Trace\":\"0\",\"Interval\":\"30\"}}"

static STRE_CAMERAIOT_EVENT_MSG  g_ST_cameraiot_eventArr_msg[] = 
{
	{EN_ZJ_AIIOT_TYPE_MOTION,0,NULL,NULL,NULL,NULL,NULL,NULL,EN_ZJ_MOTION_EVENT_MOTION,1,1 ,1,1,1,1,30, IOT_PROP_STR_MOTION},
	{EN_ZJ_AIIOT_TYPE_DNSET,0,aiiot_dnset_start,aiiot_dnset_stop,NULL,aiiot_dnset_output,NULL,NULL,0,1,1 ,1,1,1,1,30, NULL},
	{EN_ZJ_AIIOT_TYPE_INNER_LAMP,0,aiiot_inner_start,aiiot_inner_stop,NULL,aiiot_inner_output,NULL,NULL,0,1,1 ,1,1,1,1,30, NULL},

};



static int member_init(STRE_CAMERAIOT_MSG *p_cam){

	p_cam->LoopFlag = 0;
	p_cam->FullFlag = 0;
	p_cam->StreamId = 0;
	return 0;
}

static int configure_init(STRE_CAMERAIOT_MSG *pcam){
	ZJ_SetDefaultRecordProp(pcam->LoopFlag, pcam->FullFlag, pcam->StreamId);
	ZJ_SetDefaultRecordProp(pcam->LoopFlag, pcam->FullFlag, 1);
	return 0;
}

static int cbfun_register(void){

	return 0;
}

static int eventArray_init(STRE_CAMERAIOT_EVENT_MSG *eventArr,unsigned char ArrLen){
	unsigned char i;
	int rett;
	for (i = 0; i < ArrLen; ++i){
		printf("1838_(eventArr+i)->AIIoTType:%d\n",(eventArr+i)->AIIoTType);
		
		rett = ZJ_AddIoTDevice((eventArr+i)->AIIoTType, (eventArr+i)->AIIoTID,
						(eventArr+i)->pfAIIoTStart,(eventArr+i)->pfAIIoTStop, (eventArr+i)->pfAIIoTGetInput, 
						(eventArr+i)->pfAIIoTOutPut, (eventArr+i)->pfAIIoTSetProp, (eventArr+i)->pfAIIotCheckEvent); 

		printf("rett :%d AIIoTType:%u,AIIoTID:%llu\n",rett,(eventArr+i)->AIIoTType, (eventArr+i)->AIIoTID);
		ZJ_SetIoTDefaultProp(EN_ZJ_AIIOT_TYPE_MOTION, 0, (eventArr+i)->prop_char);
		ZJ_SetIotDefaultPolicy((eventArr+i)->AIIoTType,(eventArr+i)->OpenFlag,
			(eventArr+i)->EventId,(eventArr+i)->TraceFlag,(eventArr+i)->Senstive,
			(eventArr+i)->RecordFlag,(eventArr+i)->SnapFlag,(eventArr+i)->EventFlag,(eventArr+i)->Duration);	


		printf("show para AIIoTType:%d ,OpenFlag:%d ,EventId:%d ,TraceFlag:%d ,   Senstive:%d ,RecordFlag:%d ,SnapFlag:%d ,EventFlag:%d ,Duration:%d ,\n",
			(eventArr+i)->AIIoTType,(eventArr+i)->OpenFlag, 
			(eventArr+i)->EventId,(eventArr+i)->TraceFlag,(eventArr+i)->Senstive,
			(eventArr+i)->RecordFlag,(eventArr+i)->SnapFlag,(eventArr+i)->EventFlag,(eventArr+i)->Duration);	
	}
	return 0;
}



int zjre_cameraiotInit(void){
	member_init(&g_ST_cameraiot_msg);
	configure_init(&g_ST_cameraiot_msg);
	cbfun_register();
	eventArray_init(g_ST_cameraiot_eventArr_msg,sizeof(g_ST_cameraiot_eventArr_msg)/sizeof(STRE_CAMERAIOT_EVENT_MSG));
	return 0;
}








