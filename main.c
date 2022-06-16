#include "main.h"

/**
 * main - Contains all the functions to run the shell.
 * @ac: Argument count.
 * @av: NULL terminated array of strings.
 * Return: Always 0.
 */
int main(int ac __attribute__((unused)), char *av[])
{
	int is_running = 1, read_chars;
	char *input_str = NULL;
	size_t input_size = 0;
	char **args, **envs = { NULL };
	exec_vars data;

	while (is_running)
	{
		/* Displays the prompt */
		print_prompt();
		/* Get string from the stdin */
		read_chars = getline(&input_str, &input_size, stdin);
		if (read_chars == -1) /* if there is an error */
		{
			is_running = 0;
			putchar('\n');
			continue;
		}
		/* Tokenize the input string into arguments */
		args = tokenize(input_str);
		if ((args[0]) == NULL)
		{
			free(args[0]);
			continue;
		}
		else
		{
			/* Execute the inputed command */
			data.shell_call = av[0];
			data.cmd = args[0];
			data.args = args;
			data.envs = envs;
			execute_cmd(data);
		}
	}

	return (0);
}
