#include "shell.h"

/**
 * handel_inline - handle piped values or inline commands
 * @argc: number of cmd args passed
 * @argv: the cmd args passed
 * @env: the main process env to keep.
 * Return: the absolute value of int
 */

int handel_inline(int argc, char *argv[], char *env[])
{
	int wstatus = 0, pid, s_stat;
	char **new_argv, *new_program;
	struct stat sb;

	new_argv = get_new_argv(argc, argv);
	if (!new_argv)
		exit(EXIT_FAILURE);

	if (check_exit(new_argv) == -1)
		exit(EXIT_FAILURE);
	/* determine if the path is found or not */
	s_stat = stat(argv[1], &sb);
	if (s_stat == 0)
		new_program = argv[1];
	else
		new_program = search_path(argv, argv[1]);
	if (new_program == NULL)
		exit(EXIT_FAILURE);

	/* fork the current process to create the child */
	pid = fork();
	if (pid == 0)
	{
		/* this the child */
		execve(new_program, new_argv, env);
		perror(argv[0]);
		exit(EXIT_FAILURE);

	} else if (pid > 0)
	{
		/* this is the parent and pid is child pid */
		wait(&wstatus);
	} else
	{
		/* faild to fork */
		exit(EXIT_FAILURE);
	}
	return (0);
}

