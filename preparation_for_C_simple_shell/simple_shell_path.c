/* simple_shell_path.c */

#include "Simple_Shell.h"

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
 *
 * Return: Returns EXIT_SUCCESS upon successful execution.
 */
int execute_command(char *command, int command_number, char *program_name){
    pid_t pid;
    int status;
    char **args;
    char *p;
    int arg_count = 1;  /* Initial count for command itself */
    char **directories = parse_path();
    int found;
    int i;

    if (command == NULL || *command == '\0') {
        return EXIT_SUCCESS; /* Skip execution for empty commands */
    }

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

    found = 0;
    for (i = 0; directories[i] != NULL; i++) {
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
int main() {
    char *command;
    int command_number = 1;
    char *program_name = "hsh"; /* Replace this with your program's name */
    
    /* Check if input is from terminal or redirected from file/pipe */
    if (isatty(STDIN_FILENO)) {
    /* Interactive mode */    
    do {
        printf("%s", PROMPT);
        command = read_command();

        if (feof(stdin)) {
            free(command);
            write(STDOUT_FILENO, "\n", 1);
            exit(EXIT_SUCCESS);
        }

        if (!handle_builtin_commands(command)) {
            /* If not a built-in command, execute the command */
            if (execute_command(command) == EXIT_FAILURE) {
                free(command);
                continue;
            }
        }

        free(command);
    } while (1);
    } else {
        /* Non-interactive mode */
            char input[BUFFER_SIZE];
        while (fgets(input, BUFFER_SIZE, stdin)) {
            /* Process the command in the non-interactive mode */
            /* Remove the newline character from input, if any */
            input[strcspn(input, "\n")] = '\0';

            /* Execute the command */
            if (execute_command(input) == EXIT_FAILURE) {
                /* Handle error if needed */
                /* Display error messages or perform necessary actions */
            }
        }
    }
    return EXIT_SUCCESS;
}
