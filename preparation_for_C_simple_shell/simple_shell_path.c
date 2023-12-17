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

char** parse_arguments(const char *command) {
    char *token;
    int i;
    int j;
    char **args = (char **)malloc(BUFFER_SIZE * sizeof(char *));
    if (args == NULL) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    token = strtok((char *)command, " ");
    i = 0;
    while (token != NULL) {
        args[i] = (char *)malloc(strlen(token) + 1);
        if (args[i] == NULL) {
            perror("malloc error");
            for (j = 0; j < i; j++) {
                free(args[j]);
            }
            free(args);
            exit(EXIT_FAILURE);
        }
        strcpy(args[i], token);
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

        if (access(args[0], X_OK) != -1) {
            pid = fork();
        } else {
            /* Check the PATH for the command */
            char *path;
            char *env_path = getenv("PATH");
            char *token = strtok(env_path, ":");
            while (token != NULL) {
                path = (char *)malloc(strlen(token) + strlen(args[0]) + 2);
                strcpy(path, token);
                strcat(path, "/");
                strcat(path, args[0]);
                if (access(path, X_OK) != -1) {
                    args[0] = path;
                    pid = fork();
                    break;
                }
                free(path);
                token = strtok(NULL, ":");
            }
            if (token == NULL) {
                fprintf(stderr, "%s: command not found\n", args[0]);
                free(command);
                free(args);
                continue;
            }
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
        free(command);
    } while (strcmp(command, "exit") != 0);

    write(STDOUT_FILENO, "Exiting...\n", strlen("Exiting...\n"));

    return EXIT_SUCCESS;
}
