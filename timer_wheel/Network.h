//
// Created by kang on 17-10-1.
//

#ifndef KEDIS_NETWORK_H
#define KEDIS_NETWORK_H
#include <cstdio>
#include <cstdlib>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/timerfd.h>
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
static const unsigned int MAX_POLL_SIZE = 10000;
static const int LISTEN_LEN  = 1000;
class Network{
public:
    Network(short port):_port(port) {}
    ~Network(){close(_socket_fd);}

    int Listen();
    bool setNonBlocking(int fd);
    int  startMainLoop(int timeout );//default @timeout is -1
    int  initMainLoop();

private:
    socklen_t sock_len;
    int _socket_fd,_conn_fd;
    short _port;
    struct epoll_event _ev;
    struct epoll_event _events[MAX_POLL_SIZE];
    struct sockaddr_in _server_addr,_client_addr;
    int _kdpfd;
    int _nfds;

};


#endif //KEDIS_NETWORK_H
