#include <stdio.h>
#define MAXLINE 1000 // Max input line length

int max;
char line[MAXLINE];
char longest[MAXLINE];

int getline(void);
void copy(void);
int reverse(char line[], int size);

// Print longest input line
int main() {
	int len; // Current line length
	extern int max; // Max length seen so far
	extern char longest[MAXLINE]; // Longest line saved here
	max = 0;
	while ((len = getline()) > 0)
	if (len > max) { // Longer line found
		max = len;
		copy();
	}
	if (max > 0)
		printf("%s", longest);
	// (Exercise 1-16) Print length of arbitrarily long input lines
	printf("Print the lengths of lines and the lines themselves.\n");
	while ((len = getline(line, MAXLINE)) > 0) {
		printf("Length:\t%d\n", len);
		printf("Line:\t%s\n", line);
	}
	// (Exercise 1-17) Print all lines longer than 80 characters
	printf("Print the lines longer than 80 characters.\n");
	while ((len = getline(line, MAXLINE)) > 0)
		if (len > 80)
			printf("%s\n", line);
	// (Exercise 1-18) Remove trailing blanks and tabs from each line
		// of input and delete entirely blank lines.
	printf("Remove trailing blanks/tabs (delete blank lines).\n");
	while ((len = getline(line, MAXLINE)) > 0) {
		// Len has index of the last char
		for (int b = len-2; b >= 0; --b) {
			int j = line[b];
			// If it is a blank or a tab character, decrement length
			if (line[b] == ' ' || line[b] == '\t') {
				--len;
			}
			// If not, set the length + 1 to an escape sequence
			else {
				line[len + 1] = '\0';
				break;
			}
		}
		if (len == 1) {
			if ((line[0] == ' ') || (line[0] == '\t') || (line[0] == '\n')) {
				line[0] = '\0';
				--len;
			}
		}
		printf("trimmed size: %d\n", len);
		printf("trimmed string: %s\n", line);
	}
	// (Exercise 1-19) Reverse a string.
	printf("Reverse the string.\n");
	while ((len = getline(line, MAXLINE)) > 0) {
		reverse(line, len);
	}
	getch();
	return 0;
}

// Reads a line into s, return length
int getline(void) { // Arrays are not passed by value
	int c, i;
	for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n') {
		line[i] = c;
		++i; // Consider the new-line as part of the length
	}
	line[i] = '\0';
	return i;
}

// Copy 'from' into 'to
void copy(void) {
	int i;
	extern char line[], longest[];
	i = 0;
	while ((longest[i] = line[i]) != '\0') // Copy if not end
		++i; // Continue
}

// Reverses a string
int reverse(char line[], int size) {
	for (int i = 0; i < size; ++i)
		putchar(line[size - 1 - i]);
	putchar('\n');
	return 0;
}