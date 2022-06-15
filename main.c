#include "main.h"

/**
 * main - Contains all the functions to run the shell.
 * @ac: Argument count.
 * @av: NULL terminated array of strings.
 * Return: Always 0.
 */
int main(int ac __attribute__((unused)), char *av[] __attribute__((unused)))
{
	int is_running = 1, read_chars;
	char *input_str = NULL;
	size_t input_size = 0;
	char **args, **envs = av;

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
		/* Execute the inputed command */
		execute_cmd(args[0], args, envs);
	}

	return (0);
}
