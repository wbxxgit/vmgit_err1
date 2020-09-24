#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "basetypesJX.h" 
#include "device_log.h" 

#include "devCfg.h"
#include "zj_type.h"
#include "zj_log.h"

#include "dev_zj_funReg.h"
#include "forZb_comCfg.h"

#include "IPC_MediaBuff.h"
#include "sdk_commonstruct.h"
#include "sdkout_impl.h" 

#include <arpa/inet.h>
#include <linux/sockios.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <linux/ethtool.h>
#include <net/if.h>
#include <ctype.h>

#include "dev_systemSup.h" 
#include "ZJre_camera.h" 

#include "sAuxiliary.h"
#include "dev_network.h"



//ZJre_camera.h

typedef struct wifiSsidMsg{
	int flag;
	char ssid[32];
	char pwd[32];
}ST_wifiSsidMsg;
ST_wifiSsidMsg OwifiSsidMsg = {0};


#define ETHTESTNAME "eth0"

#define KEYPRESSTIME_LL  120   //200MS
#define KEYPRESSTIME_S    60

#define PARAFILEPATH "/mnt/testconfig/residuepara"
#define PARAFILEPATH_FILE "/mnt/testconfig/residuepara/para.txt"
#define PARAFILEPATH_FILE_WIFIMSG  PARAFILEPATH "/wifiMsg.txt"



typedef struct ST_stru_keyIoMsg{
	u32 preTime;
	u8 noloosenSta;

	u8 keyResult;
	u8 hasbenRst;
	u8 hasbenRst_root;
} ST_keyIoMsg;


static pthread_t tid_dev_systemSup;
static pthread_t tid_sysSup_ota;
static pthread_t tid_sysSup_netC;






#ifndef MMACRO_NOFLASH_T3_E1102	
//static unsigned char netState = 0;
#endif
static ST_ota_message g_ota_msg = {0};
static ST_keyIoMsg GMkey = {0};

static int (*p_getFWioSta) (void) = NULL;

static int time_syncFlag;

ST_ota_message *RetG_ota_msg(){
	return &g_ota_msg;
}


static int utils_Calc_FileSize(char *strFilePath)
{
	if(NULL == strFilePath)
		return -1;
	
	struct stat statbuf;
	stat(strFilePath,&statbuf);
	int size=statbuf.st_size;
	DPRI_INFO(" size = %d \n",size);
	return size;
}


int CheckNLCNetwork(char *ethName)
{
    int skfd;
    int result=-1;
    struct ethtool_value edata;
    struct ifreq ifr;
    
    if ((skfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        DPRI_INFO("Socket Failed\n");
        return -1;
    }

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, ethName, sizeof(ifr.ifr_name));
    ifr.ifr_addr.sa_family = AF_INET;
    edata.cmd = ETHTOOL_GLINK;
    ifr.ifr_data = (char *)&edata;

    if (!(ioctl(skfd, SIOCETHTOOL, &ifr)<0)) 
    {
            if(edata.data)
            {
                    result = 0;     
            }
            else
            {
                    result = -1;        
            }
    } 
    else 
    {
            result = -2;
    }
    close(skfd);    
    return result;
}



static int residuePara_write(int val){
	FILE *fp;
	fp = fopen(PARAFILEPATH_FILE, "w");
	if(fp == NULL)
	{
		perror("fopen");				// 文件打开失败，打印错误信息
		fclose(fp); 
		return -1;
	}
	fprintf(fp, "SyncFlag:%d\n", val);
	fclose(fp); 
	DPRI_INFO("*residuePara_w*:has been write:%d\n",val);
	return 0;
}


