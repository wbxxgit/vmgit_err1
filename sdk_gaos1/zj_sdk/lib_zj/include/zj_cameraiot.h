#ifndef _ZJ_CAMERAIOT_H_
#define _ZJ_CAMERAIOT_H_
/**
 ** 定义跟摄像头设备相关的IoT事件能力，如：图形侦测报警、声音报警、设备指示灯控制、蜂鸣器控制、本地录制
 **/

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************************
1 添加一个IoT设备，一起设置的是该设备的工作开始/工作结束/获取输入信号/输出信号的回调函数；
2 如果是控制器 ， 比如蜂鸣器 ， 则不需要注册 start 和 stop 函数,默认开启就行
3 如果是报警器: 比如motion: 需要注册 start stop  pfunAIIoTSetProp , 然后可以调用 ZJ_IoTEventInPut 输出信号
*******************************************************************************************/
/********************************************************************************
1 移动侦测: 
prop: json 串: {"Motion":{"Sensitive":"","Status":"","Trace":"","Interval","ActiveTime":"持续时长"},
                "Human":{"Sensitive":"","Status":"","Trace":"","Interval","MaxCount","ActiveTime":"持续时长"},
                "Face":{"Sensitive":"","Status":"","Trace":"","Interval","MaxCount","ActiveTime":"持续时长"}};
*********************************************************************************/

/********************************************************************************
2 声音报警
prop: json 串: {"Sensitive":""},
*********************************************************************************/

/*********************************************************************************
3 内置pir 
prop: {"Sensitive":""}
**********************************************************************************/

/*********************************************************************************
3 蜂鸣器
"output": {"CtrlType":"","AlarmType":"","SoundName":"","LoopCnt"}
"prop": 无
**********************************************************************************/

/*******************************************************************************
4 灯光
"prop":{"Flicker":""}
"Output":{"CtrlType":"","Flicker":"","Duration":""} // 如果没有 flicker 属性 在output 也没有 
********************************************************************************/

/*******************************************************************************
5 录像
"prop":{"RecordLoop":"", "RecordFull" : "","StreamID",""}
********************************************************************************/

/*******************************************************************************
6 本地抓图
"prop":{"LoopFlag":"", "Interval" : "","PicType","", "FullFlag":""}
********************************************************************************/

/*******************************************************************************
7 强制白天晚上
"prop":{"IrcutType":""}
"Output":{"CtrlType":""} //EN_ZJ_IRMODE
********************************************************************************/
_ZJ_API int ZJ_AddIoTDevice(unsigned int uiAIIoTType, unsigned long long lluAIIoTID,
                            ZJ_PFUN_AIIOT_START pfunAIIoTStart, ZJ_PFUN_AIIOT_STOP pfunAIIoTStop, 
                            ZJ_PFUN_AIIOT_GETINPUT pfunAIIoTGetInput, ZJ_PFUN_AIIOT_OUTPUT pfunAIIoTOutPut,
                            ZJ_PFUN_AIIOT_SETPROP pfunAIIoTSetProp, ZJ_PFUN_AIIOT_CHECKEVENT pfunAIIotCheckEvent);

//设置IoT设备的默认属性，IoT设备属性以一个JSON字符串传入
_ZJ_API int ZJ_SetIoTDefaultProp(unsigned int uiAIIoTType, unsigned long long lluAIIoTID, char* pcProp);

//IoT设备输入信号接口, 输入信号类型和对应的Json字符串作为信号描述
_ZJ_API int ZJ_IoTInPut(unsigned int uiAIIoTType, unsigned long long lluAIIoTID, char* pcInPut);

//IoT设备事件输入接口，IoT设备为事件单一设备，触发时直接根据属性输出事件；
_ZJ_API int ZJ_IoTEventInPut(unsigned int uiAIIoTType, unsigned long long lluAIIoTID, int iEvent);

// 设置默认录像的属性 或者 调用 ZJ_SetIoTDefaultProp 设置
_ZJ_API int ZJ_SetDefaultRecordProp(unsigned int uiLoopFlag,unsigned int  uiFullFlag,unsigned int uiStreamId);

// 设置本地抓图的 默认属性
_ZJ_API int ZJ_SetDefaultSnapProp(unsigned int uiLoopFlag,unsigned int uiFullFlag,unsigned int uiInterval,unsigned int uiPicType);

// 检测到人脸列表 调用这个,  不用调用 ZJ_IoTEventInPut
_ZJ_API void ZJ_SetHumanFaceEvent(unsigned int uiAIIoTType, unsigned long long lluAIIoTID,ST_ZJ_HUMANFACE_INFO *pstHumanIfoList);

//设置默认的iot策略
_ZJ_API int ZJ_SetIotDefaultPolicy(unsigned int uiIotType, unsigned int uiOpenFlag, unsigned int uiEventId, unsigned int uiTraceFlag, unsigned int uiBuzzerFlag,
    unsigned int uiSenstive, unsigned int uiRecordFlag, unsigned int uiSnapFlag, unsigned int uiEventFlag, unsigned int uiDuration,unsigned int uiActiveTime);

#ifdef __cplusplus
}
#endif

#endif
