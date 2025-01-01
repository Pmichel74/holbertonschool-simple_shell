#include "main.h"

/**
 * tokenize_command - Splits a command string into an array of tokens
 * @command: The input command string to be tokenized
 *
 * This function takes a single command string and breaks it down into
 * individual tokens (words).
 *
 * Return: A pointer to an array of strings containing the tokens,
 *        or NULL if memory allocation fails or the input is invalid
 */

char **tokenize_command(char *command)
{
	char **tokens;
	char *token;
	int i = 0;

	tokens = malloc(MAX_ARGS * sizeof(char *));

	if (!tokens)
	{
		perror("malloc failed");
		return (NULL);
	}

	token = custom_strtok(command, " ");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		tokens[i] = strdup(token);
		if (!tokens[i])
		{
			perror("strdup failed");
			free_string_array(tokens);
			return (NULL);
		}
		i++;
		token = custom_strtok(NULL, " ");
	}
	tokens[i] = NULL;
	return (tokens);
}
