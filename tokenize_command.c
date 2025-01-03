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
	char **tokens = malloc(MAX_ARGS * sizeof(char *));
	char *token;
	int i = 0;
	char *processed;

	if (!tokens)
		return (NULL);

	token = custom_strtok(command, " \t\n");
	while (token && i < MAX_ARGS - 1)
	{
		processed = remove_quotes(token);
		if (!processed)
		{
			while (--i >= 0)
				free(tokens[i]);
			free(tokens);
			return (NULL);
		}
		tokens[i] = processed;
		i++;
		token = custom_strtok(NULL, " \t\n");
	}
	tokens[i] = NULL;

	return (tokens);
}
