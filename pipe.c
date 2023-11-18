#include "shell.h"

/**
 * handel_pipe - handle piped values or inline commands
 * @env: the main env to keep
 * @argv: - the cmd args passed
 * Return: the absolute value of int
 */

void handel_pipe(char *argv[], char *env[])
{
	char *line = NULL, **new_argv, *new_program;
	size_t n = 0;
	int read, c, wstatus;
	struct stat sb;

	while (1)
	{
		read = getline(&line, &n, stdin);
		if (read == -1) /* failed to read */
			break;
		if (read == 1) /* only new line char is read */
			continue;
		line[read - 1] = '\0';
		new_argv = line_to_argv(line);
		if (!new_argv)
			continue;
		c = check_exit(new_argv, &line, &new_program, wstatus);
		if (c == -1)
			continue;
		if (stat(new_argv[0], &sb) != 0)
		{
			new_program = search_path(argv, new_argv[0]);
			if (!new_program)
				continue;
			 wstatus = go_fork(new_argv, env, &new_program, &line);
		} else
			wstatus = go_fork(new_argv, env, NULL, &line);

	}
	if (line != NULL) 
		free(line);

	exit(wstatus);
}

