#include "shell.h"

/**
 * shell_loop - The main loop of the shell.
 */
void shell_loop(void)
{
	char *line;
	char **args;
	int status = 1;

	while (status)
	{
		write(STDOUT_FILENO, "$ ", 2);
		line = read_line();
		args = split_line(line);
		status = execute(args);

		free(line);
		free(args);
	}
}

