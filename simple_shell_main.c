#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

// Function to read a command from the user
char *read_command(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters;

    printf("#this_is_a_shell_$ ");
    characters = getline(&buffer, &bufsize, stdin);

    if (characters == -1)
    {
        free(buffer);
        return NULL; // Return NULL on EOF
    }

    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
    return buffer; // Return the command
}

// Function to execute a command
void execute_command(char *command)
{
    pid_t pid = fork();
    int status;

    if (pid == -1)
    {
        perror("Error:");
        exit(1);
    }
    else if (pid == 0) // Child process
    {
        char *argv[2];
        argv[0] = command; // Command to execute
        argv[1] = NULL; // Null-terminate the array

        if (execve(command, argv, environ) == -1)
        {
            printf("./shell: No such file or directory\n");
            exit(1);
        }
    }
    else // Parent process
    {
        wait(&status); // Wait for child process to finish
    }
}

int main(void)
{
    char *command;

    while (1)
    {
        command = read_command(); // Read user command

        if (command == NULL) // Check for EOF
        {
            printf("\n");
            break;
        }

        if (strlen(command) == 0) // Ignore empty commands
        {
            free(command);
            continue;
        }

        execute_command(command); // Execute the command
        free(command); // Free the allocated memory for the command
    }

    return 0;
}
