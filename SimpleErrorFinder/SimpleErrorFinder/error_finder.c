#include <stdio.h>
#define MAXLINE		1000
// Non-code defined as strings and comments
#define INSTRING	0
#define INCHAR		2
#define INCOMM		1
#define NONCODE		0 // Flags for whether to even check for errors
#define CODE		1
int getline(char line[]);

/*
(Exercise 1-24)
Detect unclosed parentheses, brackets, and braces.
Quotes, double-quotes, escape sequences, and comments should not be overlooked.
*/
int main() {
	/*
	To check for closed/un-closed anything, 3 counters will exist for (), [], and {}
	When an opening [({ is found, increment the corresponding counter
	When a closing ])} is found, decrement the corresponding counter
		If it became negative, there is a syntax error
	If by the end, the counters are not each 0, there is a syntax error

	DOUBLE_QUOTES
	As for double-quotes, start to ignore everything until the same quote is found once more
	Check to see that quotes are closed. If not, the state will hold a NONCODE flag after
	the  last line has been processed. 

	QUOTES
	If currently in a CODE state, single quotes should delimit a char so test to see if the char
	held at position x + 2 is also a single quote.

							<<< FUTURE IMPROVEMENTS >>>
	ESCAPE SEQUENCES
	In a more thorough project-version of this, it becomes handy to enforce indentation.
	Currently, the entire program could be written on one line and be considered valid.

	SEMI-COLONS, etc.
	Let's not forget the basic rules.

	This program is not an all-round validator. Errors will be printed but all text will be processed.
	If random characters are entered, it is likely to cause silliness.
	*/
	int parentheses, brackets, braces;
	parentheses = brackets = braces = 0; // Default state
	int state = CODE; // Default state
	// When the state does become NONCODE, a reason is needed to later tell how to leave this state
	// (i.e. if it's because of a comment, look for a */ to  exit)
	int reason = -1; 
	int len;
	char line[MAXLINE];
	while ((len = getline(line)) > 0) {
		// Iterate through the line
		for (int current = 0; current <= len; ++current) {
			if (state == CODE) {
				// Openings
				if (line[current] == '(')
					++parentheses;
				else if (line[current] == '[')
					++brackets;
				else if (line[current] == '{')
					++braces;
				// Closings
				else if (line[current] == ')') {
					--parentheses;
					if (parentheses < 0) {
						printf("Error. Too many closing parentheses.\n");
					}
				}
				else if (line[current] == ']') {
					--brackets;
					if (brackets < 0) {
						printf("Error. Too many closing parentheses.\n");
					}
				}
				else if (line[current] == '}') {
					--braces;
					if (braces < 0) {
						printf("Error. Too many closing braces.\n");
					}
				}
				else if (line[current] == '/' && current != len && line[current + 1] == '/') {
					break;
				}
				else if (line[current] == '/' && current != len && line[current + 1] == '*') {
					//printf("Going inside block comment.\n");
					state = NONCODE;
					reason = INCOMM;
				}
				else if (line[current] == '"') {
					//printf("Going inside quote.\n");
					state = NONCODE;
					reason = INSTRING;
				}
				else if (line[current] == '\'') {
					//printf("Going inside char.\n");
					state = NONCODE;
					reason = INCHAR;
				}
			}
			else if (state == NONCODE) {
				//printf("%c is currently not being considered.\n", line[current]);
				if (reason == INSTRING) {
					// Look for a "
					for (int i = current + 1; i <= len; ++i) {
						if (line[i] == '"') {
							state = CODE;  // Left the string
							reason = -1;
							current = i + 1;
						}
					}
				}
				else if (reason == INCOMM) {
					// Look for a * followed by a /
					for (int i = current + 1; i <= len; ++i) {
						if (line[i] == '*' && line[i + 1] == '/') {
							state = CODE; // Not in a comment anymore
							reason = -1;
							current = i + 1;
						}
					}
				}
				else if (reason == INCHAR) {
					// Look for a '
					for (int i = current + 1; i <= len; ++i) {
						if (line[i] == '\'') {
							state = CODE;
							reason = -1;
							current = i + 1;
						}
					}
				}
			}
		}
	}
	if (parentheses != 0)
		printf("Error. Unclosed parentheses. Too many opening parentheses.\n");
	if (braces != 0)
		printf("Error. Unclosed braces. Too many opening braces.\n");
	if (brackets != 0)
		printf("Error. Unclosed brackets. Too many opening brackets.\n");
	if (!state) //  State is currently NONCODE or 0
		printf("Error. Unclosed quotes.\n");
	getch();
	return 0;
}

int getline(char line[]) {
	int len, c;
	for (len = 0; ((c = getchar()) != EOF) && len < MAXLINE - 1 && c != '\n'; ++len) {
		line[len] = c;
	}
	if (c == '\n') {
		line[len] = c;
		++len;
	}
	return len;
}