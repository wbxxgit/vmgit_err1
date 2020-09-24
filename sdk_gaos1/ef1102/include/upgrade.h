/******************************************************************************

                  版权所有 (C), 2012-2022, Goscam

 ******************************************************************************
  文 件 名   : upgrade.h
  版 本 号   : 初稿
  作    者   : mr.iubing
  生成日期   : 2014年4月9日
  最近修改   :
  功能描述   : upgrade.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年4月9日
    作    者   : mr.iubing
    修改内容   : 创建文件

******************************************************************************/

#ifndef __UPGRADE_H__
#define __UPGRADE_H__

#include "sdk_commonstruct.h"
#include "api_Remote_Upgrade.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

//return : -1 -> invalid params;		-2 -> local upgrade package path is not exist; 0 -> success
int GOS_SDK_Upgrade_Bylocal(T_SDK_UPGRADE_BYLOCAL_PARAMS *param);

//reutnr : 0 -> success;
int GOS_SDK_Upgrade_Start(T_SDK_UPGRADE_BYSELF_PARAMS *param);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __UPGRADE_H__ */
