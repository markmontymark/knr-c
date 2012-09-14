
// This file auto-generated on Wed Aug 15 07:52:40 2012_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "common.h"

const char * USAGE = "Bork all input lines longer than <argv[1]>chars";

//int can_open_data_file(const char * progname)
//void usage(const char * progname)
//void get_progname(char * path)
//int open_data_file(const char * progname,FILE * fp)
//void close_data_file(FILE * fp)

void impl( char * progname , int max_line_length );

int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(USAGE,progname);
	int max_line_length = 256;
	if(argc > 1)
		max_line_length = atoi(argv[1]);
	printf("Max line length %d\n",max_line_length);
	impl(progname, max_line_length);
	return 0;
}

void impl( char * progname , int max_line_length  )
{
	//const char * USAGE = "Print all input lines longer than 80 characters";
	int nCharsRead;
	int maxRead = max_line_length - 1;
	char buf[max_line_length];
	char * charsRead;
	while( (charsRead = fgets(buf,max_line_length,stdin)) != NULL )
	{
		nCharsRead = strlen(charsRead);
		if(nCharsRead == maxRead &&
			charsRead[nCharsRead] != '\n')
		{
			printf("long line: %s\n",charsRead);
		}
		else
		{
			printf("not long line: %s %d\n",charsRead, strlen(charsRead));
		}
	}
}

