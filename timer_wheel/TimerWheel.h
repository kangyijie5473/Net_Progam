/*
 * > File Name: TimerWheel.h
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年10月28日 星期六 10时24分47秒
 */

#ifndef _TIMERWHEEL_H
#define _TIMERWHEEL_H
template <typename T>
class TimerWheel{
    public:
    TimerWheel(int num): slotsNum(num),clurSlot(0) {}
    ~TimerWheel() = default;

    template <typename T>
    bool addEvent(T &event);

    template <typename T>
    bool dealEvent();

//    template <typename T>
//    void tick();

    private:
    int slotsNum;
    int clurSlot;
    std::vector<TimerList<T>> slots;
};
#endif
