  
#include "common.h"

const char * USAGE = "Write a calculator program, suppose that there will never be more than one char of pushback, Modify getch and ungetch accordingly";

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
