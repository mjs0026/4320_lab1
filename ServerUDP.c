/* udp server */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>

PORT = 10024;
char end[1028];

void error(char *msg)
{
	perror(msg);
	exit(0);
}

void func(char msg[1024])
{
	int j = 0;
	if(msg[8] == '5' && msg[9] == '5')
	{
		char buf[12], count[5];
		for (int i = 10; i < strlen(msg); i = i + 2)
		{
			if((msg[i] == '4' && msg[i + 1] == '1') || 
				(msg[i] == '4' && msg[i + 1] == '5') ||
				(msg[i] == '4' && msg[i + 1] == '9') ||
				(msg[i] == '4' && msg[i + 1] == 'f') ||
				(msg[i] == '5' && msg[i + 1] == '5') ||
				(msg[i] == '6' && msg[i + 1] == '1') ||
				(msg[i] == '6' && msg[i + 1] == '5') ||
				(msg[i] == '6' && msg[i + 1] == '9') ||
				(msg[i] == '6' && msg[i + 1] == 'f') ||
				(msg[i] == '7' && msg[i + 1] == '5'))
			j++;
		}
		buf[0] = '0';
		buf[1] = '0';
		buf[2] = '0';
		buf[3] = '6';
		buf[4] = msg[4];
		buf[5] = msg[5];
		buf[6] = msg[6];
		buf[7] = msg[7];
		sprintf(count,"%04x", j);
		buf[8] = count[0];
		buf[9] = count[1];
		buf[10] = count[2];
		buf[11] = count[3];
		strncpy(end, buf, 6*2);
	}
	if(msg[8] == 'a' && msg[9] == 'a')
	{
		char buf[1028], count[5];
		int countOff = 0;
		j = 8;
		for (int i = 10; i < strlen(msg); i = i + 2)
		{
			if((msg[i] == '4' && msg[i + 1] == '1') || 
				(msg[i] == '4' && msg[i + 1] == '5') ||
				(msg[i] == '4' && msg[i + 1] == '9') ||
				(msg[i] == '4' && msg[i + 1] == 'f') ||
				(msg[i] == '5' && msg[i + 1] == '5') ||
				(msg[i] == '6' && msg[i + 1] == '1') ||
				(msg[i] == '6' && msg[i + 1] == '5') ||
				(msg[i] == '6' && msg[i + 1] == '9') ||
				(msg[i] == '6' && msg[i + 1] == 'f') ||
				(msg[i] == '7' && msg[i + 1] == '5'));
			else{
				buf[j] = msg[i];
				buf[j+1] = msg[i+1];
				j = j + 2;
				countOff++;
			}
		}
		sprintf(count,"%04x", countOff + 4);
		buf[0] = count[0];
		buf[1] = count[1];
		buf[2] = count[2];
		buf[3] = count[3];
		buf[4] = msg[4];
		buf[5] = msg[5];
		buf[6] = msg[6];
		buf[7] = msg[7];
		strncpy(end, buf, (countOff + 4)*2);
	}
}


int main(int argc, char *argv[])
{
	int sock, length, fromlen, n, *local;
	struct sockaddr_in server, from;
	char buffer[256];

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		error("Opening socket");
	}

	length = sizeof(server);
	bzero(&server, length);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(argv[1]));

	if (bind(sock,(struct sockaddr *)&server,length) < 0)
	{
		error("binding");
	}
	fromlen = sizeof(struct sockaddr_in);

		n = recvfrom(sock,buffer,1024,0,(struct sockaddr *)&from, &fromlen);
		if(n < 0)
		{
			error("recvfrom");
		}
		func(buffer);
		n = sendto(sock,end,strlen(end),0,(struct sockaddr *)&from,fromlen);
		if (n < 0)
		{
			error("sendto");
		}
}