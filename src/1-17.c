#include "common.h"


const char * USAGE = "Break all input lines longer than atoi(<argv[1]>) characters";


void impl( );

int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(USAGE,progname);
	int max_length = 80;
	if(argc > 1)
		max_length = atoi(argv[1]);
	impl(max_length);
	return 0;
}

void impl( int max_length )
{
	char buf[max_length];
	char * retval;
	int charsRead = 0;
	while( (retval = fgets(buf,max_length,stdin)) != NULL )
	{
		fputs(retval,stdout);
		charsRead = strlen(retval);
		if(charsRead+1 == max_length && *(retval+charsRead-1) != '\n')
			fputs("\n",stdout);
	}
}

