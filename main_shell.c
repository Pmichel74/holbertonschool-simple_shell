/**
 * main - Entry point for the simple shell program
 * @argc: The argument count (unused)
 * @argv: The argument vector (unused)
 *
 * Return: Always returns 0 (success)
 *
 */

int main(int argc, char *argv[])
{
	char *command = NULL;
	char **args = NULL;
	char **env = argv + 1;

	(void)argc;/*Turn off warnings*/

	while (1)
	{
		command = read_command();

		if (command == NULL)
		{
			printf("\n");
			break;
		}

		if (strlen(command) == 0)
		{
			free(command);
			continue;
		}

		args = tokenize_command(command);
		if (args)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				free_tokens(args);
				free(command);
				exit(0);
			}
			execute_command(args, env);
			free_tokens(args);
		}
		free(command);

	}
	return (0);
}
