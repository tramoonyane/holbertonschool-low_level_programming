/* Shell.h */

#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define PROMPT "$ " /* You can change the prompt as needed */
extern char **environ;

char **parse_path();
int execute_command(char *command, int command_number, char *program_name);
char *read_command();
int handle_builtin_commands(char *command);
void exit_shell();

void interactive_mode(char *program_name);
void non_interactive_mode(char *program_name);
void process_command(char *command, int *command_number, char *program_name);

int count_arguments(char *command);
char **get_command_arguments(char *command, int arg_count);
void execute_command_with_path(char **args, int command_number, char *program_name);

#endif /* SHELL_H */
