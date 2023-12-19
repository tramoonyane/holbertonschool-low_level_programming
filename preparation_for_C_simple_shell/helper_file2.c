/* helper_file1.c */

#include "Simple_Shell.h"

/**
 * is_input_terminal - Checks if input is coming from a terminal
 *
 * Return: 1 if input is from a terminal, 0 otherwise
 */
int is_input_terminal(void)
{
return (isatty(fileno((stdin))));
}

/**
 * get_user_input - Retrieves user input from stdin
 *
 * Return: A pointer to the user input string.
 *
 * Description: This function reads user input
 * from standard input (stdin)
 * and returns the input as a string,
 * removing the newline character if present.
 */
char *get_user_input()
{
char input[MAX_INPUT_LENGTH];
if (fgets(input, sizeof(input), stdin) != NULL)
{
input[strcspn(input, "\n")] = '\0'; /* Remove newline character */
return (strdup(input));
}
return (NULL);
}

/**
 * parse_arguments - Parses command line arguments.
 * @input: The input string containing command and arguments.
 *
 * Return: A pointer to an array of tokens (strings).
 *
 * Description: This function tokenizes the input string
 * based on space delimiter and returns an array of tokens
 * obtained from the input (command and arguments).
 */
char **parse_arguments(char *input) {
    int i = 0;
    char **tokens = malloc(MAX_TOKENS * sizeof(char *));
    if (tokens == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    tokens[i] = strtok(input, " "); /* Tokenize input */
    while (tokens[i] != NULL && i < MAX_TOKENS - 1) {
        i++;
        tokens[i] = strtok(NULL, " ");
    }
    tokens[i + 1] = NULL;
    return tokens;
}
/**
 * execute_env_command - Print the current environment variables.
 *
 * Description: This function prints the current environment variables.
 * It accesses the global variable 'environ' containing the environment
 * variable pointers and iterates through them to print each variable.
 */
void execute_env_command() {
    char *env_cmd = "/bin/env";

    pid_t child_pid;
    int status;

    printf("Executing command: %s\n", env_cmd);

    child_pid = fork();
    if (child_pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        char **env_argv = malloc(2 * sizeof(char *));
        if (env_argv == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        
        env_argv[0] = env_cmd;
        env_argv[1] = NULL;
        
        if (execve(env_cmd, env_argv, environ) == -1) {
            fprintf(stderr, "Error executing command: %s\n", env_cmd);
            perror("Command execution failed");
            exit(EXIT_FAILURE);
        }
        
        free(env_argv); /* Free allocated memory */
    } else {
        do {
            waitpid(child_pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

/**
 * execute_with_arguments - Executes a command with arguments using execve.
 * @tokens: An array of command tokens (command and arguments).
 * @program_name: The name of the program.
 *
 * Description: This function executes a command with arguments
 * using the execve system call with the given tokens and program name.
 * It forks a child process to execute the command.
 */
void execute_with_arguments(char **tokens, char *program_name) {
    pid_t child_pid;
    int status;

    printf("Command: %s\n", tokens[0]); /* Debug print */

    child_pid = fork();
    if (child_pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        if (strcmp(tokens[0], "env") == 0) {
            execute_env_command(); /* Call the function to handle 'env' command */
            exit(EXIT_SUCCESS); /* Exit the child process after executing 'env' */
        } else if (access(tokens[0], F_OK) == 0) {
            if (execve(tokens[0], tokens, environ) == -1) {
                fprintf(stderr, "%s: ", program_name);
                perror("Command execution failed");
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "%s: command not found\n", tokens[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        do {
            waitpid(child_pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}
