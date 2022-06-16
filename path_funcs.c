#include "main.h"

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
		new->dir = _strdup(paths[i]);
		new->next = NULL;
		if (head == NULL)
			head = new;
		else
			current->next = new;
		current = new;
		i++;
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
	path_l *head, *current;
	char *correct_path, **paths;
	int i;
	size_t bufsize = 32, len;
	struct stat stats;

	paths = path_ss();
	head = create_pathlist(paths);

	free(paths[0]);
	free(paths);

	current = head;
	correct_path = malloc(bufsize * sizeof(char));
	if (correct_path == NULL)
	{
		free(cmd);
		return (0);
	}

	while (current)
	{
		_strcpy(correct_path, current->dir);
		len = _strlen(current->dir);
		correct_path[len] = '/';
		len++;
		for (i = 0; cmd[i] != '\0'; i++, len++)
		{
			if (len == bufsize)
			{
				bufsize += 8;
				correct_path = realloc(correct_path, bufsize);
			}
			correct_path[len] = cmd[i];
		}

		correct_path[len] = '\0';

		if (lstat(correct_path, &stats) == 0)
		{
			free_pathlist(&head);
			free(cmd);
			return (correct_path);
		}

		current = current->next;
	}
	free(cmd);
	return (0);
}

/**
 * path_ss - Gets all the paths in PATH.
 * Return: Pointer to an array of pointers to the path strings.
 */
char **path_ss(void)
{
	char *path_value, *path_value_cpy, *current_char, *current_path;
	char **paths;
	int i = 0;

	paths = malloc(20 * sizeof(char *));
	if (paths == NULL)
		return (0);
	path_value_cpy = malloc(100 * sizeof(char));
	if (path_value_cpy == NULL)
		return (0);
	path_value = getenv("PATH");
	_strcpy(path_value_cpy, path_value);
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

	return (paths);
}

/**
 * free_pathlist - frees the space allocated to a pathlist.
 * @head: Pointer to the List pointer (HEAD).
 * Return: Void.
 */
void free_pathlist(path_l **head)
{
	path_l *current, *temp;

	current = *head;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->dir);
		free(temp);
	}
}

/**
 * abs_currentpth - Gets th full path to an executable in the current program dir.
 * @rel_path: Relative path to the executable.
 * Return: Pointer to absolute path.
 */
char *abs_currentpth(char *rel_path)
{
	char cwd_path[256], *correct_path;
	int i = 0;
	size_t bufsize = 32, len;

	correct_path = malloc(bufsize * sizeof(char));
	if (correct_path == NULL)
	{
		free(rel_path);
		return (0);
	}
	if (getcwd(cwd_path, sizeof(cwd_path)) == NULL)
	{
		free(rel_path);
		return (0);
	}

	printf("%s\n", cwd_path);
	_strcpy(correct_path, cwd_path);
	len = _strlen(cwd_path);
	for (i = 1; rel_path[i] != '\0'; i++, len++)
	{
		if (len == bufsize)
			correct_path = realloc(correct_path, bufsize);
		correct_path[len] = rel_path[i];
	}
	correct_path[len] = '\0';

	free(rel_path);
	return (correct_path);
}
