#include "main.h"

#define BUFFER_SIZE 1024

/**
 * custom_getline - Read line from stream
 * @lineptr: Pointer to the line buffer
 * @n: Size of buffer
 * @stream: Input stream
 *
 * Return: Number of characters read, -1 on failure
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
    static char buffer[BUFFER_SIZE];
    static int buf_pos;
    static int bytes_read;
    char *new_ptr;
    size_t pos = 0;
    char c;

    if (lineptr == NULL || n == NULL || stream == NULL)
        return (-1);

    if (*lineptr == NULL)
    {
        *n = 128;
        *lineptr = malloc(*n);
        if (*lineptr == NULL)
            return (-1);
    }

    while (1)
    {
        if (buf_pos >= bytes_read)
        {
            bytes_read = read(fileno(stream), buffer, BUFFER_SIZE);
            if (bytes_read <= 0)
            {
                if (pos == 0)
                    return (-1);
                break;
            }
            buf_pos = 0;
        }

        c = buffer[buf_pos++];

        if (pos >= (*n - 1))
        {
            *n *= 2;
            new_ptr = malloc(*n);
            if (new_ptr == NULL)
                return (-1);
            memcpy(new_ptr, *lineptr, pos);
            free(*lineptr);
            *lineptr = new_ptr;
        }

        (*lineptr)[pos++] = c;

        if (c == '\n')
            break;
    }

    (*lineptr)[pos] = '\0';
    return (pos);
}
