#include "main.h"

#define READ_BUF_SIZE 1024
#define INITIAL_BUF_SIZE 120

/**
 * copy_and_reallocate - Copy with a new size without using realloc
 * @old_buf: Old buffer to copy
 * @old_size: Size of the old buffer
 * @new_size: Desired new size
 *
 * Return: New buffer or NULL if failed
 */

char *copy_and_reallocate(char *old_buf, size_t old_size,
size_t new_size)
{
	char *new_buf;
	size_t i;

	new_buf = malloc(new_size);
	if (!new_buf)
		return (NULL);

	for (i = 0; i < old_size && i < new_size; i++)
		new_buf[i] = old_buf[i];

	free(old_buf);
	return (new_buf);
}

/**
 * custom_getline - Reads a line from the input stream
 * @lineptr: Pointer to the buffer containing the line
 * @n: Size of the buffer
 * @stream: Input stream
 *
 * Return: Number of characters read, -1 if error
 */

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	static char read_buf[READ_BUF_SIZE];
	static size_t buf_pos;
	static ssize_t chars_read;
	size_t line_pos = 0;
	char *new_ptr;

	if (!lineptr || !n || !stream)
		return (-1);

	if (*lineptr == NULL)
	{
		*n = INITIAL_BUF_SIZE;
		*lineptr = malloc(*n);
		if (!*lineptr)
			return (-1);
	}

	while (1)
	{
		if (buf_pos >= (size_t)chars_read)
		{
			chars_read = read(fileno(stream), read_buf, READ_BUF_SIZE);
			buf_pos = 0;
			if (chars_read <= 0)
			{
				if (line_pos == 0)
					return (-1);
				break;
			}
		}

		if (line_pos >= *n - 1)
		{
			new_ptr = copy_and_reallocate(*lineptr, *n, *n * 2);
			if (!new_ptr)
				return (-1);
			*lineptr = new_ptr;
			*n *= 2;
		}

		(*lineptr)[line_pos++] = read_buf[buf_pos++];

		if ((*lineptr)[line_pos - 1] == '\n')
			break;
	}

	(*lineptr)[line_pos] = '\0';
	return (line_pos);
}
