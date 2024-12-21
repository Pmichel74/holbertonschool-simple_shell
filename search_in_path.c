#include "main.h"

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
