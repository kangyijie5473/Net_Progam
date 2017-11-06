/*
 * > File Name: demo.cpp
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年10月30日 星期一 20时49分04秒
 */

#include <iostream>
#include <cstring>
#include <sys/time.h>
using namespace std;
static unsigned long long getCpuKhz()
{
    FILE *fp = fopen("/proc/cpuinfo","r");
    if(!fp) 
        return 1;
    char buf[4096] = {0};
    fread(buf,1,sizeof(buf),fp);
    fclose(fp);

    char *lp = strstr(buf,"cpu MHz");
    if(!lp) 
        return 1;
    lp += strlen("cpu MHz");
    while(*lp == ' ' || *lp == '\t' || *lp == ':')
        ++lp;

    double mhz = atof(lp);
    unsigned long long u = (unsigned long long)(mhz * 1000);
    return u;

}
static unsigned long long counter(void)
{
    register uint32_t lo, hi;
    register unsigned long long o;
    __asm__ __volatile__ (
            "rdtscp" : "=a"(lo), "=d"(hi)
            );
    o = hi;
    o <<= 32;
    return (o | lo);

}
unsigned long long getTime()
{
    static uint32_t khz = getCpuKhz();
    return counter() / khz;
}
unsigned long long getTime2()
{
    struct timeval now = { 0 };
    gettimeofday( &now,NULL );
    unsigned long long u = now.tv_sec;
    u *= 1000;
    u += now.tv_usec / 1000;
    return u;
}
int main()
{
    cout << getTime() << endl;
    cout << getTime2() << endl;
}
