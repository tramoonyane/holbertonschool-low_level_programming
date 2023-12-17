#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define PROMPT "$ "

void display_prompt(void);
char *read_command(void);
char **tokenize_command(char *command);
void execute_command(char **args);
void execute_command(const char *program_name, char **args);

#endif /* SIMPLE_SHELL_H */
