#include <stdlib.h>

/* numcmp: compare s1 and s2 numerically */
int numcmp(int reverse, char *s1, char *s2) {
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
int strcmp(int reverse, char *s, char *t) {
	for (; *s == *t; s++, t++)
	if (*s == '\0')
		return 0;
	return *s - *t;
}