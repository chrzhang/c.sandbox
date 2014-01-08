#include <stdio.h>

int binsearch(int x, int v[], int n);

int main() {
	int nine[] = { 4, 1, 5, 9, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 8, 10, 1, 5};
	binsearch(9, nine, 20);
	binsearch2(9, nine, 10);
	getch();
	return 0;
}

int binsearch(int x, int v[], int n) {
	int low, high, mid;
	int ct = 0; //  Keep count of loops
	low = 0;
	high = n - 1;
	while (low <= high) {
		++ct;
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid + 1;
		else if (x > v[mid])
			low = mid + 1;
		else {
			printf("Operations: %d\n", ct);
			return mid;
		}
	}
	printf("Operations: %d\n", ct);
	return -1;
}

/*
(Exercise 3-1)
Our binary search makes two tests inside the loop, when one would suffice (at
the price of more tests outside.) Write a version with only one test inside the loop and measure
the difference in run-time.
*/
int binsearch2(int x, int v[], int n) {
	int low, high, mid;
	int ct = 0; // Keep count of loops
	low = 0;
	high = n - 1;
	while (low <= high) {
		++ct;
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid + 1;
		else 
			low = mid + 1;
	} // Exit the loop when low > high
	printf("Operations: %d\n", ct);
	if (x == mid) // The last mid calculated is as close to the value as could have been gotten
		return mid; // If what was being looked for does live here, return the location
	else
		return -1; // Not found
}