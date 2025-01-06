![image](img/shell.png)
<h1>Simple Shell</h1>

## Introduction

### What is Shell
A shell is a command-line interface that acts as an intermediary between the user and the operating system kernel. It interprets user commands, either interactively (typed directly into the terminal) or non-interactively (read from a script), and translates them into system calls that the operating system can understand and execute.

### Holberton School project
A lightweight UNIX command interpreter that executes commands from standard input. Built in C as part of the Holberton School curriculum, this shell implements core features like command execution with arguments, environment variable handling, and essential built-in commands.

### Tasks

*  README, man, AUTHORS.
*  Write a beautiful code that passes the Betty checks.
*  Write a UNIX command line interpreter.
*  Handle command lines with arguments.
*  Handle the PATH.
*  Implement the exit built-in, that exits the shell.
*  Implement the env built-in, that prints the current environment.

### Files

|File|Description|
|---|---|
|[AUTHORS](https://github.com/Pmichel74/holbertonschool-simple_shell/blob/main/AUTHORS)|Contributors in this repository|
|[README.md](https://github.com/Pmichel74holbertonschool-simple_shell/blob/README.md)|Information about our repository|
|[check_absolute_path.c](https://github.com/Pmichel74/holbertonschool-simple_shell/blob/master/check_absolute_path.c )|Execute builtins and commands|
|[custom_getline.c](https://github.com/Pmichel74/holbertonschool-simple_shell/blob/master/custom_getline.c)|Get variable PATH|
|[custom_realloc.c](https://github.com/Pmichel74//holbertonschool-simple_shell/blob/master/custom_realloc.c)|Prints enviroment to stndard output|
|[custom_strtok.c](https://github.com/Pmichel74/holbertonschool-simple_shell/blob/master/custom_strtok.c)|Gets input|
|[env_builtins.c](https://github.com/Pmichel74/holbertonschool-simple_shell/blob/master/env_builtins.c)|Main arguments functions||[hsh_string_foos.c](https://github.com/Pmichel74/holbertonschool-/blob/master/hsh_string_foos.c)|Function to work and modifie string|
|[execute_command.c](https://github.com/Pmichel74/holbertonschool-simple_shell/master/blob/master/execute_command.c)|Tokenizes a stirng|
|[find_command.c](https://github.com/Pmichel74/holbertonschool-simple_shell/blob/master/find_command.c)|Manual page our of Simple Shell|
|[find_path.c](https://github.com/Pmichel74/holbertonschool-simple_shell/blob/master/find_path.c)|Prototypes functions and headers|
|[fork_and_execute.c](https://github.com/Pmichel74/holbertonschool-simple_shell/blob/master/fork_and_execute.c)|Prototypes functions and headers|
|[free_string_array.c](https://github.com/Pmichel74/holbertonschool-simple_shell/blob/master/free_string_array.c)|Prototypes functions and headers|
|[main.c](https://github.com/Pmichel74/holbertonschool-simple_shell/blob/master/main.c)|Prototypes functions and headers|
|[print_env.c](https://github.com/Pmichel74/holbertonschool-simple_shell/blob/master/print_env.c)|Prototypes functions and headers|
|[search_in_path.c](https://github.com/Pmichel74/holbertonschool-simple_shell/blob/master/search_in_path.c)|Prototypes functions and headers|
|[sigint_handler.c](https://github.com/Pmichel74/holbertonschool-simple_shell/blob/master/sigint_handler.c)|Prototypes functions and headers|
|[string_to_int.c](https://github.com/Pmichel74/holbertonschool-simple_shell/blob/master/string_to_int.cll.h)|Prototypes functions and headers|





### General requirements
 * Allowed editors: vi, vim, emacs
 * All your files will be compiled on `Ubuntu 20.04 LTS`
 * Your C programs and functions will be compiled with `gcc` using the flags `-Wall` `-Werror` `-Wextra` and `-pedantic`
 * Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
 * No more than 5 functions per file
 * All your header files should be include guarded
 * This shell should not have any memory leaks
 * Unless specified otherwise, your program must have the exact same output as `sh` (`/bin/sh`) as well as the exact same error output.

### Allowed functions used

| System Calls | Library Functions | Process Functions |
|-------------|-------------------|-------------------|
| • `access` | • `fflush` | • `execve` |
| • `chdir` | • `free` | • `fork` |
| • `close` | • `getline` | • `getpid` |
| • `closedir` | • `malloc` | • `kill` |
| • `open` | • `perror` | • `wait` |
| • `opendir` | • `printf` | • `waitpid` |
| • `read` | • `fprintf` | • `wait3` |
| • `write` | • `sprintf` | • `wait4` |
| • `signal` | • `putchar` | • `_exit` |
| • `getcwd` | • `readdir` | • `exit` |
| • `isatty` | • `stat` | • `vfprintf` |
| • `lstat` | • `fstat` | • `strtok` |
| • `stat` | • `strcat` | • `strcmp` |
| • `strlen` | • `strcpy` | • `strncmp` |
| • `strncpy` | • `strstr` | • `strncat` |


