#include "Simple_Shell.h"

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters_read;
    char **arguments;
    int status = 0;

    while (1) {
        print_prompt(status);
        characters_read = getline(&buffer, &bufsize, stdin);
        if (characters_read == -1) {
            printf("\n");
            free(buffer);
            exit(EXIT_SUCCESS);
        }
        if (buffer[characters_read - 1] == '\n') {
            buffer[characters_read - 1] = '\0';
        }

        arguments = tokenize_input(buffer);
        if (arguments != NULL) {
            if (strcmp(arguments[0], "exit") == 0) {
                free(arguments);
                free(buffer);
                exit(EXIT_SUCCESS);
            }
             }
            execute_command(arguments);
            free(arguments);
        } else {
            status = 1;
            continue; // Skip waiting for non-existent command
        }

        wait(&status); // Wait for child process
        if (WIFEXITED(status)) {
            status = WEXITSTATUS(status);
        }
    }

    free(buffer);
    return 0;
}
