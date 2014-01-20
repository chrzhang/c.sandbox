#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "getword.h"

#define NKEYS (sizeof keytab / sizeof(keytab[0]))
#define MAXWORD 100

struct key {
	char *word;
	int count;
} keytab[] = {
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	/* ... */
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0
};

static int inAQuote = 0;

/* count C keywords */
main() {
	int n;
	char word[MAXWORD];
	while (getwordFix(word, MAXWORD) != EOF) {
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
				keytab[n].count++;
			}
	}
	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0) // Print only used keywords
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
	return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n) {
	int cond;
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	while (isspace(c = getch())) // Ignore whitespace
		;
	if (c != EOF) // Not at the end of the file, set the next char in word to the next non-space
		*w++ = c;
	if (!isalpha(c)) { // If the char isn't a letter, end the current word
		*w = '\0';
		return c; // Return the non-alpha char
	}
	for (; --lim > 0; w++) // Now, provided the char was a letter, get the rest into w
		if (!isalnum(*w = getch())) {
			ungetch(*w); // Unget the non-alphanumeric part of that word
			break;
		}
	*w = '\0'; // End the string
	return word[0];
}

/*
(Exercise 6-1)
Our version of getword does not properly handle underscores, string constants,
comments, or preprocessor control lines. Write a better version.

First, how is the CURRENT version NOT properly "handling" each of the above?
-underscores (ex. _char)
	The program by the book will not consider underscores next to valid words as
	part of the word. _char will still increase the count of char.
	This is because the program looks at a non-alpha char like _ and immediately
	considers it as its own animal without checking what comes after. To fix,
	an else statement dealing for the EOF case is handled as well as further
	inspection on what is following the non-alpha char. If it's a space, operate 
	as such in the old getword. If not, do not give preferential treatment.
-string constants (ex. " char ")
	A similar fix as above, except for " instead of _. However, in further study,
	the keyword in quotes "char" will not be considered but " char " will. In both
	cases, the keywords are used as part of a string constant and not as a keyword.
-comments (ex. "//" comments only)
	Since the desired input of this program is code, ignore what follows comments.
	**For ignoring block comments, implement something similar to quotes with an inBlockQuote
-preprocessor control lines
	#define volatile	1 should not return a count for volatile, the keyword is not
	being used in its traditional fashion.
*/
/* getword: get next word or character from input */
int getwordFix(char *word, int lim) {
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	char *temp = word;
	while (isspace(c = getch())) // Ignore whitespace
		;
	if (c != EOF) // Not at the end of the file, set the next char in word to the next non-space
		*w++ = c;
	// If the next char is a space and this is not alpha, end the word
	else { // Ah, the EOF!
		*w = '\0';
		return c;
	}
	if (!isalpha(c)) {
		if (c == '\"') {
			if (inAQuote)
				inAQuote = 0; // Exited the quote
			else {
				inAQuote = 1;
				// Get everything until the end of the quote
				while ((c = getch()) != '\"')
					if (c == EOF) {
						printf("error: quote never ends.\n");
						return EOF;
					}
				ungetch(c);
			}
		}
		else if (c == '/') {
			if ((c = getch()) == '/') {
				// Ignore everything that follows, assuming the loop in main is called once per line in real-code application
				return EOF;
			}
			else
				ungetch(c);
		}
		else if (c == '#') {
			// Ignore everything that follows, assuming the loop in main is called once per line in real-code application
			return EOF;
		}
		if (isspace(*temp = getch())) { // Check for a succeeding space
			*w = '\0';
			return c; // Return the non-alpha char
		}
		else // Oops, succeeded by part of a word, give the char back
			ungetch(*temp);
	}
	for (; --lim > 0; w++) // Now, provided the char was a letter, get the rest into w
	if (!isalnum(*w = getch())) {
		ungetch(*w); // Unget the non-alphanumeric part of that word
		break;
	}
	*w = '\0'; // End the string
	return word[0];
}