#include "Simple_Shell.h"

/**
 * execute_command - Executes the command with arguments.
 *
 * @command: The command to execute.
 *
 * Return: Returns EXIT_SUCCESS upon successful execution.
 */
int execute_command(char *command)
{
    char **args = NULL;
    char *token;
    char *path;

    /* Check for empty command */
    if (command == NULL || *command == '\0')
        return EXIT_SUCCESS;

    /* Check if command exists in PATH */
    if (access(command, X_OK) == 0) {
        /* Execute command directly if it exists */
        if (execve(command, &command, NULL) == -1) {
            perror("execve error");
            exit(EXIT_FAILURE);
        }
    }

    /* Attempt to execute the command from PATH */
    path = getenv("PATH");
    token = strtok(path, ":");
    while (token != NULL) {
        char *full_path = malloc(strlen(token) + strlen(command) + 2);
        if (full_path == NULL) {
            perror("malloc error");
            exit(EXIT_FAILURE);
        }
        sprintf(full_path, "%s/%s", token, command);

        if (access(full_path, X_OK) == 0) {
            args = malloc(2 * sizeof(char *));
            if (args == NULL) {
                perror("malloc error");
                exit(EXIT_FAILURE);
            }
            args[0] = full_path;
            args[1] = NULL;

            if (execve(args[0], args, NULL) == -1) {
                perror("execve error");
                exit(EXIT_FAILURE);
            }
        }
        free(full_path);
        token = strtok(NULL, ":");
    }

    fprintf(stderr, "%s: command not found\n", command);
    return EXIT_FAILURE;
}

/**
 * read_command - Reads a command from standard input.
 *
 * Return: Returns the input command as a dynamically allocated string.
 */
char *read_command()
{
    char input[BUFFER_SIZE];

    printf("%s", PROMPT);

    if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
        if (feof(stdin)) {
            write(STDOUT_FILENO, "\n", 1);
            exit(EXIT_SUCCESS);
        } else {
            perror("fgets error");
            exit(EXIT_FAILURE);
        }
    }

    input[strcspn(input, "\n")] = '\0';

    return strdup(input);
}

/**
 * main - Main function of the shell.
 *
 * Return: Returns EXIT_SUCCESS upon successful execution.
 */
int main()
{
    char *command;

    do {
        command = read_command();

        if (feof(stdin)) {
            free(command);
            write(STDOUT_FILENO, "\n", 1);
            exit(EXIT_SUCCESS);
        }

        if (execute_command(command) == EXIT_FAILURE) {
            free(command);
            continue;
        }

        free(command);
    } while (1);

    return EXIT_SUCCESS;
}
