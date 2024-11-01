#include "hreadelf.h"

/**
 * main - main readelf function
 *
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Success
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
		return (EXIT_FAILURE);
	}

	print_elf_header(argv[1]);
	return (EXIT_SUCCESS);
}
