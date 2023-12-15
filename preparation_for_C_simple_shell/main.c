#include "Simple_Shell.h"

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters_read;
    char **arguments;
    int status = 0;
    int interactive = isatty(STDIN_FILENO);

    while (1) {
        if (interactive) {
            print_prompt(status);
        }

        characters_read = getline(&buffer, &bufsize, stdin);
        if (characters_read == -1) {
            printf("\n");
            free(buffer);
            if (interactive) {
                exit(EXIT_SUCCESS);
            } else {
                break;
            }
        }

        if (buffer[characters_read - 1] == '\n') {
            buffer[characters_read - 1] = '\0';
        }

        arguments = tokenize_input(buffer);
        if (arguments != NULL) {
            if (strcmp(arguments[0], "exit") == 0) {
                free(arguments);
                free(buffer);
                if (interactive) {
                    exit(EXIT_SUCCESS);
                } else {
                    break;
                }
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
