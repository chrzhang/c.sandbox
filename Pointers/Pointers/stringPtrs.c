#include <stdio.h>
#define MAXLINE	1000

void strcat(char * s, char * t, const int LIMIT);
int strend(char * s, char *t);
char * strncpy(char * s, char * ct, int n, const int LIMIT);
char * strncat(char * s, char * ct, int n);
int strncmp(char * cs, char * ct, int n);

main() {
	char pmessage[MAXLINE] = "the vorpal blade we";
	char qmessage[MAXLINE] = "nt snipper-snack!";
	printf("\n\t\tSTRCAT TEST\n\n");
	printf("\"%s\" will be concatenated to the end of \"%s\"\n", qmessage, pmessage);
	strcat(pmessage, qmessage, MAXLINE);
	printf("%s\n", pmessage);

	printf("\n\t\tSTREND TEST\n\n");
	strcpy(pmessage, "hello world");
	strcpy(qmessage, "world");
	printf("Does \"%s\" occur at the end of \"%s\"? %d\n", qmessage, pmessage, strend(pmessage, qmessage));

	strcpy(pmessage, "a");
	strcpy(qmessage, "a");
	printf("Does \"%s\" occur at the end of \"%s\"? %d\n", qmessage, pmessage, strend(pmessage, qmessage));

	strcpy(qmessage, "cb");
	printf("Does \"%s\" occur at the end of \"%s\"? %d\n", qmessage, pmessage, strend(pmessage, qmessage));

	printf("\n\t\tSTRNCPY TEST\n\n");
	for (int i = -3; i < 10; ++i) {
		strcpy(pmessage, "drake");
		strcpy(qmessage, "manticore");
		printf("Replacing %d chars of \"%s\" with \"%s\"\n", i, qmessage, pmessage);
		strncpy(qmessage, pmessage, i, MAXLINE);
		printf("%s\n", qmessage);
	}

	printf("\n\t\tSTRNCAT TEST\n\n");
	for (int i = -3; i < 25; ++i) {
		strcpy(pmessage, "the stench of raf");
		strcpy(qmessage, "flesia is stifling.");
		printf("Catenating %d chars of \"%s\" to \"%s\"\n", i, qmessage, pmessage);
		strncat(pmessage, qmessage, i, MAXLINE);
		printf("%s\n", pmessage);
	}

	for (int i = 0; i < 21; ++i) {
		strcpy(pmessage, "a gleaming black spike");
		strcpy(qmessage, "a gleaming white spike");
		printf("Are %d chars of \"%s\" and \"%s\" equal? %d\n", i, pmessage, qmessage, strncmp(pmessage, qmessage, i));
	}
	getch();
	return 0;
}

/*
WARNING:
There is no way to reckon the size of the array for the string from a pointer to the
first element alone.
To prevent the program from crashing when trying to catenate a string that would 
result in a larger-than possible string, it would be wise to have catenating functions
accept a limit variable that bluntly tells of the char array's capacity.
*/

/*
(Exercise 5-3)
Write a pointer version of the function strcat that we showed in Chapter 2:
strcat(s,t) copies the string t to the end of s.
*/
void strcat(char * s, char * t, const int LIMIT) {
	int lengthS, lengthT;
	lengthS = lengthT = 0;
	while (*++s != '\0') { /* find end of s */
		++lengthS;
	} 
	char * tx = t; // Store the original value of the second string ptr
	while (*++tx != '\0') {
		++lengthT;
	}
	if (lengthS + lengthT >= LIMIT) {
		printf("error: Concatenating the strings would overstep the size limitation on the parent string.\n");
		return;
	}
	while ((*s++ = *t++) != '\0') {} /* copy t */ 
}

/*
(Exercise 5-4)
Write the function strend(s,t), which returns 1 if the string t occurs at the
end of the string s, and zero otherwise.
*/
int strend(char * s, char *t) {
	// Find the length of string t
	int lengthT = 0;
	while (*t++ != '\0')
		++lengthT;
	// Find the length of string s
	int lengthS = 0;
	while (*s++ != '\0')
		++lengthS;
	if (lengthT > lengthS)
		return 0; // Impossible if string t is longer than string s
	// s is now at the ending null sequence of s so subtract the diff.
	s -= lengthT + 1;
	// t is now at the ending null sequence of s so subtracting the length of t returns to the beginning char
	t -= lengthT + 1;
	for (;;) {
		if (*s != *t)
			return 0;
		else if (*s == '\0')
			break;
		++s;
		++t;
	}
	return 1;
}

/*
(Exercise 5-5)
Write versions of the library functions strncpy, strncat, and strncmp, which
operate on at most the first n characters of their argument strings. For example,
strncpy(s,t,n) copies at most n characters of t to s.
*/

/* Copy at most n characters of string ct to s. Return s. Pad with \0s if ct has
fewer than n characters.*/
char * strncpy(char * s, char * ct, int n, const int LIMIT) {
	if (n > LIMIT) {
		printf("error: Cannot copy over a number of characters greater than the parent string can store.\n");
		return s;
	}
	int i = 0;
	while (n > 0) {
		if (*(ct + i) == '\0') {
			// Set the remaining n characters to \0
			for (int k = n; k > 0; --k) {
				*(s + k + i - 1) = '\0';
			}
			break;
		}
		else {
			*(s + i) = *(ct + i);
		}
		++i;
		--n;
	}
	return s;
}

/* Concatenate at most n characters of string ct to string s, terminate s with '\0'.
Return s.
*/
char * strncat(char * s, char * ct, int n, const int LIMIT) {
	int lengthS = 0;
	while (*++s != '\0') { /* find end of s */
		++lengthS;
	}
	if (n + lengthS > LIMIT) {
		printf("error: Cannot catenate a number of characters greater than the parent string can store.\n");
		return s;
	}
	// s points to the end char, which is where the catenation shall begin
	while (n > 0) {
		*s++ = *ct++;
		--n;
		// If ct does not fill up n characters
		if (*ct == '\0') {
			break;
		}
	}
	*s = '\0';
	return s;
}

/* Compare at most n characters of string cs to string ct. Return < 0 if cs < ct, 0 if 
cs = ct, or > 0 if cs > ct.
*/
int strncmp(char * cs, char * ct, int n) {
	while (n > 0) {
		if (*cs++ != *ct++) {
			return *--cs - *--ct;
		}
		if (*(cs - 1) == '\0') {
			break;
		}
		--n;
	}
	return 1;
}