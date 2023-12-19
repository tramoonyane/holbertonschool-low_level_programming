/* main.c */

#include "Shell.h"

/**
 * main - Main function of the shell.
 * Return: Returns EXIT_SUCCESS upon successful execution.
 */
int main() {
    char *program_name = "hsh"; /* Replace this with your program's name */
    
    if (isatty(STDIN_FILENO)) {
        interactive_mode(program_name);
    } else {
        non_interactive_mode(program_name);
    }

    return EXIT_SUCCESS;
}

/**
 * interactive_mode - Handles the interactive mode of the shell.
 * @program_name: Name of the program (shell).
 */
void interactive_mode(char *program_name) {
    char *command;
    int command_number = 1;

    do {
        printf("%s", PROMPT);
        command = read_command();

        if (feof(stdin)) {
            free(command);
            write(STDOUT_FILENO, "\n", 1);
            exit(EXIT_SUCCESS);
        }

        if (!handle_builtin_commands(command)) {
            process_command(command, &command_number, program_name);
        }

        free(command);
        command_number++;
    } while (1);
}

/**
 * non_interactive_mode - Handles the non-interactive mode of the shell.
 * @program_name: Name of the program (shell).
 */
void non_interactive_mode(char *program_name) {
    char input[BUFFER_SIZE];
    int command_number = 1;

    while (fgets(input, BUFFER_SIZE, stdin)) {
        input[strcspn(input, "\n")] = '\0';
        process_command(input, &command_number, program_name);
        command_number++;
    }
}

/**
 * process_command - Process a command provided to the shell.
 * @command: Command to be processed.
 * @command_number: Pointer to the command number counter.
 * @program_name: Name of the program (shell).
 */
void process_command(char *command, int *command_number, char *program_name) {
    if (execute_command(command, *command_number, program_name) == EXIT_FAILURE) {
        /* Handle error if needed */
        /* Display error messages or perform necessary actions */
    }
}
