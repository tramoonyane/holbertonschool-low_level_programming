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
void execute_command(char *command)
{
    int status;
    pid_t pid = fork();

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
