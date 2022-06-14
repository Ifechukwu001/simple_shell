#include <string.h>
#include <stdio.h>
/**
 * main - Entry Point
 * Return: 0;
 */
int main(void)
{
	char str[80] = "Radarada";
	const char s[2] = "a";
	char *token;

	token = strtok(str, s);
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, s);
	}
	return (0);
}
