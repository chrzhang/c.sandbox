#include <stdio.h>
#include <math.h>
#define MAX_LINE	1000

long htoi(char s[]);
int getline(char line[]);

int main() {
	// Some test cases
	printf("Converting 0xabcdef: %d\n", htoi("0xabcdef"));
	printf("Converting 0xABCDEF: %d\n", htoi("0xABCDEF"));
	printf("Converting 0xaBcDeF: %d\n", htoi("0xaBcDeF"));
	printf("Converting abcdef %d\n", htoi("abcdef"));
	printf("Converting ABCDEF %d\n", htoi("ABCDEF"));
	printf("Converting aBcDeF %d\n", htoi("aBcDeF"));
	printf("Converting 12345 %d\n", htoi("12345"));
	printf("Converting 123abc %d\n", htoi("123abc"));
	
	// User-input enabled
	printf("Enter hexadecimal string to be converted:\n");
	char line[MAX_LINE];
	int len;
	while ((len = getline(line)) > 0) {
		printf("%d\n", htoi(line));
	}
	getch();
	return 0;
}

/*
(Exercise 2-3)
Write a function htoi(s)  which converts a string of hexadecimal digits (including
an optional 0x or 0X) into its equivalent integer value. The allowable digits
are 0 through 9, a through f, and A through F.
*/
long htoi(char s[]) {
	long decimal = 0;
	// Check whether there is an optional 0x or 0X at the beginning
	int startIndex = 0;
	if (s[0] == '0' && ((s[1] == 'x') || (s[1] == 'X')))
		startIndex = 2;
	// Consider chars from \0 to startIndex
	// First find the index of \0
	int endIndex;
	for (endIndex = 0; s[endIndex] != '\0' && s[endIndex] != '\n'; ++endIndex) {}
	// endIndex now contains the index of the end-sequence
	int powerOfSixteen = 0;
	for (int i = endIndex-1; i >= startIndex; --i) {
		// Convert each single-digit hex to its decimal equivalent
		int val = s[i] - '0';
		
		if (val >= 49 && val <= 54) {
			val -= 39;
		}
		else if (val >= 17 && val <= 22) {
			val -= 7; // A bunch of punctuation marks live at values 10 through 16 incl. so offset
		}
		else if (val < 0 || val > 9) { // Falls out of any valid range
			printf("Not part of a valid hex representation.\n");
			break;
		}
		decimal += val * pow(16, powerOfSixteen);
		++powerOfSixteen;
	}
	return decimal;
}

int getline(char line[]) {
	int len, c;
	for (len = 0; ((c = getchar()) != EOF) && len < MAX_LINE - 1 && c != '\n'; ++len)
		line[len] = c;
	if (c == '\n') {
		line[len] = c;
		++len;
	}
	return len;
}