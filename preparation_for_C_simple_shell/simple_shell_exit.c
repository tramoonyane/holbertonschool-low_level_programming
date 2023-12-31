/* simple_shell_arguments.c some sort of a back up file */

#include "Shell.h"

/**
 * parse_path - Tokenizes the PATH environment variable into directories.
 *
 * Return: Returns an array of directories.
 */
char **parse_path(void)
{
    char *path = get_path();
    char *path_copy = strdup(path);
    char **directories = allocate_directories(1);

    char *token = strtok(path_copy, ":");
    int count = 0;

    while (token != NULL)
    {
        add_directory(&directories, token, count++);
        token = strtok(NULL, ":");
    }

    directories = realloc(directories, (count + 1) * sizeof(char *));
    if (directories == NULL)
    {
        perror("realloc error");
        exit(EXIT_FAILURE);
    }
    directories[count] = NULL;

    free(path_copy);
    return directories;
}

/**
 * add_directory - Adds a directory to the directories array.
 *
 * @directories: Pointer to the array of directories.
 * @token: The directory string to be added.
 * @count: Index of the directory being added.
 */
void add_directory(char ***directories, char *token, int count)
{
    *directories = realloc(*directories, (count + 1) * sizeof(char *));
    if (*directories == NULL)
    {
        perror("realloc error");
        exit(EXIT_FAILURE);
    }
    (*directories)[count] = token;
}

/**
 * allocate_directories - Allocates memory for the directories array.
 *
 * @size: Size of the array to be allocated.
 * Return: Pointer to the newly allocated array of directories.
 */
char **allocate_directories(int size)
{
    char **directories = malloc(size * sizeof(char *));
    if (directories == NULL)
    {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }
    return directories;
}

/**
 * get_path - Retrieves the PATH environment variable.
 *
 * Return: Pointer to the PATH environment variable string.
 */
char *get_path(void)
{
    char *path = getenv("PATH");

    if (path == NULL || *path == '\0')
    {
        fprintf(stderr, "No PATH variable found or empty.\n");
        exit(EXIT_FAILURE);
    }
    return path;
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
 * count_arguments - Counts the number of arguments in a command.
 *
 * @command: The command to analyze.
 *
 * Return: Returns the number of arguments.
 */
int count_arguments(char *command)
{
int arg_count = 1; /* Initial count for command itself */
char *p;

for (p = command; *p != '\0'; ++p)
{
if (*p == ' ')
{
arg_count++;
while (*p == ' ') /* Skip consecutive spaces */
p++;
}
}
return (arg_count);
}

/**
 * get_command_arguments - Splits the command into arguments.
 *
 * @command: The command to split.
 * @arg_count: Number of arguments in the command.
 *
 * Return: Returns an array of command arguments.
 */
char **get_command_arguments(char *command, int arg_count)
{
char **args;
int i = 0;

args = malloc((arg_count + 1) * sizeof(char *));
if (args == NULL)
{
perror("malloc error");
exit(EXIT_FAILURE);
}
args[i++] = strtok(command, " \n"); /* Get the command */
while
((args[i++] = strtok(NULL, " \n")) != NULL);
return (args);
}

/**
 * execute_command_with_path - Executes the command with full path.
 *
 * @args: Array of command arguments.
 * @command_number: Number of the command in the shell session.
 * @program_name: The name of the shell program.
 */
void execute_command_with_path(char **args,
int command_number, char *program_name)
{
pid_t pid;
int status;
char **directories = parse_path();
int found = 0;
int i;

for (i = 0; directories[i] != NULL; i++)
{
char path_command[BUFFER_SIZE];

snprintf(path_command, sizeof(path_command), "%s/%s", directories[i], args[0]);
/* Check if the command is executable at the given path */
if (access(path_command, X_OK) == 0)
{
found = 1;
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
fprintf(stderr, "%s: %d: %s: not found\n",
program_name, command_number, args[0]);
exit(EXIT_FAILURE);
}
}
else
{
/* Parent process */
waitpid(pid, &status, 0);
}
break;
}
}
if (!found)
{
fprintf(stderr, "%s: %d: %s: not found\n",
program_name, command_number, args[0]);
}
free(directories);
}
