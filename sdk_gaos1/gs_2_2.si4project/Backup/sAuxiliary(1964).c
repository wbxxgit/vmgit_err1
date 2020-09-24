#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

#include "basetypesJX.h" 
#include "device_log.h"

#include "zj_type.h"
#include "zj_log.h"
#include "ZJre_comCfg.h"

#include "sAuxiliary.h"

//字符串截取
/*
char *myStrncpy(char *dest, const char *src, int n) 
{
    int size = sizeof(char)*(n + 1);
    char *tmp = (char*)malloc(size);  // 开辟大小为n+1的临时内存tmp
    if (tmp) 
    {
        memset(tmp, '\0', size);  // 将内存初始化为0
        memcpy(tmp, src, size - 1);  // 将src的前n个字节拷贝到tmp
        memcpy(dest, tmp, size);  // 将临时空间tmp的内容拷贝到dest

        free(tmp);  // 释放内存
        return dest;
    }
    else 
    {
        return NULL;
    }
} */
//得到软件编译时间 

//#define ETH_NAME	"ens33"
#define ETH_NAME	"eth0"

int getipJudge(){
	int					sockfd;
	struct sockaddr_in	sin;
	struct ifreq		ifr;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		perror("socket error");
		return -1;
	}	
	strncpy(ifr.ifr_name, ETH_NAME, IFNAMSIZ);		//Interface name	
	if (ioctl(sockfd, SIOCGIFADDR, &ifr) == 0) {	//SIOCGIFADDR 获取interface address
		memcpy(&sin, &ifr.ifr_addr, sizeof(ifr.ifr_addr));
		DPRI_INFO("ip:  %s\n", inet_ntoa(sin.sin_addr));
		return 0;
	}
	DPRI_INFO("ioctl!= 0\n");
	return -1;
}

static int judgeIp_isGateway_0isNo(char *pIP){
	int a,b,c,d;	
	char s[30] = {0};

    strcpy(s,pIP);
    if (4==sscanf(s,"%d.%d.%d.%d",&a,&b,&c,&d)) {
        if (0<=a && a<=255
         && 0<=b && b<=255
         && 0<=c && c<=255
         && 0<=d && d<=255) {
      //      DPRI_INFO("[%s] is valid IPv4\n",s);
        } else {
            DPRI_INFO("[%s] is invalid IPv4\n",s);
        }
    } else {
        DPRI_INFO("[%s] is invalid IPv4\n",s);
    }
	if((c == 0) &&(d ==1) )
		return -1;
	return 0;
}

int judgeIp_isGateway_0isGate(char *pIP,int strsize){
	int a,b,c,d;	
	char s[30] = {0};

	if(strsize < 7)
		return -1;
	if(strsize > 30)
		return -1;

    strcpy(s,pIP);
    if (4==sscanf(s,"%d.%d.%d.%d",&a,&b,&c,&d)) {
        if (0<=a && a<=255
         && 0<=b && b<=255
         && 0<=c && c<=255
         && 0<=d && d<=255) {
      //      DPRI_INFO("[%s] is valid IPv4\n",s);
        } else {
            DPRI_INFO("[%s] is invalid IPv4\n",s);
        }
    } else {
        DPRI_INFO("[%s] is invalid IPv4\n",s);
		return -1;
    }
	if((c == 0) &&(d ==1) )
		return 0;
	return 1;
}


int getipJudge_namePara(char *name){
        int sockfd;
        struct sockaddr_in      sin;
        struct ifreq            ifr;
        sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
        if (sockfd == -1) {
                perror("socket error");				
                return -1; 
        }           
        strncpy(ifr.ifr_name, name, IFNAMSIZ);          //Interface name        
        if (ioctl(sockfd, SIOCGIFADDR, &ifr) == 0) {    //SIOCGIFADDR 获取interface address
                memcpy(&sin, &ifr.ifr_addr, sizeof(ifr.ifr_addr));
				char tempstr[20] = {0};				
				const char *ptr = NULL;
				ptr = inet_ntop(AF_INET,&sin.sin_addr, tempstr, sizeof(tempstr));
				if(ptr == NULL){
					DPRI_INFO(" ptr == NULL \n");
					close(sockfd);
					return -1;
				}
				
                DPRI_INFO("inet_ntop exe,ptr != NULL.ip:  %s,EthName:%s\n", tempstr,name);
				if(judgeIp_isGateway_0isNo(tempstr) != 0 ){
					DPRI_INFO(" judgeIp_isGateway_0isNo != 0 ,it is gateway\n");
					close(sockfd);
					return -1;
				}	
				close(sockfd);
                return 0;  // succeed	
        }   
        DPRI_INFO("ioctl!= 0,EthName:%s\n",name);
		close(sockfd);
        return -1; 
}


