#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

// Barriers
pthread_barrier_t barrier1;
pthread_barrier_t barrier2;

// Worker function
void * robot_worker(void * arg)
{
	char * msg = (char *) arg;

	while (1)
	{
		// Do "work"
		puts(msg);
		// Wait for all the other threads
		pthread_barrier_wait(&barrier1);
		// Wait for the main thread to advance the conveyor belt
		pthread_barrier_wait(&barrier2);
	}

	return NULL;
}

int main(void)
{
	// The jobs for each robot arm to execute.
	// We'll launch a worker thread per job.
	char * work[] = {
		"cutting",
		"welding",
		"painting"
	};

	int nrobots = sizeof(work) / sizeof(work[0]);

	pthread_t threads[nrobots];

	// Initialise the barriers
	pthread_barrier_init(&barrier1, NULL, nrobots + 1);
	pthread_barrier_init(&barrier2, NULL, nrobots + 1);

	// Start the robot arms.
	for (int i = 0; i < nrobots; i++)
	{
		pthread_create(&threads[i], NULL, robot_worker, work[i]);
	}

	while(1)
	{
		// Wait for the robot arms to do their work
		pthread_barrier_wait(&barrier1);

		// Spend 750ms advancing the conveyor belt.
		puts("Advancing conveyor belt...");
		usleep(750000);
		puts("Next work item ready.");

		// Hit the barrier, and hence, allow the robot arms to continue
		pthread_barrier_wait(&barrier2);
	}

	// NB: As this is program never terminates, we don't destroy the barriers...
	// This is bad practice, normally you should have the following lines too:
	pthread_barrier_destroy(&barrier1);
	pthread_barrier_destroy(&barrier2);

	return 0;
}
