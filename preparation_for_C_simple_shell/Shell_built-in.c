/* Shell_built-in.c */

#include "Shell.h"

/**
 * print_environment - Prints the current environment variables.
 */
void print_environment(void)
{
/* extern char **environ; */
int i = 0;
while (environ[i] != NULL)
{
printf("%s\n", environ[i]);
i++;
}
}

/**
 * handle_builtin_commands - Handles built-in commands like 'exit' and 'env'.
 *
 * @command: The command to execute.
 *
 * Return: Returns 1 if a built-in command is executed, otherwise 0.
 */
int handle_builtin_commands(char *command)
{
if (strcmp(command, "exit") == 0)
{
exit_shell(); /* Call the exit_shell function */
return (1);     /* Return 1 to indicate the command was handled */
}
else if (strcmp(command, "env") == 0)
{
print_environment(); /* Print the environment variables */
return (1);            /* Return 1 to indicate the command was handled */
}
return (0); /* Return 0 for other commands */
}


/**
 * exit_shell - Exits the shell.
 */
void exit_shell(void)
{
exit(EXIT_SUCCESS);
}
