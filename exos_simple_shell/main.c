#include "main.h"

int main(void)
{
	char *prompt = "$ ";
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t nchars_read;

    /* Boucle principale du shell */
	while (1)
	{
		/* Affichage du prompt */
		printf("%s", prompt);

		/* Lecture de la commande entrée par l'utilisateur */
		nchars_read = getline(&lineptr, &n, stdin);

		/* Gestion de la fin de fichier (Ctrl+D) */
		if (nchars_read == -1)
		{
			printf("\n");
			free(lineptr);
			exit(EXIT_SUCCESS);
		}

		/* Suppression du caractère newline à la fin de la commande */
		lineptr[strcspn(lineptr, "\n")] = '\0';

		/* Exécution de la commande */
		if (execvp(lineptr, (char *const[])
		{lineptr, NULL}) == -1)
		{
			/* Gestion des erreurs pour les commandes inexistantes */
			printf("./shell: No such file or directory\n");
		}

		/* Libération de la mémoire allouée pour la ligne de commande */
		free(lineptr);
		lineptr = NULL;
	}

	return (0);
}
