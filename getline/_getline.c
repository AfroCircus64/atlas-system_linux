#include "_getline.h"
#include <unistd.h>

#define MAX_FDS 1024

static char buffer[MAX_FDS][READ_SIZE];
static size_t buf_pos[MAX_FDS] = {0};
static size_t buf_len[MAX_FDS] = {0};

/**
 * _getline - reads an entire line from a file descriptor
 * @fd: file descriptor to read from
 * Return: pointer to the read line or NULL
 */
char *_getline(const int fd)
{
    char *line = NULL;

	if (fd == -1)
	{
		for (int i = 0; i < MAX_FDS; i++)
		{
			buf_pos[i] = 0;
			buf_len[i] = 0;
		}
		return (NULL);
	}

	if (fd < 0 || fd >= MAX_FDS)
	{
		return (NULL);
	}

    while (1)
    {
        size_t newline = buf_len[fd];

		for (; newline > buf_pos[fd] && buffer[fd][newline] != '\n'; --newline) {}

        if (newline > buf_pos[fd])
        {
            size_t len = newline - buf_pos[fd];

            line = malloc(len + 1);
            if (!line)
			{
                return (NULL);
			}

            memcpy(line, buffer + buf_pos[fd], len);
            line[len] = '\0';

            for (size_t i = 0; i < buf_len[fd] - newline; ++i)
			{
				buffer[fd][i] = buffer[fd][buf_len[fd] - newline + i];
			}

            buf_len[fd] -= newline - buf_pos[fd];
            buf_pos[fd] = 0;

            break;
        }

        if (buf_len[fd] == buf_pos[fd] || buf_len[fd] == READ_SIZE)
        {
            buf_len[fd] = read(fd, buffer[fd], READ_SIZE);
            if (buf_len[fd] <= 0)
			{
                return (NULL);
			}
            buf_pos[fd] = 0;
        }
    }

    return (line);
}
