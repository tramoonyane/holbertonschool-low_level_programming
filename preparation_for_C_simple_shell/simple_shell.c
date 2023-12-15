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
    char *command;

    do {
        display_prompt();

        command = read_command();
        
        /* Check if the command is more than one word */
        if (strchr(command, ' ') != NULL) {
            printf("Error: Command should contain only one word.\n");
            free(command);
            continue;
        }

        printf("Command entered: %s\n", command);

        /* Free memory allocated for command */
        free(command);
    } while (strcmp(command, "exit") != 0);

    printf("Exiting...\n");

    return EXIT_SUCCESS;
}
