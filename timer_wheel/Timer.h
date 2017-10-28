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

    Timer(int timerFd, struct timespec *timerTimeout, std::function<bool(int,int)> func): fd(timerFd), doJob(func) 
    {
        timeout.tv_sec = timerTimeout->tv_sec;
        timeout.tv_nsec = timerTimeout->tv_nsec;
    }
    ~Timer(){doJob = nullptr;}
    int rotation;
    std::function<bool(int,int)> doJob;
    int fd;
    struct timespec timeout;
};
#endif
