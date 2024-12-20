![image](img/shell.png)
<h1>Simple Shell</h1>

## Introduction

### What is Shell
A shell is a command-line interface that acts as an intermediary between the user and the operating system kernel. It interprets user commands, either interactively (typed directly into the terminal) or non-interactively (read from a script), and translates them into system calls that the operating system can understand and execute.

### What is it for
A lightweight UNIX command interpreter that executes commands from standard input. Built in C as part of the Holberton School curriculum, this shell implements core features like command execution with arguments, environment variable handling, and essential built-in commands.

### Tasks

*  README, man, AUTHORS.
*  Write a beautiful code that passes the Betty checks.
*  Write a UNIX command line interpreter.
*  Handle command lines with arguments.
*  Handle the PATH. 
*  Implement the exit built-in, that exits the shell.
*  Implement the env built-in, that prints the current environment.

### General requirements
 * Allowed editors: vi, vim, emacs
 * All your files will be compiled on `Ubuntu 14.04 LTS`
 * Your C programs and functions will be compiled with `gcc 4.8.4` using the flags `-Wall` `-Werror` `-Wextra` and `-pedantic`
 * Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
 * No more than 5 functions per file
 * All your header files should be include guarded
 * This shell should not have any memory leaks
 * Unless specified otherwise, your program must have the exact same output as `sh` (`/bin/sh`) as well as the exact same error output.

### Allowed functions used 

| System Calls | Library Functions | Process Functions |
|-------------|-------------------|-------------------|
| • access | • fflush | • execve |
| • chdir | • free | • fork |
| • close | • getline | • getpid |
| • closedir | • malloc | • kill |
| • open | • perror | • wait |
| • opendir | • printf | • waitpid |
| • read | • fprintf | • wait3 |
| • write | • sprintf | • wait4 |
| • signal | • putchar | • _exit |
| • getcwd | • readdir | • exit |
| • isatty | • stat | • vfprintf |
| • lstat | • fstat | • strtok |
| • stat | • strcat | • strcmp |
| • strlen | • strcpy | • strncmp |
| • strncpy | • strstr | • strncat |
