
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

const char * USAGE = "Write htoi which converts a char * of hex digits into an int number";


void impl( );
int htoi(char *);


int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(USAGE,progname);
	impl();
	return 0;
}

void impl( )
{
	printf("htoi %s = %d\n", "0X2A",htoi("0X2A"));
	printf("htoi %s = %d\n", "0x2A",htoi("0x2A"));
	printf("htoi %s = %d\n", "0x2a",htoi("0x2a"));
	printf("htoi %s = %d\n", "0x2",htoi("0x2"));
}

int htoi(char * str)
{
	int retval = 0;
	if( strstr(str,"0X") != NULL || strstr(str,"0x") != NULL)
	{
		*++str;
		*++str;
	}
	int len = strlen(str);
	
	char c;
	for(int i=len-1, j = 0; i > -1; i--, j++)
	{
		c = str[i];
		switch( c )
		{
			case 'A': case 'B': case 'C':
			case 'D': case 'E': case 'F':
				retval += pow(16,j) * ((c - 'A') + 10);
				break;
			case 'a': case 'b': case 'c':
			case 'd': case 'e': case 'f':
				retval += pow(16,j) * ((c - 'a') + 10 );
				break;
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9': 
				retval += pow(16,j) * ((c - '0'));
				break;
		}
	}

	return retval;
}

