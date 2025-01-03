#include "main.h"

#define READ_SIZE 1024

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
    void *mem;
    char *ptr_copy, *filler;
    unsigned int index;

    if (new_size == old_size)
        return (ptr);

    if (ptr == NULL)
    {
        mem = malloc(new_size);
        if (mem == NULL) {
            perror("malloc"); /* // Ajouté perror */
            return (NULL);
        }
        return (mem);
    }

    if (new_size == 0 && ptr != NULL)
    {
        free(ptr);
        return (NULL);
    }

    ptr_copy = ptr;
    mem = malloc(new_size);
    if (mem == NULL)
    {
        perror("malloc"); /* // Ajouté perror */
        free(ptr);
        return (NULL);
    }

    filler = mem;
    for (index = 0; index < old_size && index < new_size; index++)
        filler[index] = ptr_copy[index];

    free(ptr);
    return (mem);
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
    if (*lineptr == NULL || *n < b)
    {
        if (b > READ_SIZE)
            *n = b;
        else
            *n = READ_SIZE;
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
    static char read_buffer[READ_SIZE];
    static size_t buffer_pos;
    static ssize_t chars_in_buffer;
    char *line_buffer;
    size_t line_pos = 0;

    if (!lineptr || !n)
        return (-1);

    line_buffer = malloc(READ_SIZE);
    if (!line_buffer) {
        perror("malloc"); /* // Ajouté perror */
        return (-1);
    }

    if (buffer_pos >= (size_t)chars_in_buffer)
    {
        fflush(stream);
        chars_in_buffer = read(fileno(stream), read_buffer, READ_SIZE); /* // Correction : fileno(stream) */
        if (chars_in_buffer <= 0)
        {
            free(line_buffer);
            return (-1);
        }
        buffer_pos = 0;
    }

    while (1)
    {
        /* Copy characters until newline or buffer is full */
        while (buffer_pos < (size_t)chars_in_buffer)
        {
            line_buffer[line_pos++] = read_buffer[buffer_pos++];

            /* Check for newline */
            if (line_buffer[line_pos - 1] == '\n')
            {
                line_buffer[line_pos] = '\0';
                assign_line(lineptr, n, line_buffer, line_pos + 1);
                return (line_pos);
            }

            /* Reallocate if needed */
            if (line_pos >= READ_SIZE) {
                line_buffer = copy_and_reallocate(line_buffer, line_pos, line_pos + READ_SIZE);
                if (line_buffer == NULL) { /* // Vérification après réallocation */
                    perror("realloc"); /* // Ajouté perror */
                    return -1;
                }
            }
        }

        /* Read more data if needed */
        chars_in_buffer = read(fileno(stream), read_buffer, READ_SIZE); /* // Correction : fileno(stream) */
        if (chars_in_buffer <= 0) {
            if (chars_in_buffer < 0) {
                perror("read"); /* // Ajouté perror */
            }
            break;
        }
        buffer_pos = 0;
    }

    /* Handle end of input*/
    if (line_pos == 0)
    {
        free(line_buffer);
        return (-1);
    }

    line_buffer[line_pos] = '\0';
    assign_line(lineptr, n, line_buffer, line_pos + 1);
    return (line_pos);
}
