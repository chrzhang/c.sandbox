#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define MAXLINE	1000

int main() {
	char pi[MAXLINE] = "3.14";
	printf("pi as a string \"%s\" as a double: %e\n", pi, atof(pi));
	char expNo[MAXLINE] = "123.45e-6";
	printf("sci. notation # as a string \"%s\" as a double: %e\n", expNo, atof(expNo));
	getch();
	return 0;
}

/*
(Exercise 4-2)
Extend atof to handle scientific notation of the form
123.45e-6
where a floating-point number may be followed by e or E and an optionally signed exponent
*/
/* atof: convert string s to double */
double atof(char s[]) {
	double val, power;
	int i, sign;
	for (i = 0; isspace(s[i]); i++) /* skip white space */
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	int powerOfTen = 0;
	// Now check for any 'e'
	if (s[i] == 'e') {
		i++; // Skip the e
		// Store the sign if any
		int exponentSign = (s[i] == '-') ? -1 : 1;
		if (s[i] == '+' || s[i] == '-') // Skip the sign, if any
			i++;
		for (powerOfTen = 0; isdigit(s[i]); i++)
			powerOfTen = 10.0 * powerOfTen + (s[i] - '0');
		powerOfTen *= exponentSign;
	}
	return pow(10, powerOfTen) * sign * val / power;
}