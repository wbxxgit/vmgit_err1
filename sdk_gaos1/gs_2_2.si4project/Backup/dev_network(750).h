#ifndef DEV_NETWORK_H_
#define DEV_NETWORK_H_

//#include <stdio.h>
#include "basetypesJX.h"



int d_initDevWifi();
int d_setWifi(char *pcSSID, char *pcPwd, int iEncrytType);
int d_setNet(int nettype,int flag);

int d_triggerSetNet();
int d_QRcode_sendToSdk(u8 *QRstr);
int d_wifiSsidJudge_matchQlink();

int d_startWifiCmd_qssid();





#endif




