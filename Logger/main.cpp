//
// Created by kang on 17-11-15.
//

#include "LogStream.h"
#include <iostream>
#include <cstdio>
void testDataType(){
    LogStream logger;
    unsigned int a = 123456;
    int b = 789;
    unsigned long long c = 123456;
    long long d = 789;
    std::string e = "hello world";
    LogStream logger_new;
    bool f = false;
    bool g = true;
    logger << a << b << std::string(" ")  << " "<< c << d  << e << f << g ;
    //logger_new << logger;
    printf("%s",logger.data());
}
int main(void)
{
    testDataType();
}