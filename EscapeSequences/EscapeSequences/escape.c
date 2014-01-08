#include <stdio.h>
#define MAX_LINE	1000

void escape(char s[], char t[]);
void escape2(char s[], char t[]);

int main() {
	printf("Replace a tab with \t");
	char line[] = "hey\tuniverse";
	printf("%s\n", line);
	char line2[MAX_LINE];
	escape(line2, line);
	printf("%s\n", line2);

	printf("Replace a newline with \n");
	char line3[] = "hey\nuniverse";
	printf("%s\n", line3);
	escape(line2, line3);
	printf("%s\n", line2);

	printf("In reverse, find the \\t and replace both with one '\\t'\n");
	char line4[] = "hey\\tuniverse";
	printf("%s\n", line4);
	escape2(line2, line4);
	printf("%s\n", line2);

	printf("In reverse, find the \\n and replace both with one '\\n'\n");
	char line5[] = "hey\\nuniverse";
	printf("%s\n", line5);
	escape2(line2, line5);
	printf("%s\n", line2);
	getch();
	return 0;
}

/*
(Exercise 3-2)
Write a function escape(s,t) that converts characters like newline and tab into
visible escape sequences like \n and \t as it copies the string t to s. Use a switch. 
*/
void escape(char s[], char t[]) {
	 // Parse through t
	int currentChar;
	for (int i = currentChar = 0; t[i] != '\0'; ++i) {
		switch (t[i]) {
		case '\n':
			s[currentChar++] = '\\';
			s[currentChar++] = 'n';
			break;
		case '\t':
			s[currentChar++] = '\\';
			s[currentChar++] = 't';
			break;
		default:
			s[currentChar++] = t[i];
			break;
		}
	}
	s[currentChar] = '\0';
}

/*
(Exercise 3-2)
Write a function for the other direction as well, converting escape sequences into 
the real characters.
*/
void escape2(char s[], char t[]) {
	// Parse through t
	int currentChar;
	for (int i = currentChar = 0; t[i] != '\0'; ++i) {
		switch (t[i]) {
		case '\\': // Detected a forward-slash
			switch (t[i + 1]) {
			case 't': // Detected a \t
				// Replace the forward slash with \t
				s[currentChar++] = '\t';
				// Skip on to the next character
				i += 2;
				break;
			case 'n': // Detected a \n
				// Replace the forward slash with \n
				s[currentChar++] = '\n';
				// Skip on to the next character
				i += 2;
				break;
			default:
				// It was only a slash, not an escape sequence
				s[currentChar++] = t[i];
				break;
			}
		default:
			s[currentChar++] = t[i];
			break;
		}
	}
}