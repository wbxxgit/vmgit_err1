#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


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

static pthread_t tid_dev_systemSup;
static pthread_t tid_sysSup_ota;


static unsigned char netState = 0;

static ST_ota_message g_ota_msg = {0};

ST_ota_message *RetG_ota_msg(){
	return &g_ota_msg;
}


static int utils_Calc_FileSize(char *strFilePath)
{
	if(NULL == strFilePath)
	{
		return -1;
	}
	
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

static void *dev_systemSup_ota_loop(void *arg){	
	pthread_detach(pthread_self());
	ZJ_LOG_INF("%s\n",(char *)arg);
  //  int i=3;
	ZJ_LOG_INF("enter dev_systemSup_loop\n");
    while(1)
    {   
	    ZJ_LOG_INF("ota_loop 1s is  running.timeout_loop[%d] \n",g_ota_msg.timeout_loop);
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
			//	retcode = SDK_Cmd_Impl(SDKCMD_UPGRADE_BYLOCAL,	(void*)(&t_ota_file));
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
		
		
	}
	return 0;
}

int dev_systemSup_init(void){
	printf("dev_systemSup_init exe\n");
	return 0;	
} 

int dev_systemSup_start(void){
	printf("dev_systemSup_start exe\n");
	if(-1 == pthread_create(&tid_dev_systemSup, NULL, dev_systemSup_loop, NULL)){
		printf("create error!\n");
		return -1;
	}	
	return 0;
} 
int dev_systemSup_destory(void){
	void *ret;
	pthread_t tid_tmp = tid_dev_systemSup;
	printf("dev_systemSup_destory exe\n");	
	pthread_cancel(tid_tmp);	
	pthread_join(tid_tmp,&ret);//等待线程2的返回状况，获取返回值
	if(ret==PTHREAD_CANCELED)
		return 0;			
	else{
		printf("thread return,id is:%ld,return code:NULL\n",tid_tmp);	
		return -1;
	}	
} 


