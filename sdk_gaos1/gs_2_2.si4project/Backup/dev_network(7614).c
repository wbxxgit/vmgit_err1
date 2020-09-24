#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "basetypesJX.h" 
#include "device_log.h" 

//device_log.h


#include "zj_type.h"
#include "zj_log.h"
#include "ZJre_comCfg.h"

//ZJre_comCfg.h

#include "dev_zj_funReg.h"
//#include "forZb_comCfg.h"

//DEVICE_SYSTEM_PATH_PARENT

#include "IPC_MediaBuff.h"
#include "sdk_commonstruct.h"
#include "sdkout_impl.h" 

#include "sAuxiliary.h"
/*
#include <arpa/inet.h>
#include <linux/sockios.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <linux/ethtool.h>
#include <net/if.h>
#include <ctype.h> */

//#include "dev_systemSup.h" 
//#include "ZJre_camera.h" 


//#define PARAFILEPATH_DEV "/mnt/testconfig/residuepara"
#define PARAFILEPATH_DEV  DEVICE_SYSTEM_PATH_PARENT  "/devAdapt"
#define PARAFILEPATH_FILE_WIFIMSG_DEV  PARAFILEPATH_DEV "/wifiMsg.txt"

#define DEFAULT_SETNETTYEP    0X07

#define DEFAULT_SSID "Xiaomi_8AC0"
#define DEFAULT_PWD "12345677"



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

#define NEW_INIT_DWIFIFMSG  {0,0,0,{0},{PARAFILEPATH_DEV,PARAFILEPATH_FILE_WIFIMSG_DEV}}

static ST_d_wifiMsg unique_dwifiMsg = {0,0,0,{0},{PARAFILEPATH_DEV,PARAFILEPATH_FILE_WIFIMSG_DEV}};


static int devS_SetWifi(char *pcSSID, char *pcPwd, int iEncrytType){
	T_SDK_WIRELESS_PARAMS t_wireless_param = {0};
//	t_wireless_param.un_encrypt = iEncrytType;
	t_wireless_param.un_encrypt = 1;
	t_wireless_param.e_wifi_connect_status = E_SDK_DISCONNECT;
	strncpy(t_wireless_param.a_SSID,pcSSID,sizeof(t_wireless_param.a_SSID));
	strncpy(t_wireless_param.a_passwd,pcPwd,sizeof(t_wireless_param.a_passwd));	
	t_wireless_param.e_wifi_mode = E_SDK_WIFI_CLIENT_MODE;

	DPRI_INFO("e_wifi_mode:%d\n",t_wireless_param.e_wifi_mode);
	DPRI_INFO("e_wifi_connect_status:%d\n",t_wireless_param.e_wifi_connect_status);
	DPRI_INFO("a_SSID:%s\n",t_wireless_param.a_SSID);
	DPRI_INFO("a_passwd:%s\n",t_wireless_param.a_passwd);
	DPRI_INFO("un_encrypt:%d\n",t_wireless_param.un_encrypt);
	
	if(0 != SDK_Cmd_Impl(SDKCMD_SET_WIRELESS_PARAM,  (void*)(&t_wireless_param))){
		DPRI_INFO("SDKCMD_SET_WIRELESS_PARAM err\n");
		return -1;
	}
	DPRI_INFO("SDKCMD_SET_WIRELESS_PARAM succeed.[%s]-[%s]-[%d]\n",pcSSID,pcPwd,iEncrytType);
	return 0;
}

#if 0
static int ParaInit_devWifiMsg(ST_devwifiSsid *pwifimsg,ST_devWf_pathfile *pathfile){
	if(pathfile->path == NULL || pathfile->file == NULL)
		return -1;
	
	if( !access(pathfile->file,0)){
		DPRI_INFO("*residuePara*:exist:%s\n",pathfile->file);
		FILE *pFile = fopen(pathfile->file, "r");
		if (pFile == NULL) {
			fclose(pFile);	
			return -1;
		}	
		if( EOF != fscanf(pFile,"%d,%[^,],%[^,]",&pwifimsg->flag,pwifimsg->ssid,pwifimsg->pwd)  )
		{
			DPRI_INFO("*residuePara*:read succeed\n");
			DPRI_INFO("read flag:%d, ssid:%s,pwd:%s\n",pwifimsg->flag,pwifimsg->ssid,pwifimsg->pwd);
			fclose(pFile);	
		}else{
			DPRI_INFO("*residuePara*:read file err,try again write\n");
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
			fprintf(fp, "%d,%s,%s", pwifimsg->flag,DEFAULT_SSID,DEFAULT_PWD);
			fclose(fp);					
		}
		return 0;	
	}else{
		DPRI_INFO("*residuePara*:no exist mkdir:%s\n",pathfile->file);
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
		fprintf(fp, "%d,%s,%s", pwifimsg->flag,DEFAULT_SSID,DEFAULT_PWD);
		fclose(fp);	
		return 0;
	}	
}
#endif

