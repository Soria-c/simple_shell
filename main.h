#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

extern char **environ;
void printf_error(char *cmd, char *argv);
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

#endif /*MAIN_H*/
