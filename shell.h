#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#define _GNU_SOURCE
/* buffer size for line tokens */
#define MAX_SIZE 15

void handel_inline(int argc, char *argv[], char *env[]);
void handel_pipe(char *argv[], char *env[]);
void prompt(char *argv[], char *env[]);
char **get_new_argv(int argc, char *const argv[]);
char *_strcat(char *dest, char *src);
char *search_path(char **argv, char *file);
char **line_to_argv(char *line);
void _free_array(char ***array);
void _clean_mem(char **argv, char **line, char **new_program);
/* int check_exit(char **argv); */

int check_exit(char **argv, char **line, char **new_program, int wstatus);

int go_fork(char **argv, char **env, char **new_program, char **line);


#endif
