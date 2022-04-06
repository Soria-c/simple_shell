#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdarg.h>


extern char **environ;

int builtin_check(char **cmd, char *lin);
void printenv(void);
void printf_error(char *cmd, char *argv, int c);
void _execve(char **cmd);
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


#endif /*MAIN_H*/
