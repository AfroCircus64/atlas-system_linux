#include "todo_api.h"

/**
 * create_socket - Creates a server socket and binds it to the specified port.
 * @port: The port number to bind the socket to.
 *
 * Return: The file descriptor of the created socket, or -1 on failure.
 */
int create_socket(int port)
{
	int server_fd;
	struct sockaddr_in address;
	int opt = 1;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (server_fd == 0)
	{
		perror("socket failed");
		return (-1);
	}

	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		close(server_fd);
		return (-1);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("bind failed");
		close(server_fd);
		return (-1);
	}

	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		close(server_fd);
		return (-1);
	}

	return (server_fd);
}

/**
 * read_http_request - Reads an HTTP request from the client socket.
 * @client_socket: The file descriptor of the client socket.
 * @buffer: The buffer to store the HTTP request.
 *
 * Return: The number of bytes read, or -1 on failure.
 */
int read_http_request(int client_socket, char *buffer)
{
	int bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);

	if (bytes_read < 0)
	{
		perror("read");
		return (-1);
	}
	buffer[bytes_read] = '\0';
	return (bytes_read);
}

/**
 * send_http_response - Sends an HTTP response to the client socket.
 * @client_socket: The file descriptor of the client socket.
 * @response: The HTTP response to send.
 *
 * Return: The number of bytes sent, or -1 on failure.
 */
int send_http_response(int client_socket, const char *response)
{
	int bytes_sent = write(client_socket, response, strlen(response));

	if (bytes_sent < 0)
	{
		perror("write");
		return (-1);
	}
	return (bytes_sent);
}
