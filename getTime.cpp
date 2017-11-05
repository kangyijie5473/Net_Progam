/*
 * > File Name: demo.cpp
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年10月30日 星期一 20时49分04秒
 */

#include <iostream>
#include <cstring>
using namespace std;
static unsigned long long getCpuKhz()
{
        FILE *fp = fopen("/proc/cpuinfo","r");
        if(!fp) return 1;
        char buf[4096] = {0};
        fread(buf,1,sizeof(buf),fp);
        fclose(fp);

        char *lp = strstr(buf,"cpu MHz");
        if(!lp) return 1;
        cout  << lp << endl;
        lp += strlen("cpu MHz");
        while(*lp == ' ' || *lp == '\t' || *lp == ':')
    {
                ++lp;
            
    }

        double mhz = atof(lp);
        unsigned long long u = (unsigned long long)(mhz * 1000);
        return u;

}
int main()
{
    cout << getCpuKhz() << endl;
}
