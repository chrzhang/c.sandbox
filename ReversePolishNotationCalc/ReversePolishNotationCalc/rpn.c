#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h>
#include <ctype.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MATHS '1' /* signal that a mathematical function was found*/
#define MAXVAL 100 /* maximum depth of val stack */
#define BUFSIZE 100

void push(double);
double pop(void);
int getop(char[]);
int getch(void);
void ungetch(int);

/*
(Exercise 4-4)
Add the commands to print the top elements of the stack without popping, to
duplicate it, and to swap the top two elements. Add a command to clear the stack.
*/
void top(); // Prints stack's top
void duplicateStack(); // Returns a pointer to a copy
void topSwap(); // Swaps top two elements
void clear(); // Clear current stack

// Exercise 4-5 asks for mathematical library functions
void doMathFn(char s[]);

/*
(Exercise 4-6)
Add commands for handling variables. (It's easy to provide twenty-six variables
with single-letter names.) Add a variable for the most recently printed value.
*/
double a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z;


int sp = 0; /* next free stack position */
int spCopy = -1;
double val[MAXVAL]; /* value stack */
double valCopy[MAXVAL];

/* push: push f onto value stack */
void push(double f) {
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* getop: get next character or numeric operand */
int getop(char s[]) {
	
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		; // Skip white-space
	s[1] = '\0';

	// OPERAND
	if (!isdigit(c) && c != '.' && !isalpha(c)) // Added condition that c is not a letter, which is part of a fn
		return c; /* not a number, a decimal, a space nor a tab, hence it must be an operand */

	// MATHS
	i = 0;
	if (isalpha(c)) { // Letter detected
		while (isalpha(s[++i] = c = getch())) /* collect letter part */
			;
		s[i] = '\0';
		if (c != EOF)
			ungetch(c);
		return MATHS;
	}

	// NUMBER
	i = 0;
	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.') /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c); // "un-read" next character that's not a part of the #
	return NUMBER;
}

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

/* get a (possibly pushed-back) character */
int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c) {
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

// Exercise 4-4 cont.
void top() { // Prints stack's top
	if (sp == 0) {
		printf("error: stack empty\n");
		return;
	}
	printf("%g\n", val[sp - 1]);
}

void duplicateStack() { // Returns a pointer to a copy
	
	for (int i = 0; i < MAXVAL; ++i) {
		valCopy[i] = val[i];
	}
	spCopy = sp;
}

void topSwap() { // Swaps top two elements
	if (sp < 2) {
		printf("error: fewer than two elements in the stack for a swap\n");
		return;
	}
	// Temporarily store the  top value
	double oldTop = val[sp - 1];
	// Assign the top value to the one under it
	val[sp - 1] = val[sp - 2];
	// Assign the value under top to top
	val[sp - 2] = oldTop;
}

void clear() { // Clear current stack
	sp = 0; // Simply consider the stack empty and existing values junk
}

// Exercise 4-5 cont.
void doMathFn(char s[]) {
	
	if (strcmp(s, "sin") == 0) {
		// Apply the math library's sin
		push(sin(pop()));
	}
	else if (strcmp(s, "exp") == 0) {
		// Apply the math library's exp (e^x)
		push(exp(pop()));
	}
	else if (strcmp(s, "pow") == 0) {
		// Requires two operands
		double powerMaybe = pop();
		if (powerMaybe != (int) powerMaybe) {
			printf("The desired power %g is not an integer.\n", powerMaybe);
			return;
		}
		// Faithful to its value, now cast it
		int power = (int)powerMaybe;
		push(pow(pop(), power));
	}
	else
		printf("%s is not an implemented mathematical function.\n", s);
}
/* reverse Polish calculator */
int main() {
	int type; // Hold whether symbol is a number or an op
	double op2; // Hold for additional operand in non-commutative ops like - or /
	char s[MAXOP];
	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0) // As long as it's not dividing by zero
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		/*
		(Exercise 4-3)
		Given the basic framework, it's straightforward to extend the calculator. Add the
		modulus (%) operator and provisions for negative numbers.
		*/
		case '%':
			op2 = pop();
			if (op2 != 0.0) { // Cannot divide by zero
				// Make sure the operand can be loyally casted to an int
				if (op2 == (int)op2) {
					// Make sure the result of pop() can also be considered an int
					double top = pop();
					if (top == (int)top) {
						push(((int)top) % ((int)op2));
					}
					else
						printf("one of the operands (%f) is not an integer\n", top);
				}
				else
					printf("one of the operands (%f) is not an integer\n", op2);
			}
			else
				printf("error: zero divisor\n");
			break;
		/*
		(Exercise 4-5)
		Add access to library functions like sin, exp, and pow.
		*/
		case MATHS:
			doMathFn(s);
			break;
		case '\n':
			printf("\t%.8g\n", pop()); // Print the answer
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}

	printf(">>> Testing the stack functions.\n");
	printf("Clearing stack.\n");
	clear();
	printf("Attempt to pop. Expect an error.\n");
	pop();
	printf("Push on a single value of 42.\n");
	push(42.f);
	printf("Get what is on top of the stack.\n");
	top();
	printf("Popping %g off.\n", pop());
	printf("Now pushing on 3.14 and 1.984.\n");
	push(3.14);
	push(1.984);
	printf("Get what is on top of the stack.\n");
	top();
	printf("Swapping top two elements.\n");
	topSwap();
	printf("Get what is on top of the stack.\n");
	top();
	printf("Popping %g off.\n", pop());
	printf("Get what is on top of the stack.\n");
	top();
	printf("Pushing on 1f through 9f inclusive.\n");
	for (double d = 1.f; d < 10.f; ++d)
		push(d);
	printf("Print all elements of the original stack.\n");
	for (int i = sp - 1; i >= 0; --i)
		printf("%g\n", val[i]);

	printf("Copying stack.\n");
	duplicateStack();
	printf("Clearing current stack.\n");
	clear();
	printf("Print all elements of the copy to know it is still intact.\n");
	for (int i = spCopy - 1; i >= 0; --i)
		printf("%g\n", valCopy[i]);

	getch();
	return 0;
}