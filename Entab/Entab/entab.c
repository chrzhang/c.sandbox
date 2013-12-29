#include <stdio.h>
#define TABWIDTH	4
#define MAXLINE	1000
int getline(char line[]);

/*
(Exercise 1-21)
Replace strings of blanks by minimum # of tabs/blanks to achieve same spacing
A tab should be given preference to let the array of chars store the "tab" as one index
rather than multiple spaces.
*/
int main() {
	int len;
	char line[MAXLINE];
	while ((len = getline(line)) > 0) {
		// Iterate through contents of line
		for (int i = 0; i < len-1; ++i) {
			if (line[i] == ' ') { // Space detected
				// If TABWIDTH-1 amount of spaces follow it
				int isStartOfTab = 1;
				for (int j = 1; j < TABWIDTH; ++j) {
					if (line[i+j] != ' ')
					{
						isStartOfTab = 0;
						break;
					}
				}
				if (isStartOfTab) {
					line[i] = '\t'; // Replace the first space with a tab char
					// Shift everything that follows starting from i + TAB_WIDTH to end
					// Shift something a position to pos - (TABWIDTH-1)
					for (int si = i + TABWIDTH; si < len+1; ++si) {
						line[si - (TABWIDTH - 1)] = line[si];
					}
				}
			}
		}
		printf("entabbed string: %s\n", line);
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