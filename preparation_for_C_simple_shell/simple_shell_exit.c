#include "simple_shell.h"

// ... (display_prompt, read_command, parse_arguments functions remain unchanged)

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

        char **args = parse_arguments(command);

        if (strcmp(args[0], "exit") == 0) {
            free(args);
            free(command);
            exit(EXIT_SUCCESS);
        }

        pid_t pid;
        if (access(args[0], X_OK) != -1) {
            pid = fork();
        } else {
            // PATH handling logic here
        }

        if (pid == -1) {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (execv(args[0], args) == -1) {
                perror("execv error");
                exit(EXIT_FAILURE);
            }
        } else {
            int status;
            waitpid(pid, &status, 0);
        }

        free(args);
        free(command);
    } while (1);

    write(STDOUT_FILENO, "Exiting...\n", strlen("Exiting...\n"));

    return EXIT_SUCCESS;
}
