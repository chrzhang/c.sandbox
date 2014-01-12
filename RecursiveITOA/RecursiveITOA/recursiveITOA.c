#include <stdio.h>
#define MAXLINE	100
void itoa(int n, char s[]);
void itoaAux(int n, char s[], int i);
void printd (int n);

main() {
	char s[MAXLINE];
	for (int i = -15; i < 16; ++i) {
		printf("\t\ti = %d\n", i);
		itoa(i, s);
		printf("%s\n", s);
	} 
	getch();
	return 0;
}

/*
(Exercise 4-12)
Adapt the ideas of printd to write a recursive version of itoa; that is, convert
an integer into a string by calling a recursive routine.
*/
void itoa(int n, char s[]) {
	itoaAux(n, s, 0);
}

void itoaAux(int n, char s[], int i) {
	static int j = 0;
	if (!i)
		j = 0; // Reset on first-call
	if (n < 0) {
		putchar('-'); // When negative, slap on a '-' sign
		n = -n;
	}
	if (n / 10) // If the number is greater than or equal to 10
		itoaAux(n / 10, s, (i + 1)); // Recursively deepen until n is less than 10 (this is the first digit), print it, then wind up and...
	if (i > j)
		j = i; // Keep a store of the maximum places
	s[j-i] = (n % 10 + '0'); // Print the digit place number as a character
	if (i == j)
		s[++i] = '\0'; // Null-terminate the string
}

/* printd: print n in decimal */
void printd (int n) {
	if (n < 0) {
		putchar('-'); // When negative, slap on a '-' sign
		n = -n;
	}
	if (n / 10) // If the number is greater than or equal to 10
		printd(n / 10); // Recursively deepen until n is less than 10, print it, then wind up and...
	putchar(n % 10 + '0'); // Print the digit place number as a character
}