#include "main.h"

/**
 * custom_getline - Read line from stdin
 * @lineptr: Pointer to the buffer that will hold the read line
 * @n: Size of the buffer
 * @stream: Input stream to read from (unused)
 *
 * Return: Number of bytes read, or -1 on failure
 */
ssize_t custom_getline(char **lineptr, size_t *n,
FILE *stream __attribute__((unused)))
{
	static char buff[BUFSIZ];
	static ssize_t buff_i;
	static ssize_t bytes_read;
	ssize_t i = 0;
	char c;

	if (!lineptr || !n)
		return (-1);

	if (*lineptr == NULL)
	{
		*n = BUFSIZ;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}

	while (1)
	{
		if (buff_i >= bytes_read)
		{
			bytes_read = read(STDIN_FILENO, buff, BUFSIZ);
			if (bytes_read <= 0)
				return (-1);
			buff_i = 0;
		}

		c = buff[buff_i++];
		(*lineptr)[i++] = c;

		if (c == '\n' || i >= BUFSIZ - 1)
			break;
	}

	(*lineptr)[i] = '\0';
	return (i);
}
