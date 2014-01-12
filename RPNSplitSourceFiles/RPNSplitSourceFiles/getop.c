#include <stdio.h>
#include <ctype.h>
#include "calc.h"

getop(char s[]) {
	/*
	(Exercise 4-11)
	Modify getop so that it doesn't need to use ungetch. Hint: use an internal
	static variable.
	ungetch() returns the character c to the buffer as long as it's not an EOF
	To replace this, a static int variable called last will hold this character
	for the following function call's review.
	*/
	int i, c;
	static int last = EOF; // Initialize 
	if (last == EOF || last == ' ' || last == '\t') {
		while ((s[0] = c = getch()) == ' ' || c == '\t')
			; // Skip empty space
	}
	else { // Part of an operand or a number
		c = last;
		s[0] = c;
	}
	// Reset the buffer
	last = EOF;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c; /* not a number */
	i = 0;
	if (isdigit(c)) /* collect integer part */
	while (isdigit(s[++i] = c = getch()))
		;
	if (c == '.') /* collect fraction part */
	while (isdigit(s[++i] = c = getch()))
		;
	s[i] = '\0';
	if (c != EOF)
		last = c; // Store the following character
	return NUMBER;
}