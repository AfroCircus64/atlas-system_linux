#ifndef HNM_H
#define HNM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <stdint.h>


void print_symbols(const char *filename);
void print_symbols_32(int fd, Elf32_Ehdr *ehdr);
void print_symbols_64(int fd, Elf64_Ehdr *ehdr);

#endif
