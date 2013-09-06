#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

struct tcp_msg{
  int reqID;
  short operation;
  int length;
  char message[100];
};


int main(int argc, char *argv[])
{
  int sockfd, port, n;
  struct sockaddr_in serv_addr;
  char buffer[256];
  struct hostent *server;
  
  if(argc < 5) {
    fprintf(stderr, "usage: %s client servername portnumber operation string");
    exit(0);
  }
   
  port = atoi(argv[4]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0){printf("ERROR opening socket");}
  server = gethostbyname(argv[1]);
  if (server == NULL)
    {printf("ERROR, no such host"); exit(0);}
   
bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(port);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) { printf("ERROR connecting");}
    bzero(buffer,256);

  struct tcp_msg my_struct;  
  my_struct.reqID = argv[5];
  my_struct.operation = argv[5];
  strcpy(my_struct.message, argv[6]);
  my_struct.length =strlen(argv[6]) + 5;
  n = write(sockfd, (char *)&my_struct, my_struct.length);
  if (n < 0) {printf("ERROR size of my_struct");}
  n = read(sockfd, buffer, 255);
  if (n < 0) {printf("ERROR size of read()");}
  printf("READ BUFFER: %s/n", buffer);
                           
  close(sockfd);
  return 0;
}
