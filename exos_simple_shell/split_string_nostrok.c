#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Fonction : split_string
 * -----------------------
 * Divise une chaîne en mots selon un ou plusieurs délimiteurs.
 *
 * Paramètres :
 *   str   : La chaîne à diviser
 *   delim : La chaîne contenant le ou les caractères délimiteurs
 *
 * Retourne :
 *   Un tableau de pointeurs vers des chaînes (char**), où chaque élément
 *   est un mot de la chaîne originale. Le dernier élément du tableau est NULL.
 */
char **split_string(char *str, const char *delim)
{
	char **result = NULL;  /* Tableau pour stocker les pointeurs vers les mots */
	int count = 0;         /* Nombre de mots trouvés */
	int in_word = 0;       /* Indicateur : actuellement dans un mot ou non */
	char *start = NULL;    /* Pointeur vers le début du mot courant */
	int len = strlen(str);         /* Longueur de la chaîne d'entrée */
	int delim_len = strlen(delim); /* Longueur de la chaîne de délimiteurs */

    /* Parcourir chaque caractère de la chaîne, y compris le caractère nul final */
	for (int i = 0; i <= len; i++)
	{
		int is_delim = 0;

		/* Vérifier si le caractère actuel est un délimiteur */
		for (int j = 0; j < delim_len; j++) {
			if (str[i] == delim[j] || str[i] == '\0') {
				is_delim = 1;
				break;
			}
        }

        if (!is_delim && !in_word){
            /* Début d'un nouveau mot */
            start = &str[i];
            in_word = 1;
        }
		else if (is_delim && in_word) {
            /* Fin d'un mot */
            int word_len = &str[i] - start;
            /* Allouer de l'espace pour le nouveau pointeur de mot */
            result = realloc(result, sizeof(char*) * (count + 1));
            /* Allouer de l'espace pour le mot lui-même */
            result[count] = malloc(word_len + 1);
            /* Copier le mot */
            strncpy(result[count], start, word_len);
            result[count][word_len] = '\0'; /* Ajouter le caractère nul final */
            count++;
            in_word = 0;
        }
    }

    /* Ajouter NULL à la fin du tableau pour marquer la fin */
    result = realloc(result, sizeof(char*) * (count + 1));
    result[count] = NULL;

    return result;
}

int main() {
    /* Chaîne de test */
    char str[] = "Hello,World,This,Is,A,Test";
    /* Appel de la fonction split_string */
    char **words = split_string(str, ",");

    /* Afficher chaque mot et libérer la mémoire */
    for (int i = 0; words[i] != NULL; i++) {
        printf("%s\n", words[i]);
        free(words[i]); /* Libérer la mémoire pour chaque mot */
    }
    free(words); /* Libérer le tableau de pointeurs */

    return 0;
}
