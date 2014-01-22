#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD	100
#define BUFSIZE	100
#define WORDCT	1000
#define NUMKEYWORDS	32

// External static limits visibility to current file
static char buf[BUFSIZE];
static int bufp = 0;

static struct tnode* nodeBuf[WORDCT];
static int currNode = 0;
void populate(struct tnode *p);

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
void strcpy2(char *s, char *t);

int nodecmp(struct tnode *t1, struct tnode *t2);
void qsort2(void *v[], int left, int right);
void swap(void *v[], int i, int j);

struct tnode { /* the tree node: */
	char *word; /* points to the text */
	unsigned int count; /* number of occurrences */
	struct tnode *left; /* left child */
	struct tnode *right; /* right child */
};

/*
(Exercise 6-4)
Write a program that prints the distinct words in its input sorted into decreasing
order of frequency of occurrence. Precede each word by its count.
*/
/* word frequency count */
main() {
	struct tnode *root; // Root of the tree

	char word[MAXWORD]; // Current word
	root = NULL; // Initialize it to be empty
	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0])) // If the first character is alplhabetical and NOT a keyword, add it to the tree
			root = addtree(root, word); // root always contains the first word
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
	populate(p);
	qsort2(nodeBuf, 0, currNode - 1);
	for (int i = currNode - 1; i >= 0; --i) {
		printf("%d\t%s\n", nodeBuf[i]->count, nodeBuf[i]->word);
	}
}

void populate(struct tnode *p) {
	if (p != NULL) {
		populate(p->left);
		// Add the node to the buffer array 
		if (currNode == WORDCT) {
			printf("error: too many words.\n");
			return;
		}
		nodeBuf[currNode++] = p;
		populate(p->right);
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

/* qsort2: sort v[left]...v[right] into decreasing order */
void qsort2(void *v[], int left, int right) {
	int i, last;
	void swap(void *v[], int, int);
	if (left >= right) /* do nothing if array contains */
		return; /* fewer than two elements */
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
	if (nodecmp(v[i], v[left]) < 0)
		swap(v, ++last, i);
	swap(v, left, last);
	qsort2(v, left, last - 1);
	qsort2(v, last + 1, right);
}

/* numcmp: compare s1 and s2 numerically */
int nodecmp(struct tnode *t1, struct tnode *t2) {
	unsigned int t1count, t2count;
	t1count = t1->count;
	t2count = t2->count;
	if (t1count < t2count)
		return -1;
	else if (t1count > t1count)
		return 1;
	else
		return 0;
}

void swap(void *v[], int i, int j) {
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}