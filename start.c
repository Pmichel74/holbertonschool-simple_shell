#include "main.h"

/**
 * main - Entry point for the simple shell program
 * This function implements a basic command-line interface that:
 * - Displays a prompt
 * Return: Always 0 (success)
 */
int main(void)
{
	char *line = NULL;/*stock ligne de getline*/
	size_t len = 0;/*stock longueur de ligne*/
	ssize_t num_read;/*stock nbre de char de getline*/

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		num_read = getline(&line, &len, stdin);
		if (num_read == -1)
		{
			printf("\n");
			break;
		}

		line[strcspn(line, "\n")] = '\0';
		/*execute_command(line);*/
	}

	free(line);
	return (0);
}

/**
 * execute_command - Executes a given command with arguments
 * @command: The command to execute (first argument)
 * @argv: Array of arguments, including the command
 * as the first element
 */
void execute_command(char *command)
{
	pid_t pid_child = fork();
	int status;

	if (pid_child == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid_child == 0)
	{
		char *argv[2];
			argv[0] = command;
			argv[1] = NULL;

			if (execve(command, argv, environ) == -1)
			{
				printf("./shell: No such file or directory\n");
				exit(1);
			}
	}
	else
		waitpid(pid_child, &status, 0);
}
