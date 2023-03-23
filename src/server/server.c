#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "./server.h"
#include "../socket/socket.h"

int server_start_listen(int server_fd, int max_conns) {
  int listen_status = listen(server_fd, max_conns);
  if (listen_status < 0) {
    perror("LISTEN: ERROR WHEN START LISTENING");
    exit(EXIT_FAILURE);
  }

  return listen_status;
}

int main()
{
  int server_fd = create_socket();
  socket_bind_server(server_fd);
  server_start_listen(server_fd, MAX_CONNS);

  // // Manage client petition
  // struct sockaddr_in client;
  // socklen_t socklen;
  // int client_fd = accept(server_fd, (struct sockaddr *) &client, (socklen_t *) &socklen);
  // if (client_fd < 0) {
  //   perror("CLIENT: THE CLIENT DESCRIPTOR WAS NOT OBTAINED");
  //   exit(EXIT_FAILURE);
  // }

  // char buffer[] = "Hola mundo\0";
  // ssize_t send_bytes = send(client_fd, buffer, strlen(buffer), 0);
  // if (send_bytes < (ssize_t) strlen(buffer)) {
  //   perror("SEND: NOT ALL DATA HAS BEEN SENT");
  //   exit(EXIT_FAILURE);
  // }
  // close(client_fd);

  // close(server_fd);


  return EXIT_SUCCESS;
}
