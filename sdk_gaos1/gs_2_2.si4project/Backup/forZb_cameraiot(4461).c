#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#include <signal.h>
#include "basetypesJX.h" 

#include "cJSON.h"

#include "device_log.h"
#include "zj_type.h"
#include "zj_log.h"

#include "forZb_comCfg.h"
#include "forZb_camera.h"

#include "dev_zj_funReg.h"

#include "sdk_commonstruct.h"
#include "sdkout_impl.h" 

static pthread_t tid1_whiteLedPro = 0;

static u32 global_dura;

static int ctrlLed_white_ircut(u32 cmd,int para){
	if( !(para ==0|| para ==1) ){
		DPRI_INFO("ctrlLed_white_ircut para exceed\n");
		return -1;
	}	
	if(SDK_Cmd_Impl(cmd,(void *)&para) !=0 ){
		DPRI_INFO("SDK_Cmd_Impl ctrlLed_white_ircut err\n");
		return -1;
	}	
	return 0;	
}


int test_pthread_result(pthread_t tid) /*pthread_kill的返回值：成功（0） 线程不存在（ESRCH） 信号不合法（EINVAL）*/
{
	int pthread_kill_err;
	pthread_kill_err = pthread_kill(tid,0);

	if(pthread_kill_err == ESRCH){
	//	DPRI_INFO("ID为0x%x的线程不存在或者已经退出。\n",(unsigned int)tid);
		return -1;
	}
	else if(pthread_kill_err == EINVAL){
		DPRI_INFO("发送信号非法。\n");
		return -2;
	}
	else{
	//	DPRI_INFO("ID为0x%x的线程目前仍然存活。\n",(unsigned int)tid);
		return 0;
	}
}



void *pthread_WhiteLed(void *arg){
//	u32 *num;
//	num = (u32 *)arg;
//	u32 num_int = *num;
	u32 num_int = *((u32 *)arg);	
	DPRI_INFO("pthread_WhiteLed num:%d \n",num_int);
	while(--num_int != 0){
		sleep(1);
		if(num_int%5 == 0)
			DPRI_INFO("pthread_WhiteLed sleep:%d \n",num_int);
	}
	if(num_int == 0){
		DPRI_INFO("pthread_WhiteLed num == 0 \n");
		ctrlLed_white_ircut(SDKCMD_SET_WHITE_LED_STATUS,0);
	}
	return 0;
}
static int processWhiteLed(u8 ledswitch,u32 durationt){
	DPRI_INFO("processWhiteLed switch[%d],durationt[%d] \n",ledswitch,durationt);
	if(tid1_whiteLedPro != 0){
		if( 0 == test_pthread_result(tid1_whiteLedPro)){
		//	DPRI_INFO("tid1_whiteLedPro pthread exist\n");
			int ret = pthread_cancel(tid1_whiteLedPro);
			if(ret != 0){
				DPRI_INFO("fail to cancel\n");
				return -1;		
			}
			DPRI_INFO("tid1_whiteLedPro pthread_cancel exe\n");
		}else{
			DPRI_INFO("tid1_whiteLedPro pthread no exist\n");
		}
	}else{
		ctrlLed_white_ircut(SDKCMD_SET_WHITE_LED_STATUS,0);
		DPRI_INFO("tid1_whiteLedPro ==0,no require close\n");
	}	

	if(ledswitch == 0){
		ctrlLed_white_ircut(SDKCMD_SET_WHITE_LED_STATUS,0);
	}else if( durationt == 0){
		ctrlLed_white_ircut(SDKCMD_SET_WHITE_LED_STATUS,1);
	}else {
	//	u32 tempint = 5;
	//	u32 *pdura = &tempint;
		global_dura = durationt;
		ctrlLed_white_ircut(SDKCMD_SET_WHITE_LED_STATUS,1);
		pthread_create(&tid1_whiteLedPro,NULL,pthread_WhiteLed,(void *)&global_dura);
	}
	return 0;
}

/**********************红外灯相关注册函数*******************************/
/**
 * AIiOT 设备开始工作回调接口， 通过该接口启动AIIOT设备信号采集；
 */
int aiiot_dnset_start(unsigned int uiAIIoTType, unsigned long long uiAIIoTID)
{
    /**
     * 启动IOT
     */
    DPRI_INFO("aiiot_dnset_start, aiiot type [%d] aiiot id [%llu] \n", uiAIIoTType, uiAIIoTID);
    return 0;
}


/**
 * AIiOT 设备停止工作回调接口， 通过该接口通知设备停止信号采集；
 */
int aiiot_dnset_stop(unsigned int uiAIIoTType, unsigned long long lluAIIoTID)
{
     /**
     * 停止IOT
     */
    DPRI_INFO("aiiot_dnset_stop, aiiot type [%d] aiiot id [%llu] \n", uiAIIoTType, lluAIIoTID);
    return 0;
}



