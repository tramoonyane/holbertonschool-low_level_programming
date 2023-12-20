# Simple Shell

## Description

This project is a Unix command line interpreter created as a Holberton School assignment. The shell can handle basic commands, tokenize user input, execute commands, and display a prompt. It encompasses functionalities developed across multiple files to meet various task requirements.

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

## Functions

- `tokenize_input`: Tokenizes user input into separate arguments.
- `execute_command`: Executes a command with given arguments.
- `print_prompt`: Displays the shell prompt.
- Other functions specific to different functionalities across files.

## Compilation

Compile each file for the respective task using specific commands (similar to provided examples):
- Simple shell 0.1 version
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 simple_shell.c helper_file1.c -o hsh
- ... (continue for each version)

Replace `hsh` with relevant executable names for each task if needed.

## Authors

This project was completed by Thetele Ramoonyane, Makhothi Tlali, and Relebohile Ramoshabe for Holberton School.
