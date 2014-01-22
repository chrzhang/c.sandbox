#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD	100
#define BUFSIZE	100

// External static limits visibility to current file
static char buf[BUFSIZE];
static int bufp = 0;
// Internal static means the variable is local but remains in existence

struct tnode *addtree(struct tnode *, char *, unsigned int lineNum);
void treeprint(struct tnode *);
int getword(char *, int, unsigned int*);
void strcpy2(char *s, char *t);

int isNoise(char word[]);

struct linkednode *nalloc(void);
struct linkednode *addnode(struct linkednode *head, struct linkednode *next, unsigned int lineNum);
void printll(struct linkednode *p);

struct tnode { /* the tree node: */
	char *word; /* points to the text */
	struct linkednode *linkedHead; /* number of occurrences */
	struct tnode *left; /* left child */
	struct tnode *right; /* right child */
};

struct linkednode {
	unsigned int lineNum;
	struct linkednode *next;
};

/*
(Exercise 6-3)
Write a cross-referencer that prints a list of all words in a document, and for
each word, a list of the line numbers on which it occurs. Remove noise words like ``the,''
``and,'' and so on.

The test for noise words is accomplished with strcmp.
used a linked list implementation hybrid with the given binary tree to store page numbers.
*/
/* word frequency count */
main() {
	struct tnode *root; // Root of the tree

	char word[MAXWORD]; // Current word
	root = NULL; // Initialize it to be empty
	unsigned int lineNum = 1;
	while (getword(word, MAXWORD, &lineNum) != EOF) {
		if (isalpha(word[0])) // If the first character is alplhabetical, add it to the tree
			if (!isNoise(word))
				root = addtree(root, word, lineNum); // root always contains the first word
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
int getword(char *word, int lim, unsigned int *lineNum) {
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	while (isspace(c = getch())) {// Ignore whitespace
		if (c == '\n')
			*lineNum = *lineNum + 1;
		;
	}
	if (c != EOF)// Not at the end of the file, set the next char in word to the next non-space
		*w++ = c;
	else
		return c;
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

/* nalloc: make a linkednode (returns a pointer to free space capable of fitting a linked node) */
struct linkednode *nalloc(void) {
	return (struct linkednode *) malloc(sizeof(struct linkednode));
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
struct tnode *addtree(struct tnode *p, char *w, unsigned int lineNum) {
	int cond;
	if (p == NULL) { /* a new word has arrived */
		p = talloc(); /* make a new node */
		p->word = strdup2(w);
		p->linkedHead = NULL;
		// Set the linkedHead to the line number
		p->linkedHead = addnode(p->linkedHead, NULL, lineNum);
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0) {
		// Temporarily store the linked list's head
		struct linkednode * temp = p->linkedHead;
		// Reset the head to a newly allocated linkednode
		p->linkedHead = NULL;
		// Set the next of the head to the old head
		p->linkedHead = addnode(p->linkedHead, temp, lineNum);
	}
	else if (cond < 0) { /* less than into left subtree */
		p->left = addtree(p->left, w, lineNum);
	}
	else { /* greater than into right subtree */
		p->right = addtree(p->right, w, lineNum);
	}
	return p;
}

/* addnode: add a node in the linked list with the given line number and the specified pointer for next*/
struct linkednode *addnode(struct linkednode *head, struct linkednode *next, unsigned int lineNum) {
	if (head == NULL) { 
		head = nalloc();
		head->lineNum = lineNum;
		head->next = next;
	}
	// The head always has the most recently added line number and duplicate line numbers for a word occuring more
	// than once is silly (makes output hard to read, but the following block is kept for making
	// future modifications easier
	else if ((head->lineNum == lineNum)) {
		// Do nothing
	}
	return head;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {
	if (p != NULL) {
		treeprint(p->left);
		printf("%s\t", p->word);
		printll(p->linkedHead);
		putchar('\n');
		treeprint(p->right);
	}
}

/* printll: print the linked list of page numbers */
void printll(struct linkednode *head) {
	while (head != NULL) {
		printf("%d ", head->lineNum);
		head = head->next;
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

int isNoise(char word[]) {
	return (0 == strcmp(word, "and") ||
		0 == strcmp(word, "the"));
}