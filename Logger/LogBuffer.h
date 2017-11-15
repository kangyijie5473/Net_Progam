/*
 * > File Name: LogBuffer.h
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年11月14日 星期二 22时33分51秒
 */

#ifndef _LOGBUFFER_H
#define _LOGBUFFER_H
class LogBuffer{
public:
    explicit LogBuffer(int size){}
    LogBuffer(){}

    bool append(const char *str, int len);
    void clear();
    unsigned int free_size();
    static const int buffer_max_size  = 1000;


    /* debug */
    char *show(){ return  buffer_;};
private:
    char buffer_[buffer_max_size];

    int now_index_;
};
#endif
