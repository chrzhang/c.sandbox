#include <stdio.h>
#define TABWIDTH	4
#define MAXLINE	1000

int setline(char line[]);

/*
(Exercise 1-20)
Replaces tabs in a line with spaces.
The number of columns could be a variable for run-time alterations but
conceptually, its behavior best fits that of a symbolic parameter, a constant.
*/
int main() {
	int len;
	char line[MAXLINE];
	while ((len = setline(line)) > 0) {
		printf("Modified String: %s\n", line);
	}
	getch();
	return 0;
}

// Reads a line into s, modifies it, return length on whether to continue
int setline(char line[]) { // Arrays are not passed by value
	int c, i;
	for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		if (c == '\t') {
			printf("Tab detected.\n");
			for (int j = 0; j < TABWIDTH; j++) {
				line[i + j] = ' '; // Change to X to more clearly show it
			}
			i += TABWIDTH-1;
		}
		else
		{
			line[i] = c;
		}
	}
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}