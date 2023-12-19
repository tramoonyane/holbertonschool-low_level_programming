/* Simple_Shell.h */

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

char **parse_path();
int execute_command(char *command, int command_number, char *program_name);
char* read_command();
int handle_builtin_commands(char *command);
void exit_shell();


#endif /* SHELL_H */
