#include "main.h"

/**
 * find_path - Searches for the PATH in environment variables
 * @envp: Array of environment variables
 *
 * Return: A string containing the value of PATH, or NULL if not found
 */

char *find_path(char *envp[])
{
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5); /*Retourne la valeur après "PATH="*/
	}
	return (NULL);
}

/**
 * check_absolute_path - Checks if the command is an absolute or relative path
 * @command: Name of the command to check
 *
 * Return: The full path of the command if it exists, NULL otherwise
 */

char *check_absolute_path(char *command)
{
	struct stat buffer;

	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
	{
		if (stat(command, &buffer) == 0)
			return (strdup(command));
	}
	return (NULL);
}

/**
 * search_in_path - Searches for a command in the directories specified by PATH
 * @command: Name of the command to search for
 * @path: String containing the PATH value
 *
 * Return: The full path of the command if found, NULL otherwise
 */

char *search_in_path(char *command, char *path)
{
	char *path_copy, *path_token, *file_path;
	int command_length, directory_length;
	struct stat buffer;

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	command_length = strlen(command);
	path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		directory_length = strlen(path_token);
		file_path = malloc(command_length + directory_length + 2);
		if (!file_path)
		{
			free(path_copy);
			return (NULL);
		}

		strcpy(file_path, path_token);
		strcat(file_path, "/");
		strcat(file_path, command);

		if (stat(file_path, &buffer) == 0)
		{
			free(path_copy);
			return (file_path);
		}

		free(file_path);
		path_token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * find_command - Searches for a command in PATH
 * or as an absolute/relative path
 * @command: Name of the command to search for
 * @envp: Array of environment variables
 *
 * Return: The full path of the command if found, NULL otherwise
 */

char *find_command(char *command, char *envp[])
{
	char *path;
	char *absolute_path;

	absolute_path = check_absolute_path(command);

	if (absolute_path)
		return (absolute_path);

	path = find_path(envp);

	if (!path)
		return (NULL);

	return (search_in_path(command, path));
}
