#include "main.h"

/**
 * printenv - prints the current environment
 */
void printenv(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		_printf("%s\n", environ[i]);
}

