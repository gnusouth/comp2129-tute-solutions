#include <stdio.h>
#include <inttypes.h>

int8_t set_msb(int8_t);

union int8bits
{
	int8_t val;

	struct
	{
		uint8_t rest: 7;
		uint8_t msb: 1;
	} parts;
};


int main()
{
	union int8bits ibits;

	// View some integers
	for (ibits.val = -3; ibits.val <= 3; ibits.val++)
	{
		printf("Value: %4d, MSB: %d, Rest: %3d\n", ibits.val, ibits.parts.msb, ibits.parts.rest);

		// Set the MSB on each of them
		int8_t different = set_msb(ibits.val);
		printf("Value after setting MSB to 1: %3d\n", different);
	}

	// Look at 127
	int8_t num = 127;
	int8_t num_alt = set_msb(num);
	printf("%d after setting the MSB to 1 becomes %d\n", num, num_alt);

	return 0;
}


int8_t set_msb(int8_t number)
{
	union int8bits temp;
	temp.val = number;
	temp.parts.msb = 1;
	return temp.val;
}
