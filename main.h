#ifndef MAIN_H
#define MAIN_H

/* Inclusion des bibliothèques nécessaires */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

extern char **environ;

/* Prototype de la fonction d'exécution de commande */
void execute_command(char *command, char *argv[]);
void exe_command(char *full_path, char **args);

/* Récupère la valeur de la variable PATH de l'environnement*/
char *_get_path(char **env);
char *cat(char *dest, const char *src1, char **src2);
char *_which(const char *filename);


int findpath(char **command, char **env);

void NewFunction(char full_path[1024]);

#endif
