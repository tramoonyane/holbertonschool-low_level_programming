#include "Simple_Shell.h"

char **tokenize_input(char *input) {
    int bufsize = MAX_ARGUMENTS;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, TOKEN_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += MAX_ARGUMENTS;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

void execute_command(char **arguments) {
    pid_t pid;

    if (strcmp(arguments[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execvp(arguments[0], arguments) == -1) {
            fprintf(stderr, "./hsh: 1: %s: not found\n", arguments[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        wait(NULL);
    }
}

void print_prompt(int status) {
    printf("($)");
    fflush(stdout);
}
