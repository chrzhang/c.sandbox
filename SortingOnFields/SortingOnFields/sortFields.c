#include <stdio.h>
#include "sorter.h"
#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */

char *lineptr[MAXLINES]; /* pointers to text lines */

/*
(Exercise 5-17)
Add a field-searching capability, so sorting may be done on fields within lines,
each field sorted according to an independent set of options. (The index for this book was
sorted with -df for the index category and -n for the page numbers.)

As an example, the current field searched is what follows a comma.
To pick a more specific subfield, modify the getSField(...) method.
*/

static int reverse; /* 1 if reverse sort */
static int foldCase; /* 1 if A and a are to be considered == */
static int dirMode; /* 1 if only letters, numbers, spaces matter */

// Default sorting field parameters
static int useCustomField = 0;
static char DELIMITER = ',';

/* sort input lines */
main(int argc, char *argv[]) {
	int nlines; /* number of input lines read */
	int numeric = 0; /* 1 if numeric sort */
	int c;
	while (--argc > 0 && ((*++argv)[0] == '-')) {
		while (c = *++argv[0]) {
			switch (c) {
			case 'n':
				numeric = 1;
				break;
			case 'r':
				reverse = 1;
				break;
			case  'f':
				foldCase = 1;
				break;
			case 'd':
				dirMode = 1;
				break;
			case 'c':
				useCustomField = 1;
				break;
			default:
				printf("Illegal option %c\n", c);
				argc = 0;
				break;
			}
		}
	}
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort((void**)lineptr, 0, nlines - 1,
			(int(*)(int, int, int, void*, void*))(numeric ? numcmp : strcmp));
		writelines(lineptr, nlines);
	}
	else {
		printf("input too big to sort\n");
		return 1;
	}
	getchar();
	return 0;
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
// When using fields
static char subline1[MAXLEN];
static char subline2[MAXLEN];

char *alloc(int n) { /* return pointer to n characters */
	if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
		allocp += n;
		return allocp - n; /* old p */
	}
	else /* not enough room */
		return 0;
}

void afree(char *p) { /* free storage pointed to by p */
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

/* strcpy: copy t to s; pointer version 2 */
void strcpy(char *s, char *t) {
	while ((*s++ = *t++) != '\0')
		;
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

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(void *v[], int left, int right, int(*comp)(int, int, int, void *, void *)) {

	int i, last;
	void swap(void *v[], int, int);
	if (left >= right) /* do nothing if array contains */
		return; /* fewer than two elements */
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++) {
		if (!useCustomField) {
			// To allow for fields to be used, do not send v[i] and v[left] 
			if ((*comp)(reverse, foldCase, dirMode, v[i], v[left]) < 0) {
				swap(v, ++last, i); // Default increasing sort
			}
		}
		else {
			strcpy(subline1, getSField(v[i]));
			strcpy(subline2, getSField(v[left]));
			// Instead, pass to comp the modified substrings that are to be compared
			if ((*comp)(reverse, foldCase, dirMode, subline1, subline2) < 0) {
				swap(v, ++last, i); // Default increasing sort
			}
		}

	}
	swap(v, left, last);
	qsort(v, left, last - 1, comp);
	qsort(v, last + 1, right, comp);
}


char* getSField(char * line) {
	while (*(line++) != DELIMITER) {}
	return line;
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j) {
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}