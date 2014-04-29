#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	printf("About to launch /usr/bin/sort\n");

	pid_t pid = fork();

	if (pid == 0)
	{
		int exec_status = execl("/usr/bin/sort", "sort", "forkdemo.c", (char *) NULL);
		if (exec_status == -1)
		{
			perror("Exec failed");
			return 1;
		}
	}
	else
	{
		wait(0);
		printf("Sort finished.");
	}
	return 0;
}