static int d_saveWifiMsg(ST_d_wifiMsg *pwifiMsg){
	if(  (strlen(pwifiMsg->cwifimsg.ssid)==0) ||(strlen(pwifiMsg->cwifimsg.pwd)==0)  ){
		DPRI_INFO("strlen(pwifiMsg->cwifimsg.ssid)==0 err\n");
		return -1;
	}

	FILE *fp = fopen(pwifiMsg->CdevWf_pathfile.file, "w");
	if(fp == NULL)
	{
		perror("fopen");				// 文件打开失败，打印错误信息
		fclose(fp); 
		DPRI_INFO("d_saveWifiMsg err_1\n");	
		return -1;
	}
	DPRI_INFO("save ssid:%s\n",pwifiMsg->cwifimsg.ssid);
	DPRI_INFO("save pwd:%s\n",pwifiMsg->cwifimsg.pwd);
//	pwifiMsg->cwifimsg.flag = 1;
	fprintf(fp, "%d,%s,%s", pwifiMsg->cwifimsg.flag,pwifiMsg->cwifimsg.ssid,pwifiMsg->cwifimsg.pwd);
	fclose(fp); 
	DPRI_INFO("d_saveWifiMsg succeed\n");	
	return 0;
}


static int d_readWifiMsg(ST_d_wifiMsg *pwifiMsg){
	if(access(pwifiMsg->CdevWf_pathfile.file,0)){
		DPRI_INFO("d_readWifiMsg access err\n");
		return -1;
	}
	
	FILE *pFile = fopen(pwifiMsg->CdevWf_pathfile.file, "r");
	if (pFile == NULL) {
		fclose(pFile);	
		return -1;
	}	

    while(!feof(pFile)) putchar(fgetc(pFile));  // 显示到屏幕上
    rewind(pFile);   // fp回到开始位置	


	if( EOF == fscanf(pFile,"%d,%[^,],%[^,]",&pwifiMsg->cwifimsg.flag,pwifiMsg->cwifimsg.ssid,pwifiMsg->cwifimsg.pwd) ){
		DPRI_INFO("d_readWifiMsg fscanf err\n");
		fclose(pFile);
		return -1;
	}
	DPRI_INFO("read flag:%d, ssid:%s,pwd:%s\n",pwifiMsg->cwifimsg.flag,pwifiMsg->cwifimsg.ssid,pwifiMsg->cwifimsg.pwd);
	fclose(pFile);
	return 0;
}


static int ParaInit_devWifiMsgImp(ST_d_wifiMsg *pwifiMsg){
	if( 0 != d_readWifiMsg(pwifiMsg)){
		DPRI_INFO("*residuePara*:no exist mkdir:%s\n",pwifiMsg->CdevWf_pathfile.file);
		char acCmdBuf[256] = {0};
		snprintf(acCmdBuf, sizeof(acCmdBuf), "mkdir -p %s", pwifiMsg->CdevWf_pathfile.path);
		system(acCmdBuf);

		pwifiMsg->cwifimsg.flag = 1;  //默认初始 测试网络
		strncpy(pwifiMsg->cwifimsg.ssid,DEFAULT_SSID,sizeof(pwifiMsg->cwifimsg.ssid));
		strncpy(pwifiMsg->cwifimsg.pwd,DEFAULT_PWD,sizeof(pwifiMsg->cwifimsg.pwd));		
		d_saveWifiMsg(pwifiMsg);		
	}else{
		DPRI_INFO("ParaInit_devWifiMsgImp:file exist,init read succeed\n");	

	}
	return 0;
}
//ST_d_wifiMsg *RetG_devWifiMsg(){
//	return &unique_dwifiMsg;
//}

int d_setWifi(char *pcSSID, char *pcPwd, int iEncrytType){
	ST_d_wifiMsg *pwifiMsg = &unique_dwifiMsg;	
	if(pwifiMsg->netFlag == 0 ){
		strncpy(pwifiMsg->cwifimsg.ssid,pcSSID,sizeof(pwifiMsg->cwifimsg.ssid));
		strncpy(pwifiMsg->cwifimsg.pwd,pcPwd,sizeof(pwifiMsg->cwifimsg.pwd));			
		DPRI_INFO("netFlag==0,start setWifi\n");
		if( 0 != devS_SetWifi(pwifiMsg->cwifimsg.ssid,pwifiMsg->cwifimsg.pwd,iEncrytType) ){
			DPRI_INFO("devS_SetWifi err\n");
			return -1;		
		}	
	}
	else
		DPRI_INFO("netFlag!=0,regard as have net\n");	
	return 0;
}

