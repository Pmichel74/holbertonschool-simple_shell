#include "main.h"

#define BUFSIZE 1024

/**
 * custom_getline - Custom getline function
 * @lineptr: Pointer to buffer where line is stored
 * @n: Pointer to size of buffer
 * @stream: File stream (unused)
 *
 * Return: Number of bytes read, -1 on failure
 */
ssize_t custom_getline(char **lineptr, size_t *n,
FILE *stream __attribute__((unused)))
{
	static char buf[BUFSIZE];
	static int i, len;
	int j;
	char c, *new_ptr;

	if (lineptr == NULL || n == NULL)
		return (-1);
	if (*lineptr == NULL)
	{
		*n = BUFSIZE;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	j = 0;
	while (1)
	{
		if (i >= len)
		{
			i = len = 0;
			len = read(STDIN_FILENO, buf, BUFSIZE);
			if (len == -1)
				return (-1);
			if (len == 0 && j == 0)
				return (-1);
			if (len == 0)
				break;
		}
		c = buf[i++];
		if (j >= (int)*n - 1)
		{
			*n += BUFSIZE;
			new_ptr = malloc(*n);
			if (!new_ptr)
				return (-1);
			memcpy(new_ptr, *lineptr, j);
			free(*lineptr);
			*lineptr = new_ptr;
		}
		(*lineptr)[j++] = c;
		if (c == '\n')
			break;
	}
	(*lineptr)[j] = '\0';
	return (j);
}
