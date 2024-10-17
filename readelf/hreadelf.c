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
		fprintf(stderr, "Usage: %s <elf_filename>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	size_t header_size;
	unsigned char *header = read_elf_header(argv[1], &header_size);

	if (!header)
	{
		return (EXIT_FAILURE);
	}

	process_elf_header(header);

	free(header);
	return (EXIT_SUCCESS);
}
