#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * main - Entry point for the simple shell program.
 * @argc: The number of command-line arguments.
 * @argv: An array of command-line argument strings.
 * @envp: An array of environment variable strings.
 *
 * Return: Always 0.
 */
int main(int argc, char **argv, char **envp)
{
	(void)argc;

	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *args[MAX_ARGS];
	int command_counter = 1;
	char *program_name = argv[0];
	int i;
	char *token;
	int interactive_mode;

/* Check if the shell is running in interactive mode */
interactive_mode = isatty(STDIN_FILENO);

while (1)
{
	if (interactive_mode)
	printf(":) ");

	read = getline(&line, &len, stdin);

	if (read == -1)
{
	if (interactive_mode)
		printf("\n");
	break;
}

line[strcspn(line, "\n")] = 0;

i = 0;
token = strtok(line, " ");
while (token != NULL && i < MAX_ARGS - 1)
{
	args[i] = token;
	i++;
	token = strtok(NULL, " ");
}
args[i] = NULL;

if (args[0] != NULL)
	{
<<<<<<< HEAD
		if (interactive)
			printf(":) ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (interactive)
				printf("\n");
			break;
		}
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (strlen(line) == 0)
			continue;
		args = tokenize_command(line);
		if (!args || args[0] == NULL)
		{
			if (args)
				free_args(args);
			continue;
		}
=======
>>>>>>> ef38c67 (synch)
		if (strcmp(args[0], "exit") == 0)
		{
			free(line); /* Libération de la mémoire avant de quitter */
			exit(0);
		}
		execute_command(args, envp, program_name, command_counter);
	}
	command_counter++;
}
free(line); /* Libération de la mémoire à la fin du programme */
return (0);
}
