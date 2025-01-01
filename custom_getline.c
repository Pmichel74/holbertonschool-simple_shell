#include "main.h"

/**
 * custom_getline - reads a line from stdin
 * @lineptr: pointer to the buffer containing the line
 * @n: size of buffer
 * @stream: input stream (unused)
 *
 * Return: number of bytes read
 */
ssize_t custom_getline(char **lineptr, size_t *n,
FILE *stream __attribute__((unused)))
{
	static char buffer[1024];
	static int index;
	static int bytes_read;
	ssize_t count = 0;

	if (!lineptr || !n)
		return (-1);

	if (*lineptr == NULL)
	{
		*n = 1024;
		*lineptr = malloc(*n);
		if (!*lineptr)
			return (-1);
	}
	while (1)
	{
		if (index >= bytes_read)
		{
			index = 0;
			bytes_read = read(0, buffer, 1024);
			if (bytes_read <= 0)
				return (-1);
		}

		(*lineptr)[count++] = buffer[index++];

		if (count >= (ssize_t)(*n - 1))
		{
			*n *= 2;
			*lineptr = realloc(*lineptr, *n);
			if (!*lineptr)
				return (-1);
		}

		if ((*lineptr)[count - 1] == '\n')
			break;
	}
	(*lineptr)[count] = '\0';
	return (count);
}
