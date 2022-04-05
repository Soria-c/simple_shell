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
 */
void printf_error(char *cmd, char *argv)
{
	write(STDOUT_FILENO, argv, str_len(argv));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, cmd, str_len(cmd));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "command not found\n", 18);
}
