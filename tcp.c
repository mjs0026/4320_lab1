include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define MAX 100

typedef struct msg{
        int TML;
        int requestID;
        short op;
        char m[100];
} msg;

int main(int argc, char *argv[]){
        int sockfd, numbytes;
        struct addrinfo hints, *serveinfo, *p;
        int rv;
        char buf[MAX];

        if (argc != 5) { printf("Usage: client server port operation string"); exit(0); }
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        if (( rv = getaddrinfo(argv[1], argv[2], &hints, &serveinfo) ) != 0){
                if ((sockfd = socket(p ->ai_family, p->ai_socktype, p->ai_protocol)) == -1)                     {printf("Client error: socket()");
                        exit(0);}
                if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1){
                        close(sockfd);
                        printf("Client error: connect()");
                        exit(0);
                }

        }

        if (p == NULL)
        {printf("Client error: failed to connect");
        exit(0);}


        freeaddrinfo(serveinfo);

        if ((numbytes = recv(sockfd, buf, MAX - 1, 0)) == -1){
                printf("Client error recieving");
                exit(0);
        }

        buf[numbytes] = '\0';
        printf("Client RECEIVED %s", buf);
        close(sockfd);

        return 0;

}