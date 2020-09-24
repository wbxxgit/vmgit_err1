#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "cJSON.h"

#include "zj_type.h"
#include "zj_log.h"

#include "forZb_comCfg.h"
#include "forZb_camera.h"

#include "dev_zj_funReg.h"

#include "sdk_commonstruct.h"
#include "sdkout_impl.h" 

//#include "forZbSeg_camera.h" 



static int ctrlLed_white_ircut(u32 cmd,int para){
	if( !(para ==0|| para ==1) ){
		ZJ_LOG_INF("ctrlLed_white_ircut para exceed\n");
		return -1;
	}	
	if(SDK_Cmd_Impl(cmd,(void *)&para) !=0 ){
		ZJ_LOG_INF("SDK_Cmd_Impl ctrlLed_white_ircut err\n");
		return -1;
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
    ZJ_LOG_INF("aiiot_dnset_start, aiiot type [%d] aiiot id [%llu] \n", uiAIIoTType, uiAIIoTID);
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
    ZJ_LOG_INF("aiiot_dnset_stop, aiiot type [%d] aiiot id [%llu] \n", uiAIIoTType, lluAIIoTID);
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
    ZJ_LOG_INF("aiiot_dnset_output, aiiot type [%d] aiiot id [%llu] \n", uiAIIoTType, uiAIIoTID);
    ZJ_LOG_INF("Signal Value: %s \n", pSignalValue ==NULL ? (unsigned char*)"nil":pSignalValue);

	if(pSignalValue == NULL)
		return -1;	
	cJSON *cjson = cJSON_Parse((char *)pSignalValue); 
	if(cjson == NULL){
			ZJ_LOG_INF("json pack into cjson error...\n");
			return -1;
	}
	cJSON *json_status =  cJSON_GetObjectItem(cjson, "CtrlType");	
	ZJ_LOG_INF("CtrlType:%s---prase\n", json_status->valuestring);	
	int num =atoi(json_status->valuestring);	
	ZJ_LOG_INF("num:%d---atoi\n", num);
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
    ZJ_LOG_INF("aiiot_inner_start, aiiot type [%d] aiiot id [%llu] \n", uiAIIoTType, uiAIIoTID);
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
    ZJ_LOG_INF("aiiot_inner_stop, aiiot type [%d] aiiot id [%llu] \n", uiAIIoTType, lluAIIoTID);
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
    ZJ_LOG_INF("aiiot_inner_output, aiiot type [%d] aiiot id [%llu]", uiAIIoTType, uiAIIoTID);
    ZJ_LOG_INF("Signal Value: %s ", pSignalValue ==NULL ? (unsigned char*)"nil":pSignalValue);
	if(pSignalValue == NULL)
		return -1;	
	cJSON *cjson = cJSON_Parse((char *)pSignalValue); 
	if(cjson == NULL){
			ZJ_LOG_INF("json pack into cjson error...\n");
			return -1;
	}
	cJSON *json_status =  cJSON_GetObjectItem(cjson, "CtrlType");	
	ZJ_LOG_INF("CtrlType:%s---prase", json_status->valuestring);	
	int num =atoi(json_status->valuestring);	
	ZJ_LOG_INF("num:%d---atoi", num);
	ctrlLed_white_ircut(SDKCMD_SET_WHITE_LED_STATUS,num);			
	return 0;

}














