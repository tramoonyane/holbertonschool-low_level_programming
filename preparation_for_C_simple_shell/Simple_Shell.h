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
#define BUFFER_SIZE 1024
#define PROMPT ":) "

extern char **environ;  /* Access to the environment variables */

/* Function to check if input is coming from a terminal */
int isatty(int fd);

/* Function to check if input is coming from a terminal */
int is_input_terminal();

/* Function prototypes for additional functions */
void execute_interactively(char *program_name);
void execute_non_interactively(char *program_name);
char *get_user_input();
char **tokenize_input(char *input);
int execute_command(char *command, int command_number, char *program_name);
void execute_command(char **tokens, char *program_name);
char **parse_arguments(char *input);
void execute_with_arguments(char **tokens, char *program_name);
char **parse_path();
char *read_command();
int handle_builtin_commands(char *command);

#endif /* SIMPLE_SHELL_H */
