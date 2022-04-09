#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <signal.h>

/**
 * struct f_string - linked list to store malloc created strings.
 * @str: address of a string created by malloc.
 * @next: next struct.
 */
typedef struct f_string
{
	char *str;
	struct f_string *next;
} f_s;

/**
 * struct built_ins - struct to store built ins.
 * @name: name of the built in.
 * @func_ptr: function pointer.
 * @func_lst: function pointer.
 */
typedef struct built_ins
{
	char *name;
	int (*func_ptr)(char **cmd, char *argv);
	int (*func_lst)(char **cmd, char *argv, f_s **head);
} b_i;

extern char **environ;
#define UNUSED __attribute__((unused))

void handler(int num UNUSED);
void setenv_help(char **env, int len1, int len2, char **cmd, f_s **head);
void _prompt(void);
void c_lnkdlist(f_s **head, char *s);
void cd_set(char **cd, char *c_dir, char *p_dir, char *arv, f_s **head, int i);
void free_list(f_s *head);
int _setenv(char **cmd, char *argv, f_s **head);
int _unsetenv(char **cmd, char *argv);
int array2d_len(char **a);
int str_cmp(char *s1, char *s2);
int ex_it(char **cmd, char *argv, f_s **head);
int isnt_digit(char *s);
int builtin_check(char **cmd, b_i *builtins, char *argv, f_s **head);
int printenv(char **cmd, char *argv);
void printf_error(char *cmd, char *argv, int c);
void _execve(char **cmd, char *argv, int c);
int _fork(int s, char *wcmd);
char *iteration(char **delim2, char *delim, char *str, int *i, int *j, int *k);
int strn_cmp(char *s1, char *s2, int n);
char *str_cat(char *dest, char *src);
char *str_cpy(char *dest, char *src);
int str_len(char *s);
char *_getenv(char *name);
void free_grid(char **grid);
char *_which(char *cmd);
char *delimf(char *delim);
int checkex2(char *s, char s2);
int checkex(char *s, char s2, int n);
char *str_tok(char *str, char *delim);
int _printf(const char *format, ...);
int fs(const char *format, char *fs, char *s, int sz, va_list a, int z, int w);
int pc(const char *fm, char *f, char c, int x, va_list a, int o, int z, int w);
int p(const char *fm, char *f, char *s, int x, va_list a, int o, int z, int w);
int pv(const char *format, char *f, int sz, va_list arg, int op, int z, int w);
void str_rev(char *s);
void to_string(char *s, int n);
int check(char *fs, char *s, int *op, int sz);
int fs_init(char *s, va_list args);
int _atoi(char *s);
int _cd(char **cmd, char *argv, f_s **head);

#endif /*MAIN_H*/
