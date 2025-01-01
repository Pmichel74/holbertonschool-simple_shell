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
    char *new_ptr;

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

        if (count >= (ssize_t)(*n - 1))
        {
            new_ptr = malloc(*n * 2);
            if (!new_ptr)
                return (-1);
            memcpy(new_ptr, *lineptr, count);
            free(*lineptr);
            *lineptr = new_ptr;
            *n *= 2;
        }

        (*lineptr)[count++] = buffer[index++];

        if ((*lineptr)[count - 1] == '\n')
            break;
    }

    (*lineptr)[count] = '\0';
    return (count);
}
