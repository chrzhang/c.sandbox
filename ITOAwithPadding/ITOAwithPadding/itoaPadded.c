#include <stdio.h>
#include <string.h>
#define MAXLINE	1000

void itoamod(int n, char s[], int minFieldWidth);
void reverse(char s[]);

int main() {
	char line[MAXLINE];
	itoamod(6, line, 5);
	printf("%s\n", line);
	itoamod(81, line, 5);
	printf("%s\n", line);
	itoamod(227, line, 5);
	printf("%s\n", line);
	itoamod(1234, line, 5);
	printf("%s\n", line);
	itoamod(67890, line, 5);
	printf("%s\n", line);
	itoamod(122345, line, 5);
	printf("%s\n", line);
	itoamod(3313155, line, 5);
	printf("%s\n", line);
	itoamod(59137941, line, 5);
	printf("%s\n", line);
	itoamod(121212454, line, 5);
	printf("%s\n", line);
	itoamod(1234567890, line, 5);
	printf("%s\n", line);
	itoamod(11390481073401, line, 5);
	printf("%s\n", line);
	itoamod(38913891391376458, line, 5);
	printf("%s\n", line);
	
	getch();
	return 0;
}

/*
(Exercise 3-6)
Write a version of itoa that accepts three arguments instead of two. The third
argument is a minimum field width; the converted number must be padded with blanks on the
left if necessary to make it wide enough.
*/
void itoamod(int n, char s[], int minFieldWidth) {
	int i;
	int sign = (n >= 0) ? 1 : -1;
	i = 0;
	// Create a temporary string container
	char sTemp[MAXLINE];
	do { /* generate digits in reverse order */
		sTemp[i++] = sign * (n % 10) + '0'; /* get next digit */
	} while ((n /= 10) != 0); /* delete it */
	if (sign < 0)
		sTemp[i++] = '-';
	sTemp[i++] = '\0';
	reverse(sTemp);
	
	// If the string's length is less than the minimum field width
	int length = strlen(sTemp);
	if (length < minFieldWidth) {
		// Find out how many zeroes need to be padded onto the left
		int numZeroes = minFieldWidth - length;
		for (int i = 0; i < numZeroes; ++i) {
			s[i] = '0'; // Pad on the zeroes
		}
		for (int i = numZeroes; i < (length + numZeroes); ++i) {
			s[i] = sTemp[i - numZeroes]; // Copy over everything else
		}
		s[length+numZeroes] = '\0';
	}
	else {
		// Reassign s
		for (int i = 0; sTemp[i] != '\0'; ++i)
			s[i] = sTemp[i];
		s[i] = '\0'; // Copy over the end-line
	}
}

void reverse(char s[]) {
	int c, i, j;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}