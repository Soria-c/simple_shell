#include "main.h"

/**
 * str_cat - implementation of strcat() from <string.h>.
 * @dest: target string.
 * @src: source string.
 * Return: address modified target string.
 */
char *str_cat(char *dest, char *src)
{
	int j, i;

	j = str_len(dest);
	for (i = 0; *(src + i); i++)
		*(dest + (j + i)) = *(src + i);
	*(dest + (j + i)) = '\0';
	return (dest);
}

/**
 * str_cpy - implementation of strcpy() from <string.h>.
 * @dest: target array to store src.
 * @src: source string.
 * Return: address of copied string.
 */
char *str_cpy(char *dest, char *src)
{
	int i, j;

	i = str_len(src);
	for (j = 0; j < i; j++)
		*(dest + j) = *(src + j);
	*(dest + j) = '\0';
	return (dest);
}

/**
 * str_len - implementation of strlen() from <string.h>.
 * @s: source string.
 * Return: lenght of s.
 */
int str_len(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
		continue;
	return (i);
}

/**
 * _getenv - implementation of getenv() from <stdlib.h>.
 * @name: name of the environment variable.
 * Return: address of the variable, NULL if not found.
 */
char *_getenv(char *name)
{
	unsigned int i, j;
	char save[1024];

	for (i = 0; environ[i] && name && *name; i++)
	{
		for (j = 0; environ[i][j] != '='; j++)
			save[j] = environ[i][j];
		save[j] = '\0';
		if (!(strn_cmp(name, save, str_len(save))))
			return (environ[i]);
	}
	return (NULL);
}

/**
 * _which - simple implementation of the which shell command.
 * @cmd: command.
 * Return: directory in the path, NULL if not found or malloc fails.
 */
char *_which(char *cmd)
{
	char s[8192], *path[8192], *tk, *cat, *ar;
	int i, j, k;
	struct stat st;

	for (k = 0; cmd[k] != '/' && cmd[k]; k++)
		;
	if (cmd[k])
		return (NULL);
	ar = malloc(str_len(cmd) + 2);
	ar[0] = '/';
	ar[1] = '\0';
	ar = str_cat(ar, cmd);
	if (_getenv("PATH"))
	{
		str_cpy(s, _getenv("PATH"));
		tk = str_tok(s, ":=");
		for (i = 0; tk; i++, tk = str_tok(NULL, ":"))
			path[i] = tk;
		path[i] = NULL;
		for (j = 0; path[j]; j++)
		{
			cat = malloc(str_len(path[j]) + str_len(ar) + 1);
			if (!cat)
			{
				free(ar);
				return (NULL);
			}
			cat = str_cpy(cat, path[j]);
			cat = str_cat(cat, ar);
			if (!stat(cat, &st))
			{
				free(ar);
				return (cat);
			}
		free(cat);
		}
	}
	free(ar);
	return (NULL);
}
