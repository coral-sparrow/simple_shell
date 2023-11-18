
#include "shell.h"


/**
 * prompt - open shell prompt
 * @env: the env vars for the process.
 * @argv: - the array of passed commands
 * Return: p in case of sucess
 */

void prompt(char *argv[], char *env[])
{
	int read, c, wstatus;
	size_t n = 0;
	char **new_argv, *new_program = NULL, *line = NULL;
	struct stat sb;

	while (1)
	{
		line = NULL;
		n = 0;
		printf("($) ");
		read = getline(&line, &n, stdin);
		if (read == -1) /* EOF (CTR + d ) is reached */
		{
			printf("\n");
			break;
		} else if (read == 1)	/* when user press Enter */
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
			if (new_program == NULL)
			{
				_clean_mem(new_argv, &line, &new_program);
				continue;
			}
			wstatus = go_fork(new_argv, env, &new_program, &line);
		} else
			wstatus = go_fork(new_argv, env, NULL, &line);
		new_program = NULL;
	}
	if (line != NULL)
		free(line);
	exit(WEXITSTATUS(wstatus));
}
