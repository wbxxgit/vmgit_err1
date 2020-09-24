
#include <string.h>

#include "basetypesJX.h"
#include "device_log.h"



//#include "IPC_MediaBuff.h"
//#include "sdk_commonstruct.h"
#include "sdkout_impl.h" 

int dev_hintSoundP(char *filePath){
	char S_record[50] = {0};	
	strcpy(S_record,filePath);
#ifdef MMACRO_NOFLASH_T3_E1102	
	if(SDK_Cmd_Impl(SDKCMD_SET_PLAY_AUDIO,&S_record) != 0)
	{
		DPRI_INFO("SDKCMD_SET_PLAY_AUDIO error\n"); 
		return -1;
	}
#endif		

	return 0;
}

