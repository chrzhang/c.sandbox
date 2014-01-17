#include <stdio.h>
#include <stdlib.h>

#define TABWIDTH	4
#define MAXLINE	1000

int getline(char line[]);
void entab(char line[], char *argv[], int argc);

/*
(Exercise 5-11)
Modify the program entab and detab (written as exercises in Chapter 1) to
accept a list of tab stops as arguments. Use the default tab settings if there are no arguments.
***
Replace strings of blanks by minimum # of tabs/blanks to achieve same spacing
A tab should be given preference to let the array of chars store the "tab" as one index
rather than multiple spaces.

Notes: Currently implemented entab so the alignment uses the list of tab stops but as a result,
no actual tab characters are used to replace spaces.

NEED DETAB IMPLEMENTATION
*/
main(int argc, char *argv[]) {
	char line[MAXLINE];
	entab(line, argv, argc);
	getch();
	return 0;
}

void entab(char line[], char *argv[], int argc) {
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
					if (!(argc == 1)) {
						//Find the nearest tab-stop (least tabstop greater than current index)
						int nextTabStop = -1;
						for (int j = 1; j < argc; ++j) {
							if (atoi(argv[j]) > i) { // ASSUME the command-line arguments are valid (they CAN be cast as ints)
								nextTabStop = atoi(argv[j]);
								break;
							}
						}
						if (nextTabStop != -1) {
							// Do we need to shift right or left? Shift left if the tab stop is actually between i and i + TABWIDTH, else, shift right
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
						else {
							printf("No valid tab stop was specified near this index.\n");
							break;
						}
					}
					else {
						line[i] = '\t'; // Replace the first space with a tab char
						// Shift everything that follows starting from i + TAB_WIDTH to end
						// Shift something at position to pos - (TABWIDTH-1)
						for (int si = i + TABWIDTH; si < len + 1; ++si) {
							line[si - (TABWIDTH - 1)] = line[si];
						}
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