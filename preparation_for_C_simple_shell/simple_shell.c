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
    int args_count = 1;
    char *token;
    char *temp_command = strdup(command); /* Create a temporary copy of the command */
    char **args;
    int i;
    char *path;
    char full_path[PATH_MAX];

    /* Count the number of arguments in the command */
    token = strtok(temp_command, " ");
    while (token != NULL) {
        args_count++;
        token = strtok(NULL, " ");
    }
    free(temp_command); /* Free the temporary copy of the command */

    /* Allocate memory for the args array based on the arguments count */
    args = malloc(args_count * sizeof(char *));
    if (args == NULL) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    /* Tokenize the command and store arguments in the args array */
    token = strtok(command, " ");
    args[0] = token; /* The first argument is the command itself */
    i = 1;
    while (token != NULL && i < args_count) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; /* Null-terminate the argument list */

    pid = fork();

    if (pid == -1) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /* Child process */
        /* Try to execute the command with full path */
        if (execve(args[0], args, environ) == -1) {
            /* Try to execute the command in the current directory */
            path = getenv("PWD");
            if (path == NULL) {
                perror("getenv error");
                exit(EXIT_FAILURE);
            }
            snprintf(full_path, PATH_MAX, "%s/%s", path, args[0]);

            if (execve(full_path, args, environ) == -1) {
                fprintf(stderr, "%s: %d: %s: not found\n", program_name, command_number, command);
                exit(EXIT_FAILURE);
            }
        }
    } else {
        /* Parent process */
        waitpid(pid, &status, 0);
    }

    free(args); /* Free the allocated memory for args */
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
