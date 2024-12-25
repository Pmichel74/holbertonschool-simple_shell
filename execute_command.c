#include "main.h"

/**
 * execute_command - Executes a command with given arguments
 * @args: Array of command arguments
 * @envp: Array of environment variables
 * @program_name: Name of the shell program
 *
 * Return: 0 on success, -1 on failure
 */
<<<<<<< HEAD
int execute_command(char **args, char **envp,
char *program_name __attribute__((unused)))
=======
int execute_command(char **args, char **envp, char *program_name)
>>>>>>> 6d24d6b (syn)
{
	char *command_path;
	struct stat st;

	if (!args || !args[0])
		return (-1);

	if (strcmp(args[0], "env") == 0)
	{
		print_env(envp);
		return (0);
	}

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (stat(args[0], &st) == 0 && st.st_mode & S_IXUSR)
			command_path = strdup(args[0]);
		else
		{
<<<<<<< HEAD
=======
			fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
>>>>>>> 6d24d6b (syn)
			return (-1);
		}
	}
	else
		command_path = find_command(args[0], envp);

	if (!command_path)
	{
<<<<<<< HEAD
=======
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
>>>>>>> 6d24d6b (syn)
		return (-1);
	}

	if (fork_and_execute(command_path, args, envp) == -1)
	{
<<<<<<< HEAD
=======
		fprintf(stderr, "%s: 1: %s: %s\n", program_name, args[0], strerror(errno));
>>>>>>> 6d24d6b (syn)
		free(command_path);
		return (-1);
	}

	free(command_path);
	return (0);
}
