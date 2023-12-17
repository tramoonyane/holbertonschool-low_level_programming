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
    char **args; // Dynamically allocate memory to hold command and arguments
    char *envp[] = { NULL }; // Environment variable not used here
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

        char *token = strtok(command, " "); // Split command and arguments
        int arg_count = 0;
        args = (char **)malloc(sizeof(char *)); // Allocate memory for args
        if (args == NULL) {
            perror("malloc error");
            exit(EXIT_FAILURE);
        }

        while (token != NULL) {
            args[arg_count] = token;
            arg_count++;
            args = (char **)realloc(args, sizeof(char *) * (arg_count + 1)); // Reallocate memory for args
            if (args == NULL) {
                perror("realloc error");
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL; /* NULL-terminate the args array */

        pid = fork();

        if (pid == -1) {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (execve(args[0], args, envp) == -1) {
                char error_buffer[BUFFER_SIZE];
                snprintf(error_buffer, BUFFER_SIZE, "%s: No such file or directory\n", argv[0]);
                write(STDERR_FILENO, error_buffer, strlen(error_buffer));
                exit(EXIT_FAILURE);
            }
        } else {
            waitpid(pid, &status, 0);
        }

        free(command);
        free(args); /* Free dynamically allocated args memory */
    } while (strcmp(command, "exit") != 0);

    write(STDOUT_FILENO, "Exiting...\n", strlen("Exiting...\n"));

    return EXIT_SUCCESS;
}
