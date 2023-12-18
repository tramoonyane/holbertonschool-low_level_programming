/* simple_shell.c */

#include "Simple_Shell.h"

/**
 * parse_path - Tokenizes the PATH environment variable.
 *
 * Return: Returns an array of directories.
 */
char **parse_path() {
    char *path = getenv("PATH");
    char **directories = malloc(sizeof(char *));
    if (directories == NULL) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(path, ":");
    int count = 0;
    while (token != NULL) {
        directories = realloc(directories, (count + 1) * sizeof(char *));
        if (directories == NULL) {
            perror("realloc error");
            exit(EXIT_FAILURE);
        }
        directories[count++] = token;
        token = strtok(NULL, ":");
    }
    directories = realloc(directories, (count + 1) * sizeof(char *));
    if (directories == NULL) {
        perror("realloc error");
        exit(EXIT_FAILURE);
    }
    directories[count] = NULL;

    return directories;
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
    char **args;
    char *p;
    int arg_count = 1;  /* Initial count for command itself */
    char **directories = parse_path();

    /* ... existing code ... */

    int found = 0;
    for (int i = 0; directories[i] != NULL; i++) {
        char path_command[BUFFER_SIZE];
        snprintf(path_command, sizeof(path_command), "%s/%s", directories[i], args[0]);
        if (access(path_command, X_OK) == 0) {
            found = 1;
            pid = fork();
            if (pid == -1) {
                perror("fork error");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                /* Child process */
                if (execv(path_command, args) == -1) {
                    fprintf(stderr, "%s: command execution error\n", args[0]);
                    exit(EXIT_FAILURE);
                }
            } else {
                /* Parent process */
                waitpid(pid, &status, 0);
            }
            break;
        }
    }

    if (!found) {
        fprintf(stderr, "%s: command not found\n", args[0]);
    }

    free(args);
    free(directories);
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
int main()
{
    char *command;

    do {
        printf("%s", PROMPT);
        command = read_command();

        if (feof(stdin)) {
            free(command);
            write(STDOUT_FILENO, "\n", 1);
            exit(EXIT_SUCCESS);
        }

        if (execute_command(command) == EXIT_FAILURE) {
            free(command);
            continue;
        }

        free(command);
    } while (1);

    return EXIT_SUCCESS;
}
