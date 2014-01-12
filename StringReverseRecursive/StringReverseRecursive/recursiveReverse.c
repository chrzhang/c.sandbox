#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE	1000

void swap(char v[], int i, int j);
void reverse(char s[]);
void reverseAux(char s[], int start, int end);

main() {
	char s4[] = "abcd";
	printf("string:%s\n", s4);
	reverse(s4);
	printf("\treversed:%s\n", s4);

	char s3[] = "abc";
	printf("string:%s\n", s3);
	reverse(s3);
	printf("\treversed:%s\n", s3);

	char s2[] = "ab";
	printf("string:%s\n", s2);
	reverse(s2);
	printf("\treversed:%s\n", s2);

	char s1[] = "a";
	printf("string:%s\n", s1);
	reverse(s1);
	printf("\treversed:%s\n", s1);

	getch();
	return 0;
}

/*
(Exercise 4-13)
Write a recursive version of the function reverse(s), which reverses the
string s in place.
*/
void reverse(char s[]) {
	reverseAux(s, 0, strlen(s)-1);
}

void reverseAux(char s[], int start, int end) {
	if (start >= end)
		return;
	// Swap start and end
	swap(s, start, end);
	// Call recursively on ++start and --end
	reverseAux(s, (start + 1), (end - 1));
}

/* swap: interchange v[i] and v[j] */
void swap(char s[], int i, int j) {
	char temp;
	temp = s[i];
	s[i] = s[j];
	s[j] = temp;
}