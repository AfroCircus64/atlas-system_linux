#include "hls.h"

/**
 * print_dir - prints the directory
 *
 * @dirname: name of directory
 * @command: command name to be passed into print_error()
 * @single_column: handler for the -1 flag
 */

void print_dir(const char *dirname, const char *command, int single_column)
{
	DIR *dir; /* pointer to directory stream */

	/**
	 * dirent - directory entry struct
	 */
	struct dirent *read;

	dir = opendir(dirname); /* open current pointer */
	if (!dir) /* check if not a directory */
	{
		print_error(command, dirname); /* call the error function */
		exit(EXIT_FAILURE); /* exit */
	}

	printf("%s:\n", dirname);

	while ((read = readdir(dir)) != NULL) /* iterate through the directory */
	{
		/* skip the current and parent directories */
		if (_strcmp(read->d_name, ".") == 0 || _strcmp(read->d_name, "..") == 0)
		{
			continue;
		}

		printf("%s%s", read->d_name, single_column ? "\n" : " ");
	}

	closedir(dir); /* close the directory */

	printf("\n"); /* print newline */
}

/**
 * handle_error - small helper func
 *
 * @command: command name
 * @filename: name of the file
 */
void handle_error(const char *command, const char *filename)
{
	if (errno == ENOENT)
	{
		print_error(command, filename);
	}
	else if (errno == EACCES)
	{
		print_error(command, filename);
	}
	else
	{
		printf("%s\n", filename);
	}
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
	int single_column = parse_flags(argc, argv);
	const char *program_name = argv[0];

	if (argc == 1 || (argc == 2 && single_column))
	{
		print_dir(".", program_name, single_column);
	}
	else
	{
		for (i = 1 + (single_column ? 1 : 0); i < argc; i++)
		{
			DIR *dir = opendir(argv[i]);

			if (dir != NULL)
			{
				print_dir(argv[i], program_name, single_column);
				closedir(dir);
			}
			else
			{
				handle_error(program_name, argv[i]);
			}
		}
	}
	return (0); /* return success*/
}
