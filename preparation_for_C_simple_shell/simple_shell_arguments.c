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
char **parse_arguments(const char *command) {
    int i;
    char *token;
    char *input_command;
    char **args = (char **)malloc(BUFFER_SIZE * sizeof(char *));
    if (args == NULL) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    i = 0;
    input_command = strdup(command); /* Create a copy of the input command */

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
char *read_command() {
    char *command = NULL;
    size_t bufsize = 0;

    if (getline(&command, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            write(STDOUT_FILENO, "\n", 1);
            exit(EXIT_SUCCESS);
        } else {
            perror("getline error");
            exit(EXIT_FAILURE);
        }
    }

    if (feof(stdin)) {
        write(STDOUT_FILENO, "\n", 1);
        free(command);
        exit(EXIT_SUCCESS);
    }

    /* Remove newline character from the command */
    command[strcspn(command, "\n")] = '\0';

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
    size_t bufsize = BUFFER_SIZE;
    pid_t pid;

    if (isatty(STDIN_FILENO)) { /* Check if in interactive mode */
        do {
            display_prompt();
            command = read_command();

            args = parse_arguments(command);

            pid = fork();

            if (pid == -1) {
                perror("fork error");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                execute_command(args); // Replaced execvp with execute_command
            } else {
                int status;
                waitpid(pid, &status, 0);
            }

            free(args);
            free(command);
        } while (strcmp(command, "exit") != 0);
    } else { /* Non-interactive mode */
        command = (char *)malloc(bufsize * sizeof(char));
        if (command == NULL) {
            perror("malloc error");
            exit(EXIT_FAILURE);
        }

        while (getline(&command, &bufsize, stdin) != -1) {
            command[strcspn(command, "\n")] = '\0'; /* Remove newline character */
            args = parse_arguments(command);

            pid = fork();

            if (pid == -1) {
                perror("fork error");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                execute_command(args); /* Replaced execvp with execute_command */
            } else {
                int status;
                waitpid(pid, &status, 0);
            }

            free(args);
        }

        free(command);
        exit(EXIT_SUCCESS);
    }

    write(STDOUT_FILENO, "Exiting...\n", strlen("Exiting...\n"));

    return EXIT_SUCCESS;
}
