#include <stdio.h>

/*
Prints temperature conversions.
*/
main() {
	int fahr, celsius;
	int lower, upper, step;
	lower = 0; // Starting point
	upper = 300; // End condition
	step = 20; // Increment size
	fahr = lower; // Initialize to starting point
	//  Loop through
	while (fahr <= upper) {
		celsius = 5 * (fahr - 32) / 9; // Compute
		printf("%d\t%d\n", fahr, celsius); // Modify and format output
		fahr = fahr + step; // Step to the next iteration
	}
	getch();
}