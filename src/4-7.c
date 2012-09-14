  
#include "common.h"

const char * USAGE = "Write a calculator program, write ungets(s) that pushes back an entire string.  Should ungets know about buf and bufp or should it just use ungetch?";

void impl( );

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
}
