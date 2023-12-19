/* Simple_Shell.h */

#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

extern char **environ; /* Declaration of environ variable */

void execute_command(char *command);

#endif /* SIMPLE_SHELL_H */
