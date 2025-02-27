#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 4096

int create_socket(int port);
int read_http_request(int client_socket, char *buffer);
int send_http_response(int client_socket, const char *response);

#endif /* HELPERS_H */
