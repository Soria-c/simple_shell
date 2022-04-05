#include "main.h"

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
char *str_tok(char *str, char *delim)
{
	unsigned int i, j = 0, k, f = 0;
	char *s, *delim2;
	static char *save;

	if (str)
	{
		delim2 = delimf(delim);
		for (; checkex2(delim2, str[j]) && str[j]; j++)
			continue;
		k = j;
		for (; !(checkex2(delim2, str[j]) && str[j]); j++)
			continue;
		str[j] = '\0';
		save = &str[j + 1];
		s = &str[k];
	}
	else if (!str)
	{
		if (!save)
			return (NULL);
		delim2 = delimf(delim);
		for (; checkex2(delim2, save[j]) && save[j]; j++)
			continue;
		k = j;
		for (; !(checkex2(delim2, save[j])) && save[j]; j++)
			continue;
		if (!save[j])
			f = 1;
		else if (checkex2(delim2, save[j]) && save[j])
		{
			for (i = 1; checkex2(delim2, save[j + i]) && save[j + i]; i++)
				;
			if (!save[j + i])
				f = 1;
			save[j] = '\0';
		}
		else
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
char *delimf(char *delim)
{
	int i,  j = 1;
	char s = delim[0];
	char *new;

	new = malloc(sizeof(char) * 32);

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
int strn_cmp(char *s1, char *s2, int n)
{
	int i;

	for (i = 0; (!(s1[i] - s2[i]) && (s1[i])) && (i < n); i++)
		continue;
	return (n - i);
}
