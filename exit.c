#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <dirent.h>
#include "main.h"

#define ex (execve("/bin/ls", args, NULL) == (-1))
#define ps(x) (printf("%s\n", (x)))
#define pd(x) (printf("%d\n", (x)))


/**
 * exit2 - exits the shell with specified status.
 * @sarr: array of strings containing command-line input.
 * @envp: address of environment.
 * @status: address of status int.
 * @free: address of int indicating whether, or not, to free envp.
 *
 * Return: always 0.
 */
int exit2(char **sarr, char ***envp __attribute__((unused)),
		int *status, int *free __attribute__((unused)))
{
	shstruct(NULL)->quick_exit = 0;
	if (sarr[1])
	{
		*status = str2posint(sarr[1]);
		return (0);
	}

	*status = 0;

	return (0);
}
