//
// Created by kang on 17-10-1.
//

#include "Network.h"
static bool delNotAliveFd(int notAliveFd, int epollFd)
{
    printf("notAliveFd is %d\n",notAliveFd);
    if(epoll_ctl(epollFd, EPOLL_CTL_DEL, notAliveFd, NULL) < 0)
        return true;
    else
        return false;
}
static int pipeFd;
void sig_handler(int sig)
{
    char msg = 1;
    send(pipeFd, (char *)&msg, 1, 0);
    printf("send success\n");
}
void Network::addSig(int sig)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler =sig_handler;
    sa.sa_flags |= SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGALRM);
    assert(sigaction(sig, &sa, NULL) != -1);
    printf("addSig\n");
}
int Network::Listen() {
    int optrval = 1;
    sock_len = sizeof(struct sockaddr_in);

    _socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, (void *)&optrval,sizeof(int));

    memset(&_server_addr, 0, sizeof(struct sockaddr_in));
    _server_addr.sin_family = AF_INET;
    _server_addr.sin_port = htons(_port);
    _server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    this->setNonBlocking(_socket_fd);

    bind(_socket_fd, (struct sockaddr *)&_server_addr, sizeof(struct sockaddr_in));
    listen(_socket_fd, LISTEN_LEN);
    return 1;
}
bool Network::setNonBlocking(int fd) {
    if(fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)|O_NONBLOCK) == -1){
        return false;
    }else
        return true;
}

bool Network::delFd(int fd)
{
    if(epoll_ctl(_kdpfd, EPOLL_CTL_DEL, fd, NULL) < 0)
        return false;
    else{
    	close(fd);
        return true;
    }

}

bool Network::addFd(int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLRDHUP | EPOLLET;
    if(epoll_ctl(_kdpfd, EPOLL_CTL_ADD, fd, &ev) < 0)
        return false;
    else
        return true;

}
int Network::initMainLoop() {
    socketpair(AF_UNIX, SOCK_STREAM, 0, _pipeFd);
    _kdpfd = epoll_create(MAX_POLL_SIZE);
    std::cout << "start" << std::endl;
    struct epoll_event ee = {0};
    ee.events = EPOLLIN | EPOLLET;
    ee.data.fd = _socket_fd;
    if(epoll_ctl(_kdpfd, EPOLL_CTL_ADD, _socket_fd, &ee) < 0){
        perror("epoll_ctl");
        return -1;
    } ;

    memset(&ee, 0, sizeof(struct epoll_event));
    ee.events = EPOLLIN | EPOLLET;
    ee.data.fd = _pipeFd[0];
    setNonBlocking(_pipeFd[1]);
    pipeFd = dup(_pipeFd[1]);

    if(epoll_ctl(_kdpfd, EPOLL_CTL_ADD, _pipeFd[0], &ee) < 0){
        perror("epoll_ctl");
        return -1;
    } 
    addSig(SIGALRM);
    return _kdpfd;
}
template<typename T>
bool Network::dealTimeEvent(T &timerlist)
{
    if(_timeoutFlag){
        timerlist.dealEvent();
        _timeoutFlag = false;
        return true;
    }else
        return false;
}
void Network::setAlarm()
{
    alarm(_timeSlot);
}
template<typename T>
int Network::startMainLoop(T &timerlist) {
    int curfds = 1;// It is just a demo
    int acceptCount = 0;
    _nfds = epoll_wait(_kdpfd, _events, curfds, -1);
    if(_nfds == -1 && errno != EINTR){
        perror("epoll_wait");
        return -1;
    }
    for(int n = 0; n < _nfds; n++){
        if(_events[n].data.fd == _socket_fd){
            _conn_fd = accept(_socket_fd, (struct sockaddr *)&_client_addr, &sock_len);
            if(_conn_fd < 0){
                perror("accept error");
                continue;
            }
            acceptCount++;

            if(curfds >= MAX_POLL_SIZE){
                close(_conn_fd);
                continue;
            }
            if(this->setNonBlocking(_conn_fd) < 0){
                perror("set_non_blocking error");
            }
           
            addFd(_conn_fd);
            timerlist.addEvent(std::move(Timer(_conn_fd, time(NULL) + 3 * _timeSlot, delNotAliveFd)));
            curfds++;
            continue;
        }else if(_events[n].events & EPOLLRDHUP){
            std::cout << "HUP" << std::endl;
            delFd(_events[n].data.fd);//kernel version > 2.6.9
            continue;
        }else if(_events[n].data.fd == _pipeFd[0]){
            _timeoutFlag = true;
            continue;
        }else if(_events[n].events & EPOLLIN){
        }
    }
}

