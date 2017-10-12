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


template <typename T>
TimerList<T>::~TimerList()
{
    freeList();
}

template <typename T>
void TimerList<T>::freeList()
{
    eventList.clear();
}

template <typename T>
bool TimerList<T>::addEvent(const T &event)
{
    auto it = getIndex(event.timeout);
    eventList.insert(it, event);
    return true;
}

template <typename T>
bool TimerList<T>::addEvent(T &&event)
{
    auto it = getIndex(event.timeout);
    eventList.insert(it, std::forward(event));
    return true;
}

template <typename T>
time_t TimerList<T>::getLeastTimeout()
{
    return eventList.front().timeout;
}

template <typename T>
bool TimerList<T>::delEvent(int timerId)
{
    for(auto it : eventList){
        if(it.timerId == timerId){
            eventList.erase(it);
            return true;
        }
    }
    return false;
}

template <typename T>
typename std::list<T>::iterator
TimerList<T>::getIndex(time_t timeout)
{

    typename std::list<T>::iterator i = eventList.begin();
    for(; i != eventList.end(); i++)
        if(i->timeout > timeout)
            return i;
    return i;
}

#endif
