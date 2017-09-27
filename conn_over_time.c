/*
 * > File Name: conn_over_time.c
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年09月27日 星期三 07时58分23秒
 */

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
const char *ip = "123.206.89.123";
const short port = 5473;
int  timeout_connect(int time)
{
    int ret = 0;
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    //server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_aton(ip, &server_addr.sin_addr);

    int socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    struct timeval timeout;
    timeout.tv_sec = time;
    timeout.tv_usec = 0;
    socklen_t len = sizeof(timeout);
    ret = setsockopt(socket_fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len);
    assert(ret != -1);
    ret = connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret == -1){
        if (errno = EINPROGRESS){
            printf("connecting timeout\n");
            return -1;
        }
        printf("error\n");
    }
    return socket_fd;
}
int main(void)
{
    int socket_fd = timeout_connect(10);
    if (socket_fd < 0){
        return 1;
    }
    return 0;
}
