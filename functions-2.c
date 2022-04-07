#include "main.h"

/**
 * strn_cmp - implementation of strncmp() from <string.h>.
 * @s1: string1.
 * @s2: string2.
 * @n: bytes to compare.
 * Return: 0 if s1 = s2 for n bytes, any number otherwise.
 */
int strn_cmp(char *s1, char *s2, int n)
{
	int i;

	for (i = 0; (!(s1[i] - s2[i]) && (s1[i])) && (i < n); i++)
		;
	return (n - i);
}
/**
 * _fork - executes fork(), frees wcmd if needed.
 * @s: return value from stat().
 * @wcmd: return value from wcmd.
 * Return: same as fork().
 */
int _fork(int s, char *wcmd)
{
	if (s)
		free(wcmd);
	return (fork());
}

/**
 * _execve - executes command from user.
 * @cmd: commands.
 */
void _execve(char **cmd)
{
	int rexc;
	char *wcmd;

	rexc = execve(cmd[0], cmd, NULL);
	if (rexc == -1)
	{
		wcmd = _which(cmd[0]);
		cmd[0] = wcmd;
		execve(wcmd, cmd, NULL);
	}
}
/**
 * printf_error - prints error
 * @cmd: command.
 * @argv: name of the program
 * @c: number of times the prompt has been printed.
 */
void printf_error(char *cmd, char *argv, int c)
{
	_printf("%s: %d: %s: not found\n", argv, c, cmd);
}

/**
 * builtin_check - checks for built in functions.
 * @cmd: commands.
 * @builtins: array of built in structs.
 * @argv: current name of the program.
 * @stnvf: number of new values allocated in environ.
 * Return: 0 if a built in is found, 1 otherwise
 */
int builtin_check(char **cmd, b_i *builtins, char *argv, int *stnvf)
{
	int r = 1, i;

	for (i = 0; builtins[i].name; i++)
	{
		if (!(str_cmp(cmd[0], builtins[i].name)))
		{
			if (!str_cmp(cmd[0], "exit") || !str_cmp(cmd[0], "setenv"))
				r = builtins[i].func_ex(cmd, argv, stnvf);
			else
				r = builtins[i].func_ptr(cmd, argv);
			}
	}
	return (r);
}
