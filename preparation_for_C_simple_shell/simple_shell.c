#include "Simple_Shell.h"

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt() {
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
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
    pid_t pid;
    int status;

    do {
        display_prompt();

        command = read_command();

        if (feof(stdin)) {
            write(STDOUT_FILENO, "\n", 1);
            free(command);
            exit(EXIT_SUCCESS);
        }

        pid = fork();

        if (pid == -1) {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Check if the command is a path */
            if (access(command, X_OK) == 0) {
                if (execv(command, (char *[]){command, NULL}) == -1) {
                    perror("execv error");
                    exit(EXIT_FAILURE);
                }
            } else {
                /* Attempt to execute command from PATH */
                if (execlp(command, command, NULL) == -1) {
                    perror(command);
                    exit(EXIT_FAILURE);
                }
            } 

        else {
            waitpid(pid, &status, 0);
        }

        free(command);
    } while (1);

    write(STDOUT_FILENO, "Exiting...\n", strlen("Exiting...\n"));

    return EXIT_SUCCESS;
}
