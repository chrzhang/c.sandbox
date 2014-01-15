#include <stdio.h>
#include <string.h>
#define NUMBER '0'
#define MAXLINE	1000

/*
(Exercise 5-6)
Rewrite appropriate programs from earlier chapters and exercises with pointers
instead of array indexing.
Good possibilities include 
	getline (Chapters 1 and 4), 
	atoi, 
	itoa,
and their variants (Chapters 2, 3, and 4), 
	reverse (Chapter 3), and 
	strindex and 
	getop (Chapter 4).
*/
int getline(char * s, int lim);
int atoi(char * s);
void itoa(int n, char * s);
void reverse(char * s, int length);
int strindex(char * s, char * t);
int getop(char * s);

main() {
	char s[MAXLINE];
	printf("Please enter a line of input:\n");
	getline(s, MAXLINE);
	printf("Entered %s", s);

	strcpy_s(s, MAXLINE, "1212091");
	printf("%s as an integer: %d\n", s, atoi(s));

	itoa(567, s);
	printf("Converted integer %d to string %s\n", 567, s);

	strcpy_s(s, MAXLINE, "All black and brown and covered in hair.");
	char s2[MAXLINE] = "w";
	printf("Index of %s in %s: %d\n", s2, s, strindex(s, s2));
	int type;

	char s3[MAXLINE];
	while ((type = getop(s3)) != EOF) {
		printf("%s: %d\n", s3, type);
	}
	getch();
	return 0;
}

/* getline: get line into s, return length */
int getline(char * s, int lim) {
	int c, i;
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
		*s++ = c;
		++i;
	}
	if (c == '\n') {
		*s++ = c;
		++i;
	}
	*s = '\0';
	return i;
}

/* atoi: convert s to integer */
int atoi(char * s) {
	int n;
	n = 0;
	for ( ; *s >= '0' && *s <= '9'; ++s) {
		n = 10 * n + (*s - '0');
	}
	return n;
}

/* itoa: convert n to characters in s */
void itoa(int n, char * s) {
	int sign;
	if ((sign = n) < 0) /* record sign */
		n = -n; /* make n positive */
	char * stringBegin = s;
	do { /* generate digits in reverse order */
		*s++ = n % 10 + '0'; /* get next digit */
	} while ((n /= 10) > 0); /* delete it */
	if (sign < 0)
		*s++ = '-';
	*s = '\0';
	reverse(stringBegin, strlen(stringBegin));
}

/* reverse: reverse string s in place */
void reverse(char * s, int length) {
	printf("length: %d\n", length);
	int c, i, j;
	for (i = 0, j = length - 1; i < j; i++, j--) {
		c = *(s + i);
		*(s + i) = *(s + j);
		*(s + j) = c;
	}
}

/* strindex: return index of t in s, -1 if none */
int strindex(char * s, char * t) {
	int i, j, k;
	for (i = 0; *(s + i) != '\0'; i++) {
		for (j = i, k = 0; *(t + k) != '\0' && *(s + j) == *(t + k); j++, k++)
			;
		if (k > 0 && *(t + k) == '\0')
			return i;
	}
	return -1;
}

/* getop: get next character or numeric operand */
int getop(char * s) {
	int i, c;
	while ((*s = c = getch()) == ' ' || c == '\t')
		;
	*(s + 1) = '\0';
	if (!isdigit(c) && c != '.')
		return c; /* not a number */
	if (isdigit(c)) /* collect integer part */
	while (isdigit((*++s) = c = getch()))
		;
	if (c == '.') /* collect fraction part */
	while (isdigit((*++s) = c = getch()))
		;
	*++s = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}