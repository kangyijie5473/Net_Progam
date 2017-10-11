/*
 * > File Name: TimerList.h
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年10月11日 星期三 19时12分34秒
 */

#ifndef _TIMERLIST_H
#define _TIMERLIST_H
#include <list>
#include <time.h>
template<typename T>
class TimerList{
public:
    explicit TimerList(int length): _listMaxLength(length) {}
    TimerList() = default;
    ~TimerList();
    bool addEvent(const T &x);
    bool addEvent(T &&x);
    time_t getLeastTimeout();
    bool delEvent(int TimerId);
    void freeList();

private:
    int _listMaxLength;
    std::list<T> eventList;
    typename std::list<T>::iterator getIndex(time_t timeout);
};

#endif
