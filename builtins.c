#include "main.h"


/**
 * printenv - prints the current environment.
 * @UNUSED: Macro.
 * Return: 0 always.
 */
int printenv(char **cmd UNUSED, char *argv UNUSED)
{
	int i;

	for (i = 0; environ[i]; i++)
		_printf("%s\n", environ[i]);
	return (0);
}

/**
 * ex_it - implementation of the exit shell built in.
 * @cmd: commands.
 * @argv: current name of the program.
 * @stnvf: number of new values allocated in envirion.
 * Return: 0 if it fails, otherwise exits the current shell
 */
int ex_it(char **cmd, char *argv, int *stnvf)
{
	unsigned char e;

	if (array2d_len(cmd) >= 3 && !isnt_digit(cmd[1]))
	{
		_printf("exit\n%s: exit: too many arguments\n", argv);
		return (0);
	}
	else
	{
		if (!cmd[1])
		{
			free(cmd[0]);
			check_env(stnvf);
			write(1, "exit\n", 5);
			exit(0);
		}
		else
		{
			if (isnt_digit(cmd[1]) && cmd[1][0] != '-')
			{
				_printf("exit\n%s: exit: %s:", argv, cmd[1]);
				_printf(" numeric argument required\n");
				check_env(stnvf);
				free(cmd[0]);
				exit(2);
			}
			e = atoi(cmd[1]);
			free(cmd[0]);
			write(1, "exit\n", 5);
			check_env(stnvf);
			exit(e);
		}
	}

	return (0);
}

/**
 * _setenv - sets a new environment variables or rewrites an existing one.
 * @cmd: commands.
 * @argv: current name of the program.
 * @stnvf: number of new values allocated in environ.
 * Return: 0 always.
 */
int _setenv(char **cmd, char *argv, int *stnvf)
{
	int i, j, len1, len2, f = 1;

	if (array2d_len(cmd) != 3)
	{
		_printf("%s: setenv: wrong number of arguments\n", argv);
		_printf("Usage: setenv VARIABLE VALUE\n");
		return (0);
	}
	if (checkex2(cmd[1], '=') || checkex2(cmd[2], '='))
	{
		_printf("%s: setenv: arguments must not contain '='\n", argv);
		return (0);
	}
	len1 = str_len(cmd[1]);
	len2 = str_len(cmd[2]);
	for (i = 0; environ[i]; i++)
	{
		if (!(strn_cmp(cmd[1], environ[i], len1)))
		{
			if (environ[i][str_len(environ[i]) + 1] == 'f')
				f = 0;
			for (j = 0; environ[i][j] != '='; j++)
				;
			environ[i][j + 1] = '\0';
			str_cat(environ[i], cmd[2]);
			if (!f)
				environ[i][len1 + len2 + 2] = 'f';
			return (0);
		}
	}
	environ[i] = malloc(sizeof(char) * 1024 * 8);
	*stnvf = *stnvf + 1;
	str_cpy(environ[i], cmd[1]);
	environ[i][len1] = '=';
	environ[i][len1 + 1] = '\0';
	str_cat(environ[i], cmd[2]);
	environ[i][len1 + len2 + 2] = 'f';
	environ[i + 1] = NULL;
	return (0);
}

/**
 * _unsetenv - unsets and environment variable.
 * @cmd: commands.
 * @argv: current name of the program.
 * @stvnf: number of new values allocated in environ.
 * Return: 0 always.
 */
int _unsetenv(char **cmd, char *argv __attribute__((unused)), int *stvnf)
{
	int i;
	char *f = NULL;

	if (array2d_len(cmd) != 2)
	{
		_printf("%s: unsetenv: wrong number of arguments\n", argv);
		_printf("Usage: unsetenv VARIABLE\n");
		return (0);
	}
	for (i = 0; environ[i]; i++)
	{
		if (!(strn_cmp(cmd[1], environ[i], str_len(cmd[1]))))
		{
			if (environ[i][str_len(environ[i]) + 1] == 'f')
				f = environ[i];
			environ[i] = "";
			break;
		}
	}
	if (!environ[i])
	{
		_printf("%s: unsetenv: %s not found\n", argv, cmd[1]);
		return (0);
	}
	for (; environ[i]; i++)
		environ[i] = environ[i + 1];
	if (f)
	{
		*stvnf = *stvnf - 1;
		free(f);
	}
	return (0);
}
