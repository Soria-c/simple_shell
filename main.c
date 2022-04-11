#include "main.h"

/**
 * main - entry point, takes input from user.
 * @argc: number of arguments.
 * @argv: array of arguments.
 * Return: 0
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char *lin = NULL;
	size_t n = 0;
	f_s *head = NULL;
	int c = 0, r, xs = 0;
	cmds *cm, *fcm;
	b_i builtins[] = {{"exit", NULL, NULL, ex_it},
			{"env", printenv, NULL, NULL},
			{"setenv", NULL, _setenv, NULL},
			{"unsetenv", _unsetenv, NULL, NULL},
			{"cd", NULL, _cd, NULL},
			{NULL, NULL, NULL, NULL}};

	signal(SIGINT, handler);
	for (_prompt(); (r = getline(&lin, &n, stdin)) != -1; _prompt())
	{
		c++;
		if (lin[r - 1] == '\n')
			lin[r - 1] = '\0';
		fcm = cm = command_builder(lin);
		for (; cm; cm = cm->next)
			exe(cm, c, argv[0], &head, builtins, fcm, lin, &xs);
		free_list(NULL, fcm);
	}
	free_list(head, NULL);
	free(lin);
	return (0);
}



