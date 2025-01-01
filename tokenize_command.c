#include "main.h"

/**
 * tokenize_command - Split command into tokens
 * @command: Command string to split
 *
 * Return: Array of tokens or NULL on failure
 */

char **tokenize_command(char *command)
{
	char **tokens = malloc(MAX_ARGS * sizeof(char *));
	char *token;
	int i = 0;
	char *cmd_copy;

	if (!tokens)
		return (NULL);

	cmd_copy = strdup(command);
	if (!cmd_copy)
	{
		free(tokens);
		return (NULL);
	}

	token = custom_strtok(cmd_copy, " \t\n");
	while (token && i < MAX_ARGS - 1)
	{

		if (token[0] == '"' && token[strlen(token) - 1] == '"')
		{
			token[strlen(token) - 1] = '\0';
			token++;
		}

		tokens[i] = strdup(token);
		if (!tokens[i])
		{
			free(cmd_copy);
			while (i > 0)
				free(tokens[--i]);
			free(tokens);
			return (NULL);
		}
		i++;
		token = custom_strtok(NULL, " \t\n");
	}
	tokens[i] = NULL;

	free(cmd_copy);
	return (tokens);
}
