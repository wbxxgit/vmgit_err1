#ifndef _ZJ_IOTHUB_H_
#define _ZJ_IOTHUB_H_

#ifdef __cplusplus
extern "C" {
#endif

/***
 * 管理IOT HUB扩展能力，包括HUB的通信、协议转换等；涉及与扩展能力块协议交换；
 */
//设置设备支持iOTHub扩展能力. 0. 不支持（没有扩展槽）； 1.支持（有扩展槽）；
_ZJ_API int ZJ_SetIoTHubAbility(int iSupport);

//设置设备iOTHub工作状态。 0.没有插入HUB； 1.已经插入HUB；
_ZJ_API int ZJ_SetIoTHubStatus(int iStatus);

//设置需要通过RFHub网关发送数据的回调接口， 通过该接口将数据转换为RF信号广播出去；
_ZJ_API int ZJ_SetIoTHubRecvFunc(ZJ_PFUN_IOTHUB_DATARECV pfunIoTHubDataRecv);

//RFHub网关接收到外接设备的RF信号，进行数据转换后，写入SDK模块进行处理；
_ZJ_API int ZJ_IoTHubWriteData(unsigned char* pucData, int iLen);


#ifdef __cplusplus
}
#endif

#endif