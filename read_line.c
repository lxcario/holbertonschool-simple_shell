#include "shell.h"

/**
 * read_line - Reads a line of input from stdin.
 *
 * Return: The input line.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	getline(&line, &bufsize, stdin);
	return (line);
}

