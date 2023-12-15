#include "Simple_Shell.h"

void display_prompt() {
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

char** parse_arguments(const char *command) {
    char *token;
    char **args = (char **)malloc(BUFFER_SIZE * sizeof(char *));
    if (args == NULL) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    token = strtok((char *)command, " ");
    int i = 0;
    while (token != NULL) {
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;

    return args;
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

int main(int argc, char *argv[]) {
    char *command;
    char **args;

    do {
        display_prompt();

        command = read_command();

        if (feof(stdin)) {
            write(STDOUT_FILENO, "\n", 1);
            free(command);
            exit(EXIT_SUCCESS);
        }

        args = parse_arguments(command);

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                char error_buffer[BUFFER_SIZE];
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
