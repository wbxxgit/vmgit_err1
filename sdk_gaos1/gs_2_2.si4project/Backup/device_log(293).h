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


#define __INFO_PRINTF(string,args...) printf("\033[32m""[%s] <%s> (%d): "string"\033[0m",GET_TIME,__FUNCTION__,__LINE__,##args)

#define __DEBUG_PRINTF(string,args...) printf("\033[34m""[%s] <%s> (%d): "string"\033[0m",GET_TIME,__FUNCTION__,__LINE__,##args)

#define __TRACE_PRINTF(string,args...) printf("\033[33m""[%s] <%s> (%d): "string"\033[0m",GET_TIME,__FUNCTION__,__LINE__,##args)

#define __ERROR_PRINTF(string,args...) printf("\033[31m""[%s] <%s> (%d): "string"\033[0m",GET_TIME,__FUNCTION__,__LINE__,##args)
#else

#define __INFO_PRINTF(string,args...) 

#define __DEBUG_PRINTF(string,args...) 

#define __TRACE_PRINTF(string,args...) 
#define __ERROR_PRINTF(string,args...) 
#endif
#endif