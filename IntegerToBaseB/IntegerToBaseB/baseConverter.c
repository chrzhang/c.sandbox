#include <stdio.h>
#include <ctype.h>
#define MAX_LINE	1000

void itob(int n, char s[], int b);
void reverse(char s[]);
int getline(char line[]);

int main() {
	char line[MAX_LINE];
	itob(147, line, 2);
	printf("147 in base 2: %s\n", line);
	itob(147, line, 5);
	printf("147 in base 5: %s\n", line);
	itob(147, line, 16);
	printf("147 in base 16: %s\n", line);
	itob(1479, line, 16);
	printf("1479 in base 16: %s\n", line);
	
	itob(0, line, 2);
	printf("0 in base 2: %s\n", line);
	itob(0, line, 5);
	printf("0 in base 5: %s\n", line);
	itob(0, line, 16);
	printf("0 in base 16: %s\n", line);
	itob(0, line, 16);
	printf("0 in base 16: %s\n", line);

	int len;
	char num[MAX_LINE];
	char base[MAX_LINE]; // Not guaranteed user to input valid data
	printf("Enter a number: \n"); // Prompt user
	while (getline(num) > 0) {
		if (!validInt(num)) { // Ensure that a number was entered
			printf("Not a valid integer expression. Try again.\n");
			continue;
		}
		printf("Enter a base: \n");
		getline(base);
		if (!validInt(base)) { // Ensure that a number was entered
			printf("Not a valid integer expression. Try again.\n");
			continue;
		}
		// Convert the line and base into ints
		int n = atoi(num);
		int b = atoi(base);
		itob(n, line, b);
		printf("%s\n", line);
		printf("Enter a number: \n"); // Prompt user
	}
	getch();
	return 0;
}

int validInt(char num[]) {
	for (int i = 0; num[i] != '\n' && num[i] != '\0'; ++i) {
		if (!isdigit(num[i]))
			return 0;
	}
	return 1;
}

/*
(Exercise 3-5)
Write the function itob(n,s,b) that converts the integer n into a base b
character representation in the string s. In particular, itob(n,s,16) formats s as a
hexadecimal integer in s.
*/
void itob(int n, char s[], int b) {
	int i = 0;
	if (n == 0) {
		s[i++] = '0';
		s[i] = '\0';
	}
	else if (n > 0) {
		while (n > 0) {
			char c = n % b + '0';
			if (c > '9')
				c += 7; // Extra chars to skip over between ASCII 9 and A so the hex representation will work
			s[i++] = c;
			n /= b;
			//printf("n: %d\n", n);
		}
		s[i] = '\0';
		reverse(s);
	}
	else {
		printf("Input was negative. Try again.\n"); // Negative integers not handled
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

int getline(char line[]) {
	int len, c;
	for (len = 0; len < MAX_LINE - 1 && (c = getchar()) != EOF && c != '\n'; ++len)
		line[len] = c;
	if (c == '\n')
		line[len++] = c;
	return len;
}