#include "main.h"

/**
 * p - copies args in f
 * @fm: input string
 * @f: buffer
 * @x: number of bytes before %
 * @a: arguments list
 * @o: operation number
 * @z: offset
 * @w: flag
 * @s: string to copy.
 * Return: -1 is special in f_sel is triggered, 0 otherwise.
 */

int p(const char *fm, char *f, char *s, int x, va_list a, int o, int z, int w)
{
	int copy, i, j, k, r;
	char *f_check; /**string*/

	r = 0;
	for (copy = 0; copy < x; copy++)
		f[copy] = fm[z + copy];
	/*string = va_arg(arg, char *);*/
	if (s == NULL)
		s = "(null)";
	for (k = 0; s[k] != '\0'; k++)
		f[copy + k] = s[k];
	j = copy + k;
	for (; fm[copy + z + o + 1] != '\0'; copy++)
		f[copy + k] = fm[copy + z + o + 1];
	f[copy + k] = '\0';
	f = f + j;
	f_check = f;
	for (i = 0; *f_check != '%' && *f_check != 0; i++, f_check++)
		continue;
	z = z + x + o + 1;
	r = fs(fm, f, f_check, i, a, z, w);
	if (r == -1)
		return (r);
	return (r);
}

/**
 * pc - copies args in f
 * @fm: input string
 * @f: buffer
 * @x: number of bytes before %
 * @a: arguments list
 * @o: operation number
 * @z: offset
 * @w: flag
 * @c: char to copy.
 * Return: -1 is special in f_sel is triggered, 0 otherwise.
 */

int pc(const char *fm, char *f, char c, int x, va_list a, int o, int z, int w)
{
	int copy, i, j, r, fl;
	char *f_check;

	j = r = fl = 0;
	for (copy = 0; copy < x; copy++)
		f[copy] = fm[z + copy];
	if (c)
		f[copy] = c;
	else
	{
		fl = 3;
		f--;
	}
	j = copy + 1;
	for (; fm[copy + z + o + 1] != '\0'; copy++)
		f[copy + 1] = fm[copy + z + o + 1];
	f[copy + 1] = '\0';
	f = f + j;
	f_check = f;
	for (i = 0; *f_check != '%' && *f_check != 0; i++, f_check++)
		continue;
	z = z + x + o + 1;
	r = fs(fm, f, f_check, i, a, z, w);
	if (fl == 3)
		return (3);
	if (r == -1)
		return (r);
	return (r);
}

/**
 * pv - copies args in f
 * @format: input string
 * @f: buffer
 * @sz: number of bytes before %
 * @arg: arguments list
 * @op: operation number
 * @z: offset
 * @w: flag
 *
 * Return: -1 is special in f_sel is triggered, 0 otherwise.
 */

int pv(const char *format, char *f, int sz, va_list arg, int op, int z, int w)
{
	int copy, i, j, r;
	char *f_check;

	j = r = 0;
	for (copy = 0; copy < sz; copy++)
		f[copy] = format[z + copy];
	f[copy] = format[z + copy];
	j = copy;
	if (format[z + copy + 1] == ' ')
		r = 1;
	for (; format[copy + z + op - r] != '\0'; copy++)
		f[copy + 1] = format[copy + z + op - r];
	f[copy + 1] = '\0';
	f = f + j + 2 + r;
	f_check = f;
	for (i = 0; *f_check != '%' && *f_check != 0; i++, f_check++)
		continue;
	z = z + sz + op + 1;
	w = 1;
	fs(format, f, f_check, i, arg, z, w);
	return (0);
}

/**
 * fs - selects format case
 * @format: input string
 * @fs: buffer
 * @s: address of first incidence of % in fs
 * @sz: number of bytes before %
 * @a: arguments list
 * @z: offset
 * @w: flag
 *
 * Return: 0 if f_sel is SUCCESS and 1 otherwise.
 */

int fs(const char *format, char *fs, char *s, int sz, va_list a, int z, int w)
{
	int op, r;
	char *str, str2[20], chr = '%';

	if (*s == '\0')
		return (0);
	for (op = 1; s[op] < '!' && s[op] != '\0'; op++)
		;
	if (w == 1)
		w = 2;
	if (!s[op] || ((s[op] > 47 && s[op] < 58) && !s[op + 1]))
	{
		if (w == 2)
			return (0);
		r = check(fs, s, &op, sz);
		if (r == -1)
			return (-1);
	}
	switch (s[op])
	{
		case 'c':
			chr = va_arg(a, int);
			r = pc(format, fs, chr, sz, a, op, z, w);
			break;
		case 'd':
		case 'i':
			to_string(str2, va_arg(a, int));
			r = ps(format, fs, str2, sz, a, op, z, w);
			break;
		case '%':
			r = pc(format, fs, chr, sz, a, op, z, w);
			break;
		case 's':
			str = va_arg(a, char *);
			r = ps(format, fs, str, sz, a, op, z, w);
			break;
		default:
			r = pv(format, fs, sz, a, op, z, w);
	}
	if (r == -1)
		return (-1);
	return (r); }

/**
 * check - checks special case of %
 * @fs: buffer
 * @s: address of first incidence of % in fs
 * @op: pointer to op
 * @sz: number of bytes before %
 * Return: -1 if special case exists, 0 if not
 */

int check(char *fs, char *s, int *op, int sz)
{
	for (*op = 0; s[*op + 1] < '!' && s[*op + 1] != '\0'; *op = *op + 1)
		;
	if (s[*op + 1] == '\0')
	{
		fs[sz] = '\0';
		return (-1);
	}
	if ((s[*op + 1] > 47 && s[*op + 1] < 58) && (!s[*op + 2]))
	{
		fs[sz] = '\0';
		return (-1);
	}
	return (0);
}
