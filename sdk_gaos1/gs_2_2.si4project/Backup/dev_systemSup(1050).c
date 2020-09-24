#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "zj_type.h"
#include "zj_log.h"

#include "dev_zj_funReg.h"

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

#define ETHTESTNAME "eth0"

static pthread_t tid_dev_systemSup = 0;

static unsigned char netState = 0;

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

static void *dev_systemSup_loop(){	
	printf("enter dev_systemSup_loop\n");
	while(1){
		usleep(2000000);
		if( NULL == dj_network_GtFTbl()->f_SetNetWorkType){
			printf("f_SetNetWorkType no register!\n");
			continue;			
		}	
		if( CheckNLCNetwork(ETHTESTNAME)== 0){		
			if(netState != 1){
				netState = 1;
				dj_network_GtFTbl()->f_SetNetWorkType(EN_ZJ_NETWORK_TYPE_WIRED);
				printf("net normal\n");	
			}				
		}else{
			printf("f_SetNetWorkType EN_ZJ_NETWORK_TYPE_NONET !\n");			
			if(netState != 0){
				netState = 0;
				dj_network_GtFTbl()->f_SetNetWorkType(EN_ZJ_NETWORK_TYPE_NONET);
				printf("no net!\n");
			}					
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


