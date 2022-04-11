#include "shell.h"
/**
 * main - function executed by the shell
 *
 * @argc: argument count
 * @argv: argument vector
 * Return: 0
 */
int main(int argc __attribute__((unused)), char *argv[])
{
	char *lineptr = NULL;
	char **args  = NULL;
	size_t n = 0;

	if (isatty(STDIN_FILENO) == 1)
		print_prompt(PROMPT);
	while (getline(&lineptr, &n, stdin) != -1)
	{
		args = div_string(lineptr);
		function_execute(args, argv);
		if (isatty(STDIN_FILENO) == 1)
			print_prompt(PROMPT);
	}
	free(args);
	free(lineptr);
	return (0);
}
/**
 * print_prompt - prints at the prompt
 *
 * @prompt: pointer to input
 */
void print_prompt(char *prompt)
{
	write(STDOUT_FILENO, prompt, 2);
}
