#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "./server.h"
#include "../socket/socket.h"

int server_start_listen(int server_fd, int max_conns)
{
  int listen_status = listen(server_fd, max_conns);
  if (listen_status < 0)
  {
    perror("LISTEN: ERROR WHEN START LISTENING\n");
    exit(EXIT_FAILURE);
  }

  return listen_status;
}

int server_accept_client(int server_fd)
{
  struct sockaddr_in client_conf;
  socklen_t socklen;

  int client_fd = accept(server_fd, (struct sockaddr *)&client_conf, (socklen_t *)&socklen);
  if (client_fd < 0)
  {
    perror("CLIENT: THE CLIENT DESCRIPTOR WAS NOT OBTAINED\n");
    exit(EXIT_FAILURE);
  }

  return client_fd;
}

int main(int argc, char *argv[])
{
  unsigned int port = PORT;
  if (argc >= 2)
  {
    char *end_ptr;
    port = (unsigned int)strtol(argv[1], &end_ptr, 10);
  }

  int server_fd = create_socket();
  socket_bind_server(server_fd, port);

  printf("START TO LISTEN IN PORT: %u\n", port);
  server_start_listen(server_fd, MAX_CONNS);

  int client_fd = server_accept_client(server_fd);
  char buffer[] = "Hola mundo\0";
  ssize_t send_bytes = send(client_fd, buffer, strlen(buffer), 0);
  if (send_bytes < (ssize_t)strlen(buffer))
  {
    perror("SEND: NOT ALL DATA HAS BEEN SENT\n");
    exit(EXIT_FAILURE);
  }

  close(client_fd);
  close(server_fd);

  printf("END SERVER\n");
  return EXIT_SUCCESS;
}
