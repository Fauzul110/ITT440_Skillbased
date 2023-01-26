#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

void client_handler(int socket_desc)
{
 char buffer[1024];
 int bytes_received = recv(socket_desc, buffer, sizeof(buffer), 0);
 buffer[bytes_received] = '\0';
 char outgoing_text[1024];
 snprintf(outgoing_text, sizeof(outgoing_text), "%s from server xyz", buffer);
 send(socket_desc, outgoing_text, strlen(outgoing_text), 0);
}

int main()
 {
  int server_sock = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8080);
  server_address.sin_addr.s_addr=INADDR_ANY;

  bind(server_sock, (struct sockaddr*) &server_address, sizeof(server_address));
  listen(server_sock, 5);

 while(1)
 {
  int socket_desc = accept(server_sock, NULL, NULL);
  pid_t pid = fork();
  if(pid == 0)
  {
   client_handler(socket_desc);
   close(socket_desc);
   exit(0);
  }
 }

close(server_sock);
return 0;
}
