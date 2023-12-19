/* simple_shell.c */

#include "Simple_Shell.h"

/**
 * main - Entry point of the simple shell program
 * @argc: The number of arguments.
 * @argv: Array of arguments passed to the program.
 *
 * Return: Always 0 upon successful execution.
 *
 * Description: This function acts as the entry point
 * of the simple shell program.
 * It determines if the input is from a terminal
 * or not and executes accordingly.
 */
int main(int argc, char *argv[])
{
char *program_name = argv[0]; /* Set the program name from argv[0] */
(void)argc;
if (is_input_terminal())
{
execute_interactively(program_name);
}
else
{
execute_non_interactively(program_name);
}
return ((EXIT_SUCCESS));
}

/**
 * execute_interactively - Executes commands interactively from the terminal
 * @program_name: The name of the program.
 *
 * Description: This function handles the interactive mode of the shell.
 * It displays a prompt and waits for user input to execute commands.
 */
void execute_interactively(char *program_name)
{
char *input;

while (1)
{
printf("$ "); /* Display prompt only in interactive mode */
fflush(stdout);
input = get_user_input();
if (input == NULL)
{
printf("\n"); /* Print newline after Ctrl+D */
break;        /* Exit on EOF */
}
execute_command(tokenize_input(input), program_name);
}
}

/**
 * execute_non_interactively - Executes commands non-interactively
 * @program_name: The name of the program.
 *
 * Description: This function handles the non-interactive mode of the shell.
 * It reads input from pipes or redirected input to execute commands.
 */
void execute_non_interactively(char *program_name)
{
char *input_from_pipe = get_user_input();
if (input_from_pipe != NULL)
{
execute_command(tokenize_input(input_from_pipe), program_name);
}
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

/**
 * tokenize_input - Tokenizes the input string into individual tokens
 * @input: The input string to tokenize.
 *
 * Return: A pointer to an array of tokens (strings).
 *
 * Description: This function tokenizes the input string
 * based on space delimiter
 * and returns an array of tokens (strings) obtained from the input.
 */
char **tokenize_input(char *input)
{
int i = 0;
char *tokens[MAX_TOKENS];

tokens[i] = strtok(input, " "); /* Tokenize input */
while (tokens[i] != NULL && i < MAX_TOKENS - 1)
{
i++;
tokens[i] = strtok(NULL, " ");
}
tokens[i + 1] = NULL;
return (strdup(tokens));
}

/**
 * execute_command - Executes a command using execve
 * @tokens: An array of command tokens.
 * @program_name: The name of the program.
 *
 * Description: This function executes a command
 * using the execve system call
 * with the given tokens and program name.
 * It forks a child process to execute the command.
 */
void execute_command(char **tokens, char *program_name)
{
pid_t child_pid;
int status;

child_pid = fork();
if (child_pid < 0)
{
perror("Fork failed");
exit(EXIT_FAILURE);
}
else if (child_pid == 0)
{
if (execve(tokens[0], tokens, environ) == -1)
{
fprintf(stderr, "%s: ", program_name);
perror("Command execution failed");
exit(EXIT_FAILURE);
}
}
else
{
do {
waitpid(child_pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
}
