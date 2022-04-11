#include "shell.h"
/**
 * function_execute - function that creates and executes a process
 *
 * @args: pointer to string
 * @argv: argument vector
 * Return: 1
 */
int function_execute(char **args, char **argv)
{
	pid_t id;
	int status;

	id = fork();
	if (id == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			printf("%s: No such file or directory\n", argv[0]);
		}
		exit(98);
	}
	else if (id < 0)
	{
		printf("Error");
	}
	else
	{
		wait(&status);
	}
	return (1);
}
