#include <stdio.h>
/**
 * main - Entry point
 * @argc: number of command line arguments
 * @argv: array containing command line arguments
 * Return: 0
 */
int main(int argc, char **argv)
{
	int x;

	for (x = 0; x < argc ; x++)
	{
		printf("%s\n", argv[x]);
	}
	return (0);
}
