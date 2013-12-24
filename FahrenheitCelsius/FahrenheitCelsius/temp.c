#include <stdio.h>

/*
Prints temperature conversions.
*/
main() {
	float fahr, celsius;
	float lower, upper, step;
	lower = 0; // Starting point
	upper = 300; // End condition
	step = 20; // Increment size
	fahr = lower; // Initialize to starting point
	// Print a heading (Exercise 1-3)
	printf("%3c\t%6c\n", 'F', 'C');
	//  Loop through
	while (fahr <= upper) {
		celsius = (5.0 / 9.0) * (fahr - 32); // Compute
		printf("%3.0f\t%6.1f\n", fahr, celsius); // Modify and format output
		// fahr printed at least 3 chars wide with no decimal point
		// celsius to be printed at least six characters wide with 1 digit after the decimal
		fahr = fahr + step; // Step to the next iteration
	}
	celsiusToFahr();
	getch();
}

// Program to convert celsius to fahrenheit (Exercise 1-4)
celsiusToFahr() {
	float fahr, celsius;
	float lower, upper, step;
	lower = 0; // Starting point
	upper = 300; // End condition
	step = 20; // Increment size
	celsius = lower; // Initialize to starting point
	// Print a heading
	printf("%6c\t%3c\n", 'C', 'F');
	// Loop through
	while (celsius <= upper) {
		fahr = (9.0 / 5.0) * celsius + 32; // Compute
		printf("%6.1f\t%3.0f\n", celsius, fahr);
		celsius = celsius + step;
	}
}