/*
static int ParaInit_wifiMsg(char *path,char *file){
	if(path == NULL || file == NULL)
		return -1;
	
	if( !access(file,0)){
		DPRI_INFO("*residuePara*:exist:%s\n",file);
		FILE *pFile = fopen(file, "r");
		if (pFile == NULL) {
			fclose(pFile);	
			return -1;
		}		
		if( EOF != fscanf(pFile,"Flag:%d,SSID:%s,PWD:%s\n",&OwifiSsidMsg.flag,OwifiSsidMsg.ssid,OwifiSsidMsg.pwd)  )
		{
			DPRI_INFO("*residuePara*:read succeed\n");
			DPRI_INFO("read flag:%d, %s,%s\n",OwifiSsidMsg.flag,OwifiSsidMsg.ssid,OwifiSsidMsg.pwd);
			fclose(pFile);	
		}else{
			DPRI_INFO("*residuePara*:read file err,try again write\n");
			fclose(pFile);
			FILE *fp;
			fp = fopen(file, "w");
			if(fp == NULL)
			{
				perror("fopen");				// 文件打开失败，打印错误信息
				fclose(fp);	
				return -1;
			}
			memset(&OwifiSsidMsg,0,sizeof(ST_wifiSsidMsg));
			fprintf(fp, "Flag:%d--SSID:%s--PWD:%s\n", OwifiSsidMsg.flag,"testssid","testpwd");
			fclose(fp);	
				
		}
		return 0;	
	
	}else{
		DPRI_INFO("*residuePara*:no exist mkdir:%s\n",file);
		char acCmdBuf[256] = {0};
		snprintf(acCmdBuf, sizeof(acCmdBuf), "mkdir -p %s", path);
		system(acCmdBuf);
		
		FILE *fp;
		fp = fopen(file, "w");
		if(fp == NULL)
		{
			perror("fopen");				// 文件打开失败，打印错误信息
			fclose(fp);	
			return -1;
		}
		memset(&OwifiSsidMsg,0,sizeof(ST_wifiSsidMsg));
		fprintf(fp, "Flag:%d,SSID:%s,PWD:%s\n", OwifiSsidMsg.flag,"testssid","testpwd");
		fclose(fp);	
		return 0;
	}	
}
*/



#if 0
static int residueParaInit(){

//	ParaInit_wifiMsg(PARAFILEPATH,PARAFILEPATH_FILE_WIFIMSG);

	if( !access(PARAFILEPATH_FILE,0)){
		DPRI_INFO("*residuePara*:residuepara exist\n");

		FILE *pFile = fopen(PARAFILEPATH_FILE, "r");
		if (pFile == NULL) {
			fclose(pFile);	
			return -1;
		}
		
		if( EOF != fscanf(pFile,"SyncFlag:%d",&time_syncFlag)){
			DPRI_INFO("*residuePara*:read succeed\n");
			DPRI_INFO("read flag %d\n",time_syncFlag);
			fclose(pFile);	
		}else{
			DPRI_INFO("*residuePara*:read file err,try again write\n");
			fclose(pFile);
			FILE *fp;
			fp = fopen(PARAFILEPATH_FILE, "w");
			if(fp == NULL)
			{
				perror("fopen");				// 文件打开失败，打印错误信息
				fclose(fp);	
				return -1;
			}
			time_syncFlag = 0;
			fprintf(fp, "SyncFlag:%d\n", time_syncFlag);
			fclose(fp);			
		}
		return 0;	
	
	}else{
		DPRI_INFO("*residuePara*:no exist mkdir\n");
		char acCmdBuf[256] = {0};
		snprintf(acCmdBuf, sizeof(acCmdBuf), "mkdir -p %s", PARAFILEPATH);
		system(acCmdBuf);
		
		FILE *fp;
		fp = fopen(PARAFILEPATH_FILE, "w");
		if(fp == NULL)
		{
			perror("fopen");				// 文件打开失败，打印错误信息
			fclose(fp);	
			return -1;
		}
		time_syncFlag = 0;
		fprintf(fp, "SyncFlag:%d\n", time_syncFlag);
		fclose(fp);	
		return 0;
	//	system("mkdir -p  /mnt/testconfig/system");
	}	
}
#endif

int inter_setSyncFlag(int setVal){
	time_syncFlag = setVal;
	if(0 != residuePara_write(time_syncFlag))
		return -1;
	return 0;
}

int inter_getSyncFlag(){
	return time_syncFlag;
}

