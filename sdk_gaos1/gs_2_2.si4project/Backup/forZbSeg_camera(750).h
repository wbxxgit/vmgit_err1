#ifndef FORZBSEG_CAMERA_H_
#define FORZBSEG_CAMERA_H_

#include "zj_type.h"

#define ALLOW_VIDEOSTREAM  1
#define ALLOW_AUDIOSTREAM  1


void SegCam_setVideoSw(u8 setval);
u8 SegCam_getVideoSw(void);

void SegCam_setAudioSw(u8 setval);
u8 SegCam_getAudioSw(void);


#endif




