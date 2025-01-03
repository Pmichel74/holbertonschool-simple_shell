#include "main.h"

#define READ_SIZE 1024

/**
 * custom_getline - Reads a line from the specified stream.
 * @lineptr: Pointer to the buffer to store the line.
 * @n: Size of the buffer.
 * @stream: Stream to read from (usually stdin).
 *
 * Return: The number of characters read, or -1 on failure or EOF.
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	static char read_buffer[READ_SIZE];
	static size_t buffer_pos = 0;
	static ssize_t chars_in_buffer = 0;
	size_t line_pos = 0;

	/* Check if the arguments are valid */
	if (!lineptr || !n || !stream)
		return (-1);

	/* If no buffer or insufficient size, allocate memory for lineptr */
	if (*lineptr == NULL || *n < READ_SIZE)
	{
		*n = READ_SIZE;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
		{
			perror("malloc");
			return (-1);
		}
	}

	/* Loop to read data into the buffer */
	while (1)
	{
		/* If the buffer is empty, refill it from the stream */
		if (buffer_pos >= (size_t)chars_in_buffer)
		{
			chars_in_buffer = read(fileno(stream), read_buffer, READ_SIZE);
			if (chars_in_buffer < 0)
			{
				perror("read");
				return (-1);
			}
			if (chars_in_buffer == 0) /* EOF */
			{
				if (line_pos == 0) /* If no data was read, return -1 */
					return (-1);
				break;
			}
			buffer_pos = 0;
		}

		/* Copy the character from the read buffer to lineptr */
		(*lineptr)[line_pos++] = read_buffer[buffer_pos++];

		/* If we hit a newline, terminate the string and return */
		if ((*lineptr)[line_pos - 1] == '\n')
		{
			(*lineptr)[line_pos] = '\0';
			return (line_pos);
		}

		/* If the buffer is full, reallocate more space */
		if (line_pos >= *n)
		{
			*n += READ_SIZE;
			*lineptr = realloc(*lineptr, *n);
			if (*lineptr == NULL)
			{
				perror("realloc");
				return (-1);
			}
		}
	}

	/* Add the null terminator */
	(*lineptr)[line_pos] = '\0';
	return (line_pos);
}
