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
 * parse_flags - function to handle the flags
 *
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: success
 */
int parse_flags(int argc, char **argv)
{
	int index;
	int single_column;

	for (index = 1; index < argc; index++)
	{
		if (argv[index][0] == '-' && argv[index][1] == '1' && argv[index][2] == '\0')
		{
			single_column = 1;
		}
		else
		{
			break;
		}
	}
	return (single_column);
}
