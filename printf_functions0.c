#include "main.h"

/**
 * fs_init - helps calculate possible size of final string when %c = NULL
 * @s: address of format string
 * @args: arguments
 *
 * Return: size of final string where there is %c = NULL.
 */

int fs_init(char *s, va_list args)
{
	int i, j;
	char *s2;
	va_list args3;

	va_copy(args3, args);
	s2 = s;
	j = 0;
	for (i = 0; s2[i] != '\0'; i++)
	{
		if (s2[i] == '%')
		{
			if (s2[i + 1] == 'c')
			{
				if (va_arg(args3, int) == '\0')
					j++;
			}
			else if (s2[i + 1] == 'd' || s2[i + 1] == 'i')
				va_arg(args3, int);
			else if (s2[i + 1] == 's')
				va_arg(args3, char *);
		}
	}
	va_end(args3);
	return (j);
}

/**
 * _printf - prints a formatted string
 * @format: imput string
 * @mod: number of the file descriptor.
 * Return: number of bytes if is SUCCESS, -1 otherwise.
 */

int _printf(int mod, const char *format, ...)
{
	va_list args;
	char *f_check, init[2048];
	int i, lenght, bytes, s, total;

	if (!format)
		return (-1);
	f_check = (char *)format;
	lenght = str_len(f_check);
	va_start(args, format);
	total = fs_init(f_check, args);
	for (i = 0; *f_check != '%' && *f_check != 0; i++, f_check++)
		continue;
	if (i == lenght)
	{
		write(mod, format, lenght);
		va_end(args);
		return (lenght);
	}
	else
	{
		s = fs(format, init, f_check, i, args, 0, 0);
		va_end(args);
	}
	bytes = str_len(init);
	write(mod, init, bytes + total);
	if (s == 3)
		return (bytes + total);
	if (s == -1)
		return (-1);
	return (bytes);
}

/**
 * to_string - transforms an integer into string
 * @n: input integer
 * @s: address of string to store converter integer
 *
 * Return: void
 */

void to_string(char *s, int n)
{
	int i, f = 0;
	unsigned long t = 10, n2 = n;

	if (n == 0)
	{
		s[0] = n + '0';
		s[1] = '\0';
		return;
	}
	if (n < 0)
	{
		n2 = -n2;
		f = 1;
	}
	for (i = 0; (n2 / (t / 10)) != 0; i++)
	{
		s[i] = ((n2 % t) / (t / 10)) + '0';
		t *= 10;
	}
	if (f == 1)
	{
		s[i] = '-';
		s[i + 1] = '\0';
	}
	else
		s[i] = '\0';
	str_rev(s);
}

/**
 * str_rev - reverses a string
 * @s: input string
 *
 * Return: void
 */

void str_rev(char *s)
{
	int j, k = 0;
	char m;

	j = str_len(s);
	for (j = j - 1; k < j; j--, k++)
	{
		m = *(s + j);
		*(s + j) = *(s + k);
		*(s + k) = m;
	}
}