/**
 * 向AIiOT 设备输出信号回调接口，通过该接口，将输出信号类型和对应的JSON描述字符串输出到AIiOT设备；
 */
int aiiot_dnset_output(unsigned int uiAIIoTType, unsigned long long uiAIIoTID, unsigned char* pSignalValue,ST_ZJ_TRIGGER_INFO* pstTriggerInf)
{
    /**
     * 控制信息一般json格式通过pSignalValue传递下来，需要对接厂商解析并设置
     */
    DPRI_INFO("aiiot_dnset_output, aiiot type [%d] aiiot id [%llu] \n", uiAIIoTType, uiAIIoTID);
    DPRI_INFO("Signal Value: %s ", pSignalValue ==NULL ? (unsigned char*)"nil":pSignalValue);

	if(pSignalValue == NULL)
		return -1;	
	cJSON *cjson = cJSON_Parse((char *)pSignalValue); 
	if(cjson == NULL){
		DPRI_INFO("json pack into cjson error...\n");
		return -1;
	}
	cJSON *json_status =  cJSON_GetObjectItem(cjson, "CtrlType");	
	DPRI_INFO("CtrlType:%s---prase", json_status->valuestring);	
	int num =atoi(json_status->valuestring);
//	int durationT = 30;
	DPRI_INFO("num:%d---atoi", num);
	ctrlLed_white_ircut(SDKCMD_SET_IRCUT_LED_STATUS,num);			
	return 0;	

}
/*********************************end********************************/


/**********************红外灯相关注册函数*******************************/
/**
 * AIiOT 设备开始工作回调接口， 通过该接口启动AIIOT设备信号采集；
 */
int aiiot_inner_start(unsigned int uiAIIoTType, unsigned long long uiAIIoTID)
{
    /**
     * 启动IOT
     */
    DPRI_INFO("aiiot_inner_start, aiiot type [%d] aiiot id [%llu] \n", uiAIIoTType, uiAIIoTID);
    return 0;
}


/**
 * AIiOT 设备停止工作回调接口， 通过该接口通知设备停止信号采集；
 */
int aiiot_inner_stop(unsigned int uiAIIoTType, unsigned long long lluAIIoTID)
{
     /**
     * 停止IOT
     */
    DPRI_INFO("aiiot_inner_stop, aiiot type [%d] aiiot id [%llu] \n", uiAIIoTType, lluAIIoTID);
    return 0;
}



/**
 * 向AIiOT 设备输出信号回调接口，通过该接口，将输出信号类型和对应的JSON描述字符串输出到AIiOT设备；
 */
int aiiot_inner_output(unsigned int uiAIIoTType, unsigned long long uiAIIoTID, unsigned char* pSignalValue,ST_ZJ_TRIGGER_INFO* pstTriggerInf)
{
    /**
     * 控制信息一般json格式通过pSignalValue传递下来，需要对接厂商解析并设置
     */
    int durationT = 0;
    DPRI_INFO("aiiot_inner_output, aiiot type [%d] aiiot id [%llu]\n", uiAIIoTType, uiAIIoTID);
    DPRI_INFO("Signal Value: %s \n", pSignalValue ==NULL ? (unsigned char*)"nil":pSignalValue);
	if(pSignalValue == NULL)
		return -1;	
	cJSON *cjson = cJSON_Parse((char *)pSignalValue); 
	if(cjson == NULL){
			DPRI_INFO("json pack into cjson error...\n");
			return -1;
	}
	cJSON *json_status =  cJSON_GetObjectItem(cjson, "CtrlType");	
//	DPRI_INFO("CtrlType:%s---prase\n", json_status->valuestring);
	int num =atoi(json_status->valuestring);
	
	cJSON *json_duration =  cJSON_GetObjectItem(cjson, "Duration");	
	if( json_duration == NULL){
		DPRI_INFO("durationT = 0\n");
		durationT = 0;
	}else{
//		DPRI_INFO("Duration:%s---prase\n", json_duration->valuestring);
		durationT =atoi(json_duration->valuestring);
	}		
//	int durationT = 30;
	processWhiteLed(num,durationT);
//	DPRI_INFO("num:%d-durationT:%d--atoi\n", num,durationT);	
//	ctrlLed_white_ircut(SDKCMD_SET_WHITE_LED_STATUS,num);			
	return 0;

}

/**
 * 向AIIoT设备设置属性回调接口，通过该接口，将新的属性值设置给AIIoT设备，让设备以设置的属性值进行工作；属性以一个JSON字符串传递；
 * 
 * 注意：json解析使用的是cJson仅供参考
 */
