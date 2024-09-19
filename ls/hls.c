#include "hls.h"

/**
 * print_dir - prints the directory
 *
 * @dirname: name of directory
 */

void print_dir(const char *dirname)
{
	DIR *dir; /* pointer to directory stream */

	/**
	 * dirent - directory entry struct
	 */
	struct dirent *read;

	dir = opendir(dirname); /* open current pointer */
	if (!dir) /* check if not a directory */
	{
		print_error(dirname); /* call the error function */
		exit(EXIT_FAILURE); /* exit */
	}

	if (_strcmp((char *)dirname, ".") != 0)
	{
		printf("%s:\n", dirname);
	}

	while ((read = readdir(dir)) != NULL) /* iterate through the directory */
	{
		/* skip the current and parent directories */
		if (_strcmp(read->d_name, ".") == 0 || _strcmp(read->d_name, "..") == 0)
		{
			continue;
		}

		printf("%s ", read->d_name); /* print the filename */
	}

	closedir(dir); /* close the directory */

	printf("\n"); /* print newline */
}

/**
 * main - main function
 *
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: success
 */

int main(int argc, char **argv)
{
	int i;

	if (argc == 1)
	{
		print_dir(".");
	}
	else
	{
		for (i = 1; i < argc; i++)
		{
			print_dir(argv[i]);
		}
	}
	return (0); /* return success*/
}
