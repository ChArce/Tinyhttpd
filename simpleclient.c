#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch = 'A';

	char *query_string = "GET";
	char rcvBuf[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(4000);
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        perror("oops: client1");
        exit(1);
    }
    size_t writelen = write(sockfd, "GET", 3);
	printf("write length: %d\n", writelen);
	size_t readlen = read(sockfd, rcvBuf, sizeof(rcvBuf));
	rcvBuf[readlen+1] = '\0';
    printf("char from server = %s\n", rcvBuf);
    close(sockfd);
	exit(0);
}
