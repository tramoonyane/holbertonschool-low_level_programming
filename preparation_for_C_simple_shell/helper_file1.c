
/**
 * is_input_terminal - Checks if input is coming from a terminal
 *
 * Return: 1 if input is from a terminal, 0 otherwise
 */
int is_input_terminal(void)
{
return (isatty(fileno((stdin))));
}
