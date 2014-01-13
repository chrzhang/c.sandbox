#include <stdio.h>
#include <math.h>
#define SIZE	100

main() {
	int n, array[SIZE], getint(int *), getfloat(float *);
	for (int i = 0; i < SIZE; ++i) {
		array[i] = -1;
	}
	for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
		;
	for (int i = 0; array[i] != -1; ++i) {
		printf("%d\n", array[i]);
	}
	getch();

	float arrayFloats[SIZE];
	for (int i = 0; i < SIZE; ++i) {
		arrayFloats[i] = -1.f;
	}
	for (n = 0; n < SIZE && getfloat(&arrayFloats[n]) != EOF; n++)
		;
	for (int i = 0; arrayFloats[i] != -1.f; ++i) {
		printf("%g\n", arrayFloats[i]);
	}

	getch();
	getch();
	return 0;
}

/*
(Exercise 5-1)
As written, getint treats a + or - not followed by a digit as a valid
representation of zero. Fix it to push such a character back on the input.
*/
/* getint: get next integer from input into *pn */
int getint(int *pn) {
	int c, sign;
	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); /* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	if (!isdigit(c)) {
		ungetch(c);
		return 0;
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

/*
(Exercise 5-2)
Write getfloat, the floating-point analog of getint. What type does getfloat
return as its function value?

The return type in getint is an integer. It signifies a flag for the outcome of function
execution. For this reason, in getfloat, the return type need only be an integer because the
types of return values have not changed. (0 for not a number, positive if the input contains
a valid number).
*/
int getfloat(float *pn) {
	int c, sign;
	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); /* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	if (!isdigit(c)) {
		ungetch(c);
		return 0;
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	if (c == '.') { // Collect fractional part
		int currentPower = -1;
		while (isdigit(c = getch())) {
			*pn += pow(10, currentPower) * (c - '0');
			--currentPower;
		}
	}
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}