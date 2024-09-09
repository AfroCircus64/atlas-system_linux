#include "hls.h"

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
	struct dirent *ent;

	dir = opendir("."); /* open current pointer */
	if (dir == NULL) /* check if the directory opened without error */
	{
		perror("Error opening directory"); /* print error message */
		return (1); /* return error */
	}

	while ((ent = readdir(dir)) != NULL) /* iterate through the directory */
	{
		/* skip the current and parent directory */
		if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
			continue;

		printf("%s ", ent->d_name); /* print filename */
	}

	closedir(dir); /* close the directory */

	printf("\n"); /* print newline */

	return (0); /* return success */
}
