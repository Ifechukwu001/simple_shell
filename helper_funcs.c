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

/**
 * create_pathlist - Creates a singly linked list of $PATH directories.
 * @paths: A pointer to an array of NULL terminated pointers to string paths.
 * Return: Pointer to the singly linked list (HEAD) or NULL if unsuccessful.
 */
path_l *create_pathlist(char **paths)
{
        path_l *head, *new, *current;
        int i = 0;

        head = NULL;
        current = head;

        if (paths == NULL)
                return (0);

	while (paths[i] != NULL)
        {
                new = malloc(sizeof(path_l));
                if (new == NULL)
                        return (0);
                new->dir = strdup(paths[i]);
                new->next = NULL;
                if (head == NULL)
                        head = new;
                else
                        current->next = new;
                current = new;
                i++;;
        }

        return (head);
}                  

/**
 * cmd_fullpath - Checks for the full path to a command.
 * @cmd: Executable's file name.
 * Return: Pointer to the full path.
 */
char *cmd_fullpath(char *cmd)
{
	char *path_value, path_value_cpy[100], *current_char, *current_path;
        char *paths[20], *correct_path;
        path_l *head, *current;
        int i = 0, len;
	struct stat stats;

        path_value = getenv("PATH");
        strcpy(path_value_cpy, path_value);
        current_path = path_value_cpy;
        current_char = current_path;

        while (*current_char != '\0')
        {
                if (*current_char == ':')
                {
                        *current_char = '\0';
                        paths[i] = current_path;
                        current_path = current_char + 1;
                        i++;
                }
                current_char++;
        }

        paths[i] = current_path;
        paths[++i] = NULL;

	head = create_pathlist(paths);
	current = head;
	correct_path = malloc(32 * sizeof(char));

	while (current)
	{
		strcpy(correct_path, current->dir);
		len = strlen(current->dir);
		correct_path[len] = '/';
		len++;
		for (i = 0; cmd[i] != '\0'; i++, len++)
		{
			correct_path[len] = cmd[i];
		}
		correct_path[len] = '\0';

		if (stat(correct_path, &stats) == 0)
			return (correct_path);
		current = current->next;
	}

	return (0);
}
