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

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void);

/**
 * parse_arguments - Parses the command string into arguments.
 *
 * @command: The input command to be parsed.
 *
 * Return: Returns an array of strings (arguments) parsed from the command.
 *         Returns NULL on failure or if no arguments are found.
 */
char **parse_arguments(const char *command);

/**
 * read_command - Reads a command from standard input.
 *
 * Return: Returns the input command as a dynamically allocated string.
 */
char *read_command(void);

/**
 * check_command_exists - Checks if a command exists in the PATH.
 *
 * @command: The command to check for existence.
 *
 * Return: Returns 1 if the command exists in the PATH, 0 otherwise.
 */
int check_command_exists(const char *command);

/**
 * execute_command - Executes the command if it exists in the PATH.
 *
 * @args: The array of command and arguments.
 */
void execute_command(char **args);

/**
 * get_command_path - Retrieves the full path of a command from PATH.
 *
 * @command: The command to search for in PATH.
 *
 * Return: Returns the full path of the command if found in PATH, NULL otherwise.
 */
char *get_command_path(const char *command);

/**
 * main - Main function of the shell.
 *
 * @argc: The number of arguments passed to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: Returns EXIT_SUCCESS upon successful execution.
 */
int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)));

#endif /* SIMPLE_SHELL_H */
