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
    char *path_copy, *file_path;
    char **path_tokens;
    int command_length, directory_length;
    struct stat buffer;
    int i, j;

    path_copy = strdup(path);
    if (!path_copy)
        return (NULL);

    command_length = strlen(command);
    path_tokens = custom_strtok(path_copy, ":");
    if (!path_tokens)
    {
        free(path_copy);
        return (NULL);
    }

    for (i = 0; path_tokens[i] != NULL; i++)
    {
        directory_length = strlen(path_tokens[i]);
        file_path = malloc(command_length + directory_length + 2);
        if (!file_path)
        {
            free(path_copy);
            for (j = 0; path_tokens[j]; j++)
                free(path_tokens[j]);
            free(path_tokens);
            return (NULL);
        }

        strcpy(file_path, path_tokens[i]);
        strcat(file_path, "/");
        strcat(file_path, command);

        if (stat(file_path, &buffer) == 0 && access(file_path, X_OK) == 0)
        {
            free(path_copy);
            for (j = 0; path_tokens[j]; j++)
                free(path_tokens[j]);
            free(path_tokens);
            return (file_path);
        }

        free(file_path);
    }

    free(path_copy);
    for (j = 0; path_tokens[j]; j++)
        free(path_tokens[j]);
    free(path_tokens);
    return (NULL);
}
