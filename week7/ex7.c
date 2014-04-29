#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	int pipefd[2];
	pipe(pipefd);

	pid_t pid = fork();

	// Run sort, report back to parent.
	if (pid == 0)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
		if (execlp("sort", "sort", argv[1], NULL) < 0)
		{
			perror("Could not exec into sort");
			return 1;
		}
	}

	dup2(pipefd[0], 0);
	close(pipefd[0]);
	close(pipefd[1]);
	if (execlp("uniq", "uniq", NULL) < 0)
	{
		perror("Could not exec into uniq");
		return 1;
	}
}
