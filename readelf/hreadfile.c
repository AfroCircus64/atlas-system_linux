#include "hreadelf.h"

/**
 * check_file - checks if file opened correctly
 *
 * @file: name of file
 */
static int check_file(FILE *file)
{
	if (file != NULL)
	{
		return(0);
	}
	else
	{
		return(1);
	}
	return(0);
}

/**
 * read_elf_header - func to read ELF header
 *
 * @filename: name of file
 * @size: size of header
 *
 * Return: header
 */
static unsigned char *read_elf_header(const char *filename, size_t *size)
{
	FILE *file = fopen(filename, "rb");

	if (!check_file(file))
	{
		perror("Error opening file");
		return (NULL);
	}

	unsigned char header[MAX_HEADER_SIZE];
	size_t bytes_read = fread(header, 1, sizeof(header), file);

	if (bytes_read != sizeof(header))
	{
		fprintf(stderr, "Error reading file\n");
		fclose(file);
		return (NULL);
	}

	*size = bytes_read;
	fclose(file);
	return (header);
}

/**
 * process_elf_header - func to process ELF header
 *
 * @header: header
 */
void process_elf_header(unsigned char *header)
{
	printf("ELF Header:\n");

	printf("  Magic:   ");
	for (int i = 0; i < 16; i++)
	{
		printf("%02X ", header[i]);

		if ((i + 1) % 8 == 0)
		{
			printf("\n");
		}
	}

	printf("  Class:                             ");
	if (header[4] == 1)
	{
		printf("ELF32\n");
	}
	else
	{
		printf("ELF64\n");
	}

	printf("  Data:                              ");
	switch ((header[5] & 4) >> 2)
	{
		case 0:
			printf("Unknown\n");
			break;
		case 1:
			printf("2's complement, little endian\n");
			break;
		case 2:
			printf("2's complement, big endian\n");
			break;
	}

	printf("  Version:                           %d (current)\n", header[6]);

	printf("  OS/ABI:                            ");
	switch (header[7])
	{
		case 0x01:
			printf("UNIX - System V\n");
			break;
		case 0x02:
			printf("UNIX - NetBSD\n");
			break;
		case 0x03:
			printf("UNIX - Linux\n");
			break;
		default:
			printf("Unknown\n");
	}

	printf("  ABI Version:                       %d\n", header[8]);

	printf("  Type:                              ");
	switch (header[9])
	{
		case 0x01:
			printf("NOBITS\n");
			break;
		case 0x02:
			printf("REL\n");
			break;
		case 0x03:
			printf("EXEC\n");
			break;
		case 0x04:
			printf("DYN\n");
			break;
		case 0x05:
			printf("CORE\n");
			break;
		default:
			printf("Unknown\n");
	}

	printf("  Machine:                           ");
	switch (header[10])
	{
		case 0x01:
			printf("Intel 80386\n");
			break;
		case 0x02:
			printf("Motorola 68020\n");
			break;
		case 0x03:
			printf("SPARC\n");
			break;
		case 0x04:
			printf("Intel i486\n");
			break;
		case 0x05:
			printf("Intel i860\n");
			break;
		case 0x41:
			printf("ARM\n");
			break;
		case 0x43:
			printf("SuperH\n");
			break;
		case 0x44:
			printf("Sparc\n");
			break;
		case 0x45:
			printf("X86-64\n");
			break;
		case 0x46:
			printf("MIPS R3000\n");
			break;
		case 0x47:
			printf("PowerPC\n");
			break;
		case 0x48:
			printf("PowerPC64\n");
			break;
		case 0x49:
			printf("S390\n");
			break;
		case 0x4a:
			printf("ARM64\n");
			break;
		case 0x4b:
			printf("AArch64\n");
			break;
		case 0x4c:
			printf("AVR32\n");
			break;
		case 0x4d:
			printf("AVR32\n");
			break;
		case 0x4e:
			printf("SH64\n");
			break;
		case 0x4f:
			printf("MIPS16\n");
			break;
		default:
			printf("Unknown\n");
	}

	printf("  Entry point address:               0x%x\n",
	 *(unsigned int *)(header + 24));

	printf("  Start of program headers:          %d (bytes into file)\n",
	 header[33]);

	printf("  Start of section headers:          %d (bytes into file)\n",
	 header[35]);

	printf("  Flags:                             0x%x\n", header[36]);

	printf("  Size of this header:               %d (bytes)\n", header[40]);

	printf("  Size of program headers:           %d (bytes)\n", header[42]);

	printf("  Number of program headers:         %d\n", header[44]);

	printf("  Size of section headers:           %d (bytes)\n", header[46]);

	printf("  Number of section headers:         %d\n", header[48]);

	printf("  Section header string table index: %d\n", header[50]);
}
