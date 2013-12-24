#include <stdio.h>

/* 
Experiment with escape sequences 
*/
main() {
	// New-line
	printf("New-line\n");
	printf("Hello, World!\nTake me to your leader."); 
	// Tab
	printf("\n\nTab\n");
	printf("Hello, World!\tTake me to your leader.");
	// Backspace
	printf("\n\nBackspace\n");
	printf("Hello, World!\bTake me to your leader.");
	// Double-quote
	printf("\n\nDouble-quote\n");
	printf("Hello, World!\"Take me to your leader.");
	// Back-slash
	printf("\n\nBack-slash\n");
	printf("Hello, World!\\Take me to your leader.");
	// Bad escape-sequence (Exercise 1-2)
	printf("\n\nBad escape-sequence\n");
	printf("Hello, World!\cTake me to your leader.");
	getch();
}