#include "shell.h"


/**
 * go_fork - do the fork and exeve work.
 * @env: the env vars for the process
 * @argv: - the array of passed commands
 * @new_program: to be passed to exeve.
 * @line: the line we read in.
 * Return: 0 in sucess or -1 in failure.
 */

int go_fork(char **argv, char **env, char **new_program, char **line)
{

	char *t_program;
	int pid, wstatus;

	if (new_program == NULL)
		t_program = argv[0];
	/* fork to create new process */
	pid = fork();
	if (pid == 0)
	{
		/* this the child */
		if (new_program == NULL)
			execve(t_program, argv, env);
		else
			execve(*new_program, argv, env);
		perror(argv[0]);
		_clean_mem(argv, &(*line), &(*new_program));
		exit(EXIT_FAILURE);

	} else if (pid > 0)
	{
		/* this is the parent and pid is child pid */
		wait(&wstatus);
		if (line == NULL && new_program == NULL)
			_clean_mem(argv, NULL, NULL);
		else if (line == NULL)
			_clean_mem(argv, NULL, &(*new_program));
		else if (new_program == NULL)
			_clean_mem(argv, &(*line), NULL);
		else
			_clean_mem(argv, &(*line), &(*new_program));
		return (WEXITSTATUS(wstatus));

	} else
	{
		/* faild to fork */
		_clean_mem(argv, &(*line), &(*new_program));
		exit(EXIT_FAILURE);
	}
	return (0);
}



/**
 * _free_array - do the fork and exeve work.
 * @array: ptr to array of pointers to be freed.
 * Return: 0 in sucess or -1 in failure.
 */
void _free_array(char ***array)
{
	int i;
	char **l_array;

	l_array = *array;
	if (l_array != NULL && l_array[0] != NULL)
	{
		for (i = 0; ; i++)
		{
			if (l_array[i] == NULL)
				break;

			free(l_array[i]);
			l_array[i] = NULL;
		}

		free(l_array);
		l_array = NULL;

	} else if (l_array != NULL)
	{
		free(l_array);
		l_array = NULL;
	}

}







/**
 * _clean_mem - split the line read from stdin (pipe & interacgive mode)
 * @argv: new argv array from line to argv.
 * @line: line allocated by getline.
 * @new_program: the command full path from search path function.
 * Return: Nothing
 */

void _clean_mem(char **argv, char **line, char **new_program)
{

	if (argv != NULL)
	{
		_free_array(&argv);
	}
	if (line != NULL && *line != NULL)
	{
		free(*line);
		 *line = NULL;
	}

	if (new_program != NULL && *new_program != NULL)
	{
		free(*new_program);
		*new_program = NULL;
	}

}
