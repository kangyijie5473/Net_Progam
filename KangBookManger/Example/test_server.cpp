/*
 * > File Name: test.cpp
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年06月08日 星期四 17时36分00秒
 */

#include <iostream>
#include "net.h"
int main(int argc, char **argv)
{
    int port = atoi(argv[1]);
    Server server(port);
    server.listen();
    server.start_main_thread();
    
}
