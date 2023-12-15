#include "simple_shell.h"
#include <unistd.h>
#include <libgen.h>
#include <sys/wait.h>

extern char **environ; /* Declaration of the environment variable */

#define BUFFER_SIZE 1024
#define PROMPT "$ "

void display_prompt() {
    printf("%s", PROMPT);
}

char* read_command() {
    char input[BUFFER_SIZE];

    if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
        if (feof(stdin)) {
            printf("\n");
            exit(EXIT_SUCCESS); /* Exit gracefully on Ctrl+D */
        } else {
            perror("fgets error");
            exit(EXIT_FAILURE);
        }
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

int main(int argc, char *argv[]) {
    char *command;

    do {
        display_prompt();

        command = read_command();

        if (feof(stdin)) {
            printf("\n");
            free(command);
            exit(EXIT_SUCCESS); /* Exit gracefully on Ctrl+D */
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Child process */
            char *args[] = {command, NULL};
            if (execve(command, args, environ) == -1) {
                fprintf(stderr, "%s: 1: %s: not found\n", basename(command), command);
                exit(EXIT_FAILURE);
            }
        } else {
            /* Parent process */
            int status;
            waitpid(pid, &status, 0);
        }

        free(command);
    } while (strcmp(command, "exit") != 0);

    printf("Exiting...\n");

    return EXIT_SUCCESS;
}
