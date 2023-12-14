# Simple Shell

## Description

This is a simple Unix command line interpreter created as a project for Holberton School. The shell is capable of handling basic commands, tokenizing user input, executing commands, and displaying a prompt.

## How to Use

1. Compile the shell using the provided Makefile or gcc command.
2. Run the compiled executable `hsh`.
3. Enter commands and press Enter to execute.
4. To exit the shell, use the `exit` command or press Ctrl+D.

## Files

- `simple_shell.c`: Main source code file containing the shell implementation.
- `Simple_Shell.h`: Header file containing function prototypes and definitions.

## Functions

- `tokenize_input`: Tokenizes user input into separate arguments.
- `execute_command`: Executes a command with given arguments.
- `print_prompt`: Displays the shell prompt.

## Compilation

Compile the shell using the provided following command:
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 simple_shell.c -o hsh

## Authors

This project was created by [Thetele Ramoonyane, Makhothi Tlali, Relebohile Ramoshabe] for Holberton School.
