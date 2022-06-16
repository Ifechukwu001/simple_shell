#include "main.h"

/**
 * print_prompt - prints the prompt to the output.
 * Return: Void.
 */
void print_prompt(void)
{
	dprintf(STDOUT_FILENO, "$ ");
}

/**
 * execute_cmd - executes the command string passed to it.
 * @data: Structure containing all needed to execute a binary.
 * Return: Void.
 */
void execute_cmd(exec_vars data)
{
	int childid, status;
	static int warn_no = 1;
	char original_cmd[10];

	_strcpy(original_cmd, data.cmd);
	if (data.cmd[0] != '/')
		/* Changes the command to be the full path */
		data.cmd = cmd_fullpath(data.cmd);
	if (data.cmd == NULL)
	{
		printf("%s: %d: %s: not found\n", data.shell_call, warn_no, original_cmd);
		warn_no++;
	}
	else
	{
		/* Fork to create child process */
		childid = fork();
		if (childid == 0) /* if current process equals child process */
		{
			/* execute the command */
			if (execve(data.cmd, data.args, data.envs) == -1)
			{
				printf("%s: %d: %s: not found\n",
				       data.shell_call, warn_no, original_cmd);
				warn_no++;
				/* Free the malloc'd space assigned by getline */
				if (data.cmd)
					free(data.cmd);
				if (data.args)
					free(data.args);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/* This is the parent process */
			wait(&status);
			/* Free the malloc'd space assigned by getline */
			free(data.cmd);
			free(data.args);
		}
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
		if (result)
		{
			switch (*result)
			{
			case ' ':
			case '\n':
			case '\t':
			case '\r':
			case '\a':
				continue;
				break;
			}
		}
		i++;
		arr_str[i] = result;
	}
	return (arr_str);
}
