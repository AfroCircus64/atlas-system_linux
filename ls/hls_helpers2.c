#include "hls.h"

/**
 * print_long_format - func to print the long format
 *
 * @entry: parameter
 * @path: parameter
 */
void print_long_format(struct dirent *entry, const char *path)
{
	char full_path[MAX_ARGS];

	sprintf(full_path, "%s/%s", path, entry->d_name);

	struct stat sb;

	if (lstat(full_path, &sb) == -1)
	{
		perror("lstat");
		exit(EXIT_FAILURE);
	}

	printf("%s ", get_permissions(sb.st_mode));

	printf("%lu ", sb.st_nlink);

	printf("%s ", get_username(sb.st_uid));

	printf("%s ", get_groupname(sb.st_gid));

	printf("%ld ", sb.st_size);

	printf("%.12s ", ctime(&sb.st_mtime) + 4);

	printf("%s\n", entry->d_name);

}

/**
 * get_permissions - func to get perms
 *
 * @mode: parameter
 *
 * Return: perms
 */
char *get_permissions(mode_t mode)
{
	static char perms[11];

	perms[0] = (S_ISDIR(mode)) ? 'd' : '-';
	perms[1] = (mode & S_IRUSR) ? 'r' : '-';
	perms[2] = (mode & S_IWUSR) ? 'w' : '-';
	perms[3] = (mode & S_IXUSR) ? 'x' : '-';
	perms[4] = (mode & S_IRGRP) ? 'r' : '-';
	perms[5] = (mode & S_IWGRP) ? 'w' : '-';
	perms[6] = (mode & S_IXGRP) ? 'x' : '-';
	perms[7] = (mode & S_IROTH) ? 'r' : '-';
	perms[8] = (mode & S_IWOTH) ? 'w' : '-';
	perms[9] = (mode & S_IXOTH) ? 'x' : '-';
	perms[10] = '\0';

	return (perms);
}

/**
 * get_username - func to get username
 *
 * @uid: parameter
 *
 * Return: username
 */
char *get_username(uid_t uid)
{
	struct passwd *pwd;

	pwd = getpwuid(uid);

	return (pwd ? pwd->pw_name : NULL);
}

/**
 * get_groupname - func to get groupname
 *
 * @gid: parameter
 *
 * Return: groupname
 */
char *get_groupname(gid_t gid)
{
	struct group *grp;

	grp = getgrgid(gid);

	return (grp ? grp->gr_name : NULL);
}
