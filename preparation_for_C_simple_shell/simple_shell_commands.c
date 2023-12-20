/* simple_shell_commands.c */

#include "Shell.h"

/**
 * read_command - Reads a command from standard input.
 *
 * Return: Returns the input command as a dynamically allocated string.
 */
char *read_command(void)
{
char *command;
char input[BUFFER_SIZE];

if (fgets(input, BUFFER_SIZE, stdin) == NULL)
{
if (feof(stdin))
{
write(STDOUT_FILENO, "\n", 1);
exit(EXIT_SUCCESS);
}
else
{
perror("fgets error");
exit(EXIT_FAILURE);
}
}
input[strcspn(input, "\n")] = '\0';
command = strdup(input);
if (command == NULL)
{
perror("strdup error");
exit(EXIT_FAILURE);
}
return (command);
}

/**
 * execute_command - Executes the command with arguments.
 *
 * @command: The command to execute.
 * @command_number: Number of the command in the shell session.
 * @program_name: The name of the shell program.
 *
 * Return: Returns EXIT_SUCCESS upon successful execution.
 */
int execute_command(char *command, int command_number, char *program_name)
{
char **args;
int arg_count;

if (command == NULL || *command == '\0')
{
return (EXIT_SUCCESS); /* Skip execution for empty commands */
}
arg_count = count_arguments(command);
args = get_command_arguments(command, arg_count);
execute_command_with_path(args, command_number, program_name);
free(args);
return (EXIT_SUCCESS);
}

/**
 * execute_command_with_path - Execute command by searching through
 * directories in PATH
 * This function attempts to execute a command by searching through directories
 * listed in the PATH environment variable. It constructs
 * the full path to the command
 * and checks if it is executable. If found, it executes the command using
 * execute_found_command(); otherwise, it handles the command not being found.
 *
 * @args: Array of command arguments.
 * @command_number: Number of the command in the shell session.
 * @program_name: The name of the shell program.
 */
void execute_command_with_path(char **args, int command_number,
char *program_name)
{
char **directories = parse_path();
int found = 0;
int i;

for (i = 0; directories[i] != NULL; i++)
{
char path_command[BUFFER_SIZE];

snprintf(path_command, sizeof(path_command), "%s/%s", directories[i], args[0]);
if (access(path_command, X_OK) == 0)
{
found = 1;
execute_found_command(args, command_number, program_name, path_command);
break;
}
}
handle_command_not_found(found, args[0], command_number, program_name);
free(directories);
}

/**
 * execute_found_command - Executes the found command in a child process.
 *
 * This function forks a child process and attempts to execute
 * the given command.
 * It utilizes the execv system call to execute the command and waits for the
 * child process to finish execution before returning to the parent process.
 *
 * @args: Array of command arguments.
 * @command_number: Number of the command in the shell session.
 * @program_name: The name of the shell program.
 * @path_command: The path to the command to be executed.
 */
void execute_found_command(char **args, int command_number,
char *program_name, const char *path_command)
{
pid_t pid;
int status;

pid = fork();
if (pid == -1)
{
perror("fork error");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
/* Child process */
if (execv(path_command, args) == -1)
{
fprintf(stderr, "%s: %d: %s: not found\n", program_name, command_number, args[0]);
exit(EXIT_FAILURE);
}
}
else
{
/* Parent process */
waitpid(pid, &status, 0);
}
}

/**
 * handle_command_not_found - Handles scenario when the command is not found.
 *
 * This function prints an error message to stderr if the command is not found
 * based on the 'found' flag.
 *
 * @found: Indicates if the command was found (1) or not (0).
 * @command: The command that was not found.
 * @command_number: Number of the command in the shell session.
 * @program_name: The name of the shell program.
 */
void handle_command_not_found(int found, const char *command, int command_number, const char *program_name)
{
if (!found)
{
fprintf(stderr, "%s: %d: %s: not found\n", program_name, command_number, command);
}
}
