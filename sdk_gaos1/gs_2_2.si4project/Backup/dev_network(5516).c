#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "basetypesJX.h" 

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

#define PARAFILEPATH_DEV "/mnt/testconfig/residuepara"
#define PARAFILEPATH_FILE_WIFIMSG_DEV  PARAFILEPATH_DEV "/wifiMsg.txt"


typedef struct devWf_pathfile{
	char *path;
	char *file;

}ST_devWf_pathfile;

typedef struct devwifiSsid{
	int flag;
	char ssid[32];
	char pwd[32];
}ST_devwifiSsid;

typedef struct  d_wifiMsg{

	u8 netFlag;  //0 no net,1:have net
	u8 netState;
	u8 netState_last;
	ST_devwifiSsid cwifimsg;
	ST_devWf_pathfile CdevWf_pathfile;
}ST_d_wifiMsg;

//#define NEW_INIT_DWIFIFMSG 

static ST_d_wifiMsg unique_dwifiMsg = {0,0,0,{0},{PARAFILEPATH_DEV,PARAFILEPATH_FILE_WIFIMSG_DEV}};


static int devS_SetWifi(char *pcSSID, char *pcPwd, int iEncrytType){
	T_SDK_WIRELESS_PARAMS t_wireless_param = {0};
	t_wireless_param.un_encrypt = iEncrytType;
	t_wireless_param.e_wifi_connect_status = E_SDK_DISCONNECT;
	strncpy(t_wireless_param.a_passwd,pcSSID,sizeof(t_wireless_param.a_passwd));
	strncpy(t_wireless_param.a_SSID,pcPwd,sizeof(t_wireless_param.a_SSID));
	t_wireless_param.e_wifi_mode = E_SDK_WIFI_CLIENT_MODE;
	if(0 != SDK_Cmd_Impl(SDKCMD_SET_WIRELESS_PARAM,  (void*)(&t_wireless_param))){
		printf("SDKCMD_SET_WIRELESS_PARAM err\n");
		return -1;
	}
	printf("SDKCMD_SET_WIRELESS_PARAM succeed.[%s]-[%s]-[%d]\n",pcSSID,pcPwd,iEncrytType);
	return 0;
}


#define DEFAULT_SSID "Xiaomi_8AC0"
#define DEFAULT_PWD "12345677"



static int ParaInit_devWifiMsg(ST_devwifiSsid *pwifimsg,ST_devWf_pathfile *pathfile){
	if(pathfile->path == NULL || pathfile->file == NULL)
		return -1;
	
	if( !access(pathfile->file,0)){
		printf("*residuePara*:exist:%s\n",pathfile->file);
		FILE *pFile = fopen(pathfile->file, "r");
		if (pFile == NULL) {
			fclose(pFile);	
			return -1;
		}	

		if( EOF != fscanf(pFile,"Flag:%d,SSID:%s,PWD:%s\n",&pwifimsg->flag,pwifimsg->ssid,pwifimsg->pwd)  )
		{
			printf("*residuePara*:read succeed\n");
			printf("read flag:%d, %s,%s\n",pwifimsg->flag,pwifimsg->ssid,pwifimsg->pwd);
			fclose(pFile);	
		}else{
			printf("*residuePara*:read file err,try again write\n");
			fclose(pFile);
			FILE *fp;
			fp = fopen(pathfile->file, "w");
			if(fp == NULL)
			{
				perror("fopen");				// 文件打开失败，打印错误信息
				fclose(fp);	
				return -1;
			}
			pwifimsg->flag = 1;  //默认初始 测试网络
			fprintf(fp, "Flag:%d,SSID:%s,PWD:%s\n", pwifimsg->flag,DEFAULT_SSID,DEFAULT_PWD);
			fclose(fp);					
		}
		return 0;	
	
	}else{
		printf("*residuePara*:no exist mkdir:%s\n",pathfile->file);
		char acCmdBuf[256] = {0};
		snprintf(acCmdBuf, sizeof(acCmdBuf), "mkdir -p %s", pathfile->path);
		system(acCmdBuf);
		
		FILE *fp;
		fp = fopen(pathfile->file, "w");
		if(fp == NULL)
		{
			perror("fopen");				// 文件打开失败，打印错误信息
			fclose(fp);	
			return -1;
		}
		pwifimsg->flag = 1;
		fprintf(fp, "Flag:%d,SSID:%s,PWD:%s\n", pwifimsg->flag,DEFAULT_SSID,DEFAULT_PWD);
		fclose(fp);	
		return 0;
	}	
}


