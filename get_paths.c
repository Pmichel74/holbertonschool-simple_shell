#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* Déclaration de la variable d'environnement externe */
extern char **environ;

/**
 * _which - Searches for the full path of an executable
 * @filename: Name of the executable file to search for
 *
 * Description: This function simulates the behavior of the 'which' command.
 * It iterates through the directories listed in the PATH environment variable
 * to find the full path of the specified executable.
 *
 * Return: A pointer to a string containing the full path of the executable
 * if found, or NULL if not found.
 */
char *_which(const char *filename)
{
	char *path, *dir, *full_path;
	static char result[1024];  /* Buffer statique pour stocker le résultat */

	path = NULL;
	/* Parcourt les variables d'environnement pour trouver PATH */
	for (char **env = environ; *env; env++)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			path = *env + 5;  /* Pointe vers le début de la valeur de PATH */
			break;
		}
	}

	if (!path)
		return (NULL);  /* Retourne NULL si PATH n'est pas trouvé */

	path = strdup(path);  /* Duplique PATH pour pouvoir le modifier */
	dir = strtok(path, ":");  /* Divise PATH en répertoires individuels */
	while (dir)
	{
		/* Construit le chemin complet pour le fichier */
		full_path = malloc(strlen(dir) + strlen(filename) + 2);
		sprintf(full_path, "%s/%s", dir, filename);

		/* Vérifie si le fichier existe et est exécutable */
		if (access(full_path, X_OK) == 0)
		{
			strcpy(result, full_path);  /* Copie le chemin dans le buffer de résultat */
			free(full_path);
			free(path);
			return (result);  /* Retourne le chemin trouvé */
		}
	   free(full_path);
		dir = strtok(NULL, ":");  /* Passe au répertoire suivant */
	}
   free(path);
	return (NULL);  /* Retourne NULL si le fichier n'est pas trouvé */
}

/**
 * main - Entry point of the program
 * @argc: Number of arguments passed to the program
 * @argv: Array of strings containing the arguments
 *
 * Description: This function is the main entry point of the program.
 * It checks if arguments have been provided, then calls the _which
 * function for each argument. If a path is found for an argument,
 * it is displayed on the standard output.
 *
 * Return: 0 on success, 1 if no arguments are provided
 */
int main(int argc, char *argv[])
{
	char *result;

	/* Vérifie si des arguments ont été fournis */
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s filename ...\n", argv[0]);
		return (1);
	}

	/* Parcourt tous les arguments fournis */
	for (int i = 1; i < argc; i++)
	{
		result = _which(argv[i]);
		if (result)
			printf("%s\n", result);  /* Affiche le chemin si trouvé */
	}

	return (0);
}
