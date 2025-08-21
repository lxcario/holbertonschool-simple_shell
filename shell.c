#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 10

/**
 * main - Simple shell entry point
 * @void: No parameters
 *
 * Return: 0 on success.
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t pid;
    int status;
    char *argv[MAX_ARGS];
    extern char **environ;
    char *token = NULL;
    int i;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("#resqueshell$ ");

        read = getline(&line, &len, stdin);
        
        if (read == -1)
        {
            if (isatty(STDIN_FILENO))
                printf("\n");
            break;
        }

        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        token = strtok(line, " ");

        if (token == NULL)
            continue;
        
        i = 0;
        argv[i] = token;
        i++;
        while (i < MAX_ARGS - 1)
        {
            token = strtok(NULL, " ");
            if (token == NULL)
                break;
            argv[i] = token;
            i++;
        }
        argv[i] = NULL;
        
        pid = fork();
        
        if (pid == -1)
        {
            perror("fork");
            continue;
        }

        if (pid == 0)
        {
            if (execve(argv[0], argv, environ) == -1)
            {
                perror(argv[0]);
                _exit(1);
            }
        }
        else
        {
            if (wait(&status) == -1)
                perror("wait");
        }
    }

    free(line);
    return (0);
}
