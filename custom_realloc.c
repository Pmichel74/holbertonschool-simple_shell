#include "main.h"

/**
 * _realloc - Réallocation de mémoire personnalisée
 * @ptr: Pointeur vers le bloc de mémoire existant
 * @old_size: Taille actuelle du bloc en octets
 * @new_size: Nouvelle taille désirée en octets
 *
 * Return: Pointeur vers le nouveau bloc de mémoire, ou NULL en cas d'erreur
 *
 * Cette fonction émule le comportement de realloc:
 * - Si ptr est NULL, équivalent à malloc(new_size)
 * - Si new_size est 0 et ptr non NULL, équivalent à free(ptr)
 * - Si new_size == old_size, retourne ptr sans changement
 * - Sinon, crée un nouveau bloc et copie les données
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;    /* Nouveau bloc de mémoire */
	char *temp_ptr;   /* Pour manipulation byte par byte */
	unsigned int i;   /* Compteur pour la copie */

	/* Si les tailles sont identiques, pas besoin de réallocation */
	if (new_size == old_size)
		return (ptr);

	/* Si new_size est 0 et ptr existe, équivalent à free */
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	/* Si ptr est NULL, équivalent à malloc */
	if (ptr == NULL)
	{
		new_ptr = malloc(new_size);
		if (new_ptr == NULL)
			return (NULL);
		return (new_ptr);
	}

	/* Allouer le nouveau bloc de mémoire */
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	/* Préparer les pointeurs pour la copie */
	temp_ptr = ptr;

	/* Copier les données de l'ancien bloc vers le nouveau */
	/* On copie le minimum entre old_size et new_size */
	for (i = 0; i < old_size && i < new_size; i++)
		new_ptr[i] = temp_ptr[i];

	/* Libérer l'ancien bloc */
	free(ptr);

	return (new_ptr);
}
