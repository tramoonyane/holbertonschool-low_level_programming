/* simple_shell.c */

#include "Simple_Shell.h"


/**
 * read_command - Reads a command from standard input.
 *
 * Return: Returns the input command as a dynamically allocated string.
 */
char* read_command()
{
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
 * handle_builtin_commands - Handle built-in commands.
 *
 * @command: The command to execute.
 *
 * Return: Returns 1 if a built-in command is executed, 0 otherwise.
 */
int handle_builtin_commands(char *command) {
    /* Add your implementation of built-in commands handling here. */
    /* For example, if "exit" is a built-in command, check and handle it. */
    if (strcmp(command, "exit") == 0) {
        exit(EXIT_SUCCESS);
        return 1;
    }
    /* Add more built-in commands handling as needed. */

    return 0;  // Indicate that the command is not a built-in command.
}

/**
 * main - Main function of the shell.
 *
 * Return: Returns EXIT_SUCCESS upon successful execution.
 */
int main() {
    char *command;
    int command_number = 1;
    char *program_name = "hsh"; /* Replace this with your program's name */

    /* Check if input is from terminal or redirected from file/pipe */
    if (isatty(STDIN_FILENO)) {
        /* Interactive mode */
        do {
            printf("%s", PROMPT);
            fflush(stdout); /* Flush stdout to ensure prompt is printed immediately */
            
            command = read_command();

            if (feof(stdin)) {
                free(command);
                printf("\n");  /* Print newline for proper formatting */
                exit(EXIT_SUCCESS);
            }

            if (!handle_builtin_commands(command)) {
                /* If not a built-in command, execute the command */
                if (execute_command(command, command_number, program_name) == EXIT_FAILURE) {
                    free(command);
                    continue;
                }
            }

            free(command);
            command_number++; /* Increment command number for each command */
        } while (1);
    } else {
        /* Non-interactive mode */
        char input[BUFFER_SIZE];

        while (fgets(input, BUFFER_SIZE, stdin)) {
            /* Process the command in the non-interactive mode */
            /* Remove the newline character from input, if any */
            input[strcspn(input, "\n")] = '\0';

            /* Execute the command */
            if (execute_command(input, command_number, program_name) == EXIT_FAILURE) {
                /* Handle error if needed */
                /* Display error messages or perform necessary actions */
            }
            printf("\n");  /* Print newline for proper formatting */
            command_number++; /* Increment command number for each command */
        }
    }
    return EXIT_SUCCESS;
}
