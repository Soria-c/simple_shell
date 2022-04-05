#include "main.h"
extern char **environ; /*cambiar por env*/

char *str_cat(char *dest, char *src)
{
	int j, i;

	j = str_len(dest);
	for (i = 0; *(src + i); i++)
		*(dest + (j + i)) = *(src + i);
	*(dest + (j + i)) = '\0';
	return (dest);
}
char *str_cpy(char *dest, char *src)
{
	int i, j;

	i = str_len(src);
	for (j = 0; j < i; j++)
		*(dest + j) = *(src + j);
	*(dest + j) = '\0';
	return (dest);
}
int str_len(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
		continue;
	return (i);
}
char *_getenv(char *name)
{
	unsigned int i;

	for (i = 0; environ[i] && name; i++)
	{
		if (!(strn_cmp(name, environ[i], str_len(name))))
			return (environ[i]);
	}
	return (NULL);
}

char *_which(char *cmd)
{
	char *s, **path, *tk, *cat;
	char *ar;
	int i, j;
	struct stat st;

	if (!cmd)
		return (NULL);
	path = malloc(sizeof(char) * 1024);
	ar = malloc(str_len(cmd) + 2);
	ar[0] = '/';
	ar[1] = '\0';
	ar = str_cat(ar, cmd);
	s = _getenv("PATH");
	tk = str_tok(s, ":");
	for (i = 0; tk; i++, tk = str_tok(NULL, ":"))
		path[i] = tk;
	path[i] = NULL;
	for (j = 0;path[j];j++)
	{
		cat = malloc(str_len(path[j]) + str_len(ar) + 1);
		cat = str_cpy(cat, path[j]);
		cat = str_cat(cat, ar);
		if (stat(cat, &st) == 0)
		{
			free(ar);
			free(path);
			return(cat);
		}
		free(cat);
	}
	free(ar);
	free(path);
	return (NULL);
}
