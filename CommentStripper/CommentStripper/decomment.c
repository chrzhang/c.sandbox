#include <stdio.h>
#define OUT	0
#define IN	1
#define MAXLINE	1000

int getline(char line[]);

/*
(Exercise 1-23)
Remove all comments from a C program. Don't forget to handle quoted strings and char
constants properly. C comments do NOT nest.
*/
int main() {
	// Assuming input text to be syntactically sound (all multi-line comments closed)
	int state = OUT;
	int len;
	char line[MAXLINE];
	// Per line
	while ((len = getline(line)) > 0) {	
		char commentlessLine[MAXLINE];
		int commentlessLineIndex = 0;
		int earlyEnd = 0;

		// If encounter a / followed by a /, replace the first by a newline, follow w/ \0
		for (int i = 0; i <= len; ++i) {
			if (state == OUT) {
				if ((line[i] == '/') && (line[i + 1] == '/')) {
					commentlessLine[i] = '\n';
					commentlessLine[i + 1] = '\0';
					break;
				}
				else if ((line[i] == '/') && (line[i + 1] == '*')) {
					earlyEnd = i;
					state = IN;
				}
				else {
					commentlessLine[commentlessLineIndex] = line[i];
					++commentlessLineIndex;
				}
			}
			else if ((line[i] == '*') && (line[i + 1] == '/')) {
				state = OUT;
				++i;
			}
		}
		// If by the end of the line, state is still IN
		if (state == IN)
			commentlessLine[earlyEnd] = '\0';
		printf("comment-less line: %s", commentlessLine);
	}
	getch();
	return 0;
}

int getline(char line[]) {
	int i, c;
	for (i = 0; ((c = getchar()) != EOF) && i < MAXLINE - 1 && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}