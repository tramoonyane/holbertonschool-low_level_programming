#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define TOKEN_DELIM " \t\n"
#define MAX_ARGUMENTS 64

/* Function prototypes */
char **tokenize_input(char *input);
void execute_command(char **arguments);
void print_prompt(void);
void print_environment();

#endif /* SIMPLE_SHELL_H */
