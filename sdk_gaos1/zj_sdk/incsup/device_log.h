#ifndef __DEVICE_LOG_H__
#define __DEVICE_LOG_H__


#include <stdio.h>
#include "device_log_time.h"

#define GET_TIME device_Log_GetCurTime()


#define DPRI_INFO(string,args...) printf("\033[32m""[%s][%s] <%s> (%d): "string"\033[0m",GET_TIME,(unsigned char*)"ADAPT",__FUNCTION__,__LINE__,##args)

#define DPRI_DEBUG(string,args...) printf("\033[34m""[%s][%s] <%s> (%d): "string"\033[0m",GET_TIME,(unsigned char*)"ADAPT",__FUNCTION__,__LINE__,##args)

#define DPRI_TRACE(string,args...) printf("\033[33m""[%s][%s] <%s> (%d): "string"\033[0m",GET_TIME,(unsigned char*)"ADAPT",__FUNCTION__,__LINE__,##args)

#define DPRI_ERROR(string,args...) printf("\033[31m""[%s][%s] <%s> (%d): "string"\033[0m",GET_TIME,(unsigned char*)"ADAPT",__FUNCTION__,__LINE__,##args)

#endif