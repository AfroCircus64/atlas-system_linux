#include "_getline.h"
#include <unistd.h>

static char buffer[READ_SIZE];
static size_t buf_pos = 0;
static size_t buf_len = 0;

/**
 * _getline - reads an entire line from a file descriptor
 * @fd: file descriptor to read from
 * Return: pointer to the read line or NULL
 */
char *_getline(const int fd)
{
    char *line = NULL;

    while (1)
    {
        size_t newline = buf_len;

		for (; newline > buf_pos && buffer[newline] != '\n'; --newline) {}

        if (newline > buf_pos)
        {
            size_t len = newline - buf_pos;

            line = malloc(len + 1);
            if (!line)
			{
                return (NULL);
			}

            memcpy(line, buffer + buf_pos, len);
            line[len] = '\0';

            for (size_t i = 0; i < buf_len - newline; ++i)
			{
				buffer[i] = buffer[buf_len - newline + i];
			}

            buf_len -= newline - buf_pos;
            buf_pos = 0;

            break;
        }

        if (buf_len == buf_pos || buf_len == READ_SIZE)
        {
            buf_len = read(fd, buffer, READ_SIZE);
            if (buf_len <= 0)
			{
                return (NULL);
			}
            buf_pos = 0;
        }
    }

    return (line);
}
