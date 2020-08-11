#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAXLINE 120
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
    while(1)
    {
        connfd = accept(listenfd, NULL, NULL);
        if (connfd < 0)
        {
            printf("accept error");
            continue;
        }
        if(fork() == 0)
        {
            close(listenfd);
            echo(connfd);
            close(connfd);
            exit(0);
        }
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
    ssize_t n = 0;
    char buf[MAXLINE] = {0};
again:
    while((n = read(fd, buf, MAXLINE)) > 0)
    {
        write(fd, buf, n);
    }
    if (n < 0 && errno == EINTR)
    {
        goto again;
    }
    else if (n < 0)
    {
        printf("echo: read error");
    }
}