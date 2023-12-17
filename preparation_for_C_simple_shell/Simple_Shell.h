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
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void display_prompt(void);
char *read_command(void);
char **parse_arguments(const char *command);
void execute_command(char **args);

#endif /* SIMPLE_SHELL_H */
