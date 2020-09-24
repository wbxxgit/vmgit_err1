#ifndef _ZJ_SYSTEM_H_
#define _ZJ_SYSTEM_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 设备初始化接口；传入一个配置存储路径和一个系统路径。系统路径在重置 的时候， 该文件不会被删除
 需要确保路径可访问，如不可访问则会返回对应的错误状态信息。
 */
_ZJ_API int ZJ_Init(char *pucSystemPath, char* pcConfPath);

// 自定义平台的 域名地址 xxx:port port 不带 默认 443
_ZJ_API int ZJ_SetPlatSignAddr(unsigned char *pucSignAddr);

// 企业的信息, 没有可以不填
_ZJ_API int ZJ_SetCompanyInfo(unsigned char *pucCompanyId,unsigned char* pucAppId);

// 设置设备CTEI ID
_ZJ_API int ZJ_SetCTEIID(unsigned char* pucCTEI);

// 设置设备的DeviceUID号
_ZJ_API int ZJ_SetDeviceUID(unsigned char *pucDevSn, unsigned char *pucDevKey);

//设置设备型号 EF-FH8632-0530-00  第一位 sdk 开发者 , 第二位厂商芯片信号 第三 产品型号 第四 省份
_ZJ_API int ZJ_SetDeviceModel(unsigned char *pucDevModel);

//EN_ZJ_OS_TYPE
_ZJ_API int ZJ_SetDevOsType(unsigned int uiOsType);

//设置设备类型?1.摄像机；2.分体门铃；3.单体门铃；4.NVR
_ZJ_API int ZJ_SetDevType(unsigned int uiDevType);

// 设置固件版本号；版本号定义遵循版本号定义规则；
_ZJ_API int ZJ_SetAppVersion(const char* pcVersion);

// 设备状态回调函数设置， 从初始化启动&设备配网&设备添加绑定，一般为需要上层做相关提示的产品设置该回调函数
_ZJ_API int ZJ_Set_SystemStatusCB(ZJ_PFUN_DEVICE_STATUS pFunSelfStatusCb);

// 设备重启回调函数设置，设备上层在该函数中安全关闭设备各执行程序，然后将设备重新启动
_ZJ_API int ZJ_SetDeviceRebootCbFunc(ZJ_PFUN_DEV_REBOOT pfunDevRebootCb);

//设置系统时间获取与设置回调函数
_ZJ_API int ZJ_SetZoneAndTimeCB(ZJ_PFUN_DEVICE_SETTIMEZONE pfunSetTimeZone, ZJ_PFUN_DEVICE_GETTIMEANDZONE pfunGetTimeZone);

//设置系统Memory空闲值,不设置默认为MID值
_ZJ_API void ZJ_SetSysMemLevel(EN_ZJ_DEVICE_MEM_ABILITY enZJDevAblity);

//设置设备恢复出厂设置回调函数
_ZJ_API int ZJ_SetRestoreFactorySettingCB(ZJ_PFUN_DEVICE_RESTOREFACTORYSETTING pfunRestoreFactorySetting);

//设置摄像机名称的回调，通知ui层，设备的dev配置项发生变化
_ZJ_API int ZJ_SetNoticeCfgChangeCbFun(ZJ_PFUN_CFGITEM_CHANGE pfunCfgItemChangeCb);

//设置设备加密能力， 按位与 EN_ZJ_ENCRYPT_ABILITY
_ZJ_API int ZJ_SetEncryptAbility(int iEncAbility);

// 获取设备的did, 该ID 由 服务器 分配
_ZJ_API unsigned char* ZJ_GetDeviceId();

// EN_ZJ_CTRLDEVICEID_TYPE
_ZJ_API int ZJ_CtrlDeviceId(unsigned int uiCtrlType);

// 获取 和 设置 设备名字
_ZJ_API unsigned char *ZJ_GetDeviceName();

_ZJ_API int ZJ_SetDeviceName(unsigned char *pucDevName);

// 获取当前生效的套餐
_ZJ_API int ZJ_GetCurChargePackage(ST_ZJ_CURCHARGEPACKAGE *pstChargePackage);

// 1 在组里面 0 不在
_ZJ_API int ZJ_BoolDeviceJoinGroup();

// 获取 设备 的 用户 信息
_ZJ_API int ZJ_GetDeviceOwnerPubInf(unsigned char aucName[64],unsigned char aucCcount[64],unsigned char aucMobile[32]);

// 设置设备的4G卡号
_ZJ_API int ZJ_SetSIMCardInfo(unsigned char aucSIMCard[64]);

// 设置4G卡的能力
_ZJ_API int ZJ_Set4GAbility(int i4GAbility);


_ZJ_API int ZJ_Start();

_ZJ_API int ZJ_Stop();

//SDK实例销毁接口；
_ZJ_API int ZJ_Destroy();


#ifdef __cplusplus
}
#endif

#endif