#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

static int noCaseSame(char c, char d);

/* numcmp: compare s1 and s2 numerically */
int numcmp(int reverse, int foldCase, int dirMode, char *s1, char *s2) {
	if (dirMode || foldCase) {
		printf("The flag for numerical sort has been set. Other options ignored.\n");
	}
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1 + 2 * reverse;
	else if (v1 > v2)
		return 1 + -2 * reverse;
	else
		return 0;
}

/* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp(int reverse, int foldCase, int dirMode, char *s, char *t) {
	if (dirMode) {
		return dircmp(reverse, foldCase, s, t);
	}
	for (; (*s == *t) || (foldCase && noCaseSame(*s, *t)); s++, t++) {
		if (*s == '\0')
			return 0;
	}
	if (reverse)
		return (-1 * (*s - *t));
	return (*s - *t);
}

int noCaseSame(char c, char d) {
	if ((c >= 'a') && (c <= 'z'))
		return (d == c - ('a' - 'A'));
	else if ((c >= 'A') && (c <= 'Z'))
		return (d == c + ('a' - 'A'));
	return 0;
}

/* rdircmp: return <0 if s<t, 0 if s==t, >0 if s >t */
int dircmp(int reverse, int foldCase, char *s, char *t) {
	char sc;
	char tc;
	do {
		//printf("using dircmp\n");
		while (!isalnum(*s) && *s != ' ' && *s != '\0')
			++s;
		while (!isalnum(*t) && *t != ' ' && *t != '\0')
			++t;
		sc = *s++;
		tc = *t++;

		if (sc == tc && sc == '\0')
			return 0;
	} while ((sc == tc) || (foldCase && noCaseSame(tc, sc)));
	return sc - tc;
}