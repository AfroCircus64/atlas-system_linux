#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

/**
 * usage - Prints the usage message and exits.
 * @progname: The name of the program.
 */
void usage(const char *progname)
{
	fprintf(stderr, "Usage: %s <host> <port>\n", progname);
	exit(EXIT_FAILURE);
}

/**
 * main - Entry point.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: int Exit status of the program.
 */
int main(int argc, char *argv[])
{
	int sock = 0;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	if (argc != 3)
		usage(argv[0]);

	const char *host = argv[1];
	unsigned short port = atoi(argv[2]);

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock < 0)
	{
		perror("Socket creation error");
		exit(EXIT_FAILURE);
	}

	server = gethostbyname(host);

	if (server == NULL)
	{
		fprintf(stderr, "No such host: %s\n", host);
		exit(EXIT_FAILURE);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	memcpy(&serv_addr.sin_addr.s_addr, server->h_addr_list[0], server->h_length);

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("Connection failed");
		close(sock);
		exit(EXIT_FAILURE);
	}

	printf("Connected to %s:%d\n", host, port);
	close(sock);
	return (0);
}
