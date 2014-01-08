#include <stdio.h>
#define MAX_LINE	1000
void lower(char s[]);
int getline(char s[]);

int main() {
	printf("Test cases:\n");
	char line[] = "EGAD, 'TIS A JABBERWOCKY!";
	lower(line);
	printf("%s\n", line);
	char line1[] = "i Am A vAlLeY.";
	lower(line1);
	printf("%s\n", line1);

	printf("Now input strings for testing:\n");
	char line2[MAX_LINE];
	int len;
	while ((len = getline(line2)) > 0) {
		lower(line2);
		printf("%s\n", line2);
	}
	getch();
	return 0;
}

/*
(Exercise 2-10)
Rewrite the function lower, which converts upper case letters to lower case,
with a conditional expression instead of if-else.
*/
void lower(char s[]) {
	for (int i = 0; s[i] != '\0'; ++i) {
		s[i] = (s[i] >= 65 && s[i] <= 90) ? (s[i] + 32) : s[i];
	}
}

int getline(char s[]) {
	int c, len;
	for (len = 0; len < MAX_LINE - 1 && ((c = getchar()) != EOF) && c != '\n'; ++len)
		s[len] = c;
	if (c == '\n')
		s[len++] = c;
	s[len] = '\0';
	return len;
}