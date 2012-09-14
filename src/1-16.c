
// This file auto-generated on Wed Aug 15 07:52:40 2012_

#include "common.h"

const char * USAGE = "Print the length of arbitrarily long input lines and all the text in line\nArgs: [n - number of chars that define 'long']";

void impl( char * prog, int max );

int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(USAGE,progname);
	int n_chars = 256;
	if(argc > 1)
	{
		n_chars = atoi( argv[1] );
	}
	printf("using %d as max chars per line\n",n_chars);
	impl(progname,n_chars);
	return 0;
}

void impl( char * prog, int max )
{
	//Print the length of arbitrarily long input lines and all the text in line
	int max_1 = max - 1;
	char buf[max];
	char * retval;
	int charsRead;
	while( (retval = fgets(buf,max,stdin)) != NULL )
	{
		charsRead = strlen(retval);
		if(charsRead == max
			&& buf[max_1] != '\n'
		)
		{
			//printf("hit a line w/ more than %d chars\n",max);
			buf[max_1] = '\n';
		}
		//else printf("strlen = %d, max_1 = %d\n",charsRead,max_1);
		printf("%s",buf);
	}
}

