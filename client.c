#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 520
#define HOSTNAME VM-0-10-centos
#define PORT 13
#define IP 127.0.0.1

int main(int argc, char *argv[])
{
    int clientfd;
    struct sockadd_in address;
    int len;
    int result;
    char buf[MAXLINE];

    len = sizeof(address);
    memset(&address, 0, sizeof(address));

    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_port = htonl(PORT);
    address.sin_addr.s_addr = IP;

    result = connect(clientfd, (struct sockadd*)&address, len);

    if (result == -1)
    {
        printf("oops: client");
        exit(1);
    }
    
    read(clientfd, buf, MAXLINE);
    fputs(buf, MAXLINE, stdout);

    close(clientfd);
    return 0;

}