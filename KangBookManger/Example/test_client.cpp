/*
 * > File Name: test_client.cpp
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年06月08日 星期四 19时22分27秒
 */

#include <iostream>
#include <string>
#include "net.h"
int main(int argc ,char **argv)
{
    short port = atoi(argv[2]);
    Client client(std::string(argv[1]),port);
    client.Connect();
    client.handle();
}
