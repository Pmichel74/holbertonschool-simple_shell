#include "main.h"

/**
 * main - Simple UNIX command line interpreter
 * @argc: Argument count (unused)
 * @argv: Argument vector
 * @envp: Environment variables (unused)
 * Return: Always 0
 */
int main(int argc, char *argv[], char *envp[])
{
	char *command = NULL;
	size_t bufsize = 0;
	ssize_t characters;
	pid_t pid;
	char *args[2];

	(void)argc;
	(void)envp;
	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		characters = getline(&command, &bufsize, stdin);
		if (characters == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		command[strcspn(command, "\n")] = '\0';
		if (strlen(command) == 0)
			continue;
		pid = fork();
		if (pid == -1)
			print_error(argv[0], "fork");
		else if (pid == 0)
		{
			args[0] = command;
			args[1] = NULL;
			if (execve(command, args, NULL) == -1)
			{
				print_error(argv[0], command);
				exit(1);
			}
		}
		else
			wait(NULL);
	}
	free(command);
	return (0);
}
