#ifndef SAUXILIARY_H_
#define SAUXILIARY_H_

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

u32 lin_GetTickCount();
RTC_TIME_DEF GetSoftWareBuildTargetTime(void);

int sdk_file_check(void);
int getipJudge();



#endif




