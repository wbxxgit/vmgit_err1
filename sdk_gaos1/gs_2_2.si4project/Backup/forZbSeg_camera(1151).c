#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "basetypesJX.h"


#include "zj_type.h"
#include "zj_log.h"

#include "forZb_comCfg.h"
#include "forZb_camera.h"

#include "dev_zj_funReg.h"

#include "sdk_commonstruct.h"
#include "sdkout_impl.h" 



static u8 videoStreamSW = 0;
static u8 audioStreamSW = 0;


void SegCam_setVideoSw(u8 setval){
	videoStreamSW = setval;
}

u8 SegCam_getVideoSw(void){
	return videoStreamSW;
}


void SegCam_setAudioSw(u8 setval){
	audioStreamSW = setval;
}

u8 SegCam_getAudioSw(void){
	return audioStreamSW;
}











