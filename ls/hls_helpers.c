#include "hls.h"

/**
 * _strcmp - function that compares two strings
 * @s1: string 1
 * @s2: string 2
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
 * @filename: name of file
 */

void print_error(const char *filename)
{
	switch (errno)
	{
	case ENOENT:
		fprintf(stderr,
		 "./hls cannot access %s: No such file or directory\n", filename);
		break;
	case EACCES:
		fprintf(stderr,
		 "./hls cannot open directory %s: Permission denied\n", filename);
		break;

	default:
		perror(filename);
		break;
	}
}