static int setSdkNetType(EN_ZJ_NETWORK_TYPE enum_para){
	if( NULL == dj_network_GtFTbl()->f_SetNetWorkType){
		DPRI_INFO("f_SetNetWorkType no register!\n");
		return -1;			
	}	
	dj_network_GtFTbl()->f_SetNetWorkType(enum_para);
	DPRI_INFO("setSdkNetType,netType:%d\n",enum_para);	
	return 0;
}


static int d_startWifiCmd_QRcode(){

	DPRI_INFO("d_startWifiCmd_QRcode has exed\n");	
	return 0;
}

int d_QRcode_sendToSdk(u8 *QRstr){
	if( NULL == dj_network_GtFTbl()->f_SetQRCodeString){
		DPRI_INFO("f_SetQRCodeString no register!\n");
		return -1;			
	}	
	dj_network_GtFTbl()->f_SetQRCodeString(QRstr);
	DPRI_INFO("d_QRcode_sendToSdk has exed\n");	
	return 0;
}


static int d_startWifiCmd_AP(){

	setSdkNetType(EN_ZJ_NETWORK_TYPE_AP);
	DPRI_INFO("d_startWifiCmd_AP has exed\n");	
	return 0;
}

static int d_startWifiCmd_qssid(){

	DPRI_INFO("d_startWifiCmd_qssid has exed\n");	
	return 0;
}


static int d_startInitSetWifiCmd(u8 setNetTpy){

	if( (setNetTpy&0x01)== 0x01 )
		d_startWifiCmd_QRcode();

	if( (setNetTpy&0x02)== 0x02 )
		d_startWifiCmd_AP();

	if( (setNetTpy&0x04)== 0x04 )
		d_startWifiCmd_qssid();
	
	
	return 0;
}

int d_initDevWifi(){
	ST_d_wifiMsg *pwifiMsg = &unique_dwifiMsg;
//	ParaInit_devWifiMsg(&pwifiMsg->cwifimsg,&pwifiMsg->CdevWf_pathfile);
	ParaInit_devWifiMsgImp(pwifiMsg);
	if(  pwifiMsg->cwifimsg.flag == 1){
		d_setWifi(pwifiMsg->cwifimsg.ssid,pwifiMsg->cwifimsg.pwd,0);
		DPRI_INFO("d_initDevWifi  ->  d_setWifi exe\n");
	}else{
		DPRI_INFO("pwifiMsg->cwifimsg.flag != 1,wait setwifi cmd\n");
		d_startInitSetWifiCmd(DEFAULT_SETNETTYEP);		
		
	}

	pwifiMsg->cwifimsg.flag = 1; //需要复位才能进行再次配网
	d_saveWifiMsg(pwifiMsg);
	return 0;
}

int d_triggerSetNet(){
	ST_d_wifiMsg pwifiMsg = NEW_INIT_DWIFIFMSG; //	d_readWifiMsg(pwifiMsg);
	if( 0 != d_readWifiMsg(&pwifiMsg))
		return -1;	
	pwifiMsg.cwifimsg.flag = 0; //需要复位才能进行再次配网
	d_saveWifiMsg(&pwifiMsg);
	DPRI_INFO("d_triggerSetNet has been exed\n");
	return 0;
}

//EN_ZJ_NETWORK_TYPE_WIRED



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
		DPRI_INFO("*State:%d\n",*State);
		DPRI_INFO("*StateLast:%d\n",*StateLast);
	
		*StateLast = *State ;
		if((*State &0x02) == 0x02){
			DPRI_INFO("have net :wired \n");
			setSdkNetType(EN_ZJ_NETWORK_TYPE_WIRED);
		}

		if((*State &0x04) == 0x04){
			DPRI_INFO("have net :wifi \n");
			d_saveWifiMsg(&unique_dwifiMsg);	
			setSdkNetType(EN_ZJ_NETWORK_TYPE_WIFI);//EN_ZJ_NETWORK_TYPE_WIFI
		}	

		if((*State &0x06) == 0){
			DPRI_INFO("no net :wifi & wired \n");
			setSdkNetType(EN_ZJ_NETWORK_TYPE_NONET);
		}else{  // 有网络，不进行wifi配网了
			ST_d_wifiMsg *pwifiMsg = &unique_dwifiMsg;			
			pwifiMsg->netFlag = 1;	
			DPRI_INFO("(*State &0x06) != 0..pwifiMsg->netFlag = 1 \n");
			
		}
	}

	return 0;

}


