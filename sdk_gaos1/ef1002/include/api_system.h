/**************************************************************************
 * 	FileName:		api_system.h
 *	Description:    头文件
 *	Copyright(C):	2014-2020 gos Inc.
 *	Version:		V 1.0
 *	Author:			Chenjb
 *	Created:		2014-08-06
 *	Updated:		
 *					
 **************************************************************************/
#ifndef   _API_SYSTEM_
#define   _API_SYSTEM_

#include "sdk_commonstruct.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*
int GOS_SDK_PTZ_UP(void);
int GOS_SDK_DOWN(void);
int GOS_SDK_LEFT(void);
int GOS_SDK_RIGHT(void);
int GOS_SDK_BETWEEN(void);
int GOS_SDK_AUTO_LINER(void);
int GOS_SDK_AUTO_VERTICAR(void);
int GOS_SDK_POSTION_POWER_DOWN(void);
int GOS_SDK_POSTION_BETWEEN(void);
int GOS_SDK_POSTION_CHECK(void);
int GOS_SDK_SPEED_ADD(void);
int GOS_SDK_SPEED_MINUS(void);
int GOS_SDK_Z_CHECK(void);
int GOS_SDK_STOP(void);
int GOS_SDK_SET_PREST(void);
int GOS_SDK_CALL_PREST(void);
int SetIpncRS232MotorPtz_S(unsigned int nPtzcmd);*/
unsigned int GOS_GetLinuxSecTime();
int GOS_c2i(char c);
extern int uclibcTimeZoomSet(int TimeZoom);
int gs_swosdGetCurTime_SS(int *Y,int *M,int *D,int *T,int *F,int *S);
int SDK_GetDevSwHwVersion(char* version, int version_long);
int SDK_GetDeviceInfo (T_SDK_DEVICE_INFO* pt_deviceInfo);
int SDK_SaveAllParam();
int SDK_SystemReboot();
int SDK_ResetDevice();
int SDK_SetDeviceTime(T_SDK_DEVICE_TIME *parm);
int SDK_GetDeviceTime(T_SDK_DEVICE_TIME *parm);

int SetIpncRS232MotorPtz_S(unsigned int nPtzcmd);

//设置夜视为自动还是手动
int SDK_SetNightVision(T_SDK_NIGHT_VISION *param);
int SDK_GetNightVision(T_SDK_NIGHT_VISION *parm);

//设置连接上平台的状态
int SDK_ConnectedPlatform(unsigned int *param);

int SDK_SystemReboot();
int SDK_SetGPIO(T_SDK_LED *param);
int SDK_Set_Device_Authentication(T_SDK_DEVICE_AUTHENTICATION_INFO *parm);
int SDK_Get_Device_Authentication(T_SDK_DEVICE_AUTHENTICATION_INFO *parm);
int SDK_Get_Device_Ability(T_SDK_DEVICE_ABILITY_INFO* param);
int SDK_Get_Device_Ability1(T_SDK_DEVICE_ABILITY_INFO1* param);
int SDK_Get_Device_Ability2(T_SDK_DEVICE_ABILITY_INFO2* parm);

int GOS_Clear_UpdateFile();

int GOS_Clear_System();
int SDK_Set_Light_Switch(unsigned int un_switch);
int SDK_Get_Light_Switch(unsigned int *un_switch);

int SDK_Get_Light_Open_Time(unsigned int *pir_ctl,unsigned int *man_ctl);
int SDK_Set_Light_Open_Time(unsigned int pir_ctl,unsigned int man_ctl);
int SDK_Get_Light_Timing_Info(T_SDK_DEVICE_LIGHT_TIMING *param);
int SDK_Set_Light_Timing_Info(T_SDK_DEVICE_LIGHT_TIMING *param);


int PTZ_SetPreset(unsigned int* pu32Pos);
int PTZ_DelPreset(unsigned int* pu32Pos);
int PTZ_CallPreset(unsigned int* pu32Pos);
int PTZ_DelAllPreset();
int PTZ_GetPosi(PTZ_POSI_ST* pstPosi);
int PTZ_SetPosi(PTZ_POSI_ST* pstPosi);
void Set_Auto();

int SDK_GetDevReboot();

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

