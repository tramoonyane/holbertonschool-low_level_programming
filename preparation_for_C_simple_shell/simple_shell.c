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
            free(buffer);
            break;
        }

        if (buffer[characters_read - 1] == '\n') {
            buffer[characters_read - 1] = '\0';
        }

        arguments = tokenize_input(buffer);
        if (arguments != NULL) {
            if (strcmp(arguments[0], "exit") == 0) {
                free(buffer);
                free(arguments);
                exit(EXIT_SUCCESS);
            }
            execute_command(arguments);
            free(arguments);
        } 
    }

    free(buffer);
    return 0;
}

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
            fprintf(stderr, "%s: not found\n", arguments[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        wait(NULL);
    }
}

void print_prompt(void) {
    printf("($)\n");
    fflush(stdout);
}
