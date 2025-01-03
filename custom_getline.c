#include "main.h"

/**
 * copy_and_reallocate - Reallocates memory for buffer
 * @ptr: Original buffer
 * @old_size: Old size
 * @new_size: New size
 * Return: Pointer to new buffer
 */
static void *copy_and_reallocate(void *ptr, unsigned int old_size,
unsigned int new_size)
{
	void *new_mem;
	char *ptr_copy, *filler;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	new_mem = malloc(new_size);
	if (new_mem == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = new_mem;
	for (i = 0; i < old_size && i < new_size; i++)
		filler[i] = ptr_copy[i];

	free(ptr);
	return (new_mem);
}

/**
 * assign_line - Assigns buffer to lineptr
 * @lineptr: Buffer to store input
 * @n: Size of lineptr
 * @buffer: String to assign
 * @b: Size of buffer
 */
static void assign_line(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * custom_getline - Read input from stream
 * @lineptr: Buffer to store input
 * @n: Size of buffer
 * @stream: Stream to read from
 * Return: Number of bytes read
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);

	input = 0;
	buffer = malloc(120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= 120)
			buffer = copy_and_reallocate(buffer, input, input + 1);
		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';
	assign_line(lineptr, n, buffer, input);
	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}
