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
void print_symbols_32(int fd, Elf32_Ehdr *ehdr, int is_big_endian);
void print_symbols_64(int fd, Elf64_Ehdr *ehdr, int is_big_endian);
uint16_t swap16(uint16_t val);
uint32_t swap32(uint32_t val);
uint64_t swap64(uint64_t val);


#endif
