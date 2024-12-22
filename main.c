#include "main.h"

/**
 * main - Simple UNIX command line interpreter
 *
 * Return: Always 0
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	pid_t pid;
	int status;

	while (1)
	{
		printf("$ ");
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			printf("\n");
			break;  /* Handle "end of file" condition (Ctrl+D) */
		}

		command[strcspn(command, "\n")] = '\0';

		if (strlen(command) == 0)
			continue;

		pid = fork();
		if (pid == -1)
		{
			perror("Error");
			exit(1);
		}
		else if (pid == 0)
		{
			char *args[] = {command, NULL};
			if (execve(command, args, NULL) == -1)
			{
				printf("Error: No such file or directory\n");
				exit(1);
			}
		}
		else
		{
			wait(&status);
		}
	}

	return (0);
}
