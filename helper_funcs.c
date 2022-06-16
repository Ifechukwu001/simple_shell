#include "main.h"

/**
 * print_prompt - prints the prompt to the output.
 * Return: Void.
 */
void print_prompt(void)
{
	printf("#cisfun$ ");
}

/**
 * execute_cmd - executes the command string passed to it.
 * @cmd: Command to be executed.
 * @arg: Arguments passed to the function.
 * @env: Enviroment variables passed to the function.
 * Return: Void.
 */
void execute_cmd(char *cmd, char **arg, char **env)
{
	int childid, status;

	/* Changes the command to be the full path */
	cmd = cmd_fullpath(cmd);
	if (cmd == NULL)
	{
		printf("%s: No such file or directory\n", env[0]);
		return;
	}

	/* Fork to create child process */
	childid = fork();
	if (childid == 0) /* if current process equals child process */
	{
		/* execute the command */
		if (execve(cmd, arg, env) == -1)
		{
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* This is the parent process */
		wait(&status);
		/* Free the malloc'd space assigned by getline */
		free(cmd);
	}
}

/**
 * tokenize - Creates an array of string words.
 * @string: String to convert.
 * Return: An array of strings.
 */
char **tokenize(char *string)
{
	char *result, **arr_str;
	int i = 0;

	/* Create a space that will hold the pointers to the string arguments */
	arr_str = malloc(64 * sizeof(char *));
	if (arr_str == NULL)
	{
		perror("tokenize malloc");
		return (NULL);
	}

	/* Use strtok to get the pointer to the arguments passed */
	result = strtok(string, " \n\t\r\a");
	arr_str[i] = result;
	while (result)
	{
		result = strtok(NULL, " \n\t\r\a");
		i++;
		arr_str[i] = result;
	}
	return (arr_str);
}
