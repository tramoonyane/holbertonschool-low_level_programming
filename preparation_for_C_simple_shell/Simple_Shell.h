/* Simple_Shell.h */

#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define PROMPT "$ "

/* Reads a command from standard input */
char *read_command();

/* Executes the command with arguments */
int execute_command(char *command);

/* Tokenizes the PATH environment variable */
char **parse_path();

/* Handles built-in commands like 'exit' */
int handle_builtin_commands(char *command);

/* Main function of the shell */
int main();

#endif /* SIMPLE_SHELL_H */
