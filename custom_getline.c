#include "main.h"

#define BUFFER_SIZE 1024

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
    static char buffer[BUFFER_SIZE];
    static ssize_t pos;
    static ssize_t chars_read;
    ssize_t i;
    char *new_ptr;
    char c;

    if (lineptr == NULL || n == NULL)
        return (-1);

    if (*lineptr == NULL)
    {
        *n = BUFFER_SIZE;
        *lineptr = malloc(*n);
        if (*lineptr == NULL)
            return (-1);
    }

    i = 0;
    while (1)
    {
        if (pos >= chars_read)
        {
            chars_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            if (chars_read <= 0)
                return (-1);
            pos = 0;
        }

        c = buffer[pos++];
        if (i >= (ssize_t)(*n - 1))
        {
            new_ptr = malloc(*n * 2);
            if (new_ptr == NULL)
                return (-1);
            memcpy(new_ptr, *lineptr, i);
            free(*lineptr);
            *lineptr = new_ptr;
            *n *= 2;
        }
        (*lineptr)[i++] = c;

        if (c == '\n')
            break;
    }
    (*lineptr)[i] = '\0';
    return (i);
}
