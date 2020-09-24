
#include "dev_alarm.h"
#include "dev_audio.h"
#include "dev_iot.h"
#include "dev_ptz.h"
#include "dev_systemSup.h"




int dev_all_init(){
	dev_audio_init();	
	dev_systemSup_init();
	
#ifdef MMACRO_NOFLASH_T3_E1102
	dev_ptz_init();
#endif
	
#ifdef MACROCOMPILE_THREAD_DEVIOT
	dev_iot_init();
#endif

	return 0;
}

int dev_all_statr(){
	dev_audio_start();	
	dev_systemSup_start();
#ifdef MMACRO_NOFLASH_T3_E1102
	dev_ptz_start();
#endif

	
	
#ifdef MACROCOMPILE_THREAD_DEVIOT
	dev_iot_start();
#endif

	return 0;
}

int dev_all_destory(){
	dev_audio_destory();
		
	dev_systemSup_destory();
#ifdef MMACRO_NOFLASH_T3_E1102	
	dev_ptz_destory();
#endif
#ifdef MACROCOMPILE_THREAD_DEVIOT
	dev_iot_destory();
#endif

	return 0;
}



