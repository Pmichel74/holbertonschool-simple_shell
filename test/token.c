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

	token = strtok(command, " ");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		tokens[i] = strdup(token);
		if (!tokens[i])
		{
			perror("strdup failed");
			free_tokens(tokens);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * free_tokens - Frees memory allocated for an array of strings
 * @tokens: Pointer to an array of strings (char pointers) to be freed
 *
 * This function iterates through the array of strings, freeing each
 * individual string, and then frees the array itself.
 *
 */

void free_tokens(char **tokens)
{
	int i;

	for (i = 0; tokens[i] != NULL; i++)
		free(tokens[i]);
	free(tokens);
}
