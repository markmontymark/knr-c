  
#include "common.h"

const char * USAGE = "Write a calculator program, Our getch/ungetch don't handle pushing EOF back";

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
