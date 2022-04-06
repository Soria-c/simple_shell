#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

/**
 * main - entry point, takes input from user.
 * @argc: number of arguments.
 * @argv: array of arguments.
 * Return: 0
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char *lin = NULL, *wcmd, *tk, *cmd[32];
	size_t n = 0;
	ssize_t r;
	int id, status, i, s, c = 0, b;
	struct stat st;

	_printf("Kali $: ");
	for (; (r = getline(&lin, &n, stdin)) != -1; _printf("Kali $: "))
	{
		c++;
		if (lin[r - 1] == '\n')
			lin[r - 1] = '\0';
		tk = str_tok(lin, " ");
		for (i = 0; tk; tk = str_tok(NULL, " "), i++)
			cmd[i] = tk;
		cmd[i] = NULL;
		b = builtin_check(cmd, lin);
		if (!(*cmd[0]) || !b)
			continue;
		s = stat(cmd[0], &st);
		if (s)
			wcmd = _which(cmd[0]);
		if ((!s) || (s && wcmd))
			id = _fork(s, wcmd);
		else
		{
			free(wcmd);
			printf_error(cmd[0], argv[0], c);
			continue;
		}
		if (!id)
			_execve(cmd);
		else if (id > 0)
			wait(&status);
	}
	free(lin);
	return (0);
}
