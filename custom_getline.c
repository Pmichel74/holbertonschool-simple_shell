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
    static char buffer[8192];
    static ssize_t buffer_pos;
    static ssize_t buffer_size;
    ssize_t count = 0;
    char *temp_ptr;

    if (lineptr == NULL || n == NULL)
        return (-1);

    if (*lineptr == NULL)
    {
        *lineptr = malloc(128);
        if (*lineptr == NULL)
            return (-1);
        *n = 128;
    }

    for (;;)
    {
        if (buffer_pos >= buffer_size)
        {
            buffer_size = read(STDIN_FILENO, buffer, 8192);
            buffer_pos = 0;
            if (buffer_size <= 0)
            {
                if (count == 0)
                    return (-1);
                break;
            }
        }

        if (count + 1 >= (ssize_t)*n)
        {
            temp_ptr = malloc((*n) * 2);
            if (temp_ptr == NULL)
                return (-1);
            memcpy(temp_ptr, *lineptr, count);
            free(*lineptr);
            *lineptr = temp_ptr;
            *n = (*n) * 2;
        }

        (*lineptr)[count] = buffer[buffer_pos];
        count++;
        buffer_pos++;

        if ((*lineptr)[count - 1] == '\n')
            break;
    }

    (*lineptr)[count] = '\0';
    return (count);
}
