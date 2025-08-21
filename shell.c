#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_ARGS 10

/**
 * find_executable - Finds the full path of an executable in the PATH.
 * @command: The command name to find.
 *
 * Return: The full path of the executable, or NULL if not found.
 */
char *find_executable(char *command)
{
    char *path_env = NULL;
    char *path_copy;
    char *dir;
    char *full_path;
    struct stat st;
    int i = 0;
    
    extern char **environ;

    while (environ[i] != NULL)
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
        {
            path_env = environ[i] + 5;
            break;
        }
        i++;
    }

    if (path_env == NULL || path_env[0] == '\0') /* Check if PATH is NULL or empty */
    {
        return (NULL);
    }

    path_copy = strdup(path_env);
    if (path_copy == NULL)
        return (NULL);

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (full_path == NULL)
        {
            free(path_copy);
            return (NULL);
        }
        strcpy(full_path, dir);
        strcat(full_path, "/");
        strcat(full_path, command);

        if (stat(full_path, &st) == 0 && (S_ISREG(st.st_mode) || S_ISLNK(st.st_mode)))
        {
            free(path_copy);
            return (full_path);
        }
        
        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}

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
    char *executable_path = NULL;

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
        {
            continue;
        }
        
        i = 0;
        argv[i] = token;
        i++;
        while ((token = strtok(NULL, " ")) != NULL && i < MAX_ARGS - 1)
        {
            argv[i] = token;
            i++;
        }
        argv[i] = NULL;
        
        if (strchr(argv[0], '/') != NULL)
        {
            executable_path = argv[0];
        }
        else
        {
            executable_path = find_executable(argv[0]);
        }

        if (executable_path == NULL)
        {
            perror(argv[0]);
            continue;
        }

        pid = fork();
        
        if (pid == -1)
        {
            perror("fork");
            if (executable_path != argv[0])
                free(executable_path);
            continue;
        }

        if (pid == 0)
        {
            if (execve(executable_path, argv, environ) == -1)
            {
                perror(executable_path);
                if (executable_path != argv[0])
                    free(executable_path);
                _exit(1);
            }
        }
        else
        {
            if (wait(&status) == -1)
                perror("wait");
            if (executable_path != argv[0])
                free(executable_path);
        }
    }

    free(line);
    return (0);
}

