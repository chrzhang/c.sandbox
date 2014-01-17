#include <stdio.h>
#include <stdlib.h>

#define MAXLINE	1000
#define TABWIDTH	4

void entab(char line[], int mStartCol, int nColInterval);
int getline(char line[]);

main(int argc, char *argv[]) {
	int mStartCol = 0; // Default start
	int nColInterval = TABWIDTH; // Default interval
	int currentArg = 0;
	while (currentArg < argc) {
		switch (argv[currentArg][0]) {
		case '-':
			mStartCol = atoi(argv[currentArg] + 1);
			if (mStartCol < 0) {
				printf("The starting column cannot be negative.\n");
				return;
			}
			break;
		case '+':
			nColInterval = atoi(argv[currentArg] + 1);
			if (nColInterval < 0) {
				printf("The column interval cannot be negative.\n");
				return;
			}
			break;
		}
		++currentArg;
	}
	char line[MAXLINE];
	entab(line, mStartCol, nColInterval);
	getch();
	return 0;
}

/*
(Exercise 5-12)
Extend entab and detab to accept the shorthand
entab -m +n
to mean tab stops every n columns, starting at column m. Choose convenient (for the user)
default behavior.
*/
void entab(char line[], int mStartCol, int nColInterval) {
	int len;
	while ((len = getline(line)) > 0) {
		// Iterate through contents of line
		for (int i = 0; i < len - 1; ++i) {
			if (line[i] == ' ') { // Space detected
				// If TABWIDTH-1 amount of spaces follow it
				int isStartOfTab = 1;
				for (int j = 1; j < TABWIDTH; ++j) {
					if (line[i + j] != ' ') {
						isStartOfTab = 0;
						break;
					}
				}
				if (isStartOfTab) {
					printf("Start of tab at %d\n", i);
					// Find the nearest tab-stop (if i is greater than mStartCol, (least multiple of nColInterval) >= i)
					int nextTabStop = -1;
					int multiplier = 1;
					if (i > mStartCol) {
						while (nColInterval * multiplier + mStartCol < i) {
							++multiplier;
						}
						nextTabStop = nColInterval * multiplier + mStartCol;
					}
					else { // i is <= mStartCol
						// Use mStartCol as nextTabStop
						nextTabStop = mStartCol;
					}
					printf("next tab stop: %d\n", nextTabStop);
					// Do we need to shift right or left based on the tab stop? (left if nextTabStop < i + TABWIDTH)
					if (nextTabStop < i + TABWIDTH) {
						for (int z = nextTabStop; z <= len - (i + TABWIDTH - nextTabStop); ++z) {
							line[z] = line[z + (i + TABWIDTH - nextTabStop)];
						}
						// Update len
						len -= (i + TABWIDTH - nextTabStop);
					}
					else {
						// Shift everything from i + TABWIDTH over to the right so that what started at i + TABWIDTH now starts at the nextTabStop
						// Go right to left, set each n to whatever is in n-1
						for (int l = 0; l < (nextTabStop - (i + TABWIDTH)); l++) { // Shift over nextTabStop - i + TABWIDTH spaces to the right
							//printf("nexttabstop(%d) - i(%d) + tabwidth(%d) = %d\n", nextTabStop, i, TABWIDTH, nextTabStop - i + TABWIDTH);
							for (int k = len + 1; k >= i + TABWIDTH; k--) {
								line[k] = line[k - 1];
							}
							len++;
						}
						// Set blanks until the tab-stop
						for (int k = i + TABWIDTH; k < nextTabStop; ++k) {
							line[k] = ' ';
						}
						// Change i so as to not consider the newly created spaces
						i += -1 + (TABWIDTH + nextTabStop - TABWIDTH); // -1 is necessary because the loop increments i automatically
					}
				}
			}
		}
		printf("%s\n", line);
	}
}

int getline(char line[]) {
	int c, i;
	for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';
	return i;
}