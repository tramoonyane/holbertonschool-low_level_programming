# Simple Shell

## Description

This is a simple Unix command line interpreter created as a project for Holberton School. The shell is capable of handling basic commands, tokenizing user input, executing commands, and displaying a prompt. It includes functionalities developed across multiple files to meet different task requirements.

## How to Use

1. Compile the shell for each task separately using the provided gcc commands (specific to each task).
2. Run the compiled executable for each task.
3. Enter commands and press Enter to execute.
4. To exit the shell, use the `exit` command or press Ctrl+D.

## Files

- `simple_shell.c`: Main source code file containing the basic shell implementation.
- `Simple_Shell.h`: Header file containing function prototypes and definitions.
- `simple_shell_arguments.c`: File implementing command line argument handling.
- `simple_shell_path.c`: File managing command execution with PATH handling.
- `simple_shell_exit.c`: File implementing the exit built-in command.
- `simple_shell_env.c`: File implementing the env built-in command.

## Functions

- `tokenize_input`: Tokenizes user input into separate arguments.
- `execute_command`: Executes a command with given arguments.
- `print_prompt`: Displays the shell prompt.
- Other functions specific to different functionalities across files.

## Compilation

Compile each file for the respective task using specific commands (similar to provided examples):
- Simple shell 0.1 version
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 simple_shell.c helper_file1.c -o hsh
- Simple shell 0.2 version
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 simple_shell_commands.c simple_shell_arguments.c simple_shell_path.c Shell_built-in.c main.c -o hsh
- Simple shell 0.3 version
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 simple_shell_commands.c simple_shell_arguments.c simple_shell_path.c Shell_built-in.c main.c -o hsh
- Simple shell 0.4 version
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 simple_shell_commands.c simple_shell_arguments.c simple_shell_path.c Shell_built-in.c main.c -o hsh
- Simple shell 1.0 version
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 simple_shell_commands.c simple_shell_arguments.c simple_shell_path.c Shell_built-in.c main.c -o hsh
  
Replace `hsh`with relevant executable names for each task if you wish.

## Authors

This project was done by [Thetele Ramoonyane, Makhothi Tlali, Relebohile Ramoshabe] for Holberton School.
  
