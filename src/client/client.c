#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include "./client.h"
#include "../socket/socket.h"
#include "../server/server.h"

int main(int argc, char *argv[]) {
  int client_fd = create_socket();

  char *host = HOST;
  unsigned int port = 3535;
  if (argc >= 2) {
    host = argv[1];
  }
  if (argc >= 3) {
    char *end_ptr;
    port = (unsigned int) strtol(argv[2], &end_ptr, 10);
  }

  socket_connect_client(client_fd, host, port);

  char buffer[1024];
  ssize_t recv_bytes = recv(client_fd, buffer, 1024, 0);
  if (recv_bytes < 0) {
    perror("RECV: AN ERROR HAS BEEN PRESENTED WHEN RECEIVING THE COMMUNICATION\n");
    exit(EXIT_FAILURE);
  }

  buffer[recv_bytes] = '\0';
  printf("\nMensaje: %s\n", buffer);

  close(client_fd);
  return EXIT_SUCCESS;
}