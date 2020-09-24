#ifndef DEV_NETWORK_H_
#define DEV_NETWORK_H_

//#include <stdio.h>
#include "basetypesJX.h"



int d_initDevWifi();
int d_setWifi(char *pcSSID, char *pcPwd, int iEncrytType);
int d_sendStateToWifi(int netState);
int d_setNet(int nettype,int flag);



#endif




