#include "main.h"

/**
 * printenv - prints the current environment.
 * @c: commands.
 * @a: current name of the program.
 * Return: 0 always.
 */
int printenv(char **c __attribute__((unused)), char *a __attribute__((unused)))
{
	int i;

	for (i = 0; environ[i]; i++)
		_printf(STDOUT_FILENO, "%s\n", environ[i]);
	return (0);
}

/**
 * ex_it - implementation of the exit shell built in.
 * @cmd: commands.
 * @argv: current name of the program.
 * @head: address of malloc string linked list to be freed is necessary.
 * @f: address of linked list cm to be freed if necessary
 * @l: address of input line, to be freed if necessary.
 * Return: 0 if it fails, otherwise exits the current shell
 */
int ex_it(char **cmd, char *argv __attribute__((unused))
, f_s **head, cmds *f, char *l)
{
	unsigned char e;

	if (array2d_len(cmd) >= 3 && !isnt_digit(cmd[1]))
	{
		return (0);
	}
	else
	{
		if (!cmd[1])
		{
			free(l);
			free_list(*head, f);
			exit(0);
		}
		if ((isnt_digit(cmd[1]) && cmd[1][0] != '-') || isnt_digit(&cmd[1][1]))
		{
			return (0);
		}
		e = _atoi(cmd[1]);
		free(l);
		free_list(*head, f);
		exit(e);
	}
	return (0);
}

/**
 * _setenv - sets a new environment variables or rewrites an existing one.
 * @cmd: commands.
 * @argv: current name of the program.
 * @head: address of linked list.
 * Return: 0 always.
 */
int _setenv(char **cmd, char *argv, f_s **head)
{
	int i, j, len1, len2, lenenv;

	if (array2d_len(cmd) != 3)
	{
		_printf(STDERR_FILENO, "%s: setenv: wrong number of arguments\n", argv);
		_printf(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n");
		return (0);
	}
	if (checkex2(cmd[1], '=') || checkex2(cmd[2], '='))
	{
		_printf(STDERR_FILENO, "%s: setenv: arguments must not contain '='\n", argv);
		return (0);
	}
	len1 = str_len(cmd[1]);
	len2 = str_len(cmd[2]);
	for (i = 0; environ[i]; i++)
	{
		if (!(strn_cmp(cmd[1], environ[i], len1)))
		{
			lenenv = str_len(environ[i]);
			if (lenenv < len1 + len2 + 1)
				setenv_help(&environ[i], len1, len2, cmd, head);
			else
			{
				for (j = 0; environ[i][j] != '='; j++)
					;
				environ[i][j + 1] = '\0';
				str_cat(environ[i], cmd[2]);
			}
			return (0);
		}
	}
	setenv_help(&environ[i], len1, len2, cmd, head);
	environ[i + 1] = NULL;
	return (0);
}

/**
 * _unsetenv - unsets and environment variable.
 * @cmd: commands.
 * @argv: current name of the program.
 * Return: 0 always.
 */
int _unsetenv(char **cmd, char *argv __attribute__((unused)))
{
	int i;

	if (array2d_len(cmd) != 2)
	{
		_printf(STDERR_FILENO, "%s: unsetenv: wrong number of arguments\n", argv);
		_printf(STDERR_FILENO, "Usage: unsetenv VARIABLE\n");
		return (0);
	}
	for (i = 0; environ[i]; i++)
	{
		if (!(strn_cmp(cmd[1], environ[i], str_len(cmd[1]))))
			break;
	}
	if (!environ[i])
	{
		_printf(STDERR_FILENO, "%s: unsetenv: %s not found\n", argv, cmd[1]);
		return (0);
	}
	for (; environ[i]; i++)
		environ[i] = environ[i + 1];
	return (0);
}

/**
 * _cd - implementation of the cd shell built in.
 * @cmd: commands.
 * @argv: current name of the program.
 * @head: address of linked list.i
 * Return: 0 always.
 */
int _cd(char **cmd, char *argv, f_s **head)
{
	char *c_dir = NULL, *p_dir = NULL, *cdcmd[4];

	cdcmd[0] = cmd[0];
	cdcmd[3] = NULL;
	if (array2d_len(cmd) > 2)
	{
		_printf(STDERR_FILENO, "%s: cd: too many arguments\n", argv);
		_printf(STDERR_FILENO, "Usage: cd [DIRECTORY]\n");
		return (0);
	}
	if (cmd[1] && str_len(cmd[1]) == 1 && cmd[1][0] == '-')
	{
		cd_set(cdcmd, c_dir, p_dir, argv, head, 0);
		return (0);
	}
	p_dir = getcwd(NULL, 0);
	if (cmd[1] && chdir(cmd[1]))
	{
		_printf(STDERR_FILENO, "%s: cd: %s: ", argv, cmd[1]);
		_printf(STDERR_FILENO, "No such file or directory\n");
		free(p_dir);
		return (0);
	}
	else
	{
		cdcmd[1] = "OLDPWD";
		cdcmd[2] = p_dir;
		_setenv(cdcmd, argv, head);
	}
	if (!cmd[1])
	{
		cd_set(cdcmd, c_dir, p_dir, argv, head, 1);
		return (0);
	}
	c_dir = getcwd(NULL, 0);
	cdcmd[1] = "PWD";
	cdcmd[2] = c_dir;
	_setenv(cdcmd, argv, head);
	free(c_dir), free(p_dir);
	return (0);
}
