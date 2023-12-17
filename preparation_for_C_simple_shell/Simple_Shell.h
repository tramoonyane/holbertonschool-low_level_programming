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

void display_prompt(void);
char **parse_arguments(const char *command);
char *read_command(void);
int check_command_exists(const char *command);
void execute_command(char **args); /* Updated function prototype */
char *get_command_path(const char *command);
int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)));

#endif /* SIMPLE_SHELL_H */
