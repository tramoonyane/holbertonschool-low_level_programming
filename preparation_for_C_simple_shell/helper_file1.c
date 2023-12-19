/* helper_file1.c */

#include "Simple_Shell.h"

/**
 * is_input_terminal - Checks if input is coming from a terminal
 *
 * Return: 1 if input is from a terminal, 0 otherwise
 */
int is_input_terminal(void)
{
return (isatty(fileno((stdin))));
}

/**
 * get_user_input - Retrieves user input from stdin
 *
 * Return: A pointer to the user input string.
 *
 * Description: This function reads user input
 * from standard input (stdin)
 * and returns the input as a string,
 * removing the newline character if present.
 */
char *get_user_input()
{
char input[MAX_INPUT_LENGTH];
if (fgets(input, sizeof(input), stdin) != NULL)
{
input[strcspn(input, "\n")] = '\0'; /* Remove newline character */
return (strdup(input));
}
return (NULL);
}

