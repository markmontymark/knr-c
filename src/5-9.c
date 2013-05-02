
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "common.h"

const char * USAGE = "Rewrite day_of_year and month_day with pointers instead of indexing";

void impl( );

int day_of_year( struct tm * );
int month_day( struct tm * );


int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	impl();
	return 0;
}

void impl( )
{
/*
	time_t t;
	struct tm now;
	&now = localtime(time(&t));
	printf("day of year:  %d\n", day_of_year(&now));
	printf("day of month: %d\n", month_day(&now));
*/
}

int day_of_year( struct tm * t)
{
	return t->tm_yday;	
}

int month_day( struct tm * t)
{
	return t->tm_mday;	
}
