#include <stdio.h>
#include <stdlib.h>
/**
 * main - Entry point
 * Return: 0;
 */
int main(void)
{
	char *buffer;
	size_t bufsize = 32;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}

	printf("$ ");
	getline(&buffer, &bufsize, stdin);
	printf("%s", buffer);
	printf("You typed: %s", buffer);
	return (0);
}
