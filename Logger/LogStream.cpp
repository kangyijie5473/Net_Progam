/*
 * > File Name: LogStream.cpp
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年11月14日 星期二 22时22分03秒
 */
#include "LogStream.h"
#include <algorithm>


LogStream& LogStream::operator<<(bool b) {
    buffer_.append(b ? "T" : "F", 1);
    return *this;
}
LogStream& LogStream::operator<<(const char c)
{
    buffer_.append(&c, 1);
    return *this;
}

/* Integer to string */
static const char digits[19] = {'9', '8', '7', '6', '5', '4', '3', '2', '1', '0',
                                '1', '2', '3', '4', '5', '6', '7', '8', '9'};
static const char *zero = digits + 9;
template <typename T>
int LogStream::getIntegerString_(char *buf, T value) {
    char *p = buf;
    do{
        int i = value % 10;
        *p++ = zero[i];
        value /= 10;
    }while (value);
    if(value < 0)
        *p++ = '-';
    *p = '\0';
    std::reverse(buf, p);
    return p - buf;
}

/* Integer */
LogStream& LogStream::operator<<(unsigned int i)
{
    char buf[30];//TODO:30 is temp
    int len = getIntegerString_(buf, i);
    buffer_.append(buf, len);
    return *this;
}
LogStream& LogStream::operator<<(int i)
{
    char buf[30];//TODO:30 is temp
    int len = getIntegerString_(buf, i);
    buffer_.append(buf, len);
    return *this;
}
//LogStream& LogStream::operator<<(unsigned long)
//{
//
//}
//LogStream& LogStream::operator<<(long)
//{
//
//}
//LogStream& LogStream::operator<<(long long)
//{
//
//}
//LogStream& LogStream::operator<<(unsigned long long)
//{
//
//}
//
