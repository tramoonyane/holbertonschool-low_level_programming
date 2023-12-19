/* simple_shell.c */
#include "Simple_Shell.h"

extern char **environ; /* Declaration of environ variable */

/**
 * main - Entry point for the simple shell
 *
 * Description: Displays a prompt, reads a command from the user, and executes
 *              it using execve. This shell handles single-word commands without arguments.
 *              It uses fork(), execve(), and waits for the child process to finish.
 *
 * Return: Always returns 0.
 */
int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    int status;
    pid_t pid;

    while (1)
    {
        printf("$ ");
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            printf("\n");
            break; /* Ctrl+D (EOF) is pressed */
        }

        /* Remove newline character */
        command[strcspn(command, "\n")] = '\0';

        /* Forking a child process */
        pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) /* Child process */
        {
            char **args = malloc(sizeof(char *) * 2);
            if (args == NULL)
            {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
            args[0] = command;
            args[1] = NULL;

            if (execve(command, args, environ) == -1)
            {
                fprintf(stderr, "Error: Command not found: %s\n", command);
                free(args);
                exit(EXIT_FAILURE);
            }
            free(args);
        }
        else /* Parent process */
        {
            waitpid(pid, &status, 0);

            if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            {
                fprintf(stderr, "Error: Command execution failed\n");
            }
        }
    }

    return 0;
}

/**
 * execute_command - Executes the command entered by the user
 * @command: The command to be executed
 *
 * Description: This function executes the specified command using fork(),
 *              execve(), and waits for the child process to finish.
 *              It displays error messages if the command execution fails.
 *
 * Return: Void
 */
void execute_command(char *command) {
    int status;
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { /* Child process */
        char *token, *path, *full_path;
        path = getenv("PATH");
        full_path = malloc(strlen(path) + strlen(command) + 2); // +2 for '/' and null terminator
        if (full_path == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        
        token = strtok(path, ":");
        while (token != NULL) {
            strcpy(full_path, token);
            strcat(full_path, "/");
            strcat(full_path, command);
            if (access(full_path, X_OK) == 0) {
                char **args = malloc(sizeof(char *) * 2);
                if (args == NULL) {
                    perror("Memory allocation failed");
                    exit(EXIT_FAILURE);
                }
                args[0] = full_path;
                args[1] = NULL;

                if (execve(full_path, args, environ) == -1) {
                    fprintf(stderr, "Error: Command execution failed\n");
                    free(args);
                    exit(EXIT_FAILURE);
                }
                free(args);
            }
            token = strtok(NULL, ":");
        }

        fprintf(stderr, "Error: Command not found: %s\n", command);
        free(full_path);
        exit(EXIT_FAILURE);
    } else { /* Parent process */
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            fprintf(stderr, "Error: Command execution failed\n");
        }
    }
}
