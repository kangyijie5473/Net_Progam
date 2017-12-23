//
// Created by kang on 17-11-15.
//

#include "LogStream.h"
#include "AsyncLogger.h"
#include <iostream>
#include <cstdio>
#include <zconf.h>

std::function<void(const char *, int)> LogStream::outputLogMessage = nullptr;

void toAsyncLogFile(const char *, int);
void testDataType(){

    std::string e = "hello";

    int t= 90000;
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


    testDataType();
    sleep(1);
}