#include <stdio.h>
#define IN	1
#define OUT	0

int printHistogram();
int printFrequencies();

/* Count digits, white-space, other */
int main() {
	int c, i, nwhite, nother;
	int ndigit[10]; // Declare an array
	nwhite = nother = 0;
	for (i = 0; i < 10; ++i)
		ndigit[i] = 0; // Initialize array contents to 0
	while ((c = getchar()) != EOF)
		if (c >= '0' && c <= '9')
			++ndigit[c - '0']; // Numeric value of c when c is digit
		else if (c == ' ' || c == '\n' || c == '\t')
			++nwhite;
		else
			++nother;
	printf("digits =");
	for (i = 0; i < 10; ++i)
		printf(" %d", ndigit[i]);
	printf(", white space = %d, other = %d\n", nwhite, nother);
	getch();
	printf("Print a histogram for word lengths.\n");
	printHistogram();
	printf("Print frequencies of various character occurrences.\n");
	printFrequencies();
	getch();
	return 0;
}

/* (Exercise 1-13) Print a histogram of lengths of words in input.
Do this horizontally and as a challenge, vertically.*/
int printHistogram() {
	int nchars[11]; // Indices 0-10, representing the various counts
	for (int z = 0; z < 11; ++z)
		nchars[z] = 0;
	int c, thisWordLength, state;
	state = OUT;
	thisWordLength = 0;
	while ((c = getchar()) != EOF) {
		// Reached the end of a word
		if (c == ' ' || c == '\n' || c == '\t') {
			state = OUT; // Mark state
			if (thisWordLength > 10) // Cap it at a maximum of 9, 10 stands for > 9
				thisWordLength = 10;
			++nchars[thisWordLength]; // Increment appropriate index
			thisWordLength = 0; // Reset current word-length count
		}
		else if (state == OUT) { // Not escape seq., start of new word
			state = IN;
			++thisWordLength;
		}
		else // Inside a word
			++thisWordLength;
	}
	// HORIZONTAL HISTOGRAM
	for (int i = 1; i < 10; ++i) {
		// For each length from 1 to 9
		printf(" %d: ", i);
		for (int j = 0; j < nchars[i]; ++j) {
			printf("X");
		}
		printf("\n");
	}
	// For the special index 10 
	printf(">9: ");
	for (int j = 0; j < nchars[10]; ++j) {
		printf("X");
	}
	printf("\n");
	// VERTICAL HISTOGRAM
	// Input printed by lines, so find max in the array first
	int max = 0;
	for (int i = 0; i < 11; ++i) {
		if (nchars[i] > max)
			max = nchars[i];
	}
	for (int i = max; i > 0; --i) {
		// For each line
		// Go through the array
		for (int a = 1; a < 11; ++a) {
			// Print whether its count is greater than or equal to current line level
			if (nchars[a] >= i)
				printf("X\t");
			else
				printf(" \t");
		}
		//printf("\n"); // The tab-characters fill a line in a standard terminal window, uncomment if need-be
	}
	// At the very end, print the labels to clarify output
	for (int b = 1; b < 10; ++b)
		printf("%d\t", b);
	printf(">9\n");
	return 0;
}

/* (Exercise 1-14) Print a histogram of of the frequencies of different characters in its input. */
int printFrequencies() {
	// With what is given, it is difficult to determine possible character inputs
	// ASSUME that users are 
	// Create a 128 index array
	int freqs[128]; // Indices 0-127
	int c; // Current char
	for (int i = 0; i < 128; ++i)
		freqs[i] = 0; // 0-initialize array
	while ((c = getchar()) != EOF) {
		++freqs[c]; // Increment for each type of char
	}
	for (int i = 0; i < 128; ++i) {
		char y = (char) i;
		printf("%d:\t", i);
		printf("%1c\t", y);
		for (int u = 0; u < freqs[i]; ++u) {
			printf("X");
		}
		printf("\n");
	}
	return 0;
}