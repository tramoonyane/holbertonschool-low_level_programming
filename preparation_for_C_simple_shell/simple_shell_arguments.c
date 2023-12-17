#include "Simple_Shell.h"

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt() {
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

/**
 * parse_arguments - Parses the command string into arguments.
 *
 * @command: The input command to be parsed.
 *
 * Return: Returns an array of strings (arguments) parsed from the command.
 *         Returns NULL on failure or if no arguments are found.
 */
char** parse_arguments(const char *command) {
    char **args = (char **)malloc(BUFFER_SIZE * sizeof(char *));
    if (args == NULL) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    char *token;
    char *input_command = strdup(command); /* Create a copy of the input command */

    token = strtok(input_command, " ");
    while (token != NULL) {
        args[i] = strdup(token); /* Allocate memory for each argument */
        if (args[i] == NULL) {
            perror("malloc error");
            exit(EXIT_FAILURE);
        }
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL; /* NULL-terminate the arguments array */

    free(input_command); /* Free the copy of the input command */

    return args;
}

/**
 * read_command - Reads a command from standard input.
 *
 * Return: Returns the input command as a dynamically allocated string.
 */
char* read_command() {
    char *command;
    char input[BUFFER_SIZE];

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

    command = (char *)malloc(strlen(input) + 1);
    if (command == NULL) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    strcpy(command, input);
    return command;
}

/**
 * main - Main function of the shell.
 *
 * @argc: The number of arguments passed to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: Returns EXIT_SUCCESS upon successful execution.
 */
int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused))) {
    char *command;
    char **args;
    pid_t pid;

    do {
        display_prompt();

        command = read_command();

        if (feof(stdin)) {
            write(STDOUT_FILENO, "\n", 1);
            free(command);
            exit(EXIT_SUCCESS);
        }

        args = parse_arguments(command);

        pid = fork();

        if (pid == -1) {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                char error_buffer[BUFFER_SIZE];
                snprintf(error_buffer, BUFFER_SIZE, "%s: command not found\n", args[0]);
                write(STDERR_FILENO, error_buffer, strlen(error_buffer));
                exit(EXIT_FAILURE);
            }
        } else {
            int status;
            waitpid(pid, &status, 0);
        }

        free(args);
        free(command);
    } while (strcmp(command, "exit") != 0);

    write(STDOUT_FILENO, "Exiting...\n", strlen("Exiting...\n"));

    return EXIT_SUCCESS;
}
