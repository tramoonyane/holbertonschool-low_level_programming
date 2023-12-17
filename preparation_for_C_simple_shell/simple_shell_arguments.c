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
 * tokenize_command - Tokenizes the command into arguments.
 *
 * @command: The command string to be tokenized.
 *
 * Return: Returns an array of strings containing the command and arguments.
 */
char **tokenize_command(char *command) {
    char **args = NULL;
    char *token = strtok(command, " \t\n");
    int arg_count = 0;

    while (token != NULL) {
        args = realloc(args, (arg_count + 1) * sizeof(char *));
        if (args == NULL) {
            perror("realloc error");
            exit(EXIT_FAILURE);
        }

        args[arg_count++] = token;
        token = strtok(NULL, " \t\n");
    }

    args = realloc(args, (arg_count + 1) * sizeof(char *));
    if (args == NULL) {
        perror("realloc error");
        exit(EXIT_FAILURE);
    }
    args[arg_count] = NULL;

    return args;
}

/**
 * execute_command - Executes the command with arguments.
 *
 * @args: An array of strings containing the command and arguments.
 */
void execute_command(char **args) {
    char *envp[] = { NULL };

    pid_t pid = fork();

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
        int status;
        waitpid(pid, &status, 0);
    }
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
    int status;

    do {
        display_prompt();
        command = read_command();

        if (feof(stdin)) {
            write(STDOUT_FILENO, "\n", 1);
            free(command);
            exit(EXIT_SUCCESS);
        }

        char **args = tokenize_command(command);
        execute_command(args);

        free(command);
        free(args);
    } while (strcmp(command, "exit") != 0);

    write(STDOUT_FILENO, "Exiting...\n", strlen("Exiting...\n"));
    return EXIT_SUCCESS;
}
