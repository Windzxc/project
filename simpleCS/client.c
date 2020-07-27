#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 520
#define PORT 2020

int main(int argc, char *argv[])
{
    int clientfd;
    struct sockaddr_in address;
    int len;
    int result;
    char buf[MAXLINE];

    memset(&address, 0, sizeof(address));
    len = sizeof(address);

    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd < 0)
    {
        printf("socket error\n");
        exit(1);
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    //printf("address.sin_addr is %s\n",address.sin_addr.s_addr);
    printf("发起连接。。。\n");

    result = connect(clientfd, (struct sockaddr *)&address, len);

    if (result < 0)
    {
        printf("oops: client\n");
        exit(1);
    }
    printf("连接成功！\n");
    read(clientfd, buf, MAXLINE);
    fputs(buf, stdout);

    close(clientfd);
    return 0;

}