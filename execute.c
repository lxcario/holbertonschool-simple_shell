#include "shell.h"

/**
 * execute - Executes a command.
 * @args: The command arguments.
 *
 * Return: 1 to continue, 0 to exit.
 */
int execute(char **args)
{
	pid_t pid;
	int status;

	if (args[0] == NULL)
		return (1);
	if (strcmp(args[0], "exit") == 0)
		return (0);

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("execvp");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (1);
}

