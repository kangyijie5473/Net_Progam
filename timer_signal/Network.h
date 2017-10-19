//
// Created by kang on 17-10-1.
//

#ifndef KEDIS_NETWORK_H
#define KEDIS_NETWORK_H
#include <cstdio>
#include <cstdlib>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <sys/resource.h>
#include <string>
#include <cstring>
#include <iostream>
#include <csignal>
#include <cassert>
#include <list>
static const unsigned int MAX_POLL_SIZE = 10000;
static const int LISTEN_LEN  = 1000;
class Network{
public:
    Network(short port, int keepAliveTime):_port(port), _timeoutFlag(false), _timeSlot(keepAliveTime) {}
    ~Network(){close(_socket_fd);}

    int Listen();
    bool setNonBlocking(int fd);
    template<typename T> int  startMainLoop(T &timerlist);
    int  initMainLoop();
    template<typename T> bool dealTimeEvent(T &timerlist);
    bool addFd(int fd);
    bool delFd(int fd);
    void setAlarm();
    void addSig(int sig);

private:
    socklen_t sock_len;
    int _socket_fd,_conn_fd;
    short _port;
    bool _timeoutFlag;
    struct epoll_event _events[MAX_POLL_SIZE];
    struct sockaddr_in _server_addr,_client_addr;
    int _kdpfd;
    int _nfds;
    int _pipeFd[2];
    int _timeSlot;
};

#endif //KEDIS_NETWORK_H
