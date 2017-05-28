/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
 ************************************************************************/
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
int fd;
struct sockaddr_in serverAddr;
int key;
const int MAXSIZE = 5000;
const int PORT = 1314;                  // Your server bind port
const char *IP_ADDR = "192.168.30.123"; //Your server Ip address
int main(void)
{
    fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(fd > 0);
    
    memset(&serverAddr, 0, sizeof(struct sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    key = inet_aton(IP_ADDR, &serverAddr.sin_addr);
    key = connect(fd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in ));
    assert(!key);

    char  send_buffer[MAXSIZE];
    char read_buffer[MAXSIZE];
    int n;
    while(1){
        memset(&send_buffer, 0, sizeof(send_buffer));
        memset(&read_buffer, 0, sizeof(read_buffer));
        scanf("%s",send_buffer);
        if(strcmp("exit",send_buffer) == 0)
            break;
        if(write(fd, send_buffer, strlen(send_buffer)+1) < 0){
            continue;
        }
        n = read(fd, read_buffer, sizeof(read_buffer));
        if(n < 0)
            continue;
        puts(read_buffer);
    }
    close(fd);
    printf("close\n");
    return 0 ;


    

    

}
