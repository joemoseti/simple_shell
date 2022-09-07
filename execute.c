#include "main.h"

char **environ;

/**
 * execute - executes the command
 * @cmd: command to run
 * Return: 0 on success1 -1 if cmd is exit and 1 on any other error
 */
int execute(char **cmd)
{
	pid_t child_pid;
	int status;
	char *pathway;
	size_t arglen = _strlen(cmd[0]); /* Argument length */

	/* When users press Enter without an argument */
	if (cmd[0] == NULL)
		return (1);

	if (strncmp("exit", cmd[0], 4) == 0)
		return (-1);

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error");
		return (1);
	}
	else if (child_pid == 0)
	{
		pathway = malloc(10 + arglen);
		sprintf(pathway, "/usr/bin/%s", cmd[0]);
		if (execve(pathway, cmd, environ) == -1)
		{
			perror("Error");
			exit(-1);
		}
	}
	else
		wait(&status);
	return (1);
}
