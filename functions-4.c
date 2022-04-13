#include "main.h"

/**
 * _prompt - prints a prompt in the command line
 */
void _prompt(void)
{
	if (isatty(STDIN_FILENO))
		_printf(STDOUT_FILENO, "Kali $: ");
}

/**
 * c_lnkdlist - creates and updates linked list.
 * @head: address of head.
 * @s: new value to add.
 */
void c_lnkdlist(f_s **head, char *s)
{
	f_s *new;

	new = malloc(sizeof(f_s));
	new->str = s;
	new->next = *head;
	(*head) = new;
}

/**
 * free_list - frees linked lists.
 * @head: address of malloc strings linked list.
 * @head0: address of commands linked list.
 */
void free_list(f_s *head, cmds *head0)
{
	f_s *s;
	cmds *tmp;

	for (; head; free(s->str), free(s))
	{
		s = head;
		head = head->next;
	}

	for (; head0; head0 = head0->next, free(tmp))
		tmp = head0;
}

/**
 * handler - executes when SINGINT is catch.
 * @num: integer sent by signal().
 */
void handler(int num __attribute__((unused)))
{
	write(STDOUT_FILENO, "\n", 1);
	_prompt();
}

/**
 * cd_set - helper function for _cd, when "cd" and "cd -"/
 * @cd: commands for cd.
 * @c_dir: array to store name of current directory.
 * @p_dir: array to store name of previous directory.
 * @arv: current name of the program.
 * @head: address of linked list.
 * @n: flag, 0 if the case is "cd -", 1 for "cd".
 */
void cd_set(char **cd, char *c_dir, char *p_dir, char *arv, f_s **head, int n)
{
		int i;

		if (!n)
		{
			if (_getenv("OLDPWD"))
			{
				c_dir = getcwd(NULL, 0);
				p_dir = _getenv("OLDPWD");
				for (i = 0; p_dir[i] != '='; i++)
					;
				chdir(&p_dir[i + 1]);
				cd[1] = "PWD";
				cd[2] = &p_dir[i + 1];
				_setenv(cd, arv, head);
				cd[1] = "OLDPWD";
				cd[2] = c_dir;
				_setenv(cd, arv, head);
				free(c_dir);
			}
		}
		else
		{
			if (_getenv("HOME"))
			{
				c_dir = _getenv("HOME");
				for (i = 0; c_dir[i] != '='; i++)
					;
				chdir(&c_dir[i + 1]);
				cd[1] = "PWD";
				cd[2] = &c_dir[i + 1];
				_setenv(cd, arv, head);
				free(p_dir);
			}
		}
}
