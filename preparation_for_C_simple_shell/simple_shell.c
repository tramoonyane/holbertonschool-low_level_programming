#include "simple_shell.h"
/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0 on success
 */
int main(void)
{
    char *buffer;
    size_t bufsize = BUFFER_SIZE;

    buffer = malloc(bufsize * sizeof(char));
    if (buffer == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        print_prompt();
        if (getline(&buffer, &bufsize, stdin) == -1)
        {
            printf("\n");
            break;
        }

        if (buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }

        char **arguments = tokenize_input(buffer);
        if (arguments != NULL)
        {
            execute_command(arguments);
            free(arguments);
        }
    }

    free(buffer);
    return 0;
}
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
    return tokens;
}
/**
 * execute_command - Execute a command with given arguments
 * @arguments: Array of pointers to tokens (arguments)
 *
 * Description: This function takes the parsed input command
 *              and executes it with the given arguments.
 */
void execute_command(char **arguments)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (execvp(arguments[0], arguments) == -1)
        {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
    }
}
/**
 * print_prompt - Display shell prompt
 *
 * Description: This function prints the shell prompt.
 */
void print_prompt(void)
{
    printf("$ ");
}
