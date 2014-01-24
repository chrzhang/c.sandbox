#include <stdio.h>
#include <ctype.h>

/*
(Exercise 7-1)
Write a program that converts upper case to lower or lower case to upper,
depending on the name it is invoked with, as found in argv[0].
*/
main(int argc, char *argv[]) { /* lower: convert input to lower case*/
	int c;
	int(*operation)(int c) = NULL;
	if (argc == 2) {
		switch (*argv[1]) {
		case 'u':
			operation = tolower;
			printf("Upper-to-lower mode.\n");
			break;
		case 'l':
			operation = toupper;
			printf("Lower-to-upper mode.\n");
			break;
		}
	}
	else {
		printf("Please specify a mode: u OR l.\n");
		return 0;
	}
	while ((c = getchar()) != EOF)
		putchar((*operation)(c));
	return 0;
}