#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 520
#define HOSTLEN 120
#define PORTNUM 2020
#define BACKLOG 5

int make_server_socket(int port, int backlog);
void echo(int fd);

int main(int argc, int *argv[])
{
    int listenfd;
    int connfd;
    
    listenfd = make_server_socket(PORTNUM, BACKLOG);
    printf("端口打开监听，服务器已启动\n");
    while(1)
    {
        printf("监听端口：%d\n",PORTNUM);
        connfd = accept(listenfd, NULL, NULL);
        if (connfd < 0)
        {
            printf("accept error");
            continue;
        }
        printf("等待发送。。。\n");
        echo(connfd);
        close(connfd);
    }
    eixt(0);
}


int make_server_socket(int port, int backlog)
{
    int listenfd;
    struct sockaddr_in address;
    int portnum = port;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
    {
        printf("oops: error socket");
        exit(1);
    }

    memset(&address, 0, sizeof(address));    
    address.sin_family = AF_INET;
    address.sin_port = htons(portnum);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenfd, (struct sockaddr *)&address, sizeof(address)) != 0)
    {
        printf("oops: error bind");
        exit(1);
    }

    if (listen(listenfd, backlog) != 0)
    {
        printf("oops: error listen");
        exit(1);
    }

    return listenfd;
}

void echo(int fd)
{
    time_t now;
    char *cp;
    time(&now);
    cp = ctime(&now);
    write(fd, cp, strlen(cp));
}