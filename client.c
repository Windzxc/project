#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 520

int main(int argc, char *argv[])
{
    int clientfd;
    struct sockadd_in address;
    int len;
    int result;
    char *host;
    char *port;
    char buf[MAXLINE];

    host = argv[1];
    port = argv[2];
    len = sizeof(address);
    memset(&address, 0, sizeof(address));

    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_port = htonl(port);
    address.sin_addr.s_addr = host;

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