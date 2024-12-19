#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structure for each node in the linked list
 * Contains a directory string and a pointer to the next node
 */
typedef struct path_node
{
	char *directory;
	struct path_node *next;
} path_node_t;

/* Function to create a new node
 * Allocates memory for the node and copies the directory string
 * Returns NULL if memory allocation fails
 */
path_node_t *create_node(char *dir)
{
	path_node_t *new_node = malloc(sizeof(path_node_t));
	if (!new_node)
	return (NULL);

	/* Copie le nom du répertoire */
	new_node->directory = strdup(dir);
	if (!new_node->directory)
	{
		free(new_node);
		return (NULL);
	}

	new_node->next = NULL;
	return (new_node);
}

/* Main function to build the linked list of PATH directories
 * Retrieves PATH, tokenizes it, and creates a node for each directory
 * Returns the head of the list, or NULL if an error occurs
 */
path_node_t *build_path_list(void)
{
	/* Récupère la variable d'environnement PATH */
	char *path = getenv("PATH");

	if (!path)
	return (NULL);

	path_node_t *head = NULL, *current = NULL;
	/* Découpe la chaîne PATH en utilisant ':' comme séparateur */
	char *token = strtok(path, ":");

	while (token)
	{
		/* Crée un nouveau nœud pour chaque répertoire */
		path_node_t *new_node = create_node(token);

		if (!new_node)
		{
			/* Gestion d'erreur : libérer la liste et retourner NULL */
			/* (code de nettoyage omis pour brièveté) */
			return (NULL);
		}

		/* Ajoute le nouveau nœud à la liste */
		if (!head)
		{
			head = new_node;
			current = head;
		}
		else
		{
			current->next = new_node;
			current = new_node;
		}

		token = strtok(NULL, ":");
	}

	return (head);
}

/* Function to free the memory allocated for the linked list */
void free_path_list(path_node_t *head)
{
	path_node_t *current = head;
	while (current) {
		path_node_t *temp = current;
		current = current->next;
		/* Libère la mémoire pour le nom du répertoire et le nœud */
		free(temp->directory);
		free(temp);
	}
}

/* Function to print the linked list (for testing purposes) */
void print_path_list(path_node_t *head)
{
	path_node_t *current = head;
	while (current) {
		/* Affiche chaque répertoire */
		printf("%s\n", current->directory);
		current = current->next;
	}
}

int main(void)
{
	path_node_t *path_list = build_path_list();
	if (path_list) {
		/* Affiche et libère la liste si elle a été créée avec succès */
		print_path_list(path_list);
		free_path_list(path_list);
	} else {
		printf("Impossible de construire la liste du PATH\n");
	}
	return 0;
}
