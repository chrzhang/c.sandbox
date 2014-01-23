#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define HASHSIZE 101
#define MAXLEN 100

struct nlist { /* table entry: */
	struct nlist *next; /* next entry in chain */
	char *name; /* defined name */
	char *defn; /* replacement text */
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

unsigned hash(char *s);
struct nlist *lookup(char *);
struct nlist *install(char *name, char *defn);
char *strdup2(char *);
void strcpy2(char *s, char *t);
void undef(char *name);
int getword(char *word, int lim);

/*
(Exercise 6-6)
Implement a simple version of the #define processor (i.e., no arguments)
suitable for use with C programs, based on the routines of this section. You may also find
getch and ungetch helpful.
*/
main() {
	char word[MAXLEN];
	while (getword(word, MAXLEN) != EOF) {
		if (0 == strcmp(word, "#define")) {
			// Get the next word which follows #define, it will be the key
			char key[MAXLEN];
			getword(key, MAXLEN);
			// Now get the value
			char value[MAXLEN];
			getword(value, MAXLEN);
			printf("Adding key: %s\tvalue: %s\n", key, value);
			install(key, value);
			break;
		}
	}
	return 0;
}

/* hash: form hash value for string s */
unsigned hash(char *s) {
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {
	struct nlist *np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
	if (strcmp(s, np->name) == 0)
		return np; /* found */
	return NULL; /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn) {
	struct nlist *np;
	unsigned hashval;
	if ((np = lookup(name)) == NULL) { /* not found */
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup2(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else /* already there */
		free((void *)np->defn); /*free previous defn */
	if ((np->defn = strdup2(defn)) == NULL)
		return NULL;
	return np;
}

/* undef: remove name and def from table */
void undef(char *name) {
	struct nlist *np;
	struct nlist *prev;
	np = prev = hashtab[hash(name)];
	if (strcmp(name, np->name) == 0) { // Case 1 : first node 
		hashtab[hash(name)] = np->next;
		return;
	}
	for (; np != NULL; np = np->next) { // Case 2 : middle or end
		if (strcmp(name, np->name) == 0) {
			// Delete the block by setting the current linked node to the next
			prev->next = np->next;
		}
		prev = np;
	}
}

/* strdup2: copies the string given into a safe place using malloc */
char *strdup2(char *s) { /* make a duplicate of s */
	char *p;
	p = (char *)malloc(strlen(s) + 1); /* +1 for '\0' */
	if (p != NULL)
		strcpy2(p, s);
	return p;
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

#include <stdio.h>
#define BUFSIZE	100
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
				printf("entered a block comment\n");
				while (c = getch()) {
					if (c == '*') {
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