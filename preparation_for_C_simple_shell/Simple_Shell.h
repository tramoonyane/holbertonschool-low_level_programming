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
#define PROMPT "#cisfun$ "

/* Reads a command from standard input */
char* read_command();

/* Main function of the shell */
int main();

#endif /* SIMPLE_SHELL_H */
