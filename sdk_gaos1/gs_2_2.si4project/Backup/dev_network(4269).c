#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "basetypesJX.h" 
#include "device_log.h" 

#include "zj_type.h"
#include "zj_log.h"
#include "ZJre_comCfg.h"

#include "dev_zj_funReg.h"

#include "IPC_MediaBuff.h"
#include "sdk_commonstruct.h"
#include "sdkout_impl.h" 

#include "sAuxiliary.h"
#include "dev_hint.h"
#include "dev_network.h"


#define PARAFILEPATH_DEV  DEVICE_SYSTEM_PATH_PARENT  "/devAdapt"
#define PARAFILEPATH_FILE_WIFIMSG_DEV  PARAFILEPATH_DEV "/wifiMsg.txt"

#define DEFAULT_SETNETTYEP    0X07  //bit0: QRcode  bit1: AP bit2: qssid
#define DEFAULT_SSID "Xiaomi_8AC0"
#define DEFAULT_PWD "12345677"

#define DEVNET_EXEINTER_WIFI_NOR  10  //2S/200MS = 10
#define DEVNET_EXEINTER_WIFI_QLINK  1  //200/200MS = 1
#define DEVNET_EXEINTER_WIRED_NOR  15  //3S/200MS = 10


typedef enum{
	EN_D_NTYPE_NOEXE,
	EN_D_NTYPE_NONET,
	EN_D_NTYPE_QLINK,
	EN_D_NTYPE_NORWIFI,
	EN_D_NTYPE_WIREDNET		
}EN_dev_netType;


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


typedef struct  de_wifiMsg{
	EN_dev_netType netSta;
	EN_dev_netType netSta_last;
	u32 exeInterval_wired;
	u32 exeInterval_wifi;
}ST_de_wifiMsg;


typedef struct  d_wifiSsidMsg{
	u8 state;  
	char matchSsid[32];

}ST_d_wifiSsidMsg;

#define WIFISSID_QLINK "ChinaNet-QLINK"
#define WIFISSIDPWD_QLINK "ChinaNet-QLINK-IOT"


#define NEW_INIT_DWIFIFMSG  {0,0,0,{0},{PARAFILEPATH_DEV,PARAFILEPATH_FILE_WIFIMSG_DEV}}

#define NEW_INIT_DE_WIFIFMSG  {EN_D_NTYPE_NONET,EN_D_NTYPE_NONET,DEVNET_EXEINTER_WIRED_NOR,DEVNET_EXEINTER_WIFI_QLINK}  //DEVNET_EXEINTER_WIRED_NOR

static ST_d_wifiMsg unique_dwifiMsg = {0,0,0,{0},{PARAFILEPATH_DEV,PARAFILEPATH_FILE_WIFIMSG_DEV}};

ST_d_wifiSsidMsg qlinkMsg = {0};


//static ST_de_wifiMsg unique_wifiMsg = {0};
static ST_de_wifiMsg unique_wifiMsg = NEW_INIT_DE_WIFIFMSG;


static pthread_t tid_waitQRAPthread;
static u32 global_waitQRAPtime = 90;


int d_wifiSsidJudge_matchQlink(){   // 1:enter ssid process  0:skip  other:error

	if(qlinkMsg.state == 1){
		
		T_SDK_NETWORK_PARAMS t_net_param = {0};		
		if(0 != SDK_Cmd_Impl(SDKCMD_GET_NETWORK_PARAM, &t_net_param)){
			DPRI_INFO("SDKCMD_GET_NETWORK_PARAM err\n");
			return -1;
		}
		DPRI_INFO("t_net_param.t_wireless_param.a_SSID:%s\n",t_net_param.t_wireless_param.a_SSID);

		int ret;
		DPRI_INFO("matchQlink qlinkMsg.matchSsid:%s\n",qlinkMsg.matchSsid);
		ret = strcmp(t_net_param.t_wireless_param.a_SSID,qlinkMsg.matchSsid);
		if(ret == 0){
			DPRI_INFO("strcmp succeed\n");
			qlinkMsg.state = 2;
			//start qlink
			if( NULL == dj_network_GtFTbl()->f_SetAutoConnStatus){
				DPRI_INFO("f_SetAutoConnStatus no register!\n");
				return -1;			
			}	
			dj_network_GtFTbl()->f_SetAutoConnStatus(1);
			DPRI_INFO("f_SetAutoConnStatus(1)\n");
			return 1;
		}else{
			DPRI_INFO("strcmp failed,send qlink,wifi not match,other linked\n");
			qlinkMsg.state = 4;	
			return -1;
		}	
	}else if(qlinkMsg.state == 2){

		T_SDK_NETWORK_PARAMS t_net_param = {0};		
		if(0 != SDK_Cmd_Impl(SDKCMD_GET_NETWORK_PARAM, &t_net_param)){
			DPRI_INFO("SDKCMD_GET_NETWORK_PARAM err\n");
			return -1;
		}
		DPRI_INFO("qlinkMsg.state == 2,a_SSID:%s\n",t_net_param.t_wireless_param.a_SSID);

		int ret;
		DPRI_INFO("matchQlink qlinkMsg.matchSsid:%s\n",qlinkMsg.matchSsid);
		ret = strcmp(t_net_param.t_wireless_param.a_SSID,qlinkMsg.matchSsid);
		if(ret == 0){	
			return 1;//always stay qlink ssid
		}else{
			DPRI_INFO("is switch wifi,normal net\n");
			qlinkMsg.state = 3;	
			return 0;
		}		
	}
	return 0;  //other is normal net
}

