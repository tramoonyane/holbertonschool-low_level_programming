/* simple_shell.c */

#include "Simple_Shell.h"

/**
 * handle_builtin_commands - Handles built-in commands like 'exit' and 'env'.
 *
 * @command: The command to execute.
 *
 * Return: Returns 1 if a built-in command is executed, otherwise 0.
 */
int handle_builtin_commands(char *command) {
    if (strcmp(command, "exit") == 0) {
        exit(EXIT_SUCCESS); /* Exit the shell */
        return 1;            /* Return 1 to indicate the command was handled */
    } else if (strcmp(command, "env") == 0) {
        extern char **environ;
        int i = 0;
        while (environ[i] != NULL) {
            printf("%s\n", environ[i]);
            i++;
        }
        return 1; /* Return 1 to indicate the command was handled */
    }
    return 0; /* Return 0 for other commands */
}

/**
 * execute_command - Executes the command with arguments.
 *
 * @command: The command to execute.
 *
 * Return: Returns EXIT_SUCCESS upon successful execution.
 */
int execute_command(char *command) {
    pid_t pid;
    int status;

    if (command == NULL || *command == '\0') {
        return EXIT_SUCCESS; /* Skip execution for empty commands */
    }

    pid = fork();
    if (pid == -1) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /* Child process */
        if (execlp(command, command, NULL) == -1) {
            fprintf(stderr, "%s: command not found\n", command);
            exit(EXIT_FAILURE);
        }
    } else {
        /* Parent process */
        waitpid(pid, &status, 0);
    }

    return EXIT_SUCCESS;
}

/**
 * read_command - Reads a command from standard input.
 *
 * Return: Returns the input command as a dynamically allocated string.
 */
char* read_command() {
    char* command;
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

    command = strdup(input);
    if (command == NULL) {
        perror("strdup error");
        exit(EXIT_FAILURE);
    }

    return command;
}

/**
 * main - Main function of the shell.
 *
 * Return: Returns EXIT_SUCCESS upon successful execution.
 */
int main() {
    char *command;
    
    /* Interactive mode */    
    do {
        command = read_command();

        if (feof(stdin)) {
            free(command);
            write(STDOUT_FILENO, "\n", 1);
            exit(EXIT_SUCCESS);
        }

        if (!handle_builtin_commands(command)) {
            /* If not a built-in command, execute the command */
            if (execute_command(command) == EXIT_FAILURE) {
                free(command);
                continue;
            }
        }

        free(command);
    } while (1);

    return EXIT_SUCCESS;
}
