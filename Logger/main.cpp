//
// Created by kang on 17-11-15.
//

#include "LogStream.h"
#include <iostream>
#include <cstdio>
int main(void)
{
    LogStream Logger;
    unsigned int a = 987654321;
    Logger << a;
    Logger << 0;
    printf("%s",Logger.show());
}