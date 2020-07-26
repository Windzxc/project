#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLINE 520
#define HOSTNAME VM-0-10-centos
#define PORT 13

int main(int argc, char *argv[])
{
    int clientfd;
    struct sockaddr_in address;
    int len;
    int result;
    char buf[MAXLINE];
    char *ip = "127.0.0.1";

    len = sizeof(address);
    memset(&address, 0, sizeof(address));

    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_port = htonl(PORT);
    if (inet_pton(AF_INET, ip, &address.sin_addr) <= 0)
    {
        printf("error:inet_pton");
        exit(1);
    }

    result = connect(clientfd, (struct sockadd*)&address, len);

    if (result == -1)
    {
        printf("oops: client");
        exit(1);
    }
    
    read(clientfd, buf, MAXLINE);
    fputs(buf, stdout);

    close(clientfd);
    return 0;

}