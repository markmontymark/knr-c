
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

const char * USAGE = "Write tail(int n) to print last n lines...also how about allowing for tail -f ?";

void impl( );
int tail( const char * path, int num_lines );

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	if( argc < 2 )
		return 0;
	const char * path = argv[1];
	int num_lines = atoi(argv[2]);
	tail( path, num_lines );
	return 0;
}

int tail( const char * path, int num_lines )
{
	FILE * f_in;
	if( (f_in = fopen(path, "rb")) == NULL )
	{
		perror(path);
		return errno;
	}
	if( f_in != NULL )
		fclose(f_in);
	return 0;
}
