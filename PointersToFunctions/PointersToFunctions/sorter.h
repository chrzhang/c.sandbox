int numcmp(int reverse, int foldCase, int dirMode, char *s1, char *s2);
int strcmp(int reverse, int foldCase, int dirMode, char *s, char *t);
int dircmp(int reverse, int foldCase, int dirMode, char *s, char *t);
int getline(char *, int);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(void *lineptr[], int left, int right, int(*comp)(int, int, int, void *, void *));
char *alloc(int);
void strcpy(char *s, char *t);