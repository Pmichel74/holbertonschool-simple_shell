#include "main.h"

#define BUFFER_SIZE 1024

/**
 * custom_getline - Custom implementation of getline
 * @lineptr: Pointer to buffer where the line will be stored
 * @n: Pointer to size of allocated buffer
 * @stream: File stream to read from (unused in this implementation)
 * Return: Number of characters read, -1 on failure or EOF
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
    static char buffer[BUFFER_SIZE];
    static size_t buf_pos;
    static ssize_t buf_size;
    size_t pos = 0;
    char *new_ptr;
    (void)stream;

    if (!lineptr || !n)
        return (-1);

    /* Initial allocation if needed */
    if (*lineptr == NULL)
    {
        *lineptr = malloc(BUFFER_SIZE);
        if (!*lineptr)
            return (-1);
        *n = BUFFER_SIZE;
    }

    while (1)
    {
        /* Read more data if buffer is empty */
        if (buf_pos >= (size_t)buf_size)
        {
            buf_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            if (buf_size <= 0)
            {
                if (pos == 0)
                    return (-1);
                break;
            }
            buf_pos = 0;
        }

        /* Reallocate if needed */
        if (pos >= *n - 1)
        {
            new_ptr = malloc(*n * 2);
            if (!new_ptr)
                return (-1);
            memcpy(new_ptr, *lineptr, pos);
            free(*lineptr);
            *lineptr = new_ptr;
            *n *= 2;
        }

        /* Copy and check for newline */
        (*lineptr)[pos] = buffer[buf_pos];
        if (buffer[buf_pos] == '\n')
        {
            pos++;
            buf_pos++;
            break;
        }
        pos++;
        buf_pos++;
    }

    (*lineptr)[pos] = '\0';
    return (pos);
}
