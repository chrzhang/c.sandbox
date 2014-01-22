#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


main() {
	char hodor[MAXLEN] = "hodor";
	char king[MAXLEN] = "king";
	install(hodor, king);
	printf("%s\n", (lookup(hodor)->defn));
	undef(hodor);
	struct nlist * hodorL = lookup(hodor);
	if (hodorL == NULL)
		printf("not found.\n");
	else
		printf("%s\n", (hodorL->defn));
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

/*
(Exercise 6-5)
Write a function undef that will remove a name and definition from the table
maintained by lookup and install.
*/
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