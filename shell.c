#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Simple shell entry point
 * @void: No parameters
 *
 * Return: 0 on success.
 */
int main(void)
{
    char *line = NULL;
    char *trimmed_line = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t pid;
    int status;
    char *argv[2];
    extern char **environ;
    char *end = NULL;

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

        trimmed_line = line;

        while (*trimmed_line == ' ' || *trimmed_line == '\t' || *trimmed_line == '\n')
        {
            trimmed_line++;
        }

        if (strlen(trimmed_line) == 0)
        {
            continue;
        }

        end = trimmed_line + strlen(trimmed_line) - 1;
        while (end >= trimmed_line && (*end == ' ' || *end == '\t' || *end == '\n'))
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
            argv[0] = trimmed_line;
            argv[1] = NULL;
            
            if (execve(argv[0], argv, environ) == -1)
            {
                perror(trimmed_line);
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
