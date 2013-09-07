#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

typedef struct Msg{
  short length;
  short reqID;
  char op;
  char *message;
} Msg;

int main(int argc, char *argv[]){
  int counter = 0;
  int sockfd, port, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char buffer[256];

  printf("1%s 2%s 3%s 4%s 5%s", argv[1], argv[2], argv[3], argv[4], argv[5]);


  if (argc < 5) {printf("ERROR, usage: client servername port operation message"); 
    exit(0);}

  Msg *m = (Msg*)malloc (sizeof(Msg));
  m->reqID = counter++;
  m->op = atoi(argv[4]); 
  m->length=(strlen(argv[5]) + 5);
  m->message = malloc(strlen(argv[5]) + 1);
  strcpy(m->message, argv[5]);

  
 port = atoi(argv[3]);
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfd < 0) {printf("CLIENT: error with sockfd");}
 server = gethostbyname(argv[1]);
 if (server == NULL) {printf("CLIENT: error with hostname");exit(0);}

 serv_addr.sin_port = htons(port); 
  bzero((char *) &serv_addr, sizeof(serv_addr));
 serv_addr.sin_family = AF_INET;
 bcopy((char *)server->h_addr, 
                      (char *)&serv_addr.sin_addr.s_addr,
                               server->h_length);
 serv_addr.sin_port = htons(port);
 if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
              {printf("ERROR connecting");}
  bzero(buffer,256);

  time_t t1, t2;
  t1 = time(0);

   ssize_t sending;
  sending = write(sockfd,(char *)&m, m->length);
  printf("CLIENT: sent %s", (char *)&m);
  if (sending < 0) {printf("CLIENT: error sending");}
  sending = read(sockfd, buffer, 255);

  t2 = time(0);
  
  if (sending < 0) {printf("CLIENT: error receiving");} 
  printf("CLIENT redceived: %s\n", buffer);
  printf("CLIENT elapsed: %d\n", difftime(t2, t1));
  close(sockfd);




  
  
  return 0;
}
