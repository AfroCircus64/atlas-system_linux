#include "signals.h"

/**
 * main - program that prints a description of a given signal
 *
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: success
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <signum>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	int signum = atoi(argv[1]);
	const char *description = strsignal(signum);

	printf("%d: %s\n", signum, description ? description : "Unknown signal");
	return (0);
}
