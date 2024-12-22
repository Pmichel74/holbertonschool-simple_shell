#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_error(char *prog_name, char *cmd);
int main(int argc, char *argv[], char *envp[]);

#endif /* MAIN_H */
