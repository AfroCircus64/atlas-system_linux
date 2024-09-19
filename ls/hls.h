#ifndef HLS_H
#define HLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

/* prototypes will go here */
int main(int argc, char **argv);
int _strcmp(char *s1, char *s2);
void print_error(const char *filename);
void print_dir(const char *dirname);


#endif /* HLS_H */
