#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - Simple command-line interpreter
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	extern char **environ;

	while (1)
	{
		printf("#resqueshell$ ");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			printf("\n");
			break;
		}
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		if (line[0] == '\0')
			continue;
		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}
		if (pid == 0)
		{
			char *argv[] = {line, NULL};
			execve(line, argv, environ);
			fprintf(stderr, "Error: %s not found\n", line);
			free(line);
			exit(1);
		}
		else
		{
			wait(NULL);
		}
	}
	free(line);
	return 0;
}
