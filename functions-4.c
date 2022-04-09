#include "main.h"

/**
 * _prompt - prints a prompt in the command line
 */
void _prompt(void)
{
	if (isatty(STDIN_FILENO))
		_printf("Kali $: ");
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
 * free_list - frees a list_t list.
 * @head: address of linked list.
 */
void free_list(f_s *head)
{
	f_s *s;

	for (; head; free(s->str), free(s))
	{
		s = head;
		head = head->next;
	}
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
