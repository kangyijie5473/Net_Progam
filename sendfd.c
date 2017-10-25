/*
 * > File Name: sendfd.c
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年10月25日 星期三 17时17分48秒
 */

#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

static const int CONTROL_LEN = CMSG_LEN(sizeof(int));
int recv_fd(int fd)
{
    struct iovec iov[1];
    struct msghdr msg;
    char buf[0];

    iov[0].iov_base = buf;
    iov[0].iov_len = 1;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;

    struct cmsghdr cm;
    msg.msg_control = &cm;
    msg.msg_controllen = CONTROL_LEN;
    
    recvmsg(fd, &msg, 0);

    int fd_to_pass = *(int *)CMSG_DATA(&cm);
    return fd_to_pass;

}
void send_fd(int fd, int fd_to_send)
{
    struct iovec iov[1];
    struct msghdr msg;
    char buf[0];

    iov[0].iov_base = buf;
    iov[0].iov_len = 1;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;

    struct cmsghdr cm;
    cm.cmsg_len = CONTROL_LEN;
    cm.cmsg_level = SOL_SOCKET;
    cm.cmsg_type = SCM_RIGHTS;
    *(int *)CMSG_DATA(&cm) = fd_to_send;
    msg.msg_control = &cm;
    msg.msg_controllen = CONTROL_LEN;

    sendmsg(fd, &msg, 0);
}
int main(void)
{
    int pipefd[2];
    int fd_to_pass = 0;
    assert(socketpair(PF_UNIX, SOCK_DGRAM, 0, pipefd) != -1);

    pid_t pid = fork();
    if(pid == 0){
        close(pipefd[0]);
        fd_to_pass = open("./Makefile", O_RDWR, 0666);
        send_fd(pipefd[1], (fd_to_pass > 0) ? fd_to_pass : 0);
        close(fd_to_pass);
        exit(0);
    }

    close(pipefd[1]);
    fd_to_pass = recv_fd(pipefd[0]);
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    read(fd_to_pass, buf, 1024);
    printf("got %d\n%s\n",fd_to_pass, buf);
    close(fd_to_pass);
}
