#include "main.h"

/**
 * _strtok - returns the first word in a string.
 * @string: String passed to the function.
 * @delim: Delimiter to diferrenciate words.
 * Return: pointer to the word string.
 */
char *_strtok(char *string, char *delim)
{
	static char *current_str;
	char *word_ptr;
	int i, j, k;

	/* Check string = NULL;if true use the former,else reset to a new one */
	if (string == NULL)
		;
	else
		current_str = string;

	/* Set a pointer to the beginning of the word to be used */
	word_ptr = current_str;
	/* Check each character till the end of the string */
	for (i = 0; current_str[i] != '\0'; i++)
	{
		/* Check all the characters in delim */
		for (k = 0; delim[k] != '\0'; j++, k++)
		{
			/* if string character == character in delim */
			if (current_str[i] == delim[k])
			{
				/* Change the character to '\0' */
				current_str[i] = '\0';
				/* Static variable to point to next character */
				current_str = &current_str[++j];
			}
			else /* keep checking */
				continue;
		}
	}
	return (word_ptr);
}
