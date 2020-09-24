#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "basetypesJX.h" 
#include "zj_type.h"
#include "zj_log.h"

#include "sAuxiliary.h"

//#include "dev_zj_funReg.h"
//#include "forZb_camera.h"  

//#include "IPC_MediaBuff.h"
//#include "sdk_commonstruct.h"
//#include "sdkout_impl.h" 


//字符串截取
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
}
//得到软件编译时间 
/*
RTC_TIME_DEF GetSoftWareBuildTargetTime(void)
{
    char arrDate[20]; //Jul 03 2018
    char arrTime[20]; //06:17:05
    char pDest[20];
    RTC_TIME_DEF stTime;

    sprintf(arrDate,"%s",__DATE__);//Jul 03 2018
    sprintf(arrTime,"%s",__TIME__);//06:17:05    
    //char *strncpy(char *dest, const char *src, int n)
    //(char*)(&(pDest[0])) = myStrncpy(pDest, arrDate, 3);
  //  sprintf(pDest, "%s", myStrncpy(pDest, arrDate, 3));
	strncpy(pDest,arrDate,3);
	printf("%s",pDest);
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
  //   sprintf(pDest, "%s", myStrncpy(pDest, arrDate+4, 2));
    //int atoi(const char *nptr);
    stTime.nDay = atoi(pDest);

	strncpy(pDest, arrDate + 4 + 3, 4);
 //   sprintf(pDest, "%s", myStrncpy(pDest, arrDate + 4 + 3, 4));
    //int atoi(const char *nptr);
    stTime.nYear = atoi(pDest);
    //time
    strncpy(pDest, arrTime, 2);
  //  sprintf(pDest, "%s", myStrncpy(pDest, arrTime, 2));
    stTime.nHour = atoi(pDest);
	strncpy(pDest, arrTime+3, 2);
  //  sprintf(pDest, "%s", myStrncpy(pDest, arrTime+3, 2));
    stTime.nMinute = atoi(pDest);
	strncpy(pDest, arrTime + 3 + 3, 2);
 //   sprintf(pDest, "%s", myStrncpy(pDest, arrTime + 3 + 3, 2));
    stTime.nSecond = atoi(pDest);
    return stTime;
}*/

RTC_TIME_DEF GetSoftWareBuildTargetTime(void)
{
    char arrDate[20] = {0}; //Jul 03 2018
    char arrTime[20]= {0}; //06:17:05
    char pDest[20]= {0};
    RTC_TIME_DEF stTime;

	memset(&stTime,0,sizeof(RTC_TIME_DEF));
    sprintf(arrDate,"%s",__DATE__);//Jul 03 2018
    sprintf(arrTime,"%s",__TIME__);//06:17:05  
//	printf("arrTime:%s\n",arrTime);
	strncpy(pDest,arrDate,3);
//	printf("%s\n",pDest);
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
//	printf("%s\n",pDest);
    stTime.nYear = atoi(pDest);
    //time
//    memset(pDest,0,20);
    strncpy(pDest, arrTime, 2);
	pDest[2] = '\0';
//	printf("%s\n",pDest);
    stTime.nHour = atoi(pDest);
//	memset(pDest,0,20);
	strncpy(pDest, arrTime+3, 2);
	pDest[2] = '\0';
//	printf("%s\n",pDest);
    stTime.nMinute = atoi(pDest);
//	memset(pDest,0,20);
	strncpy(pDest, arrTime + 3 + 3, 2);
	pDest[2] = '\0';
//	printf("%s\n",pDest);
    stTime.nSecond = atoi(pDest); 
    return stTime;
}


u32 lin_GetTickCount()
{
  struct timespec stTime;

  clock_gettime(CLOCK_REALTIME, &stTime);

  return (stTime.tv_sec * 1000 + stTime.tv_nsec/1000000);
}

int sdk_file_check(void){
	if( !access("/mnt/testconfig/system",0)){
		printf("/testconfig/system exist\n");
	}else{
		system("mkdir -p  /mnt/testconfig/system");
	}	
	if( !access("/mnt/testconfig/config",0)){
		printf("/testconfig/config exist\n");
	}else{
		system("mkdir -p  /mnt/testconfig/config");
	}
	system("ls -l /mnt/testconfig/");
	return 0;
}

