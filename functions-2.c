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
 * @argv: current name of the program.
 * @c: program prompt counter.
 * @head: address of malloc string linked list to be freed is necessary.
│* @f: address of linked list cm to be freed if necessary.
 */
void _execve(char **cmd, char *argv, int c, f_s **head, cmds *f)
{
	int rexc;
	char *wcmd;

	rexc = execve(cmd[0], cmd, environ);
	if (rexc == -1)
	{
		wcmd = _which(cmd[0]);
		rexc = execve(wcmd, cmd, environ);
		if (rexc == -1)
		{
			printf_error(cmd[0], argv, c);
			free(f->cmd[0]);
			free_list(*head, f);
			free(wcmd);
			_exit(127);
		}
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
	_printf(STDERR_FILENO, "%s: %d: %s: not found\n", argv, c, cmd);
}

/**
 * builtin_check - checks for built in functions.
 * @cmd: commands.
 * @builtins: array of built in structs.
 * @argv: current name of the program.
 * @head: address of malloc strings linked list.
 * @f: address of commands linked list.
 * Return: 0 if a built in is found, 1 otherwise
 */
int builtin_check(char **cmd, b_i *builtins, char *argv, f_s **head, cmds *f)
{
	int r = 1, i;

	for (i = 0; builtins[i].name; i++)
	{
		if (!(str_cmp(cmd[0], builtins[i].name)))
		{
			if	(!str_cmp(cmd[0], "setenv") || !str_cmp(cmd[0], "cd"))
				r = builtins[i].func_lst(cmd, argv, head);
			else if (!str_cmp(cmd[0], "exit"))
				r = builtins[i].func_ex(cmd, argv, head, f);
			else
				r = builtins[i].func_ptr(cmd, argv);
		}
	}
	return (r);
}
