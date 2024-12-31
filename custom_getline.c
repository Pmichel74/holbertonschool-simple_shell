#include "main.h"

/**
 * custom_getline - Reads an entire line from stream
 * @lineptr: Pointer to the buffer that will store the line
 * @n: Pointer to the size of the buffer
 * @stream: The stream to read from (unused)
 *
 * Return: Number of characters read, -1 on failure
 */
ssize_t custom_getline(char **lineptr, size_t *n,
FILE *stream __attribute__((unused)))
{
    static char buffer[1024];
    static int buf_size;
    static int buf_pos;
    int line_pos = 0;
    char *temp;

    if (!lineptr || !n)
        return (-1);

    if (*lineptr == NULL)
    {
        *n = 128;
        *lineptr = malloc(sizeof(char) * (*n));
        if (!*lineptr)
            return (-1);
    }

    while (1)
    {
        if (buf_pos == buf_size)
        {
            buf_size = read(STDIN_FILENO, buffer, 1024);
            buf_pos = 0;
            if (buf_size <= 0)
                return (-1);
        }

        if ((size_t)line_pos + 1 >= *n)
        {
            *n *= 2;
            temp = malloc(*n);
            if (!temp)
                return (-1);
            memcpy(temp, *lineptr, line_pos);
            free(*lineptr);
            *lineptr = temp;
        }

        (*lineptr)[line_pos] = buffer[buf_pos];

        if (buffer[buf_pos] == '\n')
        {
            (*lineptr)[line_pos + 1] = '\0';
            buf_pos++;
            return (line_pos + 1);
        }

        line_pos++;
        buf_pos++;
    }
}
