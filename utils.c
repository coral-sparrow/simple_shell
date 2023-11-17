#include "shell.h"

/**
 * get_new_argv - slice the original argv inline mode to be passed to exeve
 * @argc: the original argc
 * @argv:  the cmd args passed
 * Return: new argv vector
 */

char **get_new_argv(int argc, char *const argv[])
{
	char **new_argv;
	int i;

	new_argv = malloc(sizeof(char *) * argc);
	/* new_argv[0] = malloc(sizeof(char) * 30); */
	if (!new_argv)
		return (NULL);

	/* strcpy(new_argv[0], argv[1]); */

	for (i = 0; i < (argc - 1); i++)
	{
		new_argv[i] = malloc(sizeof(char) * 10);
		if (new_argv[i] == NULL)
		{
			_free_array(&new_argv);
			break;
		}

		strcpy(new_argv[i], argv[i + 1]);
	}


	new_argv[argc - 1] = NULL;
	return (new_argv);
}





/**
 * _strcat - concat dest + / + src
 * @dest: first string
 * @src: second string
 * Return: new concated string
 */


char *_strcat(char *dest, char *src)
{
	int l1, l2;
	char *new;

	l1 = strlen(dest);
	l2 = strlen(src);

	new = malloc(sizeof(char) * (l1 + l2 + 2));

	if (!new)
		exit(EXIT_FAILURE);

	strcpy(new, dest);
	strcat(new, "/");
	strcat(new, src);

	return (new);
}





/**
 * search_path - concat dest + / + src
 * @argv: the cmd args vector
 * @file: the program file passed by user
 * Return: new concated string
 */


char *search_path(char **argv, char *file)
{
	char *path, *tok, *tmp_str, *full_file_path, *tmp;
	int i, s_stat, path_len;
	struct stat sb;

	path = getenv("PATH");
	path_len = strlen(path);

	tmp_str = malloc(sizeof(char) * (path_len + 1));
	if (!tmp_str)
	{
		perror("search path");
		return (NULL);
	}

	strcpy(tmp_str, path);
	path = NULL;
	tmp = tmp_str;

	for (i = 0; ; i++, tmp_str = NULL)
	{
		tok = strtok(tmp_str, ":");

		if (tok == NULL)
		{
			perror(argv[0]);
			free(tmp);
			return (NULL);
		}

		full_file_path = _strcat(tok, file);
		s_stat = stat(full_file_path, &sb);

		if (s_stat == 0)
		{
			free(tmp);
			return (full_file_path);
		}

		free(full_file_path);
	}
}



/**
 * line_to_argv - split the line read from stdin (pipe & interacgive mode)
 * @line: the program file passed by user
 * Return: new argument vector (argv)
 */

char **line_to_argv(char *line)
{
	char **new_argv, *tok, *tmp_line;
	int i;

	new_argv = malloc(sizeof(char *) * MAX_SIZE);
	if (!new_argv)
		return (NULL);

	for (i = 0, tmp_line = line; i < MAX_SIZE - 1; i++, tmp_line = NULL)
	{
		new_argv[i] = NULL;
		tok = strtok(tmp_line, " ");

		if (tok == NULL)
			break;

		new_argv[i] = malloc(sizeof(char) * (strlen(tok) + 1));
		strcpy(new_argv[i], tok);
	}

	if (i > 0 && i < MAX_SIZE - 1)
	{
		/* this when tok == NULL caused break */
		/* no need to add NULL at the end it is there */
		return (new_argv);
	} else if (i > 0 && i == MAX_SIZE - 1)
	{
		/* to handle the case where #args > MAX_SIZE */
		new_argv[i] = NULL;
		return (new_argv);
	}

	_free_array(&new_argv);
	return (NULL);

}






/**
 * check_exit - split the line read from stdin (pipe & interacgive mode)
 * @line: line read from user
 * @new_program: another ptr to free.
 * @argv: the command argv passed.
 * Return: Nothing
 */

int check_exit(char **argv, char **line, char **new_program)
{
	char *test = "exit";
	char *endptr;
	long val;

	/* int strcmp(const char *s1, const char *s2); */

	if (strcmp(test, argv[0]) == 0)
	{
		if (argv[1])
		{
			errno = 0;    /* To distinguish success/failure after call */
			val = strtol(argv[1], &endptr, 10);
			/* Check for various possible errors. */
			if (errno != 0)
			{
				perror("Exit");
				_clean_mem(argv, &(*line), &(*new_program));
				return (-1);
			}

			if (endptr == argv[1])
			{
				/* no int in the string */
				printf("exit: Illegal number: %s\n", argv[1]);
				_clean_mem(argv, &(*line), &(*new_program));
				return (-1);
			}

			_clean_mem(argv, &(*line), &(*new_program));
			exit(val);
		}

		_clean_mem(argv, &(*line), &(*new_program));
		exit(EXIT_SUCCESS);
	}

	return (0);
}






