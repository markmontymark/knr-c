
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "common.h"

const char * USAGE = "Rewrite day_of_year and month_day with pointers instead of indexing";
const char * WRONGARGS = "Usage:\n\
\t./src/5-9 month_day 1973 68 -- will tell what day of month is the 68th day of the year\n\
\t./src/5-9 day_of_year 1870 12 4 -- will tell you the day of December 4th, 1870\n";

int is_leap( int year );
int orig_day_of_year( int year, int month, int day);
void orig_month_day(  int year, int yearday, int * month, int * day);

int day_of_year( struct tm * );
int month_day( struct tm * );

static char daytab[2][13] = {
	{0,31,28,31,30,31,30,31,31,30,31,30,31},
	{0,31,29,31,30,31,30,31,31,30,31,30,31},
};


int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	if( argc < 4 )
	{
		printf("%s\n",WRONGARGS);
		return 0;
	}
	char * cmd = argv[1];
	if( strcmp(cmd,"month_day") == 0 )
	{
		if( argc != 4 )
		{
			printf("%s\n",WRONGARGS);
			return 0;
		}
		int month;
		int day;
		int year = atoi(argv[2]);
		int iday_of_year = atoi(argv[3]);
		orig_month_day( year, iday_of_year, &month, &day );
		printf("orig month_day of %d %d is %d-%02d-%02d\n", year, iday_of_year, year, month, day);
	}
	else if( strcmp(cmd,"day_of_year") == 0 )
	{
		if( argc != 5 )
		{
			printf("%s\n",WRONGARGS);
			return 0;
		}
		
		int year = atoi(argv[2]);
		int month = atoi(argv[3]);
		int day = atoi(argv[4]);
		int dyear = orig_day_of_year( year, month, day );
		printf("orig day_of_year %d-%02d-%02d is %d\n", year, month, day, dyear);
	}
	else
		printf("Didn't understand your command.\n%s\n",WRONGARGS);
	return 0;
}

int day_of_year( struct tm * t)
{
	return t->tm_yday;	
}

int month_day( struct tm * t)
{
	return t->tm_mday;	
}


int is_leap( int year )
{
	return (year % 4 == 0) && ( (year % 100 != 0) || (year % 400 == 0) );
}

int orig_day_of_year( int year, int month, int day)
{
	int i, leap;
	leap = is_leap( year );
	for( i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

void orig_month_day(  int year, int yearday, int * month, int * day)
{
	int i, leap;
	leap = is_leap( year );
	if(yearday < 1 )
	{
		printf("Bad day_of_year, can't be less than 1.\n%s\n",WRONGARGS);
		return;
	}
	if( is_leap)
	{ 
		if( yearday > 366)
		{
			printf("Bad day_of_year for leap year, can't be greater than 366.\n%s\n",WRONGARGS);
			return;
		}
	}
	else if( yearday > 365)
	{
		printf("Bad day_of_year for leap year, can't be greater than 365.\n%s\n",WRONGARGS);
		return;
	}
	for( i = 1; yearday > daytab[leap][i]; i++ )
		yearday -= daytab[leap][i];
	* month = i;
	* day = yearday;
}
