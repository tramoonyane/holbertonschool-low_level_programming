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
int execute_command(char *command, int command_number, char *program_name)
{
    pid_t pid;
    int status;
    char **args;
    char *p;
    int arg_count = 1;  /* Initial count for command itself */
    (void)command_number; /* Suppress the unused parameter warning */
    (void)program_name;   /* Suppress the unused parameter warning */


    /* Count the number of arguments (tokens) */
    for (p = command; *p != '\0'; ++p) {
        if (*p == ' ') {
            arg_count++;
            while (*p == ' ')  /* Skip consecutive spaces */
                p++;
        }
    }

    /* Allocate memory for the args array */
    args = malloc((arg_count + 1) * sizeof(char *));
    if (args == NULL) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    arg_count = 0;
    args[arg_count++] = strtok(command, " \n");  /* Get the command */

    /* Get the arguments and store them in the args array */
    while ((args[arg_count++] = strtok(NULL, " \n")) != NULL);

    pid = fork();

    if (pid == -1) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /* Child process */
        if (execve(args[0], args, environ) == -1) {
            perror(args[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        /* Parent process */
        waitpid(pid, &status, 0);
    }

    free(args);
    return EXIT_SUCCESS;
}
/**
 * read_command - Reads a command from standard input.
 *
 * Return: Returns the input command as a dynamically allocated string.
 */
char* read_command()
{
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
