#include "simple_shell.h"

#define BUFFER_SIZE 1024
#define PROMPT "$ "

void display_prompt() {
    printf("%s", PROMPT);
}

char* read_command() {
    char input[BUFFER_SIZE];

    if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
        perror("fgets error");
        exit(EXIT_FAILURE);
    }

    input[strcspn(input, "\n")] = '\0'; /* Remove trailing newline */

    char *command = (char *)malloc(strlen(input) + 1);
    if (command == NULL) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    strcpy(command, input);
    return command;
}

int main() {
    while (1) {
        display_prompt();

        char *command = read_command();
        printf("Command entered: %s\n", command);

        /* Exit the loop if the user inputs 'exit' */
        if (strcmp(command, "exit") == 0) {
            printf("Exiting...\n");
            free(command);
            break;
        }

        /* Free memory allocated for command */
        free(command);
    }

    return EXIT_SUCCESS;
}
