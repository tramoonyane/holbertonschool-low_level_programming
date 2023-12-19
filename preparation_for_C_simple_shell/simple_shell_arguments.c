/* simple_shell_arguments.c */

#include "Shell.h"

/**
 * parse_path - Tokenizes the PATH environment variable.
 *
 * Return: Returns an array of directories.
 */
char **parse_path() {
    char *path = getenv("PATH");
    char *token;
    int count;
    char *path_copy;
    char **directories = malloc(sizeof(char *));
    if (path == NULL || *path == '\0') {
        fprintf(stderr, "No PATH variable found or empty.\n");
        exit(EXIT_FAILURE);
    }
    path_copy = strdup(path);
    if (path_copy == NULL) {
        perror("strdup error");
        exit(EXIT_FAILURE);
    }

    token = strtok(path_copy, ":");
    count = 0;
    directories = malloc(sizeof(char *));
    if (directories == NULL) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }
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
    free(path_copy);

    return directories;
}

/**
 * execute_command - Executes the command with arguments.
 *
 * @command: The command to execute.
 * @command_number: Number of the command in the shell session.
 * @program_name: The name of the shell program.
 *
 * Return: Returns EXIT_SUCCESS upon successful execution.
 */
int execute_command(char *command, int command_number, char *program_name) {
    char **args;
    int arg_count;

    if (command == NULL || *command == '\0') {
        return EXIT_SUCCESS; /* Skip execution for empty commands */
    }

    arg_count = count_arguments(command);
    args = get_command_arguments(command, arg_count);

    execute_command_with_path(args, command_number, program_name);

    free(args);
    return EXIT_SUCCESS;
}

/**
 * count_arguments - Counts the number of arguments in a command.
 *
 * @command: The command to analyze.
 *
 * Return: Returns the number of arguments.
 */
int count_arguments(char *command) {
    int arg_count = 1; /* Initial count for command itself */
    char *p;

    for (p = command; *p != '\0'; ++p) {
        if (*p == ' ') {
            arg_count++;
            while (*p == ' ') /* Skip consecutive spaces */
                p++;
        }
    }

    return arg_count;
}

/**
 * get_command_arguments - Splits the command into arguments.
 *
 * @command: The command to split.
 * @arg_count: Number of arguments in the command.
 *
 * Return: Returns an array of command arguments.
 */
char **get_command_arguments(char *command, int arg_count) {
    char **args;
    int i = 0;

    args = malloc((arg_count + 1) * sizeof(char *));
    if (args == NULL) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    args[i++] = strtok(command, " \n"); /* Get the command */

    while ((args[i++] = strtok(NULL, " \n")) != NULL);

    return args;
}

/**
 * execute_command_with_path - Executes the command with full path.
 *
 * @args: Array of command arguments.
 * @command_number: Number of the command in the shell session.
 * @program_name: The name of the shell program.
 */
void execute_command_with_path(char **args, int command_number, char *program_name) {
    pid_t pid;
    int status;
    char **directories = parse_path();
    int found = 0;
    int i;

    for (i = 0; directories[i] != NULL; i++) {
        char path_command[BUFFER_SIZE];
        snprintf(path_command, sizeof(path_command), "%s/%s", directories[i], args[0]);

        /* Check if the command is executable at the given path */
        if (access(path_command, X_OK) == 0) {
            found = 1;
            pid = fork();
            if (pid == -1) {
                perror("fork error");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                /* Child process */
                if (execv(path_command, args) == -1) {
                    fprintf(stderr, "%s: %d: %s: not found\n", program_name, command_number, args[0]);
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
        fprintf(stderr, "%s: %d: %s: not found\n", program_name, command_number, args[0]);
    }

    free(directories);
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
 * handle_builtin_commands - Handles built-in commands like 'exit' and 'env'.
 *
 * @command: The command to execute.
 *
 * Return: Returns 1 if a built-in command is executed, otherwise 0.
 */
int handle_builtin_commands(char *command) {
    if (strcmp(command, "exit") == 0) {
        exit_shell(); /* Call the exit_shell function */
        return 1;     /* Return 1 to indicate the command was handled */
    } else if (strcmp(command, "env") == 0) {
        print_environment(); /* Print the environment variables */
        return 1;            /* Return 1 to indicate the command was handled */
    }
    return 0; /* Return 0 for other commands */
}


/**
 * exit_shell - Exits the shell.
 */
void exit_shell() {
    exit(EXIT_SUCCESS);
}
