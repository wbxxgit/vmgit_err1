#ifndef _ZJ_CHANNEL_H_
#define _ZJ_CHANNEL_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 发送自定义消息指令；
 */
_ZJ_API int ZJ_SendCustomData(const unsigned char* pucPeerID, unsigned char* pucData, int iLen);

_ZJ_API int ZJ_SetRecvCustomDataFunc(ZJ_PFUN_DEVICE_RECVCUSTOMDATA pFuncOnRecvCustomData);


#ifdef __cplusplus
}
#endif

#endif