#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	int n = 6;
	pid_t pid;

	printf("Before fork\n");
	pid = fork();

	if (pid < 0)
	{
		perror("Fork failed");
		return 1;
	}

	// Child
	if (pid == 0)
	{
		n++;
		sleep(30);
	}
	// Parent
	else
	{
		n *= 2;
		wait(0);
	}

	printf("Fork returned %d, n is %d\n", pid, n);
	return 0;
}
