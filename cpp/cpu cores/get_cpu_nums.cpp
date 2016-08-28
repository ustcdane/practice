/*===============================================================
*   Copyright (C) 2016 All rights reserved.
*   
*   文件名称：get_cpu_nums.cpp
*   创 建 者: Daniel
*   创建日期：2016年08月28日
*   描    述：测试获得cpu核数
*   备    注: 
*   更新日志：
*
================================================================*/
 
#include <iostream>

#include "GetCpuNums.hpp"

using namespace std;
// please add your code here!

int main() {
    unsigned int sz = coreCount();
    cout<<"cpu cores: "<<sz<<endl;
    return 0;
}
