#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_ARGS 64


int main(int argc, char *argv[], char *envp[]);

char *read_command(void);
int fork_and_execute(char *command_path, char **args, char **envp);
int execute_command(char **args, char **envp, char *program_name);

char **tokenize_command(char *command);
void free_tokens(char **tokens);

char *find_path(char *envp[]);
char *check_absolute_path(char *command);
char *search_in_path(char *command, char *path);
char *find_command(char *command, char *envp[]);

void free_args(char **args);
int lsh_exit(char **args);
int handle_exit(char **args);


void print_env(char *envp[]);

#endif