static void *dev_systemSup_ota_loop(void *arg){	
	pthread_detach(pthread_self());
	DPRI_INFO("%s",(char *)arg);
  //  int i=3;
	DPRI_INFO("enter dev_systemSup_loop");
    while(1)
    {   
	    DPRI_INFO("ota_loop 1s is  running.timeout_loop[%d]",g_ota_msg.timeout_loop);
	    sleep(1);
		if(g_ota_msg.timeout_loop)
			g_ota_msg.timeout_loop--;


		if(g_ota_msg.triggerStaTsk == 3 ||(g_ota_msg.triggerStaTsk == 5)){
			if(g_ota_msg.triggerStaTsk == 3){
				DPRI_INFO("need firmware upgrade");

				long nDownSize = utils_Calc_FileSize(FIRMWARE_PATH_FILE);
				DPRI_INFO("nDownSize = %ld\n",nDownSize);
				
				T_SDK_UPGRADE_BYLOCAL_PARAMS t_ota_file;
				//�����ļ�������Ŀ¼
				t_ota_file.un_mode = 1;
				t_ota_file.un_FileSize = nDownSize;
				strcpy(t_ota_file.a_local_path,FIRMWARE_PATH_FILE);	
				if(SDK_Cmd_Impl(SDKCMD_UPGRADE_BYLOCAL,	(void*)(&t_ota_file)) != 0)
				{
					DPRI_INFO("SDKCMD_UPGRADE_BYLOCAL cmd err");					
				}
				DPRI_INFO("SDKCMD_UPGRADE_BYLOCAL no err");	
			
				g_ota_msg.triggerStaTsk = 4;
			}	
			pthread_exit((void*)4);
		}

		if(g_ota_msg.interruptTsk == 1){
			g_ota_msg.interruptTsk = 0;
			if(g_ota_msg.pFun_destory != NULL)				
				g_ota_msg.pFun_destory(&g_ota_msg);
			else
				DPRI_INFO("g_ota_msg.pFun_destory = NULL\n");
			
			DPRI_INFO("interrupt cmd.pthread_exit will exe\n");
			pthread_exit((void*)2);
		}	

		if(g_ota_msg.timeout_loop == 0){
			//
			if(g_ota_msg.pFun_destory != NULL)				
				g_ota_msg.pFun_destory(&g_ota_msg);
			else
				DPRI_INFO("g_ota_msg.pFun_destory = NULL\n");
			DPRI_INFO("timeout_loop appear!end ota loop\n");
			pthread_exit((void*)2);
		}		
    }  	
	
}

static void *dev_sysSup_net_loop(){		
	u32 i_count;
	DPRI_INFO("enter dev_sysSup_net_loop\n");
	while(1){
		usleep(200000);  //200ms
		d_dualNetCheck(i_count++);
	}
	return 0;
}


