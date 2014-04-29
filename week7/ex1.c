#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int pipefd[2];

	if (pipe(pipefd) < 0)
	{
		printf("Error.\n");
		return 1;
	}

	pid_t pid = fork();

	// Parent
	if (pid > 0)
	{
		close(pipefd[0]);
		printf("Parent: Sending a message!\n");
		char msg[] = "Hello Son.";
		write(pipefd[1], msg, strlen(msg) + 1);
		close(pipefd[1]);
		return 0;
	}
	// Child
	else if (pid == 0)
	{
		close(pipefd[1]);
		char buffer[256];
		int bytes_read = read(pipefd[0], buffer, 256);

		if (bytes_read > 0)
		{
			printf("Child: Received a message!\n");
			printf("Message: %s\n", buffer);
		}
		close(pipefd[0]);
		return 0;
	}
	else
	{
		printf("Fork error.\n");
		return 1;
	}
	return 1;
}
