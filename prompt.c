#include <stdio.h>
#include <stdlib.h>

int main()
{
    /* Pointeur pour stocker la ligne lue */
    char *line = NULL;
    /* Taille du buffer alloué, initialisée à 0 pour que getline alloue automatiquement */
    size_t len = 0;
    /* Variable pour stocker le nombre de caractères lus par getline */
    ssize_t nread;

    /* Boucle principale du programme */
    while (1)
	{
        /* Affiche le prompt */
        printf("$ ");
        /* Force l'affichage immédiat du prompt */
        fflush(stdout);

        /* Lit une ligne depuis l'entrée standard
         * &line : adresse du pointeur qui sera alloué par getline
         * &len : adresse de la variable qui contiendra la taille allouée
         * stdin : flux d'entrée standard
         */
        nread = getline(&line, &len, stdin);

        /* Vérifie si getline a rencontré une erreur ou EOF */
        if (nread == -1)
		{
            /* Vérifie spécifiquement si c'est la fin du fichier (EOF) */
            if (feof(stdin))
			{
                /* Ajoute une nouvelle ligne pour l'esthétique en cas de EOF */
                printf("\n");
                /* Sort de la boucle si EOF est atteint */
                break;
            }
			else
			{
                /* Affiche un message d'erreur si ce n'est pas EOF */
                perror("getline");
                /* Quitte le programme avec un code d'erreur */
                exit(EXIT_FAILURE);
            }
        }

        /* Si la lecture a réussi, affiche la ligne lue
         * Pas besoin d'ajouter \n car getline inclut le saut de ligne */
        printf("%s %s  %s", line, line, line);
    }

    /* Libère la mémoire allouée par getline */
    free(line);
    /* Termine le programme avec succès */
    return 0;
}
