#include <stdio.h>

/*
(Exercise 4-14)
Define a macro swap(t,x,y) that interchanges two arguments of type t.
(Block structure will help.)
Note lack of semicolon after while(0)
*/
#define swap(t,x,y) do {t temp = x; x = y; y = temp;} while(0) 

main() {
	int a = 45;
	int b = 67;
	printf("a=%d\nb=%d\n", a, b);
	swap(int, a, b);
	printf("Swapping a and b.\n");
	printf("a=%d\nb=%d\n", a, b);
	getch();
	return 0;
}