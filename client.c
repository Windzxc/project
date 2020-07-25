#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define hostname root

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockadd_in address;
    int len;
    int result;

    memset(&address, 0, sizeof(address));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_port = htonl(900);
    address.sin_addr.s_addr = hostname;

    len = sizeof(address);

    result = connect(sockfd, (struct sockadd*)&address, len);

    if (result == -1)
    {
        printf("oops: client");
        exit(1);
    }

    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    close(sockfd);
    return 0;

}