#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * void_print_path_directory : Function to print in the PATH environment variable
 * Each directory is printed on a separate line
 * If PATH is not found, an error message is displayed
 */
void print_path_directories(void)
{
	/* Récupère la valeur de la variable d'environnement PATH */
	char *path = getenv("PATH");

	if (path == NULL)
	{
		/* Affiche un message d'erreur si PATH n'est pas trouvé */
		printf("Variable d'environnement PATH non trouvée.\n");
		return;
	}

	/* Utilise strtok pour séparer la chaîne PATH en répertoires individuels */
	char *token = strtok(path, ":");

	while (token != NULL)
	{
		/* Affiche chaque répertoire sur une nouvelle ligne */
		printf("%s\n", token);
		/* Passe au répertoire suivant */
		token = strtok(NULL, ":");
	}
}

int main(void)
{
	/* Appelle la fonction pour afficher les répertoires du PATH */
	print_path_directories();
	return (0);
}
