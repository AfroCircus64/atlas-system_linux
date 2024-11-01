#include "hreadelf.h"

/**
 * print_elf_header - Prints the ELF file header information
 *
 * @filename: Name of the ELF file to read
 */
void print_elf_header(const char *filename)
{
	FILE *file = fopen(filename, "rb");

	if (!file)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	unsigned char e_ident[EI_NIDENT];

	fread(e_ident, 1, EI_NIDENT, file);

	if (memcmp(e_ident, ELFMAG, SELFMAG) != 0)
	{
		fprintf(stderr, "Not an ELF file\n");
		fclose(file);
		exit(EXIT_FAILURE);
	}

	int is_64bit = (e_ident[EI_CLASS] == ELFCLASS64);

	if (is_64bit)
	{
		Elf64_Ehdr header;

		fseek(file, 0, SEEK_SET);
		fread(&header, 1, sizeof(header), file);
		printf("ELF Header:\n");
		printf("  Magic:   ");
		for (int i = 0; i < EI_NIDENT; i++)
		{
			printf("%02x ", header.e_ident[i]);
		}
		printf("\n  Class:                             ELF64\n");
		printf("  Data:                              %s\n", header.e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" : "2's complement, big endian");
		printf("  Version:                           %d (current)\n", header.e_ident[EI_VERSION]);
		printf("  OS/ABI:                            %d\n", header.e_ident[EI_OSABI]);
		printf("  ABI Version:                       %d\n", header.e_ident[EI_ABIVERSION]);
		printf("  Type:                              %d\n", header.e_type);
		printf("  Machine:                           %d\n", header.e_machine);
		printf("  Version:                           0x%x\n", header.e_version);
		printf("  Entry point address:               0x%lx\n", header.e_entry);
		printf("  Start of program headers:          %ld (bytes into file)\n", header.e_phoff);
		printf("  Start of section headers:          %ld (bytes into file)\n", header.e_shoff);
		printf("  Flags:                             0x%x\n", header.e_flags);
		printf("  Size of this header:               %d (bytes)\n", header.e_ehsize);
		printf("  Size of program headers:           %d (bytes)\n", header.e_phentsize);
		printf("  Number of program headers:         %d\n", header.e_phnum);
		printf("  Size of section headers:           %d (bytes)\n", header.e_shentsize);
		printf("  Number of section headers:         %d\n", header.e_shnum);
		printf("  Section header string table index: %d\n", header.e_shstrndx);
	} else
	{
		Elf32_Ehdr header;
		fseek(file, 0, SEEK_SET);
		fread(&header, 1, sizeof(header), file);
		printf("ELF Header:\n");
		printf("  Magic:   ");
		for (int i = 0; i < EI_NIDENT; i++)
		{
			printf("%02x ", header.e_ident[i]);
		}
		printf("\n  Class:                             ELF32\n");
		printf("  Data:                              %s\n", header.e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" : "2's complement, big endian");
		printf("  Version:                           %d (current)\n", header.e_ident[EI_VERSION]);
		printf("  OS/ABI:                            %d\n", header.e_ident[EI_OSABI]);
		printf("  ABI Version:                       %d\n", header.e_ident[EI_ABIVERSION]);
		printf("  Type:                              %d\n", header.e_type);
		printf("  Machine:                           %d\n", header.e_machine);
		printf("  Version:                           0x%x\n", header.e_version);
		printf("  Entry point address:               0x%x\n", header.e_entry);
		printf("  Start of program headers:          %d (bytes into file)\n", header.e_phoff);
		printf("  Start of section headers:          %d (bytes into file)\n", header.e_shoff);
		printf("  Flags:                             0x%x\n", header.e_flags);
		printf("  Size of this header:               %d (bytes)\n", header.e_ehsize);
		printf("  Size of program headers:           %d (bytes)\n", header.e_phentsize);
		printf("  Number of program headers:         %d\n", header.e_phnum);
		printf("  Size of section headers:           %d (bytes)\n", header.e_shentsize);
		printf("  Number of section headers:         %d\n", header.e_shnum);
		printf("  Section header string table index: %d\n", header.e_shstrndx);
	}

	fclose(file);
}

/**
 * print_section_headers - Prints the ELF section headers information
 *
 * @filename: Name of the ELF file to read
 */
void print_section_headers(const char *filename)
{
	FILE *file = fopen(filename, "rb");
	if (!file)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	unsigned char e_ident[EI_NIDENT];
	fread(e_ident, 1, EI_NIDENT, file);

	if (memcmp(e_ident, ELFMAG, SELFMAG) != 0)
	{
		fprintf(stderr, "Not an ELF file\n");
		fclose(file);
		exit(EXIT_FAILURE);
	}

	int is_64bit = (e_ident[EI_CLASS] == ELFCLASS64);
	if (is_64bit)
	{
		Elf64_Ehdr header;
		fseek(file, 0, SEEK_SET);
		fread(&header, 1, sizeof(header), file);

		Elf64_Shdr *section_headers = malloc(header.e_shentsize * header.e_shnum);
		fseek(file, header.e_shoff, SEEK_SET);
		fread(section_headers, header.e_shentsize, header.e_shnum, file);

		char *shstrtab = malloc(section_headers[header.e_shstrndx].sh_size);
		fseek(file, section_headers[header.e_shstrndx].sh_offset, SEEK_SET);
		fread(shstrtab, 1, section_headers[header.e_shstrndx].sh_size, file);

		printf("There are %d section headers, starting at offset 0x%lx:\n\n", header.e_shnum, header.e_shoff);
		printf("Section Headers:\n");
		printf("  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al\n");
		for (int i = 0; i < header.e_shnum; i++) {
			printf("  [%2d] %-17s %-15x %016lx %06lx %06lx %02lx %3lx %2d %3d %2lx\n",
				   i,
				   &shstrtab[section_headers[i].sh_name],
				   section_headers[i].sh_type,
				   section_headers[i].sh_addr,
				   section_headers[i].sh_offset,
				   section_headers[i].sh_size,
				   section_headers[i].sh_entsize,
				   section_headers[i].sh_flags,
				   section_headers[i].sh_link,
				   section_headers[i].sh_info,
				   section_headers[i].sh_addralign);
		}

		free(section_headers);
		free(shstrtab);
	} else
	{
		Elf32_Ehdr header;
		fseek(file, 0, SEEK_SET);
		fread(&header, 1, sizeof(header), file);

		Elf32_Shdr *section_headers = malloc(header.e_shentsize * header.e_shnum);
		fseek(file, header.e_shoff, SEEK_SET);
		fread(section_headers, header.e_shentsize, header.e_shnum, file);

		char *shstrtab = malloc(section_headers[header.e_shstrndx].sh_size);
		fseek(file, section_headers[header.e_shstrndx].sh_offset, SEEK_SET);
		fread(shstrtab, 1, section_headers[header.e_shstrndx].sh_size, file);

		printf("There are %d section headers, starting at offset 0x%x:\n\n", header.e_shnum, header.e_shoff);
		printf("Section Headers:\n");
		printf("  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al\n");
		for (int i = 0; i < header.e_shnum; i++) {
			printf("  [%2d] %-17s %-15x %08x %06x %06x %02x %3x %2d %3d %2x\n",
				   i,
				   &shstrtab[section_headers[i].sh_name],
				   section_headers[i].sh_type,
				   section_headers[i].sh_addr,
				   section_headers[i].sh_offset,
				   section_headers[i].sh_size,
				   section_headers[i].sh_entsize,
				   section_headers[i].sh_flags,
				   section_headers[i].sh_link,
				   section_headers[i].sh_info,
				   section_headers[i].sh_addralign);
		}

		free(section_headers);
		free(shstrtab);
	}

	fclose(file);
}
