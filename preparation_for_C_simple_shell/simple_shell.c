#include "simple_shell.h"
#include <unistd.h>
#include <libgen.h> // Included for basename()

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

int is_valid_command(const char *command) {
    if (access(command, X_OK) == -1) {
        fprintf(stderr, "%s: 1: %s: not found\n", basename(command), command);
        return 0; /* Not a valid command */
    }
    return 1; /* Valid command */
}

int main(int argc, char *argv[]) {
    char *command;

    do {
        display_prompt();

        command = read_command();
        
        /* Check if the command is more than one word */
        if (strchr(command, ' ') != NULL) {
            fprintf(stderr, "%s: 1: %s: Command should contain only one word.\n", argv[0], command);
            free(command);
            continue;
        }

        if (!is_valid_command(command)) {
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
