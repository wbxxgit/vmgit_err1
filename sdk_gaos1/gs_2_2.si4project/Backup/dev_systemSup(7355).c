#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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
#include "basetypesJX.h" 


#define ETHTESTNAME "eth0"

#define KEYPRESSTIME_LL  120   //200MS
#define KEYPRESSTIME_S    60

#define PARAFILEPATH "/mnt/testconfig/residuepara"
#define PARAFILEPATH_FILE "/mnt/testconfig/residuepara/para.txt"



typedef struct ST_stru_keyIoMsg{
	u32 preTime;
	u8 noloosenSta;

	u8 keyResult;
	u8 hasbenRst;
	u8 hasbenRst_root;
} ST_keyIoMsg;


static pthread_t tid_dev_systemSup;
static pthread_t tid_sysSup_ota;







static unsigned char netState = 0;
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
	printf(" size = %d \n",size);
	return size;
}


int CheckNLCNetwork(char *ethName)
{
    int skfd;
    int result=-1;
    struct ethtool_value edata;
    struct ifreq ifr;
    
    if ((skfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Socket Failed\n");
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
	printf("*residuePara_w*:has been write:%d\n",val);
	return 0;
}

#if 0
static int residueParaInit(){
	
	if( !access(PARAFILEPATH_FILE,0)){
		printf("*residuePara*:residuepara exist\n");

		FILE *pFile = fopen(PARAFILEPATH_FILE, "r");
		if (pFile == NULL) {
			fclose(pFile);	
			return -1;
		}
		
		if( EOF != fscanf(pFile,"SyncFlag:%d",&time_syncFlag)){
			printf("*residuePara*:read succeed\n");
			printf("read flag %d\n",time_syncFlag);
			fclose(pFile);	
		}else{
			printf("*residuePara*:read file err,try again write\n");
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
		printf("*residuePara*:no exist mkdir\n");
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
	ZJ_LOG_INF("%s",(char *)arg);
  //  int i=3;
	ZJ_LOG_INF("enter dev_systemSup_loop");
    while(1)
    {   
	    ZJ_LOG_INF("ota_loop 1s is  running.timeout_loop[%d]",g_ota_msg.timeout_loop);
	    sleep(1);
		if(g_ota_msg.timeout_loop)
			g_ota_msg.timeout_loop--;


		if(g_ota_msg.triggerStaTsk == 3 ||(g_ota_msg.triggerStaTsk == 5)){
			if(g_ota_msg.triggerStaTsk == 3){
				ZJ_LOG_INF("need firmware upgrade");

				long nDownSize = utils_Calc_FileSize(FIRMWARE_PATH_FILE);
				printf("nDownSize = %ld\n",nDownSize);
				
				T_SDK_UPGRADE_BYLOCAL_PARAMS t_ota_file;
				//�����ļ�������Ŀ¼
				t_ota_file.un_mode = 1;
				t_ota_file.un_FileSize = nDownSize;
				strcpy(t_ota_file.a_local_path,FIRMWARE_PATH_FILE);	
				if(SDK_Cmd_Impl(SDKCMD_UPGRADE_BYLOCAL,	(void*)(&t_ota_file)) != 0)
				{
					ZJ_LOG_INF("SDKCMD_UPGRADE_BYLOCAL cmd err");					
				}
				ZJ_LOG_INF("SDKCMD_UPGRADE_BYLOCAL no err");	
			
				g_ota_msg.triggerStaTsk = 4;
			}	
			pthread_exit((void*)4);
		}

		if(g_ota_msg.interruptTsk == 1){
			g_ota_msg.interruptTsk = 0;
			if(g_ota_msg.pFun_destory != NULL)				
				g_ota_msg.pFun_destory(&g_ota_msg);
			else
				ZJ_LOG_INF("g_ota_msg.pFun_destory = NULL\n");
			
			ZJ_LOG_INF("interrupt cmd.pthread_exit will exe\n");
			pthread_exit((void*)2);
		}	

		if(g_ota_msg.timeout_loop == 0){
			//
			if(g_ota_msg.pFun_destory != NULL)				
				g_ota_msg.pFun_destory(&g_ota_msg);
			else
				ZJ_LOG_INF("g_ota_msg.pFun_destory = NULL\n");
			ZJ_LOG_INF("timeout_loop appear!end ota loop\n");
			pthread_exit((void*)2);
		}		
    }  
	
	
}


static void *dev_systemSup_loop(){	
#ifdef OTA_SD_TEST
	u8 second_ota_countdown = 20;//30s
#endif	
	ZJ_LOG_INF("enter dev_systemSup_loop\n");
	while(1){
		usleep(2000000);
		if( NULL == dj_network_GtFTbl()->f_SetNetWorkType){
			ZJ_LOG_INF("f_SetNetWorkType no register!\n");
			continue;			
		}	
		if( CheckNLCNetwork(ETHTESTNAME)== 0){		
			if(netState != 1){
				netState = 1;
				dj_network_GtFTbl()->f_SetNetWorkType(EN_ZJ_NETWORK_TYPE_WIRED);
				ZJ_LOG_INF("net normal\n");	
			}				
		}else{
			ZJ_LOG_INF("f_SetNetWorkType EN_ZJ_NETWORK_TYPE_NONET !\n");			
			if(netState != 0){
				netState = 0;
				dj_network_GtFTbl()->f_SetNetWorkType(EN_ZJ_NETWORK_TYPE_NONET);
				ZJ_LOG_INF("no net!\n");
			}					
		}
		
		//ota relation
		if( g_ota_msg.triggerStaTsk == 1){
			g_ota_msg.triggerStaTsk = 2;
			if(pthread_create(&tid_sysSup_ota,NULL,dev_systemSup_ota_loop,"ota_loop has been create!")!=0) 	  
				ZJ_LOG_INF("Create thread1 error ! \n");
			usleep(1000000);
		}	
		//OTA SD TEST
//	#if	OTA_SD_TEST
	#ifdef OTA_SD_TEST
		if(second_ota_countdown>0)
			second_ota_countdown--;
		ZJ_LOG_INF("second_ota_countdown:%d \n",second_ota_countdown);
		if(second_ota_countdown == 1){

			T_SDK_UPGRADE_BYLOCAL_PARAMS t_ota_file;
			long nDownSize = utils_Calc_FileSize(FIRMWARE_PATH_FILE_SDTEST);	
			ZJ_LOG_INF("nDownSize = %ld\n",nDownSize);
			t_ota_file.un_mode = 1;
			t_ota_file.un_FileSize = nDownSize;
			strcpy(t_ota_file.a_local_path,FIRMWARE_PATH_FILE_SDTEST); 
			if(SDK_Cmd_Impl(SDKCMD_UPGRADE_BYLOCAL, (void*)(&t_ota_file)) != 0)			
				ZJ_LOG_INF("SDKCMD_UPGRADE_BYLOCAL cmd err\n");				
			ZJ_LOG_INF("SDKCMD_UPGRADE_BYLOCAL has been exe\n");	
		}
	#endif	
		
	}
	return 0;
}

#ifdef MACROCOMPILE_RSTIO
static pthread_t tid_dev_systemRstIo;
static void *dev_systemRstIo_loop(){	
	ZJ_LOG_INF("enter dev_systemRstIo_loop");
	while(1){
		usleep(200000); //200ms
	//	ZJ_LOG_INF("net normal\n");	
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
			ZJ_LOG_INF("key trigger:longlong press\n");
		
		}else if( (GMkey.preTime > KEYPRESSTIME_S) ){
			GMkey.keyResult = 2;
			ZJ_LOG_INF("key trigger:long press\n");
		}else if((GMkey.preTime > 0) && (GMkey.noloosenSta == 0)){
			GMkey.keyResult = 3;
			ZJ_LOG_INF("key trigger:short press\n");
		}

		//result process
		if( GMkey.keyResult == 1 ){
			if(GMkey.hasbenRst == 0){
				GMkey.hasbenRst = 1;
				ZJ_LOG_INF("keyresult:long reset\n");
			//	sysClrCmdByPath(PATH_RESETDELETE_LONG);
				
			}			
		}else if(GMkey.keyResult == 2){
			if(GMkey.hasbenRst == 0){
				GMkey.hasbenRst = 1;
				ZJ_LOG_INF("keyresult:short reset\n");	
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
	printf("dev_systemSup_init exe\n");
	memset(&GMkey, 0, sizeof(ST_keyIoMsg));
	p_getFWioSta = NULL;

//	residueParaInit();
	
	return 0;	
} 

int dev_systemSup_start(void){
	printf("dev_systemSup_start exe\n");
	if(-1 == pthread_create(&tid_dev_systemSup, NULL, dev_systemSup_loop, NULL)){
		printf("create dev_systemSup_looperror!\n");
		return -1;
	}	

#ifdef MACROCOMPILE_RSTIO
	if(-1 == pthread_create(&tid_dev_systemRstIo, NULL, dev_systemRstIo_loop, NULL)){
		printf("create dev_systemRstIo_loop error!\n");
		return -1;
	}	
#endif	



	return 0;
} 
int dev_systemSup_destory(void){
	void *ret;
	pthread_t tid_tmp = tid_dev_systemSup;
	printf("dev_systemSup_destory exe\n");	
	pthread_cancel(tid_tmp);	
	pthread_join(tid_tmp,&ret);//等待线程2的返回状况，获取返回�?
	if(ret !=PTHREAD_CANCELED){
		printf("thread return,id is:%ld,return code:NULL\n",tid_tmp);	
		return -1;
	}

#ifdef MACROCOMPILE_RSTIO
	tid_tmp = tid_dev_systemRstIo;
	pthread_cancel(tid_tmp);	
	pthread_join(tid_tmp,&ret);//等待线程2的返回状况，获取返回�?
	if(ret !=PTHREAD_CANCELED){
		printf("thread return,id is:%ld,return code:NULL\n",tid_tmp);	
		return -1;
	}
#endif	




	return 0;
	
} 


