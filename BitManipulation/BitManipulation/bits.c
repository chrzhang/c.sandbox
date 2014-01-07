#include <stdio.h>
#include <math.h>

unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned invert(unsigned x, int p, int n);
unsigned rightrot(unsigned x, int n);
int bitcount(unsigned x);

int main() {
	printf("%u\n", getbits(9846, 3, 4));
	// 9846 is 10011001110110 in binary
	// Expected output is 4 bits from position 3 which is 0110 or 6
	printf("Expected: 6\n");
	printf("%u\n", setbits(54151, 8, 5, 39));
	// 54151 is 1101001110000111 in binary
	// 39 is 100111 in binary
	// Expected output is replacing bits 8 - 4 with 00111 so 1101001001110111 or 53879
	printf("Expected: 53879\n");
	printf("%u\n", invert(749, 7, 5));
	// 749 is 1011101101 in binary and inverting five bits from position 5 would end in
	// 1000010101 or 533
	printf("Expected: 533\n");
	printf("%u\n", rightrot(229, 3));
	// 229 is 11100101 in binary
	// Expected output is 10111100 or 188
	printf("Expected: 188\n");
	printf("%d\n", bitcount(8));
	// 8 is 1000 in binary so expect 1
	printf("Expected: 1\n");
	printf("%d\n", bitcount(7));
	// 8 is 111 in binary so expect 3
	printf("Expected: 3\n");
	getch();
	return 0;
}

// Get n bits from position p
unsigned getbits(unsigned x, int p, int n) {
	return (x >> (p + 1 - n)) & ~(~0 << n);
	// x >> (p+1-n) MOVES the desired field to the right end of the word
	// ~0, all 1 bits, so SHIFTING it left n positions puts 0s in the rightmost n bits
	// Complementing this with ~ makes a mask with ones in the rightmost n bits
}

/*
(Exercise 2-6)
Write a function setbits(x,p,n,y) that returns
x with the n bits that begin at p
set to the rightmost n bits of y
leaving the other bits unchanged.
*/
unsigned setbits(unsigned x, int p, int n, unsigned  y) {
	int mask = (1 << n) - 1; // Decrementing makes the mask 01111 instead of 10000 when n=5
	y = (y & mask) << (p - n + 1); // Apply the mask and shift result left by p-n+1 places
	// Now the digits to be replaced in x have the same posisition as those in y
	// Zero out the old values of x that will be replaced
	// Create a mask
	mask = ~(((1 << n) - 1) << (p - n + 1)); // Before the negation, this looks like 011110000; after negation, it resembles 100001111
	x &= mask; // Zeroing out the old values
	return x | y; // Combine
}

/*
(Exercise 2-7)
Invert n bits that begin at p.
*/
unsigned invert(unsigned x, int p, int n) {
	// Get the part that should be inverted
	int mask = (1 << n) - 1;
	unsigned y = x & (mask << (p - n + 1)); // Shifting the mask and applying it
	// Bit-wise invert
	y = ~y;
	// The invert will also apply to the filler 0s at the beginning so re-apply the mask
	y &= (mask << (p - n + 1));
	// Clear the area in the original
	mask = ~(((1 << n) - 1) << (p - n + 1));
	x &= mask;
	// OR y with it
	return x | y;
}

/*
(Exercise 2-8)
Rotate an integer right by n positions.
Due to unclear wording and in light of the current topic,
the following implementation will be by bits rather than decimal digits.
*/
unsigned rightrot(unsigned x, int n) {
	// Find the leftmost 1
	// The leftmost 1 is the highest power of 2 that will fit in the representation
	int highestPower;
	for (highestPower = 0; (unsigned int) pow(2, highestPower) <= x; ++highestPower) {}
	if (highestPower > 0)
		--highestPower;
	// Create and apply the mask to the rightmost n digits
	int mask = (1 << n) - 1;
	int y = x & mask;
	y = y << (highestPower - n + 1); // Shift result left, leaving the specified amount of blanks on the right
	x = x >> n; // Shift the original value right
	return x | y; // After shift, zeroes guaranteed to appear on left of original value so do a bitwise OR
}

/*
(Exercise 2-9)
In two's complement, x &= (x-1) deletes the rightmost 1-bit in x.
Explanation:
Subtracting 1 from x flips the rightmost 1 bit and flips all the zeroes that follow. 
8 is 1000
7 is 0111.
Anding these together will delete the rightmost bit in 8 which happens to be the only one. 
Write a faster version of bitcount.
It counts 1 bits in x.
*/
int bitcount(unsigned x) {
	int b;
	for (b = 0; x != 0; x &= (x - 1)) // Delete the rightmost 1-bit until there are none
		++b;
	return b;
}