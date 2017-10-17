/*
 * > File Name: main.cpp
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年10月11日 星期三 17时45分21秒
 */

#include <iostream>
#include "Network.h" 
#include "./TimerList.hpp"
#include "./Timer.h"

static int func(void *arg)
{
    std::cout << "ding dong! Now is  "<< time(NULL) << std::endl;
    return 1;
}

int main(void)
{
    TimerList<Timer> timerlist(5);

    
    Timer t,b;
    t.fd = 1;
    t.timerId = 2;
    t.timeout = time(NULL) + 10;
    t.doJob = func;

    b.timeout = t.timeout + 5;
    b.doJob = func;
    
    int timeout;
    Network server(5473);
    server.Listen();
    server.initMainLoop();
    timerlist.addEvent(t);
    timerlist.addEvent(b);

    while(!timerlist.isEmpty()){
        timeout = (timerlist.getLeastTimeout() - time(NULL) ) * 1000;
        server.startMainLoop(timeout);
        timerlist.dealEvent();
    }

}
