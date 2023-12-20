/* simple_shell_arguments.c */

#include "Shell.h"

/**
 * count_arguments - Counts the number of arguments in a command.
 *
 * @command: The command to analyze.
 *
 * Return: Returns the number of arguments.
 */
int count_arguments(char *command)
{
int arg_count = 1; /* Initial count for command itself */
char *p;

for (p = command; *p != '\0'; ++p)
{
if (*p == ' ')
{
arg_count++;
while (*p == ' ') /* Skip consecutive spaces */
p++;
}
}
return (arg_count);
}

/**
 * get_command_arguments - Splits the command into arguments.
 *
 * @command: The command to split.
 * @arg_count: Number of arguments in the command.
 *
 * Return: Returns an array of command arguments.
 */
char **get_command_arguments(char *command, int arg_count)
{
char **args;
int i = 0;

args = malloc((arg_count + 1) * sizeof(char *));
if (args == NULL)
{
perror("malloc error");
exit(EXIT_FAILURE);
}
args[i++] = strtok(command, " \n"); /* Get the command */
while
((args[i++] = strtok(NULL, " \n")) != NULL);
return (args);
}