int aiiot_motion_setprop(unsigned int uiAIIoTType, unsigned long long uiAIIoTID, unsigned char* pstProp)
{
    /**
     * EN_ZJ_AIIOT_TYPE_MOTION中
     * 注意：运动侦测iot包含，移动侦测、人形侦测、人脸识别三种事件类型，每一种事件类型都可以配置
     * 格式如下以移动侦测为例：
     * json格式（需要对接厂商自己解析，取出对应的值并设置）：
     *          {"Motion":{"Interval":"30","Sensitive":"25","Status":"0","Trace":"0"}}
     * Interval     时间间隔
     * Sensitive    灵敏度 低25 中50 高75
     * Status       开启状态
     * Trace        是否开启自动追踪
     */


	DPRI_INFO("motion_setprop, aiiot type [%d] aiiot id [%llu],pstProp:%s\n", uiAIIoTType, uiAIIoTID,pstProp);
	
/*	
    int iInterval = 0;
    int iSensitive = 0;
    int iStatus = 0;
    int iTrace = 0;
    cJSON *cProp = NULL;
    cJSON *cMotion = NULL;
    cJSON *cHuman = NULL;
    if((pstProp == NULL)|| (strlen((char*)pstProp) <= 0))
    {
        __ERROR_PRINTF("device aiiot set prop failed\n");
        return -1;
    }
    cProp = cJSON_Parse((char*)pstProp);
    if(cProp == NULL)
    {
        __ERROR_PRINTF("device aiiot set prop failed, json prase err\n");
        return -1;
    }
    cMotion = cJSON_GetObjectItem(cProp, "Motion");
    if(cMotion != NULL)
    {
        if(GetIntegerValue(cJSON_GetObjectItem(cMotion,"Interval"), &iInterval)==0)
        {
            g_StIotMng.stMotion.iInterval = iInterval;
            g_StIotMng.stHuman.iInterval = iInterval;
        }
        if(GetIntegerValue(cJSON_GetObjectItem(cMotion,"Sensitive"), &iSensitive) == 0)
        {
            g_StIotMng.stMotion.iSensitive = iSensitive;
            g_StIotMng.stHuman.iSensitive = iSensitive;
        }
        if(GetIntegerValue(cJSON_GetObjectItem(cMotion,"Status"), &iStatus)==0)
        {
            g_StIotMng.stMotion.iStatus = iStatus;
        }
        if(GetIntegerValue(cJSON_GetObjectItem(cMotion,"Trace"), &iTrace) == 0)
        {
            g_StIotMng.stMotion.iTrace = iTrace;
        }
        __INFO_PRINTF("device aiiot set prop, aiiot type [%d] aiiot id [%llu]:\n", uiAIIoTType, uiAIIoTID);
        __INFO_PRINTF("                                              Interval: [%d]\n", g_StIotMng.stHuman.iInterval);
        __INFO_PRINTF("                                             Sensitive: [%d]\n", g_StIotMng.stHuman.iSensitive);
        __INFO_PRINTF("                                                Status: [%d]\n", g_StIotMng.stHuman.iStatus);
        __INFO_PRINTF("                                                 Trace: [%d]\n", g_StIotMng.stHuman.iTrace);
    }

    cHuman = cJSON_GetObjectItem(cProp, "Motion");
    if(cHuman != NULL)
    {
        if(GetIntegerValue(cJSON_GetObjectItem(cMotion,"Interval"), &iInterval)==0)
        {
            g_StIotMng.stMotion.iInterval = iInterval;
            g_StIotMng.stHuman.iInterval = iInterval;
        }
        if(GetIntegerValue(cJSON_GetObjectItem(cMotion,"Sensitive"), &iSensitive) == 0)
        {
            g_StIotMng.stMotion.iSensitive = iSensitive;
            g_StIotMng.stHuman.iSensitive = iSensitive;
        }
        if(GetIntegerValue(cJSON_GetObjectItem(cMotion,"Status"), &iStatus)==0)
        {
            g_StIotMng.stHuman.iStatus = iStatus;
        }
        if(GetIntegerValue(cJSON_GetObjectItem(cMotion,"Trace"), &iTrace) == 0)
        {
            g_StIotMng.stHuman.iTrace = iTrace;
        }
        __INFO_PRINTF("device aiiot set prop, aiiot type [%d] aiiot id [%llu]:\n", uiAIIoTType, uiAIIoTID);
        __INFO_PRINTF("                                              Interval: [%d]\n", g_StIotMng.stHuman.iInterval);
        __INFO_PRINTF("                                             Sensitive: [%d]\n", g_StIotMng.stHuman.iSensitive);
        __INFO_PRINTF("                                                Status: [%d]\n", g_StIotMng.stHuman.iStatus);
        __INFO_PRINTF("                                                 Trace: [%d]\n", g_StIotMng.stHuman.iTrace);
    }
    
    __INFO_PRINTF("device aiiot set prop, aiiot type [%d] aiiot id [%llu] \n", uiAIIoTType, uiAIIoTID);
    __INFO_PRINTF("prop: %s\n", pstProp);  */
    return 0;
}














