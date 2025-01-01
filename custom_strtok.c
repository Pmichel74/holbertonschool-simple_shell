#include "main.h"

/**
 * custom_strtok - Split string into tokens
 * @str: String to be parsed
 * @delim: String containing delimiter characters
 * Return: Next token or NULL if no more tokens
 */
char *custom_strtok(char *str, const char *delim)
{
    static char *next_token;
    char *token_start;
    char *token_end;

    if (!delim)
        return (NULL);

    if (str)
        next_token = str;

    if (!next_token)
        return (NULL);

    while (*next_token)
    {
        const char *d = delim;
        int is_delim = 0;
        while (*d)
        {
            if (*next_token == *d)
            {
                is_delim = 1;
                break;
            }
            d++;
        }
        if (!is_delim)
            break;
        next_token++;
    }

    if (*next_token == '\0')
    {
        next_token = NULL;
        return (NULL);
    }

    token_start = next_token;
    token_end = token_start;

    while (*token_end)
    {
        const char *d = delim;
        int is_delim = 0;
        while (*d)
        {
            if (*token_end == *d)
            {
                is_delim = 1;
                break;
            }
            d++;
        }
        if (is_delim)
            break;
        token_end++;
    }

    if (*token_end == '\0')
    {
        next_token = NULL;
    }
    else
    {
        *token_end = '\0';
        next_token = token_end + 1;
    }

    return (token_start);
}
