#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = {
	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

/*
(Exercise 5-8)
There is no error checking in day_of_year or month_day.
Remedy this defect.
*/

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
	if (!(year > 0)) {
		printf("Year must be positive.\n");
		return -1;
	}	
	if (!(month > 0 && month <= 12)) {
		printf("Month must be between 1 and 12.\n");
		return -1;
	} 
	if (!(day > 0 && day <= 31)) {
		printf("Day must be between 1 and 31.\n");
	}
	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	if (day > daytab[leap][month]) {
		printf("There are only %d days in this month.\n", daytab[leap][month]);
		return -1;
	}
	for (i = 1; i < month; i++)
		// Choose from the two calendars based on whether 0 or 1 (as indices) it's a leap year
		day += daytab[leap][i]; 
	return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
	if (!(year > 0)) {
		printf("Year must be positive.\n");
		return -1;
	}
	if (!(yearday <= 366 && yearday > 0)) {
		printf("Day of year must be between 1 and 366.\n");
		return -1;
	}
	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	if ((!leap) && (yearday == 366)) {
		printf("It's not a leap year so the day-of-year cannot be 366.\n");
		return -1;
	}
	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}

main() {
	int m = 0;
	int d = 0;
	int * month = &m;
	int * day = &d;
	// Find the day's position in the calendar with month and day for first four days of each month
	for (int i = 1; i < 13; ++i) {
		for (int j = 1; j < 5; ++j) {
			int doy = day_of_year(2014, i, j);
			//printf("Month: %d Day: %d -> %d\n", i, j, doy);
			// Confirm that going forwards and backwards works
			month_day(2014, doy, month, day);
			//printf("Day of Year: %d -> Month: %d Day: %d\n", doy, *month, *day);
			if (i != *month) {
				printf("Months are inaccurate.\n");
				return;
			}
			if (j != *day) {
				printf("Days are inaccurate.\n");
				return;
			}
		}
	}
	// Attempt erroneous input
	day_of_year(-2014, 3, 5); // Negative year
	day_of_year(2014, 50, 6); // 50th month
	day_of_year(2014, 12, -3); // Negative day
	day_of_year(2014, 2, 29); // A leap day on a non-leap year
	month_day(2014, 366, month, day); // A leap day on a non-leap year
	month_day(-2014, 365, month, day); // Negative year
	month_day(0, 365, month, day); // Zero year
	getch();
	return 0;
}