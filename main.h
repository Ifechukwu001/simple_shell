#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Path list stucture */
typedef struct path_t
{
	char *dir;
	struct path_t *next;
} path_l;

/* Argument structure */
typedef struct
{
	char *shell_call;
	char *cmd;
	char **args;
	char **envs;
} exec_vars;

/* Global variables */
extern FILE *stdin;


/* Function Prototypes */

/* Helper_functions */
void execute_cmd(exec_vars data);
void print_prompt(void);
char **tokenize(char *string);

/* Path functions */
path_l *create_pathlist(char **paths);
char *cmd_fullpath(char *cmd);
char **path_ss(void);

/* Reengineered */
char *_strtok(char *string, char *delim);

#endif /* MAIN_H */
