#include "hnm.h"

void print_symbols(const char *filename)
{
    int fd;
    unsigned char e_ident[EI_NIDENT];

    fd = open(filename, O_RDONLY);
    if (fd < 0)
	{
        perror("open");
        return;
    }

    if (read(fd, e_ident, EI_NIDENT) != EI_NIDENT)
	{
        perror("read");
        close(fd);
        return;
    }

    if (memcmp(e_ident, ELFMAG, SELFMAG) != 0)
	{
        fprintf(stderr, "%s is not an ELF file\n", filename);
        close(fd);
        return;
    }

    int is_big_endian = (e_ident[EI_DATA] == ELFDATA2MSB);

    if (e_ident[EI_CLASS] == ELFCLASS32)
	{
        Elf32_Ehdr ehdr;
        lseek(fd, 0, SEEK_SET);

        if (read(fd, &ehdr, sizeof(ehdr)) != sizeof(ehdr))
		{
            perror("read");
            close(fd);
            return;
        }
        print_symbols_32(fd, &ehdr, is_big_endian);
    }
	else if (e_ident[EI_CLASS] == ELFCLASS64)
	{
        Elf64_Ehdr ehdr;
        lseek(fd, 0, SEEK_SET);

        if (read(fd, &ehdr, sizeof(ehdr)) != sizeof(ehdr))
		{
            perror("read");
            close(fd);
            return;
        }
        print_symbols_64(fd, &ehdr, is_big_endian);
    }
	else
	{
        fprintf(stderr, "Unknown ELF class\n");
    }

    close(fd);
}

void print_symbols_32(int fd, Elf32_Ehdr *ehdr, int is_big_endian)
{
    Elf32_Shdr *shdrs;
    Elf32_Sym *symtab;
    char *strtab;
    int i, j;
    size_t shdr_size, symtab_size;

    shdr_size = ehdr->e_shentsize * ehdr->e_shnum;
    shdrs = malloc(shdr_size);

    if (!shdrs)
	{
        perror("malloc");
        return;
    }

    lseek(fd, ehdr->e_shoff, SEEK_SET);

    if (read(fd, shdrs, shdr_size) != shdr_size)
	{
        perror("read");
        free(shdrs);
        return;
    }

    for (i = 0; i < ehdr->e_shnum; i++)
	{
        if (shdrs[i].sh_type == SHT_SYMTAB)
		{
            symtab_size = shdrs[i].sh_size;
            symtab = malloc(symtab_size);

            if (!symtab)
			{
                perror("malloc");
                free(shdrs);
                return;
            }

            lseek(fd, shdrs[i].sh_offset, SEEK_SET);

            if (read(fd, symtab, symtab_size) != symtab_size)
			{
                perror("read");
                free(symtab);
                free(shdrs);
                return;
            }

            strtab = malloc(shdrs[shdrs[i].sh_link].sh_size);

            if (!strtab)
			{
                perror("malloc");
                free(symtab);
                free(shdrs);
                return;
            }

            lseek(fd, shdrs[shdrs[i].sh_link].sh_offset, SEEK_SET);

            if (read(fd, strtab, shdrs[shdrs[i].sh_link].sh_size) != shdrs[shdrs[i].sh_link].sh_size)
			{
                perror("read");
                free(strtab);
                free(symtab);
                free(shdrs);
                return;
            }

            for (j = 0; j < symtab_size / sizeof(Elf32_Sym); j++)
			{
                uint32_t value = symtab[j].st_value;

                if (is_big_endian)
				{
                    value = swap32(value);
                }
                printf("%08x %c %s\n", value, ELF32_ST_TYPE(symtab[j].st_info), &strtab[symtab[j].st_name]);
            }

            free(strtab);
            free(symtab);
        }
    }

    free(shdrs);
}

void print_symbols_64(int fd, Elf64_Ehdr *ehdr, int is_big_endian)
{
    Elf64_Shdr *shdrs;
    Elf64_Sym *symtab;
    char *strtab;
    int i, j;
    size_t shdr_size, symtab_size;

    shdr_size = ehdr->e_shentsize * ehdr->e_shnum;
    shdrs = malloc(shdr_size);

    if (!shdrs)
	{
        perror("malloc");
        return;
    }

    lseek(fd, ehdr->e_shoff, SEEK_SET);

    if (read(fd, shdrs, shdr_size) != shdr_size)
	{
        perror("read");
        free(shdrs);
        return;
    }

    for (i = 0; i < ehdr->e_shnum; i++)
	{
        if (shdrs[i].sh_type == SHT_SYMTAB)
		{
            symtab_size = shdrs[i].sh_size;
            symtab = malloc(symtab_size);

            if (!symtab)
			{
                perror("malloc");
                free(shdrs);
                return;
            }

            lseek(fd, shdrs[i].sh_offset, SEEK_SET);

            if (read(fd, symtab, symtab_size) != symtab_size)
			{
                perror("read");
                free(symtab);
                free(shdrs);
                return;
            }

            strtab = malloc(shdrs[shdrs[i].sh_link].sh_size);

            if (!strtab)
			{
                perror("malloc");
                free(symtab);
                free(shdrs);
                return;
            }

            lseek(fd, shdrs[shdrs[i].sh_link].sh_offset, SEEK_SET);

            if (read(fd, strtab, shdrs[shdrs[i].sh_link].sh_size) != shdrs[shdrs[i].sh_link].sh_size)
			{
                perror("read");
                free(strtab);
                free(symtab);
                free(shdrs);
                return;
            }

            for (j = 0; j < symtab_size / sizeof(Elf64_Sym); j++)
			{
                uint64_t value = symtab[j].st_value;

                if (is_big_endian)
				{
                    value = swap64(value);
                }
                printf("%016lx %c %s\n", value, ELF64_ST_TYPE(symtab[j].st_info), &strtab[symtab[j].st_name]);
            }

            free(strtab);
            free(symtab);
        }
    }

    free(shdrs);
}