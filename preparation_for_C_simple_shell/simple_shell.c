#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void prompt() {
    printf("#cisfun$ ");
}

int main(void) {
    char buffer[BUFFER_SIZE];
    char *argv[2];

    while (1) {
        prompt();

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            printf("\n");
            break;  // End of file (Ctrl+D)
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        pid_t pid = fork();

        if (pid == -1) {
            perror("Error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            argv[0] = buffer;
            argv[1] = NULL;

            if (execve(argv[0], argv, NULL) == -1) {
                perror("Error");
                exit(EXIT_FAILURE);
            }
        } else {
            wait(NULL);
        }
    }

    return EXIT_SUCCESS;
}
