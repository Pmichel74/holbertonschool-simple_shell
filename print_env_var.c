#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av, char **environ)
{
	/* Accès aux arguments*/
	for (int i = 0; i < ac; i++)
	{
		printf("Argument %d : %s\n", i, av[i]);
	}

	/*Accès aux variables d'environnement*/
	for (int i = 0; env[i] != NULL; i++)
	{
		printf("Variable d'environnement : %s\n", environ[i]);
	}

	return (0);
}
