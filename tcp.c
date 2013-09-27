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
          char message[100];
} Msg;

int main(int argc, char *argv[]){

  int counter = 0;
  int sockfd, port, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char buffer[256];
  printf("1%s 2%s 3%s 4%s", argv[1], argv[2], argv[3], argv[4]);


  if (argc < 4)
  printf("ERROR, usage: client servername port operation message");

  Msg m;
  m.reqID = counter++;
  m.op = atoi(argv[3]);
  m.length=(strlen(argv[4]) + 5);
  strcpy(m.message, argv[4]);
  printf("\nM.message %s", m.message);

  port = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {printf("CLIENT: error with sockfd");}
  printf("\nsockfd %d", sockfd);

  server = gethostbyname(argv[1]);
  printf("\nserver %s", argv[1]);

  if (server == NULL) {printf("CLIENT: error with hostname");exit(0);}

   serv_addr.sin_port = htons(port);
   bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr,
   (char *)&serv_addr.sin_addr.s_addr,server->h_length);
   serv_addr.sin_port = htons(port);

   int g;
   g = connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
   if (g < 0)
   {printf("ERROR connecting");}
   bzero(buffer,256);

   time_t t1, t2;
   t1 = time(0);

   ssize_t sending;
  sending = write(sockfd,(char *)&m, m.length);
   printf("\nSENDING = %d. &m = %s", sending, (char *)&m);


  printf("END\n\n");
  return 0;
}
