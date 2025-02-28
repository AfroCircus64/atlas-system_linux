#include "todo_api.h"

#define PORT 8080

void handle_client(int client_socket)
{
	char buffer[BUFFER_SIZE];
	char client_ip[INET_ADDRSTRLEN];
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);

	/* Get client IP address */
	getpeername(client_socket, (struct sockaddr *)&client_addr, &client_addr_len);
	inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
	printf("Client connected: %s\n", client_ip);

	/* Read the HTTP request */
	if (read_http_request(client_socket, buffer) < 0)
	{
		close(client_socket);
		return;
	}

	/* Print the full HTTP request */
	printf("Raw request: \"%s\"\n", buffer);

	/* Parse the first line of the HTTP request */
	char method[16], path[256], version[16];

	if (sscanf(buffer, "%s %s %s", method, path, version) != 3)
	{
		fprintf(stderr, "Failed to parse HTTP request line\n");
		close(client_socket);
		return;
	}

	printf("Path: %s\n", path);

	/* Print body parameters */
	char *body_start = strstr(buffer, "\r\n\r\n") + 4;
	char *param = strtok(body_start, "&");
	while (param != NULL)
	{
		char *key = strtok(param, "=");
		char *value = strtok(NULL, "\r\n");
		if (key && value)
		{
			printf("Body param: \"%s\" -> \"%s\"\n", key, value);
		}
		param = strtok(NULL, "&");
	}

	/* Send HTTP 200 OK response */
	const char *response = "HTTP/1.1 200 OK\r\n\r\n";
	send_http_response(client_socket, response);

	/* Close the connection */
	close(client_socket);
}

/**
 * main - Entry point.
 *
 * Return: int Exit status of the program.
 */
int main(void)
{
	int server_fd = create_socket(PORT);

	if (server_fd < 0)
	{
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port %d\n", PORT);

	while (1)
	{
		int client_socket = accept(server_fd, NULL, NULL);

		if (client_socket < 0)
		{
			perror("accept");
			close(server_fd);
			exit(EXIT_FAILURE);
		}
		handle_client(client_socket);
	}

	close(server_fd);
	return (0);
}
