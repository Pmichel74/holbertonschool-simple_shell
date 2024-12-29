#include "main.h"

/**
 * main - Main execution loop for the simple shell program
 * @argc: Argument count (unused).
 * @argv: Argument vector.
 * @envp: Array of environment variables.
 *
 * Return: Always returns 0 (success).
 */
int main(int argc, char *argv[], char *envp[])
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args = NULL;
	int interactive = isatty(STDIN_FILENO);
	int status = 0;
	int command_counter = 0; /* Compteur de commandes */

	(void)argc; /* Suppress unused parameter warning */

	while (1)
	{
		if (interactive)
			printf("$ ");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (feof(stdin))
			{
				if (interactive)
					printf("\n");
				free(line);
				exit(status); /* Sortie propre avec code de retour */
			}
			else
			{
				perror("getline");
				free(line);
				exit(1); /* Quitte avec un code d'erreur */
			}
		}

		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		command_counter++; /* Incrémente le compteur de commandes */

		/* Gestion de la commande 'exit' et de ses arguments */
		status = exitshell(line);
		if (status != -99)
		{
			free(line);
			exit(status);
		}

		if (strlen(line) == 0)
		{
			free(line);
			line = NULL;
			continue;
		}

		args = tokenize_command(line);
		if (!args || args[0] == NULL)
		{
			free_args(args);
			free(line);
			line = NULL;
			continue;
		}

		status = execute_command(args, envp, argv[0]);
		if (status == 127)
			fprintf(stderr, "%s: %d: %s: not found\n",
				argv[0], command_counter, args[0]);

		free_args(args);
		free(line);
		line = NULL;
		args = NULL;
	}
	return (0);
}
