#include "shell.h"


/**
 * go_fork - do the fork and exeve work.
 * @env: the env vars for the process
 * @argv: - the array of passed commands
 * @new_program: to be passed to exeve.
 * Return: 0 in sucess or -1 in failure.
 */

int go_fork(char **argv, char **env, char *new_program)
{

	int pid, wstatus = 0;

	/* fork to create new process */
	pid = fork();

	if (pid == 0)
	{
		/* this the child */
		execve(new_program, argv, env);
		perror(argv[0]);
		return (-1);

	} else if (pid > 0)
		/* this is the parent and pid is child pid */
		wait(&wstatus);
	else
		/* faild to fork */
		return (-1);

	return (0);
}
