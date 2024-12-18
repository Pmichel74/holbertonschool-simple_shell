#include <string.h>
#include <stdlib.h>

/*
 * Fonction : split_string
 * ----------------------
 * Divise une chaîne de caractères en mots selon un délimiteur donné.
 *
 * Paramètres :
 *   str   : La chaîne à diviser. Attention, cette chaîne sera modifiée.
 *   delim : La chaîne contenant le ou les caractères délimiteurs.
 *
 * Retourne :
 *   Un tableau de pointeurs vers des chaînes (char**), où chaque élément
 *   est un mot de la chaîne originale. Le dernier élément du tableau est NULL.
 *
 * Note :
 *   - La mémoire est allouée dynamiquement pour le tableau de retour et pour
 *     chaque mot. L'appelant est responsable de libérer cette mémoire.
 *   - La fonction utilise strtok(), qui n'est pas thread-safe.
 *   - La chaîne d'entrée est modifiée par strtok().
 */
char **split_string(char *str, const char *delim)
{
	char **result = NULL;  /* Tableau de chaînes pour stocker les mots */
	char *token;           /* Pour stocker chaque mot extrait */
	int count = 0;         /* Compteur de mots */

    /* Obtenir le premier mot */
	token = strtok(str, delim);

    /* Parcourir tous les autres mots */
	while (token != NULL)
	{
		/* Réallouer de la mémoire pour ajouter un nouveau mot */
		result = realloc(result, sizeof(char*) * (count + 1));
		/* Copier le mot dans le tableau */
		result[count] = strdup(token);
		count++;
		/* Obtenir le mot suivant */
		token = strtok(NULL, delim);
    }

    /* Ajouter un terminateur NULL à la fin du tableau */
	result = realloc(result, sizeof(char*) * (count + 1));
	result[count] = NULL;

	return (result);
}
