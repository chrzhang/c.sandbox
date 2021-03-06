#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
void dcl(void);
void dirdcl(void);
int gettoken(void);
int tokentype; /* type of last token */
int considerLast; // Whether to look at the last token 
char token[MAXTOKEN]; /* last token string */
char name[MAXTOKEN]; /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[1000];

main() { // convert declaration to words 
	while (gettoken() != EOF) { // 1st token on line
		strcpy_s(datatype, MAXTOKEN, token); // is the datatype
		out[0] = '\0';
		dcl(); // parse rest of line 
		if (tokentype != '\n' && tokentype != '\r') // carriage return in Windows command-line
			printf("syntax error %d %c \n", tokentype, tokentype);
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}



/* undcl: convert word descriptions to declarations */
/*
int main() {
	printf("undcl\n");
	int type;
	char temp[MAXTOKEN];
	while (gettoken() != EOF) {
		strcpy_s(out, MAXTOKEN, token);
		while (((type = gettoken()) != '\n') && (type != '\r'))
			if (type == PARENS || type == BRACKETS)
				strcat_s(out, MAXTOKEN, token);
			else if (type == '*') {
				sprintf_s(temp, MAXTOKEN, "(*%s)", out);
				strcpy_s(out, MAXTOKEN, temp);
			}
			else if (type == NAME) {
				sprintf_s(temp, MAXTOKEN, "%s %s", token, out);
				strcpy_s(out, MAXTOKEN, temp);
			}
			else
				printf("invalid input at %s\n", token);
	}
	return 0;
}
*/

/*
(Exercise 5-18)
Make dcl recover from input errors.
*/
/* dcl: parse a declarator */
void dcl(void) {
	int ns;
	for (ns = 0; gettoken() == '*';) /* count *'s */
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat_s(out, MAXTOKEN, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void) {
	int type;
	if (tokentype == '(') { /* ( dcl ) */
		dcl();
		if (tokentype != ')') {
			printf("error: missing )\n");
			considerLast = 1; // Look at the last token
		}
	}
	else if (tokentype == NAME) /* variable name */
		strcpy_s(name, MAXTOKEN, token);
	else {
		printf("error: expected name or (dcl)\n");
		considerLast = 1;
	}
	while ((type = gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat_s(out, MAXTOKEN, " function returning");
		else {
			strcat_s(out, MAXTOKEN, " array");
			strcat_s(out, MAXTOKEN, token);
			strcat_s(out, MAXTOKEN, " of");
		}
}

// Skips blanks and tabs, finds next token in the input
// Token: name, pair of parentheses, pair of brackets w/ or wo/ a no. or a single char
int gettoken(void) { /* return next token */
	int c, getch(void);
	void ungetch(int);
	char *p = token;
	if (considerLast) {
		considerLast = 0;
		return tokentype; // Ignore the beginning of the error, return the current valid token
	}
	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy_s(token, MAXTOKEN, "()");
			return tokentype = PARENS;
		}
		else {
			ungetch(c);
			return tokentype = '(';
		}
	}
	else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']';)
			;
		*p = '\0';
		return tokentype = BRACKETS;
	}
	else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch());)
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
	else
		return tokentype = c;
}

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