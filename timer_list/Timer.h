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
    int fd;
    int timerId;
    time_t timeout;
    std::function<int(void *)> doJob;
};
#endif
