#include <stdio.h>

/* Copy input to output. */
main() {
	int c; // Can store any character as well as EOF
	printf("What is the value of EOF?\n"); // (Exercise 1.7)
	printf("%d\n", EOF);
	// Grab a char from  user-input (keyboard)
	while ((c = getchar()) != EOF) { // As long as the user entered a non-empty string
		// (Exercise 1.6) int b = c != EOF; // Verify that != returns 0 or 1
		// printf("%d\n", b);
		putchar(c); // Print what they just submitted
		c = getchar(); // and wait for more input
	}
}