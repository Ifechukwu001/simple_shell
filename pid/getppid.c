#include <stdio.h>
#include <unistd.h>
/**
 * main - Entry point
 * Return: 0;
 */
int main(void)
{
	pid_t myppid;

	myppid = getppid();
	printf("%u\n", myppid);
	return (0);
}
