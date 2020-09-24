#include <stdio.h>
#include <unistd.h>

#include <stdlib.h>
#include <string.h>
#include <time.h>


#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef unsigned char  vu8;
typedef unsigned int  vu16;
//时间结构体
typedef struct
{
	vu8 nHour;
	vu8 nMinute;
	vu8 nSecond;
	//公历日月年周
	vu8  nMonth;
	vu8  nDay;
	vu8  nWeek;
	vu16 nYear;

} RTC_TIME_DEF;





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
	sprintf(pDest, "%s", myStrncpy(pDest, arrDate, 3));

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

	sprintf(pDest, "%s", myStrncpy(pDest, arrDate+4, 2));
	//int atoi(const char *nptr);
	stTime.nDay = atoi(pDest);

	sprintf(pDest, "%s", myStrncpy(pDest, arrDate + 4 + 3, 4));
	//int atoi(const char *nptr);
	stTime.nYear = atoi(pDest);
	//time
	sprintf(pDest, "%s", myStrncpy(pDest, arrTime, 2));
	stTime.nHour = atoi(pDest);
	sprintf(pDest, "%s", myStrncpy(pDest, arrTime+3, 2));
	stTime.nMinute = atoi(pDest);
	sprintf(pDest, "%s", myStrncpy(pDest, arrTime + 3 + 3, 2));
	stTime.nSecond = atoi(pDest);
	return stTime;
}

int main(int argc,char *argv[])
{

	int i = 3;

	RTC_TIME_DEF pshow_compiletm = GetSoftWareBuildTargetTime();
	printf("*******Get_Compile_Date--y:%d-M:%d-d:%d-h:%d-m:%d-s:%d\n",
			pshow_compiletm.nYear,pshow_compiletm.nMonth,pshow_compiletm.nDay,
			pshow_compiletm.nHour,pshow_compiletm.nMinute,pshow_compiletm.nSecond);


	while(i--)
	{

		sleep(1);
		printf("hello jing\n");
	}
}
