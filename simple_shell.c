#include "shell.h"



/**
 *  main - the main function for the shell
 * @argc: the number of cmd args
 * @argv: the array of the arguments
 * @env: is the process env vector.
 * Return: nothing
 */

int main(int argc, char *argv[], char *env[])
{

	int tty;


	tty = isatty(fileno(stdin));

	if (!tty)
	{
		handel_pipe(argv);
	} else if (argc > 1)
	{
		handel_inline(argc, argv);
	} else
	{
		prompt(argv, env);
	}

	return (0);
}
