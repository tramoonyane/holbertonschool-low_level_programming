/* simple_shell_exit.c */
#include "Simple_Shell.h"

/**
 * exit_shell - Exits the shell.
 */
void exit_shell() {
    exit(EXIT_SUCCESS);
}

/**
 * handle_builtin_commands - Handles built-in commands like 'exit'.
 *
 * @command: The command to execute.
 *
 * Return: Returns 1 if a built-in command is executed, otherwise 0.
 */
int handle_builtin_commands(char *command) {
    if (strcmp(command, "exit") == 0) {
        exit_shell(); /* Call the exit_shell function */
        return 1;     /* Return 1 to indicate the command was handled */
    }
    return 0; /* Return 0 for other commands */
}

int main() {
    char *command;

    do {
        printf("%s", PROMPT);
        command = read_command();

        if (feof(stdin)) {
            free(command);
            write(STDOUT_FILENO, "\n", 1);
            exit(EXIT_SUCCESS);
        }

        if (!handle_builtin_commands(command)) {
            // If not a built-in command, execute the command
            if (execute_command(command) == EXIT_FAILURE) {
                free(command);
                continue;
            }
        }

        free(command);
    } while (1);

    return EXIT_SUCCESS;
}
