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

/**
 * _strdup - creates a memory array and dumps a string there.
 * @str: String to be dumped.
 * Return: Pointer to the memory array.
 */
char *_strdup(char *str)
{
	int i, str_size = _strlen(str);
	char *ptr;

	if (str)
	{
		ptr = malloc(str_size + 1);
		if (ptr)
		{
			for (i = 0; i < str_size + 1; i++)
				ptr[i] = str[i];
		}
	}
	else
		return (0);
	return (ptr);
}

/**
 * *_strcpy -  copies the string pointed to by src
 * @dest: char type string
 * @src: char type string
 * Description: Copy the string pointed to by pointer `src` to
 * the buffer pointed to by `dest`
 * Return: Pointer to `dest`
 */

char *_strcpy(char *dest, const char *src)
{
	int i = -1;

	do {
		i++;
		dest[i] = src[i];
	} while (src[i] != '\0');

	return (dest);
}

/**
 * _strlen - checks the lenght of the string.
 * @s: Character array (string).
 * Return: int (the lenght of the string).
 */
int _strlen(char *s)
{
	int i, len = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		++len;
	}
	return (len);
}
