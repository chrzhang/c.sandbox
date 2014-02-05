#include <stdarg.h>
#include <stdio.h>

/*
(Exercise 7-3)
Revise minprintf to handle more of the other facilities of printf.
*/
void minprintf(char *fmt, ...) {
	va_list ap;
	char *p, *sval;
	int ival;
	double dval;
	void* pval;
	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		switch (*++p) {
		case '%':
			putchar('%');
			break;
		case 'd':
			ival = va_arg(ap, int);
			printf("%d", ival);
			break;
		case 'i':
			ival = va_arg(ap, int);
			printf("%i", ival);
			break;
		case 'o':
			ival = va_arg(ap, int);
			printf("%o", ival);
			break;
		case 'x':
			ival = va_arg(ap, int);
			printf("%x", ival);
			break;
		case 'X':
			ival = va_arg(ap, int);
			printf("%x", ival);
			break;
		case 'u':
			ival = va_arg(ap, int);
			printf("%u", ival);
			break;
		case 'c':
			ival = va_arg(ap, int);
			printf("%c", ival);
			break;
		case 'f':
			dval = va_arg(ap, double);
			printf("%f", dval);
			break;
		case 'e':
			dval = va_arg(ap, double);
			printf("%e", dval);
			break;
		case 'E':
			dval = va_arg(ap, double);
			printf("%E", dval);
			break;
		case 'g':
			dval = va_arg(ap, double);
			printf("%g", dval);
			break;
		case 'G':
			dval = va_arg(ap, double);
			printf("%G", dval);
			break;
		case 'p':
			pval = va_arg(ap, void*);
			printf("%p", pval);
			break;
		case 's':
			for (sval = va_arg(ap, char *); *sval; sval++)
				putchar(*sval);
			break;
		default:
			putchar(*p);
			break;
		}
	}
	va_end(ap);
}

int main() {
	minprintf("Hello.%d%%\n", 100);
	printf("Hello.%d%%\n", 100);
	return 0;
}