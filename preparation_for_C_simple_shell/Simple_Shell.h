/* Simple_Shell.h */

#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_TOKENS 100

extern char **environ;  /* Access to the environment variables */

/* Function to check if input is coming from a terminal */
int is_input_terminal();

#endif /* SIMPLE_SHELL_H */
