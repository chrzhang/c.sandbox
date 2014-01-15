#include <stdio.h>
#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */

char *lineptr[MAXLINES]; /* pointers to text lines */

int getline(char *, int);
int readlines(char *lineptr[], int nlines);
int readlinesFAST(char lines[][MAXLEN], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
char *alloc(int);
void strcpy(char *s, char *t);

/* sort input lines */
main() {
	int nlines; /* number of input lines read */
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
	}
	else {
		printf("error: input too big to sort\n");
		return 1;
	}
	char * lines[MAXLINES];
	if ((nlines = readlinesFAST(lines, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
	}
	else {
		printf("error: input too big to sort\n");
		return 1;
	}
	getch();
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

/*
(Exercise 5-7)
Rewrite readlines to store lines in an array supplied by main, rather than
calling alloc to maintain storage. How much faster is the program?
*/
/* readlines: read input lines */
int readlinesFAST(char lines[][MAXLEN], int maxlines) {
	int len, currentLine;
	currentLine = 0;
	int wouldBeAllocCounter = 0;
	while ((len = getline(lines[currentLine], MAXLEN)) > 0) {
		++wouldBeAllocCounter;
		if (currentLine >= maxlines)
			return -1; // Too many lines for further reading
		else
			lines[currentLine++][len - 1] = '\0'; // Replace newline
	}
	printf("Skipped %d calls to alloc().\n", wouldBeAllocCounter);
	return currentLine;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right) {
	int i, last;
	void swap(char *v[], int i, int j);
	if (left >= right) /* do nothing if array contains */
		return; /* fewer than two elements */
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j) {
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}