#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "zj_type.h"
#include "zj_log.h"
#include "forZb_comCfg.h"

#include "forZb_ota.h"

#include "dev_zj_funReg.h"

#include "dev_systemSup.h"

 //#define "\mnt\1"   ///opt/httpServer/lighttpd/htdocs/sd

#define FIRMWARE_PATH_FILE    "opt/httpServer/lighttpd/htdocs/sd/testGrade/file.bin"
#define FIRMWARE_PATH         "opt/httpServer/lighttpd/htdocs/sd/testGrade"

int ota_msg_callback_reset(ST_ota_message *pOtaMsg){
	pOtaMsg->triggerStaTsk = 0;
	pOtaMsg->omRecFileSize = 0;
	pOtaMsg->timeout_loop = 0;
    //delete file

	
	if(pOtaMsg->fHandle != NULL)
		fclose(pOtaMsg->fHandle);
	return 0;
}

int ota_msg_callback_init(ST_ota_message *pOtaMsg,u32 initFileSize){
	char acCmdBuf[256] = "";

	pOtaMsg->triggerStaTsk = 1;
	pOtaMsg->omFileSize = initFileSize;	
//	pOtaMsg->expectUpgrade = 0;
	pOtaMsg->omRecFileSize = 0;
	pOtaMsg->timeout_loop = 100;
	pOtaMsg->fmFileName = FIRMWARE_PATH_FILE;
	pOtaMsg->pFun_destory = ota_msg_callback_reset;


	if( !access(FIRMWARE_PATH,0)){
		printf("/testconfig/system exist\n");
	}else{
		snprintf(acCmdBuf, sizeof(acCmdBuf), "mkdir -p %s", FIRMWARE_PATH);
	//	system("mkdir -p  /mnt/testconfig/system");
		system(acCmdBuf);
	}		
	//delete file
	pOtaMsg->fHandle = fopen(pOtaMsg->fmFileName,"w");
	if(pOtaMsg->fHandle == NULL){
		ZJ_LOG_INF("delete file fail!\n");
		return -1;
	}
	ZJ_LOG_INF("clear firmware file!\n");



	
	pOtaMsg->fHandle = fopen(pOtaMsg->fmFileName,"a+");
	if(pOtaMsg->fHandle == NULL){
		ZJ_LOG_INF("pOtaMsg->fHandle == NULL err!\n");
		return -1;
	}
	return 0;
}




int fzb_NewVersionCb(unsigned char *pucNewVersion,unsigned int uiFileSize){
	ZJ_LOG_INF("NewVersionCb exe,NewVersion[%s],FileSize[%d]\n",pucNewVersion,uiFileSize);

	if(pucNewVersion == NULL || uiFileSize == 0)
		return -1;	
	
	if( ota_msg_callback_init(RetG_ota_msg(),uiFileSize) != 0)
		return -1;		
	if(dj_ota_GtFTbl()->f_StartUpdate == NULL)
		return -1;	
	dj_ota_GtFTbl()->f_StartUpdate();
	return 0;
}
int fzb_VersonDataDownCb(unsigned char *pucPackage,unsigned int uiPacklen,unsigned int uiEndFlag){
	ZJ_LOG_INF("VersonDataDownCb exe,Packlen[%d],EndFlag[%d]\n",uiPacklen,uiEndFlag);

	if(RetG_ota_msg()->triggerStaTsk == 2){  //运行状态
		RetG_ota_msg()->omRecFileSize += uiPacklen;
		ZJ_LOG_INF("RetG_ota_msg()->omRecFileSize[%d]",RetG_ota_msg()->omRecFileSize);

		if(RetG_ota_msg()->fHandle == NULL){
			ZJ_LOG_INF("fHandle = NULL err!\n");
			return -1;
		}
		fwrite(pucPackage, uiPacklen , 1, RetG_ota_msg()->fHandle );

		if(dj_ota_GtFTbl()->f_SetBurnningProgress == NULL)
			return -1;
		dj_ota_GtFTbl()->f_SetBurnningProgress( RetG_ota_msg()->omRecFileSize *100 
												/(RetG_ota_msg()->omFileSize) );

		if(uiEndFlag == 1){										
	//	if(RetG_ota_msg()->omRecFileSize == RetG_ota_msg()->omFileSize){
			ZJ_LOG_INF("omRecFileSize==omFileSize,rec succeed\n");

			RetG_ota_msg()->triggerStaTsk = 3;
			fclose(RetG_ota_msg()->fHandle);
		}	
	}
	return 0;
}
int fzb_StopUpgrade(){
	ZJ_LOG_INF("StopUpgrade exe\n");
	RetG_ota_msg()->interruptTsk = 1;
	return 0;
}
int fzb_CoverImageNotice(unsigned int uiCoverFlag){
	ZJ_LOG_INF("CoverImageNotice exe,CoverFlag[%d]\n",uiCoverFlag);
	return 0;
}























