#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char **argv, char **env)
{
	char *lin = NULL, *wcmd;
	size_t n = 0;
	ssize_t r;
	char *cmd[2];
	int id, status, rexc;


	cmd[1] = NULL;
	write(1, "customShell $: ", 15);
	for (;(r = getline(&lin, &n, stdin)) != -1; write(1, "customShell $: ", 15))
	{
		if (lin[r - 1] == '\n')
			lin[r - 1] = '\0';
		cmd[0] = lin;
		id = fork();
		if (!id)
		{
			rexc = execve(lin, cmd, NULL);
			if (rexc == -1)
			{
				wcmd = _which(lin);
				if (!wcmd || !(*cmd[0]))
				{
					printf("File not found\n");
					free(lin);
					free(wcmd);
					/*kill(getpid(), SIGKILL);*/
					_exit(1);
				}
				else
				{
					cmd[0] = str_cpy(cmd[0], wcmd);
					execve(wcmd, cmd, NULL);
				}
			}
		}
		else if (id > 0)
		{
			wait(&status);
			/*kill(getpid(), SIGKILL);*/
		}
	}
	free(lin);
	return (0);

}
