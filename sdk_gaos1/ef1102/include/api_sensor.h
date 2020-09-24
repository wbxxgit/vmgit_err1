/**************************************************************************
 * 	FileName:		api_sensor.h
 *	Description:    头文件
 *	Copyright(C):	2014-2020 gos Inc.
 *	Version:		V 1.0
 *	Author:			Chenjb
 *	Created:		2014-08-06
 *	Updated:		
 *					
 **************************************************************************/
#ifndef   _API_SENSOR_
#define   _API_SENSOR_

#include "sdk_commonstruct.h"
#include "global.h"
#include "adi_vi.h"
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

//视频输入的色彩调节和相关设置，类型定义
typedef enum _VIDEO_IN_SENSOR_E
{
	//色彩
	VCT_BRIGHTNESS	= 0,//亮度
	VCT_CONTRAST	   ,//对比度
	VCT_HUE			   ,//色度
	VCT_SATURATION	   ,//饱和度
}VIDEO_IN_SENSOR_E;
//视频输入的色彩调节和相关设置，类型定义
typedef struct _VIDEO_IN_SENSOR_S
{
	//色彩
	int brghtness; //亮度
	int contrast;  //对比度
	int hue;       //色度
	int saturation;//饱和度
	int sharp1[3]; //锐度
}PACKED VIDEO_IN_SENSOR_S;
int  GOS_SDK_ISP_SetCCM_day();
int  GOS_SDK_ISP_SetCCM_night();
int  GOS_SDK_ISP_SetGammaTable(unsigned char u8GammaTabNum);
int  GOS_SDK_ISP_SetSharpenAttr_night();
int  GOS_SDK_ISP_SetSharpenAttr_day();
int  GOS_SDK_ISP_SetSaturationAttr_day(int value);
int  GOS_SDK_VPSS_GetChnSpParam();
int  GOS_SDK_VPSS_SetChnSpParam(T_SDK_SENSOR_SHARP *param_input);
int  GOS_SDK_ISP_SetSaturation_day();
int  GOS_SDK_ISP_SetSaturation_night();
int  GOS_SDK_ISP_GetAEAttrEx(T_SDK_SENSOR_AUTO_EXPOSURE *stAEAttr_output);
int  GOS_SDK_ISP_SetAEAttrEx(T_SDK_SENSOR_AUTO_EXPOSURE *stAEAttr_input);
int  GOS_SDK_ISP_SetAEAttrEx_night();
int  GOS_SDK_ISP_SetAEAttrEx_day();
int  GOS_SDK_Vi_Set_CSC_Contrast(unsigned int value);
int  GOS_SDK_Vi_Set_CSC_Brightness(unsigned int value);
int  GOS_SDK_Vi_Set_CSC_Hue(unsigned int value);
int  GOS_SDK_Vi_Set_CSC_Satu(unsigned int value);
int  GOS_SDK_Vi_Get_CSC(T_SDK_SENSOR_PARAM *parm);
int  GOS_SDK_Vi_Set_CSC(unsigned int value,unsigned int type);
int  GOS_SDK_ISP_SetPalOrNtsc(int value);
int  GOS_SDK_ISP_SetFarme(int value);
int  GOS_SDK_ISP_SetDemosaicAttr_day();
int  GOS_SDK_ISP_SetDemosaicAttr_night();
int  GOS_SDK_ISP_SetShadingAttr_Close();
int  GOS_SDK_ISP_SetShadingAttr_Open();
int  GOS_SDK_ISP_SetShading(unsigned int *param_input);
int  GOS_SDK_VPSS_Close_3DNr();
int  GOS_SDK_VPSS_Open_3DNr();
int  GOS_SDK_Set_VPSS_3DNr(int u32SfStrength ,int u32TfStrength,int u32ChromaRange);
int  GOS_SDK_ISP_SetShadingTable();
int  GOS_SDK_Vi_Get_Ircut(unsigned int *param_output);
int  Calc_Ae();
int  Calc_Ae_Ex();
int  PoeLEDBlink();
int  GOS_VI_CheckIo();
void GOS_SDK_Check_ViMirrorMode(unsigned int bMirror, unsigned int bFlip, unsigned int *mode);
int  GOS_SDK_Get_ViMirrorMode(int nMinEnc,unsigned int *mode);
int  GOS_SDK_Set_ViMirrorMode(int nMinEnc,unsigned int mode, unsigned int flag); 
int  GOS_SDK_ISP_SetDefectPixelAttr_day();
int  GOS_SDK_ISP_SetDefectPixelAttr_night(int BadPixelSlope,int BadPixelThresh);
int  GOS_SDK_ISP_SetSaturation(unsigned char u8SatTarget,unsigned char *p);
int  GOS_SDK_ISP_SetSharpenAttr(unsigned char * p);
int  GOS_SDK_ISP_SetDenoiseAttr_day();
int GOS_SDK_ISP_SetDenoiseAttr_day_lowLight();
int  GOS_SDK_ISP_SetDenoiseAttr_night();

void GOS_Switch_ViMirrorMode(unsigned int *Mode);

extern VIDEO_IN_SENSOR_S  stImageAttr;        //图像属性
extern GADI_VI_SettingParamsT   viParams;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

