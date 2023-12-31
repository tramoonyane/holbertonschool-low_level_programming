#include "main.h"
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

/**
 * append_text_to_file - appends text_content to the end of a file
 * @filename: the name of the file
 * @text_content: a NULL terminated string to append to the file
 * Return: 1 on success, -1 on failure
 */
int append_text_to_file(const char *filename, char *text_content)
{
int file_descriptor, write_status, close_status;

if (filename == NULL)
return (-1);
if (text_content == NULL)
return (1);
file_descriptor = open(filename, O_WRONLY | O_APPEND);
if (file_descriptor == -1)
return (-1);
write_status = write(file_descriptor, text_content, strlen(text_content));
if (write_status == -1)
{
close(file_descriptor);
return (-1);
}
close_status = close(file_descriptor);
if (close_status == -1)
return (-1);
return (1);
}
