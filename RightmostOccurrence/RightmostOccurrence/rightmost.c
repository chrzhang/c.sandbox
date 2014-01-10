#include <stdio.h>
#define MAXLINE	1000
int strindex(char s[], char t);
int getline(char s[], int lim);

int main() {
	char line[MAXLINE];
	printf("Enter a line:\n"); // Prompt user for input
	while ((getline(line, MAXLINE) > 0)) {
		printf("Enter a character:\n"); 
		int c;
		c = getchar();
		getchar(); // Related to I/O, the newline or <Enter> press after the char is stored
		// Calling getchar() wipes the newline out, allowing the user-input to iterate
		printf("Rightmost occurrence of %c: %d\n", c, strindex(line, c));
		printf("Enter a line:\n"); // Prompt user for input
	}
	getch();
	return 0;
}

/*
(Exercise 4-1)
Write the function strindex(s,t) which returns the position of the rightmost
occurrence of t in s, or -1 if there is none.
*/
int strindex(char s[], char t) {
	// Cannot go backwards without knowledge of string-length
	// strlen() has linear complexity anyway so simply traverse left-right, updating a holder for the position
	int pos = -1;
	for (int i = 0; s[i] != '\0'; ++i) {
		if (s[i] == t)
			pos = i;
	}
	return pos;
}

int getline(char s[], int lim) {
	int c, i;
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
		s[i++] = c;
	}
	
	if (c == '\n') {
		s[i++] = c;
	}
	s[i] = '\0';
	return i;
}