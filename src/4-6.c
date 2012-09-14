  
#include "common.h"

const char * USAGE = "Write a calculator program, add cmds for creating, retrieving variables.";

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
