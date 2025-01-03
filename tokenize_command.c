#include "main.h"

/**
 * remove_quotes - Remove quotes from a string
 * @str: String to process
 * Return: New string without quotes
 */
static char *remove_quotes(char *str)
{
    int len = strlen(str);
    char *new_str = malloc(len + 1);
    int i, j = 0;

    if (!new_str)
        return (NULL);

    for (i = 0; str[i]; i++)
    {
        if (str[i] != '"' && str[i] != '\\')
            new_str[j++] = str[i];
    }
    new_str[j] = '\0';

    return (new_str);
}

/**
 * tokenize_command - Split command line into tokens
 * @command: Command line to split
 *
 * Return: Array of tokens
 */
char **tokenize_command(char *command)
{
    char **raw_tokens;
    char **processed_tokens;
    int i, j;
    int token_count = 0;

    if (!command)
        return (NULL);

    raw_tokens = custom_strtok(command, " \t\n");
    if (!raw_tokens)
        return (NULL);

    /* // Count tokens */
    while (raw_tokens[token_count])
        token_count++;

    processed_tokens = malloc((token_count + 1) * sizeof(char *));
    if (!processed_tokens)
    {
        for (i = 0; raw_tokens[i]; i++)
            free(raw_tokens[i]);
        free(raw_tokens);
        return (NULL);
    }

    for (i = 0, j = 0; i < token_count && j < MAX_ARGS - 1; i++)
    {
        processed_tokens[j] = remove_quotes(raw_tokens[i]);
        if (!processed_tokens[j])
        {
            while (--j >= 0)
                free(processed_tokens[j]);
            free(processed_tokens);
            for (i = 0; raw_tokens[i]; i++)
                free(raw_tokens[i]);
            free(raw_tokens);
            return (NULL);
        }
        j++;
    }
    processed_tokens[j] = NULL;

    /* // Free raw_tokens */
    for (i = 0; raw_tokens[i]; i++)
        free(raw_tokens[i]);
    free(raw_tokens);

    return processed_tokens;
}
