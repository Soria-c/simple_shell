#include "main.h"

/**
 * command_builder - classifies commands from s and adds
 * them to the cmds linked list.
 * @s: input taken from getline.
 * Return: address of linked list.
 */

cmds *command_builder(char *s)
{
	char *tok;
	cmds *head0, *h, *new0, *prev0;
	int i;

	new0 = malloc(sizeof(cmds));
	new0->sline = str_tok(s, ";");
	prev0 = head0 = new0;
	new0->next = NULL;
	for (; (tok = str_tok(NULL, ";")); prev0 = new0)
	{
		new0 = malloc(sizeof(cmds));
		prev0->next = new0;
		new0->sline = tok;
		new0->next = NULL;
	}
	h = head0;
	h->cmd[0] = str_tok(h->sline, " \t");
	for (;; h->cmd[0] = str_tok(h->sline, " \t"))
	{
		for (i = 1; (h->cmd[i] = str_tok(NULL, " \t")); i++)
			;
		h = h->next;
		if (!h)
			break;
	}
	return (head0);
}

/**
 * exe - executes all commands from the cm linked list.
 * @cm: commands linked list, at each iteration the address will change.
 * @c: counts the number of times the prompt has been printed.
 * @argv: current name of the program.
 * @head: linked list of some strings created by malloc.
 * @f: Head of the commands linked list.
 * @bins: struct countaining pointers to builtin functions
 * @l: address of input line.
 */
void exe(cmds *cm, int c, char *argv, f_s **head, b_i *bins, cmds *f, char *l)
{
	struct stat st;
	int s, id;
	char *wcmd;

	if (!*(cm->cmd[0]) || !bin_chck(cm->cmd, bins, argv, head, f, l))
		return;
	s = stat(cm->cmd[0], &st);
	if (s)
		wcmd = _which(cm->cmd[0]);
	else if (check_route(cm->cmd[0]))
	{
		printf_error(cm->cmd[0], argv, c);
		return;
	}
	if ((!s) || (s && wcmd))
		id = _fork(s, wcmd);
	else
	{
		free(wcmd);
		printf_error(cm->cmd[0], argv, c);
		return;
	}
	if (!id)
		_execve(cm->cmd, argv, c, head, f, l);
	else if (id > 0)
		wait(NULL);
	else
		write(STDERR_FILENO, "Could not create process\n", 25);
}
/**
 * check_route - checks validity of a route
 * @cmd: command
 * Return: 1 if route is invalid, 0 otherwise.
 */
int check_route(char *cmd)
{
	int k, len = str_len(cmd);


	if (!strn_cmp(cmd, "/usr/bin", 8))
	{
		if (len <= 9)
			return (1);

		for (k = 9; cmd[k] == '/' && cmd[k]; k++)
			;
		if (!cmd[k])
			return (1);

	}
	if (str_len(cmd) <= 5)
		return (1);

		for (k = 5; cmd[k] == '/' && cmd[k]; k++)
			;
		if (!cmd[k])
			return (1);
	return (0);
}
