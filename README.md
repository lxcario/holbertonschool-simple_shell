# holbertonschool-simple_shell
Write a simple UNIX command interpreter.

![](https://s3.amazonaws.com/intranet-projects-files/holbertonschool-low_level_programming/235/shell.jpeg)
****
## Table of contents
 - **What is the shell?**
 - **About this project**
 - **Essential Functionalities of the Simple Shell**
 - **File description**
 - **List of allowed functions and system calls for this project**
 - **USAGE**
 - **Example of Usage**
 - **Bugs**
 - **TEAM**
 ****

## What is the shell?
The shell is a program that takes commands from the keyboard via the terminal, and gives them to the operating system to perform.\
**To better understand how the shell actually works, you can read our [Article].**

## About this project
This project is a simple version of the linux shell made for [Holberton School] taking part of the "Low-level programming & Algorithm - Linux and Unix system programming" projects.\
It is created using the **C programming Language** and it can do many functionalities that a real shell does.

## Essential Functionalities of the Simple Shell:
> Displays a prompt "#cisfun$ " and waits for user input.\
> Runs all commands of type "executable program" (ls and /bin/ls).\
> Runs the following build_in commands: **exit**, **env**, **setenv** and **unsetenv**.\
> Handles commands with arguments.\
> Handles the PATH global variable.\
> Handles The EOF (End Of File) condition.\
> Handles the Ctrl + C signal -> It doesn't exit the shell

## Files description
 - **AUTHORS** -> List of contributors to this repository
 - **man_1_simple_shell** -> Manual page for the simple_shell
 - **shell.h** -> Header file
 - **shell.c** -> main function
	- **sig_handler** -> handles the Ctrl + C signal
	- **_EOF** -> handles the End Of File condition
 - **string.c**
	- **_putchar** -> prints a character
	- **_puts** -> prints a string
	- **_strlen** -> gives the length of a string
	- **_strdup** -> copies a string in a newly allocated memory
	- **concat_all** -> concatenates 3 strings in a newly allocated memory
 - **line_exec.c**
	- **splitstring** -> splits a string into an array of words
	- **execute** -> executes a command using execve
	- **realloc** -> reallocates a memory block
	- **freearv** -> frees a 2 dimensional array
 - **linkpath.c**
	- **_getenv** -> returns the value of a global variable
	- **add_node_end** -> adds a node in a singly linked list
	- **linkpath** -> creates a singly linked list for PATH directories
	- **_which** -> finds the pathname of a command
	- **free_list** -> frees the linked list of PATH value
 - **checkbuild.c**
	- **checkbuild** -> checks if a command is a build-in command
 - **buildin.c**
	- **exitt** -> handles the exit buildin command
	- **_atoi** -> converts a string into an integer
	- **env** -> prints the current environment
	- **_setenv** -> Initialize a new global variable, or modify an existing one
	- **_unsetenv** -> remove a global variable
 
More Info
---------

### Output

-   Unless specified otherwise, your program **must have the exact same output** as `sh` (`/bin/sh`) as well as the exact same error output.
-   The only difference is when you print an error, the name of the program must be equivalent to your `argv[0]` (See below)

Example of error with `sh`:

```
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$

```

Same error with your program `hsh`:

```
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$

```

****
## List of allowed functions and system calls for this project
 - access (man 2 access)
 - chdir (man 2 chdir)
 - close (man 2 close)
 - closedir (man 3 closedir)
 - execve (man 2 execve)
 - exit (man 3 exit)
 - _exit (man 2 _exit)
 - fflush (man 3 fflush)
 - fork (man 2 fork)
 - free (man 3 free)
 - getcwd (man 3 getcwd)
 - getline (man 3 getline)
 - isatty (man 3 isatty)
 - kill (man 2 kill)
 - malloc (man 3 malloc)
 - open (man 2 open)
 - opendir (man 3 opendir)
 - perror (man 3 perror)
 - read (man 2 read)
 - readdir (man 3 readdir)
 - signal (man 2 signal)
 - stat (__xstat) (man 2 stat)
 - lstat (__lxstat) (man 2 lstat)
 - fstat (__fxstat) (man 2 fstat)
 - strtok (man 3 strtok)
 - wait (man 2 wait)
 - waitpid (man 2 waitpid)
 - wait3 (man 2 wait3)
 - wait4 (man 2 wait4)
 - write (man 2 write)
****

## USAGE
You can try our shell by following these steps:
> **Step 1:** Clone our repository using this command, (you need to have git installed on your machine first)
````
git clone https://github.com/MatriMariem/simple_shell
````
> **Step 2:** Change directory to simple_shell:
````
cd simple_shell
````
> **Step 3:** Compile the C files in this way:
````
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
````
> **Step 4:** Run the shell
````
./hsh
````
**Exiting the shell**
When you want to exit the shell, you can use one of the following methods:
> **1: Type the command "exit"**
````
exit
````
> **2: Press on Ctrl + D**

## Bugs
No bugs (:
