#include "main.h"

char *_which(const char *filename)
{
	char *path, *dir, *full_path;
	static char result[1024];

	path = NULL;
	for (char **env = environ; *env; env++)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			path = *env + 5;
			break;
		}
	}

	if (!path)
	{
		return (NULL);
	}

	path = strdup(path);
	dir = strtok(path, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(filename) + 2);
		sprintf(full_path, "%s/%s", dir, filename);

		if (access(full_path, X_OK) == 0)
		{
			strcpy(result, full_path);
			free(full_path);
			free(path);
			return (result);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}

void exe_command(char *full_path, char **args)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		execve(full_path, args, environ);
		perror("execve");
		exit(1);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	else
	{
		perror("fork");
	}
}
