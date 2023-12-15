#include "Simple_Shell.h"

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters_read;
    char **arguments;

    while (1) {
        print_prompt();
        characters_read = getline(&buffer, &bufsize, stdin);

        if (characters_read == -1) {
            // Handle end of file (Ctrl+D)
            printf("\n");
            free(buffer);
            break;
        }

        if (buffer[characters_read - 1] == '\n') {
            buffer[characters_read - 1] = '\0';
        }

        arguments = tokenize_input(buffer);
        if (arguments != NULL && arguments[0] != NULL) {
            execute_command(arguments);
            free(arguments);
        }
    }

    free(buffer);
    return 0;
}

char **tokenize_input(char *input) {
    char **tokens = malloc(2 * sizeof(char *));

    if (!tokens) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    tokens[0] = input;
    tokens[1] = NULL;

    return tokens;
}

void execute_command(char **arguments) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execvp(arguments[0], arguments) == -1) {
            fprintf(stderr, "%s: command not found\n", arguments[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        waitpid(pid, &status, 0);
    }
}

void print_prompt(void) {
    printf("($) ");
    fflush(stdout);
}
