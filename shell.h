#ifndef _HEADER_
#define _HEADER_
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PROMPT "$ "
int function_execute(char **args, char **argv);
char **div_string(char *str);
void print_prompt(char *prompt);
#endif /*_HEADER_*/