static void *dev_systemSup_loop(){	
#ifdef OTA_SD_TEST
	u8 second_ota_countdown = 20;//30s
#endif	

#ifdef MACROCOMPILE_QSSIDTEST
	u32 ssidcnt_countdown = 18;//30s
#endif		

	u8 i_sdM;
	DPRI_INFO("enter dev_systemSup_loop\n");
	while(1){
		usleep(2000000);
	/*	if( NULL == dj_network_GtFTbl()->f_SetNetWorkType){
			DPRI_INFO("f_SetNetWorkType no register!\n");
			continue;			
		}	 */

//#ifndef MMACRO_NOFLASH_T3_E1102		
		#if 0
		if( CheckNLCNetwork(ETHTESTNAME)== 0){		
			if(netState != 1){
				netState = 1;
				dj_network_GtFTbl()->f_SetNetWorkType(EN_ZJ_NETWORK_TYPE_WIRED);
				DPRI_INFO("net normal\n");	
			}				
		}else{
			DPRI_INFO("f_SetNetWorkType EN_ZJ_NETWORK_TYPE_NONET !\n");			
			if(netState != 0){
				netState = 0;
				dj_network_GtFTbl()->f_SetNetWorkType(EN_ZJ_NETWORK_TYPE_NONET);
				DPRI_INFO("no net!\n");
			}					
		}
		#endif
//#else
#if 0

		if( 0 == getipJudge_namePara("eth0"))
			d_setNet(1,1);
		else
			d_setNet(1,0);


#ifdef MMACRO_NOFLASH_T3_E1102

		if( 0 == getipJudge_namePara("ra0")){
			if( d_wifiSsidJudge_matchQlink() == 0){
				d_setNet(2,1);
			}else{
		//		DPRI_INFO("d_wifiSsidJudge_matchQlink err!\n");
			}			
		}			
		else{
			d_setNet(2,0);
			
			//25s start connect qlink
			#if MACROCOMPILE_QSSIDTEST		
			if(ssidcnt_countdown == 1){
				DPRI_INFO("ssidcnt_countdown == 1 ,again setwifi\n");
				d_startWifiCmd_qssid();
			}
			#endif
		}
		if(ssidcnt_countdown>0)
			ssidcnt_countdown--;					
#endif	
#endif

#ifdef MMACRO_NOFLASH_T3_E1102
#ifdef MACROCOMPILE_QSSIDTEST		
		if(ssidcnt_countdown == 1){
			DPRI_INFO("ssidcnt_countdown == 1 ,again setwifi\n");
			d_startWifiCmd_qssid();
		}
#endif
#endif

#ifdef MACROCOMPILE_QSSIDTEST
		if(ssidcnt_countdown>0)
			ssidcnt_countdown--;
#endif






		//ota relation
		if( g_ota_msg.triggerStaTsk == 1){
			g_ota_msg.triggerStaTsk = 2;
			if(pthread_create(&tid_sysSup_ota,NULL,dev_systemSup_ota_loop,"ota_loop has been create!")!=0) 	  
				DPRI_INFO("Create thread1 error ! \n");
			usleep(1000000);
		}	

		//sd mount check
	//	i_sdM++
		if(i_sdM++%2 == 0){  //4s check
			static u32 glo_sdMountState = 0;
			u32 un_connected = 0;		
			if(i_sdM++%12 == 0)
				DPRI_INFO("sd mount check(only show):i_sdM++10 == 0 \n");
			
		//	retcode = SDK_Cmd_Impl(SDKCMD_GET_SD_CARD_MOUNT,  &un_connected);
	//		int	retcode = SDK_Cmd_Impl(SDKCMD_GET_SD_CARD_MOUNT,  &un_connected);	
			T_SDK_STORAGE_INFO storage_info;
			if( SDK_Cmd_Impl(SDKCMD_GET_STORAGE_INFO,  (void *)&storage_info) == 0){
				un_connected = 3;
				DPRI_INFO("SDKCMD_GET_STORAGE_INFO ==0 :%d\n",un_connected);
			}else{
				un_connected = 1;
				DPRI_INFO("SDKCMD_GET_STORAGE_INFO ! =0 :%d\n",un_connected);
			}

			if(glo_sdMountState == 0){	//first time
				glo_sdMountState = un_connected;
			}
			
			if(un_connected == 3){	//mount
				if(glo_sdMountState == 1){	//trigger
					glo_sdMountState = 3;
					DPRI_INFO("mount  trigger! \n");
				
					zjre_packF_sdMountPro(1);
				}					
			}else if(un_connected == 1){ //unnount
				if(glo_sdMountState == 3){	//trigger
					glo_sdMountState = 1;
					DPRI_INFO("unnount	trigger! \n");
					zjre_packF_sdMountPro(0);					
				}					
			}
			
		/*	if(retcode != 0)			
				DPRI_INFO("SDKCMD_GET_SD_CARD_MOUNT error ! \n");
			else{
				if(glo_sdMountState == 0){  //first time
					glo_sdMountState = un_connected;
				}
				
				if(un_connected == 3){  //mount
					if(glo_sdMountState == 1){  //trigger
						glo_sdMountState = 3;
						DPRI_INFO("mount  trigger! \n");
					
						zjre_packF_sdMountPro(1);
					}			

				}else if(un_connected == 1){ //unnount
					if(glo_sdMountState == 3){	//trigger
						glo_sdMountState = 1;
						DPRI_INFO("unnount  trigger! \n");
						zjre_packF_sdMountPro(0);					
					}					
				}	
			}	*/		
		}
		//OTA SD TEST
	#ifdef OTA_SD_TEST
		if(second_ota_countdown>0)
			second_ota_countdown--;
		DPRI_INFO("second_ota_countdown:%d \n",second_ota_countdown);
		if(second_ota_countdown == 1){

			T_SDK_UPGRADE_BYLOCAL_PARAMS t_ota_file;
			long nDownSize = utils_Calc_FileSize(FIRMWARE_PATH_FILE_SDTEST);	
			DPRI_INFO("nDownSize = %ld\n",nDownSize);
			t_ota_file.un_mode = 1;
			t_ota_file.un_FileSize = nDownSize;
			strcpy(t_ota_file.a_local_path,FIRMWARE_PATH_FILE_SDTEST); 
			if(SDK_Cmd_Impl(SDKCMD_UPGRADE_BYLOCAL, (void*)(&t_ota_file)) != 0)			
				DPRI_INFO("SDKCMD_UPGRADE_BYLOCAL cmd err\n");				
			DPRI_INFO("SDKCMD_UPGRADE_BYLOCAL has been exe\n");	
		}
	#endif			
	}
	return 0;
}

