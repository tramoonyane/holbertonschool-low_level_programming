#include "Simple_Shell.h"

int main(int argc, char *argv[]) {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters_read;
    char **arguments;
    int status = 0;
    int interactive = isatty(STDIN_FILENO);

    if (!interactive) {
        characters_read = getline(&buffer, &bufsize, stdin);
        if (characters_read == -1) {
            perror("getline");
            exit(EXIT_FAILURE);
        }

        if (buffer[characters_read - 1] == '\n') {
            buffer[characters_read - 1] = '\0';
        }

        arguments = tokenize_input(buffer);
        if (arguments != NULL) {
            execute_command(arguments);
            free(arguments);
            free(buffer);
            return 0;
        } else {
            free(buffer);
            return 1;
        }
    }

    while (1) {
        print_prompt(status);

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
        if (arguments != NULL) {
            if (strcmp(arguments[0], "exit") == 0) {
                free(arguments);
                free(buffer);
                break;
            }
            execute_command(arguments);
            free(arguments);
            status = 0;
        } else {
            status = 1;
        }
    }

    free(buffer);
    return 0;
}
