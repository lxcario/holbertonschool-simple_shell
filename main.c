#include "shell.h"

/**
 * main - Entry point of the simple shell.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: Always 0 (success).
 */
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	shell_loop();
	return (0);
}

