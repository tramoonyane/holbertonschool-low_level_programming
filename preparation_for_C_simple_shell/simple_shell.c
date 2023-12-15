#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024
#define PROMPT "$ "

void display_prompt() {
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

char* read_command() {
    char input[BUFFER_SIZE];

    if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
        if (feof(stdin)) {
            write(STDOUT_FILENO, "\n", 1);
            exit(EXIT_SUCCESS);
        } else {
            perror("fgets error");
            exit(EXIT_FAILURE);
        }
    }

    input[strcspn(input, "\n")] = '\0';

    char *command = (char *)malloc(strlen(input) + 1);
    if (command == NULL) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    strcpy(command, input);
    return command;
}

bool has_arguments(const char *command) {
    for (int i = 0; command[i] != '\0'; ++i) {
        if (command[i] == ' ') {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    char *command;

    do {
        display_prompt();

        command = read_command();

        if (feof(stdin)) {
            write(STDOUT_FILENO, "\n", 1);
            free(command);
            exit(EXIT_SUCCESS);
        }

        if (has_arguments(command)) {
            char *error_message = "Error: Command should not contain arguments.\n";
            write(STDERR_FILENO, error_message, strlen(error_message));
            free(command);
            continue;
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            char *args[] = {command, NULL};
            if (execve(command, args, NULL) == -1) {
                char error_buffer[BUFFER_SIZE];
                snprintf(error_buffer, BUFFER_SIZE, "%s: 1: %s: not found\n", argv[0], command);
                write(STDERR_FILENO, error_buffer, strlen(error_buffer));
                exit(EXIT_FAILURE);
            }
        } else {
            int status;
            waitpid(pid, &status, 0);
        }

        free(command);
    } while (strcmp(command, "exit") != 0);

    write(STDOUT_FILENO, "Exiting...\n", strlen("Exiting...\n"));

    return EXIT_SUCCESS;
}
