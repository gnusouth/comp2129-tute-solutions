#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// How many philosophers are dining?
#define NPHIL 5

pthread_t threads[NPHIL];
pthread_mutex_t forks[NPHIL];

// Semaphore for controlled eating
sem_t semaphore;

void fail()
{
	printf("Could not lock a mutex.\n");
	exit(1);
}

// Each thread is a philosopher at the table.
void *worker(void *arg)
{
	// ID of the philosopher (from 0 to NPHIL-1)
	int id = *(int *)arg;

	// IDs of their left and right fork.
	int left = id;
	int right = (id + 1) % NPHIL;

	while (1)
	{
		// Attempt to get into the critical section
		sem_wait(&semaphore);

		// Pick up the first fork
		if (pthread_mutex_lock(&forks[left]) != 0)
		{
			fail();
		}
		if (pthread_mutex_lock(&forks[right]) != 0)
		{
			fail();
		}
		// Om nom nom.
		printf("Philosopher %d is eating...\n", id);

		// Release left, release right.
		pthread_mutex_unlock(&forks[left]);
		pthread_mutex_unlock(&forks[right]);

		// Leave the critical section
		sem_post(&semaphore);

		// Thinking.
		printf("Philosopher %d is thinking...\n", id);
	}
}

int main(void)
{
	int args[NPHIL];

	// Create mutexes
	for (int i = 0; i < NPHIL; i++)
	{
		pthread_mutex_init(&forks[i], NULL);
	}

	// Initialise the semaphore
	sem_init(&semaphore, 0, NPHIL - 1);

	// Start each philosopher dining. They never stop.
	for (int i = 0; i < NPHIL; i++)
	{
		args[i] = i;
		pthread_create(&threads[i], NULL, worker, &args[i]);
	}

	while (1)
	{
		sleep(1);
	}

	return 0;
}
