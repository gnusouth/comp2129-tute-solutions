#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	// The size of the buffer
	int buffer_length = 8;

	// The size of the string contained in the buffer already
	int str_length = 0;

	// Allocate memory for the buffer
	char * buffer = (char *) malloc(buffer_length * sizeof(char));
	if (buffer == NULL)
	{
		perror(argv[0]);
		exit(EXIT_FAILURE);
	}

	// Read an appropriate number of characters into the buffer
	while (fgets(buffer + str_length, buffer_length - str_length, stdin) != NULL)
	{
		// Update the length of the string in the buffer
		str_length = strlen(buffer);

		// Check if the last character before the null byte is a newline
		if (buffer[str_length - 1] != '\n')
		{
			// If it isn't, the string must have been truncated
			// Therefore, we need to resize the buffer
			fprintf(stderr, "Resizing buffer from %d to %d\n", buffer_length, 2*buffer_length);
			buffer_length *= 2;
			buffer = realloc(buffer, buffer_length * sizeof(char));
			if (buffer == NULL)
			{
				perror(argv[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			// If the last character is a newline, we're fine.
			// Remove the newline (we don't want to count it).
			buffer[str_length - 1] = '\0';
			str_length--;

			printf("(%d) %s\n", str_length, buffer);

			// Reset the string length for the next run
			str_length = 0;
		}
	}

	// Always remember to free dynamically allocated memory!
	free(buffer);
	return 0;
}
