#include <stdio.h>

void expand(char s1[], char s2[]);
int isLowercaseAlpha(char c);
int isUppercaseAlpha(char c);

int main() {
	char line[] = "Hello, World. a-z a-a z-a A-Z a-Z -1-8 0-3 9-7";
	printf("Line: %s\n", line);
	char line2[1000];
	expand(line, line2);
	printf("%s\n", line2);
	getch();
	return 0;
}

/*
(Exercise 3-3)
Write a function expand(s1, s2) that expands shorthand notations like a - z in
the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either case
and digits, and be prepared to handle cases like a - b - c and a - z0 - 9 and - a - z.Arrange that a
leading or trailing - is taken literally.
*/
void expand(char s1[], char s2[]) {
	// Parse through s1
	int currentChar;
	for (int i = currentChar = 0; s1[i] != '\0' && s1[i+1] != '\0' && s1[i+2] != '\0'; ++i) {
		// Detect if the sequence 'lowercase char' '-' 'lowercase char' is found OR
		// Detect if the sequence 'uppercase char' '-' 'uppercase char' is found OR
		// Detect if the sequence 'digit' '-' 'digit' is found
		if ((isLowercaseAlpha(s1[i]) && s1[i + 1] == '-' && isLowercaseAlpha(s1[i + 2]))
			|| (isUppercaseAlpha(s1[i]) && s1[i + 1] == '-' && isUppercaseAlpha(s1[i + 2]))
			|| (isdigit(s1[i]) && s1[i + 1] == '-' && isdigit(s1[i + 2]))) {
			// Then replace the currentChar in s2 with the appropriate sequence
			// The question assumes that the first char comes before the second
			// However, the alternative is possible as well as the case where it is a-a
			int trich;
			if (s1[i] <= s1[i + 2]) // If it looks like a-z
				trich = 1;
			else // If it looks like z-a
				trich = -1;
			char c = s1[i];
			while (c != s1[i + 2]) {
				s2[currentChar] = c;
				c += trich;
				++currentChar;
			}
			s2[currentChar] = c;
			++currentChar;
			// Increment i by 2
			i += 2;
		}
		else {
			s2[currentChar] = s1[i];
			++currentChar;
		}
	}
	s2[currentChar] = '\0';
}

int isLowercaseAlpha(char c) {
	return (c >= 'a' && c <= 'z');
}

int isUppercaseAlpha(char c) {
	return (c >= 'A' && c <= 'Z');
}