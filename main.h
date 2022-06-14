#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Global variables */
extern FILE *stdin;


/* Function Prototypes */

/* Helper_functions */
void execute_cmd(char *cmd, char **arg, char **env);
void print_prompt(void);
char **tokenize(char *string);

/* Reengineered */
char *_strtok(char *string, char *delim);

#endif /* MAIN_H */
