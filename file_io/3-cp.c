#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 1024
#define PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)

/**
 * print_error - Prints error messages and
 * exits the program with the given code
 * @code: Exit code
 * @message: Error message
 * @filename: Name of the file causing the error
 * @fd: File descriptor value
 */
void print_error(int code, char *message, char *filename, int fd)
{
dprintf(STDERR_FILENO, "%s %s", message, filename);
if (fd != -1)
dprintf(STDERR_FILENO, " fd %d", fd);
dprintf(STDERR_FILENO, "\n");
exit(code);
}

/**
 * main - Copies the content of one file to another file
 * @argc: Number of arguments
 * @argv: Array of arguments
 * Return: 0 on success, 97, 98, 99, or 100 on error
 */
int main(int argc, char *argv[]) {
    int fd_from, fd_to, bytes_read, bytes_written;
    char buffer[BUF_SIZE];

    if (argc != 3) {
        dprintf(STDERR_FILENO, "Usage: %s file_from file_to\n", argv[0]);
        return (97);
    }

    fd_from = open(argv[1], O_RDONLY);
    if (fd_from == -1)
        print_error(98, "Error: Can't read from file", argv[1], -1);

    fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, PERMS);
    if (fd_to == -1)
        print_error(99, "Error: Can't write to file", argv[2], -1);

    while ((bytes_read = read(fd_from, buffer, BUF_SIZE)) > 0) {
        bytes_written = write(fd_to, buffer, bytes_read);
        if (bytes_written != bytes_read)
            print_error(99, "Error: Can't write to file", argv[2], fd_to);
    }

    if (bytes_read == -1)
        print_error(98, "Error: Can't read from file", argv[1], fd_from);

    if (close(fd_from) == -1 || close(fd_to) == -1)
        print_error(100, "Error: Can't close fd", "", -1);

    return (0);
}
