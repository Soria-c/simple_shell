#include "shell.h"
/**
 * div_string - split the string
 *
 * @str: pointer to string
 * Return: NULL or pointer
 */
char **div_string(char *str)
{
	int buffsize = 32;
	int i = 0;
	char **new;
	char *token;

	new = malloc(buffsize * sizeof(char *));
	if (new == NULL)
	{
		free(new);
		return (NULL);
	}
	token = strtok(str, "\t\n");
	while (token != NULL)
	{
		new[i] = token;
		i++;
		if (i >= buffsize)
		{
			buffsize += 32;
			*new = realloc(new, buffsize * sizeof(char *));
			if (new == NULL)
			{
				free(new);
				return (NULL);
			}
		}
		token = strtok(NULL, "\t\n");
	}
	new[i] = NULL;
	return (new);
}
