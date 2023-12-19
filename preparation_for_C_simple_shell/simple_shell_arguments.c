/* simple_shell_arguments.c */

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
    (void)argc;
    if (is_input_terminal())
    {
        execute_interactively(argv[0]);
    }
    else
    {
        execute_non_interactively(argv[0]);
    }
    return EXIT_SUCCESS;
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
 * execute_command - Executes a command using execve
 * @tokens: An array of command tokens.
 * @program_name: The name of the program.
 *
 * Description: This function executes a command
 * using the execve system call
 * with the given tokens and program name.
 * It forks a child process to execute the command.
 * It also handles command execution when PATH is present.
 */
void execute_command(char **tokens) {
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        if (execvp(tokens[0], tokens) == -1) {
            char *path = getenv("PATH");
            if (path != NULL) {
                char *token;
                token = strtok(path, ":");
                while (token != NULL) {
                    char *executable = malloc(strlen(token) + strlen(tokens[0]) + 2);
                    if (executable == NULL) {
                        perror("Memory allocation failed");
                        exit(EXIT_FAILURE);
                    }
                    strcpy(executable, token);
                    strcat(executable, "/");
                    strcat(executable, tokens[0]);
                    if (access(executable, X_OK) == 0) {
                        free(tokens[0]);
                        tokens[0] = executable;
                        if (execve(executable, tokens, environ) == -1) {
                            perror("Command execution failed");
                            exit(EXIT_FAILURE);
                        }
                    }
                    free(executable);
                    token = strtok(NULL, ":");
                }
            }
            fprintf(stderr, "%s: command not found\n", tokens[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        do {
            waitpid(child_pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}
