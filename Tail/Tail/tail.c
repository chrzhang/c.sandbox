#include <stdio.h>
#include <stdlib.h>

#define MAXLINES 5000 /* max #lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to textlines */
#define MAXLEN 1000 /* max length of any input line */

int readlines(char *lineptr[], int tailAmount);
void writelines(char *lineptr[], int nlines);
void tail(char *lineptr[], int nlines, int tailAmount);
int getline(char *, int);
char *alloc(int);
void strcpy(char *s, char *t);

/*
(Exercise 5-13)
Write the program tail, which prints the last n lines of its input. By default, n
is set to 10, let us say, but it can be changed by an optional argument so that
tail -n
prints the last n lines. The program should behave rationally no matter how unreasonable the
input or the value of n. Write the program so it makes the best use of available storage; lines
should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of
fixed size.

Since the order is irrelevant, have a buffer of the desired input size which wraps with each
writing of each new line.
*/
main(int argc, char *argv[]) {
	int tailAmount = 10;
	if (argc > 1) {
		for (int i = 1; i < argc; ++i) {
			switch (argv[i][0]) {
			case '-':
				tailAmount = atoi(argv[i] + 1);
				break;
			default:
				printf("Unknown command.\n");
				return;
			}
		}
	}
	if (tailAmount > MAXLINES) {
		printf("Too many most recent lines requested, printing as much as possible.\n");
		tailAmount = MAXLINES;
	}
	int nlines;

	if ((nlines = readlines(lineptr, tailAmount)) >= 0) {
		if (nlines < tailAmount) {
			printf("# of lines do not meet the parameter.\n");
			// Print all the lines that have been entered
			writelines(lineptr, nlines);
		}
		else {
			tail(lineptr, nlines, tailAmount);
		}
	}
	getch();
	return 0;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int tailAmount) {
	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0) {
		p = alloc(len);
		if (p == NULL)
			return -1;
		else {
			line[len - 1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines % tailAmount] = p;
			++nlines;
		}
	}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

void tail(char *lineptr[], int nlines, int tailAmount) {
	// Go to the last line printed and subtract the amount of lines to be printed
	for (int i = 0; i < tailAmount; ++i) {
		printf("%s\n", lineptr[i]);
	}
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