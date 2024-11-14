#include "hnm.h"

/**
 * main - main nm function
 *
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: success
 */
int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s [objfile ...]\n", argv[0]);
		return (EXIT_FAILURE);
	}

	for (int i = 1; i < argc; i++)
	{
		print_symbols(argv[i]);
	}

	return (EXIT_SUCCESS);
}
