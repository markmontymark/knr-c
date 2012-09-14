
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

const char * USAGE = "Write escape(to,from) which converts newline to \n and tab to \t";

void impl( );
void escape(char * from,char * to);
void convert(char * newchars,char * from, char * to);

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
	char * from = "This is a sentence with a literal newline -\n- and a literal -\t-.";
	char * to = malloc(sizeof(from));
	escape(from,to);
	printf("from: %s\nto  : %s\n",from,to);

	from = "T\n\n\n\n\n\n\n\n\nhis is a sentence \t\t\t\twith a literal newline -\n- and a literal -\t-.";
	to = malloc(sizeof(from));
	escape(from,to);
	printf("from: %s\nto  : %s\n",from,to);
}

void escape(char * from,char * to)
{
	while( *from )
	{
		if( *from == '\n')
		{
			*to = '\\';
			*to++;
			*to = 'n';
			*to++;
		}
		else if( *from == '\t')
		{
			*to = '\\';
			*to++;
			*to = 't';
			*to++;
		}
		else
		{
			*to = *from;
			to++;
		}	
		from++;
	}
}
