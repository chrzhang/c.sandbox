#include <stdio.h>
#define MAXLINE	1000
#define COL_WIDTH 5

int getline(char line[]);

/*
(Exercise 1-22)
Fold long input lines into 2 or more shorter lines after the last non-blank char
that occurs.
*/
int main() {
	char line[MAXLINE];
	int len;
	while ((len = getline(line)) > 0) {
		if (len <= COL_WIDTH)
			printf(line); // Phew! No folding needed
		else { // Uh-oh! Needs word-wrapping
			int unModified = len; // Amount that is unmodified chars will determine whether 
			int endlineIndex = COL_WIDTH - 1;
			while (unModified > COL_WIDTH) {
				int change = 0;
				while (endlineIndex == ' ') {
					--endlineIndex;
					++change;
				}
				for (int i = (endlineIndex - (COL_WIDTH - 1)); i <= endlineIndex; ++i) {
					if (i < 0)
						i = 0;
					putchar(line[i]);
				}
				putchar('\n');
				unModified -= COL_WIDTH - change;
				endlineIndex += COL_WIDTH;
			}
			for (int i = endlineIndex - (COL_WIDTH - 1); i <= endlineIndex && line[i] != '\0'; ++i) {
				putchar(line[i]);
			}
		}
	}
	getch();
	return 0;
}

int getline(char line[]) {
	int c, i;
	for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}
