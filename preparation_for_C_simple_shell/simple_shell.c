#include "Simple_Shell.h"
/**
 * tokenize_input - Tokenize user input
 * @input: User input string
 *
 * Return: Array of pointers to tokens (arguments)
 */
char **tokenize_input(char *input)
{
    int bufsize = MAX_ARGUMENTS;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, TOKEN_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += MAX_ARGUMENTS;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIM);
    }
    tokens[position] = NULL;
    return (tokens);
}
/**
 * execute_command - Execute a command with given arguments
 * @arguments: Array of pointers to tokens (arguments)
 *
 * Description: This function takes the parsed input command
 *              and executes it with the given arguments.
 */
void execute_command(char **arguments) {
    pid_t pid;
    int status;

    if (strcmp(arguments[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execvp(arguments[0], arguments) == -1) {
            fprintf(stderr, "./hsh: 1: %s: not found\n", arguments[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            status = WEXITSTATUS(status);
            exit(status);
        } else {
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * print_prompt - Display shell prompt
 *
 * Description: This function prints the shell prompt.
 */
void print_prompt(int status) {
    if (status == 0) {
        printf("($)");
    } else {
        printf("($?)");
    }
    fflush(stdout);
}
