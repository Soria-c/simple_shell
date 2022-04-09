#include "main.h"

/**
 * main - entry point, takes input from user.
 * @argc: number of arguments.
 * @argv: array of arguments.
 * Return: 0
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char *lin = NULL, *wcmd = NULL, *tk = NULL, *cmd[256];
	size_t n = 0;
	f_s *head = NULL;
	int id, i, s = 1, c = 0, r;
	struct stat st;
	b_i builtins[] = {{"exit", NULL, ex_it}, {"env", printenv, NULL},
	{"setenv", NULL, _setenv}, {"unsetenv", _unsetenv, NULL},
	{"cd", NULL, _cd}, {NULL, NULL, NULL}};

	signal(SIGINT, handler);
	for (_prompt(); (r = getline(&lin, &n, stdin)) != -1; _prompt())
	{
		c++;
		if (lin[r - 1] == '\n')
			lin[r - 1] = '\0';
		tk = str_tok(lin, " \t");
		for (i = 0; tk; tk = str_tok(NULL, " \t"), i++)
			cmd[i] = tk;
		cmd[i] = NULL;
		if (!(*cmd[0]) || !builtin_check(cmd, builtins, argv[0], &head))
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
			wait(NULL);
	}
	free_list(head);
	free(lin);
	return (0);
}

