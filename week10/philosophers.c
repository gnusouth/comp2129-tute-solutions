#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// How many philosophers are dining?
#define NPHIL 5

pthread_t threads[NPHIL];
pthread_mutex_t forks[NPHIL];

void fail()
{
	printf("Could not lock a mutex.\n");
	exit(1);
}

// Each thread is a philosopher at the table.
void * worker(void * arg)
{
	// ID of the philosopher (from 0 to NPHIL - 1)
	int id = *((int *) arg);

	// IDs of their left and right fork.
	int left = id;
	int right = (id + 1) % NPHIL;

	// Solve the deadlock by imposing a global locking hierarchy.
	// Always lock *lower numbered* forks first.
	int first_fork = (left < right ? left : right);
	int second_fork = (left < right ? right : left);

	while (1)
	{
		// Pick up the lower numbered fork.
		if (pthread_mutex_lock(&forks[first_fork]) != 0)
		{
			fail();
		}
		// Then the highered numbered fork.
		if (pthread_mutex_lock(&forks[second_fork]) != 0)
		{
			fail();
		}
		// Om nom nom.
		printf("Philosopher %d is eating...\n", id);

		// Release left, release right.
		pthread_mutex_unlock(&forks[first_fork]);
		pthread_mutex_unlock(&forks[second_fork]);

		// Thinking.
		printf("Philosopher %d is thinking...\n", id);
	}
}

int main(void)
{
	int args[NPHIL];

	// Create mutexes.
	for (int i = 0; i < NPHIL; i++)
	{
		pthread_mutex_init(&forks[i], NULL);
	}

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

	// Mutexes never destroyed... this is bad but whatever.

	return 0;
}
