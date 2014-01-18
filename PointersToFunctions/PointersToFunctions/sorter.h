int numcmp(int reverse, char *s1, char *s2);
int strcmp(int reverse, char *s, char *t);
int getline(char *, int);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(int reverse, void *lineptr[], int left, int right,
	int(*comp)(void *, void *));
char *alloc(int);
void strcpy(char *s, char *t);