#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int status;

    /* Boucle pour créer 5 processus enfants */
	for (int i = 0; i < 5; i++)
    {
		/* Création d'un nouveau processus */
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
			printf("Enfant %d (PID: %d) : Exécution de ls -l /tmp\n", i + 1, getpid());

			/* Exécution de la commande ls -l /tmp */
			char *args[] = {"ls", "-l", "/tmp", NULL};

			execvp("ls", args);

			/* Si execvp retourne, c'est qu'il y a eu une erreur */
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		else
		{
			/* Code exécuté par le processus père */
			printf("Père : Attente de la fin du processus enfant %d (PID: %d)\n", i + 1, pid);

			/* Attente de la fin du processus enfant */
			waitpid(pid, &status, 0);

			if (WIFEXITED(status))
			{
				printf("Père : L'enfant %d s'est terminé avec le statut %d\n", i + 1);
			}
			else
			{
				printf("Père : L'enfant %d s'est terminé anormalement\n", i + 1);
			}
		}
	}

	printf("Père : Tous les enfants ont terminé\n");
	return (0);
}
