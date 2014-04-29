#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(void)
{
	int pipefd[2];
	if (pipe(pipefd) < 0)
	{
		perror("Could not create pipe");
		return 1;
	}

	pid_t pid = fork();
	if (pid < 0)
	{
		perror("Could not fork");
		return 1;
	}

	// Child replaces stdout with the pipe, and runs ls -l
	if (pid == 0)
	{
		close(pipefd[0]);
		close(1);
		dup(pipefd[1]);
		if (execlp("ls", "ls", "-l", NULL) < 0)
		{
			perror("Could not exec");
			return 1;
		}
	}

	// Parent reads from child, annotating lines
	close(pipefd[1]);
	FILE *fp = fdopen(pipefd[0], "r");
	char buf[BUFFER_SIZE];
	int i = 0;
	while (fgets(buf, BUFFER_SIZE, fp) != NULL)
	{
		printf("Line %d: %s", i++, buf);
	}

	return 0;
}
