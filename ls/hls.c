#include "hls.h"

/**
 * print_dir - prints the directory
 *
 * @dirname: name of directory
 * @command: command name to be passed into print_error()
 * @opts: options
 */

void print_dir(const char *dirname, const char *command, Options opts)
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

	if (opts.long_format)
	{
		printf("%s:\n", dirname);
	}

	while ((read = readdir(dir)) != NULL) /* iterate through the directory */
	{
		if (opts.show_all == SHOW_NONE && read->d_name[0] == '.')
		{
			continue;
		}
		if (opts.show_all == SHOW_ALMOST_ALL && (_strcmp(read->d_name,
		 ".") == 0 || _strcmp(read->d_name, "..") == 0))
		{
			continue;
		}

		if (opts.long_format)
		{
			print_long_format(read, dirname);
		}
		else
		{
			printf("%s ", read->d_name);
		}
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
	Options opts = parse_options(argc, argv);
	const char *program_name = argv[0];

	if (argc == 1 || (argc == 2 && opts.show_all == SHOW_NONE))
	{
		print_dir(".", program_name, opts);
	}
	else
	{
		for (i = 1; i < argc; i++)
		{
			if (argv[i][0] != '-')
			{
				DIR *dir = opendir(argv[i]);

				if (dir != NULL)
				{
					if (opts.long_format)
					{
						printf("%s:\n", argv[i]);
					}

					print_dir(argv[i], program_name, opts);

					closedir(dir);
				}
				else
				{
					handle_error(program_name, argv[i]);
				}
			}
		}
	}
	return (0); /* return success*/
}
