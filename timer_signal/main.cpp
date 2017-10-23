/*
 * > File Name: main.cpp
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年10月19日 星期四 15时47分51秒
 */

#include <iostream>
#include <cstdio>
#include "./TimerList.hpp"
#include "./Network.cpp"
#include <assert.h>
int main(void)
{
    TimerList<Timer> timerlist(5);
    Network server(5473,5);
    server.Listen();
    
    int epollfd = server.initMainLoop();
    assert(epollfd != -1);
    timerlist.setEpollFd(epollfd);

    server.setAlarm();
    while(1){
        server.startMainLoop(timerlist);
        if(server.dealTimeEvent(timerlist)){
            server.setAlarm();
        }
    }
}
