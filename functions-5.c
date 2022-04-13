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
	h->cmd[0] = str_tok(h->sline, " >\t");
	for (;; h->cmd[0] = str_tok(h->sline, " \t"))
	{
		for (i = 1; (h->cmd[i] = str_tok(NULL, " >\t")); i++)
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
 * @a: current name of the program.
 * @h: linked list of some strings created by malloc.
 * @f: Head of the commands linked list.
 * @bi: struct countaining pointers to builtin functions
 * @l: address of input line.
 * @xs: exit status of the previous command
 */
void exe(cmds *cm, int c, char *a, f_s **h, b_i *bi, cmds *f, char *l, int *xs)
{
	struct stat st;
	int s, id, k;
	char *wcmd;

	if (!*(cm->cmd[0]) || !bin_chck(cm->cmd, bi, a, h, f, l, xs))
		return;
	s = lstat(cm->cmd[0], &st);
	if (s || (!s && (strn_cmp(cm->cmd[0], "/bin", 4) || strn_cmp(cm->cmd[0], "/usr/bin", 8))))
		wcmd = _which(cm->cmd[0]);
	if ((!s && (!strn_cmp(cm->cmd[0], "/bin", 4) || !strn_cmp(cm->cmd[0], "/usr/bin", 8))) || (s && wcmd))
		id = _fork(s, wcmd);
	else
	{
		free(wcmd);
		printf_error(cm->cmd[0], a, c, xs);
		return;
	}
	if (!id)
		_execve(cm->cmd, a, c, h, f, l, xs);
	else if (id > 0)
	{
		waitpid(id, &k, 0);
		if (WIFEXITED(k))
			*xs = WEXITSTATUS(k);
	}
	else
		write(STDERR_FILENO, "Could not create process\n", 25);
}

