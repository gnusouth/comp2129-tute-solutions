#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handle_sigterm(int sig)
{
	printf("Dying now\n");
	exit(0);
}

void handle_sigint(int sig)
{
	printf("You won't get rid of me that easily!\n");
}

int main(void)
{
	struct sigaction sa;
	sa.sa_handler = handle_sigterm;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGTERM, &sa, NULL) == -1)
	{
		perror("Could not register handler");
		exit(1);
	}

	sa.sa_handler = handle_sigint;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Could not register handler");
		exit(1);
	}

	while (1)
	{
		sleep(1);
	}
}
