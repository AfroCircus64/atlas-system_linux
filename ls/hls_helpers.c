#include "hls.h"

/**
 * _strcmp - function that compares two strings
 *
 * @s1: string 1
 * @s2: string 2
 *
 * Return: success
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0; /* variable */

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0); /* return success */
}

/**
 * _strlen - returns the length of a string
 * @s: parameter
 * Return: Always 0
 */

int _strlen(char *s)
{
	int i;
	int length = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		length++;
	}
	return (length);
}

/**
 * print_error - error handling function
 *
 * @command: command name that is passed in
 * @filename: name of file
 */

void print_error(const char *command, const char *filename)
{
	switch (errno)
	{
	case ENOENT:
		fprintf(stderr,
		 "%s: cannot access %s: No such file or directory\n", command, filename);
		break;
	case EACCES:
		fprintf(stderr,
		 "%s: cannot open directory %s: Permission denied\n", command,  filename);
		break;

	default:
		perror(filename);
		break;
	}
}

/**
 * parse_options - func to parse options
 *
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: options
 */
Options parse_options(int argc, char **argv)
{
	Options opts = {SHOW_NONE, 0};

	int opt_index = 1;

	while (opt_index < argc && argv[opt_index][0] == '-')
	{
		if (_strcmp(argv[opt_index], "-1") == 0)
		{
			opts.show_all = SHOW_ALL;
		}
		else if (_strcmp(argv[opt_index], "-l") == 0)
		{
			opts.long_format = 1;
		}
		else if (_strcmp(argv[opt_index],
		 "-a") == 0 || _strcmp(argv[opt_index], "--all") == 0)
		{
			opts.show_all = SHOW_ALL;
		}
		else if (_strcmp(argv[opt_index],
		 "-A") == 0 || _strcmp(argv[opt_index], "--almost-all") == 0)
		{
			opts.show_all = SHOW_ALMOST_ALL;
		}
		else
		{
			fprintf(stderr, "%s: invalid option -- '%c'\n",
			 argv[0], argv[opt_index][1]);
			exit(EXIT_FAILURE);
		}
		opt_index++;
	}

	return (opts);
}
