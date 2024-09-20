#ifndef HLS_H
#define HLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>


#define MAX_ARGS 512

/**
 * enum showtype - struct
 *
 * @SHOW_NONE: parameter
 * @SHOW_ALL: parameter
 * @SHOW_ALMOST_ALL: parameter
 */
typedef enum showtype
{
	SHOW_NONE,
	SHOW_ALL,
	SHOW_ALMOST_ALL
} ShowType;

/**
 * struct options - Structure to hold options for the ls-like program.
 *
 * @show_all: parameter
 * @long_format: parameter
 */
typedef struct options
{
	int show_all;
	int long_format;
} Options;

/* prototypes will go here */
int main(int argc, char **argv);
int _strcmp(char *s1, char *s2);
void print_error(const char *command, const char *filename);
void print_dir(const char *dirname, const char *command, Options opts);
void handle_error(const char *command, const char *filename);
Options parse_options(int argc, char **argv);
void print_long_format(struct dirent *entry, const char *path);
char *get_permissions(mode_t mode);
char *get_username(uid_t uid);
char *get_groupname(gid_t gid);


#endif /* HLS_H */
