#include <stdio.h>
#include <inttypes.h>
#include <math.h>

union Floatbits {
	float f;
	struct {
		uint32_t mantissa:23;
		uint32_t exponent:8;
		uint32_t sign:1;
	} parts;
};

void print_binary(uint32_t num, int bits)
{
	for (int mask = 1 << bits; mask != 0; mask >>= 1)
		putchar((mask & num) ? '1' : '0');
}

int main(void)
{
	float eps = 1;
	while (1 + eps != 1)
		eps /= 2;

	float vals[] = {
		0, 1, 2, 2.5, 16.5, -1, 1.5, 1.75, 6e30, -INFINITY, NAN, eps,
		1 + eps, 1 + (2 * eps)
	};

	int nvals = sizeof(vals) / sizeof(vals[0]);

	printf("Sign  Mantissa                    Exponent  Value\n");
	for (int i = 0; i < nvals; i++)
	{
		union Floatbits bits;
		bits.f = vals[i];

		// Sign is a single bit: 0 or 1
		printf("%d     ", bits.parts.sign);

		// Print mantissa usual human-readable way. Put a "1." before it,
		// since that's how it is actually interpreted. Of course the mantissa
		// is all the stuff _after_ the "1."
		printf("1.");
		print_binary(bits.parts.mantissa, 23);

		// Value of the exponent: exponent - 127. Must store it in
		// an int first, since unsigned ints can't go negative.
		int expval = bits.parts.exponent;
		expval -= 127;
		printf("  %4d      ", expval);

		// Actual value of the float
		printf("%g\n", bits.f);
	}

}
