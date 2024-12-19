#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

extern char **environ;

int main(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters;
    pid_t pid;
    int status;

    while (1)
    {
        printf("#this_is_a_shell_$ ");
        characters = getline(&buffer, &bufsize, stdin);

        if (characters == -1)
        {
            printf("\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) == 0)
            continue;

        pid = fork();

        if (pid == -1)
        {
            perror("Error:");
            exit(1);
        }
        else if (pid == 0)
        {
            char *argv[2];
            argv[0] = buffer;
            argv[1] = NULL;
            if (execve(buffer, argv, environ) == -1)
            {
                printf("./shell: No such file or directory\n");
                exit(1);
            }
        }
        else
        {
            wait(&status);
        }
    }

    free(buffer);
    return 0;
}