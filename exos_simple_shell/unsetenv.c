#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * _unsetenv - Delete a variable from the environment
 * @name: Name of the environment variable to delete
 *
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
	/* Vérification de la validité du nom */
	if (name == NULL || *name == '\0' || strchr(name, '=') != NULL)
	{
		return (-1);  /* Nom invalide */
	}

	size_t name_len = strlen(name);
	char **env_ptr;
	int found = 0;

	/* Parcours de l'environnement */
	for (env_ptr = environ; *env_ptr != NULL;)
	{
		/* Vérification si la variable actuelle correspond au nom */
		if (strncmp(*env_ptr, name, name_len) == 0 && (*env_ptr)[name_len] == '=')
		{
			/* Variable trouvée, on la supprime */
			char **move_ptr = env_ptr;

			free(*env_ptr);  /* Libération de la mémoire de la variable */

			/* Décalage des variables suivantes */
			do {
				move_ptr[0] = move_ptr[1];
			} while (*move_ptr++);

			found = 1;
			/* On ne incrémente pas env_ptr ici pour vérifier la variable suivante */
		}
		else
		{
			env_ptr++;  /* Passe à la variable suivante */
		}
	}

	return (found ? 0 : -1);  /* Retourne 0 si trouvé et supprimé, -1 sinon */
}

/**
 * main - Test function for _unsetenv
 *
 * Return: Always 0
 */
int main(void)
{
	/* Test de _unsetenv */
	setenv("TEST_VAR", "test_value", 1);
	printf("Avant: TEST_VAR=%s\n", getenv("TEST_VAR"));

	if (_unsetenv("TEST_VAR") == 0)
	{
		printf("Après: TEST_VAR=%s\n", getenv("TEST_VAR"));
	}
	else
	{
		printf("Erreur lors de la suppression de TEST_VAR\n");
	}

	/* Test avec une variable inexistante */
	if (_unsetenv("NONEXISTENT_VAR") == -1)
	{
		printf("Tentative de suppression d'une variable inexistante : échec attendu\n");
	}

	return (0);
}
