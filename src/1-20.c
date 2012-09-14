
// This file auto-generated on Wed Aug 15 07:52:40 2012_

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "common.h"

const char * USAGE = "detab - replace tabs with N spaces";
const char * SHIFTWIDTH = "   ";
const int MAX_CHARS = 1024;

void impl( char * progname );

int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(USAGE,progname);
	impl(progname);
	return 0;
}

void impl( char * progname )
{
	int nCharsRead;
	char * charsRead;
	char buf[MAX_CHARS];
	while( (charsRead = fgets(buf,MAX_CHARS,stdin)) != NULL )
	{
		nCharsRead = strlen(charsRead);
		for(int i = 0; i < nCharsRead; i++)
		{
			if(charsRead[i] == '\t')
				fputs(SHIFTWIDTH,stdout);
			else
				fputc(charsRead[i],stdout);
		}
	}
}

