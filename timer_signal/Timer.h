/*
 * > File Name: Timer.h
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年10月11日 星期三 19时19分11秒
 */

#ifndef _TIMER_H
#define _TIMER_H
#include <functional>
#include <time.h>
struct Timer{

    Timer(int timerFd, time_t timerTimeout, std::function<bool(int,int)> func): fd(timerFd),timeout(timerTimeout),doJob(func) {}
    ~Timer(){doJob = nullptr;}
    std::function<bool(int,int)> doJob;
    int fd;
    time_t timeout;
};
#endif
