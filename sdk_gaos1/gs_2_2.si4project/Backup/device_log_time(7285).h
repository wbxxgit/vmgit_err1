
#ifndef __DEVICE_LOG_TIME_H__
#define __DEVICE_LOG_TIME_H__

char *device_Log_GetCurTime();


#endif




/*

#include <stdio.h>
#include <time.h>

char *device_Log_GetCurTime()
{
    static char s[20];
    time_t t;
    struct tm* ltime;
    time(&t);
    ltime = localtime(&t);
    strftime(s, 20, "%Y-%m-%d %H:%M:%S", ltime);
    return s;
} */
