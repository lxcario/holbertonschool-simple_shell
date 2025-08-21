#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

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
    char *argv[2];
    extern char **environ;

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

        while (isspace((unsigned char)*line))
        {
            line++;
        }

        if (strlen(line) == 0)
        {
            continue;
        }

        char *end = line + strlen(line) - 1;
        while (end >= line && isspace((unsigned char)*end))
        {
            *end = '\0';
            end--;
        }

        pid = fork();
        
        if (pid == -1)
        {
            perror("fork");
            continue;
        }

        if (pid == 0)
        {
            argv[0] = line;
            argv[1] = NULL;
            
            if (execve(argv[0], argv, environ) == -1)
            {
                perror(line);
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
