#ifndef DEV_PTZ_H_
#define DEV_PTZ_H_

#include "zj_type.h"


int dev_ptz_init(void);
int dev_ptz_start(void);
int dev_ptz_destory(void);

//int devd_PTZrotate(EN_ZJ_CAMERA_PTZ_CONTROL direction,u32 durationMs);

int dev_setRotateSta(EN_ZJ_CAMERA_PTZ_CONTROL orien);

void dev_pushRotateCmd(int v);


#endif




