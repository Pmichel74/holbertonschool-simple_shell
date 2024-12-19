#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * main - Exemple d'utilisation de la fonction stat
 * @ac: Nombre d'arguments passés au programme
 * @av: Tableau de chaînes contenant les arguments
 *
 * Return: 0 en cas de succès, 1 si aucun argument n'est fourni
 */
int main(int ac, char **av)
{
	unsigned int i;
	struct stat st;

	/* Vérifier si au moins un argument (chemin de fichier) a été fourni */
	if (ac < 2)
	{
		printf("Usage: %s path_to_file ...\n", av[0]);
		return (1);
	}

	/* Commencer à partir du premier argument (indice 1) */
	i = 1;

	/* Boucle pour traiter chaque argument (chemin de fichier) */
	while (av[i])
	{
		/* Afficher le chemin du fichier actuellement traité */
		printf("%s:", av[i]);

		/* Utiliser stat pour vérifier l'existence du fichier */
		if (stat(av[i], &st) == 0)
		{
			/* Si stat réussit (retourne 0), le fichier existe */
			printf(" FOUND\n");
		}
		else
		{
			/* Si stat échoue, le fichier n'existe pas ou une erreur s'est produite */
			printf(" NOT FOUND\n");
		}

		/* Passer à l'argument suivant */
		i++;
	}

	return (0);
}