int d_wifi_matchSsid_0isSame(char *Cssid){
	T_SDK_NETWORK_PARAMS t_net_param = {0}; 	
	if(0 != SDK_Cmd_Impl(SDKCMD_GET_NETWORK_PARAM, &t_net_param)){
		DPRI_INFO("SDKCMD_GET_NETWORK_PARAM err\n");
		return -1;
	}
	int ret = strcmp(t_net_param.t_wireless_param.a_SSID,Cssid);
	if(ret == 0)	
		return 0;// 0 is same
	return 1;
}


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
//	DPRI_INFO("save pwd:%s\n",pwifiMsg->cwifimsg.pwd);
//	pwifiMsg->cwifimsg.flag = 1;
	fprintf(fp, "%d,%s,%s", pwifiMsg->cwifimsg.flag,pwifiMsg->cwifimsg.ssid,pwifiMsg->cwifimsg.pwd);
	fclose(fp); 
	DPRI_INFO("d_saveWifiMsg succeed,save ssid:%s-pwd:%s-flag:%d\n",pwifiMsg->cwifimsg.ssid,pwifiMsg->cwifimsg.pwd,pwifiMsg->cwifimsg.flag);
//	DPRI_INFO("d_saveWifiMsg succeed\n");	
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

	DPRI_INFO("ee\n");
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

		pwifiMsg->cwifimsg.flag = SETNET_IMME_QRAP;  //default init is 	QRAP
		strncpy(pwifiMsg->cwifimsg.ssid,DEFAULT_SSID,sizeof(pwifiMsg->cwifimsg.ssid));
		strncpy(pwifiMsg->cwifimsg.pwd,DEFAULT_PWD,sizeof(pwifiMsg->cwifimsg.pwd));		
		d_saveWifiMsg(pwifiMsg);		
	}else
		DPRI_INFO("ParaInit_devWifiMsgImp:file exist,init read succeed\n");	
	
	return 0;
}

