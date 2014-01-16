#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXOPLEN	10
#define NUMBER	'0'
#define MAXVAL	100

int sp = 0;
double val[MAXVAL];

double expr(int argc, char *argv[]);
void push(double d);
double pop(void);

main(int argc, char *argv[]) {
	double a = expr(argc, argv);
	printf("\t%.8g\n", a);
	getch();
	return 0;
}

/*
(Exercise 5-10)
Write the program expr, which evaluates a reverse Polish expression from the
command line, where each operator or operand is a separate argument. For example,
expr 2 3 4 + *
evaluates 2 * (3+4).
*/
double expr(int argc, char *argv[]) {
	// Iterate through the args
	for (int i = 1; i < argc; ++i) {
		int type = getop(argv[i]);
		double op2;
		switch (type) {
		case NUMBER:
			push(atof(argv[i]));
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
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		default:
			printf("error: unknown command %s\n", argv[i]);
			break;
		}
	}
	return (pop());
}

int getop(char s[]) {
	// Operand
	if (!isdigit(*s) && *s != '.') {
		return *s;
	}
	// Number
	else
		return NUMBER;
}

void push(double d) {
	if (sp < MAXVAL)
		val[sp++] = d;
	else
		printf("error: stack full, can't push %g\n", d);
}

double pop(void) {
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}