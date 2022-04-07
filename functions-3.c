#include "main.h"

/**
 * str_cmp - implementation of strcmp() from <string.h>.
 * @s1: string.
 * @s2: string.
 * Return: 0 if s1 == s2, 1 otherwise
 */
int str_cmp(char *s1, char *s2)
{
	int i;

	for (i = 0; !(s1[i] - s2[i]) && s1[i] && s2[i]; i++)
		;
	if (!s1[i] && !s2[i])
		return (0);
	return (1);
}

/**
 * isnt_digit - checks is there is not a digit in s.
 * @s: string.
 * Return: 0 if s is made up only from digits, 1 otherwise
 */
int isnt_digit(char *s)
{
	int i;

	for (i = 0; (s[i] >= '0' && s[i] <= '9') && s[i]; i++)
		;
	if (!s[i])
		return (0);
	return (1);
}

/**
 * array2d_len - computes the lenght of a 2d array.
 * @a: 2d array.
 * Return: lenght of 2d array.
 */
int array2d_len(char **a)
{
	int i;

	for (i = 0; a[i]; i++)
		;
	return (i);
}
/**
 * check_env - checks the environ array and frees if needed.
 * @stnvf: number of new value allocated in envrion.
 */
void check_env(int *stnvf)
{
	int i;

	if (*stnvf)
	{
		for (i = array2d_len(environ) - *stnvf; environ[i]; i++)
		free(environ[i]);
	}
}
