
#include "shell.h"


/**
 * prompt - open shell prompt
 * @env: the env vars for the process.
 * @argv: - the array of passed commands
 * Return: p in case of sucess
 */

void prompt(char *argv[], char *env[])
{
	int read, c;
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
		}
		if (read == 1)	/* when user press Enter */
			continue;
		line[read - 1] = '\0';
		new_argv = line_to_argv(line);
		if (!new_argv)
			continue;
		c = check_exit(new_argv, &line, &new_program);
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
		} else
			new_program = new_argv[0];
		go_fork(new_argv, env, &new_program, &line);
		new_program = NULL;
	}
	if (line != NULL)
		free(line);
}
