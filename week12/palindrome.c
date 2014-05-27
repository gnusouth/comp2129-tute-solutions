#include <stdio.h>
#include <stdlib.h>

int is_palindrome_iterative(char * str, int length)
{
	for (int i = 0; i < length / 2; i++)
	{
		if (str[i] != str[length - 1 - i])
		{
			return 0;
		}
	}
	return 1;
}

int is_palindrome_recursive(char * str, int length)
{
	if (length <= 1)
	{
		return 1;
	}
	else if (str[0] != str[length - 1])
	{
		return 0;
	}
	return is_palindrome_recursive(str + 1, length - 2);
}

#ifdef TEST
int main()
{
	char * anna = "anna";
	char * racecar = "racecar";
	char * comp2129 = "comp2129";

	char * test_words[] = {anna, racecar, comp2129};
	int lengths[] = {4, 7, 8};

	for (int i = 0; i < 3; i++)
	{
		int rec = is_palindrome_recursive(test_words[i], lengths[i]);
		int it = is_palindrome_iterative(test_words[i], lengths[i]);
		printf("is_palindrome(%s) = (%d, %d)\n", test_words[i], rec, it);
	}
	return 0;
}

#else

char rand_letter()
{
	return 'a' + (rand() % 26);
}

char * long_palindrome(int length)
{
	char * palindrome = malloc(length * sizeof(char));
	if (palindrome == NULL) exit(EXIT_FAILURE);

	int halfway = length / 2;
	for (int i = 0; i < halfway; i++)
	{
		char c = rand_letter();
		palindrome[i] = c;
		palindrome[length - 1 - i] = c;
	}

	if (length % 2 == 1)
	{
		palindrome[halfway] = rand_letter();
	}

	return palindrome;
}

int main(int argc, char ** argv)
{
	if (argc < 2)
	{
		printf("Please provide a length.\n");
		return 1;
	}

	int length = 0;
	sscanf(argv[1], "%d", &length);
	char * str = long_palindrome(length);

	int is_palindrome;

	#ifdef RECURSIVE
	is_palindrome = is_palindrome_recursive(str, length);
	#else
	is_palindrome = is_palindrome_iterative(str, length);
	#endif

	printf("Is it a palindrome? %d\n", is_palindrome);

	return 0;
}

#endif
