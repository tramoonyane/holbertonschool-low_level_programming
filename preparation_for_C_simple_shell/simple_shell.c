#include "Simple_Shell.h"
#include <string.h>
#include <stdlib.h>

#define MAX_TOKENS 64
#define PATH_MAX_LENGTH 1024

extern char **environ;

int main(int argc, char *argv[]) {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters_read;
    char **arguments;

    if (argc == 1) {
        char **arguments;

        while (1) {
            print_prompt();
            characters_read = getline(&buffer, &bufsize, stdin);

            if (characters_read == -1) {
                printf("\n");
                free(buffer);
                break;
            }

            if (buffer[characters_read - 1] == '\n') {
                buffer[characters_read - 1] = '\0';
            }

            arguments = tokenize_input(buffer);
            if (arguments != NULL && arguments[0] != NULL) {
                if (strcmp(arguments[0], "exit") == 0) {
                    free(buffer);
                    free(arguments);
                    break;
                } else if (strcmp(arguments[0], "env") == 0) {
                    print_environment();
                } else {
                    execute_command(arguments);
                    free(arguments);
                }
            }
        }
    } else {
        FILE *input_file = fopen(argv[1], "r");
        if (input_file == NULL) {
            perror("Error opening file");
            return EXIT_FAILURE;
        }

        while ((characters_read = getline(&buffer, &bufsize, input_file)) != -1) {
            if (buffer[characters_read - 1] == '\n') {
                buffer[characters_read - 1] = '\0';
            }

            arguments = tokenize_input(buffer);
            if (arguments != NULL && arguments[0] != NULL) {
                execute_command(arguments);
                free(arguments);
            }
        }

        fclose(input_file);
    }

    free(buffer);
    return EXIT_SUCCESS;
}

char **tokenize_input(char *input) {
    int bufsize = MAX_TOKENS;
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
            bufsize += MAX_TOKENS;
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
    int status;
    char *path_env;
    char *path;
    char command_path[PATH_MAX_LENGTH];
    int found;
    
    
    if (strcmp(arguments[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    } else if (strcmp(arguments[0], "env") == 0) {
        print_environment();
        return;
    }
    path_env = getenv("PATH");
    path = strtok(path_env, ":");
    found = 0;

    while (path != NULL) {
        snprintf(command_path, PATH_MAX_LENGTH, "%s/%s", path, arguments[0]);
        if (access(command_path, X_OK) == 0) {
            found = 1;
            break;
        }
        path = strtok(NULL, ":");
    }

    if (!found) {
        fprintf(stderr, "%s: command not found\n", arguments[0]);
        return;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execv(command_path, arguments) == -1) {
            perror("execv");
            exit(EXIT_FAILURE);
        }
    } else {
        waitpid(pid, &status, 0);
    }
}


void print_prompt(void) {
    printf("$ ");
    fflush(stdout);
}

void print_environment() {
    char **env = environ;

    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }
}
