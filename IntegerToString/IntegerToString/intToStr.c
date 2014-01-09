#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <math.h> 

void itoaMod(int n, char s[]);
void itoa(int n, char s[]);
void reverse(char s[]);

int main() {
	int x = INT_MIN;
	printf("The largest two's complement negative number is: %d\n", INT_MIN);
	char numberStr[1000];
	itoa(x, numberStr);
	printf("%s\n", numberStr);
	printf("Hmm, the original itoa function doesn't seem to work.\n");
	printf("Using updated itoa.\n");
	itoaMod(x, numberStr);
	printf("%s\n", numberStr);
	printf("Make sure the modified version works for some normal numbers.\n");
	for (x = -999; x < 1000; x += 50) {
		itoaMod(x, numberStr);
		printf("%s\n", numberStr);
	}
	getch();
	return 0;
}

/*
(Exercise 3-4)
In a two's complement number representation, our version of itoa does not
handle the largest negative number, that is, the value of n equal to -(2^wordsize-1). Explain why not.

The magnitude of the largest negative number in two's complement cannot be expressed unsigned with the same number of bits.
With 5 given bits, the maximum negative value is -16 or 10000 but the maximum positive value is 15 or 01111.
There are 32 values that range from 15 to -16. There are five bits, allowing for only 32 unique combinations.
There is no room to store a +16 representation.
Hence, the part in itoa that "makes n positive" will not work.
It will make -16 become something other than 16 (since there is no legal 16 in 5-bits).

Modify it to print that value correctly, regardless of the machine on which it runs.

The crux of the problem is solved when a sign variable is used for dealing with the divisions. Rather than attempt to convert -16 to 16, maintain
-16 as -16. Consider the power of the base raised to the desired power, then negating the result.
Comparisons will allow the correct answer to result because the highest power of 10 less than magnitude 16 is 1 and 10^highestPower can be represented
in both its original and negated forms.

itoaMod converts n to characters in s
*/
void itoaMod(int n, char s[]) {
	int i;
	int sign = (n >= 0) ? 1 : -1;
	i = 0;
	do { /* generate digits in reverse order */
		s[i++] = sign * (n % 10) + '0'; /* get next digit */
	} while ((n /= 10) != 0); /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/* The original itoa that converts n to characters in s*/
void itoa(int n, char s[]) {
	int i, sign;
	if ((sign = n) < 0) /* record sign */
		n = -n; /* make n positive */
	i = 0;
	do { /* generate digits in reverse order */
		s[i++] = n % 10 + '0'; /* get next digit */
	} while ((n /= 10) > 0); /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void reverse(char s[]) {
	int c, i, j;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}