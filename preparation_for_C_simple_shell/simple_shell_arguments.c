/* simple_shell_arguments.c */

#include "Simple_Shell.h"
extern char **environ;

/**
 * execute_command - Executes the command with arguments.
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
    char *args[BUFFER_SIZE + 1];  /* Maximum buffer size for arguments */
    int arg_count = 0; /* Initialize count for command arguments */
    char *token;
    int i;
    (void)command_number; /* Suppress the unused parameter warning */
    (void)program_name;   /* Suppress the unused parameter warning */

    /* Tokenize the command and store arguments in the args array */
    token = strtok(command, " \n");
    while (token != NULL && arg_count < BUFFER_SIZE) {
        args[arg_count++] = strdup(token);
        if (args[arg_count - 1] == NULL) {
            perror("strdup error");
            /* Free allocated memory before exiting */
            for (int i = 0; i < arg_count - 1; ++i) {
                free(args[i]);
            }
            exit(EXIT_FAILURE);
        }
        token = strtok(NULL, " \n");
    }
    args[arg_count] = NULL; /* Null-terminate the argument list */

    pid = fork();

    if (pid == -1) {
        perror("fork error");
        /* Free allocated memory before exiting */
        for (i = 0; i < arg_count; ++i) {
            free(args[i]);
        }
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /* Child process */
        if (execve(args[0], args, environ) == -1) {
            perror(args[0]);
            /* Free allocated memory before exiting */
            for (i = 0; i < arg_count; ++i) {
                free(args[i]);
            }
            exit(EXIT_FAILURE);
        }
    } else {
        /* Parent process */
        waitpid(pid, &status, 0);
    }

    /* Free allocated memory for arguments */
    for (i = 0; i < arg_count; ++i) {
        free(args[i]);
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
int main(int argc, char *argv[]) {
    char *command;
    int command_number = 1;
    char *program_name = basename(argv[0]); /* Get the base name of the program */
    (void)argc; /* Suppress the unused parameter warning */

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

            if (execute_command(command, command_number, program_name) == EXIT_FAILURE) {
                free(command);
                continue;
            }

            free(command);
            command_number++; /* Increment command number for each command */
        } while (1);
    } else {
        /* Non-interactive mode */
        char input[BUFFER_SIZE];

        /* Process the command in the non-interactive mode */
        while (fgets(input, BUFFER_SIZE, stdin)) {
            /* Remove the newline character from input, if any */
            input[strcspn(input, "\n")] = '\0';

            /* Execute the command */
            if (execute_command(input, command_number, program_name) == EXIT_FAILURE) {
                /* Handle error if needed */
                /* Display error messages or perform necessary actions */
            }

            if (feof(stdin)) {
                printf("\n"); /* Print newline for proper formatting before exiting */
                exit(EXIT_SUCCESS);
            } else {
                printf("\n"); /* Print newline for proper formatting between commands */
            }

            command_number++; /* Increment command number for each command */
        }
    }

    return EXIT_SUCCESS;
}
