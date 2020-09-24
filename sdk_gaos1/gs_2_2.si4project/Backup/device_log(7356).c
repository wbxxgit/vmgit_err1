#ifndef __DEVICE_LOG_H__
#define __DEVICE_LOG_H__


#ifndef __TIME_FUNC__
#define __TIME_FUNC__
#include <stdio.h>
#include <time.h>
static char *device_Log_GetCurTime()
{
    static char s[20];
    time_t t;
    struct tm* ltime;
    time(&t);
    ltime = localtime(&t);
    strftime(s, 20, "%Y-%m-%d %H:%M:%S", ltime);
    return s;
}
#define GET_TIME device_Log_GetCurTime()


#define DPRI_INFO(string,args...) printf("\033[32m""[%s][%s] <%s> (%d): "string"\033[0m",GET_TIME,(unsigned char*)"ADAPT",__FUNCTION__,__LINE__,##args)

#define DPRI_DEBUG(string,args...) printf("\033[34m""[%s][%s] <%s> (%d): "string"\033[0m",GET_TIME,(unsigned char*)"ADAPT",__FUNCTION__,__LINE__,##args)

#define DPRI_TRACE(string,args...) printf("\033[33m""[%s][%s] <%s> (%d): "string"\033[0m",GET_TIME,(unsigned char*)"ADAPT",__FUNCTION__,__LINE__,##args)

#define DPRI_ERROR(string,args...) printf("\033[31m""[%s][%s] <%s> (%d): "string"\033[0m",GET_TIME,(unsigned char*)"ADAPT",__FUNCTION__,__LINE__,##args)
#else

#define DPRI_INFO(string,args...) 
#define DPRI_DEBUG(string,args...) 
#define DPRI_TRACE(string,args...) 
#define DPRI_ERROR(string,args...) 
#endif
#endif