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
#define PORT 8080
#define BACKLOG 5

int make_server_socket(int port, int backlog);
void echo(int fd);

int main(int argc, int *argv[])
{
    int listenfd;
    int connfd;
    struct sockadd_in clientaddr;
    socklen_t clientlen;


    port = argv[1];
    backlog = argv[2];
    

    listenfd = make_server_socket(PORT, BACKLOG);
    
    while(1)
    {
        connfd = accept(listenfd, &clientaddr, &clientlen);

        echo(connfd);
        close(connfd);
    }
    eixt(0);
}


int make_server_socket(int port, int backlog)
{
    int listenfd;
    struct hostent *hp;
    struct sockadd_in address;
    char hostname[HOSTLEN];
  
    int portnum = port;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
    {
        printf("oops: error socket");
        exit(1);
    }

    memset(&address, 0, sizeof(address));
    gethostname(hostname,HOSTLEN);
    hp = gethostbyname(hostname);
    
    address.sin_family = AF_INET;
    address.sin_port = htonl(portnum);
    address.sin_addr.s_addr = hp->h_addr_list[1];

    if (bind(listenfd, &address, sizeof(address)) != 0)
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