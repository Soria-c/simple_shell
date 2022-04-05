#include "main.h"
/**
 * checkex2 - checks if a char is found in a set.
 * @s: set.
 * @s2: char.
 * Return: 1 if s2 is included in s, 0 otherwise.
 */
int checkex2(char *s, char s2)
{
	int i;

	for (i = 0; s[i]; i++)
	{
		if (s2 == s[i])
			return (1);
	}
	return (0);
}

/**
 * iteration - evaluates the source string to tokenize it later.
 * @delim2: address to store the new delimiter.
 * @delim: previous delimiter.
 * @str: source string.
 * @i: counter.
 * @j: counter.
 * @k: counter.
 * Return: address of new delimiter, NULL if malloc fails.
 */
char *iteration(char **delim2, char *delim, char *str, int *i, int *j, int *k)
{
	*delim2 = delimf(delim);
	if (!(*delim2))
		return (NULL);
	for (; checkex2(*delim2, str[*j]) && str[*j]; *j = *j + 1)
		;
	*k = *j;
	for (; !(checkex2(*delim2, str[*j])) && str[*j]; *j = *j + 1)
		;
	for (; checkex2(*delim2, str[*j + *i]) && str[*j + *i]; *i = *i + 1)
		;
	return (*delim2);
}

/**
 * str_tok - implementation of strtok() fron <string.h>.
 * @str: source string.
 * @delim: delimiter.
 * Return: address of new token, NULL if no more tokens are found/malloc fails.
 */
char *str_tok(char *str, char *delim)
{
	int i = 0, j = 0, k = 0, f = 0;
	char *s, *delim2, *mllc;
	static char *save;

	if (str)
	{
		mllc = iteration(&delim2, delim, str, &i, &j, &k);
		if (!mllc)
			return (NULL);
		if (!str[i + j] || !str[j])
			save = NULL;
		else
			save = &str[j + 1];
		str[j] = '\0';
		s = &str[k];
	}
	else if (!str)
	{
		if (!save)
			return (NULL);
		mllc = iteration(&delim2, delim, save, &i, &j, &k);
		if (!mllc)
			return (NULL);
		if (!save[j] || !save[j + i])
			f = 1;
		save[j] = '\0';
		s = &save[k];
		if (f)
			save = NULL;
		else
			save = &save[j + 1];
	}
	free(delim2);
	return (s);
}

/**
 * checkex - checks if a char is found in s for n bytes of s.
 * @s: source delimiter.
 * @s2: char.
 * @n: number of bytes to compare.
 * Return: 1 if s2 is include in s2, 0 otherwise.
 */
int checkex(char *s, char s2, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		if (s[i] == s2)
			return (1);
	}
	return (0);
}

/**
 * delimf - creates a new delimiter without repeated chars.
 * @delim: source delimiter.
 * Return: address of new delimiter, NULL if malloc fails.
 */
char *delimf(char *delim)
{
	int i,  j = 1;
	char s = delim[0];
	char *new;

	new = malloc(sizeof(char) * 32);
	if (!new)
		return (NULL);
	new[0] = delim[0];
	new[1] = '\0';
	for (i = 1; delim[i]; i++)
	{
		if ((delim[i] != s) && !(checkex(delim, delim[i], i)))
		{
			s = delim[i];
			new[j] = delim[i];
			j++;
			new[j] = '\0';
		}
	}
	return (new);
}
