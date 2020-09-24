#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#include "device_log.h"
#include "zj_type.h"
#include "zj_log.h"
#include "forZb_comCfg.h"

#include "forZb_ota.h"

#include "dev_zj_funReg.h"

#include "dev_systemSup.h"

 //#define "\mnt\1"   ///opt/httpServer/lighttpd/htdocs/sd

//#define FIRMWARE_PATH_FILE    "/opt/httpServer/lighttpd/htdocs/sd/testGrade/file.bin"

static int copy_firmware_process(char *copyPath){
	int retSys;
	char acCmdBuf[256] = {0};
	

	if( !access(copyPath,F_OK)){
		DPRI_INFO("copyPath exist\n");
	}else{
		DPRI_INFO("will mk\n");
		memset(acCmdBuf,0,sizeof(acCmdBuf));
		snprintf(acCmdBuf, sizeof(acCmdBuf), "mkdir -p %s", copyPath);
		retSys = system(acCmdBuf);
		DPRI_INFO("retsys:%d!\n",retSys);
		system("ls  /opt/httpServer/lighttpd/htdocs/sd/");
	}	
	
	memset(acCmdBuf,0,sizeof(acCmdBuf));
	snprintf(acCmdBuf, sizeof(acCmdBuf), "cp %s %s",FIRMWARE_PATH_FILE, copyPath);
	retSys = system(acCmdBuf);
	DPRI_INFO("FIRMWARE_PATH_FILE retsys:%d!\n",retSys);

	return 0;
}


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
	char acCmdBuf[256] = {0};
	int retSys;
	pOtaMsg->triggerStaTsk = 1;
	pOtaMsg->omFileSize = initFileSize;
	pOtaMsg->omRecFileSize = 0;
	pOtaMsg->timeout_loop = 210;
	pOtaMsg->fmFileName = FIRMWARE_PATH_FILE;
	pOtaMsg->pFun_destory = ota_msg_callback_reset;

	if( !access(FIRMWARE_PATH,F_OK)){
		DPRI_INFO("FIRMWARE_PATH exist\n");
	}else{
		snprintf(acCmdBuf, sizeof(acCmdBuf), "mkdir -p %s", FIRMWARE_PATH);
		system(acCmdBuf);
	}		 //delete file	
	
	pOtaMsg->fHandle = fopen(pOtaMsg->fmFileName,"wb+");
	if(pOtaMsg->fHandle == NULL){
		DPRI_INFO("delete file fail!\n");
		return -1;
	}  
	DPRI_INFO("clear firmware file succeed!\n");

	memset(acCmdBuf,0,sizeof(acCmdBuf));	
	snprintf(acCmdBuf, sizeof(acCmdBuf), "chmod 777 %s", FIRMWARE_PATH_FILE);
	retSys = system(acCmdBuf);
	DPRI_INFO("retsys:%d!\n",retSys);
	memset(acCmdBuf,0,sizeof(acCmdBuf));	
	snprintf(acCmdBuf, sizeof(acCmdBuf), "ls -l %s", FIRMWARE_PATH);
	retSys = system(acCmdBuf);
	DPRI_INFO("retsys:%d!\n",retSys);	

	return 0;
}




int fzb_NewVersionCb(unsigned char *pucNewVersion,unsigned int uiFileSize){
	DPRI_INFO("NewVersionCb exe,NewVersion[%s],FileSize[%d]\n",pucNewVersion,uiFileSize);

	if(pucNewVersion == NULL || uiFileSize == 0)
		return -1;	
	
	if( ota_msg_callback_init(RetG_ota_msg(),uiFileSize) != 0)
		return -1;		
	if(dj_ota_GtFTbl()->f_StartUpdate == NULL)
		return -1;	
	dj_ota_GtFTbl()->f_StartUpdate();

//	ZJ_StartUpdate();
	return 0;
}
int fzb_VersonDataDownCb(unsigned char *pucPackage,unsigned int uiPacklen,unsigned int uiEndFlag){
	int retfw;
//	DPRI_INFO("VersonDataDownCb exe,Packlen[%d],EndFlag[%d],triggerStaTsk_1424[%d]\n",uiPacklen,uiEndFlag,RetG_ota_msg()->triggerStaTsk);
	if(RetG_ota_msg()->triggerStaTsk == 2){  //运行状态
		RetG_ota_msg()->omRecFileSize += uiPacklen;
		u32 pro_per = (RetG_ota_msg()->omRecFileSize) *100 /(RetG_ota_msg()->omFileSize) ;
		DPRI_INFO("RetG_ota_msg()->omRecFileSize[%d],pro_per= %d\n",RetG_ota_msg()->omRecFileSize,pro_per);		
	//	DPRI_INFO("pro_per= %d\n",pro_per);
		if(RetG_ota_msg()->fHandle == NULL){
			DPRI_INFO("fHandle = NULL err!\n");
			return -1;
		}		
		retfw = fwrite(pucPackage, 1, uiPacklen, RetG_ota_msg()->fHandle );		
		if(retfw == 0 ){
			DPRI_INFO("fwrite == 0\n");
			fclose(RetG_ota_msg()->fHandle);
			return -1;
		} 
		if(dj_ota_GtFTbl()->f_SetBurnningProgress == NULL)
			return -1;		
		dj_ota_GtFTbl()->f_SetBurnningProgress( pro_per );

		if(uiEndFlag == 1){	
			fclose(RetG_ota_msg()->fHandle);
			copy_firmware_process(FIRMWARE_COPYPATH);
			DPRI_INFO("uiEndFlag == 1,fclose fHandle\n");
		}
	}
	return 0;
}
int fzb_StopUpgrade(){
	DPRI_INFO("StopUpgrade exe\n");
	RetG_ota_msg()->interruptTsk = 1;
	return 0;
}

int fzb_CoverImageNotice(unsigned int uiCoverFlag){
	DPRI_INFO("CoverImageNotice exe,CoverFlag[%d]\n",uiCoverFlag);

	if(RetG_ota_msg()->omRecFileSize == RetG_ota_msg()->omFileSize){
		DPRI_INFO("omRecFileSize==omFileSize,rec succeed\n");	
		RetG_ota_msg()->triggerStaTsk = 3; //last release state 			
	}else{
		DPRI_INFO("omRecFileSize[%d],omFileSize[%d]\n",RetG_ota_msg()->omRecFileSize,RetG_ota_msg()->omFileSize);	
		RetG_ota_msg()->triggerStaTsk = 5;
		return -1;
	}

	
	return 0;
}
