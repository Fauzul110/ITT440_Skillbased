#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main(int argc, char*argv[])
{
	int socket_desc, client_sock, c;
	struct sockaddr_in server, client;
	int random_number;
	srand(time(0));
	//create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1)
	{
		printf("could not create socket");
		return 1;
	}
	//prepare sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8080);
	//bind socket
	if(bind(socket_desc,(struct sockadd *)&server, sizeof(server))<0)
	{
		perror("Bind failed");
		return 1;
	}
	puts("bind done");
	//listem to socket
	listen(socket_desc,3);
	puts("waiting connection");
	c = sizeof(struct sockaddr_in);
	//accept connection
	client_sock = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c);
	if(client_sock<0)
	{
		perror("accept failed");
		return 1;
	}
	puts("connection accepted");
	//generate rand number
	random_number = (rand()%(999 - 100 + 1) + 100);
	//send number
	write(client_sock, &random_number, sizeof(random_number));
	//close socket
	close(client_sock);
	close(socket_desc);
	return 0;
}
