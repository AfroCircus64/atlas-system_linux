#ifndef HREADELF_H
#define HREADELF_H

#define MAX_HEADER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]);
static int check_file(FILE *file);
static unsigned char *read_elf_header(const char *filename, size_t *size);
void process_elf_header(unsigned char *header);


#endif
