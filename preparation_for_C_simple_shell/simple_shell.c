#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_TOKENS 100

extern char **environ;  // Access to the environment variables

/**
 * main - Simple Shell
 *
 * Return: Always 0
 */
int main(void)
{
    char input[MAX_INPUT_LENGTH];
    char *tokens[MAX_TOKENS];
    pid_t child_pid;
    int status;

    while (1)
    {
        printf("$ "); /* Display prompt */
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            if (feof(stdin))
            {
                printf("\n"); /* Print newline after Ctrl+D */
                break; /* Exit on EOF */
            }
        }

        input[strcspn(input, "\n")] = '\0'; /* Remove newline character */

        child_pid = fork();

        if (child_pid < 0)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else if (child_pid == 0)
        {
            int i = 0;
            tokens[i] = strtok(input, " "); /* Tokenize input */

            while (tokens[i] != NULL && i < MAX_TOKENS - 1)
            {
                i++;
                tokens[i] = strtok(NULL, " ");
            }

            tokens[i + 1] = NULL;

            if (execve(tokens[0], tokens, environ) == -1)
            {
                perror("Command execution failed");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            do
            {
                waitpid(child_pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }

    return EXIT_SUCCESS;
}
