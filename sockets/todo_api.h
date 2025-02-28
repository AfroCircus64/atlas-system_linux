#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 4096

/**
 * struct todo - A todo item.
 * @id: The ID of the todo.
 * @title: The title of the todo.
 * @description: The description of the todo.
 * @next: A pointer to the next todo in the list.
 */
typedef struct todo
{
	int id;
	char title[256];
	char description[256];
	struct todo *next;
} todo_t;

int create_socket(int port);
int read_http_request(int client_socket, char *buffer);
int send_http_response(int client_socket, const char *response);

#endif /* HELPERS_H */
