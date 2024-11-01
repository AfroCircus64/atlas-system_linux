#ifndef HREADELF_H
#define HREADELF_H

#define MAX_HEADER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <elf.h>

int main(int argc, char *argv[]);
void print_elf_header(const char *filename);
void print_section_headers(const char *filename);


#endif
