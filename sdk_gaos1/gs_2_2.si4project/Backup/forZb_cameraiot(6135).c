#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#include "zj_type.h"
#include "zj_log.h"

#include "forZb_comCfg.h"
#include "forZb_camera.h"

#include "dev_zj_funReg.h"

#include "sdk_commonstruct.h"
#include "sdkout_impl.h" 

//#include "forZbSeg_camera.h" 





/**********************红外灯相关注册函数*******************************/
/**
 * AIiOT 设备开始工作回调接口， 通过该接口启动AIIOT设备信号采集；
 */
int aiiot_dnset_start(unsigned int uiAIIoTType, unsigned long long uiAIIoTID)
{
    /**
     * 启动IOT
     */
    ZJ_LOG_INF("device aiiot start, aiiot type [%d] aiiot id [%llu] \n", uiAIIoTType, uiAIIoTID);
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
    ZJ_LOG_INF("device aiiot stop, aiiot type [%d] aiiot id [%llu] \n", uiAIIoTType, lluAIIoTID);
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
    ZJ_LOG_INF("device aiiot output, aiiot type [%d] aiiot id [%llu] \n", uiAIIoTType, uiAIIoTID);
    ZJ_LOG_INF("Signal Value: %s \n", pSignalValue ==NULL ? (unsigned char*)"nil":pSignalValue);
    if(pstTriggerInf!= NULL)
    {
        ZJ_LOG_INF(" trigger info: \n");
        ZJ_LOG_INF("    uiIotType: %u\n",    pstTriggerInf->uiIotType);
        ZJ_LOG_INF("     lluIotId: %llu\n",  pstTriggerInf->lluIotId);
        ZJ_LOG_INF("    uiEventId: %u\n",    pstTriggerInf->uiEventId);
        ZJ_LOG_INF("   uiDuration: %u\n",    pstTriggerInf->uiDuration);
        ZJ_LOG_INF("  tCreateTime: %lu\n",   pstTriggerInf->tCreateTime);
        ZJ_LOG_INF("   pstHandler: %p\n",    pstTriggerInf->pstHandler);
    }

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
    ZJ_LOG_INF("device aiiot start, aiiot type [%d] aiiot id [%llu] \n", uiAIIoTType, uiAIIoTID);
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
    ZJ_LOG_INF("device aiiot stop, aiiot type [%d] aiiot id [%llu] \n", uiAIIoTType, lluAIIoTID);
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
    ZJ_LOG_INF("device aiiot output, aiiot type [%d] aiiot id [%llu] \n", uiAIIoTType, uiAIIoTID);
    ZJ_LOG_INF("Signal Value: %s \n", pSignalValue ==NULL ? (unsigned char*)"nil":pSignalValue);
    ZJ_LOG_INF(" trigger info: \n");
    ZJ_LOG_INF("    uiIotType: %u\n", pstTriggerInf->uiIotType);
    ZJ_LOG_INF("     lluIotId: %llu\n", pstTriggerInf->lluIotId);
    ZJ_LOG_INF("    uiEventId: %u\n", pstTriggerInf->uiEventId);
    ZJ_LOG_INF("   uiDuration: %u\n", pstTriggerInf->uiDuration);
    ZJ_LOG_INF("  tCreateTime: %lu\n", pstTriggerInf->tCreateTime);
    ZJ_LOG_INF("   pstHandler: %p\n", pstTriggerInf->pstHandler);

    return 0;
}
/*********************************end********************************/


















