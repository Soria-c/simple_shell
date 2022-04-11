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
 * exec_all - executes all commands from the cm linked list.
 * @cm: commands linked list, at each iteration the address will change.
 * @c: counts the number of times the prompt has been printed.
 * @argv: current name of the program.
 * @head: linked list of some strings created by malloc.
 * @f: Head of the commands linked list.
 * @builtins: struct countaining pointers to builtin functions
 */
void exec_all(cmds *cm, int c, char *argv, f_s **head, b_i *builtins, cmds *f)
{
	struct stat st;
	int s, id;
	char *wcmd;

	if (!*(cm->cmd[0]) || !builtin_check(cm->cmd, builtins, argv, head, f))
		return;
	s = stat(cm->cmd[0], &st);
	if (s)
		wcmd = _which(cm->cmd[0]);
	if ((!s) || (s && wcmd))
		id = _fork(s, wcmd);
	else
	{
		free(wcmd);
		printf_error(cm->cmd[0], argv, c);
		return;
	}
	if (!id)
		_execve(cm->cmd, argv, c, head, f);
	else if (id > 0)
		wait(NULL);
	else
		write(STDERR_FILENO, "Could not create process\n", 25);
}
