#include <stdio.h>
#define MAX_LINE	1000

void squeeze(char s1[], char s2[]);
int getline(char line1[], char line2[]);
int any(char s1[], char s2[]);

int main() {
	printf("Removing chars from s1 that exist in s2.\nEnter two lines separated by a newline:\n");
	char line1[MAX_LINE];
	char line2[MAX_LINE];
	int len;
	while ((len = getline(line1, line2)) > 0) {
		squeeze(line1, line2);
		printf("modified first line: %s\n", line1);
	}
	printf("Finding first location in s1 where a char from s2 appears.\nEnter two lines separated by a newline:\n");
	while ((len = getline(line1, line2)) > 0) {
		printf("%d\n", any(line1, line2));
	}
	getch();
	return 0;
}

/*
(Exercise 2-4)
Deletes each character in s1 that matches any character in the string s2.
*/
void squeeze(char s1[], char s2[]) {
	int i, j;
	for (i = j = 0; s1[i] != '\0'; i++) {
		// For each char in s1, iterate through the second string
		int foundInS2 = 0;
		for (int k = 0; s2[k] != '\0'; k++) {
			// Determine if the current s1 char is in s2
			if (s1[i] == s2[k]) {
				foundInS2 = 1;
				break;
			}
		}
		if (!foundInS2) {
			s1[j++] = s1[i];
		}
	}
	s1[j] = '\0';
}

/*
(Exercise 2-5)
Return the first location in s1 where any character from the string s2 occurs.
Return -1 if s1 contains no characters from s2.
*/
int any(char s1[], char s2[]) {
	int retVal = -1; // Default return-value
	// Iterate through s1
	for (int i = 0; s1[i] != '\0'; ++i) {
		// Check if each character is contained in s2
		for (int j = 0; s2[j] != '\0'; ++j) {
			if (s1[i] == s2[j])
				return i;
		}
	}
	return retVal;
}

int getline(char line1[], char line2[]) {
	int c, len1, len2;
	for (len1 = 0; ((c = getchar()) != EOF) && len1 < MAX_LINE - 1 && c != '\n'; ++len1)
		line1[len1] = c;
	if (c == '\n') {
		line1[len1++] = c;
		line1[len1] = '\0';
	}
	for (len2 = 0; ((c = getchar()) != EOF) && len2 < MAX_LINE - 1 && c != '\n'; ++len2)
		line2[len2] = c;
	if (c == '\n') {
		line2[len2++] = c;
		line2[len2] = '\0';
	}
	return len1 + len2;
}