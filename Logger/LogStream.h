/*
 * > File Name: LogStream.h
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年11月14日 星期二 22时22分12秒
 */

#ifndef _LOGSTREAM_H
#define _LOGSTREAM_H

#include <string>
#include "LogBuffer.h"
//class LogBuffer;TOdo:how to declare
class LogStream{
public:
    LogStream &operator<<(bool);

    LogStream &operator<<(unsigned char);
    LogStream &operator<<(const char);
    LogStream &operator<<(const char *);

    LogStream &operator<<(unsigned int);
    LogStream &operator<<(unsigned long);
    LogStream &operator<<(unsigned long long);
    LogStream &operator<<(unsigned short);
    LogStream &operator<<(long);
    LogStream &operator<<(int);
    LogStream &operator<<(long long);
    LogStream &operator<<(short);

    LogStream &operator<<(double);
    LogStream &operator<<(float);

    LogStream &operator<<(const std::string &);
    LogStream &operator<<(const LogBuffer &);

    /* debug */
    const char *show(){return buffer_.show();}
private:
    template <typename T>
    int getIntegerString_(char *buf, T value);
    LogBuffer buffer_;

    template <typename T>
    void appendFormatInteger_(T i);

};
#endif