#ifdef MACROCOMPILE_RSTIO
static pthread_t tid_dev_systemRstIo;
static void *dev_systemRstIo_loop(){	
	DPRI_INFO("enter dev_systemRstIo_loop");
	while(1){
		usleep(200000); //200ms
	//	DPRI_INFO("net normal\n");	
		if(p_getFWioSta == NULL){
			continue;
		}	
		//reset io check
		if( (*p_getFWioSta)() == 0){
			GMkey.preTime++;
			GMkey.noloosenSta = 1;
	
		}else{
			GMkey.noloosenSta = 0;
		}

		//time judge
		if( GMkey.preTime > KEYPRESSTIME_LL){
			GMkey.keyResult = 1;
			DPRI_INFO("key trigger:longlong press\n");
		
		}else if( (GMkey.preTime > KEYPRESSTIME_S) ){
			GMkey.keyResult = 2;
			DPRI_INFO("key trigger:long press\n");
		}else if((GMkey.preTime > 0) && (GMkey.noloosenSta == 0)){
			GMkey.keyResult = 3;
			DPRI_INFO("key trigger:short press\n");
		}

		//result process
		if( GMkey.keyResult == 1 ){
			if(GMkey.hasbenRst == 0){
				GMkey.hasbenRst = 1;
				DPRI_INFO("keyresult:long reset\n");
			//	sysClrCmdByPath(PATH_RESETDELETE_LONG);
				
			}			
		}else if(GMkey.keyResult == 2){
			if(GMkey.hasbenRst == 0){
				GMkey.hasbenRst = 1;
				DPRI_INFO("keyresult:short reset\n");	
			//	sysClrCmdByPath(PATH_RESETDELETE_SHORT);				
			}
		}
		//reboot judge
		if( ((GMkey.preTime > KEYPRESSTIME_S) && (GMkey.noloosenSta == 0))||( GMkey.preTime > KEYPRESSTIME_LL ) ){
			if(GMkey.hasbenRst_root == 0){
				GMkey.hasbenRst_root = 1;
				system("reboot");				
			}			
		}	
		//clear time
		if(GMkey.noloosenSta == 0){
			GMkey.preTime = 0;
		}		
		
	}
	return 0; 	
}

#endif




int dev_systemSup_init(void){
	DPRI_INFO("dev_systemSup_init exe\n");
	memset(&GMkey, 0, sizeof(ST_keyIoMsg));
	p_getFWioSta = NULL;

//	residueParaInit();

#ifdef MMACRO_NOFLASH_T3_E1102
	d_initDevWifi();
#endif

	
	
	return 0;	
} 

int dev_systemSup_start(void){
	DPRI_INFO("dev_systemSup_start exe\n");
	if(-1 == pthread_create(&tid_dev_systemSup, NULL, dev_systemSup_loop, NULL)){
		DPRI_INFO("create dev_systemSup_looperror!\n");
		return -1;
	}	

	if(-1 == pthread_create(&tid_sysSup_netC, NULL, dev_sysSup_net_loop, NULL)){
		DPRI_INFO("create dev_systemSup_looperror!\n");
		return -1;
	}	

#ifdef MACROCOMPILE_RSTIO
	if(-1 == pthread_create(&tid_dev_systemRstIo, NULL, dev_systemRstIo_loop, NULL)){
		DPRI_INFO("create dev_systemRstIo_loop error!\n");
		return -1;
	}	
#endif	



	return 0;
} 
int dev_systemSup_destory(void){
	void *ret;
	pthread_t tid_tmp = tid_dev_systemSup;
	DPRI_INFO("dev_systemSup_destory exe\n");	
	pthread_cancel(tid_tmp);	
	pthread_join(tid_tmp,&ret);//等待线程2的返回状况，获取返回�?
	if(ret !=PTHREAD_CANCELED){
		DPRI_INFO("thread return,id is:%ld,return code:NULL\n",tid_tmp);	
		return -1;
	}

	tid_tmp = tid_sysSup_netC;
	pthread_cancel(tid_tmp);	
	pthread_join(tid_tmp,&ret);//等待线程2的返回状况，获取返回�?
	if(ret !=PTHREAD_CANCELED){
		DPRI_INFO("thread return,id is:%ld,return code:NULL\n",tid_tmp);	
		return -1;
	}

#ifdef MACROCOMPILE_RSTIO
	tid_tmp = tid_dev_systemRstIo;
	pthread_cancel(tid_tmp);	
	pthread_join(tid_tmp,&ret);//等待线程2的返回状况，获取返回�?
	if(ret !=PTHREAD_CANCELED){
		DPRI_INFO("thread return,id is:%ld,return code:NULL\n",tid_tmp);	
		return -1;
	}
#endif	




	return 0;
	
} 


