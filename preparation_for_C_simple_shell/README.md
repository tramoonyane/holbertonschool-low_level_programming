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
- Task 2. Simple shell 0.1
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 simple_shell.c helper_file1.c -o hsh
- Task 3. Simple shell 0.2
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 simple_shell_arguments.c helper_file2.c -o hsh
- Task 4. Simple shell 0.3
   gcc -Wall -Werror -Wextra -pedantic -std=gnu89 simple_shell_path.c simple_shell_exit.c -o hsh
- Task 5. Simple shell 0.4
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 simple_shell_path.c simple_shell_exit.c -o hsh
- Task 6. Simple shell 1.0
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 simple_shell_path.c simple_shell_exit.c -o hsh
  
Replace `hsh`with relevant executable names for each task if you wish.

## Authors

This project was created by [Thetele Ramoonyane, Makhothi Tlali, Relebohile Ramoshabe] for Holberton School.
  

  

  
  

