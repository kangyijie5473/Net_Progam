/*************************************************************************
	> File Name: echo_server.c
	> Author: Jack Kang
	> Mail: kangyijie@xiyoulinux.org
	> Created Time: 2017年03月28日 星期二 19时13分04秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<sys/resource.h>
const int LEN = 5000;
const int MAXPOLLSIZE = 10000;
const int MAXLINE = 100;
const int PORT = 1314;
int handle(int conn_fd);
int init_daemon()
{
    pid_t pid;
    pid = fork();
    if(pid > 0)
        exit(0);
    chdir("\\");
    umask(0);
    setsid();
    pid = fork();
    if(pid > 0)
        exit(0);
    return 0;
}
int setnonblocking(int socket_fd)
{
    if(fcntl(socket_fd, F_SETFL, fcntl(socket_fd, F_GETFD, 0)| O_NONBLOCK) == -1){
        return -1;
    }
    else return 0;
}

int main(void)
{
    init_daemon();
    int socket_fd ;
    int kdpfd, n;
    int nfds;
    int conn_fd;
    char buf[MAXLINE];
    int acceptCount = 0;
    struct epoll_event ev;
    struct epoll_event events[MAXPOLLSIZE];
    struct rlimit rt;
    struct sockaddr_in server_addr,client_addr;
    socklen_t sock_len = sizeof(struct sockaddr_in);
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    int optrval = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (void *)&optrval, sizeof(int));
    memset(&server_addr, 0 ,sizeof(struct sockaddr_in));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    setnonblocking(socket_fd);

    bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    listen(socket_fd, LEN);

    kdpfd = epoll_create(MAXPOLLSIZE);
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = socket_fd;
    if(epoll_ctl(kdpfd, EPOLL_CTL_ADD, socket_fd, &ev) < 0){
        fprintf(stderr, "epoll set insertion error '%d' to poll failed %s\n",socket_fd,strerror(errno));
        return -1;
    }
    int curfds = 1;
    printf("epollserver start up port %d, max connection is %d,backlog is %d\n",PORT,MAXPOLLSIZE, socket_fd);
    while(1){
        nfds = epoll_wait(kdpfd, events, curfds, -1);
        if(nfds == -1){
            perror("epoll_wait");
            continue;
        }
        for(n = 0; n < nfds; ++n){
            if(events[n].data.fd == socket_fd){
                conn_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &sock_len);
                if(conn_fd < 0){
                    perror("accept error");
                    continue;
                }

                sprintf(buf, "accept from %s %d\n",inet_ntoa(client_addr.sin_addr),client_addr.sin_port);
                printf("%d:%s",++acceptCount,buf);

                if(curfds >= MAXPOLLSIZE){
                    fprintf(stderr, "too many connection, more than %d\n",MAXPOLLSIZE);
                    close(conn_fd);
                    continue ;
                }
                if(setnonblocking(conn_fd) < 0){
                    perror("setnonblocking error");
                }
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = conn_fd;
                if(epoll_ctl(kdpfd, EPOLL_CTL_ADD, conn_fd,&ev) < 0){
                    fprintf(stderr, "add socket '%d'to epoll failed:%s\n",conn_fd,strerror(errno));
                    return -1;
                }
                curfds++;
                continue;

            }
            
            if(handle(events[n].data.fd) < 0){
                epoll_ctl(kdpfd, EPOLL_CTL_DEL, events[n].data.fd, &ev);
                curfds--;
            }
        }
    }
    close(socket_fd);
    return 0;

}
int handle(int conn_fd)
{
   int nread;
   char buf[MAXLINE];

    nread = read(conn_fd, buf, MAXLINE);
    if(nread == 0){
        printf("client close connection\n");
        close(conn_fd);
        return -1;
    }
    if(nread < 0){
        perror("read error");
        close(conn_fd);
        return -1;
    }
    if(!strcmp("quit",buf))
        close(conn_fd);
    write(conn_fd, buf, nread);
    return 0;
}
