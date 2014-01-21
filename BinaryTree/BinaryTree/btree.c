#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD	100
#define BUFSIZE	100
#define NUMKEYWORDS	32

// External static limits visibility to current file
static char buf[BUFSIZE];
static int bufp = 0;
// Internal static means the variable is local but remains in existence

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
void strcpy2(char *s, char *t);
int isKeyword(char word[]);
int numCharsGreaterThanLim(char word[]);

struct tnode { /* the tree node: */
	char *word; /* points to the text */
	int count; /* number of occurrences */
	struct tnode *left; /* left child */
	struct tnode *right; /* right child */
};

static char *keywords[] = { "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while" };

static unsigned int numChars = 6; // Default value

/*
(Exercise 6-2)
Write a program that reads a C program and prints in alphabetical order each
group of variable names that are identical in the first 6 characters, but different somewhere
thereafter. Don't count words within strings and comments. Make 6 a parameter that can be set
from the command line.
*/
/* word frequency count */
main(int argc, char * argv[]) {
	if (argc > 1)
		numChars = atoi(argv[1]);
	struct tnode *root; // Root of the tree
	
	char word[MAXWORD]; // Current word
	root = NULL; // Initialize it to be empty
	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0])) // If the first character is alplhabetical and NOT a keyword, add it to the tree
			if (!isKeyword(word))
				if (numCharsGreaterThanLim(word)) {
					root = addtree(root, word); // root always contains the first word
				}
	}
	treeprint(root); // Display the tree
	return 0;
}

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	while (isspace(c = getch())) // Ignore whitespace
		;
	if (c != EOF)// Not at the end of the file, set the next char in word to the next non-space
		*w++ = c;
	else
		return c;
	if (!isalpha(c)) { // If the char isn't a letter, end the current word
		
		if (c == '\"') {
			printf("Entering a quote.\n");
			// Get everything until the end of the quote
			while ((c = getch()) != '\"')
				if (c == EOF) {
					printf("error: quote never ends.\n");
					return EOF;
				}
		}

		if (c == '/') {
			if ((c = getch()) == '/') {
				while ((c = getch()) != '\n')
					if (c == EOF) {
						return EOF;
					}
			}
			else if (c == '*') {
				// Entered a block comment
				while (c == getch()) {
					if (c = '*') {
						if ((c = getch()) == '/')
							break;
					}
				}
			}
			else
				ungetch(c);
		}
		if (isspace(c = getch())) { // Check for a succeeding space
			*w = '\0';
			return c; // Return the non-alpha char
		}
		else { // Oops, succeeded by part of a word, give the char back
			ungetch(c);
		}
	}
	for (; --lim > 0; w++) { // Now, provided the char was a letter, get the rest into w
		if (!isalnum(*w = getch())) {
			ungetch(*w); // Unget the non-alphanumeric part of that word
			break;
		}
	}
	*w = '\0'; // End the string
	return word[0];
}

struct tnode *talloc(void);
char *strdup2(char *);

/* talloc: make a tnode (returns a pointer to free space capable of fitting a tree node) */
struct tnode *talloc(void) {
	return (struct tnode *) malloc(sizeof(struct tnode));
}

/* strdup2: copies the string given into a safe place using malloc */
char *strdup2(char *s) { /* make a duplicate of s */
	char *p;
	p = (char *)malloc(strlen(s) + 1); /* +1 for '\0' */
	if (p != NULL)
		strcpy2(p, s);
	return p;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
	int cond;
	if (p == NULL) { /* a new word has arrived */
		p = talloc(); /* make a new node */
		p->word = strdup2(w);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0)
		p->count++; /* repeated word */
	else if (cond < 0) /* less than into left subtree */
		p->left = addtree(p->left, w);
	else /* greater than into right subtree */
		p->right = addtree(p->right, w);
	return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

/* strcpy2: copy t to s; pointer version */
void strcpy2(char *s, char *t) {
	int i;
	i = 0;
	while ((*s = *t) != '\0') {
		s++;
		t++;
	}
}

int isKeyword(char word[]) {
	for (int i = 0; i < NUMKEYWORDS; ++i) {
		if (0 == strcmp(keywords[i], word)) {
			return 1;
		}
	}
	return 0;
}

int numCharsGreaterThanLim(char word[]) {
	return (strlen(word) > numChars);
}