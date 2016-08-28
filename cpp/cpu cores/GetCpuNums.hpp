/*===============================================================
*   Copyright (C) 2016 All rights reserved.
*   
*   文件名称：get_cpu_nums.hpp
*   创 建 者 Daniel
*   创建日期：2016年08月28日
*   描    述：获得cpu核数
*   备    注: 
*   更新日志：
*
================================================================*/
 
#ifndef _GET_CPU_NUMS_H
#define _GET_CPU_NUMS_H
#ifdef __cplusplus
extern "C"
{
#endif

    #if !defined (_WIN32) && !defined (_WIN64)
    #define LINUX
        #include <unistd.h>
    #else
    #define WINDOWS
        #include <windows.h>
    #endif

    unsigned int coreCount() {
        unsigned int count = 1; // 至少一个
    #if defined (LINUX)
        count = sysconf(_SC_NPROCESSORS_CONF);
    #elif defined (WINDOWS)
        SYSTEM_INFO si;
        GetSystemInfo(&si);
        count = si.dwNumberOfProcessors;
    #endif
        return count;
    }

#ifdef __cplusplus
}
#endif //GET_CPU_NUMS_H
#endif