int d_setWifi(char *pcSSID, char *pcPwd, int iEncrytType){
//	ST_de_wifiMsg *pdewifi = &unique_wifiMsg;
	ST_d_wifiMsg *pwifiMsg = &unique_dwifiMsg;	
//	if(pwifiMsg->netFlag == 0 ){
	if(unique_wifiMsg.netSta != EN_D_NTYPE_WIREDNET ){
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
	u32 n_record = 1;
	if(SDK_Cmd_Impl(SDKCMD_SET_QR_NETWORK, &n_record) != 0)
	{
		DPRI_INFO("SDKCMD_SET_QR_NETWORK error\n"); 
		return -1;
	}
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
	u32 n_record = 1;	
	if(SDK_Cmd_Impl(SDKCMD_SET_AP_NETWORK, &n_record) != 0)
	{
		DPRI_INFO("SDKCMD_SET_AP_NETWORK error\n"); 
		return -1;
	}
	setSdkNetType(EN_ZJ_NETWORK_TYPE_AP);
	DPRI_INFO("d_startWifiCmd_AP has exed\n");	
	return 0;
}




void *pthread_waitQRandAPst(void *arg){

	u32 num_int = *((u32 *)arg);	
	DPRI_INFO("pthread_waitQRandAPst create. time:%d \n",num_int);
	while(--num_int != 0){
		sleep(1);
		if(num_int%5 == 0)
			DPRI_INFO("pthread_waitQRandAPst sleep:%d \n",num_int);
	
	//	if( (unique_dwifiMsg.netState &0x02) == 0x02 ){  //unique_wifiMsg
		if( unique_wifiMsg.netSta == EN_D_NTYPE_NORWIFI ){
			dev_hintSoundP(DEVVOICE_QL_SUCCEED);
			DPRI_INFO("have net,exit wait thread.residue time:%d \n",num_int);
			break;
		}	
	}
	if(num_int == 0){
		dev_hintSoundP(DEVVOICE_QL_FAIL);
		d_startWifiCmd_QRcode();
		d_startWifiCmd_AP();
		DPRI_INFO("exe QRAP setup Net \n");
	}
	return 0;
}

int d_startWifiCmd_qssid(){
	dev_hintSoundP(DEVVOICE_QL_START);	
	pthread_create(&tid_waitQRAPthread,NULL,pthread_waitQRandAPst,(void *)&global_waitQRAPtime);

	qlinkMsg.state = 1;
	strncpy((char *)qlinkMsg.matchSsid,WIFISSID_QLINK,sizeof(qlinkMsg.matchSsid));
	d_setWifi(WIFISSID_QLINK,WIFISSIDPWD_QLINK,0);
	dev_hintSoundP(DEVVOICE_QL_START);
	DPRI_INFO("d_startWifiCmd_qssid has exed\n");	
	return 0;
}



static int d_startInitSetWifiCmd(u8 setNetTpy,u8 qsFlag){

	if(qsFlag == 1){
		if( (setNetTpy&0x04)== 0x04 )
			d_startWifiCmd_qssid();	

	}else{
	
		if( (setNetTpy&0x01)== 0x01 )
			d_startWifiCmd_QRcode();
		if( (setNetTpy&0x02)== 0x02 )
			d_startWifiCmd_AP();		
	}	
	return 0;
}

int d_initDevWifi(){
	ST_d_wifiMsg *pwifiMsg = &unique_dwifiMsg;
	ParaInit_devWifiMsgImp(pwifiMsg);	
//	pwifiMsg->cwifimsg.flag =0; //tested delete
	if(  pwifiMsg->cwifimsg.flag == SETNET_NOREQUIRE){
	//	d_setWifi(pwifiMsg->cwifimsg.ssid,pwifiMsg->cwifimsg.pwd,0);
		DPRI_INFO("flag == SETNET_NOREQUIRE,let gaosi SDK auto setwifi\n");
	}else{
		u8 qssidFlag = 0;
		if(pwifiMsg->cwifimsg.flag == SETNET_QLINK)  //ssid flag is 2
			qssidFlag = 1;
		
		pwifiMsg->cwifimsg.flag = SETNET_NOREQUIRE; //需要复位才能进行再次配网
		d_saveWifiMsg(pwifiMsg);		
		DPRI_INFO("pwifiMsg->cwifimsg.flag != SETNET_NOREQUIRE,wait setwifi cmd\n");
		d_startInitSetWifiCmd(DEFAULT_SETNETTYEP,qssidFlag);			
	}
	return 0;
}

int d_triggerSetNet(EN_type_setNet netType){
	ST_d_wifiMsg pwifiMsg = NEW_INIT_DWIFIFMSG; //	d_readWifiMsg(pwifiMsg);
	if( 0 != d_readWifiMsg(&pwifiMsg)){
		DPRI_INFO("d_readWifiMsg exe err\n");
		return -1;	
	}		
	pwifiMsg.cwifimsg.flag = netType; 
	d_saveWifiMsg(&pwifiMsg);
	if(netType == SETNET_IMME_QRAP)
		dev_hintSoundP(DEVVOICE_TRISETNET_QR);
	else
		dev_hintSoundP(DEVVOICE_TRISETNET_QLINK);
	DPRI_INFO("d_triggerSetNet has been exed,flag:%d\n",pwifiMsg.cwifimsg.flag);
	return 0;
}


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






static int d_netStateSetPro(EN_dev_netType netTP){

	if(netTP == EN_D_NTYPE_QLINK){
		DPRI_INFO("EN_D_NTYPE_QLINK:has linked succeed\n");
		if( NULL == dj_network_GtFTbl()->f_SetAutoConnStatus){
			DPRI_INFO("f_SetAutoConnStatus no register!\n");
			return -1;			
		}	
		dj_network_GtFTbl()->f_SetAutoConnStatus(1);
		DPRI_INFO("start qlink process\n");	
	}else if(netTP == EN_D_NTYPE_NORWIFI){
	//	ST_de_wifiMsg *pwifimsg = &unique_wifiMsg;
	//	pwifimsg->exeInterval_wifi = DEVNET_EXEINTER_WIFI_NOR; // 2s/200ms = 
		unique_wifiMsg.exeInterval_wifi = DEVNET_EXEINTER_WIFI_NOR; // 2s/200ms = 
	}

	EN_ZJ_NETWORK_TYPE sdkNet;
	if(netTP == EN_D_NTYPE_NONET)
		sdkNet = EN_ZJ_NETWORK_TYPE_NONET;
	else if(netTP == EN_D_NTYPE_QLINK)
		sdkNet = EN_ZJ_NETWORK_TYPE_NONET;
	else if(netTP == EN_D_NTYPE_NORWIFI)
		sdkNet = EN_ZJ_NETWORK_TYPE_WIFI;
	else if(netTP == EN_D_NTYPE_WIREDNET)		
		sdkNet = EN_ZJ_NETWORK_TYPE_WIRED;
	else 		
		sdkNet = EN_ZJ_NETWORK_TYPE_NONET;
	setSdkNetType(sdkNet);

	return 0;
}


int d_netJudge_wired(EN_dev_netType *pNet){
	char strip[20] = {0};
	if( 0 == getipJudge_bynameRetIPc("eth0",strip,sizeof(strip))   )
		*pNet = EN_D_NTYPE_WIREDNET;
	else
		*pNet = EN_D_NTYPE_NONET;
	return 0;
}

int d_netJudge_wifi(EN_dev_netType *pNet){
	char strip[20] = {0};
	
	if( 0 == getipJudge_bynameRetIPc("ra0",strip,sizeof(strip))    ){
		if( 1 ==  judgeIp_isGateway_0isGate(strip,sizeof(strip)) ){  //not gate,normal ip
		
			int ret = d_wifi_matchSsid_0isSame(qlinkMsg.matchSsid);
			if(ret == 0){  // qlink
				*pNet = EN_D_NTYPE_QLINK;
			}else if(ret == 1){  // othe wifi
				*pNet = EN_D_NTYPE_NORWIFI;
			}else{
				DPRI_INFO("d_wifi_matchSsid_0isSame cmd err\n");
			}
		
		}else{
			*pNet = EN_D_NTYPE_NONET;
		}

	}else
		*pNet = EN_D_NTYPE_NONET;

	return 0;
}


int d_dualNetCheck(u32 exeCount){
	EN_dev_netType nettmp = EN_D_NTYPE_NOEXE;
	ST_de_wifiMsg *pwifimsg = &unique_wifiMsg;

#ifdef MMACRO_NOFLASH_T3_E1102	
	DPRI_INFO("test star\n");
	if(pwifimsg->netSta != EN_D_NTYPE_WIREDNET){
		if( exeCount%pwifimsg->exeInterval_wifi == 0){
			d_netJudge_wifi(&nettmp);
			if(exeCount % (pwifimsg->exeInterval_wifi *20) == 0 ){  //only show
				DPRI_INFO("d_netJudge_wifi(&nettmp) has been exe,nettmp:%d,exeInterval_wifi[%d]\n",nettmp,pwifimsg->exeInterval_wifi);
			}
		}
	}
#endif		
	
	if( exeCount%pwifimsg->exeInterval_wired == 0){
		d_netJudge_wired(&nettmp);
		if(exeCount % (pwifimsg->exeInterval_wired *20) == 0 ){  //only show
			DPRI_INFO("d_netJudge_wired(&nettmp) has been exe,nettmp:%d,exeInterval_wired[%d]\n",nettmp,pwifimsg->exeInterval_wired);
		}		
	}

	if(nettmp != EN_D_NTYPE_NOEXE){

		pwifimsg->netSta = nettmp;
		if(pwifimsg->netSta != pwifimsg->netSta_last){
			pwifimsg->netSta_last = nettmp;
			DPRI_INFO("net changed,now is:%d\n",nettmp);	
			d_netStateSetPro(nettmp);
		}	
	}

	return 0;
}



