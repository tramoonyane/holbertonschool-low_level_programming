/* simple_shell.c */

#include "Simple_Shell.h"
extern char **environ;

/**
 * execute_command - Executes the command.
 *
 * @command: The command to execute.
 * @command_number: The number of the command.
 * @program_name: The name of the program.
 *
 * Return: Returns EXIT_SUCCESS upon successful execution.
 */
int execute_command(char *command, int command_number, char *program_name) {
    pid_t pid;
    int status;
    char *args[] = { command, NULL };

    pid = fork();

    if (pid == -1) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /* Child process */
        if (execve(command, args, environ) == -1) {
            fprintf(stderr, "%s: %d: %s: not found\n", program_name, command_number, command);
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
char *read_command() {
    char *command = NULL;
    size_t bufsize = 0;
    ssize_t characters;

    printf("%s", PROMPT);
    fflush(stdout);

    characters = getline(&command, &bufsize, stdin);
    if (characters == -1) {
        if (feof(stdin)) {
            free(command);
            exit(EXIT_SUCCESS);
        } else {
            perror("getline error");
            exit(EXIT_FAILURE);
        }
    }

    command[strcspn(command, "\n")] = '\0'; /* Remove newline character */
    return command;
}

/**
 * main - Main function of the shell.
 *
 * Return: Returns EXIT_SUCCESS upon successful execution.
 */
int main(void) {
    char *command;

    /* Interactive mode */
    do {
        command = read_command();

        if (execute_command(command, 1, "hsh") == EXIT_FAILURE) {
            free(command);
            continue;
        }

        free(command);
    } while (1);

    return EXIT_SUCCESS;
}
