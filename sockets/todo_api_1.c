#include "todo_api.h"

#define PORT 8080

/**
 * parse_query_params - Parses query parameters from the URL.
 * @url: The URL containing the query parameters.
 */
void parse_query_params(const char *url)
{
	char *query = strchr(url, '?');
	if (query)
	{
		query++; /* Skip the '?' */
		char *key_value = strtok(query, "&");
		while (key_value)
		{
			char *key = strtok(key_value, "=");
			char *value = strtok(NULL, "=");
			if (key && value)
			{
				printf("Query: \"%s\" -> \"%s\"\n", key, value);
			}
			key_value = strtok(NULL, "&");
		}
	}
}

/**
 * handle_client - Handles the client connection.
 * @client_socket: The client socket file descriptor.
 */
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
	char *query_start = strchr(buffer, '?');
	if (query_start)
	{
		*query_start = '\0'; /* Terminate the path string before the query */
		sscanf(buffer, "%s %s %s", method, path, version);
		*query_start = '?'; /* Restore the query character */
	}
	else
	{
		sscanf(buffer, "%s %s %s", method, path, version);
	}

	printf("Method: %s\n", method);
	printf("Path: %s\n", path);
	printf("Version: %s\n", version);

	/* Parse and print query parameters */
	parse_query_params(buffer);

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
