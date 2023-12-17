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
    char *path;
    char *program_name;
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
if (strchr(args[0], '/') != NULL) {
    path = strdup(args[0]);
    program_name = strrchr(path, '/') + 1;
    args[0] = program_name;
    free(path);
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
 * check_command_exists - Checks if a command exists in the PATH.
 *
 * @command: The command to check for existence.
 *
 * Return: Returns 1 if the command exists in the PATH, 0 otherwise.
 */
int check_command_exists(const char *command) {
    char *path = getenv("PATH");
    char *path_copy;
    char *token;
    if (path == NULL) {
        fprintf(stderr, "Unable to get PATH\n");
        exit(EXIT_FAILURE);
    }

    path_copy = strdup(path);
    token = strtok(path_copy, ":");

    while (token != NULL) {
        char *full_path = (char *)malloc(strlen(token) + strlen(command) + 2);
        if (full_path == NULL) {
            perror("malloc error");
            exit(EXIT_FAILURE);
        }
        sprintf(full_path, "%s/%s", token, command);

        if (access(full_path, X_OK) == 0) {
            free(path_copy);
            free(full_path);
            return 1; /* Command exists in the PATH */
        }

        free(full_path);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return 0; /* Command not found in the PATH */
}

/**
 * execute_command - Executes the command if it exists in the PATH.
 *
 * @args: The array of command and arguments.
 */
void execute_command(char **args) {
    if (check_command_exists(args[0])) {
        char *path = NULL;
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Child process */
            path = getenv("PATH");
            printf("PATH: %s\n", path);
            printf("Executing: %s\n", args[0]);
            if (execvp(args[0], args) == -1) {
                perror("execvp error");
                exit(EXIT_FAILURE);
            }
        } else {
            /* Parent process */
            int status;
            waitpid(pid, &status, 0);
        }
        free(path); /* Free allocated memory if used */
    } else {
        fprintf(stderr, "%s: command not found\n", args[0]);
    }
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

    if (isatty(STDIN_FILENO)) { /* Check if in interactive mode */
        do {
            display_prompt();
            command = read_command();

            args = parse_arguments(command);

            execute_command(args);

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

            execute_command(args);

            free(args);
        }

        free(command);
        exit(EXIT_SUCCESS);
    }

    write(STDOUT_FILENO, "Exiting...\n", strlen("Exiting...\n"));

    return EXIT_SUCCESS;
}
