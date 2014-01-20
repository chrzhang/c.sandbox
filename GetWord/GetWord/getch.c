#include <stdio.h>
#include "getword.h"
#define BUFSIZE        100
// External static limits visibility to current file
static char buf[BUFSIZE];
static int bufp = 0;
// Internal static means the variable is local but remains in existence

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}