#include "main.h"

/**
 * execute_command - Executes a command with given arguments
 * @args: Array of command arguments
 * @envp: Array of environment variables
 * @program_name: Name of the shell program
 *
 * Return: 0 on success, 127 if command not found, or -1 on other errors
 */

int execute_command(char **args, char **envp, char *program_name)
{
<<<<<<< HEAD
	char *command_path = NULL;
	struct stat st;
	int result;
=======
    char *command_path = NULL;
    struct stat st;
    int status;
    pid_t pid;
>>>>>>> dcd8586 (sync)

    if (!args || !args[0])
        return (-1);

    if (strcmp(args[0], "env") == 0)
    {
        print_env(envp);
        return (0);
    }

<<<<<<< HEAD
	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (stat(args[0], &st) == 0 && (st.st_mode & S_IXUSR))
			command_path = strdup(args[0]);
		else
		{
			fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
			return (127);
		}
	}
	else
	{
		command_path = find_command(args[0], envp);

		if (!command_path)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
			return (127);
		}
	}

	result = fork_and_execute(command_path, args, envp, program_name);
	free(command_path);
	return (result);
=======
    if (args[0][0] == '/' || args[0][0] == '.')
    {
        if (stat(args[0], &st) == 0 && st.st_mode & S_IXUSR)
            command_path = strdup(args[0]);
    }
    else
    {
        command_path = find_command(args[0], envp);
    }

    if (!command_path)
    {
        fprintf(stderr, "%s: 1: %s: not folllund\n", program_name, args[0]);
        exit(127);  /* Retourne le code d'erreur 127 si la commande n'est pas trouvée */
    }

    pid = fork();
    if (pid == 0)
    {
        /* Processus enfant */
        if (execve(command_path, args, envp) == -1)
        {
            fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]); /* Affiche le message d'erreur si execve échoue */
            exit(127); /* Quitte avec le code de sortie 127 si execve échoue */
        }
    }
    else if (pid > 0)
    {
        /* Processus parent */
        waitpid(pid, &status, 0);

        if (WIFSIGNALED(status))
        {
            /* La commande a été terminée par un signal */
            int signal_number = WTERMSIG(status);
            if (signal_number == SIGINT)
            {
                /* Interruption par Ctrl+C */
                fprintf(stderr, "\n"); /* Affiche juste une nouvelle ligne */
            }
            else
            {
                /* Autre signal */
                fprintf(stderr, "%s: %d: Terminated by signal %d\n", program_name, pid, signal_number);
            }
        }
    }
    else
    {
        /* Erreur lors du fork */
        perror("fork");
        free(command_path);
        return -1;
    }

    free(command_path);
    return (0);
>>>>>>> dcd8586 (sync)
}