//ST_d_wifiMsg *RetG_devWifiMsg(){
//	return &unique_dwifiMsg;
//}

int d_setWifi(char *pcSSID, char *pcPwd, int iEncrytType){
	ST_d_wifiMsg *pwifiMsg = &unique_dwifiMsg;	
	if(pwifiMsg->netFlag == 0 ){
		strncpy(pwifiMsg->cwifimsg.ssid,pcSSID,sizeof(pwifiMsg->cwifimsg.ssid));
		strncpy(pwifiMsg->cwifimsg.pwd,pcPwd,sizeof(pwifiMsg->cwifimsg.pwd));			
		printf("netFlag==0,start setWifi\n");
		if( 0 != devS_SetWifi(pwifiMsg->cwifimsg.ssid,pwifiMsg->cwifimsg.pwd,iEncrytType) ){
			printf("devS_SetWifi err\n");
			return -1;		
		}	
	}
	else
		printf("netFlag!=0,regard as have net\n");		

	return 0;
}


int d_initDevWifi(){
	ST_d_wifiMsg *pwifiMsg = &unique_dwifiMsg;
	ParaInit_devWifiMsg(&pwifiMsg->cwifimsg,&pwifiMsg->CdevWf_pathfile);

	if(  pwifiMsg->cwifimsg.flag == 1){
		d_setWifi(pwifiMsg->cwifimsg.ssid,pwifiMsg->cwifimsg.pwd,0);
		printf("d_initDevWifi  ->  d_setWifi exe\n");
	}else{
		printf("pwifiMsg->cwifimsg.flag != 1,wait setwifi cmd\n");
	}
	
	return 0;
}


static int d_saveWifiMsg(){
//	FILE *fp;
	ST_d_wifiMsg *pwifiMsg = &unique_dwifiMsg;	
	FILE *fp = fopen(pwifiMsg->CdevWf_pathfile.file, "w");
	if(fp == NULL)
	{
		perror("fopen");				// 文件打开失败，打印错误信息
		fclose(fp); 
		printf("d_saveWifiMsg err_1\n");	
		return -1;
	}
//	pwifimsg->flag = 1;
	pwifiMsg->cwifimsg.flag = 1;
	fprintf(fp, "Flag:%d,SSID:%s,PWD:%s\n", pwifiMsg->cwifimsg.flag,pwifiMsg->cwifimsg.ssid,pwifiMsg->cwifimsg.pwd);
	fclose(fp); 
	printf("d_saveWifiMsg succeed\n");	
	return 0;
}


/*
int d_sendStateToWifi(int netState){
	ST_d_wifiMsg *pwifiMsg = &unique_dwifiMsg;
	pwifiMsg->netFlag = netState;
	if(netState == 2){  //save wifimsg
		d_saveWifiMsg();		
	}
	return 0;
}  */


//1 :eth    2:wifi  
int d_setNet(int nettype,int flag){  //
	u8 *State = &unique_dwifiMsg.netState;
	u8 *StateLast = &unique_dwifiMsg.netState_last;
	if(nettype == 1){
		if(flag == 1)
			*State = *State|0x02;		
		else
			*State = *State&0xfd;		
	}else if(nettype == 2){
		if(flag == 1)
			*State = *State|0x04;		
		else
			*State = *State&0xfb;		
	}

	if(*State != *StateLast){
		printf("*State:%d\n",*State);
		printf("*StateLast:%d\n",*StateLast);
	
		*StateLast = *State ;
		if((*State |0x02) == 0x02){
			printf("have net :wired \n");
		}

		if((*State |0x04) == 0x04){
			printf("have net :wifi \n");
			d_saveWifiMsg();			
		}	

		if((*State &0x06) == 0){
			printf("no net :wifi & wired \n");
		}else{  // 有网络，不进行wifi配网了
			ST_d_wifiMsg *pwifiMsg = &unique_dwifiMsg;			
			pwifiMsg->netFlag = 1;	
			printf("(*State &0x06) != 0..pwifiMsg->netFlag = 1 \n");
		}
	}

	return 0;
		

	


}


