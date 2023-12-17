#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024
#define PROMPT "$ "

void display_prompt();
char** parse_arguments(const char *command);
char* read_command();
int is_exit_command(const char *command);

#endif /* SIMPLE_SHELL_H */
