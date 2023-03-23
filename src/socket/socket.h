#pragma once
#ifndef _SOCKET_H_
#define _SOCKET_H_

#define HOST "127.0.0.1"

int create_socket();
int socket_bind_server(int server_fd);
int socket_connect_client(int client_fd);

#endif // !_SOCKET_H_
