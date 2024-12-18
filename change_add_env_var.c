#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * _setenv - Change or add an environment variable
 * @name: Name of the environment variable
 * @value: Value to set for the environment variable
 * @overwrite: Flag to determine if existing variable should be overwritten
 *
 * Return: 0 on success, -1 on error
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	/* Vérification des paramètres */
	if (name == NULL || *name == '\0' || strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	/* Appel à la fonction setenv standard */
	return (setenv(name, value, overwrite));
}

/**
 * main - Fonction de test pour _setenv
 *
 * Return: Toujours 0
 */
int main(void)
{
	/* Test de _setenv */
	printf("Avant: TEST=%s\n", getenv("TEST"));

	if (_setenv("TEST", "123", 1) == 0)
		printf("Après: TEST=%s\n", getenv("TEST"));
	else
		printf("Erreur lors de la définition de TEST\n");

	/* Test avec overwrite à 0 */
	if (_setenv("TEST", "456", 0) == 0)
		printf("Après (sans écrasement): TEST=%s\n", getenv("TEST"));
	else
		printf("Erreur lors de la tentative de redéfinition de TEST\n");

	/* Test avec une nouvelle variable */
	if (_setenv("NOUVELLE_VAR", "nouvelle_valeur", 1) == 0)
		printf("Nouvelle variable: NOUVELLE_VAR=%s\n", getenv("NOUVELLE_VAR"));
	else
		printf("Erreur lors de la définition de NOUVELLE_VAR\n");

	return (0);
}
