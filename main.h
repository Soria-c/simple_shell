#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

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
