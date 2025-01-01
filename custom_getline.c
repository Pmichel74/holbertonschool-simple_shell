#include "main.h"

/**
 * custom_getline - Custom implementation of getline
 * @lineptr: Pointer to the line buffer
 * @n: Pointer to the size of the buffer
 * @stream: Stream to read from (unused)
 *
 * Return: Number of characters read, -1 on failure
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream __attribute__((unused)))
{
    static char buff[1024];
    static ssize_t buff_size;
    static ssize_t buff_pos;
    ssize_t bytes = 0;
    int c;

    if (!lineptr || !n)
        return (-1);

    if (!*lineptr)
    {
        *n = 1024;
        *lineptr = malloc(*n);
        if (!*lineptr)
            return (-1);
    }

    while (1)
    {
        if (buff_pos >= buff_size)
        {
            buff_size = read(STDIN_FILENO, buff, 1024);
            if (buff_size <= 0)
            {
                if (bytes == 0)
                    return (-1);
                break;
            }
            buff_pos = 0;
        }

        c = buff[buff_pos++];
        (*lineptr)[bytes++] = c;

        if (bytes >= (ssize_t)*n - 1)
        {
            char *new_ptr = malloc(*n * 2);
            if (!new_ptr)
                return (-1);
            memcpy(new_ptr, *lineptr, bytes);
            free(*lineptr);
            *lineptr = new_ptr;
            *n *= 2;
        }

        if (c == '\n')
            break;
    }

    (*lineptr)[bytes] = '\0';
    return (bytes);
}
