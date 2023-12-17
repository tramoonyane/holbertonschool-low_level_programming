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

char **tokenize_command(char *command) {
    char **args = NULL;
    char *token;
    int arg_count = 0;

    token = strtok(command, " \t\n");
    while (token != NULL) {
        args = realloc(args, (arg_count + 1) * sizeof(char *));
        if (args == NULL) {
            perror("realloc error");
            exit(EXIT_FAILURE);
        }

        args[arg_count] = strdup(token);
        if (args[arg_count] == NULL) {
            perror("strdup error");
            exit(EXIT_FAILURE);
        }

        arg_count++;
        token = strtok(NULL, " \t\n");
    }

    args = realloc(args, (arg_count + 1) * sizeof(char *));
    if (args == NULL) {
        perror("realloc error");
        exit(EXIT_FAILURE);
    }
    args[arg_count] = NULL;

    return args;
}

void execute_command(const char *program_name, char **args) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        char *envp[] = { NULL };
        if (execve(args[0], args, envp) == -1) {
            perror("execve error");
            exit(EXIT_FAILURE);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused))) {
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

        args = tokenize_command(command);
        execute_command(argv[0], args);

        free(command);
        free(args);
    } while (strcmp(command, "exit") != 0);

    write(STDOUT_FILENO, "Exiting...\n", strlen("Exiting...\n"));
    return EXIT_SUCCESS;
}
