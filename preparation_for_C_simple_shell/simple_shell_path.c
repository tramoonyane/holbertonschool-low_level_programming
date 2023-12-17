#include "Simple_Shell.h"

void display_prompt() {
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

char** parse_arguments(const char *command) {
    char *token;
    int i;
    char **args = (char **)malloc(BUFFER_SIZE * sizeof(char *));
    if (args == NULL) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    token = strtok((char *)command, " ");
    i = 0;
    while (token != NULL) {
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;

    return args;
}

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused))) {
    char *command;
    char **args;
    pid_t pid;

    do {
        display_prompt();

        command = read_command();

        if (feof(stdin)) {
            write(STDOUT_FILENO, "\n", 1);
            free(command);
            exit(EXIT_SUCCESS);
        }

        if (command[0] == '\0') {
            free(command);
            continue; /* Continue to the next iteration if an empty command is provided */
        }

        args = parse_arguments(command);

        pid = fork();

        if (pid == -1) {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Check if the command is an absolute path */
            if (command[0] == '/') {
                if (execv(args[0], args) == -1) {
                    char error_buffer[BUFFER_SIZE];
                    snprintf(error_buffer, BUFFER_SIZE, "%s: command not found\n", args[0]);
                    write(STDERR_FILENO, error_buffer, strlen(error_buffer));
                    exit(EXIT_FAILURE);
                }
            } else {
                /* Check the PATH for the command */
                char error_buffer[BUFFER_SIZE];
                char *env_path = getenv("PATH");
                char *path = strtok(env_path, ":");
                while (path != NULL) {
                    char exec_path[BUFFER_SIZE];
                    snprintf(exec_path, BUFFER_SIZE, "%s/%s", path, args[0]);
                    if (access(exec_path, X_OK) == 0) {
                        if (execv(exec_path, args) == -1) {
                            char error_buffer[BUFFER_SIZE];
                            snprintf(error_buffer, BUFFER_SIZE, "%s: command not found\n", args[0]);
                            write(STDERR_FILENO, error_buffer, strlen(error_buffer));
                            exit(EXIT_FAILURE);
                        }
                    }
                    path = strtok(NULL, ":");
                }
                snprintf(error_buffer, BUFFER_SIZE, "%s: command not found\n", args[0]);
                write(STDERR_FILENO, error_buffer, strlen(error_buffer));
                exit(EXIT_FAILURE);
            }
        } else {
            int status;
            waitpid(pid, &status, 0);
        }

        free(args);
        free(command);
    } while (strcmp(command, "exit") != 0);

    write(STDOUT_FILENO, "Exiting...\n", strlen("Exiting...\n"));

    return EXIT_SUCCESS;
}
