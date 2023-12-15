#include "Simple_Shell.h"

void display_prompt() {
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

char* read_command() {
    char *command;
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

    command = (char *)malloc(strlen(input) + 1);
    if (command == NULL) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    strcpy(command, input);
    return command;
}

void print_environment() {
    extern char **environ;
    int i;
    for (i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
}

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused))) {
    char *command;
    pid_t pid;

    do {
        display_prompt();

        command = read_command();

        if (feof(stdin)) {
            write(STDOUT_FILENO, "\n", 1);
            free(command);
            exit(EXIT_SUCCESS);
        }

        if (strcmp(command, "env") == 0) {
            print_environment();
            free(command);
            continue;
        }

        pid = fork();

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
