#include <stdio.h>
#define IN	1 /* in a word */
#define OUT	0 /* not in a word */

int characterCount1();
int characterCount2();
int lineCount();
int blankTabNLCount();
int limitBlanks();
int replaceEscapeSeqs();
int lnWordCharCount();
int printOneWordPerLine();

/* Copy input to output. */
int main() {
	int c; // Can store any character as well as EOF
	printf("What is the value of EOF?\n"); // (Exercise 1.7)
	printf("%d\n", EOF);
	// Grab a char from  user-input (keyboard)
	while ((c = getchar()) != EOF) { 
		// As long as the user entered a non-empty string
		// (Exercise 1.6) int b = c != EOF; // Verify != returns 0 or 1
		// printf("%d\n", b);
		putchar(c); // Print what they just submitted
	}
	printf("Starting character counter.\n");
	characterCount1();
	printf("Starting second character counter.\n");
	characterCount2();
	printf("Starting line counter.\n");
	lineCount();
	printf("Starting blank-tab-newline counter.\n");
	blankTabNLCount();
	printf("Starting blank replacement.\n");
	limitBlanks();
	printf("Starting escape sequence replacement.\n");
	replaceEscapeSeqs();
	printf("Starting one word-per-line changer.\n");
	printOneWordPerLine();
	// NOTE: On Windows, Ctrl+Z gives the EOF character
	getch();
	return 0;
}

/* Count characters in input. */
int characterCount1() {
	long nc;
	nc = 0;
	while (getchar() != EOF)
		++nc; // Increment by one
	printf("Count of characters:\t");
	printf("%ld\n", nc); // Note formatting %ld for a long type
	return 0;
}

/* Count characters in input using a double. */
int characterCount2() {
	double nc;
	for (nc = 0; getchar() != EOF; ++nc) {}
	printf("Count of characters:\t");
	printf("%.0f\n", nc); // Want no digits after a decimal point
	return 0;
}

/* Count lines in input. */
int lineCount() {
	int c, nl;
	nl = 0;
	while ((c = getchar()) != EOF)
		if (c == '\n') // Increment with each new-line char found
			++nl;
	printf("Count of lines:\t");
	printf("%d\n", nl);
	return 0;
}

/* (Exercise 1-8) Count blanks, tabs, and newlines. */
int blankTabNLCount() {
	int c, blanks, tabs, nl;
	blanks = tabs = nl = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\n')
			++nl;
		else if (c == '\t')
			++tabs;
		else if (c == ' ')
			++blanks;
	}
	printf("Count of lines:\t%d\n", nl);
	printf("Count of tabs:\t%d\n", tabs);
	printf("Count of blanks:\t%d\n", blanks);
	return 0;
}

/* (Exercise 1-9) Copy input to output. 
Replace each string of one or more blanks by a single blank. */
int limitBlanks() {
	int c;
	while ((c = getchar()) != EOF) {
		// Check if it is a string of one or more blanks.
		if (c == ' ') { // A blank has been found
			putchar(c);
			// Do not act on additional spaces after it
			while ((c = getchar()) == ' ' && c != EOF) {}
		}
		if (c == EOF) // End of file has been reached
			break;
		putchar(c); // The input does not contain a single blank
	}
	return 0;
}

/* (Exercise 1-10) Replace actual tabs by \t, backspaces by \b and backslashes by \\. */
int replaceEscapeSeqs() {
	int c;
	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			putchar('\\');
			putchar('t');
		}
		else if (c == '\b') {
			putchar('\\');
			putchar('b');
		}
		else if (c == '\\') {
			putchar('\\');
		}
		else
			putchar(c);
	}
	return 0;
}

/* Counter for lines, words, and characters in input. */
int lnWordCharCount() {
	int c, nl, nw, nc, state;
	state = OUT;
	nl = nw = nc = 0; // Initialize count for lines, words, and characters to 0
	while ((c = getchar()) != EOF) {
		++nc; // Increment character count
		if (c == '\n') // At the end of a line
			++nl; // So increment line counter
		if (c == ' ' || c == '\n' || c == '\t') // Definition of a delimiter for words
			state = OUT; // Change state
		else if (state == OUT) { // If between words
			state = IN; // Go inside the next word
			++nw; // Increment word counter
		}
	}
	printf("%d %d %d\n", nl, nw, nc);
	/* (Exercise 1-11) To test the word count program, enter expected input such as 
	a file containing a mix of tabs, spaces, and newlines. Then, to check for bugs, 
	test the program with a file containing no data, only tabs, only newlines,
	only blanks, and finally a large amount that will reveal the limitations of using
	an int as a count for the occurrences.*/
	return 0;
}

/* (Exercise 1-12) Prints input one word per line. */
int printOneWordPerLine() {
	int c;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') // A break between words encountered
			putchar('\n'); // Print a newline to separate
		else
			putchar(c);
	}
	return 0;
}