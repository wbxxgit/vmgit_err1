#ifndef COMMON_UTILS_H
#define COMMON_UTILS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct
{
	unsigned long long a_total_size;	//总容量
	unsigned long long a_used_size;	    //已用容量
	unsigned long long a_free_size;	    //未用容量
}tf_info;

//执行控制台指令
int exec_cmd(const char *cmd);		
//获取系统剩余内存
unsigned long get_system_mem_freeKb();		
//获取目录剩余存储空间
unsigned long long get_system_tf_freeKb(char* dir);
//获取系统自启动时间到现在的tick数
int64_t get_tick_count();
//从全路径文件名中获取文件名
void  get_file_pure_name(char* full_name,char * dest);

int get_system_tf_info(char* dir,tf_info *info);

#ifdef __cplusplus
}
#endif

#endif