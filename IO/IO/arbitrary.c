#include <stdio.h>
#define MAXLINES	5000 /* max lines to be entered then printed */
#define MAXLEN 1000 /* max length of any input line */
#define WIDTH	5

void writelines(char *lineptr[], int nlines);
int readlines(char *lineptr[], int maxlines);
int getline(char s[], int lim);
char *alloc(int n);
void strcpy(char *s, char *t);

char * lineptr[MAXLINES];

/*
(Exercise 7-2)
Write a program that will print arbitrary input in a sensible way. As a minimum,
it should print non-graphic characters in octal or hexadecimal according to local custom, and
break long text lines.
*/
main(int argc, char *argv[]) {
	int nlines = 0;
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		writelines(lineptr, nlines);
	}
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
	while (nlines-- > 0) {
		// Iterate through the chars of each line
		for (int i = 0; (i < MAXLEN) && ((*lineptr)[i] != '\0'); ++i) {
			// Arbitrary input will be classified as a char ranging in value from 0 to 127
			// Graphic chars are those that can be expressed from 32-126
			if ((*lineptr)[i] >= 32 && (*lineptr)[i] <= 126)
				putchar((*lineptr)[i]);
			else // It's non-graphic
				printf("(%x)", (*lineptr)[i]);
			// To wrap long-lines, choose a width and output a newline once i has reached a multiple
			if (i != 0 && i % (WIDTH - 1) == 0)
				putchar('\n');
		}
		putchar('\n');
		++lineptr;
	}
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0) {
		p = alloc(len);
		if ((p == NULL) || (nlines >= maxlines))
			return -1;
		else {
			line[len - 1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim) {
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i++] = c;
	}
	s[i] = '\0';
	return i;
}

#define ALLOCSIZE 10000 /* size of available space */
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */
char *alloc(int n) { /* return pointer to n characters */
	if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
		allocp += n;
		return allocp - n; /* old p */
	}
	else /* not enough room */
		return 0;
}

/* strcpy: copy t to s; pointer version 2 */
void strcpy(char *s, char *t) {
	while ((*s++ = *t++) != '\0')
		;
}