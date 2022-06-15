#include "main.h"

void print_dirs(void);
path_l *create_pathlist(char **paths);

int main(void)
{
	print_dirs();
	return (0);
}

/**
 * print_dirs - Prints all the paths in $PATH.
 * Return: Void.
 */
void print_dirs(void)
{
	char *path_value, path_value_cpy[100], *current_char, *current_path;
	char *paths[20];
	path_l *head, *current;
	int i = 0;

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
	while (current)
	{
		printf("%s\n", current->dir);
		current = current->next;
	}
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
		i++;
	}

	return (head);
}
