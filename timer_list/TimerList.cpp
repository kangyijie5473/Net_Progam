/*
 * > File Name: list.cpp
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年10月11日 星期三 17时12分28秒
 */

#include <iostream>

#include "./TimerList.h"

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
