#include "main.h"

void execmd(char *cmd)
{
    pid_t pid;

    /* Création d'un processus enfant */
    pid = fork();

    if (pid == -1)
    {
		/* Gestion de l'erreur de fork */
		perror("Error:");
		return;
	}
	else if (pid == 0)
	{

			/* Exécute la commande avec son chemin complet, sans arguments */
			if (execve(cmd) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		} else
		{
			wait(NULL);
		}
    }
