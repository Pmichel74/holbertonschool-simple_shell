#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>



int main()
{

	char *cmd = NULL;/* pointeur pour stocker ligne lue */
	size_t len = 0;/* Longueur de la commande */
	ssize_t nread;/*stock nmbre de caracteres lue par getline*/
	pid_t pid;    /*stock le PID du processus enfant */

    while (1)
	{  /* Boucle infinie pour le shell */
		/* Affiche le prompt et le vide immédiatement */
		printf("$ ");
		fflush(stdout);

		/* Lit la commande de l'utilisateur */
		nread = getline(&cmd, &len, stdin);
		{
			/* Gère EOF (Ctrl+D) */
			printf("\n");
			break;
		}
		/* Supprime le caractère newline à la fin de la commande si présent */
		if (nread > 0 && cmd[nread - 1] == '\n')
		cmd[nread - 1] = '\0';

		/* Vérifie si l'utilisateur veut quitter le shell */
		if (strcmp(cmd, "exit") == 0)
		break;


		/* Crée un nouveau processus */
		pid = fork();

		if (pid == -1)
		{
			/* Erreur lors de la création du processus */
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			 /* Code exécuté par le processus enfant */
            /* Prépare les arguments pour execve */
            char *argv[] = {cmd, NULL};
            char *envp[] = {NULL};

			/* Exécute la commande avec son chemin complet, sans arguments */
            if (execve(cmd, argv, envp) == -1)
			{
			/* Si execl échoue, affiche une erreur */
				perror("execve");
				exit(EXIT_FAILURE);
			}
        }
		else
		{
            /* Code exécuté par le processus parent */
            /* Attend que le processus enfant se termine */
            wait(NULL);
        }
    }
	 /* Libère la mémoire allouée par getline */
    free(cmd);

    return (0);
}
