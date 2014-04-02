#include <stdio.h>
#include <math.h>

// Dangerous macro, consider bad_mult(1 + 2, 2 + 3)
#define bad_mult(x, y) (x*y)

// Safe macro (note the brackets)
#define good_mult(x, y) ((x)*(y))

// Dangerous macro
#define bad_max(x, y) (x >= y ? x : y)

// Still dangerous. Consider max(i++, j++)
// There's no way to fix this.
#define mad_max(x, y) ((x) >= (y) ? (x) : (y))

// Perfectly safe macro (constants are always fine)
#define BUFFER_SIZE 256

int main()
{
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, BUFFER_SIZE, stdin) != NULL)
	{
		printf("%s", buffer);
	}


	// Here's an example of *conditional* compilation (very useful)
	// Compile with an extra flag: -DDEBUG (this defines a macro from the cmd line).
	#ifdef DEBUG
	printf("Secret message!\n");
	#endif

	return 0;
}
