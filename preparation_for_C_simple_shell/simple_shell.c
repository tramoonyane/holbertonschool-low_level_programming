#include "Simple_Shell.h"

void prompt() {
    printf("($)\n$ ");
    fflush(stdout); /* Flush the output buffer */
}

int main(void) {
    char buffer[BUFFER_SIZE];
    char *argv[2];
    pid_t pid;

    char *program_name = "./hsh"; /* Change this accordingly if your executable has a different name */

    while (1) {
        prompt();

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            printf("\n");
            break;  /* End of file (Ctrl+D) */
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        pid = fork();

        if (pid == -1) {
            perror(program_name);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            argv[0] = buffer;
            argv[1] = NULL;

            if (execve(argv[0], argv, NULL) == -1) {
                perror(program_name);
                exit(EXIT_FAILURE);
            }
        } else {
            wait(NULL);
            prompt(); /* Print the prompt after executing the command */
        }
    }

    return EXIT_SUCCESS;
}
