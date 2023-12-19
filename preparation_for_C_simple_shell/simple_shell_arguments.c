#include "Simple_Shell.h"

/**
 * parse_arguments - Parses command line arguments.
 * @input: The input string containing command and arguments.
 *
 * Return: A pointer to an array of tokens (strings).
 *
 * Description: This function tokenizes the input string
 * based on space delimiter and returns an array of tokens
 * obtained from the input (command and arguments).
 */
char **parse_arguments(char *input)
{
int i = 0;
char **tokens = malloc(MAX_TOKENS * sizeof(char *));
if (tokens == NULL)
{
perror("Memory allocation failed");
exit(EXIT_FAILURE);
}
tokens[i] = strtok(input, " "); /* Tokenize input */
while (tokens[i] != NULL && i < MAX_TOKENS - 1)
{
i++;
tokens[i] = strtok(NULL, " ");
}
tokens[i + 1] = NULL;
return (tokens);
}

/**
 * execute_with_arguments - Executes a command with arguments using execve.
 * @tokens: An array of command tokens (command and arguments).
 * @program_name: The name of the program.
 *
 * Description: This function executes a command with arguments
 * using the execve system call with the given tokens and program name.
 * It forks a child process to execute the command.
 */
void execute_with_arguments(char **tokens, char *program_name)
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
