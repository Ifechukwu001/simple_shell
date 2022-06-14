#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * main - Entry point
 * Return: 0
 */
int main(void)
{
	char *argv[] = {"/bin/ls", "-l", "/tmp/", NULL};
	pid_t child_pid;
	unsigned int counter = 0;

	while (counter < 5)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error:");
			return (1);
		}
		if (child_pid == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("Error:");
			}
			printf("waiting...");
			sleep(4);
			exit(0);
		}
		else
			wait(NULL);
		counter++;
	}
	return (0);
}
