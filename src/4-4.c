  
#include "common.h"

const char * USAGE = "Write a calculator program, add commands to print the top stack element without popping, duplicate the top element, and to swap the top two elements.  Add a command to clear the stack";

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
