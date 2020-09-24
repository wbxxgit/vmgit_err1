#ifndef _ZJ_NETWORK_H_
#define _ZJ_NETWORK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * 设置设备网络状态信息，主动触发SDK对网络变化的响应，让响应更加及时；
 *************************************************************************/
_ZJ_API int ZJ_SetNetWorkType(EN_ZJ_NETWORK_TYPE enNetType);

// 设置获取WIFI列表和设置WIFI的回调函数；
_ZJ_API int ZJ_SetWifiCB(ZJ_PFUN_DEVICE_SETWIFI pfuncSetWifi, ZJ_PFUN_DEVICE_GETWIFI pfuncGetWifi, ZJ_PFUN_DEVICE_GETNETINFO pfunGetNetInfo);
// 设置网络错误状态，当网络发生错误时，通知错误类型
_ZJ_API int ZJ_SetNetErrStatus(EN_ZJ_NETWORK_ERR_STATUS enNetWorkErrStatus);

// WiFi配置能力设置，根据EN_ZJ_SETWIFI_ABILITY按位与表示支持多种配网模式
_ZJ_API int ZJ_SetWifiSetAbility(unsigned int uiSetWifiAbility); 

/**********************************************************************************
二维码 配网流程 上层识别到二维码，将对应的字符串设置下来
***********************************************************************************/
_ZJ_API int ZJ_SetQRCodeString(unsigned char *pstrQRCode);

//声波配网， 将上层声波识别的字符串设置下来
_ZJ_API int ZJ_SetVoiceString(unsigned char* pstrVoiceString);


#ifdef __cplusplus
}
#endif

#endif