int getipJudge_bynameRetIPc(char *name,char *retIP,int ipsize){
        int sockfd;
        struct sockaddr_in      sin;
        struct ifreq            ifr;
		if(ipsize <20)
			return -1;
        sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
        if (sockfd == -1) {
                perror("socket error");				
                return -1; 
        }           
        strncpy(ifr.ifr_name, name, IFNAMSIZ);          //Interface name        
        if (ioctl(sockfd, SIOCGIFADDR, &ifr) == 0) {    //SIOCGIFADDR 获取interface address
                memcpy(&sin, &ifr.ifr_addr, sizeof(ifr.ifr_addr));
				char tempstr[20] = {0};				
				const char *ptr = NULL;
				ptr = inet_ntop(AF_INET,&sin.sin_addr, tempstr, sizeof(tempstr));
				if(ptr == NULL){
					DPRI_INFO(" ptr == NULL \n");
					close(sockfd);
					return -1;
				}
				strncpy(retIP, tempstr, 20);        
				close(sockfd);
                return 0;  // succeed	
        }   
        DPRI_INFO("ioctl!= 0,EthName:%s\n",name);
		close(sockfd);
        return -1; 
}



RTC_TIME_DEF GetSoftWareBuildTargetTime(void)
{
    char arrDate[20] = {0}; //Jul 03 2018
    char arrTime[20]= {0}; //06:17:05
    char pDest[20]= {0};
    RTC_TIME_DEF stTime;

	memset(&stTime,0,sizeof(RTC_TIME_DEF));
    sprintf(arrDate,"%s",__DATE__);//Jul 03 2018
    sprintf(arrTime,"%s",__TIME__);//06:17:05  
//	DPRI_INFO("arrTime:%s\n",arrTime);
	strncpy(pDest,arrDate,3);
//	DPRI_INFO("%s\n",pDest);
    if (strcmp(pDest, "Jan") == 0) stTime.nMonth = 1;
    else if (strcmp(pDest, "Feb") == 0) stTime.nMonth = 2;
    else if (strcmp(pDest, "Mar") == 0) stTime.nMonth = 3;
    else if (strcmp(pDest, "Apr") == 0) stTime.nMonth = 4;
    else if (strcmp(pDest, "May") == 0) stTime.nMonth = 5;
    else if (strcmp(pDest, "Jun") == 0) stTime.nMonth = 6;
    else if (strcmp(pDest, "Jul") == 0) stTime.nMonth = 7;
    else if (strcmp(pDest, "Aug") == 0) stTime.nMonth = 8;
    else if (strcmp(pDest, "Sep") == 0) stTime.nMonth = 9;
    else if (strcmp(pDest, "Oct") == 0) stTime.nMonth = 10;
    else if (strcmp(pDest, "Nov") == 0) stTime.nMonth = 11;
    else if (strcmp(pDest, "Dec") == 0) stTime.nMonth = 12;
    else stTime.nMonth = 1;

	strncpy(pDest, arrDate+4, 2);
    stTime.nDay = atoi(pDest);

	strncpy(pDest, arrDate + 4 + 3, 4);
//	DPRI_INFO("%s\n",pDest);
    stTime.nYear = atoi(pDest);
    //time
//    memset(pDest,0,20);
    strncpy(pDest, arrTime, 2);
	pDest[2] = '\0';
//	DPRI_INFO("%s\n",pDest);
    stTime.nHour = atoi(pDest);
//	memset(pDest,0,20);
	strncpy(pDest, arrTime+3, 2);
	pDest[2] = '\0';
//	DPRI_INFO("%s\n",pDest);
    stTime.nMinute = atoi(pDest);
//	memset(pDest,0,20);
	strncpy(pDest, arrTime + 3 + 3, 2);
	pDest[2] = '\0';
//	DPRI_INFO("%s\n",pDest);
    stTime.nSecond = atoi(pDest); 
    return stTime;
}


u32 lin_GetTickCount()
{
  struct timespec stTime;

  clock_gettime(CLOCK_REALTIME, &stTime);

  return (stTime.tv_sec * 1000 + stTime.tv_nsec/1000000);
}

int checkPathOrMk(char *path){
	if( !access(path,0))
		DPRI_INFO("checkPathOrMk exist:%s\n",path);
	else{
		char CmdBuf[256] = {0};
		sprintf(CmdBuf,"mkdir -p %s",path);
		system(CmdBuf);
	}
	return 0;
}

int sdk_file_check(void){

	checkPathOrMk(DEVICE_SYSTEM_PATH);	
	checkPathOrMk(DEVICE_CONFIG_PATH);
	char CmdBuf[256] = {0};
	sprintf(CmdBuf,"ls -l %s",DEVICE_SYSTEM_PATH_PARENT);
	system(CmdBuf);
	return 0;
}

