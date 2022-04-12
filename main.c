#include "main.h"
/**
 * money - handles $$ and $?
 * @lin: input line.
 * @xs: exit status of the previous command.
 */
void money(char **lin, int *xs)
{
	int i, ln, m, z, h, x;
	char n[256], cpy[256], *env, buff[1024], buff2[1024], n2[256], *save;

	for (i = 0; (*lin)[i]; i++)
	{
		if ((*lin)[i] == '#' && (*lin)[i - 1] == ' ')
		{
			(*lin)[i] = '\0';
			break;
		}
		if ((*lin)[i] == '$')
		{
			if ((*lin)[i + 1] ==  '?')
			{
				to_string(n2, *xs);
				ln = str_len(n2);
				if (ln)
				str_cat(n2, &(*lin)[i + 2]);
				(*lin) = realloc(*lin, str_len(*lin) + ln + 4);
				(*lin)[i] = '\0';
				str_cat(*lin, n2);
			}
			else if ((*lin)[i + 1] ==  '$')
			{
				to_string(n, getpid());
				ln = str_len(n);
				str_cat(n, &(*lin)[i + 2]);
				(*lin) = realloc(*lin, str_len(*lin) + ln + 4);
				(*lin)[i] = '\0';
				str_cat(*lin, n);
			}
			else
			{
				str_cpy(cpy, &(*lin)[i + 1]);
				for (z = 0; cpy[z] != ' ' && cpy[z]; z++)
					;
				cpy[z] = '\0';
				env = _getenv(cpy);
				if (!env)
				{
					for (h = 0; (*lin)[h + i] != ' ' && (*lin)[h + i]; h++)
						;
					if (!(*lin)[h + i])
					{
						(*lin)[i - 1] = '\0';
						continue;
					}
					for (x = i; (*lin)[x + h]; x++)
						(*lin)[x] = (*lin)[h + x];
					(*lin)[x] = '\0';
					continue;
				}
				for (m = 0; env[m] != '=' && env[m]; m++)
					;
				str_cpy(buff, &env[z + 1]);
				str_cpy(buff2, &(*lin)[i + z + 1]);
				str_cat(buff, buff2);
				save = realloc(*lin, i + str_len(buff) + 1);
				*lin = save;
				(*lin)[i] = '\0';
				str_cat(*lin, buff);
			}
		}
	}
}
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
		money(&lin, &xs);
		fcm = cm = command_builder(lin);
		for (; cm; cm = cm->next)
		{
			exe(cm, c, argv[0], &head, builtins, fcm, lin, &xs);
		}
		free_list(NULL, fcm);
	}
	free_list(head, NULL);
	free(lin);
	return (0);
}



