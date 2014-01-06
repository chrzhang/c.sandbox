#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

int main() {
	// (Exercise 2-1)
	// Determine ranges of char, short, int, long, both signed and unsigned
	// Determine ranges of various floating-point types
	printf("\t\tUsing <limits.h> library definitions...\n");
	printf("CHAR\n");
	printf("signed char max: %d\n", SCHAR_MAX);
	printf("unsigned char max: %u\n", UCHAR_MAX); // Note use of u, formatting output
	printf("signed char min: %d\n", SCHAR_MIN);
	printf("SHORT\n");
	printf("signed short min: %d\n", SHRT_MIN);
	printf("signed short max: %d\n", SHRT_MAX);
	printf("unsigned short max: %d\n", USHRT_MAX);
	printf("INT\n");
	printf("signed int max: %d\n", INT_MAX);
	printf("unsigned int max: %u\n", UINT_MAX); 
	printf("signed int min: %d\n", INT_MIN);
	printf("LONG\n");
	printf("signed long max: %d\n", LONG_MAX);
	printf("unsigned long max: %u\n", ULONG_MAX);
	printf("signed long min: %d\n", LONG_MIN);
	printf("FLOAT\n");
	printf("signed float max: %e\n", FLT_MAX);
	printf("signed float min: %e\n", FLT_MIN);
	printf("DOUBLE\n");
	printf("signed double max: %e\n", DBL_MAX);
	printf("signed double min: %e\n", DBL_MIN);
	
	printf("\n\t\tUsing computation...\n");
	//////////////////////////////////////////////////////////////////
	printf("CHAR\n");
	// Find the greatest power of 2 not to create a sign flip
	signed char signedCharMax;
	signedCharMax = 1;
	while (signedCharMax > 0) {
		signedCharMax *= 2;
		if ((signed char)(2 * signedCharMax) <= 0) // Has flipped sign
			break; // Done
	}
	// In binary for this char, this fills the first digit from the left with a 1
	// To find the maximum possible, consider the bits that follow
	// Filling all of them with 1 adds a number that is 1 less than the current signed
	// char max.
	signedCharMax += signedCharMax - 1;
	printf("signed char max: %d\n", signedCharMax);

	unsigned char unsignedCharMax;
	unsignedCharMax = 1;
	while (unsignedCharMax > 0) {
		unsignedCharMax *= 2;
		if ((unsigned char)(2 * unsignedCharMax) < 0)
			break;
	}
	unsignedCharMax += unsignedCharMax - 1;
	printf("unsigned char max: %d\n", unsignedCharMax);

	// To find the min of signed chars find the greatest power of -2 that won't sign-flip
	signed char signedCharMin;
	signedCharMin = -1;
	while (signedCharMin < 0) {
		signedCharMin *= 2;
		if (((signed char) (2 * signedCharMin)) >= 0)
			break;
	}
	printf("signed char min: %d\n", signedCharMin);

	//////////////////////////////////////////////////////////////////
	printf("SHORT\n");
	signed short signedShortMin;
	signedShortMin = -1;
	while (signedShortMin < 0) {
		signedShortMin *= 2;
		if ((signed short)(2 * signedShortMin) >= 0)
			break;
	}
	printf("signed short min: %d\n", signedShortMin);
	
	signed short signedShortMax;
	signedShortMax = 1;
	while (signedShortMax > 0) {
		signedShortMax *= 2;
		if ((signed short)(2 * signedShortMax) <= 0) // Has flipped sign
			break; // Done
	}
	signedShortMax += signedShortMax - 1;
	printf("signed short max: %d\n", signedShortMax);

	unsigned short unsignedShortMax;
	unsignedShortMax = 1;
	while (unsignedShortMax > 0) {
		unsignedShortMax *= 2;
		if ((unsigned short)(2 * unsignedShortMax) <= 0)
			break;
	}
	unsignedShortMax += unsignedShortMax - 1;
	printf("unsigned short max: %d\n", unsignedShortMax);

	//////////////////////////////////////////////////////////////////
	printf("INT\n");
	signed int signedIntMax;
	signedIntMax = 1;
	while (signedIntMax > 0) {
		signedIntMax *= 2;
		if ((signed int)(2 * signedIntMax) <= 0)
			break;
	}
	signedIntMax += signedIntMax - 1;
	printf("signed int max: %d\n", signedIntMax);

	unsigned int unsignedIntMax;
	unsignedIntMax = 1;
	while (unsignedIntMax > 0) {
		unsignedIntMax *= 2;
		if ((unsigned int)(2 * unsignedIntMax) <= 0)
			break;
	}
	unsignedIntMax += unsignedIntMax - 1;
	printf("unsigned int max: %u\n", unsignedIntMax);

	signed int signedIntMin;
	signedIntMin = -1;
	while (signedIntMin < 0) {
		signedIntMin *= 2;
		if ((signed int)(2 * signedIntMin) >= 0)
			break;
	}
	printf("signed int min: %d\n", signedIntMin);

	//////////////////////////////////////////////////////////////////
	printf("INT\n");
	signed long signedLongMax;
	signedLongMax = 1;
	while (signedLongMax > 0) {
		signedLongMax *= 2;
		if ((signed long)(2 * signedLongMax) <= 0)
			break;
	}
	signedLongMax += signedLongMax - 1;
	printf("signed long max: %d\n", signedLongMax);

	unsigned long unsignedLongMax;
	unsignedLongMax = 1;
	while (unsignedLongMax > 0) {
		unsignedLongMax *= 2;
		if ((unsigned long)(2 * unsignedLongMax) <= 0)
			break;
	}
	unsignedLongMax += unsignedLongMax - 1;
	printf("unsigned long max: %u\n", unsignedLongMax);

	signed long signedLongMin;
	signedLongMin = -1;
	while (signedLongMin < 0) {
		signedLongMin *= 2;
		if ((signed long)(2 * signedLongMin) >= 0)
			break;
	}
	printf("signed long min: %d\n", signedLongMin);

	//////////////////////////////////////////////////////////////////
	printf("FLOAT\n");
	// The IEEE-754 standard defines representation of a single-precision number as 32 bits
	// For a double, its precision is twice as much, or 64 bits.
	// A float has 8 bits for the exponent and 23 bits for the mantissa
	// Note that the library definitions are for the mantissa, the bit that follows the 1. 
	// for normalized floats.
	// Below, E is the number of bits for the exponent
	// The maximum value is
	// 2 ^ MAX_POWER * MAX_MANTISSA
	// = 2 ^(2^(E-1)-1)) * (1 + (2^M-1)/2^M)
	double MAX_POWER;
	double MAX_MANTISSA;
	// The sign is set to positive
	// Given 8 positions for exponent, the maximum number representable in 8 bits is (2^(8-1)-1)
	MAX_POWER = pow(2, 7) - 1; // 11111111 is reserved for infinities and NaNs so the max is 1 less
	// The mantissa looks like 11111111111111111111111 (binary)
	// Its value is 2^-1 + 2^-2 + ... + 2^-23
	// Or 1/2 + 1/4 + ... + 1/(2^23)
	// If this were an infinite series and a computer operated on pure math, it would converge to 1
	// This is because the sum can be written as s = 1 - 1/(2^n) and n approaching infinity gives 1
	// Given this is normalized, there is a 1 to be added to this decimal part
	// Use some calculation to get the closest value
	MAX_MANTISSA = 1 + (1 - 1 / (pow(2, 23)));
	float floatMax = pow(2, MAX_POWER) * MAX_MANTISSA;
	printf("signed float max: %e\n", floatMax);

	double MIN_POWER;
	double MIN_MANTISSA;
	MIN_POWER = -(pow(2, 7) - 2); // This gives -126, which is the least exponent possible for normal #s
	// The mantissa looks like 00000000000000000000001
	// Again, due to the library definition being normalized, there is a 1. before the decimal part
	MIN_MANTISSA = 1 + pow(2, -23);
	float floatMin = pow(2, MIN_POWER) * MIN_MANTISSA;
	printf("signed float min: %e\n", floatMin);

	//////////////////////////////////////////////////////////////////
	printf("DOUBLE\n");
	double MAX_POWER2;
	double MAX_MANTISSA2;
	// A double has 11 bits for the exponent and 52 bits for the mantissa
	MAX_POWER2 = pow(2, 10) - 1;
	MAX_MANTISSA2 = 1 + (1 - 1 / (pow(2, 52)));
	double doubleMax = pow(2, MAX_POWER2) * MAX_MANTISSA2;
	printf("signed double max: %e\n", doubleMax);

	double MIN_POWER2;
	double MIN_MANTISSA2;
	MIN_POWER2 = -(pow(2, 10) - 2);
	MIN_MANTISSA2 = 1 + pow(2, -52);
	double doubleMin = pow(2, MIN_POWER2) * MIN_MANTISSA2;
	printf("signed double min: %e\n", doubleMin);

	getch();
	return 0;
}