
// This file auto-generated on Wed Aug 15 07:52:40 2012_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include "common.h"

const char * USAGE = "Remove trailing whitespace (except newline) from input lines and delete blank lines";

void impl( char * progname );
int is_blank_line(char * line);
char * remove_trailing_spaces(char * line);

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
	int max = 25;
	char *line[0];
	
	while( read_line(line,max,stdin) != -1 )
	{
		if( is_blank_line( *line) )
			continue;
		*line = remove_trailing_spaces( *line);
		fprintf(stdout,"%s\n",*line);
	}
}

char * remove_trailing_spaces(char * line)
{
	int last_space_idx = -1;
	int len = strlen( line );

	if(len < 1 )
		return line;

	int i = len;
		
	while( --i > -1 && line[i] == ' ') 
		;

	//printf("len is %d, start of last space chars is %d\n", len, i);

	if( i != (len - 1))
	{
		char * linecopy = malloc( len );
		strncat(linecopy,line,i+1);
		return linecopy;
	}
	return line;
}

int is_blank_line(char * line)
{
	if(line == NULL)
		return 1;

	for(int i = 0; line[i]; i++)
		if(line[i] != ' ')
			return 0;

	return 1;
}

