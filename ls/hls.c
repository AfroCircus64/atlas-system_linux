#include "hls.h"

/**
 * _strcmp - function that compares two strings
 * @s1: string 1
 * @s2: string 2
 * Return: success
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}


/**
 * main - Entry point
 *
 * Return: 0 on success
 */
int main(void)
{
	DIR *dir; /* pointer to directory stream */

	/**
	 * dirent - directory entry struct
	 */
	struct dirent *read;

	dir = opendir("."); /* open current pointer */
	if (dir == NULL) /* check if the directory opened without error */
	{
		perror("Error opening directory"); /* print error message */
		return (1); /* return error */
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

	return (0); /* return success */
}
