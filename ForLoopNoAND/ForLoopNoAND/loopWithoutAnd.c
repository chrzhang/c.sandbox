#include <stdio.h>

int main() {
	// (Exercise 2-2) Write a loop equivalent to the for loop without using && or ||
	// for (i=0; i < lim-1 && (c=getchar()) != '\n' && c!=EOF; ++i)
	int lim = 1000;
	int c;
	for (int i = 0; i < lim - 1; ++i) {
		if ((c = getchar()) == '\n')
			break;
		if (c == EOF)
			break;
		// Do something
		printf("%c\n", c);
	}
	getch();
	return 0;
}