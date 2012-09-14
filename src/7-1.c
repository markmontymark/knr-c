  
#include "common.h"

const char * USAGE = "Write a program, like rcfile, that changes behavior based on name of argv[0]";

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
