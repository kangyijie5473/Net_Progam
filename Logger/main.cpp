//
// Created by kang on 17-11-15.
//

#include "LogStream.h"
#include "AsyncLogger.h"
#include <iostream>
#include <cstdio>
std::function<void(const char *, int)> LogStream::outputLogMessage = nullptr;
void toAsyncLogFile(const char *, int);
void testDataType(){
    //LogStream logger;

    unsigned int a = 123456;
    int b = 789;
    unsigned long long c = 123456;
    long long d = 789;
    std::string e = "worldkl";
    bool f = false;
    bool g = true;

    //logger << a << b << std::string(" ")  << " "<< c << d  << e << f << g ;
    int t= 100;
    while(t--){
        LogStream logger;
        logger << e;
    }

}
AsyncLogger testLogger("hello_log");


void toAsyncLogFile(const char *src, int len)
{
    testLogger.append(src, len);
}

int main(void)
{
    LogStream::setOutputLogMessage(std::bind(toAsyncLogFile, std::placeholders::_1, std::placeholders::_2));
    testLogger.run();
//    testLogger.setDebug();
//    testLogger.setDebug();
//    testLogger.getDebug();
//    testLogger.run();
//    testLogger.getDebug();

    testDataType();
}