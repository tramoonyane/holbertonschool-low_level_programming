/* simple_shell.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_TOKENS 100

extern char **environ;  /* Access to the environment variables */

/* Function to check if input is coming from a terminal */
int is_input_terminal() {
    return isatty(fileno(stdin));
}

/**
 * main - Simple Shell
 *
 * Return: Always 0
 */
int main(int argc, char *argv[]) {
    char input[MAX_INPUT_LENGTH];
    char *tokens[MAX_TOKENS];
    pid_t child_pid;
    int status;
    int interactive = is_input_terminal(); /* Check if input is interactive */
    char *program_name = argv[0]; /* Set the program name from argv[0] */
    int i;
    (void)argc;  /* Acknowledge the unused parameter to prevent the warning */

    if (interactive) {
        while (1) {
            printf("$ "); /* Display prompt only in interactive mode*/
            fflush(stdout);

            if (fgets(input, sizeof(input), stdin) == NULL) {
                if (feof(stdin)) {
                    printf("\n"); /* Print newline after Ctrl+D */
                    break;        /* Exit on EOF */
                }
            }

            input[strcspn(input, "\n")] = '\0'; /* Remove newline character */

            child_pid = fork();

            if (child_pid < 0) {
                perror("Fork failed");
                exit(EXIT_FAILURE);
            } else if (child_pid == 0) {
                int i = 0;
                tokens[i] = strtok(input, " "); /* Tokenize input */

                while (tokens[i] != NULL && i < MAX_TOKENS - 1) {
                    i++;
                    tokens[i] = strtok(NULL, " ");
                }

                tokens[i + 1] = NULL;

                if (execve(tokens[0], tokens, environ) == -1) {
                    fprintf(stderr, "%s: ", program_name);
                    perror("Command execution failed");
                    exit(EXIT_FAILURE);
                }
            } else {
                do {
                    waitpid(child_pid, &status, WUNTRACED);
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
            }
        }
    } else {
        /* Non-interactive mode: Read input from pipes or redirected input */
        char input_from_pipe[MAX_INPUT_LENGTH];

        if (fgets(input_from_pipe, sizeof(input_from_pipe), stdin) != NULL) {
            input_from_pipe[strcspn(input_from_pipe, "\n")] = '\0'; /* Remove newline character */

            i = 0;
            tokens[i] = strtok(input_from_pipe, " "); /* Tokenize input */

            while (tokens[i] != NULL && i < MAX_TOKENS - 1) {
                i++;
                tokens[i] = strtok(NULL, " ");
            }

            tokens[i + 1] = NULL;

            child_pid = fork();

            if (child_pid < 0) {
                perror("Fork failed");
                exit(EXIT_FAILURE);
            } else if (child_pid == 0) {
                if (execve(tokens[0], tokens, environ) == -1) {
                    fprintf(stderr, "%s: ", program_name);
                    perror("Command execution failed");
                    exit(EXIT_FAILURE);
                }
            } else {
                do {
                    waitpid(child_pid, &status, WUNTRACED);
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
            }
        }
    }

    return EXIT_SUCCESS;
}
