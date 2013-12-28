#include <stdio.h>

// Symbolic constants
#define LOWER	0 /* Lower bound */
#define UPPER	300 /* Upper bound */
#define STEP	20 /* Incremental size */

int celsiusToFahr();
int fahrToCelsiusForLoop();
int fahrToCelsiusReverse();

/*
Prints temperature conversions.
*/
int main() {
	float fahr, celsius;
	fahr = LOWER; // Initialize to starting point
	// Print a heading (Exercise 1-3)
	printf("%3c\t%6c\n", 'F', 'C');
	//  Loop through
	while (fahr <= UPPER) {
		celsius = (5.0 / 9.0) * (fahr - 32); // Compute
		printf("%3.0f\t%6.1f\n", fahr, celsius); // Modify and format output
		// fahr printed at least 3 chars wide with no decimal point
		// celsius to be printed at least six characters wide with 1 digit after the decimal
		fahr = fahr + STEP; // Step to the next iteration
	}
	printf("Now do a conversion with the same bounds from Celsius to Fahrenheit.\n");
	celsiusToFahr();
	printf("Repeat the first conversion using a for loop.\n");
	fahrToCelsiusForLoop();
	printf("Repeat the first conversion in reverse using a for loop.\n");
	fahrToCelsiusReverse();
	getch();
	return 0;
}

// Program to convert celsius to fahrenheit (Exercise 1-4)
int celsiusToFahr() {
	float fahr, celsius;
	celsius = LOWER; // Initialize to starting point
	// Print a heading
	printf("%6c\t%3c\n", 'C', 'F');
	// Loop through
	while (celsius <= UPPER) {
		fahr = (9.0 / 5.0) * celsius + 32; // Compute
		printf("%6.1f\t%3.0f\n", celsius, fahr);
		celsius = celsius + STEP;
	}
	return 0;
}

// For statement that does the same conversion
int fahrToCelsiusForLoop() {
	int fahr;
	for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
		printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
	return 0;
}

// For statement that does the conversion in reverse (Exercise 1-5)
int fahrToCelsiusReverse() {
	int fahr;
	for (fahr = UPPER; fahr >= LOWER; fahr = fahr - STEP)
		printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
	return 0;
}