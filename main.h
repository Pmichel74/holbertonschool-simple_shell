#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
<<<<<<< HEAD
#include <errno.h>
=======
>>>>>>> 611470c (add main.h)
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_ARGS 64

int main(int argc, char *argv[], char *envp[]);

char *read_command(void);
<<<<<<< HEAD
int fork_and_execute(char *command_path, char **args, char **envp);
int execute_command(char **args, char **envp, char *program_name);
int execute_command_main(char **args, char **envp, char *program_name);
=======
void fork_and_execute(char *command_path, char **args, char **envp);
void execute_command(char **args, char **envp);
>>>>>>> 611470c (add main.h)

char **tokenize_command(char *command);
void free_tokens(char **tokens);

char *find_path(char *envp[]);
char *check_absolute_path(char *command);
char *search_in_path(char *command, char *path);
char *find_command(char *command, char *envp[]);

void free_args(char **args);
<<<<<<< HEAD
int lsh_exit(char **args);
=======
>>>>>>> 611470c (add main.h)

void print_env(char *envp[]);

#endif
