#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h>
#include <ctype.h>
#include <string.h>

#define MAXOP	100 /* max size of operand or operator */
#define NUMBER	'0' /* signal that a number was found */
#define MATHS	'1' /* signal that a mathematical function was found*/
#define VARIABLE	'2' /*signal that a variable was found */
#define ASSIGNMENT	'3' /* signal that a new variable is being assigned*/
#define RECENT	'4'
#define MAXVAL	100 /* maximum depth of val stack */
#define BUFSIZE	100
#define MAXLINE	1000

void push(double);
double pop(void);
int getop(char[]);
int getline();

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

A calculator typically allows users to define variables using the alphabet and Greek letters.
Only the 26 English alphabetical characters in their CAPITALIZED forms will be used.
They will be stored with an alpha-char for name, a double value, and an int flag (1 or 0)
for whether or not the variable has been assigned (with the = operator) by the user.

To allow user to interact with variables, allow
1. assignment operator (=)
usage: "A = 10.0" supported, variable name 'A' must come first, followed by '=' then its value
2. using variables instead of values
3. printing all currently used variables
4. resetting all variables
5. automatically assigning the last printed value
*/
int visited[26] = { 0 }; // Default variables are unused, flagged 0
double values[26]; // Contain the values for each variable
double recent; // Store the last printed value, use ^ to ref
void printVars(); // Print currently assigned variables
void resetVars(); // Reset all variables to 0

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
	// With the addition of getline, guaranteed no leading or trailing white-space
	int i, c;
	// ASSIGNMENT
	if (s[1] == '=') { // Without making the program too complex, assume assignment has no spaces ("A=5" is supported)
		return ASSIGNMENT;
	}
	c = s[0];
	// RECENT
	if (c == '^') {
		return RECENT; // Most recently output value, a double
	}
	// OPERAND
	if (!isdigit(c) && c != '.' && !isalpha(c)) // Added condition that c is not a letter, which is part of a fn
		return c; /* not a number, a decimal, a space, a tab, nor a letter, hence it must be an operand */
	
	// VARIABLE
	if (isalpha(c) && (c >= 'A' && c <= 'Z')) {
		// This variable may have formerly been assigned or is being assigned
		return VARIABLE;
	}
	// MATHS
	i = 0;
	if (isalpha(c)) { // Letter detected
		while (isalpha(s[++i])) /* collect letter part */
			;
		if (c != EOF)
			ungetch(c);
		return MATHS;
	}
	// NUMBER
	i = 0;
	if (isdigit(c)) /* collect integer part */
	while (isdigit(s[++i]))
		;
	if (s[i] == '.') /* collect fraction part */
	while (isdigit(s[++i]))
		;
	if (c != EOF)
		ungetch(c); // "un-read" next character that's not a part of the #
	return NUMBER;
}

// Exercise 4-4 cont.
void top() { // Prints stack's top
	if (sp == 0) {
		printf("error: stack empty\n");
		return;
	}
	printf("%g\n", val[sp - 1]);
}

void duplicateStack() {
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
		if (powerMaybe != (int)powerMaybe) {
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

// Exercise 4-6 cont.
void printVars() {
	for (int i = 0; i < 26; ++i) {
		if (visited[i])
			printf("%c: %g\n", i + 'A', values[i]);
	}
}

void resetVars() {
	for (int i = 0; i < 26; ++i) {
		visited[i] = 0;
	}
}

/*
(Exercise 4-10)
An alternate organization uses getline to read an entire input line; this makes
getch and ungetch unnecessary. Revise the calculator to use this approach.
*/
int getline(char s[], int lim) {
	int c, i;
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

void processWord(char s[]) {
	int type; // Hold whether symbol is a number or an op
	double op2; // Hold for additional operand in non-commutative ops like - or /
	type = getop(s);
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
				// Make sure the operand can be accurately casted to an int
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
		// Exercise 4-6 cont.
		case VARIABLE:
			// Check to make sure variable is visited
			if (visited[s[0] - 'A']) {
				// Now replace the letter with the proper value
				push(values[s[0] - 'A']);
			}
			else {
				printf("%c was never assigned to a value.\n", s[0]);
			}
			break;
		case ASSIGNMENT:
			// Assignment is not written in post-fix
			if (s[0] >= 'A' && s[0] <= 'Z') { // Ensure var name valid
				// Assign the value to receiverOn
				char numberStr[MAXLINE];
				for (int i = 2; s[i] != '\0' && s[i] != '\n'; ++i) {
					numberStr[i - 2] = s[i];
				}
				values[s[0] - 'A'] = atof(numberStr);
				visited[s[0] - 'A'] = 1;
				return;
			}
			else {
				printf("Assignment attempt detected. Please use capital single-letter variables and the assignment should not have spaces.");
			}
			break;
		case RECENT:
			printf("recent\n");
			push(recent);
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
	}
}

/* reverse Polish calculator */
int main() {
	printf("\tA Postfix Calculator.\nPlease use single capital characters as variables.\n");
	char s[MAXOP];
	char line[MAXLINE];
	int len;
	// For each line to be evaluated
	while ((len = getline(line, MAXLINE)) > 0) {
		int i = 0;
		int state = 0;
		int j = 0;
		while (i < len) {
			if (line[i] == ' ' || (i+1 == len)) {
				if (i + 1 == len)
					s[j++] = line[i];
				s[j] = '\0';
				processWord(s);
				state = 0;
				j = 0;
			}
			else
				state = 1;
			if (state)
				s[j++] = line[i];
			++i;
		}
		if (sp > 0) {
			// Store the result
			recent = val[sp - 1];
			printf("\t%.8g\n", pop()); // Print the answer
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