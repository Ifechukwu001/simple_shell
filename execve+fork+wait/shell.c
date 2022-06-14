#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
/**
 * main - Entry point
 * Return: 0
 */
int main(void)
{
	char *buffer;
	size_t bufsize = 1024;
	size_t lenIn = 0;
	pid_t child_pid;
	char *argv[1024];

	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}
	printf("#cisfun$ ");
	lenIn = getline(&buffer, &bufsize, stdin);
	buffer[lenIn - 1] = '\0';
	argv[0] = buffer;
	printf("%s", buffer);
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid == 0)
	{
		if (execve(buffer, argv, NULL) == -1)
		{
			perror("Error:\n");
			kill(0, 0);
		}
	}
	else
		wait(NULL);
	return (0);
}
